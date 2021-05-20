#ifndef MYAPP_H
#define MYAPP_H

#include <wx/wx.h>
#include <wx/frame.h>
#include <wx/panel.h>

#define GAME_TITLE "Card Game"
const int DEFAULT_SIZE_X = 720;
const int DEFAULT_SIZE_Y = 540;

enum AppStatus {
	kMainMenu,
	kGameMenu,
	kSinglePlayerSetting,
	kMultiPlayerMenu,
	kClientPlayerSetting,
	kServerPlayerSetting,
	kUNOGame,
	kPokeGame,
	kGameOver
};

class BaseCanvas;

class MainFrame : public wxFrame {
public:
	MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size = wxSize(DEFAULT_SIZE_X, DEFAULT_SIZE_Y));
	void Refresh();

private:
	AppStatus app_status;
	BaseCanvas* p_canvas;

	void OnHello(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	void OnExit(wxCommandEvent& event);

	wxDECLARE_EVENT_TABLE();
};

class BaseCanvas : public wxPanel {
public:
	BaseCanvas () = delete;
	BaseCanvas (MainFrame* p_frame) : wxPanel(p_frame) {}
	virtual ~BaseCanvas () = default;
};

enum {ID_Hello = 1}; 
wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
	EVT_MENU(ID_Hello,   MainFrame::OnHello)
	EVT_MENU(wxID_EXIT,  MainFrame::OnExit)
	EVT_MENU(wxID_ABOUT, MainFrame::OnAbout)
wxEND_EVENT_TABLE()

class GameApp : public wxApp {
private:
	MainFrame* p_mainframe;
public:
	virtual bool OnInit();
};

class MainMenuCanvas : public BaseCanvas {
private:
	wxButton* p_button;
public:
	MainMenuCanvas () = delete;
	MainMenuCanvas (MainFrame* p_frame);
	~MainMenuCanvas();
};

class GameMenuCanvas;
class SinglePlayerSettingCanvas;
class MultiPlayerMenuCanvas;
class ClientPlayerSettingCanvas;
class ServerPlayerSettingCanvas;
class UNOGameCanvas;
class PokeGameCanvas;
class GameOverCanvas;

#endif