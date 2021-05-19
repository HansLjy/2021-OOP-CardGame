#ifndef TEXTEDITORAPP_H
#define TEXTEDITORAPP_H
#include "wx/wxprec.h"

class GameApp : public wxApp {
public:
	virtual bool OnInit();
};

DECLARE_APP(GameApp)

#endif // TEXTEDITORAPP_H