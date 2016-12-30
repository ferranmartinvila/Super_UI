#include "j1Console.h"

#include "p2Log.h"

#include "j1App.h"
#include "j1Input.h"
#include "j1Render.h"

#include "UI_Scroll.h"
#include "UI_String.h"
#include "UI_Text_Box.h"

//Constructors ============================================
j1Console::j1Console()
{
	name.create("console");
}


//Destructors =============================================
j1Console::~j1Console()
{

}

//Game Loop ===============================================
bool j1Console::Awake(pugi::xml_node& config)
{
	LOG("Console Awake");
	App->gui->SetDefaultInputTarget(this);

	//Load console window size
	console_area.x = config.child("area").attribute("x").as_int();
	console_area.y = config.child("area").attribute("y").as_int();
	console_area.w = config.child("area").attribute("w").as_int();
	console_area.h = config.child("area").attribute("h").as_int();
	//Load console window color
	console_color.r = config.child("area_color").attribute("r").as_int();
	console_color.g = config.child("area_color").attribute("g").as_int();
	console_color.b = config.child("area_color").attribute("b").as_int();
	console_color.a = config.child("area_color").attribute("a").as_int();

	//Load Console Text Box
	SDL_Rect input_box;
	input_box.x = config.child("input_box").attribute("x").as_int();
	input_box.y = config.child("input_box").attribute("y").as_int();
	input_box.w = config.child("input_box").attribute("w").as_int();
	input_box.h = config.child("input_box").attribute("h").as_int();
	
	//Load Console Text Font
	font = App->font->Load(config.child("console_font").attribute("file").as_string(), config.child("console_font").attribute("size").as_int());
	font_color.r = config.child("font_color").attribute("r").as_int();
	font_color.g = config.child("font_color").attribute("g").as_int();
	font_color.b = config.child("font_color").attribute("b").as_int();
	font_color.a = config.child("font_color").attribute("a").as_int();
	
	//Load Text Cursor
	int cursor_w = config.child("cursor").attribute("w").as_int();
	int cursor_h = config.child("cursor").attribute("h").as_int();
	
	//Build Console Text
	UI_String* console_text = new UI_String({ 0,0,0,0 }, "", { font_color.r,font_color.g,font_color.b,font_color.a }, font);
	console_input_box = new UI_Text_Box(input_box, console_text, cursor_w, cursor_h);
	
	//Build Console Labels Scroll
	UI_Image scroll_item({ console_area.w - 28,20 }, { 1000,880,19,20 });
	scroll_item.AdjustBox();
	UI_Image scroll_back({ console_area.w - 25,20 }, { 985,874,13,149 });
	scroll_back.AdjustBox();
	SDL_Rect scroll_area = { console_area.x,console_area.y,console_area.w,console_area.y - (console_area.y - input_box.y) };
	SDL_Rect viewport_area = { scroll_area.x,scroll_area.y,scroll_item.GetBox()->x,input_box.y };
	console_labels_scroll = new UI_Scroll(scroll_area, viewport_area, scroll_item, scroll_back);

	LOG("Console Build");

	return true;
}

bool j1Console::Start()
{
	GenerateLabelsTextures();
	UpdateConsoleLabels();
	return true;
}

bool j1Console::PostUpdate()
{
	//Update Console Input Box
	console_input_box->HandleInput();
	console_labels_scroll->HandleInput();
	
	UpdateConsoleLabels();

	
	//Draw Console Area
	App->render->DrawQuad(console_area, console_color.r, console_color.g, console_color.b, console_color.a);

	//Draw console labels
	console_labels_scroll->Draw(true);

	//Draw Console Input Box
	console_input_box->Draw(true);
	
	return true;
}

bool j1Console::CleanUp()
{
	return true;
}


void j1Console::GUI_Input(UI_Element * target, GUI_INPUT input)
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
		if (target == console_labels_scroll)
		{
			console_labels_scroll->MoveScroll(x, y);
		}
		break;
	case MOUSE_LEFT_BUTTON_UP:
		if (target == console_labels_scroll)
		{
			console_labels_scroll->UnselectScroll();
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

// Functionality =========================================
void j1Console::ChangeConsoleState()
{
	active = !active;
	if(active == true)App->gui->ItemSelected = console_input_box;
	else this->console_input_box->SetText("");
}

void j1Console::AddConsoleText(char* new_text)
{
	UI_String* label = new UI_String({ 0,0,0,0 }, new_text, font_color, font);
	console_labels.PushBack(label);
}

void j1Console::GenerateLabelsTextures()
{
	uint labels_num = console_labels.Count();
	for (uint k = 0; k < labels_num; k++)
	{
		console_labels[k]->SetFont(font);
		console_labels[k]->SetColor(font_color);
		console_labels[k]->GenerateTexture();
		console_labels[k]->AdjustBox();
		
	}
}

void j1Console::UpdateConsoleLabels()
{
	uint labels_num = console_labels.Count();
	uint scroll_labels_num = console_labels_scroll->GetScrollItemsNum();

	if (scroll_labels_num == labels_num)return;
	
	for (uint k = scroll_labels_num; k < labels_num; k++)
	{
		console_labels_scroll->AddScrollItemAtBottom(((UI_String*)*console_labels.At(k)));
	}
}
