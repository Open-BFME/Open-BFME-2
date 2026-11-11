// cl: -O1 -GR- -EHsc-
// platformsdk
// ?Run@Rva005A0D61@@QAEXH@Z @0x005A0D61 97B: flag-gated refresh with time.
// If the byte arg is nonzero goto tail; else if m_4AC is nonzero, snapshot
// timeGetTime, compare m_4AC+0x3E8 against it, and goto tail unless above;
// run the +0x450 sub-object check (rowed 0x580172), and unless it passes,
// run the GameSpyInfo slot-0xB8 virtual; if that is false return, else tail.
// Tail refreshes via pinned 0x5A061B, snapshots timeGetTime, stamps m_4AC.

#include <windows.h>
#include "../../Include/GameNetwork/Rva00580172.h"

#include "../../Include/GameNetwork/GameSpyInfoInterface.h"

extern GameSpyInfoInterface *TheGameSpyInfo;

class AptOnlineCustomMatch
{
public:
	char pad[0x450];
	Rva00580172 m_450;
	char pad2[0x4AC - 0x450 - 4];
	int m_4AC;

	void rva005A0D61(bool flag);
	void PopulateGamesListBox();	// rowed 0x005A061B
};

void AptOnlineCustomMatch::rva005A0D61(bool flag)
{
	if (flag)
		goto tail;
	{
		int *slot = &m_4AC;
		if (*slot != 0) {
			unsigned long t = timeGetTime();
			if ((unsigned long)(*slot + 0x3e8) <= t)
				goto tail;
			if (m_450.rva00580172())
				goto tail;
			if (!TheGameSpyInfo->hasStagingRoomListChanged())
				return;
		}
	}
tail:
	PopulateGamesListBox();
	{
		unsigned long t = timeGetTime();
		m_4AC = (int)t;
	}
}
