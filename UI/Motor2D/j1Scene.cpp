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

	_TTF_Font* test_font = App->font->Load("fonts/open_sans/OpenSans-BoldItalic.ttf", 26);
	/*
	text_box = new UI_Text_Box({ 250,350,50,15 }, UI_String({ 0,0 }, "Your Name"), 3, 9, false);
	text_box->SetTabable();
	scene_1_screen->AddChild(text_box);
	*/

	player1_item = new UI_Image({ 20,450 }, { 1485, 110, 72, 109 },0);
	player1_item->AdjustBox();
	scene_1_screen->AddChild(player1_item);
	/*player1_item->SetTabable();
	scene_1_screen->AddChild((UI_Element*)player1_item);
	*/

	/*
	UI_IMG({ 197,20 }, { 1000,880,19,20 });
	UI_IMG scroll_item({ 517,20 }, { 1000,880,19,20 });
	scroll_item.AdjustBox();
	UI_IMG({ 200,20 }, { 985,874,13,149 });
	UI_IMG scroll_back({ 520,20 }, { 985,874,13,149 });
	scroll_back.AdjustBox();
	*/
	UI_Image item({ 397,20,19,40 }, { 1000,880,19,20 });
	scroll = new UI_Scroll({ 250,250,450,350 }, { 20,20,300,250 }, item, UI_Image({ 400,20 }, { 985,874,13,149 }), VERTICAL, 1500);
	scroll->AddScrollItem(player1_item);
	scroll->ScrollBack.AdjustBox();
	//scroll->ScrollItem.AdjustBox();
	scroll->SetTabable();
	scene_1_screen->AddChild(scroll);

	
	text = new UI_String({ 400,500,0,0 }, "This code \n is a prank \n plz stop or I will kill myself gg.", 26, {255,255,255,255}, test_font);
	text->TokenizeString(5);
	text->AdjustBox();
	//text->TokenizeString();

	scene_1_screen->AddChild(text);
	

	/*
	ui coordinates
	- button 414,169,224,64
	*/
	App->gui->PushScreen(scene_1_screen);

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
	//Mouse Inputs ----------------------------------------
	int x, y;
	App->input->GetMouseMotion(x, y);

	
	if (scroll->MoveScroll(x, y) == false) {
		scroll->Drag();
	}
	
	text->Drag();
	player1_item->Drag();
	// Gui Input ------------------------------------------
	App->gui->CalculateUpperElement(scene_1_screen);

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN && App->gui->ItemSelected == player1_item) {

		this->player1_item->MoveBox(5, 0);
	}

	return true;
}

// Called each loop iteration
bool j1Scene::PostUpdate()
{
	bool ret = true;

	if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool j1Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}
