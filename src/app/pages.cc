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
	control->app_status.game_type = game_select->GetSelection() == 0 ? kLandlord3 : kLandlord4;
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

	game_select->Insert(wxT("三人斗地主"), 0);
	game_select->Insert(wxT("四人斗地主"), 1);
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
	control->app_status.game_type = game_select->GetSelection() == 0 ? kLandlord3 : kLandlord4;
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

wxBEGIN_EVENT_TABLE(GamePending, wxPanel)
	EVT_TIMER(pendingID_timer, GamePending::OnTimer)
wxEND_EVENT_TABLE()

GamePending::GamePending(wxWindow *p_parent) : wxPanel(p_parent), p_parent(p_parent) {
	wait_label = new MyLabel(this, wxID_ANY, wxT("正在等待玩家加入，等待时长："));
	timer = new wxTimer(this, pendingID_timer);
	CenterBlockSizer *sizer = new CenterBlockSizer(this);
	sizer->AddWidget(wait_label, true);
	sizer->Create();
	SetSizer(sizer);
}

void GamePending::OnTimer(wxTimerEvent &event) {
	static char time_string[10];
	itoa(count, time_string, 10);
	switch (status) {
		case kWaiting:
			wait_label->SetLabelText(wxT("正在等待玩家加入，等待时长：") + wxString(time_string) + "s");
			break;
		case kJoining:
			wait_label->SetLabelText(wxT("正在加入房间，等待时长：") + wxString(time_string) + "s");
			break;
	}
	count++;
}

void GamePending::StartPending(Status set_status) {
	status = set_status;
	count = 0;
	timer->Start(1000);
}

void GamePending::StopPending() {
	timer->Stop();
}

wxBEGIN_EVENT_TABLE(GameOver, wxPanel)
	EVT_BUTTON(overID_back, GameOver::OnReturn)
wxEND_EVENT_TABLE()

GameOver::GameOver(wxWindow *p_parent) : wxPanel(p_parent), p_parent(p_parent) {
	go_back = new MyButton(this, overID_back, wxT("返回主菜单"));
	title = new MyLabel(this, wxID_ANY, wxT("游戏结束！"));
	winner_label = new MyLabel(this, wxID_ANY, wxT("获胜的玩家是："));

	CenterBlockSizer *sizer = new CenterBlockSizer(this);
	sizer->AddWidget(title, true);
	sizer->AddWidget(winner_label, true);
	sizer->AddWidget(go_back, true);
	sizer->Create();

	SetSizer(sizer);
}

void GameOver::OnReturn(wxCommandEvent &event) {
	std::cerr << "Click Return" << std::endl;
	event.Skip();
}

