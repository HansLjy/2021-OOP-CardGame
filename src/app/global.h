#pragma once
#include "wx/panel.h"
#include "wx/font.h"
#include "wx/colour.h"
#include "wx/pen.h"
#include "wx/brush.h"

const int k_window_length = 1200;
const int k_window_height = 1000;

const wxPoint k_default_position(50, 50);
const wxSize k_default_size(k_window_length, k_window_height);

const wxColour	k_bgcolor("#EFEFEF");
const wxPen		invisible_pen(k_bgcolor);
const wxBrush	invisible_brush(k_bgcolor);
const wxFont	h1_font(30, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
const wxFont	button_font(18, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
const wxFont	label_font(18, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
