#ifndef _CONSOLE_H_
#define _CONSOLE_H_

#include "j1Module.h"
#include "SDL\include\SDL_rect.h"
#include "p2DynArray.h"
#include "C_var.h"

struct UI_Text_Box;
struct UI_Scroll;
struct UI_String;
struct _TTF_Font;

enum CONSOLE_COMMAND_TYPE 
{
	INVALID,
	GET,
	SET,
	QUIT
};

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
	
	p2DynArray<Cvar*>		console_variables;
	
	_TTF_Font*				font;
	SDL_Color				font_color;

public:

	// Recieve UI input and work with it
	void GUI_Input(UI_Element* target, GUI_INPUT input);

	//Active / Desactive the Console
	void ChangeConsoleState();
	
	//Console Output ----------------------------
	//Add a text at text list of scroll
	void AddConsoleText(char* new_text);
	//Generate labels textures
	void GenerateLabelsTextures(uint index = 0);
	//Texturize the console labels and push it to the scroll
	void UpdateConsoleLabels();

	//Console Input -----------------------------
	//Get Cvar from input
	Cvar* GetCvarfromInput(char* input)const;
	//Get value from input
	char* GetValuefromInput(char* input)const;
	//Get input data
	CONSOLE_COMMAND_TYPE GetInputType(char* input);
	//Cvar type transformations
	char*		CvarTypetoString(C_VAR_TYPE cvar_type)const;
	C_VAR_TYPE	StringtoCvarType(const p2SString* string)const;
	//Command type transformations
	CONSOLE_COMMAND_TYPE StringtoCommandType(const p2SString* string)const;

	//Console Variables Creation ----------------
	//Add Console Variable
	Cvar* AddCvar(const char* name, const char* description,const char* value, C_VAR_TYPE cvar_type, j1Module* module_target);
	//Load Console Variable
	Cvar* LoadCvar(const char* name, const char* description,const char* value, C_VAR_TYPE cvar_type, j1Module* module_target);
	//Save Console Variable
	bool CreateCvar(const char* name, const char* description, const char* value, C_VAR_TYPE cvar_type, j1Module* module_target);



	//Handle Console Input ----------------------
	void Console_Input(Cvar* cvar, CONSOLE_COMMAND_TYPE command_type, p2SString* input);

};
#endif