#pragma once
#include "wx/panel.h"
#include "wx/textctrl.h"
#include "wx/textwrapper.h"
#include "image_panel.h"

class MainMenu : public wxPanel {
public:
	MainMenu () = delete;
	MainMenu (wxWindow* p_parent);

	wxWindow *p_parent; 
	wxImagePanel *image;
	wxStaticText *title;
	wxButton *b_play_UNO;
	wxButton *b_play_Poke;
	wxButton *b_quit;

	void OnPlayUNO(wxCommandEvent& event);
	void OnPlayPoke(wxCommandEvent& event);
	void OnQuit(wxCommandEvent& event);

};

enum GameType {
	kUNO,
	kPoke
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