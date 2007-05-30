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

Application::Application() : BApplication(SIGNATURE)
{
	PRINT(("Application::Application()\n"));
	BPath path;
	find_directory(B_USER_SETTINGS_DIRECTORY,&path);
	path.Append(APPLICATION_DIR);
	create_directory(path.Path(),0755);
	path.Append(WINDOW_FILE);

	window = 0;
	BFile settings(path.Path(), B_READ_ONLY);
	status_t status = settings.InitCheck();
	if(status == B_OK)
	{
		BMessage archive;
		if(archive.Unflatten(&settings) == B_OK)
		{
			window = new AppWindow(&archive,NULL);
		}
	}

	if(!window)
	{
		window = new AppWindow(NULL);
	}

	window->Show();
}

void
Application::ArgvReceived(int32 argc, char** argv)
{
	PRINT(("Application::ArgvReceived()\n"));
}

void
Application::RefsReceived(BMessage* message)
{
	PRINT(("Application::RefsReceived()\n"));
	if(window->Lock())
	{
		((AppWindow*)window)->SetRefs(message);
		window->Unlock();
	}
}
