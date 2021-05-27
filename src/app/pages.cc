#include <iostream>
#include "pages.h"
#include "wx/button.h"
#include "wx/sizer.h"
#include "wx/spinctrl.h"
#include "wx/dcclient.h"
#include "image_panel.h"
#include "page_control_event.h"

MainMenu::MainMenu(wxWindow* p_parent)
	: wxPanel(p_parent), p_parent(p_parent) {

	right_panel 	= new wxPanel(this);
	title 			= new wxStaticText(right_panel, wxID_ANY, wxT("Main Menu"));
	image 			= new wxImagePanel(this, wxString("./static/main.jpg"), wxBITMAP_TYPE_JPEG);
	b_play_single 	= new wxButton(right_panel, mainID_play_single, wxT("Single Player"));
	b_play_multi	= new wxButton(right_panel, mainID_play_multi, wxT("Multi Player"));
	b_quit 			= new wxButton(right_panel, wxID_EXIT, wxT("Quit"));

	wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);

	hbox->Add(image, 1, wxEXPAND | wxALL, 20);

	vbox->Add(title, 	   		1, wxALIGN_CENTER_HORIZONTAL | wxUP | wxBOTTOM, 10);
	vbox->Add(b_play_single,  	1, wxALIGN_CENTER_HORIZONTAL | wxUP | wxBOTTOM, 5);
	vbox->Add(b_play_multi, 	1, wxALIGN_CENTER_HORIZONTAL | wxUP | wxBOTTOM, 5);
	vbox->Add(b_quit, 	   		1, wxALIGN_CENTER_HORIZONTAL | wxUP | wxBOTTOM, 5);
	right_panel->SetSizer(vbox);

	hbox->Add(right_panel, 1, wxALIGN_CENTER | wxUP | wxBOTTOM, 10);

	SetSizer(hbox);

	Connect(mainID_play_single, 	wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(OnPlaySingle));
	Connect(mainID_play_multi,		wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(OnPlayMulti));
	Connect(wxID_EXIT, 		  		wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(OnQuit));
}

void MainMenu::OnQuit(wxCommandEvent& event) {
	event.Skip();
}

void MainMenu::OnPlaySingle(wxCommandEvent& event) {
	std::cerr << "Select Single" << std::endl;
	event.Skip();
}

void MainMenu::OnPlayMulti(wxCommandEvent& event) {
	std::cerr << "Select Multi" << std::endl;
	event.Skip();
}

SingleGameMenu::SingleGameMenu (wxWindow* p_parent)
	: wxPanel (p_parent), p_parent(p_parent) {

	wxPanel *panel = new wxPanel(this);

	title = new wxStaticText(panel, wxID_ANY, wxT("Single Player Mode"));
	game_select_label = new wxStaticText(panel, wxID_ANY, wxT("Choose game: "));
	game_select = new wxChoice(panel, singleID_game_select);
	user_name_label = new wxStaticText(panel, wxID_ANY, wxT("User Name: "));
	user_name_input = new wxTextCtrl(panel, singleID_player_number, wxT("Player NO.1"));
	user_number_label = new wxStaticText(panel, wxID_ANY, wxT("Player Number: "));
	user_number_input = new wxSpinCtrl(panel, singleID_player_number, wxT("4"));
	confirm = new wxButton(panel, singleID_confirm, wxT("confirm"));
	go_back = new wxButton(panel, singleID_back, wxT("return"));

	game_select->Insert(wxT("Poke0"), 0);
	game_select->Insert(wxT("Poke1"), 1);
	game_select->SetSelection(0);

	wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *panel_box = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *hbox0 = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer *hbox1 = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer *hbox2 = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer *hbox3 = new wxBoxSizer(wxHORIZONTAL);

	hbox0->Add(game_select_label, 1, wxALIGN_LEFT);
	hbox0->Add(game_select, 1, wxALIGN_LEFT);
	hbox1->Add(user_name_label, 1, wxALIGN_LEFT);
	hbox1->Add(user_name_input, 1, wxALIGN_LEFT);
	hbox2->Add(user_number_label, 1, wxALIGN_LEFT);
	hbox2->Add(user_number_input, 1, wxALIGN_LEFT);
	hbox3->Add(confirm, 1, wxCENTER);
	hbox3->Add(go_back, 1, wxCENTER);

	panel_box->Add(title, 0, wxALIGN_CENTER_HORIZONTAL | wxUP | wxBOTTOM, 20);
	panel_box->Add(hbox0, 0, wxALIGN_CENTER_HORIZONTAL | wxUP | wxBOTTOM, 20);
	panel_box->Add(hbox1, 0, wxALIGN_CENTER_HORIZONTAL | wxUP | wxBOTTOM, 20);
	panel_box->Add(hbox2, 0, wxALIGN_CENTER_HORIZONTAL | wxUP | wxBOTTOM, 20);
	panel_box->Add(hbox3, 0, wxALIGN_CENTER_HORIZONTAL | wxUP | wxBOTTOM, 20);

	panel->SetSizer(panel_box);
	vbox->Add(new wxPanel(this), 1, wxALL | wxEXPAND, 20);
	vbox->Add(panel, 1, wxALL | wxEXPAND, 20);
	vbox->Add(new wxPanel(this), 1, wxALL | wxEXPAND, 20);
	SetSizer(vbox);

	Connect(singleID_confirm, 	wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(OnConfirm));
	Connect(singleID_back,		wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(OnReturn));
}

