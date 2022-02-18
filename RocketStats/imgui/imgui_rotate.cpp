#include "imgui_rotate.h"
#include "imgui_internal.h"

int rotation_start_index;
ImDrawList* rotation_drawlist;

void ImRotateStart(ImDrawList* drawlist) 
{ 
	rotation_drawlist = drawlist;
	rotation_start_index = drawlist->VtxBuffer.Size;
}

ImVec2 ImRotationCenter()
{
	ImVec2 l(FLT_MAX, FLT_MAX), u(-FLT_MAX, -FLT_MAX); // bounds

	const auto& buf = rotation_drawlist->VtxBuffer;
	for (int i = rotation_start_index; i < buf.Size; ++i)
		l = ImMin(l, buf[i].pos), u = ImMax(u, buf[i].pos);

	return ImVec2{ ((l.x + u.x) / 2), ((l.y + u.y) / 2) }; // or use _ClipRectStack?
}

//ImVec2 operator-(const ImVec2& l, const ImVec2& r) { return { l.x - r.x, l.y - r.y }; }

void ImRotateEnd(float rad, ImVec2 center)
{
	float s = float(sin(rad)), c = float(cos(rad));
	center = (ImRotate(center, s, c) - center);

	auto& buf = rotation_drawlist->VtxBuffer;
	for (int i = rotation_start_index; i < buf.Size; ++i)
		buf[i].pos = (ImRotate(buf[i].pos, s, c) - center);
}