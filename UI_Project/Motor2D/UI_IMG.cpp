#include "UI_IMG.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Gui.h"

//Constructors
UI_IMG::UI_IMG(const SDL_Rect& box, const SDL_Rect& texture_rect, int texture_id, int x_img, int y_img) : UI_Element(box, IMG), texture_rect(texture_rect), texture_id(texture_id), x_img(x_img), y_img(y_img) {}

UI_IMG::UI_IMG(const UI_IMG* copy) : UI_Element(copy->box, IMG), texture_rect(copy->texture_rect), texture_id(copy->texture_id), x_img(copy->x_img), y_img(copy->y_img) {}

UI_IMG::UI_IMG() : UI_Element({ 0,0,0,0 }, IMG), texture_rect({ 0,0,0,0 }), x_img(0), y_img(0) {}

//Destructors
UI_IMG::~UI_IMG()
{

}


// ==========================
void UI_IMG::Draw(bool debug)const
{
	//This Draw
	if(debug)App->render->DrawQuad({ box.x, box.y, box.w, box.h }, 150, 50, 0);

	//Draw from Atlas
	if (texture_id == -1)App->render->Blit(((SDL_Texture*)App->gui->GetAtlas()), box.x + x_img - App->render->camera.x, box.y + y_img - App->render->camera.y, &texture_rect);
	
	//Draw from other textures
	else {
		
		//Undefined draw size
		if (texture_rect.w == 0 || texture_rect.h == 0)App->render->Blit(App->gui->Get_UI_Texture(texture_id), box.x + x_img - App->render->camera.x, box.y + y_img - App->render->camera.y);
		//Defined draw size
		else App->render->Blit(App->gui->Get_UI_Texture(texture_id), box.x + x_img - App->render->camera.x, box.y + y_img - App->render->camera.y, &texture_rect);

	}

	//Childs Draw
	DrawChilds(debug);
}

SDL_Rect UI_IMG::AdjustBox()
{
	
	box.w = texture_rect.w;
	box.h = texture_rect.h;

	y_img = x_img = 0;

	if (box.w == 0 || box.h == 0) {
	
		int w, h;
		SDL_QueryTexture(App->gui->Get_UI_Texture(this->texture_id), NULL, NULL, &w, &h);

		box.w = w;
		box.h = h;
	}

	return box;
}

void UI_IMG::DrawAt(int x, int y) const
{
	x += this->box.x;
	y += this->box.y;

		//Draw from Atlas
		if (texture_id == -1)App->render->Blit(((SDL_Texture*)App->gui->GetAtlas()), x - App->render->camera.x, y - App->render->camera.y, &texture_rect);

		//Draw from other textures
		else {

			//Undefined draw size
			if (texture_rect.w == 0 || texture_rect.h == 0)App->render->Blit(App->gui->Get_UI_Texture(texture_id), x - App->render->camera.x, y - App->render->camera.y);
			//Defined draw size
			else App->render->Blit(App->gui->Get_UI_Texture(texture_id), x - App->render->camera.x, y - App->render->camera.y, &texture_rect);

		}
}

void UI_IMG::ChangeTextureRect(SDL_Rect new_rect)
{
	texture_rect = new_rect;
}
