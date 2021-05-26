#pragma once
#include "wx/panel.h"
#include "wx/textctrl.h"
#include "wx/textwrapper.h"
#include "wx/spinctrl.h"
#include "image_panel.h"
#include "deck.h"
#include "game.h"

class MainMenu : public wxPanel {
public:
	MainMenu () = delete;
	MainMenu (wxWindow* p_parent);

	wxWindow *p_parent;
	wxPanel *right_panel;
	wxImagePanel *image;
	wxStaticText *title;
	wxButton *b_play_UNO;
	wxButton *b_play_Poke;
	wxButton *b_quit;

	void OnPlayUNO(wxCommandEvent& event);
	void OnPlayPoke(wxCommandEvent& event);
	void OnQuit(wxCommandEvent& event);

};

class SubMenu : public wxPanel {
public:
	SubMenu (wxWindow* p_parent, GameType game_type);

	wxWindow *p_parent;
	wxImagePanel *image;
	wxStaticText *title;
	wxButton *b_single;
	wxButton *b_multi;
	wxButton *b_back;
	
	void OnSingle(wxCommandEvent& event);
	void OnMulti(wxCommandEvent& event);
	void OnBack(wxCommandEvent& event);
};

class SingleGameMenu : public wxPanel {
public:
	SingleGameMenu () = delete;
	SingleGameMenu (wxWindow *p_parent);

	wxStaticText *title;
	wxWindow *p_parent;
	wxStaticText *user_name_label;
	wxTextCtrl *user_name_input;
	wxStaticText *user_number_label;
	wxSpinCtrl *user_number_input;
	wxButton *confirm;
	wxButton *go_back;

	void OnConfirm(wxCommandEvent &event);
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