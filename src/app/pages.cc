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
#include "page_control.h"

#define get_controller(controller) auto (controller) = static_cast<PageController*>(this->p_parent);

wxBEGIN_EVENT_TABLE(MainMenu, wxPanel)
	EVT_BUTTON(mainID_play_single, MainMenu::OnPlaySingle)
	EVT_BUTTON(mainID_play_multi, MainMenu::OnPlayMulti)
	EVT_BUTTON(wxID_EXIT, MainMenu::OnQuit)
wxEND_EVENT_TABLE()

MainMenu::MainMenu(wxWindow* p_parent)
	: wxPanel(p_parent), p_parent(p_parent) {

	right_panel 	= new wxPanel(this);
	title 			= new MyLabel(right_panel, wxID_ANY, wxT("主菜单"));
	image 			= new wxImagePanel(this, wxString("./static/main.jpg"), wxBITMAP_TYPE_JPEG);
	b_play_single 	= new MyButton(right_panel, mainID_play_single, wxT("Single Player"));
	b_play_multi	= new MyButton(right_panel, mainID_play_multi, wxT("Multi Player"));
	b_quit 			= new MyButton(right_panel, wxID_EXIT, wxT("Quit"));

	title->SetFont(h1_font);
	b_play_single->SetFont(button_font);

	wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);

	hbox->Add(image, 1, wxEXPAND | wxALL, 20);

	vbox->Add(title, 	   		1, wxALIGN_CENTER_HORIZONTAL | wxUP | wxBOTTOM, 10);
	vbox->Add(b_play_single,  	0, wxALL | wxCENTER, 10);
	vbox->Add(b_play_multi, 	0, wxALL | wxCENTER, 10);
	vbox->Add(b_quit, 	   		0, wxALL | wxCENTER, 10);
	right_panel->SetSizer(vbox);

	hbox->Add(right_panel, 1, wxALIGN_CENTER | wxUP | wxBOTTOM, 10);

	SetSizer(hbox);
}

void MainMenu::OnQuit(wxCommandEvent& event) {
	event.Skip();
}

void MainMenu::OnPlaySingle(wxCommandEvent& event) {
	auto control = static_cast<PageController*>(this->p_parent);
	control->app_status.single_multi = kSingle;
	std::cerr << "Select Single" << std::endl;
	event.Skip();
}

void MainMenu::OnPlayMulti(wxCommandEvent& event) {
	auto control = static_cast<PageController*>(this->p_parent);
	control->app_status.single_multi = kMulti;
	std::cerr << "Select Multi" << std::endl;
	event.Skip();
}

wxBEGIN_EVENT_TABLE(SingleGameMenu, wxPanel)
	EVT_BUTTON(singleID_confirm, SingleGameMenu::OnConfirm)
	EVT_BUTTON(singleID_back, SingleGameMenu::OnReturn)
wxEND_EVENT_TABLE()

SingleGameMenu::SingleGameMenu (wxWindow* p_parent)
	: wxPanel (p_parent), p_parent(p_parent) {

	title = new MyLabel(this, wxID_ANY, wxT("Single Player Mode"));
	game_select_label = new MyLabel(this, wxID_ANY, wxT("Choose game: "));
	game_select = new wxChoice(this, singleID_game_select);
	user_name_label = new MyLabel(this, wxID_ANY, wxT("User Name: "));
	user_name_input = new wxTextCtrl(this, singleID_player_number, wxT("Player NO.1"));
	user_number_label = new MyLabel(this, wxID_ANY, wxT("Player Number: "));
	user_number_input = new wxSpinCtrl(this, singleID_player_number, wxT("4"));
	confirm = new MyButton(this, singleID_confirm, wxT("confirm"));
	go_back = new MyButton(this, singleID_back, wxT("return"));

	game_select->Insert(wxT("争上游"), 0);
	game_select->Insert(wxT("斗地主"), 1);
	game_select->SetSelection(0);

	CenterBlockSizer *sizer = new CenterBlockSizer(this);

	sizer->AddWidget(title, true);
	sizer->AddWidget(game_select_label, true);
	sizer->AddWidget(game_select, false);
	sizer->AddWidget(user_name_label, true);
	sizer->AddWidget(user_name_input, false);
	sizer->AddWidget(user_number_label, true);
	sizer->AddWidget(user_number_input, false);
	sizer->AddWidget(confirm, true);
	sizer->AddWidget(go_back, false);

	sizer->Create();
	SetSizer(sizer);
}

