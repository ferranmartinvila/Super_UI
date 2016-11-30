#include "UI_IMG.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Gui.h"

//Constructors
UI_IMG::UI_IMG(const iPoint& position, int texture_id, const SDL_Rect& texture_rect) : UI_Element(position, IMG), texture_rect(texture_rect), texture_id(texture_id) {}

UI_IMG::UI_IMG(const iPoint & position, const SDL_Rect & texture_rect): UI_Element(position,IMG), texture_rect(texture_rect), texture_id(-1){}

UI_IMG::UI_IMG(const UI_IMG* copy) : UI_Element(copy->position, IMG), texture_rect(copy->texture_rect), texture_id(copy->texture_id) {}

UI_IMG::UI_IMG() : UI_Element({ 0,0 }, IMG), texture_rect({ 0,0,0,0 }) {}

//Destructors
UI_IMG::~UI_IMG()
{

}


// ==========================
void UI_IMG::Draw()const
{
	//This Draw
	int x = this->position.x;
	int y = this->position.y;
	if (parent != nullptr) {
		x += parent->position.x;
		y += parent->position.y;
	}

	//Draw from Atlas
	if(texture_id == -1)App->render->Blit(((SDL_Texture*)App->gui->GetAtlas()),x - App->render->camera.x, y - App->render->camera.y, &texture_rect);
	
	//Draw from other textures
	else {
		//Undefined draw size
		if (texture_rect.w == 0 || texture_rect.h == 0)App->render->Blit(App->gui->Get_UI_Texture(texture_id), x - App->render->camera.x, y - App->render->camera.y);
		//Defined draw size
		else App->render->Blit(App->gui->Get_UI_Texture(texture_id), x - App->render->camera.x, y - App->render->camera.y, &texture_rect);

	}

	//Childs Draw
	DrawChilds();
}
