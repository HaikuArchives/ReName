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

#include "List.h"

List::List() : BList()
{
	PRINT(("List::List()\n"));
}

List::~List()
{
	PRINT(("List::~List()\n"));
	DeleteItemsInList();
}

time_t
List::GetLastUpdateTime()
{
	PRINT(("List::GetLastUpdateTime()\n"));
	return update_time;
}

void
List::Updated()
{
	PRINT(("List::Updated()\n"));
	update_time = time(NULL);
}

void
List::DeleteAll(void)
{
	PRINT(("List::DeleteAll()\n"));
	DeleteItemsInList();
	MakeEmpty();
}

bool
List::Lock()
{
	PRINT(("List::Lock()\n"));
	return lock.Lock();
}

void
List::Unlock()
{
	PRINT(("List::Unlock()\n"));
	lock.Unlock();
}

void
List::DeleteItemsInList()
{
	PRINT(("List::DeleteItemsInList()\n"));
	void* item;
	int32 num_items = CountItems();
	for(int i=0;i<num_items;i++)
	{
		item = ItemAt(i);
		delete item;
	}
}
