#ifndef __j1SCENE_H__
#define __j1SCENE_H__

#include "j1Module.h"
#include "p2DynArray.h"

struct SDL_Texture;
struct UI_Button;
struct UI_String;
struct UI_Interactive_String;
struct UI_Image;
struct UI_Element;
struct UI_Text_Box;
struct UI_Scroll;

class j1Scene : public j1Module
{
public:

	j1Scene();

	// Destructor
	virtual ~j1Scene();

	// Called before render is available
	bool Awake(pugi::xml_node& config);

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	// Recieve UI input and work with it
	void GUI_Input(UI_Element* target, GUI_INPUT input);

private:

	//Scene	UI
	UI_Element* scene_1_screen;

	//Scene UI Elements
	UI_Image*		player1_item;
	UI_Image*		player1_item_2;
	UI_Scroll*		scroll;
	UI_Scroll*		lateral_scroll;
	UI_Text_Box*	text_box;
	UI_Button*		button;

public:

	//Map Folders
	p2DynArray<p2SString> map_folder;

	uint current_map;

	//Change the current map
	void Change_Map();

	//Load the choosed Map
	bool Load_Current_Map();

	//Textures data
	SDL_Texture* tex_goal;
	SDL_Texture* tex_path;

};

#endif // __j1SCENE_H__