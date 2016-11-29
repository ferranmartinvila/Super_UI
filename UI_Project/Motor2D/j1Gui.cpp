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
#include "UI_Interactive_String.h"


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
	//Load Atlas
	atlas = App->tex->Load(atlas_file_name.GetString());

	//Load other textures
	ui_textures.add(App->tex->Load("gui/BlizzardLogo.png"));
	ui_textures.add(App->tex->Load("gui/WOWLogo.png"));
	
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

	p2List_item<UI_Element*>* item = ui_elements.start;
	while (item) {

		if (item->data->IsActive) {
			item->data->Update();
			item->data->Draw();
		}
		item = item->next;
	}

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

	//Copy factory
	if (element != nullptr) {
		type = element->ui_type;
		switch (type) {
		case UI_TYPE::IMG:					new_element = new UI_IMG(((UI_IMG*)element));										break;
		case UI_TYPE::STRING:				new_element = new UI_String((UI_String*)element);									break;
		case UI_TYPE::INTERACTIVE_STRING:	new_element = new UI_Interactive_Element((UI_Interactive_Element*)element);			break;
		case UI_TYPE::BUTTON:				new_element = new UI_Button((UI_Button*)element);									break;
		case UI_TYPE::TEXT_BOX:				new_element = new UI_Text_Box((UI_Text_Box*)element);								break;
		
		}
	}

	//Default factory
	else {
		type = ui_type;
		switch (type) {
		case UI_TYPE::IMG:					new_element = new UI_IMG();							break;
		case UI_TYPE::STRING:				new_element = new UI_String();						break;
		case UI_TYPE::INTERACTIVE_STRING:	new_element = new UI_Interactive_Element();			break;
		case UI_TYPE::BUTTON:				new_element = new UI_Button();						break;
		case UI_TYPE::TEXT_BOX:				new_element = new UI_Text_Box();					break;
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
const SDL_Texture* j1Gui::GetAtlas() const
{
	return atlas;
}

SDL_Texture * j1Gui::Get_UI_Texture(uint tex_id)
{
	if (tex_id > ui_textures.count() - 1)return nullptr;
	
	return ui_textures.At(tex_id)->data;
}

