#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Map.h"
#include "j1PathFinding.h"
#include "j1Gui.h"
#include "j1Scene.h"
#include "j1Fonts.h"

#include "UI_Text_Box.h"
#include "UI_Button.h"
#include "UI_Interactive_String.h"

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
	//Map Load --------------------------------------------
	if (App->map->Load("iso_walk.tmx") == true)
	{
		int w, h;
		uchar* data = NULL;
		if (App->map->CreateWalkabilityMap(w, h, &data))
			App->pathfinding->SetMap(w, h, data);

		RELEASE_ARRAY(data);
	}
	debug_tex = App->tex->Load("maps/path2.png");

	//UI Scene build --------------------------------------
	scene_1_screen = new UI_Element({ 0,0 }, UNDEFINED, true);

	UI_IMG test_image({ 50,50 }, 0);
	blizzard_image = (UI_IMG*)scene_1_screen->AddChild((UI_Element*)&test_image);

	App->gui->PushScreen(scene_1_screen);
	/*
	App->gui->PushScreen(scene_1_screen);
	//UI Image test
	UI_IMG test_image({ 50,50 },0);

	
	blizzard_image = (UI_IMG*)App->gui->Create_UI_Element(IMG, ((UI_Element*)&test_image));



	//UI Interactive Text
	UI_String test({ 250,40 }, "Hello", App->font->default);

	UI_Interactive_String test_text({ 250,40 }, { 250,40,60,15 }, &test);
	interactive_text = (UI_Interactive_String*)App->gui->Create_UI_Element(INTERACTIVE_STRING, ((UI_Element*)&test_text));


	//UI Button test
	UI_IMG tex_on({ 120,350 }, { 415,168,222,67 });
	UI_IMG tex_off({ 120,350 }, { 647,168,221,67 });
	UI_IMG tex_over({ 120,350 }, { 6,116,220,60 });
	
	UI_Button button_test({ 120,280 }, { 120, 350,220,60 }, tex_on, tex_off, tex_over);
	button = (UI_Button*)App->gui->Create_UI_Element(BUTTON, ((UI_Element*)&button_test));
	*/

	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate()
{

	// debug pathfing ------------------
	static iPoint origin;
	static bool origin_selected = false;

	int x, y;
	App->input->GetMousePosition(x, y);
	iPoint p = App->render->ScreenToWorld(x, y);
	p = App->map->WorldToMap(p.x, p.y);

	if(App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
	{
		if(origin_selected == true)
		{
			App->pathfinding->CreatePath(origin, p);
			origin_selected = false;
		}
		else
		{
			origin = p;
			origin_selected = true;
		}
	}

	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{
	// Mouse Position -------------------------------------
	int x, y;
	App->input->GetMousePosition(x, y);



	// Gui Input ------------------------------------------
	/*if (App->input->GetMouseButtonDown(1) == KEY_DOWN || App->input->GetMouseButtonDown(1) == KEY_REPEAT) {

		//Button
		if (button->MouseIsIn({ x,y }))button->Change_State(ON);
		
		//Interactive Text
		if (interactive_text->MouseIsIn({ x,y }))interactive_text->SetString("Left Click");

	}
	else if (App->input->GetMouseButtonDown(3) == KEY_DOWN || App->input->GetMouseButtonDown(3) == KEY_REPEAT) {

		
		//Interactive Text
		if (interactive_text->MouseIsIn({ x,y }))interactive_text->SetString("Right Click");

	}
	else {

		//Interactive Text
		if (interactive_text->MouseIsIn({ x,y }))interactive_text->SetString("Mouse In");

		//Button
		if (button->MouseIsIn({ x,y }))button->Change_State(OVER);
		else button->Change_State(OFF);

	}*/

	


	// Hardware Input -------------------------------------
	if(App->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
		App->LoadGame("save_game.xml");

	if(App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
		App->SaveGame("save_game.xml");

	if(App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		App->render->camera.y += floor(200.0f * dt);

	if(App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		App->render->camera.y -= floor(200.0f * dt);

	if(App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		App->render->camera.x += floor(200.0f * dt);

	if(App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		App->render->camera.x -= floor(200.0f * dt);


	// Map Draw -------------------------------------------
	App->map->Draw();


	// Window Pathfinding Title --------------------------
	iPoint map_coordinates = App->map->WorldToMap(x - App->render->camera.x, y - App->render->camera.y);
	p2SString title("Map:%dx%d Tiles:%dx%d Tilesets:%d Tile:%d,%d",
					App->map->data.width, App->map->data.height,
					App->map->data.tile_width, App->map->data.tile_height,
					App->map->data.tilesets.count(),
					map_coordinates.x, map_coordinates.y);

	//App->win->SetTitle(title.GetString());



	// Debug pathfinding ----------------------------------
	App->input->GetMousePosition(x, y);
	iPoint p = App->render->ScreenToWorld(x, y);
	p = App->map->WorldToMap(p.x, p.y);
	p = App->map->MapToWorld(p.x, p.y);

	App->render->Blit(debug_tex, p.x, p.y);

	const p2DynArray<iPoint>* path = App->pathfinding->GetLastPath();

	for(uint i = 0; i < path->Count(); ++i)
	{
		iPoint pos = App->map->MapToWorld(path->At(i)->x, path->At(i)->y);
		App->render->Blit(debug_tex, pos.x, pos.y);
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