void SingleGameMenu::OnConfirm(wxCommandEvent &event) {
	std::cerr << "Click confirm" << std::endl;
	event.Skip();
}

void SingleGameMenu::OnReturn(wxCommandEvent &event) {
	std::cerr << "Click Return" << std::endl;
	event.Skip();
}

MultiGameMenu::MultiGameMenu (wxWindow *p_parent)
	: wxPanel(p_parent), p_parent(p_parent) {
	wxPanel *panel = new wxPanel(this);
	
	title = new wxStaticText(panel, wxID_ANY, wxT("Multi Player Game"));
	join_game = new wxButton(panel, multiID_join_game, wxT("Join game"));
	create_game = new wxButton(panel, multiID_create_game, wxT("Create game"));
	go_back = new wxButton(panel, multiID_back, wxT("Return"));

	wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *panel_box = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer *panel_vbox = new wxBoxSizer(wxVERTICAL);

	panel_vbox->Add(title, 1, wxCENTER);
	panel_vbox->Add(join_game, 1, wxCENTER);
	panel_vbox->Add(create_game, 1, wxCENTER);
	panel_vbox->Add(go_back, 1, wxCENTER);

	panel_box->Add(new wxPanel(this), 1, wxALL | wxEXPAND, 20);
	panel_box->Add(panel_vbox, 1, wxALL | wxEXPAND, 20);
	panel_box->Add(new wxPanel(this), 1, wxALL | wxEXPAND, 20);

	panel->SetSizer(panel_box);

	vbox->Add(new wxPanel(this), 1, wxALL | wxEXPAND, 20);
	vbox->Add(panel, 1, wxALL | wxEXPAND, 20);
	vbox->Add(new wxPanel(this), 1, wxALL | wxEXPAND, 20);
	SetSizer(vbox);

	Connect(multiID_join_game,		wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(OnJoin));
	Connect(multiID_create_game,	wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(OnCreate));
	Connect(multiID_back,			wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(OnReturn));
}

void MultiGameMenu::OnJoin(wxCommandEvent &event) {
	std::cerr << "Click Join" << std::endl;
	event.Skip();
}

void MultiGameMenu::OnCreate(wxCommandEvent &event) {
	std::cerr << "Click Create" << std::endl;
	event.Skip();
}

void MultiGameMenu::OnReturn(wxCommandEvent &event) {
	std::cerr << "Click Return" << std::endl;
	event.Skip();
}

GameInterface::GameInterface(wxWindow *p_parent)
	: wxPanel(p_parent), p_parent(p_parent), dc(this) {
}

void GameInterface::render() {
	deck[0].cards.push_back(1);
	deck[0].cards.push_back(2);
	deck[0].cards.push_back(3);
	deck[0].Draw(dc, 0, 0);
}