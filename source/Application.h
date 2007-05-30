#ifndef __APPLICATION_H__
#define __APPLICATION_H__

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

#include <be/support/Debug.h>

#include <be/app/Application.h>
#include <be/app/Message.h>
#include <be/storage/Directory.h>
#include <be/storage/Entry.h>
#include <be/storage/File.h>
#include <be/storage/FindDirectory.h>
#include <be/storage/Path.h>

#define SIGNATURE "application/x-vnd.flipsidesoftware.rename"

class Application : public BApplication
{
	public:
		Application();
		virtual void ArgvReceived(int32 argc, char** argv);
		virtual void RefsReceived(BMessage* message);
	private:
		BWindow* window;
};

#endif
