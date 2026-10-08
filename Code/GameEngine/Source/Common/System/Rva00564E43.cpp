// cl: /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/reference/shims/cdmanager /Ireference/open-bfme-1/reference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
#include "PreRTS.h"
// ?rva00564E43@Rva00564E43@@QAEXXZ @0x00564E43 125B: unlock loops 8B array at +8/+0xc setting local AsciiString from +4 then calling m_b0 rva002104C7 with 1. Evidence: calls rowed set releaseBuffer rva002104C7 EH_prolog; g_009FEF10; single caller call at 0x00566972; prev CDManager next GloItem.
class Rva002104C7
{
public:
	bool rva002104C7(void *a1, void *a2);
};
class Rva002BA8F1Logic
{
public:
	char m_pad[0xb0];
	Rva002104C7 *m_b0;
};

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
struct Rva00564E43Item
{
	int m_0;
	AsciiString m_4;
};
class Rva00564E43
{
public:
	char m_pad0[8];
	Rva00564E43Item *m_begin;
	Rva00564E43Item *m_end;
	void rva00564E43();
};
void Rva00564E43::rva00564E43()
{
	AsciiString tmp;
	if ((*(Rva002BA8F1Logic **)&TheLivingWorldLogic)->m_b0 == 0)
		return;
	for (unsigned i = 0; i < (unsigned)(((char *)m_end - (char *)m_begin) >> 3); ++i)
	{
		_ReadWriteBarrier();
		tmp.set(m_begin[i].m_4);
		Rva002104C7 *h = (*(Rva002BA8F1Logic **)&TheLivingWorldLogic)->m_b0;
		_ReadWriteBarrier();
		h->rva002104C7(&tmp, (void *)1);
	}
}
