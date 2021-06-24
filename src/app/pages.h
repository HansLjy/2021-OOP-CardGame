#pragma once
#include "wx/panel.h"
#include "wx/textctrl.h"
#include "wx/textwrapper.h"
#include "wx/spinctrl.h"
#include "wx/choice.h"
#include "image_panel.h"
#include "deck.h"
#include "wrapper.h"
#include "message.h"

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
	
	enum Status {
		kWaiting,
		kJoining
	} status;

	int			count;
	wxWindow	*p_parent;
	wxTimer		*timer;
	MyLabel		*wait_label;

	void StartPending(Status status);
	void StopPending();
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
public:
	// Status
	int num_players;			// 玩家的数量
	int num_cards[4];			// 牌的数量
	int stake;					// 倍数
	int count_down;				// 倒计时，开始倒计时的时候将其设置为倒计时的初始时间
	int smallest_bid;			// 最小初始分
	int largest_bid;			// 最大初始分

	bool is_counting_down;		// 是否正在倒计时
	bool show_stake;			// 是否显示倍数
	bool show_count_down;		// 是否显示倒计时
	bool is_auction;			// 是否是叫分，叫分时候右下角显示四个按钮
	bool is_my_turn;			// 是否轮到我行动，轮到我行动的时候

	CardSet my_cards;			// 我的牌
	CardSet last_round_card[4];	// 上一轮的牌
	wxString user_name[4];		// 用户名
	string info;
	Message LastRequest;

	GameInterface () = delete;
	GameInterface (wxWindow* p_parent);

	wxTimer			*timer;
	MyLabel			*timer_label;
	MyLabel			*center_info;
	MyLabel			*user_info[4];
	wxWindow		*p_parent;
	MyButton		*deal;
	MyButton		*pass;
	MyButton		*call_auction[4];
	wxClientDC		dc;
	DeckPanel		*deck[4];
	DeckPanel		*last_round[4];
	wxPanel			*midpan;

	void StartGame();

	void OnDeal(wxCommandEvent &event);
	void OnPass(wxCommandEvent &event);
	void OnTimer(wxTimerEvent &event);
	void Render();

	wxDECLARE_EVENT_TABLE();
};