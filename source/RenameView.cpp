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

#include "AppWindow.h"
#include "FileName.h"
#include "RenameView.h"

RenameView::RenameView(BRect rect) :
	BView(rect,"renameView", B_FOLLOW_ALL, B_NAVIGABLE_JUMP)
{
	PRINT(("RenameView::RenameView(BRect)\n"));

	SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));

	BRect frame;
	font_height fh;
	GetFontHeight(&fh);
	float height = fh.ascent + fh.descent + fh.leading;
	float width = 0.0;
	float space = 15.0;

	//Create CheckBoxes
	width = StringWidth("Change Basename") + 25;
	frame.Set(0,0,width,height);
	basenameCheckBox = new BCheckBox(frame,"basenameCheckBox","Change Basename",
			new BMessage(BASENAME_CBOX_MSG));

	width = StringWidth("Change Extension") + 25;
	frame.Set(0,0,width,height);
	extensionCheckBox = new BCheckBox(frame,"extensionCheckBox",
			"Change Extension",new BMessage(EXTENSION_CBOX_MSG));

	width = StringWidth("Change Case") + 25;
	frame.Set(0,0,width,height);
	caseCheckBox = new BCheckBox(frame,"caseCheckBox","Change Case",
			new BMessage(CASE_CBOX_MSG));

	width = StringWidth("Search & Replace") + 25;
	frame.Set(0,0,width,height);
	searchReplaceCheckBox = new BCheckBox(frame,"searchReplaceCheckBox",
			"Search & Replace",new BMessage(SEARCH_REPLACE_CBOX_MSG));

	//Create Boxes
	frame = Bounds();
	frame.InsetBy(space,space);
	frame.bottom = frame.top + (2*space) + (2*height);
	basenameBox = new BBox(frame,"basenameBox",B_FOLLOW_LEFT_RIGHT|B_FOLLOW_TOP);
	basenameBox->SetLabel(basenameCheckBox);
	AddChild(basenameBox);

	frame.OffsetBy(0,frame.Height()+space);
	extensionBox = new BBox(frame,"extensionBox",
			B_FOLLOW_LEFT_RIGHT|B_FOLLOW_TOP);
	extensionBox->SetLabel(extensionCheckBox);
	AddChild(extensionBox);

	frame.OffsetBy(0,frame.Height()+space);
	caseBox = new BBox(frame,"caseBox",B_FOLLOW_LEFT_RIGHT|B_FOLLOW_TOP);
	caseBox->SetLabel(caseCheckBox);
	AddChild(caseBox);

	frame.OffsetBy(0,frame.Height()+space);
	frame.bottom += height + space;
	searchReplaceBox = new BBox(frame,"searchReplaceBox",
			B_FOLLOW_LEFT_RIGHT|B_FOLLOW_TOP);
	searchReplaceBox->SetLabel(searchReplaceCheckBox);
	AddChild(searchReplaceBox);

	//Create Controls
	frame = basenameBox->Bounds();
	frame.InsetBy(space,space);
	frame.OffsetBy(0,space/2);
	width = basenameBox->StringWidth("Basename:");
	basenameTextControl = new BTextControl(frame,"basenameTextControl",
			"Basename:","",NULL,B_FOLLOW_LEFT_RIGHT|B_FOLLOW_TOP);
	basenameTextControl->SetDivider(width);
	basenameBox->AddChild(basenameTextControl);
	
	frame = extensionBox->Bounds();
	frame.InsetBy(space,space);
	frame.OffsetBy(0,space/2);
	width = extensionBox->StringWidth("Extension:");
	extensionTextControl = new BTextControl(frame,"extensionTextControl",
			"Extension:","",NULL,B_FOLLOW_LEFT_RIGHT|B_FOLLOW_TOP);
	extensionTextControl->SetDivider(width);
	extensionBox->AddChild(extensionTextControl);
	
	frame = caseBox->Bounds();
	frame.InsetBy(space,space);
	frame.OffsetBy(0,space/2);
	width = caseBox->StringWidth("UPPER") + 18;
	frame.right = frame.left + width;
	upperRadioButton = new BRadioButton(frame,"upperRadioButton","UPPER",NULL,
			B_FOLLOW_LEFT|B_FOLLOW_TOP);
	caseBox->AddChild(upperRadioButton);

	frame.OffsetBy(frame.Width()+7,0);
	width = caseBox->StringWidth("lower") + 18;
	frame.right = frame.left + width;
	lowerRadioButton = new BRadioButton(frame,"lowerRadioButton","lower",NULL,
			B_FOLLOW_H_CENTER|B_FOLLOW_TOP);
	caseBox->AddChild(lowerRadioButton);

	frame.OffsetBy(frame.Width()+7,0);
	width = caseBox->StringWidth("Capitalize Each Word") + 18;
	frame.right = frame.left + width;
	capEachWordRadioButton = new BRadioButton(frame,"capEachWordRadioButton",
			"Capitalize Each Word",NULL,B_FOLLOW_RIGHT|B_FOLLOW_TOP);
	caseBox->AddChild(capEachWordRadioButton);

	frame = searchReplaceBox->Bounds();
	frame.InsetBy(space,space);
	frame.OffsetBy(0,space/2);
	frame.bottom = frame.top + height;
	width = searchReplaceBox->StringWidth("Replace:");
	searchTextControl = new BTextControl(frame,"searchTextControl",
			"Search:","",NULL,B_FOLLOW_LEFT_RIGHT|B_FOLLOW_TOP);
	searchTextControl->SetDivider(width);
	searchReplaceBox->AddChild(searchTextControl);
	
	frame.OffsetBy(0,frame.Height()+space);
	frame.bottom = frame.top + height;
	width = searchReplaceBox->StringWidth("Replace:");
	replaceTextControl = new BTextControl(frame,"replaceTextControl",
			"Replace:","",NULL,B_FOLLOW_LEFT_RIGHT|B_FOLLOW_TOP);
	replaceTextControl->SetDivider(width);
	searchReplaceBox->AddChild(replaceTextControl);

	//Create Buttons
	frame = Bounds();
	frame.InsetBy(space,space);
	frame.left = frame.right - 75;
	frame.top = frame.bottom - 30;
	renameButton = new BButton(frame,"renameButton","ReName!",
			new BMessage(RENAME_MSG), B_FOLLOW_RIGHT|B_FOLLOW_BOTTOM);
	AddChild(renameButton);

	frame.OffsetBy(-75-space, 0);
	cancelButton = new BButton(frame,"cancelButton","Cancel",
			new BMessage(CANCEL_MSG), B_FOLLOW_RIGHT|B_FOLLOW_BOTTOM);
	AddChild(cancelButton);

	frame = Bounds();
	frame.InsetBy(space,space);
	frame.right = (cancelButton->Frame()).left - space;
	frame.top = frame.bottom - 35;
	statusBar = new BStatusBar(frame,"statusBar");
	statusBar->SetResizingMode(B_FOLLOW_LEFT_RIGHT|B_FOLLOW_BOTTOM);
	statusBar->Hide();
	AddChild(statusBar);
}

