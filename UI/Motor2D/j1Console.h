#ifndef _CONSOLE_H_
#define _CONSOLE_H_
#include "j1Module.h"
#include "SDL\include\SDL_rect.h"

struct UI_Text_Box;
struct UI_Scroll;
struct _TTF_Font;

class j1Console : public j1Module {
public:

	j1Console();
	~j1Console();

public:

	bool Awake(pugi::xml_node&);

	bool Start();

	bool PostUpdate();

	bool CleanUp();

private:

	SDL_Rect		console_area;
	SDL_Color		console_color;
	UI_Text_Box*	console_input_box;
	UI_Scroll*		console_scroll;
	_TTF_Font*		font;
	SDL_Color		font_color;
public:

	//Active / Desactive the Console
	void ChangeConsoleState();
	//Add a label in the console text scroll
	void AddConsoleText(char* new_text);

};
#endif