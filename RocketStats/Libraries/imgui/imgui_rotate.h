#pragma once
#include "imgui.h"

extern int rotation_start_index;
extern ImDrawList* rotation_drawlist;

int ImRotateStart(ImDrawList* drawlist = nullptr);
ImVec2 ImRotationCenter(int start = rotation_start_index, ImDrawList* drawlist = nullptr);
void ImRotateEnd(float rad, int start = rotation_start_index, ImDrawList* drawlist = rotation_drawlist, ImVec2 center = ImRotationCenter());
