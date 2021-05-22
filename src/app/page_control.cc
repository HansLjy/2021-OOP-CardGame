#include "page_control.h"
#include "page_control_event.h"

enum {
	kMainMenu = 0,
	kSubMenuUNO,
	kSubMenuPoke,
};

PageController::PageController(wxWindow* p_parent)
	: wxSimplebook(p_parent) {
	// Page ID: 0
	p_main_menu = new MainMenu(this);
	AddPage(p_main_menu, wxT("Main Menu"), true);

	// Page ID: 1
	p_sub_menu_uno = new SubMenu(this, kUNO);
	AddPage(p_sub_menu_uno, wxT("Sub Menu UNO"));

	// Page ID: 2
	p_sub_menu_poke = new SubMenu(this, kPoke);
	AddPage(p_sub_menu_poke, wxT("Sub Menu Poke"));

	Connect(mainID_play_UNO,  wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(OnButton));
	Connect(mainID_play_Poke, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(OnButton));
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
		default:
			event.Skip();
			break;
	}

}