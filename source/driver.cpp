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

#include <iostream.h>
#include <be/add-ons/tracker/TrackerAddOn.h>
#include <be/app/Application.h>
#include <be/app/Message.h>
#include <be/interface/Window.h>
#include <be/storage/Entry.h>
#include <be/storage/File.h>
#include <be/storage/FindDirectory.h>
#include <be/storage/Path.h>
#include "AppDefs.h"
#include "Application.h"
#include "AppWindow.h"


void
process_refs(entry_ref dir_ref, BMessage* msg, void* reserved)
{
	PRINT(("process_refs(entry_ref,BMessage*,void*)\n"));
	BPath path;
	find_directory(B_USER_SETTINGS_DIRECTORY,&path);
	path.Append(APPLICATION_DIR);
	create_directory(path.Path(),0755);
	path.Append(WINDOW_FILE);

	AppWindow* window = 0;

	BFile settings(path.Path(), B_READ_ONLY);
	status_t status = settings.InitCheck();
	if(status == B_OK)
	{
		BMessage archive;
		if(archive.Unflatten(&settings) == B_OK)
		{
			window = new AppWindow(&archive,msg);
		}
	}

	if(!window)
	{
		window = new AppWindow(msg);
	}
	
	window->Show();

	thread_id thread = window->Thread();
	status_t win_status = B_OK;
	wait_for_thread(thread, &win_status);     
}

void
main()
{
	PRINT(("main()\n"));
	new Application();
	be_app->Run();
	delete be_app;
}
