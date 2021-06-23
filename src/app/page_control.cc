#include "page_control.h"
#include "page_control_event.h"
#include <Windows.h>
#include <process.h>

enum {
	kMainMenu = 0,
	kSingleGameMenu,
	kMultiGameMenu,
	kMultiGameJoinSetting,
	kMultiGameCreateSetting,
	kGamePending,
	kGameOver,
	kGameInterface,
};

PageController::PageController(wxWindow* p_parent)
	: wxSimplebook(p_parent) {
	main_menu = new MainMenu(this);
	AddPage(main_menu, wxT("Main Menu"), true);

	single_game_menu = new SingleGameMenu(this);
	AddPage(single_game_menu, wxT("Single Game Menu"));

	multi_game_menu = new MultiGameMenu(this);
	AddPage(multi_game_menu, wxT("Multi Game Menu"));

	multi_game_join_setting = new MultiGameJoinSetting(this);
	AddPage(multi_game_join_setting, wxT("Multi Game Join Menu"));

	multi_game_create_setting = new MultiGameCreateSetting(this);
	AddPage(multi_game_create_setting, wxT("Create Game"));

	game_pending = new GamePending(this);
	AddPage(game_pending, wxT("Pending"));

	game_over = new GameOver(this);
	AddPage(game_over, wxT("Over"));

	game_interface = new GameInterface(this);
	AddPage(game_interface, wxT("Game Interface"));

	Connect(mainID_play_single, 	wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(OnButton));
	Connect(mainID_play_multi, 		wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(OnButton));
	Connect(singleID_confirm, 		wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(OnButton));
	Connect(singleID_back,	  		wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(OnButton));
	Connect(multiID_join_game,		wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(OnButton));
	Connect(multiID_create_game,	wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(OnButton));
	Connect(multiID_back, 			wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(OnButton));
	Connect(joinID_confirm, 		wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(OnButton));
	Connect(joinID_back, 			wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(OnButton));
	Connect(createID_confirm, 		wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(OnButton));
	Connect(createID_back, 			wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(OnButton));
	Connect(overID_back, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(OnButton));
	Connect(wxID_EXIT, 		  		wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(OnQuit));
}

void PageController::OnQuit(wxCommandEvent& event) {
	event.Skip();
}

// 菜单系统
void PageController::OnButton(wxCommandEvent& event) {
	switch (event.GetId()) {
		case mainID_play_single:
			ChangeSelection(kSingleGameMenu);
			break;
		case mainID_play_multi:
			ChangeSelection(kMultiGameMenu);
			break;
		case singleID_confirm:
			ChangeSelection(kGameInterface);
			game_interface->StartGame();
			break;
		case singleID_back:
			ChangeSelection(kMainMenu);
			break;
		case multiID_join_game:
			ChangeSelection(kMultiGameJoinSetting);
			break;
		case multiID_create_game:
			ChangeSelection(kMultiGameCreateSetting);
			break;
		case createID_confirm:
			game_pending->StartPending();
			ChangeSelection(kGamePending);
			if (CreateGame()) {
				game_interface->StartGame();
				ChangeSelection(kGameInterface);
			} else {
				wxMessageBox(wxT("异常！无法创建房间"));
			}
			break;
		case createID_back:
			ChangeSelection(kMultiGameMenu);
			break;
		case multiID_back:
			ChangeSelection(kMainMenu);
			break;
		case joinID_back:
			ChangeSelection(kMultiGameMenu);
			break;
		case joinID_confirm:
			game_pending->StartPending();
			ChangeSelection(kGamePending);
			if (Pending()) {
				game_interface->StartGame();
				ChangeSelection(kGameInterface);
			} else {
				wxMessageBox(wxT("连接超时！"));
				ChangeSelection(kMainMenu);
			}
			break;
		case overID_back:
			ChangeSelection(kMainMenu);
			break;
		default:
			event.Skip();
			break;
	}

}

#include "Server.h"
#include "Client.h"
#include "message.h"

bool PageController::Pending() {
	int game_type;
	auto user_name = client.JoinRoom(app_status.IP_address, string(app_status.user_name), game_type);
	if (user_name.size() == 0) { // 连接超时，异常
		// TODO
		return false;
	}
	// 设置用户名
	for (int i = 0; i < 4; i++) {
		game_interface->user_name[i] = user_name[i];
	}
	return true;
}

bool PageController::CreateGame() {
	switch (app_status.game_type) {
		case kLandlord3:
			return server.OpenRoom(sanrendoudizhu, app_status.player_number, 3 - app_status.player_number) == 0;
			break;
		case kLandlord4:
			return server.OpenRoom(sirendoudizhu, app_status.player_number, 4 - app_status.player_number) == 0;
			break;
	}
}