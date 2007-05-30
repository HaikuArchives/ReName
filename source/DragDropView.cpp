/*
 * This software has been donated to the BeOS community by FlipSide Software.
 * It is now been opened up under public domain.  You may do anything you want
 * with this software, but you must not hold FlipSide Software, it's owners, or
 * employees responsible for anything it does to you, your system, your
 * children, your friends or your car.  There is absolutely no guarantees
 * with this software, it is provided "as is".
 *
 * The icon remains property of Copland, used with permission.
 *
 */

#include "DragDropView.h"

DragDropView::DragDropView(BRect frame) : BView(frame,"DragDropView",
		B_FOLLOW_ALL,B_NAVIGABLE_JUMP)
{
	PRINT(("DragDropView::DragDropView(BRect)\n"));

	SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));

	BRect frame = Bounds();
	frame.InsetBy(10,10);
	dragDropBox = new BBox(frame,"dragDropBox",B_FOLLOW_ALL);
	dragDropBox->SetLabel(LABEL);
	AddChild(dragDropBox);
}
