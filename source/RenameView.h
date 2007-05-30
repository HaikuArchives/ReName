#ifndef __RENAME_VIEW_H__
#define __RENAME_VIEW_H__

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
#include <be/interface/Box.h>
#include <be/interface/Button.h>
#include <be/interface/CheckBox.h>
#include <be/interface/RadioButton.h>
#include <be/interface/Rect.h>
#include <be/interface/StatusBar.h>
#include <be/interface/TextControl.h>
#include <be/interface/View.h>
#include <be/interface/Window.h>

#define BASENAME_CBOX_MSG       '001'
#define EXTENSION_CBOX_MSG      '002'
#define CASE_CBOX_MSG           '003'
#define SEARCH_REPLACE_CBOX_MSG '004'

#define RENAME_MSG '005'
#define CANCEL_MSG '006'

class RenameView : public BView
{
	public:
		RenameView(BRect rect);
		virtual void AttachedToWindow();
		virtual void MessageReceived(BMessage* message);
	private:
		void BasenameAction();
		void ExtensionAction();
		void CaseAction();
		void SearchReplaceAction();
		void RenameAction();
		void CancelAction();
		BCheckBox* basenameCheckBox;
		BCheckBox* extensionCheckBox;
		BCheckBox* caseCheckBox;
		BCheckBox* searchReplaceCheckBox;
		BBox* basenameBox;
		BBox* extensionBox;
		BBox* caseBox;
		BBox* searchReplaceBox;
		BTextControl* basenameTextControl;
		BTextControl* extensionTextControl;
		BTextControl* searchTextControl;
		BTextControl* replaceTextControl;
		BRadioButton* upperRadioButton;
		BRadioButton* lowerRadioButton;
		BRadioButton* capEachWordRadioButton;
		BButton* renameButton;
		BButton* cancelButton;
		BStatusBar* statusBar;
};

#endif
