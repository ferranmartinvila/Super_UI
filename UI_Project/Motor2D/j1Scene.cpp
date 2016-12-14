#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Gui.h"
#include "j1Scene.h"


//UI Elements
#include "UI_Text_Box.h"
#include "UI_Button.h"
#include "UI_String.h"
#include "UI_Scroll.h"


j1Scene::j1Scene() : j1Module()
{
	name.create("scene");
}

// Destructor
j1Scene::~j1Scene()
{}

// Called before render is available
bool j1Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool j1Scene::Start()
{
	//UI Scene build --------------------------------------
	scene_1_screen = new UI_Element({ 0,0,App->win->screen_surface->w, App->win->screen_surface->h }, UNDEFINED, true);


	UI_IMG back({ 0,0 },2, { 970, 1844, 768, 579 });
	background = (UI_IMG*)scene_1_screen->AddChild((UI_Element*)&back);

	UI_IMG p1_item({ 240,78 }, 2, { 1485, 110, 72, 109 });
	player1_item = (UI_IMG*)background->AddChild((UI_Element*)&p1_item);

	UI_IMG p2_item({ 312,174 }, 2, { 1560, 110, 72, 109 });
	player2_item = (UI_IMG*)background->AddChild((UI_Element*)&p2_item);

	UI_IMG p1_avatar({ 24, 61 }, 2,{ 925, 605, 168, 279 });
	player1_avatar = (UI_IMG*)background->AddChild((UI_Element*)&p1_avatar);

	UI_IMG p2_avatar({ 543, 61 }, 2, { 1093, 884, 168, 279 });
	player2_avatar = (UI_IMG*)background->AddChild((UI_Element*)&p2_avatar);

	App->gui->PushScreen(scene_1_screen);
	App->gui->ItemSelected = player1_item;
	current_id = &p1_avatar_id;

	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{

	// Gui Input ------------------------------------------
	App->gui->CalculateUpperElement(scene_1_screen,0);
	bool action = false;

	//Swap Selection
	if (App->input->GetKey(SDL_SCANCODE_TAB) == KEY_DOWN)
	{
		if (App->gui->ItemSelected == player1_item)
		{
			App->gui->ItemSelected = player2_item;
			current_id = &p2_avatar_id;
		}
		else
		{
			App->gui->ItemSelected = player1_item;
			current_id = &p1_avatar_id;
		}
	}

	//Move Right
	else if(App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN && App->gui->ItemSelected->box.x < 450)
	{
		App->gui->ItemSelected->MoveBox(72, 0);
		*current_id += 1;
		action = true;
	}
	//Move Left
	else if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN && App->gui->ItemSelected->box.x > 250)
	{
		App->gui->ItemSelected->MoveBox(-72, 0);
		*current_id -= 1;
		action = true;
	}
	//Move Up
	else if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN && App->gui->ItemSelected->box.y > 170)
	{
		App->gui->ItemSelected->MoveBox(0, -96);
		*current_id -= 4;
		action = true;
	}
	//Move Down
	else if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN && App->gui->ItemSelected->box.y < 170)
	{
		App->gui->ItemSelected->MoveBox(0, 96);
		*current_id += 4;
		action = true;
	}

	//Change current player avatar
	if (action)
	{
		if (App->gui->ItemSelected == player1_item)ChangeAvatar(player1_avatar);
		else ChangeAvatar(player2_avatar);
	}

	return true;
}

// Called each loop iteration
bool j1Scene::PostUpdate()
{
	bool ret = true;

	if(App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool j1Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}

void j1Scene::ChangeAvatar(UI_IMG * target)
{
	switch (*current_id) {
	case 0:		target->ChangeTextureRect({ 925, 605, 168, 279 });		break;
	case 1:		target->ChangeTextureRect({ 1093, 605, 168, 279 });		break;
	case 2:		target->ChangeTextureRect({ 1261, 605, 168, 279 });		break;
	case 3:		target->ChangeTextureRect({ 1429, 605, 168, 279 });		break;
	case 4:		target->ChangeTextureRect({ 925, 884, 168, 279 });		break;
	case 5:		target->ChangeTextureRect({ 1093, 884, 168, 279 });		break;
	case 6:		target->ChangeTextureRect({ 1261, 884, 168, 279 });		break;
	case 7:		target->ChangeTextureRect({ 1429, 884, 168, 279 });		break;
	}
}
