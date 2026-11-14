// cl: -GR- -EHsc-
// ?Run@Rva005B692FBox@@QAEXXZ @0x005B692F 56B: conditional sub-object poke.
// Unless +0x8 is clear, runs the pinned 0-arg helper (free-function
// spelling: the site sets no ecx, entry ecx flows through untouched, same
// as the landed 0x5A671D counter); hands m_4 + 0x27C to the pinned manager
// method on the 0xDFE344 global, pokes the same adjusted sub-object with 1
// through the pinned setter, and stamps the byte +0x14. The repeated 0x27C
// rides edi. Targets from retail REL32/DIR32.
// Row spellings of the three callees.
class CreateAHeroData;
#include "../../Include/GameLogic/CreateAHeroManager.h"
#include "../../Include/Common/Rva005B034ADwordSlot.h"
#include "../../Include/Common/AptCreateAHero.h"
class AptCreateAHero::Manager { public: void PopulateHeroList(); };

extern CreateAHeroManager *TheCreateAHeroManager;

struct Rva005B692FBox
{
	char pad[4];
	void *m_4;
	int m_8;
	char pad2[0x14 - 0xc];
	unsigned char m_14;

	void Run();
};

void Rva005B692FBox::Run()
{
	if (m_8 != 0)
		((AptCreateAHero::Manager *)this)->PopulateHeroList();
	int off = 0x27c;
	TheCreateAHeroManager->rva0021A428(*(const CreateAHeroData *)((char *)m_4 + off));
	((Rva005B034ADwordSlot *)((char *)m_4 + off))->set(1);
	m_14 = 1;
}
