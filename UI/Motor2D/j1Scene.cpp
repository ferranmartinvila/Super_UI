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
	App->gui->SetDefaultInputTarget(this);

	//UI Scene build --------------------------------------
	scene_1_screen = new UI_Element({ 0,0,App->win->screen_surface->w, App->win->screen_surface->h }, UNDEFINED, true);


	player1_item = new UI_Image({ 20,360 }, { 1485, 110, 72, 109 }, 0);
	player1_item->AdjustBox();

	UI_Image on({ 0,0 }, { 5,116,220,59 });
	UI_Image off({ 0,0 }, { 648,172,219,59 });
	UI_Image over({ 0,0 }, { 416,170,220,62 });
	button = new UI_Button({ 50,50,230,60 }, on, off, over);
	scene_1_screen->AddChild(button);

	UI_Image scroll_item({ 517,20 }, { 1000,880,19,20 });
	scroll_item.AdjustBox();
	UI_Image scroll_back({ 520,20 }, { 985,874,13,149 });
	scroll_back.AdjustBox();

	UI_Image item({ 397,20,19,40 }, { 1000,880,19,20 });
	scroll = new UI_Scroll({ 250,250,450,350 }, { 20,20,300,250 }, item, UI_Image({ 400,20 }, { 985,874,13,149 }), VERTICAL);
	scroll->AddScrollItem(player1_item);
	scroll->ScrollBack.AdjustBox();
	scroll->ScrollItem.AdjustBox();
	scroll->SetTabable();
	scene_1_screen->AddChild(scroll);

	text_box = new UI_Text_Box({ 0,0,50,50 }, UI_String({ 0,0,0,0 }, "") , 2, 5);
	scene_1_screen->AddChild(text_box);

	App->gui->PushScreen(scene_1_screen);
	// ----------------------------------------------------

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
	// Gui Upper Element ---------------------------
	App->gui->CalculateUpperElement(scene_1_screen);

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

void j1Scene::GUI_Input(UI_Element* target, GUI_INPUT input)
{
	int x, y;
	App->input->GetMouseMotion(x, y);
	switch (input)
	{
	case UP_ARROW:
		break;
	case DOWN_ARROW:
		break;
	case LEFT_ARROW:
		break;
	case RIGHT_ARROW:
		break;
	case MOUSE_LEFT_BUTTON_DOWN:
		break;
	case MOUSE_LEFT_BUTTON_REPEAT:
		if (target == player1_item)
		{
			player1_item->MoveBox(x, y);
		}
		else if (target == scroll)
		{
			if (scroll->MoveScroll(x,y) == false)scroll->MoveBox(x, y);
		}
		break;
	case MOUSE_LEFT_BUTTON_UP:
		if (target == scroll)
		{
			scroll->UnselectScroll();
		}
		break;
	case MOUSE_RIGHT_BUTTON:
		break;
	case BACKSPACE:
		break;
	case SUPR:
		break;
	case MOUSE_IN:
		break;
	case MOUSE_OUT:
		break;
	}
}
