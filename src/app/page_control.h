#pragma once
#include "wx/simplebook.h"
#include "pages.h"

class PageController : public wxSimplebook {
public:
	PageController () = delete;
	PageController (wxWindow* p_parent);
	MainMenu *p_main_menu;
	SubMenu *p_sub_menu_uno, *p_sub_menu_poke;

	void OnQuit(wxCommandEvent& event);
	void OnButton(wxCommandEvent& event);
};