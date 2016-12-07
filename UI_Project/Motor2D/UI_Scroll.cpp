#include "UI_Scroll.h"
#include "j1App.h"
#include "j1Render.h"

void UI_Scroll::Draw(bool debug) const
{
	if (debug)App->render->DrawQuad({ box.x, box.y, box.w, box.h }, 150, 50, 0);
}

bool UI_Scroll::MoveScroll(int mouse_y_motion)
{
	return false;
}
