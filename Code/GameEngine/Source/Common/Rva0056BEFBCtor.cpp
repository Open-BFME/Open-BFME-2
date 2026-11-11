// cl: /MD
// ??0Rva00402F28Item@@QAE@PAX@Z @0x0056BEFB 36B. Ctor via pinned 0x0056B7E4 init plus vtable 0x00C37898 and bytes 0,1,0 at +0x58..0x5A. Evidence: same pad 0x58 as Rva0056B63E sibling, vtable and 3-byte layout match Rva00402F28Item copy ctor 0x00402F28, caller 0x0056BFA6.
class AsciiString;

// The 0x0056B7E4 init is the rowed base ctor
// ??0Rva0056B7E4@@QAE@ABVAsciiString@@@Z (Rva0056B7E4Ctor.cpp).
#include "../../Include/Common/Rva0056B7E4.h"

extern "C" const void *const __identifier("??_7Rva003F9FE6@@6B@")[];

class Rva00402F28Item
{
public:
	Rva00402F28Item(void *arg);
private:
	char m_pad[0x58];
	unsigned char m_58;
	unsigned char m_59;
	unsigned char m_5A;
};

Rva00402F28Item::Rva00402F28Item(void *arg)
{
	((Rva0056B7E4 *)this)->Rva0056B7E4::Rva0056B7E4(*(const AsciiString *)arg);
	*(unsigned int *)this = (unsigned int)__identifier("??_7Rva003F9FE6@@6B@");
	m_58 = 0;
	m_59 = 1;
	m_5A = 0;
}