void SingleGameMenu::OnConfirm(wxCommandEvent &event) {
	get_controller(control)
	std::cerr << "User name: " << user_name_input->GetLineText(0) << std::endl;
	control->app_status.user_name = user_name_input->GetLineText(0);
	std::cerr << "User number: " << user_number_input->GetValue() << std::endl;
	control->app_status.player_number = user_number_input->GetValue();
	std::cerr << "Game Select: " << game_select->GetSelection() << std::endl;
	control->app_status.game_type = game_select->GetSelection() == 0 ? kPoke : kLandlord;
	std::cerr << "Click confirm" << std::endl;
	event.Skip();
}

void SingleGameMenu::OnReturn(wxCommandEvent &event) {
	std::cerr << "Click Return" << std::endl;
	event.Skip();
}

wxBEGIN_EVENT_TABLE(MultiGameMenu, wxPanel)
	EVT_BUTTON(multiID_join_game, MultiGameMenu::OnJoin)
	EVT_BUTTON(multiID_create_game, MultiGameMenu::OnCreate)
	EVT_BUTTON(multiID_back, MultiGameMenu::OnReturn)
wxEND_EVENT_TABLE()

MultiGameMenu::MultiGameMenu (wxWindow *p_parent)
	: wxPanel(p_parent), p_parent(p_parent) {
	
	title = new MyLabel(this, wxID_ANY, wxT("Multi Player Game"));
	join_game = new MyButton(this, multiID_join_game, wxT("Join game"));
	create_game = new MyButton(this, multiID_create_game, wxT("Create game"));
	go_back = new MyButton(this, multiID_back, wxT("Return"));

	CenterBlockSizer *sizer = new CenterBlockSizer(this);

	sizer->AddWidget(title, true);
	sizer->AddWidget(join_game, true);
	sizer->AddWidget(create_game, true);
	sizer->AddWidget(go_back, true);
	sizer->Create();

	SetSizer(sizer);
}

void MultiGameMenu::OnJoin(wxCommandEvent &event) {
	get_controller(control);
	control->app_status.join_create = kJoin;
	std::cerr << "Click Join" << std::endl;
	event.Skip();
}

void MultiGameMenu::OnCreate(wxCommandEvent &event) {
	get_controller(control);
	control->app_status.join_create = kCreate;
	std::cerr << "Click Create" << std::endl;
	event.Skip();
}

void MultiGameMenu::OnReturn(wxCommandEvent &event) {
	std::cerr << "Click Return" << std::endl;
	event.Skip();
}

wxBEGIN_EVENT_TABLE(MultiGameJoinSetting, wxPanel)
	EVT_BUTTON(joinID_confirm, MultiGameJoinSetting::OnConfirm)
	EVT_BUTTON(joinID_back, MultiGameJoinSetting::OnReturn)
wxEND_EVENT_TABLE()

MultiGameJoinSetting::MultiGameJoinSetting (wxWindow *p_parent)
	: wxPanel(p_parent), p_parent(p_parent) {
	
	title = new MyLabel(this, wxID_ANY, wxT("Join Game"));
	user_name_label = new MyLabel(this, wxID_ANY, wxT("User Name: "));
	user_name_input = new wxTextCtrl(this, joinID_username, wxT("Player NO.1"));
	IP_label = new MyLabel(this, wxID_ANY, wxT("IP: "));
	IP_input = new wxTextCtrl(this, joinID_IP);
	passwd_label = new MyLabel(this, wxID_ANY, wxT("Password: "));
	passwd_input = new wxTextCtrl(this, joinID_passwd);
	confirm = new MyButton(this, joinID_confirm, wxT("Confirm"));
	go_back = new MyButton(this, joinID_back, wxT("Return"));

	CenterBlockSizer *sizer = new CenterBlockSizer(this);

	sizer->AddWidget(title, true);
	sizer->AddWidget(user_name_label, true);
	sizer->AddWidget(user_name_input, false);
	sizer->AddWidget(IP_label, true);
	sizer->AddWidget(IP_input, false);
	sizer->AddWidget(passwd_label, true);
	sizer->AddWidget(passwd_input, false);
	sizer->AddWidget(confirm, true);
	sizer->AddWidget(go_back, false);
	sizer->Create();

	SetSizer(sizer);
}

