#ifndef CANVAS_H
#define CANVAS_H

#include <wx/panel.h>
#include <wx/dc.h>
#include "myapp.h"

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

#endif // CANVAS_H

