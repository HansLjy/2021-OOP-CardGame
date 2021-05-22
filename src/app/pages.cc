#include <iostream>
#include "pages.h"
#include "wx/button.h"
#include "wx/sizer.h"
#include "image_panel.h"
#include "page_control_event.h"

MainMenu::MainMenu(wxWindow* p_parent)
	: wxPanel(p_parent), p_parent(p_parent) {

	title = new wxStaticText(this, wxID_ANY, wxT("Main Menu"));
	image = new wxImagePanel(this, wxString("./static/UNO.jpg"), wxBITMAP_TYPE_JPEG);
	b_play_UNO = new wxButton(this, mainID_play_UNO, wxT("Play UNO"));
	b_play_Poke = new wxButton(this, mainID_play_Poke, wxT("Play Poke"));
	b_quit = new wxButton(this, wxID_EXIT, wxT("Quit"));

	wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);


	hbox->Add(image, 1, wxEXPAND | wxALL, 20);
	
	vbox->Add(title, 1, wxALIGN_CENTER_HORIZONTAL | wxUP | wxBOTTOM, 10);
	vbox->Add(b_play_UNO, 0, wxALIGN_CENTER_HORIZONTAL | wxUP | wxBOTTOM, 5);
	vbox->Add(b_play_Poke, 0, wxALIGN_CENTER_HORIZONTAL | wxUP | wxBOTTOM, 5);
	vbox->Add(b_quit, 0, wxALIGN_CENTER_HORIZONTAL | wxUP | wxBOTTOM, 5);

	hbox->Add(vbox, 1, wxALIGN_CENTER | wxUP | wxBOTTOM, 10);

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