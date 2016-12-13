#include "j1App.h"
#include "j1Render.h"
#include "j1Input.h"
#include "j1Gui.h"

#include "UI_Scroll.h"
#include "UI_IMG.h"
#include "UI_String.h"
#include "UI_Button.h"
#include "UI_Text_Box.h"

//Constructors ============================================
UI_Scroll::UI_Scroll(const SDL_Rect& box, const SDL_Rect& ContentWindow, const UI_IMG& ScrollItem, const UI_IMG& ScrollBack, SCROLL_TYPE Scroll_Type) :UI_Element(box, SCROLL), ContentWindow(ContentWindow), ScrollItem(ScrollItem), ScrollBack(ScrollBack),Scroll_Type(Scroll_Type) {}

UI_Scroll::UI_Scroll(const UI_Scroll* copy) : UI_Element(copy->box, SCROLL), ContentWindow(copy->ContentWindow), ScrollItem(copy->ScrollItem), ScrollBack(copy->ScrollBack), Scroll_Type(copy->Scroll_Type) {}


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
		App->render->DrawQuad({ box.x + ScrollBack.box.x,box.y + ScrollBack.box.y,ScrollBack.box.w, ScrollBack.box.h }, 90, 20, 0);
		App->render->DrawQuad({ box.x + ScrollItem.box.x,box.y + ScrollItem.box.y,ScrollItem.box.w, ScrollItem.box.h }, 90, 20, 0);
	}

	//Draw the scroll img ------------------
	ScrollBack.DrawAt(box.x,box.y);
	ScrollItem.DrawAt(box.x, box.y);

	
	//Draw the items -----------------------
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
	//Calculate the distance that the items have to move
	double y_desp = 0;
	double x_desp = 0;

	switch (Scroll_Type)
	{
	case SCROLL_TYPE::VERTICAL:			y_desp = -((float)ScrollLocation - (float)ScrollLastLocation) * ((float)ContentLenght / (float)ScrollBack.box.h);	break;
	case SCROLL_TYPE::VERTICAL_INV:		y_desp = ((float)ScrollLocation - (float)ScrollLastLocation) * ((float)ContentLenght / (float)ScrollBack.box.h);	break;
	case SCROLL_TYPE::LATERAL:			x_desp = -((float)ScrollLocation - (float)ScrollLastLocation) * ((float)ContentLenght / (float)ScrollBack.box.w);	break;
	case SCROLL_TYPE::LATERAL_INV:		x_desp = ((float)ScrollLocation - (float)ScrollLastLocation) * ((float)ContentLenght / (float)ScrollBack.box.w);	break;
	}


	//Round the distance (because we are moving in pixels)
	y_desp = (y_desp - floor(y_desp) > 0.5) ? ceil(y_desp) : floor(y_desp);
	x_desp = (x_desp - floor(x_desp) > 0.5) ? ceil(x_desp) : floor(x_desp);

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

void UI_Scroll::HandleInput()
{
	//Handle the input of the items and mouse gary
}



// Functionality =========================================
bool UI_Scroll::MoveScroll(int mouse_x_motion, int mouse_y_motion)
{
	//Get mouse left button state
	j1KeyState mouse_button_1 = App->input->GetMouseButtonDown(1);

	//Select the Scroll Item ----------
	if (ScrollItem.MouseIsIn(box.x,box.y) && mouse_button_1 == KEY_DOWN && App->gui->upper_element == this->layer)
	{
		ScrollSelected = true;
		App->gui->ItemSelected = this;
	}
	
	//Unselect the Scroll Item --------
	else if (ScrollSelected && mouse_button_1 == KEY_UP)
	{
		ScrollSelected = false;
	}

	//Drag the Scroll Item ------------
	if (ScrollSelected)
	{
		if (ScrollItem.RectIsIn(&ScrollBack.box, mouse_x_motion, mouse_y_motion)  == false)
		{
			//Put the Scroll Item at the limit 
			if (mouse_y_motion < 0)
			{
				mouse_y_motion = ScrollBack.box.y - ScrollItem.box.y;
			}
			else if (mouse_y_motion > 0)
			{
				mouse_y_motion = ScrollBack.box.y + ScrollBack.box.h - (ScrollItem.box.h + ScrollItem.box.y);
			}
		}
		ScrollItem.MoveBox(0, mouse_y_motion);
		ScrollLocation += mouse_y_motion;
	}

	return ScrollSelected;
}

UI_Element* UI_Scroll::AddScrollItem(const UI_Element* new_item)
{
	//Pointer to new item
	UI_Element* item = nullptr;

	//Create the new item
	switch (new_item->ui_type)
	{
	case UI_TYPE::IMG:					item = new UI_IMG(((UI_IMG*)new_item));						break;
	case UI_TYPE::STRING:				item = new UI_String((UI_String*)new_item);					break;
	case UI_TYPE::BUTTON:				item = new UI_Button((UI_Button*)new_item);					break;
	case UI_TYPE::TEXT_BOX:				item = new UI_Text_Box((UI_Text_Box*)new_item);				break;
	case UI_TYPE::SCROLL:				item = new UI_Scroll((UI_Scroll*)new_item);					break;
	}

	//Calculate the size for the scroll
	int lenght = 0;
	if(Scroll_Type == VERTICAL || Scroll_Type == VERTICAL_INV)
	{
		//Vertical Scroll Case
		lenght = item->box.y - (ContentWindow.h - ContentWindow.y) + item->box.h;
		if (lenght > 0 && lenght > ContentLenght)ContentLenght = lenght;
	}
		//Lateral Scroll Case
	else
	{
		lenght = item->box.x - (ContentWindow.w - ContentWindow.x) + item->box.w;
		if (lenght > 0 && lenght > ContentLenght)ContentLenght = lenght;

	}
	//Set item layer
	item->layer = this->layer + 1;

	//Add the new item to the list of items
	this->Items.add(item);

	return item;
}

