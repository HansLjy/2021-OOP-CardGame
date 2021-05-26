#include <iostream>
#include "pages.h"
#include "wx/button.h"
#include "wx/sizer.h"
#include "wx/spinctrl.h"
#include "image_panel.h"
#include "page_control_event.h"

MainMenu::MainMenu(wxWindow* p_parent)
	: wxPanel(p_parent), p_parent(p_parent) {

	right_panel = new wxPanel(this);
	title 		= new wxStaticText(right_panel, wxID_ANY, wxT("Main Menu"));
	image 		= new wxImagePanel(this, wxString("./static/UNO.jpg"), wxBITMAP_TYPE_JPEG);
	b_play_UNO  = new wxButton(right_panel, mainID_play_UNO, wxT("Play UNO"));
	b_play_Poke = new wxButton(right_panel, mainID_play_Poke, wxT("Play Poke"));
	b_quit 		= new wxButton(right_panel, wxID_EXIT, wxT("Quit"));

	wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);

	hbox->Add(image, 1, wxEXPAND | wxALL, 20);
	
	vbox->Add(title, 	   1, wxALIGN_CENTER_HORIZONTAL | wxUP | wxBOTTOM, 10);
	vbox->Add(b_play_UNO,  1, wxALIGN_CENTER_HORIZONTAL | wxUP | wxBOTTOM, 5);
	vbox->Add(b_play_Poke, 1, wxALIGN_CENTER_HORIZONTAL | wxUP | wxBOTTOM, 5);
	vbox->Add(b_quit, 	   1, wxALIGN_CENTER_HORIZONTAL | wxUP | wxBOTTOM, 5);
	right_panel->SetSizer(vbox);

	hbox->Add(right_panel, 1, wxALIGN_CENTER | wxUP | wxBOTTOM, 10);

	SetSizer(hbox);

	Connect(mainID_play_UNO,  wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(OnPlayUNO));
	Connect(mainID_play_Poke, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(OnPlayPoke));
	Connect(wxID_EXIT, 		  wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(OnQuit));
}

void MainMenu::OnQuit(wxCommandEvent& event) {
	event.Skip();
}

void MainMenu::OnPlayUNO(wxCommandEvent& event) {
	std::cerr << "Select UNO" << std::endl;
	event.Skip();
}

void MainMenu::OnPlayPoke(wxCommandEvent& event) {
	std::cerr << "Select Poke" << std::endl;
	event.Skip();
}

SubMenu::SubMenu (wxWindow* p_parent, GameType game_type) 
	: wxPanel (p_parent), p_parent(p_parent) {
	switch (game_type) {
		case kUNO :
			title = new wxStaticText(this, wxID_ANY, wxT("UNO"));
			image = new wxImagePanel(this, wxString("static/UNO.jpg"), wxBITMAP_TYPE_JPEG);
			break;
		case kPoke :
			title = new wxStaticText(this, wxID_ANY, wxT("Poke"));
			image = new wxImagePanel(this, wxString("static/Poke.jpg"), wxBITMAP_TYPE_JPEG);
			break;
	}
	b_single = new wxButton(this, subID_single, wxT("Single Player"));
	b_multi  = new wxButton(this, subID_multi,  wxT("Multi Player"));
	b_back   = new wxButton(this, subID_back,   wxT("Back to main"));

	wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);

	hbox->Add(image, 1, wxEXPAND | wxALL, 20);
	
	vbox->Add(title,	1, wxALIGN_CENTER_HORIZONTAL | wxUP | wxBOTTOM, 10);
	vbox->Add(b_single,	0, wxALIGN_CENTER_HORIZONTAL | wxUP | wxBOTTOM, 5);
	vbox->Add(b_multi,	0, wxALIGN_CENTER_HORIZONTAL | wxUP | wxBOTTOM, 5);
	vbox->Add(b_back,	0, wxALIGN_CENTER_HORIZONTAL | wxUP | wxBOTTOM, 5);

	hbox->Add(vbox, 1, wxALIGN_CENTER | wxUP | wxBOTTOM, 10);

	SetSizer(hbox);

	Connect(subID_single,	wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(OnSingle));
	Connect(subID_multi,	wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(OnMulti));
	Connect(subID_back,		wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(OnBack));
}

void SubMenu::OnSingle(wxCommandEvent& event) {
	std::cerr << "Select Single" << std::endl;
	event.Skip();
}

void SubMenu::OnMulti(wxCommandEvent& event) {
	std::cerr << "Select Multi" << std::endl;
	event.Skip();
}

void SubMenu::OnBack(wxCommandEvent& event) {
	std::cerr << "Back" << std::endl;
	event.Skip();
}

SingleGameMenu::SingleGameMenu (wxWindow* p_parent)
	: wxPanel (p_parent), p_parent(p_parent) {

	wxPanel *panel = new wxPanel(this);

	title = new wxStaticText(panel, wxID_ANY, wxT("Single Player Mode"));
	user_name_label = new wxStaticText(panel, wxID_ANY, wxT("User Name: "));
	user_name_input = new wxTextCtrl(panel, singleID_player_number, wxT("Player NO.1"));
	user_number_label = new wxStaticText(panel, wxID_ANY, wxT("Player Number: "));
	user_number_input = new wxSpinCtrl(panel, singleID_player_number, wxT("4"));
	confirm = new wxButton(panel, singleID_confirm, wxT("confirm"));
	go_back = new wxButton(panel, singleID_back, wxT("return"));

	wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *panel_box = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *hbox1 = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer *hbox2 = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer *hbox3 = new wxBoxSizer(wxHORIZONTAL);

	hbox1->Add(user_name_label, 0, wxALIGN_LEFT);
	hbox1->Add(user_name_input, 0, wxALIGN_LEFT);
	hbox2->Add(user_number_label, 0, wxALIGN_LEFT);
	hbox2->Add(user_number_input, 0, wxALIGN_LEFT);
	hbox3->Add(confirm, 0, wxCENTER);
	hbox3->Add(go_back, 0, wxCENTER);

	panel_box->Add(title, 0, wxALIGN_CENTER_HORIZONTAL | wxUP | wxBOTTOM, 20);
	panel_box->Add(hbox1, 0, wxALIGN_CENTER_HORIZONTAL | wxUP | wxBOTTOM, 20);
	panel_box->Add(hbox2, 0, wxALIGN_CENTER_HORIZONTAL | wxUP | wxBOTTOM, 20);
	panel_box->Add(hbox3, 0, wxALIGN_CENTER_HORIZONTAL | wxUP | wxBOTTOM, 20);

	panel->SetSizer(panel_box);
	vbox->Add(panel, 1, wxALL | wxEXPAND, 20);
	SetSizer(vbox);
}