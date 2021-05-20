#include "canvas.h"

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