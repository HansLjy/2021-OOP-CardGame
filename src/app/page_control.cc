#include "page_control.h"
#include "page_control_event.h"

enum {
	kMainMenu = 0,
	kSubMenuUNO,
	kSubMenuPoke,
	kSingleGameMenu
};

PageController::PageController(wxWindow* p_parent)
	: wxSimplebook(p_parent) {
	main_menu = new MainMenu(this);
	AddPage(main_menu, wxT("Main Menu"), true);

	sub_menu_uno = new SubMenu(this, kUNO);
	AddPage(sub_menu_uno, wxT("Sub Menu UNO"));

	sub_menu_poke = new SubMenu(this, kPoke);
	AddPage(sub_menu_poke, wxT("Sub Menu Poke"));

	single_game_menu = new SingleGameMenu(this);
	AddPage(single_game_menu, wxT("Single Game Menu"));

	Connect(mainID_play_UNO,  wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(OnButton));
	Connect(mainID_play_Poke, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(OnButton));
	Connect(subID_single, 	  wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(OnButton));
	Connect(subID_multi,	  wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(OnButton));
	Connect(subID_back,		  wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(OnButton));
	Connect(wxID_EXIT, 		  wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(OnQuit));
}

void PageController::OnQuit(wxCommandEvent& event) {
	event.Skip();
}

void PageController::OnButton(wxCommandEvent& event) {
	switch (event.GetId()) {
		case mainID_play_Poke:
			ChangeSelection(kSubMenuPoke);
			break;
		case mainID_play_UNO:
			ChangeSelection(kSubMenuUNO);
			break;
		case subID_back:
			ChangeSelection(kMainMenu);
			break;
		case subID_single:
			ChangeSelection(kSingleGameMenu);
			break;
		case subID_multi:
		default:
			event.Skip();
			break;
	}

}