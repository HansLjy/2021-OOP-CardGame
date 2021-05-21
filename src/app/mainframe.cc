#include "mainframe.h"

MainFrame::MainFrame(const wxString& title) :
	wxFrame(nullptr, wxID_ANY, title, k_default_position, k_default_size) {
	menu_bar = new wxMenuBar;
	file = new wxMenu;
	file->Append(wxID_EXIT, wxT("&Quit"));
	Connect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrame::OnQuit));

	menu_bar->Append(file, wxT("&File"));
	SetMenuBar(menu_bar);

	Center();
}

void MainFrame::OnQuit(wxCommandEvent& event) {
	Close(true);
}