#ifndef __FILENAME_H__
#define __FILENAME_H__

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

#include <be/storage/Entry.h>
#include <be/support/String.h>

class FileName
{
	public:
		FileName(entry_ref* p_ref);
		void SetBasename(const char* p_basename, int p_index, int p_total);
		void SetExtension(const char* p_extension);
		void ToUpper();
		void ToLower();
		void CapEachWord();
		void Replace(const char* oldStr, const char* newStr);
		void Rename();
		const char* Value() const;
	private:
		void SetValue();
		entry_ref* ref;
		BString basename;
		BString extension;
		BString value;
};

#endif
