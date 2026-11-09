// cl: /DNDEBUG /MD
//
// ?rva003FD02E@Rva003FC428@@UAEHPAD@Z @0x003FD02E 40B:
// vtable slot 2 of table at 0x00837C20; two-call narrow concat write via
// rowed ?write@AsciiStringPlusText@@QAEHPAD@Z @0x000BBD41 and
// ?write@AsciiStringRef@@QAEHPAD@Z @0x0002C5B1; member pointer at [ecx+4]
// holds PlusText at +0 and Ref at +0xC (Rva0020F58E shape); ret 4 one char*
// arg returning total bytes.

class AsciiString;

#include "../../Include/Common/AsciiStringRef.h"

#include "../../Include/Common/Rva000B3F84Pair.h"

#include "../../Include/Common/AsciiStringPlusText.h"

struct Rva003FD02ETarget
{
	AsciiStringPlusText m_first;
	AsciiStringRef m_second;
};

// Slot 2 of Rva003FC428's table (constructor in RvaSmallVtableCtors.cpp;
// slots 0 and 1 are in VslotMemberForwarders.cpp).
class Rva003FC428
{
public:
	virtual void rva003FCE30();
	virtual void rva003FD056(int firstValue, int secondValue, int thirdValue);
	virtual int rva003FD02E(char *dst);

private:
	Rva003FD02ETarget *m_member;
};

// vtable 0x00837C20#2
int Rva003FC428::rva003FD02E(char *dst)
{
	Rva003FD02ETarget *target = m_member;
	int n = target->m_first.write(dst);
	return n + target->m_second.write(dst + n);
}
