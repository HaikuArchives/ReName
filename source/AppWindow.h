#ifndef __APP_WINDOW_H__
#define __APP_WINDOW_H__

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

#include <be/app/Message.h>
#include <be/interface/Alert.h>
#include <be/interface/Menu.h>
#include <be/interface/MenuBar.h>
#include <be/interface/MenuItem.h>
#include <be/interface/Point.h>
#include <be/interface/View.h>
#include <be/interface/Window.h>
#include <be/storage/Entry.h>
#include <be/storage/File.h>
#include <be/storage/FindDirectory.h>
#include <be/storage/NodeInfo.h>
#include <be/storage/Path.h>
#include <be/support/ClassInfo.h>
#include <be/support/String.h>
#include "DragDropView.h"
#include "List.h"
#include "RenameView.h"

#define WIN_TITLE "ReName!"
#define WIN_LEFT 300
#define WIN_TOP 200
#define WIN_RIGHT 610
#define WIN_BOTTOM 575
#define WIN_MIN_WIDTH 310
#define WIN_MAX_WIDTH 2000
#define WIN_MIN_HEIGHT 375
#define WIN_MAX_HEIGHT 375

class AppWindow : public BWindow
{
	public:
		AppWindow(BMessage* refs_msg);
		AppWindow(BMessage* message, BMessage* refs_msg);
		~AppWindow();
		void SetRefs(BMessage* refs_msg);
		List* GetRefs();
		virtual void MessageReceived(BMessage* message);
		virtual bool QuitRequested();
	private:
		void AddRefs(BMessage* refs_msg);
		void InitWindow();
		void DisplayView();
		void DragDropAction(BMessage* message);
		List* refs;
		DragDropView* dragDropView;
		RenameView* renameView;
};

#endif
