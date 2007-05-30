#ifndef __LIST_H__
#define __LIST_H__

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

#include <time.h>
#include <be/support/List.h>
#include <be/support/Locker.h>

class List : public BList
{
	public:
		List();
		virtual ~List();
		time_t GetLastUpdateTime();
		void Updated();
		void DeleteAll();
		bool Lock();
		void Unlock();
	private:
		BLocker lock;
		void DeleteItemsInList();
		time_t update_time;
};

#endif
