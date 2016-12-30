#ifndef _CONSOLE_H_
#define _CONSOLE_H_

#include "j1Module.h"
#include "SDL\include\SDL_rect.h"
#include "p2DynArray.h"

struct UI_Text_Box;
struct UI_Scroll;
struct UI_String;
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

	SDL_Rect				console_area;
	SDL_Color				console_color;
	UI_Text_Box*			console_input_box;

	UI_Scroll*				console_labels_scroll;
	p2DynArray<UI_String*>	console_labels;
	
	_TTF_Font*				font;
	SDL_Color				font_color;

public:

	// Recieve UI input and work with it
	void GUI_Input(UI_Element* target, GUI_INPUT input);

	//Active / Desactive the Console
	void ChangeConsoleState();
	
	//Add a label in the console text scroll
	void AddConsoleText(char* new_text);
	
	//Generate labels textures
	void GenerateLabelsTextures();
	
	//Texturize the console labels and push it to the scroll
	void UpdateConsoleLabels();
};
#endif