void
RenameView::AttachedToWindow()
{
	PRINT(("RenameView::AttachedToWindow()\n"));

	basenameCheckBox->SetTarget(this);
	extensionCheckBox->SetTarget(this);
	caseCheckBox->SetTarget(this);
	searchReplaceCheckBox->SetTarget(this);
	renameButton->SetTarget(this);
	cancelButton->SetTarget(this);
	renameButton->MakeDefault(true);

	//Set Inital State of controls
	basenameCheckBox->SetValue(B_CONTROL_ON);
	extensionCheckBox->SetValue(B_CONTROL_ON);
	caseCheckBox->SetValue(B_CONTROL_OFF);
	upperRadioButton->SetValue(B_CONTROL_ON);
	upperRadioButton->SetEnabled(false);
	lowerRadioButton->SetEnabled(false);
	capEachWordRadioButton->SetEnabled(false);
	searchReplaceCheckBox->SetValue(B_CONTROL_OFF);
	searchTextControl->SetEnabled(false);
	replaceTextControl->SetEnabled(false);
}

void
RenameView::MessageReceived(BMessage* message)
{
	//PRINT(("RenameView::MessageReceived(BMessage*)\n"));

	switch(message->what)
	{
		case BASENAME_CBOX_MSG:
			BasenameAction();
			break;
		case EXTENSION_CBOX_MSG:
			ExtensionAction();
			break;
		case CASE_CBOX_MSG:
			CaseAction();
			break;
		case SEARCH_REPLACE_CBOX_MSG:
			SearchReplaceAction();
			break;
		case RENAME_MSG:
			RenameAction();
			break;
		case CANCEL_MSG:
			CancelAction();
			break;
	}
}