void GameOver::SetWinner() {
	get_controller(control);
	winner_label->SetLabelText(wxT("获胜的玩家是：") + control->app_status.winner);
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

	user_info[0] = new MyLabel(this, wxID_ANY, wxT("玩家0"));
	user_info[1] = new MyLabel(this, wxID_ANY, wxT("玩家1"));
	user_info[2] = new MyLabel(this, wxID_ANY, wxT("玩家2"));
	user_info[3] = new MyLabel(this, wxID_ANY, wxT("玩家3"));

	midpan = new wxPanel(this);
	deal = new MyButton(this, gameID_deal, wxT("出牌"));
	pass = new MyButton(this, gameID_pass, wxT("跳过"));
	call_auction[0] = new MyButton(this, gameID_auction0, wxT("不叫"));
	call_auction[1] = new MyButton(this, gameID_auction1, wxT("叫1分"));
	call_auction[2] = new MyButton(this, gameID_auction2, wxT("叫2分"));
	call_auction[3] = new MyButton(this, gameID_auction3, wxT("叫3分"));
	timer_label = new MyLabel(midpan, wxID_ANY, wxT("回合剩余时间："));
	center_info = new MyLabel(midpan, wxID_ANY, wxT("测试信息："));
	timer = new wxTimer(this, gameID_count_down);

	last_round[0] = new DeckPanel(midpan, kFaceUp, kCenter);
	last_round[1] = new DeckPanel(midpan, kFaceUp, kCenter);
	last_round[2] = new DeckPanel(midpan, kFaceUp, kCenter);
	last_round[3] = new DeckPanel(midpan, kFaceUp, kCenter);
	
	wxBoxSizer *mid_vbox = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *mid_hbox = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer *mid_hbox_inner = new wxBoxSizer(wxHORIZONTAL);

	mid_hbox->Add(last_round[3], 1, wxEXPAND);
	mid_hbox->Add(mid_vbox, 2, wxEXPAND);
	mid_hbox->Add(last_round[1], 1, wxEXPAND);

	mid_vbox->Add(last_round[2], 1, wxEXPAND);
	mid_vbox->Add(timer_label, 1, wxALIGN_CENTER);
	mid_vbox->Add(center_info, 1, wxALIGN_CENTER);
	mid_vbox->Add(last_round[0], 1, wxEXPAND);

	midpan->SetSizer(mid_hbox);

	wxBoxSizer *up_box = new wxBoxSizer(wxHORIZONTAL);
	up_box->Add(user_info[2], 2, wxALIGN_TOP);
	up_box->Add(deck[2], 8, wxALIGN_CENTER);

	wxBoxSizer *left_box = new wxBoxSizer(wxVERTICAL);
	left_box->Add(user_info[3], 2, wxALIGN_LEFT);
	left_box->Add(deck[3], 8, wxALIGN_CENTER);

	wxBoxSizer *right_box = new wxBoxSizer(wxVERTICAL);
	right_box->Add(user_info[1], 2, wxALIGN_RIGHT);
	right_box->Add(deck[1], 8, wxALIGN_CENTER);

	wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);
	hbox->Add(left_box, 2, wxEXPAND);
	hbox->Add(midpan, 6, wxEXPAND);
	hbox->Add(right_box, 2, wxEXPAND);

	wxBoxSizer *down_box = new wxBoxSizer(wxHORIZONTAL);
	down_box->Add(user_info[0], 2, wxALIGN_TOP);
	down_box->Add(deck[0], 7, wxEXPAND);


	wxBoxSizer *button_box = new wxBoxSizer(wxVERTICAL);
	button_box->Add(deal, 1, wxALL, 5);
	button_box->Add(pass, 1, wxALL, 5);
	down_box->Add(button_box, 1, wxEXPAND);

	wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
	vbox->Add(up_box, 2, wxEXPAND);
	vbox->Add(hbox, 7, wxEXPAND);
	vbox->Add(down_box, 2, wxEXPAND);

	for (int i = 0; i < 4; i++) {
		button_box->Add(call_auction[i], 1, wxALL, 5);
	}
	deal->Hide();
	pass->Hide();
	for (int i = 0; i < 4; i++) {
		call_auction[i]->Hide();
	}

	SetSizer(vbox);
}

CardSet getCardSet(int n) {
	CardSet result(0);
	for (int i = 1; i <= n; i++) {
		result.Insert(1, 1);
	}
	return result;
}


#include "Client.h"
#include "message.h"
#include <process.h>
#include <Windows.h>

unsigned WINAPI GameThread(GameInterface& game_interface, Client& client);

void GameInterface::StartGame() {

	center_info->SetLabelText(wxT("正在初始化……"));
	center_info->Show();

	timer->Start(1000);

	// HANDLE hThread;
	// unsigned threadID;
	// int param = 5;

	// hThread = (HANDLE)_beginthreadex(NULL, 0, GameThread, (void*)&param, 0, &threadID);


	Render();
}

