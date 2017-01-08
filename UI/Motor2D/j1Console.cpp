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
	
	LOG("Console Config data Loaded");
	
	
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

	LOG("Console UI Build");

	//Build Cvars from config.xml
	pugi::xml_node c_var = config.child("c_vars").first_child();
	
	while (c_var != NULL)
	{
		//Load the cvar data from config.xml
		const char* name = c_var.attribute("name").as_string();
		const char* description = c_var.attribute("description").as_string();
		char* value = (char*)c_var.attribute("value").as_string();
		const char* type_c = c_var.attribute("type").as_string();
		C_VAR_TYPE type = StringtoCvarType(type_c);
		j1Module* module = App->GetModule((char*)c_var.attribute("module").as_string());
		
		//Build the new cvar
		Cvar* new_cvar = AddCvar(name, description, value, type, module);
		//LOG("-- %s -- Cvar from module %s added", new_cvar->GetCvarName(),new_cvar->GetCvarModule()->name.GetString());

		//Focus next cvar from config.xml
		c_var = c_var.next_sibling();
	}
	
	LOG("Console config.xml Variables Generated");

	return true;
}

bool j1Console::Start()
{
	GenerateLabelsTextures();
	UpdateConsoleLabels();
	LOG("Console Labels Generated");

	return true;
}

bool j1Console::PostUpdate()
{
	//Update Console Input Box
	console_input_box->HandleInput();
	console_labels_scroll->HandleInput();
	
	//Update Console LOG Labels
	UpdateConsoleLabels();
	
	//Draw Console Area
	App->render->DrawQuad(console_area, console_color.r, console_color.g, console_color.b, console_color.a);

	//Draw console labels
	if(console_labels_scroll->GetActiveState())console_labels_scroll->Draw(false);

	//Draw Console Input Box
	if(console_input_box->GetActiveState())console_input_box->Draw(true);
	
	return true;
}

bool j1Console::CleanUp()
{
	return true;
}

//Functionality ===========================================
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
	case ENTER:
		if (target == console_input_box)
		{
			Cvar* target_cvar = GetCvarfromInput(console_input_box->GetText());
			if (GetInputType(console_input_box->GetText()) == "get")
			{
				Console_Input(target_cvar, nullptr);
			}
			else Console_Input(target_cvar, this->GetValuefromInput(console_input_box->GetText()));
		}
		break;
	}
}

// Functionality =========================================
void j1Console::ChangeConsoleState()
{
	active = !active;
	if (active)
	{
		App->gui->ItemSelected = console_input_box;
		console_input_box->Activate();
		console_labels_scroll->Activate();
	}
	else
	{
		console_input_box->SetText(nullptr);
		console_input_box->Desactivate();
		console_labels_scroll->Desactivate();
	}
}

void j1Console::AddConsoleText(char* new_text)
{
	UI_String* label = new UI_String({ 0,0,0,0 }, new_text, font_color, font);
	console_labels.PushBack(label);
}

void j1Console::GenerateLabelsTextures(uint index)
{
	uint labels_num = console_labels.Count();
	for (uint k = index; k < labels_num; k++)
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
		GenerateLabelsTextures(k);
	}
}

Cvar* j1Console::AddCvar(const char * name,const char * description,char * value, C_VAR_TYPE cvar_type,j1Module* module_target)
{
	//Check if the cvar already exist
	uint num = console_variables.Count();
	for (uint k = 0; k < num; k++)
	{
		if (name == console_variables[k]->GetCvarName())return false;
	}
	
	//Create the new cvar
	Cvar* new_cvar = new Cvar(name, description, value, cvar_type, module_target);
	//Add it to the cvars array
	console_variables.PushBack(new_cvar);
	
	return new_cvar;
}

Cvar * j1Console::GetCvarfromInput(char * input) const
{
	char* cvar_name = new char[10];
	char* module_name = new char[10];

	uint name_init = 0;
	uint name_end = 0;
	uint module_init = 0;

	//Get the var name start and end position
	uint char_num = strlen(input) + 1;
	for (uint k = 0; k < char_num; k++)
	{
		if (input[k] == '/')module_init = k + 1;
		else if (input[k] == '.')name_init = k + 1;
		else if (input[k] == '\0' || input[k] == '=')name_end = k;
	}
	//Copy the name in a new string
	uint j = 0;
	for (uint pos = name_init; pos < name_end; pos++)
	{
		cvar_name[j] = input[pos];
		j++;
	}
	//Copy the module name in a new string
	j = 0;
	for (uint k = module_init; k < name_init - 1; k++)
	{
		module_name[j] = input[k];
		j++;
	}
	//Search the Cvar with the name build
	uint cvar_num = console_variables.Count();
	for (uint k = 0; k < cvar_num; k++)
	{
		if (console_variables[k]->GetCvarName() == cvar_name && console_variables[k]->GetCvarModule()->name.GetString() == module_name)return console_variables[k];
	}
	return nullptr;
}

char * j1Console::GetValuefromInput(char * input) const
{
	char* value = nullptr;
	uint init = 0;
	uint val_pos = 0;
	uint char_num = strlen(input);
	for (uint k = 0; k < char_num; k++)
	{
		if (input[k] == '=')init = k;
		if (k > init && init != 0)
		{
			value[val_pos] = input[k];
			val_pos++;
			if (input[k] == '\0')return value;
		}
	}
	return nullptr;
}

char * j1Console::GetInputType(char * input)
{
	char* command_type = new char[4];

	uint char_num = strlen(input);
	for (uint k = 0; k < char_num; k++)
	{
		if (input[k] == '/')
		{
			command_type[k] = '\0';
			break;
		}
		command_type[k] = input[k];

	}
	return command_type;
}

char * j1Console::CvarTypetoString(C_VAR_TYPE cvar_type) const
{
	switch (cvar_type)
	{
	case INT_VAR:		return "integrer";	break;
	case FLOAT_VAR:		return "float";		break;
	case CHAR_VAR:		return "character";	break;
	case BOOLEAN_VAR:	return "boolean";	break;
	case UNDEF:			return "undefined";	break;
	}
}

C_VAR_TYPE j1Console::StringtoCvarType(const char* string) const
{
	if			(string == "integrer")return INT_VAR;
	else if		(string == "float")	return FLOAT_VAR;
	else if		(string == "character")return CHAR_VAR;
	else if		(string == "boolean")
	{
		return BOOLEAN_VAR;
	}
	else return UNDEF;
}

void j1Console::Console_Input(Cvar * cvar, char * input)
{
	// TODO: update app state with cvars input
}