void
RenameView::BasenameAction()
{
	PRINT(("RenameView::BasenameAction()\n"));

	if(basenameCheckBox->Value() == B_CONTROL_ON)
	{
		basenameTextControl->SetEnabled(true);
	}
	else
	{
		basenameTextControl->SetEnabled(false);
	}
}

void
RenameView::ExtensionAction()
{
	PRINT(("RenameView::ExtensionAction()\n"));

	if(extensionCheckBox->Value() == B_CONTROL_ON)
	{
		extensionTextControl->SetEnabled(true);
	}
	else
	{
		extensionTextControl->SetEnabled(false);
	}
}

void
RenameView::CaseAction()
{
	PRINT(("RenameView::CaseAction()\n"));

	if(caseCheckBox->Value() == B_CONTROL_ON)
	{
		upperRadioButton->SetEnabled(true);
		lowerRadioButton->SetEnabled(true);
		capEachWordRadioButton->SetEnabled(true);
	}
	else
	{
		upperRadioButton->SetEnabled(false);
		lowerRadioButton->SetEnabled(false);
		capEachWordRadioButton->SetEnabled(false);
	}
}

void
RenameView::SearchReplaceAction()
{
	PRINT(("RenameView::SearchReplaceAction()\n"));

	if(searchReplaceCheckBox->Value() == B_CONTROL_ON)
	{
		searchTextControl->SetEnabled(true);
		replaceTextControl->SetEnabled(true);
	}
	else
	{
		searchTextControl->SetEnabled(false);
		replaceTextControl->SetEnabled(false);
	}
}

void
RenameView::RenameAction()
{
	PRINT(("RenameView::RenameAction()\n"));

	BList* refs = ((AppWindow*)Window())->GetRefs();
	int numRefs = refs->CountItems();
	statusBar->SetMaxValue(numRefs);
	statusBar->Show();
	for(int i=0;i<numRefs;i++)
	{
		entry_ref* ref = (entry_ref*)refs->ItemAt(i);
		FileName file(ref);

		if(basenameCheckBox->Value() == B_CONTROL_ON)
		{
			file.SetBasename(basenameTextControl->Text(),i+1,numRefs);
		}

		if(extensionCheckBox->Value() == B_CONTROL_ON)
		{
			file.SetExtension(extensionTextControl->Text());
		}

		if(caseCheckBox->Value() == B_CONTROL_ON)
		{
			if(upperRadioButton->Value() == B_CONTROL_ON)
			{
				file.ToUpper();
			}
			else if(lowerRadioButton->Value() == B_CONTROL_ON)
			{
				file.ToLower();
			}
			else if(capEachWordRadioButton->Value() == B_CONTROL_ON)
			{
				file.CapEachWord();
			}
		}

		if(searchReplaceCheckBox->Value() == B_CONTROL_ON)
		{
			file.Replace(searchTextControl->Text(),replaceTextControl->Text());
		}

		file.Rename();
		statusBar->Update(1,"0%","100%");
	}
	statusBar->Hide();

	Window()->PostMessage(B_QUIT_REQUESTED);
}

void
RenameView::CancelAction()
{
	PRINT(("RenameView::CancelAction()\n"));

	Window()->PostMessage(B_QUIT_REQUESTED);
}
