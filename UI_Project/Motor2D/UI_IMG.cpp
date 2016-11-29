#include "UI_IMG.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Gui.h"

//Constructors
UI_IMG::UI_IMG(const iPoint & position, const SDL_Rect & texture_rect, int texture_id) : UI_Element(position, IMG), texture_rect(texture_rect), texture_id(texture_id) {}

UI_IMG::UI_IMG(const UI_IMG* copy) : UI_Element(copy->position, IMG), texture_rect(copy->texture_rect), texture_id(copy->texture_id) {}

UI_IMG::UI_IMG() : UI_Element({ 0,0 }, IMG), texture_rect({ 0,0,0,0 }) {}

//Destructors
UI_IMG::~UI_IMG()
{

}


// ==========================
void UI_IMG::Draw()const
{
	if(texture_id == -1)App->render->Blit(((SDL_Texture*)App->gui->GetAtlas()), position.x - App->render->camera.x, position.y - App->render->camera.y, &texture_rect);
	else App->render->Blit(App->gui->Get_UI_Texture(texture_id) , position.x - App->render->camera.x, position.y - App->render->camera.y, &texture_rect);
}
