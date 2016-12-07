#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1Input.h"
#include "j1Gui.h"
#include "UI_Element.h"


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
	bool ret = true;

	p2List_item<UI_Element*>* item = screen.start;
	while (item) {

		if (item->data->IsActive)
			ret = item->data->Update();

		item = item->next;
	}
	
	return ret;
}

// Called after all Updates
bool j1Gui::PostUpdate()
{
	//Debug Mode ------------------------------------------
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN)debug = !debug;


	// Update & draw the UI screens
	p2List_item<UI_Element*>* item = screen.start;
	while (item) {

		if (item->data->IsActive)
			item->data->Draw(debug);

		item = item->next;
	}

	return true;
}

// Called before quitting
bool j1Gui::CleanUp()
{
	LOG("Freeing GUI");
	bool ret = true;
	p2List_item<UI_Element*>* item = screen.end;
	p2List_item<UI_Element*>* item_prev = nullptr;

	if (item != nullptr)item_prev = item->prev;
	while (item) {

		//CleanUp the item childs
		ret = item->data->CleanUp();
		//Delete all item data
		screen.del(item);

		item = item_prev;
		if(item_prev != nullptr)item_prev = item_prev->prev;

	}

	return true;
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

uint j1Gui::PushScreen(const UI_Element* new_screen)
{
	screen.add((UI_Element*)new_screen);
	return screen.count();
}

uint j1Gui::GetUpperElement(const UI_Element* parent, uint layer) const
{
	if (ItemSelected != nullptr)return 0;

	p2List_item<UI_Element*>* item = parent->childs.start;

	while (item) {

		layer = GetUpperElement(item->data,layer);

		if (item->data->layer > layer && item->data->IsActive && item->data->MouseIsIn())layer = item->data->layer;
		
		item = item->next;

	}
	return uint(layer);
}

