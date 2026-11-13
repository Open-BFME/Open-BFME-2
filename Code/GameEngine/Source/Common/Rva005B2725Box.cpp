// cl: -O1 -GR- -EHsc- -Ireference/shims/bfme2_ascii
// ?Run@Rva005B2725@@QAEXH@Z @0x005B2725 104B: m_4 414/418 gate plus hero prep.
// If m_4 +0x414 equals +0x418, run rowed 0x5B5C02 on +0x418 and return; else
// fetch via TheHeroManager List (pinned 0x21F797), build 7-arg init via
// pinned 0x219251 (-1, 0xFF707070, -1, 0xE0C898, 0,0,0), consume m_4+0x27C
// via rowed 0x409359 Use, then run rowed 0x423A68. Fresh m_4 reloads; list
// in ebx, built in edi per retail.
#include "../../Include/Common/Rva005B5C02Box.h"

#include "../../Include/Common/Rva005B5C02List.h"

// The list getter 0x0021F797 is the rowed CreateAHeroManager::rva0021F797.
class Rva0040A3F9;
#include "../../Include/GameLogic/CreateAHeroManager.h"
extern CreateAHeroManager *TheCreateAHeroManager;
#define TheHeroManager TheCreateAHeroManager
#include "unicode_string.h"
// 0x00409359 consumes the source record as CreateAHeroData's rowed assignment.
#include "../../Include/GameLogic/CreateAHeroData.h"

#include "../../Include/Common/Rva00219251.h"


#include "../../Include/Common/Rva00423A68.h"

class ModuleData;

struct Rva005B2725
{
	char pad[4];
	void *m_4;

	void Run(int unused);
};

void Rva005B2725::Run(int unused)
{
	(void)unused;
	void *box = *(void **)((char *)m_4 + 0x418);
	if (*(int *)((char *)m_4 + 0x414) == (int)box) {
		((Rva005B5C02Box *)box)->Run();
		return;
	}
	Rva005B5C02List *list = (Rva005B5C02List *)TheHeroManager->rva0021F797();
	CreateAHeroData *built = ((Rva00219251 *)TheHeroManager)->rva00219251(0, 0, 0, UnicodeString::TheEmptyString, -1, (int)0xFF707070, -1);
	*built = *(const CreateAHeroData *)((char *)m_4 + 0x27C);
	((Rva00423A68 *)list)->rva00423A68((const class ModuleData *)built);
}
