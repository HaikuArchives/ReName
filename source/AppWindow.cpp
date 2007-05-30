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

#include "AppDefs.h"
#include "Application.h"
#include "AppWindow.h"

AppWindow::AppWindow(BMessage* refs_msg) :
	BWindow(BRect(WIN_LEFT,WIN_TOP,WIN_RIGHT,WIN_BOTTOM),
	WIN_TITLE,B_TITLED_WINDOW,B_ASYNCHRONOUS_CONTROLS)
{
	PRINT(("AppWindow::AppWindow(BMessage*)\n"));

	refs = new List();

	InitWindow();
	SetRefs(refs_msg);
}

AppWindow::AppWindow(BMessage* message, BMessage* refs_msg) : BWindow(message)
{
	PRINT(("AppWindow::AppWindow(BMessage*,BMessage*)\n"));

	refs = new List();

	InitWindow();
	SetRefs(refs_msg);
}

AppWindow::~AppWindow()
{
	PRINT(("AppWindow::~AppWindow()\n"));

	delete refs;
}

void
AppWindow::InitWindow()
{
	PRINT(("AppWindow::InitWindow(BMessage*)\n"));

	SetTitle(WIN_TITLE);
	SetType(B_TITLED_WINDOW);
	SetFlags(B_ASYNCHRONOUS_CONTROLS|B_NOT_RESIZABLE|B_NOT_ZOOMABLE);
	SetSizeLimits(WIN_MIN_WIDTH,WIN_MAX_WIDTH,WIN_MIN_HEIGHT,WIN_MAX_HEIGHT);
	SetWorkspaces(B_CURRENT_WORKSPACE);

	dragDropView = new DragDropView(Bounds());
	dragDropView->Hide();
	AddChild(dragDropView);

	renameView = new RenameView(Bounds());
	renameView->Hide();
	AddChild(renameView);
}

void
AppWindow::SetRefs(BMessage* refs_msg)
{
	PRINT(("AppWindow::SetRefs(BMessage*)\n"));

	if(refs->Lock())
	{
		refs->DeleteAll();
		if(refs_msg)
		{
			AddRefs(refs_msg);
		}
		refs->Updated();
		refs->Unlock();
	}
	DisplayView();
}

void
AppWindow::AddRefs(BMessage* refs_msg)
{
	//PRINT(("AppWindow::AddRefs(BMessage*,bool*)\n"));

	entry_ref tmp_ref;
	int num_refs = 0;
	while(refs_msg->FindRef("refs",num_refs,&tmp_ref) == B_NO_ERROR)
	{
		BNode node(&tmp_ref);
		if(node.IsFile())
		{
			bool found = false;
			for(int i=0;i<refs->CountItems();i++)
			{
				entry_ref* ref = (entry_ref*)refs->ItemAt(i);
				if(*ref == tmp_ref)
				{
					found = true;
					break;
				}
			}
			if(!found)
			{
				refs->AddItem(new entry_ref(tmp_ref));
			}
		}
		else if(node.IsDirectory())
		{
			BDirectory dir(&tmp_ref);
			if(dir.InitCheck() == B_OK)
			{
				BMessage message(B_REFS_RECEIVED);
				entry_ref t_ref;
				while(dir.GetNextRef(&t_ref) != B_ENTRY_NOT_FOUND)
				{
					message.AddRef("refs",&t_ref);
				}
				AddRefs(&message);
			}
		}
		else if(node.IsSymLink())
		{
			BEntry entry(&tmp_ref,true);
			if((entry.InitCheck() == B_OK) && (entry.GetRef(&tmp_ref) == B_OK))
			{
				BMessage message;
				message.AddRef("refs",&tmp_ref);
				AddRefs(&message);
			}
		}
		num_refs++;
	}
}

void
AppWindow::DisplayView()
{
	PRINT(("AppWindow::DisplayView()\n"));

	if(Lock())
	{
		if(refs->CountItems() == 0)
		{
			if(dragDropView->IsHidden())
			{
				dragDropView->Show();
			}
			if(!renameView->IsHidden())
			{
				renameView->Hide();
			}
		}
		else
		{
			if(!dragDropView->IsHidden())
			{
				dragDropView->Hide();
			}
			if(renameView->IsHidden())
			{
				renameView->Show();
			}
		}
		Unlock();
	}
}

List*
AppWindow::GetRefs()
{
	PRINT(("AppWindow::GetRefs()\n"));

	return refs;
}

void
AppWindow::DragDropAction(BMessage* message)
{
	PRINT(("AppWindow::DragDropAction()\n"));

	SetRefs(message);
}

void
AppWindow::MessageReceived(BMessage* message)
{
	//PRINT(("AppWindow::MessageReceived(BMessage*)\n"));

	switch(message->what)
	{
		case B_SIMPLE_DATA:
			DragDropAction(message);
			break;
		default:
			BWindow::MessageReceived(message);
	}
}

bool
AppWindow::QuitRequested()
{
	PRINT(("AppWindow::QuitRequested()\n"));

	BPath path;
	find_directory(B_USER_SETTINGS_DIRECTORY,&path);
	path.Append(APPLICATION_DIR);
	path.Append(WINDOW_FILE);

	BMessage* archive = new BMessage();
	Archive(archive,false);
	BFile settings(path.Path(), B_READ_WRITE | B_CREATE_FILE | B_ERASE_FILE);
	if(settings.InitCheck() == B_OK)
	{
		archive->Flatten(&settings);
	}

	if(is_instance_of(be_app,Application))
	{
		be_app->PostMessage(B_QUIT_REQUESTED);
	}

	return true;
}
