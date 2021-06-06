#include <iostream>
#include "pages.h"
#include "wx/button.h"
#include "wx/sizer.h"
#include "wx/spinctrl.h"
#include "wx/dcclient.h"
#include "image_panel.h"
#include "center_block_sizer.h"
#include "page_control_event.h"
#include "deck.h"

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

MultiGameJoinSetting::MultiGameJoinSetting (wxWindow *p_parent)
	: wxPanel(p_parent), p_parent(p_parent) {
	
	title = new wxStaticText(this, wxID_ANY, wxT("Join Game"));
	user_name_label = new wxStaticText(this, wxID_ANY, wxT("User Name: "));
	user_name_input = new wxTextCtrl(this, joinID_username, wxT("Player NO.1"));
	IP_label = new wxStaticText(this, wxID_ANY, wxT("IP: "));
	IP_input = new wxTextCtrl(this, joinID_IP);
	passwd_label = new wxStaticText(this, wxID_ANY, wxT("Password: "));
	passwd_input = new wxTextCtrl(this, joinID_passwd);
	confirm = new wxButton(this, joinID_confirm, wxT("Confirm"));
	go_back = new wxButton(this, joinID_back, wxT("Return"));

	wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer *inner_vbox = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *inner_hbox0 = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer *inner_hbox1 = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer *inner_hbox2 = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer *inner_hbox3 = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer *inner_hbox4 = new wxBoxSizer(wxHORIZONTAL);

	inner_hbox0->Add(title, 1, wxALIGN_CENTER);
	inner_hbox1->Add(user_name_label, 1, wxALIGN_CENTER);
	inner_hbox1->Add(user_name_input, 1, wxALIGN_CENTER);
	inner_hbox2->Add(IP_label, 1, wxALIGN_CENTER);
	inner_hbox2->Add(IP_input, 1, wxALIGN_CENTER);
	inner_hbox3->Add(passwd_label, 1, wxALIGN_CENTER);
	inner_hbox3->Add(passwd_input, 1, wxALIGN_CENTER);
	inner_hbox4->Add(confirm, 1, wxALIGN_CENTER);
	inner_hbox4->Add(go_back, 1, wxALIGN_CENTER);

	inner_vbox->Add(inner_hbox0, wxALIGN_CENTER);
	inner_vbox->Add(inner_hbox1, wxALIGN_CENTER);
	inner_vbox->Add(inner_hbox2, wxALIGN_CENTER);
	inner_vbox->Add(inner_hbox3, wxALIGN_CENTER);
	inner_vbox->Add(inner_hbox4, wxALIGN_CENTER);

	hbox->Add(new wxPanel(this), 1, wxALL | wxEXPAND, 20);
	hbox->Add(inner_vbox, 1, wxALL | wxEXPAND, 20);
	hbox->Add(new wxPanel(this), 1, wxALL | wxEXPAND, 20);

	vbox->Add(new wxPanel(this), 1, wxALL | wxEXPAND, 20);
	vbox->Add(hbox, 1, wxALL | wxEXPAND, 20);
	vbox->Add(new wxPanel(this), 1, wxALL | wxEXPAND, 20);

	SetSizer(vbox);

	Connect(joinID_confirm, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(OnConfirm));
	Connect(joinID_back, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(OnReturn));
}

void MultiGameJoinSetting::OnConfirm(wxCommandEvent &event) {
	std::cerr << "Click Confirm" << std::endl;
	event.Skip();
}

void MultiGameJoinSetting::OnReturn(wxCommandEvent &event) {
	std::cerr << "Click Return" << std::endl;
	event.Skip();
}

