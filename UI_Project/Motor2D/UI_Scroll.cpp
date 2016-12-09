#include "UI_Scroll.h"
#include "j1App.h"
#include "j1Render.h"
#include "UI_IMG.h"
#include "UI_String.h"
#include "j1Input.h"

//Constructors ============================================
UI_Scroll::UI_Scroll(const SDL_Rect& box, const SDL_Rect& ContentWindow, const UI_IMG& ScrollItem, const UI_IMG& ScrollBack, UI_Element* Content) :UI_Element(box, SCROLL), ContentWindow(ContentWindow), ScrollItem(ScrollItem), ScrollBack(ScrollBack), Content(Content)
{
	this->ScrollItem.SetParent(this);
	this->ScrollBack.SetParent(this);
	this->Content->SetParent(this);
}

UI_Scroll::UI_Scroll(const UI_Scroll* copy) : UI_Element(copy->box, SCROLL), ContentWindow(copy->ContentWindow), ScrollItem(copy->ScrollItem), ScrollBack(copy->ScrollBack), Content(copy->Content) {}


//Destructors =============================================
UI_Scroll::~UI_Scroll()
{

}


//Game Loop ===============================================
void UI_Scroll::Draw(bool debug) const
{
	if (debug)App->render->DrawQuad({ box.x, box.y, box.w, box.h }, 150, 150, 0);

	//Draw the element check the type
	switch (Content->ui_type) {
		
	case UI_TYPE::IMG:		((UI_IMG*)Content)->Draw(false);		break;
	case UI_TYPE::STRING:	((UI_String*)Content)->Draw(false);		break;
		
	}

	//Draw the scroll img
	ScrollBack.Draw(false);
	ScrollItem.Draw(false);

}



// Functionality =========================================
bool UI_Scroll::MoveScroll(int mouse_x_motion, int mouse_y_motion)
{
	//Get mouse left button state
	j1KeyState mouse_button_1 = App->input->GetMouseButtonDown(1);

	if (ScrollItem.MouseIsIn() && mouse_button_1 == KEY_REPEAT)
	{
		Content->MoveBox(mouse_x_motion, mouse_y_motion);
		ScrollItem.MoveBox(mouse_x_motion, mouse_y_motion);
		ScrollBack.
		return true;
	}

	return false;
}

void UI_Scroll::MoveBox(int x_vel, int y_vel)
{
	box.x += x_vel;
	box.y += y_vel;
	ScrollItem.MoveBox(x_vel, y_vel);
	ScrollBack.MoveBox(x_vel, y_vel);
	Content->MoveBox(x_vel, y_vel);
}
