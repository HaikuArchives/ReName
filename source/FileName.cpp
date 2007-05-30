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

#include <ctype.h>
#include <be/interface/Alert.h>
#include <be/support/Debug.h>
#include "FileName.h"

FileName::FileName(entry_ref* p_ref)
{
	PRINT(("FileName::FileName(entry_ref*)\n"));

	ref = p_ref;

	basename.SetTo("");
	extension.SetTo("");

	BString tmp(p_ref->name);
	int32 last = tmp.FindLast('.');
	if(last != B_ERROR)
	{
		int32 basenameLength = last;
		int32 extensionLength = tmp.CountChars() - last - 1;
		tmp.CopyInto(basename,0,basenameLength);
		tmp.CopyInto(extension,last+1,extensionLength);
	}
	else
	{
		basename = tmp;
	}
	SetValue();
}

void
FileName::SetBasename(const char* p_basename, int p_index, int p_total)
{
	PRINT(("FileName::SetBasename(const char*,int,int)\n"));

	BString tmp(p_basename);
	if((p_total > 1) && (tmp.FindFirst('*') == B_ERROR))
	{
		BString cur;
		BString tot;
		cur << (int32)p_index;
		tot << (int32)p_total;
		int numZeros = tot.CountChars() - cur.CountChars();
		for(int i=0;i<numZeros;i++)
		{
			tmp << (int32)0;
		}
		tmp << (int32)p_index;
	}
	else if(tmp.FindFirst('*') != B_ERROR)
	{
		tmp.ReplaceAll("*",basename.String());
	}
	basename = tmp;
	SetValue();
}

void
FileName::SetExtension(const char* p_extension)
{
	PRINT(("FileName::SetExtension(const char*)\n"));

	BString tmp(p_extension);
	tmp.RemoveFirst(".");
	extension = tmp;
	SetValue();
}

void
FileName::SetValue()
{
	PRINT(("FileName::SetValue()\n"));

	value.SetTo(basename);
	if(strcmp(extension.String(),"") != 0)
	{
		value << "." << extension;
	}
}

void
FileName::ToUpper()
{
	PRINT(("FileName::ToUpper()\n"));

	basename.ToUpper();
	extension.ToUpper();
	SetValue();
}

void
FileName::ToLower()
{
	PRINT(("FileName::ToLower()\n"));

	basename.ToLower();
	extension.ToLower();
	SetValue();
}

void
FileName::CapEachWord()
{
	PRINT(("FileName::CapEachWord()\n"));

	int len;
	int i;
	char* str;

	str = (char*)basename.String();
	if(str == NULL || (strcmp(str,"")==0))
	{
	}
	str = NULL;

	ToLower();
	len = basename.CountChars();
	str = basename.LockBuffer(0);
	str[0] = toupper(str[0]);
	for(int i=0;i<len;i++)
	{
		if((i+1 < len) &&
			((str[i] == ' ') || (str[i] == '(') || (str[i] == ')') ||
			 (str[i] == '_') || (str[i] == '[') || (str[i] == ']') ||
			 (str[i] == ',') || (str[i] == '<') || (str[i] == '>') ||
			 (str[i] == '&') || (str[i] == '{') || (str[i] == '}') ||
			 (str[i] == '-')))
		{
			str[i+1] = toupper(str[i+1]);
		}
		else if((i+2 < len) && (str[i] == 'M') && (str[i+1] == 'c'))
		{
			str[i+2] = toupper(str[i+2]);
		}
	}
	basename.UnlockBuffer();
	SetValue();
}

void
FileName::Replace(const char* oldStr, const char* newStr)
{
	PRINT(("FileName::Replace(const char*,const char*)\n"));

	basename.ReplaceAll(oldStr,newStr);
	extension.ReplaceAll(oldStr,newStr);
	SetValue();
}

void
FileName::Rename()
{
	PRINT(("FileName::Rename()\n"));

	if(strcmp(ref->name,Value()) != 0)
	{
		BEntry entry(ref);
		status_t status = entry.Rename(Value());
		if(status == B_FILE_EXISTS)
		{
			BAlert* alert;
			BString alertMsg;
			alertMsg << Value() << " already exists.";
			alert = new BAlert("ReName!",alertMsg.String(),"ReName Anyway!",
					"Don't Do It!",NULL,B_WIDTH_AS_USUAL,B_WARNING_ALERT);
			alert->SetShortcut(1,B_ESCAPE);
			int32 button = alert->Go();
			if(button == 0)
			{
				status = entry.Rename(Value(),true);
			}
		}
	}
}

const char*
FileName::Value() const
{
	PRINT(("FileName::Value()\n"));

	return value.String();
}
