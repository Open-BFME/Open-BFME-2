// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
// Target evidence at 0x00433DFE: Apt query callback over the Save/Load label
// and the Campaign/Skirmish/Replay/WOTR/WOTRMP mode bits. The surrounding
// save/load callbacks establish the screen and state field at +0x27C.
extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *, const char *);
extern "C" char *__cdecl _mbscpy(char *, const char *);
extern "C" char *__cdecl _mbscat(char *, const char *);

#include "../../../../../Include/GameClient/AptSaveLoad.h"

void AptSaveLoad::Externs(int query, char *value, bool set)
{
	if (!set)
	{
		value[0] = '0';
		value[1] = 0;
	}

	switch (query)
	{
	case 0:
		if (!set)
		{
			if (field294 == 3)
				_mbscpy(value, "Save");
			else if (field294 == 2)
				_mbscpy(value, "Load");
		}
		break;
	case 1:
		if (set)
			return;
		value[0] = set;
		if (field298Byte & 1)
			_mbscat(value, "Campaign");
		if (field298Byte & 2)
			_mbscat(value, "Skirmish");
		if (field298Byte & 4)
			_mbscat(value, "Replay");
		if (field298Byte & 8)
			_mbscat(value, "WOTRSP");
		if (field298Byte & 16)
			_mbscat(value, "WOTRMP");
		break;
	case 2:
		if (!set)
			return;
		if (_strcmpi(value, "Campaign") == 0)
			field2A0 = 1;
		else if (_strcmpi(value, "Skirmish") == 0)
			field2A0 = 2;
		else if (_strcmpi(value, "Replay") == 0)
			field2A0 = 4;
		else if (_strcmpi(value, "WOTRSP") == 0)
			field2A0 = 8;
		else if (_strcmpi(value, "WOTRMP") == 0)
			field2A0 = 16;
		if (field27C == 0)
			field27C = 2;
		break;
	}
}
