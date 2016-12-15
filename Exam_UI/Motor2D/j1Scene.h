#ifndef __j1SCENE_H__
#define __j1SCENE_H__

#include "j1Module.h"

struct SDL_Texture;
struct UI_Button;
struct UI_String;
struct UI_Interactive_String;
struct UI_IMG;
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
	bool Awake();

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

private:

	//Scene
	UI_Element* scene_1_screen;

	UI_String* text;

	UI_IMG*		player1_item;
	UI_Scroll*	scroll;

	UI_Text_Box* text_box;

};

#endif // __j1SCENE_H__