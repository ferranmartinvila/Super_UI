#include "UI_Scroll.h"
#include "j1App.h"
#include "j1Render.h"
#include "UI_IMG.h"

//Constructors ============================================
UI_Scroll::UI_Scroll(const SDL_Rect& box, const SDL_Rect& ContentWindow, const UI_IMG& ScrollItem, const UI_IMG& ScrollBack,const UI_Element& Content) :UI_Element(box, SCROLL), ContentWindow(ContentWindow), ScrollItem(ScrollItem), ScrollBack(ScrollBack), Content(Content) {}

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
	((UI_IMG*)&Content)->Draw(false);
}


// Functionality =========================================
bool UI_Scroll::MoveScroll(int mouse_y_motion)
{
	return false;
}
