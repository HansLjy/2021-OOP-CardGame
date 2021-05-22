#pragma once
#include "wx/menu.h"
#include "wx/frame.h"
#include "page_control.h"

const wxPoint k_default_position(50, 50);
const wxSize k_default_size(800, 600);

class MainFrame : public wxFrame {
public:
	MainFrame () = delete;
	MainFrame (const wxString& title);

	PageController *m_controller;	// 页面选择器
	wxMenuBar *menu_bar; 			// 菜单栏
	wxMenu *file;					// 文件菜单

private:
	void OnQuit(wxCommandEvent& event);
};