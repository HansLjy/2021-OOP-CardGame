#pragma once
#include "wx/simplebook.h"
#include "pages.h"

enum GUISingleOrMulti {
	kSingle = 0,
	kMulti
};

enum GUIGameType {
	kPoke = 0,
	kLandlord
};

enum GUIJoinOrCreate {
	kJoin,
	kCreate
};

struct AppStatus {
	GUISingleOrMulti single_multi;
	GUIGameType	game_type;
	GUIJoinOrCreate join_create;
	wxString user_name;
	wxString IP_address;
	wxString passwd;
	wxString winner = "Hans & Stella";
	int player_number;
};

class PageController : public wxSimplebook {
public:
	AppStatus app_status;

	PageController () = delete;
	PageController (wxWindow* p_parent);
	MainMenu				*main_menu;
	SingleGameMenu			*single_game_menu;
	MultiGameMenu			*multi_game_menu;
	MultiGameJoinSetting	*multi_game_join_setting;
	MultiGameCreateSetting	*multi_game_create_setting;
	GamePending				*game_pending;
	GameOver				*game_over;
	GameInterface			*game_interface;

	void OnQuit(wxCommandEvent& event);
	void OnButton(wxCommandEvent& event);

	bool Pending();
};