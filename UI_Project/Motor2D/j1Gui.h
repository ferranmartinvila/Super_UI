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
	p2List<UI_Element*> ui_elements;

public:

	// UI elements functions
	UI_Element* Create_UI_Element(UI_TYPE ui_type, UI_Element* element = nullptr);
	
	bool Delete_UI_Element(uint index);
	
	bool Delete_UI_Element(UI_Element* element);

private:

	SDL_Texture* atlas;
	p2List<SDL_Texture*> ui_textures;
	p2SString atlas_file_name;

public:

	//UI textures functions
	const SDL_Texture* GetAtlas() const;

	SDL_Texture* Get_UI_Texture(uint tex_id);

};

#endif // __j1GUI_H__