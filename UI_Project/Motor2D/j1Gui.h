#ifndef __j1GUI_H__
#define __j1GUI_H__

#include "j1Module.h"
#include "UI_Element.h"

#define CURSOR_WIDTH 2


// ---------------------------------------------------
class j1Gui : public j1Module
{
public:

	j1Gui();

	// Destructor
	virtual ~j1Gui();

	// Called when before render is available
	bool Awake(pugi::xml_node&);

	// Call before first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called after all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

private:

	//UI elements
	UI_Element* screen;

	//UI Textures
	SDL_Texture* atlas;
	p2List<SDL_Texture*> ui_textures;
	p2SString atlas_file_name;

public:

	//UI textures functions
	const SDL_Texture* GetAtlas() const;
	SDL_Texture* Get_UI_Texture(uint tex_id);

	//UI elements functions
	uint PushScreen(const UI_Element& new_screen);

};

#endif // __j1GUI_H__