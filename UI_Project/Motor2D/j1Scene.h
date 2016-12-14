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

	//Exam
	UI_IMG* background;
	UI_IMG* player1_avatar;
	UI_IMG* player2_avatar;

	UI_IMG* player1_item;
	uint	p1_avatar_id = 0;
	UI_IMG* player2_item;
	uint	p2_avatar_id = 5;
	uint*	current_id = 0;

public:

	void ChangeAvatar(UI_IMG* target);

};

#endif // __j1SCENE_H__