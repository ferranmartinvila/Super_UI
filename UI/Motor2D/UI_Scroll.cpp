#include "j1App.h"
#include "j1Render.h"
#include "j1Input.h"
#include "p2Log.h"
#include "UI_Scroll.h"


//Constructors ============================================
UI_Scroll::UI_Scroll(const SDL_Rect& box, const SDL_Rect& ContentWindow, const UI_Image& ScrollItem, const UI_Image& ScrollBack, SCROLL_TYPE Scroll_Type, int MaxValue) :UI_Element(box, SCROLL), ContentWindow(ContentWindow), ScrollItem(ScrollItem), ScrollBack(ScrollBack), Scroll_Type(Scroll_Type), MaxValue(MaxValue) {}

UI_Scroll::UI_Scroll(const UI_Scroll* copy) : UI_Element(copy->box, SCROLL), ContentWindow(copy->ContentWindow), ScrollItem(copy->ScrollItem), ScrollBack(copy->ScrollBack), Scroll_Type(copy->Scroll_Type), MaxValue(copy->MaxValue) {}


//Destructors =============================================
UI_Scroll::~UI_Scroll()
{

}

//Game Loop ===============================================
void UI_Scroll::Draw(bool debug)
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

// Functionality =========================================
int UI_Scroll::CalculateScrollDesp()
{
	float y_loc = -((ScrollItem.GetBox()->y - ScrollBack.GetBox()->y));
	if (y_loc == 0) return 0;
	float y_desp = (y_loc * ContentLenght) / (ScrollBack.GetBox()->h - ScrollItem.GetBox()->h);
	return y_desp = (y_desp - floor(y_desp) > 0.5) ? ceil(y_desp) : floor(y_desp);;
}

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
		//Move the scroll Item ---
		ScrollItem.MoveBox(0, mouse_y_motion);
		
		//Move the scroll items --
		int desp = CalculateScrollDesp();
		p2List_item<UI_Element*>* item = Items.start;
		p2List_item<iPoint>* item_location = Items_location.start;
		while (item_location)
		{
			item->data->SetBoxPosition(item_location->data.x, item_location->data.y + desp);
			item = item->next;
			item_location = item_location->next;
		}

		//Update the scroll pos --
		ScrollPosition += mouse_y_motion;
		
		//Update scroll value ----
		Value = ((ScrollItem.GetBox()->y - ScrollBack.GetBox()->y) * MaxValue) / (float)(ScrollBack.GetBox()->h - ScrollItem.GetBox()->h);

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
		lenght = (new_item->GetBox()->y + new_item->GetBox()->h + ContentWindow.y) - (ContentWindow.h + ContentWindow.y);
		if (lenght > 0 && lenght > ContentLenght)ContentLenght = lenght;
	}

	//Set item layer
	new_item->SetLayer(this->layer + 1);

	//Add the new item to the list of items
	this->Items.add(new_item);
	this->Items_location.add(iPoint(new_item->GetBox()->x, new_item->GetBox()->y));
}

void UI_Scroll::AddScrollItemAtBottom(UI_Element * new_item)
{
	//Locat item at the bottom of the scroll
	if(Items.end != nullptr)new_item->SetBoxPosition(0, Items_location.end->data.y + Items.end->data->GetBox()->h);
	else new_item->SetBoxPosition(0, 0);
	
	//Update the scroll length
	int lenght = (new_item->GetBox()->y + new_item->GetBox()->h + ContentWindow.y) - (ContentWindow.h + ContentWindow.y);
	if (lenght > 0 && lenght > ContentLenght)ContentLenght = lenght;
	
	//Set item layer
	new_item->SetLayer(this->layer + 1);

	//Add the new item to the list of items
	this->Items.add(new_item);
	this->Items_location.add(iPoint(new_item->GetBox()->x, new_item->GetBox()->y));
}

uint UI_Scroll::GetScrollItemsNum() const
{
	return uint(Items.count());
}

UI_Element * UI_Scroll::GetScrollItem(uint index)
{
	return this->Items.At(index)->data;
}

