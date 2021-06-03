#include "page_control.h"
#include "page_control_event.h"

enum {
	kMainMenu = 0,
	kSingleGameMenu,
	kMultiGameMenu,
	kMultiGameJoinSetting,
	kMultiGameCreateSetting,
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
	Connect(wxID_EXIT, 		  		wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(OnQuit));
}

void PageController::OnQuit(wxCommandEvent& event) {
	event.Skip();
}

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
			// TODO
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
			// TODO
			break;
		default:
			event.Skip();
			break;
	}

}