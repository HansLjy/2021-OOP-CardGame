#include "myapp.h"
#include "interface.h"

MainFrame::MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
	: wxFrame (NULL, wxID_ANY, title, pos, size), app_status(kMainMenu) {
	wxMenu *menuFile = new wxMenu;
    menuFile->Append(ID_Hello, "&Hello...\tCtrl-H",
                     "Help string shown in status bar for this menu item");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);
    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append( menuFile, "&File" );
    menuBar->Append( menuHelp, "&Help" );
    SetMenuBar( menuBar );
    CreateStatusBar();
    SetStatusText( "Game Initialized!");
	Center();
	p_canvas = new MainMenuCanvas(this);
}

void MainFrame::Refresh() {
	this->Show(true);
}

void MainFrame::OnHello(wxCommandEvent& event) {
	wxLogMessage("Hello World from Hans");
}

void MainFrame::OnExit(wxCommandEvent& event) {
	Close(true);
}

void MainFrame::OnAbout(wxCommandEvent& event) {
	wxMessageBox("Card Game by OOP G1", "About this game", wxOK | wxICON_INFORMATION);
}

bool GameApp::OnInit() {
	Initialization();
	p_mainframe = new MainFrame(GAME_TITLE, wxPoint(50, 50));
	p_mainframe->Refresh();
	return true;
}

enum {
	mainID_Poke = 1001,
	mainID_UNO = 1002
};

MainMenuCanvas::MainMenuCanvas(MainFrame* p_frame) : BaseCanvas (p_frame) {
	p_button = new wxButton(this, wxID_EXIT, wxT("Quit"), wxPoint(20, 20));
}

MainMenuCanvas::~MainMenuCanvas() {
	if (p_button) {
		delete p_button;
	}
}

wxIMPLEMENT_APP(GameApp);