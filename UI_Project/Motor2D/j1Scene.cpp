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

	text_box = new UI_Text_Box({ 250,350,50,15 }, UI_String({ 0,0 }, "Your Name", App->font->default));
	scene_1_screen->AddChild(text_box);

	/*background = new UI_IMG({ 0,0 }, { 970, 1844, 768, 579 }, 2);
	scene_1_screen->AddChild((UI_Element*)background);
	*/
	player1_item = new UI_IMG({ 240,78 }, { 1485, 110, 72, 109 }, 2);
	scene_1_screen->AddChild((UI_Element*)player1_item);

	App->gui->PushScreen(scene_1_screen);
	App->gui->ItemSelected = player1_item;

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
	text_box->Select();

	// Gui Input ------------------------------------------
	App->gui->CalculateUpperElement(scene_1_screen,0);

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
