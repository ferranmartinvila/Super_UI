#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1Input.h"
#include "j1Gui.h"

#include "UI_Text_Box.h"
#include "UI_Button.h"


j1Gui::j1Gui() : j1Module()
{
	name.create("gui");
}

// Destructor
j1Gui::~j1Gui()
{}

// Called before render is available
bool j1Gui::Awake(pugi::xml_node& conf)
{
	LOG("Loading GUI atlas");
	bool ret = true;

	atlas_file_name = conf.child("atlas").attribute("file").as_string("");

	return ret;
}

// Called before the first frame
bool j1Gui::Start()
{
	atlas = App->tex->Load(atlas_file_name.GetString());

	return true;
}

// Update all guis
bool j1Gui::PreUpdate()
{
	return true;
}

// Called after all Updates
bool j1Gui::PostUpdate()
{
	return true;
}

// Called before quitting
bool j1Gui::CleanUp()
{
	LOG("Freeing GUI");

	return true;
}


//UI ELEMENTS FUNCTIONS ============================================
UI_Element * j1Gui::Create_UI_Element(UI_TYPE ui_type, UI_Element* element)
{
	//Pointer to new
	UI_Element* new_element = element;

	//Define the UI Element type
	UI_TYPE type;
	if (element != nullptr) {
		type = element->ui_type;
		switch (type) {
		case UI_TYPE::IMG:			new_element = new UI_IMG(((UI_IMG&)element));				break;
		case UI_TYPE::STRING:		new_element = new UI_String((UI_String&)element);			break;
		case UI_TYPE::BUTTON:		new_element = new UI_Button((UI_Button&)element);			break;
		case UI_TYPE::TEXT_BOX:		new_element = new UI_Text_Box((UI_Text_Box&)element);		break;
		}
	}

	else {
		type = ui_type;
		switch (type) {
		case UI_TYPE::IMG:			new_element = new UI_IMG();									break;
		case UI_TYPE::STRING:		new_element = new UI_String();								break;
		case UI_TYPE::BUTTON:		new_element = new UI_Button();								break;
		case UI_TYPE::TEXT_BOX:		new_element = new UI_Text_Box();							break;
		}
	}

	//Add the new element to the ui_elements list
	ui_elements.add(new_element);

	return new_element;
}

bool j1Gui::Delete_UI_Element(uint index)
{
	return ui_elements.del(ui_elements.At(index));;
}

bool j1Gui::Delete_UI_Element(UI_Element* element)
{
	return ui_elements.del(ui_elements.At(ui_elements.find(element)));
}

// =================================================================

// const getter for atlas
const SDL_Texture* j1Gui::GetAtlas() const
{
	return atlas;
}

// class Gui ---------------------------------------------------

