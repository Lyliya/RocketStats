#pragma once
#include "imgui.h"

extern int rotation_start_index;
extern ImDrawList* rotation_drawlist;

void ImRotateStart(ImDrawList* drawlist);
ImVec2 ImRotationCenter();
void ImRotateEnd(float rad, ImVec2 center = ImRotationCenter());
