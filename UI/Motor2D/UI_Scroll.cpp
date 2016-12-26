#include "j1App.h"
#include "j1Render.h"
#include "j1Input.h"
#include "p2Log.h"
#include "UI_Scroll.h"


//Constructors ============================================
UI_Scroll::UI_Scroll(const SDL_Rect& box, const SDL_Rect& ContentWindow, const UI_Image& ScrollItem, const UI_Image& ScrollBack, SCROLL_TYPE Scroll_Type, uint MaxValue) :UI_Element(box, SCROLL), ContentWindow(ContentWindow), ScrollItem(ScrollItem), ScrollBack(ScrollBack), Scroll_Type(Scroll_Type), MaxValue(MaxValue) {}

UI_Scroll::UI_Scroll(const UI_Scroll* copy) : UI_Element(copy->box, SCROLL), ContentWindow(copy->ContentWindow), ScrollItem(copy->ScrollItem), ScrollBack(copy->ScrollBack), Scroll_Type(copy->Scroll_Type), MaxValue(copy->MaxValue) {}


//Destructors =============================================
UI_Scroll::~UI_Scroll()
{

}


//Game Loop ===============================================
void UI_Scroll::Draw(bool debug) const
{
	//Draw Scroll & Content View Area Qwad -
	if (debug)
	{
		App->render->DrawQuad({ box.x, box.y, box.w, box.h }, 150, 150, 0);
		App->render->DrawQuad({ ContentWindow.x + box.x,ContentWindow.y + box.y,ContentWindow.w,ContentWindow.h }, 0, 50, 0);
		App->render->DrawQuad({ box.x + ScrollBack.GetBox()->x,box.y + ScrollBack.GetBox()->y,ScrollBack.GetBox()->w, ScrollBack.GetBox()->h }, 90, 20, 0);
		App->render->DrawQuad({ box.x + ScrollItem.GetBox()->x,box.y + ScrollItem.GetBox()->y,ScrollItem.GetBox()->w, ScrollItem.GetBox()->h }, 90, 80, 110);
	}

	//Draw the scroll img ------------------
	ScrollBack.DrawAt(box.x,box.y);
	ScrollItem.DrawAt(box.x, box.y);
	
	//Draw scroll items --------------------
	SDL_Rect view_port = { ContentWindow.x + box.x, ContentWindow.y + box.y, ContentWindow.w,ContentWindow.h };
	SDL_RenderSetViewport(App->render->renderer,&view_port);
	p2List_item<UI_Element*>* item = Items.start;
	while (item) {
		
		item->data->Draw(debug);

		item = item->next;
	}
	SDL_RenderSetViewport(App->render->renderer,NULL);
	
	//Draw Scroll Childs -------------------
	DrawChilds(debug);
}

bool UI_Scroll::Update()
{
	HandleInput();

	if (ScrollLastLocation == ScrollLocation)return true;

	//Calculate the distance that the items have to move
	double y_desp = 0;
	double x_desp = 0;

	switch (Scroll_Type)
	{
	case SCROLL_TYPE::VERTICAL:			y_desp = -((float)ScrollLocation - (float)ScrollLastLocation) * ((float)ContentLenght / (float)ScrollBack.GetBox()->h);	break;
	case SCROLL_TYPE::VERTICAL_INV:		y_desp = ((float)ScrollLocation - (float)ScrollLastLocation) * ((float)ContentLenght / (float)ScrollBack.GetBox()->h);	break;
	}


	//Round the distance (because we are moving in pixels)
	y_desp = (y_desp - floor(y_desp) > 0.4) ? ceil(y_desp) : floor(y_desp);
	x_desp = (x_desp - floor(x_desp) > 0.4) ? ceil(x_desp) : floor(x_desp);

	//Move the items 
	p2List_item<UI_Element*>*  item = Items.start;

	while (item) {

		item->data->MoveBox(x_desp, y_desp);
		item = item->next;

	}
	
	//Update the ScrollLastLocation used for calculate the motion
	ScrollLastLocation = ScrollLocation;

	return true;
}


// Functionality =========================================
bool UI_Scroll::MoveScroll(int mouse_x_motion, int mouse_y_motion)
{
	//Select the Scroll Item ----------
	if (ScrollItem.MouseIsIn(box.x,box.y) || ScrollSelected)
	{
		ScrollSelected = true;
	}

	//Drag the Scroll Item ------------
	if (ScrollSelected)
	{
		if (ScrollItem.RectIsIn(ScrollBack.GetBox(), mouse_x_motion, mouse_y_motion)  == false)
		{
			//Put the Scroll Item at the limit 
			if (mouse_y_motion < 0)
			{
				mouse_y_motion = ScrollBack.GetBox()->y - ScrollItem.GetBox()->y;
			}
			else if (mouse_y_motion > 0)
			{
				mouse_y_motion = ScrollBack.GetBox()->y + ScrollBack.GetBox()->h - (ScrollItem.GetBox()->h + ScrollItem.GetBox()->y);
			}
		}
		ScrollItem.MoveBox(0, mouse_y_motion);
		ScrollLocation += mouse_y_motion;
		Value += (((float)mouse_y_motion / (float)ContentLenght)* (float)MaxValue);
	}

	return ScrollSelected;
}

void UI_Scroll::UnselectScroll()
{
	ScrollSelected = false;
}

void UI_Scroll::AddScrollItem(UI_Element* new_item)
{
	//Calculate the size for the scroll
	int lenght = 0;
	if(Scroll_Type == VERTICAL || Scroll_Type == VERTICAL_INV)
	{
		//Vertical Scroll Case
		lenght = new_item->GetBox()->y + new_item->GetBox()->h - ContentWindow.y;
		if (lenght > 0 && lenght > ContentLenght)ContentLenght = lenght;
	}
		//Lateral Scroll Case
	else
	{
		lenght = new_item->GetBox()->x - (ContentWindow.w - ContentWindow.x) + new_item->GetBox()->w;
		if (lenght > 0 && lenght > ContentLenght)ContentLenght = lenght;

	}
	//Set item layer
	new_item->SetLayer(this->layer + 1);

	//Add the new item to the list of items
	this->Items.add(new_item);
}

