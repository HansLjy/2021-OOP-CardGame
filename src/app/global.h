#pragma once
#include "wx/panel.h"

const int k_window_length = 1000;
const int k_window_height = 800;

const wxPoint k_default_position(50, 50);
const wxSize k_default_size(k_window_length, k_window_height);

const wxColour k_bgcolor("#EFEFEF");
const wxPen invisible_pen(k_bgcolor);
const wxBrush invisible_brush(k_bgcolor);