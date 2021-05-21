#include "wx/menu.h"
#include "wx/frame.h"

const wxPoint k_default_position(50, 50);
const wxSize k_default_size(720, 540);

class MainFrame : public wxFrame {
public:
	MainFrame () = delete;
	MainFrame (const wxString& title);
	wxMenuBar *menu_bar; 
	wxMenu *file;

private:
	void OnQuit(wxCommandEvent& event);
};