unsigned WINAPI GameThread(GameInterface& game_interface, Client& client) {
	while (true) {
		bool end_loop = false;
		auto package = client.CollectGameMsg();
		if (package.GetHeader().IsSuccess() == false) {	// 断开连接
			wxMessageBox(wxT("断开连接！"));
			break;
		}
		auto message = Message(package.GetData());
		switch (message.GetType()) {
			case m_end:
				end_loop = true;
				break;
			case m_playout:
				if (message.IsRequest()) {
					// 需要出牌
					game_interface.is_counting_down = true;
					game_interface.is_my_turn = true;
					game_interface.count_down = message.GetTime();
				} else {
					game_interface.num_cards[message.GetPlayer()] = message.GetPar();
					game_interface.last_round_card[message.GetPlayer()] = message.GetCards();
				}
				break;
			case m_deny:
				wxMessageBox(wxT("请好好出牌！"));
				break;
			case m_changestake:
				game_interface.stake = message.GetPar();
				break;
			case m_setlandlord:
				game_interface.num_cards[message.GetPlayer()] = message.GetPar();
				game_interface.last_round_card[message.GetPlayer()] = message.GetCards();
				break;
		}
		if (end_loop) {
			break;
		}
		game_interface.Render();
	}
}

// 根据当前的状态来渲染房间
void GameInterface::Render() {
	deck[0]->SetDeck(my_cards);
	last_round[0]->SetDeck(last_round_card[0]);
	user_info[0]->SetLabelText(user_name[0]);
	user_info[0]->Show();

	deck[1]->SetDeck(getCardSet(num_cards[1]));
	last_round[1]->SetDeck(last_round_card[1]);
	user_info[1]->SetLabelText(user_name[1]);
	user_info[1]->Show();

	if (num_players == 3) {
		deck[2]->SetDeck(CardSet(0));
		last_round[2]->SetDeck(CardSet(0));
		user_info[2]->Hide();

		deck[3]->SetDeck(getCardSet(num_cards[2]));
		last_round[3]->SetDeck(last_round_card[2]);
		user_info[3]->SetLabelText(user_name[2]);
		user_info[3]->Show();
	} else if (num_players == 4) {
		deck[2]->SetDeck(getCardSet(num_cards[2]));
		last_round[2]->SetDeck(last_round_card[2]);
		user_info[2]->SetLabelText(user_name[2]);
		user_info[2]->Show();

		deck[3]->SetDeck(getCardSet(num_cards[3]));
		last_round[3]->SetDeck(last_round_card[3]);
		user_info[3]->SetLabelText(user_name[3]);
		user_info[3]->Show();
	}

	this->Layout();

	static char number[20];
	itoa(stake, number, 10);
	center_info->SetLabelText(wxT("当前倍数：") + wxString(number));

	if(show_count_down) {
		timer_label->Show();
	} else {
		timer_label->Hide();
	}

	if (show_stake) {
		center_info->Show();
	} else {
		center_info->Hide();
	}

	if (is_my_turn) {
		deal->Show();
		pass->Show();
	} else {
		deal->Hide();
		pass->Hide();
	}
	
	for (int i = 0; i < 4; i++) {
		call_auction[i]->Hide();
	}

	if (is_auction) {
		for (int i = smallest_bid; i <= largest_bid; i++) {
			call_auction[i]->Show();
		}
	}

	this->Layout();

	for (int i = 0; i < 4; i++) {
		deck[i]->Render();
		last_round[i]->Render();
	}
}

void GameInterface::OnDeal(wxCommandEvent &event) {
	CardSet draw_card(0);
	int card_num = deck[0]->GetDrawnDeck();
	get_controller(control);
	Client &client = control->client;
	std::cerr << "Dealt!" << std::endl;
}

void GameInterface::OnPass(wxCommandEvent &event) {
	std::cerr << "Pass!" << std::endl;
}

void GameInterface::OnTimer(wxTimerEvent &event) {
	if (!is_counting_down) {
		return;
	}
	if (count_down < 0) {
		is_counting_down = false;
		// TODO 倒计时结束了
		return;
	}
	count_down--;
	static char time_string[10];
	itoa(count_down, time_string, 10);
	timer_label->SetLabel(wxT("回合剩余时间：") + wxString(time_string) + wxString("s"));
}