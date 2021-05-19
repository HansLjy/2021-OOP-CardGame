#include "wx/wxprec.h"

#ifndef WX_PRECOMP
	#include "wx/wx.h"
#endif

#include "myapp.h"
#include "TextFrame.h"

IMPLEMENT_APP(GameApp)

bool GameApp::OnInit()
{
	TextFrame *frame = new TextFrame(
		wxT("Simple Text Editor"), 100, 100, 400, 300);
	frame->Show(TRUE);
	SetTopWindow(frame);
	return true;
}