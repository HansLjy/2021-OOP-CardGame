#include "center_block_sizer.h"

CenterBlockSizer::CenterBlockSizer (wxWindow *p_parent)
	: wxBoxSizer(wxVERTICAL), p_parent(p_parent) {
	panel = new wxPanel(p_parent);
	panel_box = new wxBoxSizer(wxVERTICAL);
	hbox = new wxBoxSizer(wxHORIZONTAL);
}

void CenterBlockSizer::AddWidget (bool new_line, wxWindow* widget) {
	static wxBoxSizer *cur_sizer = nullptr;
	if (new_line) {
		cur_sizer = new wxBoxSizer(wxHORIZONTAL);
		hboxes.push_back(cur_sizer);
	}

	cur_sizer->Add(widget, 1, wxALIGN_LEFT | wxBOTTOM | wxUP, 5);
}

void CenterBlockSizer::Create () {
	for (auto &sizer : hboxes) {
		panel_box->Add(sizer);
	}
	panel->SetSizer(panel_box);

	hbox->Add(new wxPanel(p_parent), 1, wxEXPAND);
	hbox->Add(panel, 1, wxEXPAND);
	hbox->Add(new wxPanel(p_parent), 1, wxEXPAND);

	Add(new wxPanel(p_parent), 1, wxEXPAND);
	Add(hbox, 1, wxEXPAND);
	Add(new wxPanel(p_parent), 1, wxEXPAND);
}