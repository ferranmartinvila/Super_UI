#ifndef __j1SCENE_H__
#define __j1SCENE_H__

#include "j1Module.h"

struct SDL_Texture;
struct UI_Button;
struct UI_String;
struct UI_Interactive_String;
struct UI_IMG;
struct UI_Element;

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

	SDL_Texture* debug_tex;

private:

	//Scene
	UI_Element* scene_1_screen;

	//Scene Items
	UI_IMG*		window_img;
	UI_Button*	button;

	//UI_Interactive_String* interactive_text;
	UI_IMG* blizzard_image;
	UI_IMG* blizzard_child;
	UI_IMG* blizzard_child_child;

};

#endif // __j1SCENE_H__