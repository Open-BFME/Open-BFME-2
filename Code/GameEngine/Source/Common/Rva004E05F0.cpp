// cl: /O1 /arch:SSE /G7 /MD
// ?rva004E05F0@Rva004E05F0@@QAEPAVCreateAHeroData@@XZ @0x004E05F0 21B
// evidence: callee pin ?rva003F083A@Rva003F1093@@QAEPAVCreateAHeroData@@PAX@Z; callers at 0x005CE13E 0x005CE61D 0x005CE698 0x005CF147; between Disp getters 0x004E05E9 and 0x004E0605

class CreateAHeroData;

#include "../../Include/Common/Rva003F1093.h"

#include "../../Include/Common/Rva004E05F0.h"

CreateAHeroData *Rva004E05F0::rva004E05F0()
{
	if (m_24 != 0)
		return m_24->rva003F083A(m_18);
	return 0;
}
