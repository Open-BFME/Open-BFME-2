// cl: /MD
// ?Rva002B256EGet@@YAPAXXZ @0x002B256E 11B.
// Global-to-method tail jump: mov ecx,[0x00E02D6C]; jmp 0x003B8BAA.
// Evidence: retail 8B 0D 6C 2D E0 00 E9 ...; callee is rowed
// ?rva003B8BAA@LivingWorldCampaignManager@@QAEPAXXZ; callers at 0x0020EBD5 0x003F4FF5 0x0057443C
// 0x00574464 0x00574F2F use eax as vtable object. Tail return gives jmp at /O1.
class Rva00E02D6C; extern Rva00E02D6C *TheCampaignManager;

struct Rva003B8BAAElem
{
	char m_pad[0x20];
	void *m_ptr20;
};
#include "../../Include/Common/LivingWorldCampaignManager.h"
#define TheRva00E02D6C ((LivingWorldCampaignManager *)TheCampaignManager)

void *Rva002B256EGet(void)
{
	return TheRva00E02D6C->rva003B8BAA();
}

#include "../../Include/Common/Rva002B256E.h"

// ICF-folded twin of Rva002B256EGet above (same 11 bytes at 0x002B256E):
// the member spelling ignores its own receiver exactly like the free
// spelling ignores its absent one, so both compile to the same tail jump.
void *Rva002B256E::rva002B256E()
{
	return TheRva00E02D6C->rva003B8BAA();
}
