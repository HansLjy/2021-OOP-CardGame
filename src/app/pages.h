#pragma once
#include "wx/panel.h"
#include "wx/textctrl.h"
#include "wx/textwrapper.h"
#include "wx/spinctrl.h"
#include "wx/choice.h"
#include "image_panel.h"
#include "deck.h"
#include "wrapper.h"

class MainMenu : public wxPanel {
public:
	MainMenu () = delete;
	MainMenu (wxWindow* p_parent);

	wxWindow 	 *p_parent;
	wxPanel 	 *right_panel;
	wxImagePanel *image;
	MyLabel 	 *title;
	MyButton 	 *b_play_single;
	MyButton 	 *b_play_multi;
	MyButton 	 *b_quit;

	void OnPlaySingle(wxCommandEvent& event);
	void OnPlayMulti(wxCommandEvent& event);
	void OnQuit(wxCommandEvent& event);

	wxDECLARE_EVENT_TABLE();
};

class SingleGameMenu : public wxPanel {
public:
	SingleGameMenu () = delete;
	SingleGameMenu (wxWindow *p_parent);

	MyLabel 		*title;
	wxWindow 	 	*p_parent;
	MyLabel 		*game_select_label;
	wxChoice		*game_select;
	MyLabel 		*user_name_label;
	wxTextCtrl   	*user_name_input;
	MyLabel 		*user_number_label;
	wxSpinCtrl   	*user_number_input;
	MyButton		*confirm;
	MyButton		*go_back;

	void OnConfirm(wxCommandEvent &event);
	void OnReturn(wxCommandEvent &event);

	wxDECLARE_EVENT_TABLE();
};

class MultiGameMenu : public wxPanel {
public:
	MultiGameMenu () = delete;
	MultiGameMenu (wxWindow *p_parent);

	wxWindow		*p_parent;
	MyLabel			*title;
	MyButton		*join_game;
	MyButton		*create_game;
	MyButton		*go_back;

	void OnJoin(wxCommandEvent &event);
	void OnCreate(wxCommandEvent &event);
	void OnReturn(wxCommandEvent &event);

	wxDECLARE_EVENT_TABLE();
};

class MultiGameJoinSetting : public wxPanel {
public:
	MultiGameJoinSetting () = delete;
	MultiGameJoinSetting (wxWindow *p_parent);
	
	wxWindow		*p_parent;
	MyLabel			*title;
	MyLabel			*user_name_label;
	wxTextCtrl		*user_name_input;
	MyLabel			*IP_label;
	wxTextCtrl		*IP_input;
	MyLabel			*passwd_label;
	wxTextCtrl		*passwd_input;
	MyButton		*confirm;
	MyButton		*go_back;

	void OnConfirm(wxCommandEvent &event);
	void OnReturn(wxCommandEvent &event);

	wxDECLARE_EVENT_TABLE();
};

class MultiGameCreateSetting : public wxPanel {
public:
	MultiGameCreateSetting () = delete;
	MultiGameCreateSetting (wxWindow *p_parent);

	wxWindow		*p_parent;
	MyLabel			*title;
	MyLabel 		*game_select_label;
	wxChoice		*game_select;
	MyLabel			*user_name_label;
	wxTextCtrl		*user_name_input;
	MyLabel 		*user_number_label;
	wxSpinCtrl   	*user_number_input;
	MyLabel			*passwd_label;
	wxTextCtrl		*passwd_input;
	MyButton		*confirm;
	MyButton		*go_back;

	void OnConfirm(wxCommandEvent &event);
	void OnReturn(wxCommandEvent &event);

	wxDECLARE_EVENT_TABLE();
};

class GamePending : public wxPanel {
public:
	GamePending () = delete;
	GamePending (wxWindow *p_parent);

	int			count;
	wxWindow	*p_parent;
	wxTimer		*timer;
	MyLabel		*wait_label;

	void StartPending();
	void OnTimer(wxTimerEvent& event);

	wxDECLARE_EVENT_TABLE();
};

class GameOver : public wxPanel {
	wxWindow	*p_parent;
	wxButton	*go_back;
	MyLabel		*winner_label;
	MyLabel		*title;

public:
	GameOver () = delete;
	GameOver (wxWindow *p_parent);	

	void SetWinner();
	void OnReturn(wxCommandEvent &event);
	wxDECLARE_EVENT_TABLE();
};

class GameInterface : public wxPanel {
	int num_cards[4];		// 牌的数量
	int ratio;				// 倍数
	CardSet my_cards;		// 我的牌
	CardSet last_round_card[4];

public:
	GameInterface () = delete;
	GameInterface (wxWindow* p_parent);

	int 			count_down;
	wxTimer			*timer;
	MyLabel			*timer_label;
	MyLabel			*game_info;
	MyLabel			*info_label[4];
	wxWindow		*p_parent;
	MyButton		*deal;
	MyButton		*pass;
	wxClientDC		dc;
	DeckPanel		*deck[4];
	DeckPanel		*last_round[4];
	wxPanel			*midpan;

	void OnDeal(wxCommandEvent &event);
	void OnPass(wxCommandEvent &event);
	void OnTimer(wxTimerEvent &event);
	void Render();

	wxDECLARE_EVENT_TABLE();
};