MultiGameCreateSetting::MultiGameCreateSetting(wxWindow *p_parent)
	: wxPanel(p_parent), p_parent(p_parent) {
	title = new wxStaticText(this, wxID_ANY, wxT("Create Game"));
	game_select_label = new wxStaticText(this, wxID_ANY, wxT("Choose game: "));
	game_select = new wxChoice(this, createID_game_select);
	user_name_label = new wxStaticText(this, wxID_ANY, wxT("User Name: "));
	user_name_input = new wxTextCtrl(this, createID_username, wxT("Player NO.1"));
	user_number_label = new wxStaticText(this, wxID_ANY, wxT("Player Number: "));
	user_number_input = new wxSpinCtrl(this, createID_player_number, wxT("4"));
	passwd_label = new wxStaticText(this, wxID_ANY, wxT("Password: "));
	passwd_input = new wxTextCtrl(this, createID_passwd);
	confirm = new wxButton(this, createID_confirm, wxT("Confirm"));
	go_back = new wxButton(this, createID_back, wxT("Return"));

	game_select->Insert(wxT("Poke0"), 0);
	game_select->Insert(wxT("Poke1"), 1);
	game_select->SetSelection(0);

	CenterBlockSizer *sizer = new CenterBlockSizer(this);
	sizer->AddWidget(title, true, wxALIGN_CENTRE);
	sizer->AddWidget(game_select_label, true);
	sizer->AddWidget(game_select);
	sizer->AddWidget(user_name_label, true);
	sizer->AddWidget(user_name_input);
	sizer->AddWidget(user_number_label, true);
	sizer->AddWidget(user_number_input);
	sizer->AddWidget(passwd_label, true);
	sizer->AddWidget(passwd_input);
	sizer->AddWidget(confirm, true);
	sizer->AddWidget(go_back);
	sizer->Create();

	SetSizer(sizer);

	Connect(createID_confirm, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(OnConfirm));
	Connect(createID_back, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(OnReturn));
}

void MultiGameCreateSetting::OnConfirm(wxCommandEvent &event) {
	std::cerr << "Click Confirm" << std::endl;
	event.Skip();
}

void MultiGameCreateSetting::OnReturn(wxCommandEvent &event) {
	std::cerr << "Click Return" << std::endl;
	event.Skip();
}

wxBEGIN_EVENT_TABLE(GameInterface, wxPanel)
	EVT_BUTTON(gameID_deal, GameInterface::OnDeal)
	EVT_BUTTON(gameID_pass, GameInterface::OnPass)
	EVT_TIMER(gameID_count_down, GameInterface::OnTimer)
wxEND_EVENT_TABLE()

GameInterface::GameInterface(wxWindow *p_parent)
	: wxPanel(p_parent), p_parent(p_parent), dc(this) {

	deck[0] = new DeckPanel(this, kFaceUp, kDown);
	deck[1] = new DeckPanel(this, kFaceDown, kLeft);
	deck[2] = new DeckPanel(this, kFaceDown, kUp);
	deck[3] = new DeckPanel(this, kFaceDown, kRight);
	deck[0]->SetDeck({1, 2, 3});
	deck[1]->SetDeck({4, 5, 6, 7, 8});
	deck[2]->SetDeck({1, 2, 3, 4, 5, 6, 7, 8, 9});
	deck[3]->SetDeck({0, 1, 2, 3});

	midpan = new wxPanel(this);
	deal = new wxButton(midpan, gameID_deal, "deal");
	pass = new wxButton(midpan, gameID_pass, "pass");
	timer = new wxTimer(this, gameID_count_down);
	timer_label = new wxStaticText(midpan, wxID_ANY, "Time left:");
	last_round = new DeckPanel(midpan, kFaceUp, kCenter);
	
	timer->Start(1000);
	last_round->SetDeck({10, 20, 30, 53});

	wxBoxSizer *mid_vbox = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *mid_hbox = new wxBoxSizer(wxHORIZONTAL);
	mid_hbox->Add(deal, 0, wxRIGHT, 10);
	mid_hbox->Add(pass, 0, wxRIGHT, 10);
	mid_vbox->Add(timer_label, 0, wxEXPAND);
	mid_vbox->Add(last_round, 1, wxEXPAND);
	mid_vbox->Add(mid_hbox, 0, wxALIGN_RIGHT);
	midpan->SetSizer(mid_vbox);

	wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);
	hbox->Add(deck[1], 2, wxEXPAND);
	hbox->Add(midpan, 7, wxEXPAND);
	hbox->Add(deck[3], 2, wxEXPAND);

	wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
	vbox->Add(deck[2], 2, wxEXPAND);
	vbox->Add(hbox, 7, wxEXPAND);
	vbox->Add(deck[0], 2, wxEXPAND);

	SetSizer(vbox);
}

void GameInterface::render() {
	count_down = 60;
	std::cerr << "render!" << std::endl;
}

void GameInterface::OnDeal(wxCommandEvent &event) {
	std::cerr << "Dealt!" << std::endl;
}

void GameInterface::OnPass(wxCommandEvent &event) {
	std::cerr << "Pass!" << std::endl;
}

void GameInterface::OnTimer(wxTimerEvent &event) {
	if (count_down < 0) {
		count_down = 60;
	}
	std::cout << count_down-- << std::endl;
	static char time_string[10];
	itoa(count_down, time_string, 10);
	timer_label->SetLabel(wxString("Time left in this round: ") + wxString(time_string) + wxString("s"));
}