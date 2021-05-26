#pragma once
#include "wx/simplebook.h"
#include "pages.h"

class PageController : public wxSimplebook {
public:
	PageController () = delete;
	PageController (wxWindow* p_parent);
	MainMenu *main_menu;
	SubMenu *sub_menu_uno, *sub_menu_poke;
	SingleGameMenu *single_game_menu;

	void OnQuit(wxCommandEvent& event);
	void OnButton(wxCommandEvent& event);
};