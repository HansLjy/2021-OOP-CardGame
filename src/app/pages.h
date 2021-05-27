#pragma once
#include "wx/panel.h"
#include "wx/textctrl.h"
#include "wx/textwrapper.h"
#include "wx/spinctrl.h"
#include "wx/choice.h"
#include "image_panel.h"
#include "deck.h"
#include "game.h"

class MainMenu : public wxPanel {
public:
	MainMenu () = delete;
	MainMenu (wxWindow* p_parent);

	wxWindow 	 *p_parent;
	wxPanel 	 *right_panel;
	wxImagePanel *image;
	wxStaticText *title;
	wxButton 	 *b_play_single;
	wxButton 	 *b_play_multi;
	wxButton 	 *b_quit;

	void OnPlaySingle(wxCommandEvent& event);
	void OnPlayMulti(wxCommandEvent& event);
	void OnQuit(wxCommandEvent& event);

};

class SingleGameMenu : public wxPanel {
public:
	SingleGameMenu () = delete;
	SingleGameMenu (wxWindow *p_parent);

	wxStaticText 	*title;
	wxWindow 	 	*p_parent;
	wxStaticText 	*game_select_label;
	wxChoice		*game_select;
	wxStaticText 	*user_name_label;
	wxTextCtrl   	*user_name_input;
	wxStaticText 	*user_number_label;
	wxSpinCtrl   	*user_number_input;
	wxButton		*confirm;
	wxButton		*go_back;

	void OnConfirm(wxCommandEvent &event);
	void OnReturn(wxCommandEvent &event);
};

class MultiGameMenu : public wxPanel {
public:
	MultiGameMenu () = delete;
	MultiGameMenu (wxWindow *p_parent);

	wxWindow		*p_parent;
	wxStaticText	*title;
	wxButton		*join_game;
	wxButton		*create_game;
	wxButton		*go_back;

	void OnJoin(wxCommandEvent &event);
	void OnCreate(wxCommandEvent &event);
	void OnReturn(wxCommandEvent &event);
};

class GameInterface : public wxPanel {
public:
	GameInterface () = delete;
	GameInterface (wxWindow* p_parent);

	wxWindow *p_parent;
	wxClientDC dc;
	Deck deck[4];	// 四位玩家的手牌

	void render();
};