void MultiGameJoinSetting::OnConfirm(wxCommandEvent &event) {
	get_controller(control);
	std::cerr << "User name: " << user_name_input->GetLineText(0) << std::endl;
	control->app_status.user_name = user_name_input->GetLineText(0);
	std::cerr << "IP address: " << IP_input->GetLineText(0) << std::endl;
	control->app_status.IP_address = IP_input->GetLineText(0);
	std::cerr << "Password: " << passwd_input->GetLineText(0) << std::endl;
	control->app_status.passwd = passwd_input->GetLineText(0);
	std::cerr << "Click Confirm" << std::endl;
	event.Skip();
}

void MultiGameJoinSetting::OnReturn(wxCommandEvent &event) {
	std::cerr << "Click Return" << std::endl;
	event.Skip();
}

wxBEGIN_EVENT_TABLE(MultiGameCreateSetting, wxPanel)
	EVT_BUTTON(createID_confirm, MultiGameCreateSetting::OnConfirm)
	EVT_BUTTON(createID_back, MultiGameCreateSetting::OnReturn)
wxEND_EVENT_TABLE()

MultiGameCreateSetting::MultiGameCreateSetting(wxWindow *p_parent)
	: wxPanel(p_parent), p_parent(p_parent) {
	title = new MyLabel(this, wxID_ANY, wxT("Create Game"));
	game_select_label = new MyLabel(this, wxID_ANY, wxT("Choose game: "));
	game_select = new wxChoice(this, createID_game_select);
	user_name_label = new MyLabel(this, wxID_ANY, wxT("User Name: "));
	user_name_input = new wxTextCtrl(this, createID_username, wxT("Player NO.1"));
	user_number_label = new MyLabel(this, wxID_ANY, wxT("Player Number: "));
	user_number_input = new wxSpinCtrl(this, createID_player_number, wxT("4"));
	passwd_label = new MyLabel(this, wxID_ANY, wxT("Password: "));
	passwd_input = new wxTextCtrl(this, createID_passwd);
	confirm = new MyButton(this, createID_confirm, wxT("Confirm"));
	go_back = new MyButton(this, createID_back, wxT("Return"));

	game_select->Insert(wxT("争上游"), 0);
	game_select->Insert(wxT("斗地主"), 1);
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
}

void MultiGameCreateSetting::OnConfirm(wxCommandEvent &event) {
	get_controller(control);
	std::cerr << "Game Select: " << game_select->GetSelection() << std::endl;
	control->app_status.game_type = game_select->GetSelection() == 0 ? kPoke : kLandlord;
	std::cerr << "User name: " << user_name_input->GetLineText(0) << std::endl;
	control->app_status.user_name = user_name_input->GetLineText(0);
	std::cerr << "User number: " << user_number_input->GetValue() << std::endl;
	control->app_status.player_number = user_number_input->GetValue();
	std::cerr << "Password: " << passwd_input->GetLineText(0) << std::endl;
	control->app_status.passwd = passwd_input->GetLineText(0);
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
	deck[0]->SetDeck(CardSet(10));
	deck[1]->SetDeck(CardSet(10));
	deck[2]->SetDeck(CardSet(10));
	deck[3]->SetDeck(CardSet(10));

	midpan = new wxPanel(this);
	deal = new MyButton(midpan, gameID_deal, "deal");
	pass = new MyButton(midpan, gameID_pass, "pass");
	timer = new wxTimer(this, gameID_count_down);
	timer_label = new MyLabel(midpan, wxID_ANY, "Time left:");
	last_round = new DeckPanel(midpan, kFaceUp, kCenter);
	
	last_round->SetDeck(CardSet(10));

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

void GameInterface::Render() {
	std::cerr << "render!" << std::endl;
	count_down = 60;
	timer->Start(1000);
	for (int i = 0; i < 4; i++) {
		deck[i]->Render();
	}
	last_round->Render();
}

void GameInterface::OnDeal(wxCommandEvent &event) {
	std::cerr << "Dealt!" << std::endl;
}

void GameInterface::OnPass(wxCommandEvent &event) {
	std::cerr << "Pass!" << std::endl;
}

void GameInterface::OnTimer(wxTimerEvent &event) {
	if (count_down < 0) {
		timer->Stop();
	}
	count_down--;
	std::cout << count_down << std::endl;
	static char time_string[10];
	itoa(count_down, time_string, 10);
	timer_label->SetLabel(wxString("Time left in this round: ") + wxString(time_string) + wxString("s"));
}