#include "wx/sizer.h"
#include "wx/panel.h"
#include <vector>

class CenterBlockSizer : public wxBoxSizer {
public:
	CenterBlockSizer(wxWindow* p_prent);
	void AddWidget(bool new_line, wxWindow* widget);
	void Create();

private:
	wxWindow 	*p_parent;
	wxPanel 	*panel;
	wxBoxSizer	*panel_box, *hbox;
	std::vector <wxBoxSizer*> hboxes;
};