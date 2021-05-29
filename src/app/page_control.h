#pragma once
#include "wx/simplebook.h"
#include "pages.h"

class PageController : public wxSimplebook {
public:
	PageController () = delete;
	PageController (wxWindow* p_parent);
	MainMenu				*main_menu;
	SingleGameMenu			*single_game_menu;
	MultiGameMenu			*multi_game_menu;
	MultiGameJoinSetting	*multi_game_join_setting;
	MultiGameCreateSetting	*multi_game_create_setting;
	GameInterface			*game_interface;

	void OnQuit(wxCommandEvent& event);
	void OnButton(wxCommandEvent& event);
};