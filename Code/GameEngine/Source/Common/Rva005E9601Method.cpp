// cl: /O1 /MD
// Range-34 dump lane: 36B plain method at 0x005E9601 (ret).
// Runs the pinned 0x005F977D helper; when the +0x10 byte is set and the
// pinned 0x005FA854 member check on +0xC passes, tail-jumps through vtable
// slot 8 (third virtual, never defined in this unit). All identities
// unproven (address-derived).
// LINK: the callees are rowed as Rva005FA854::rva005FA854 and Rva005F977D::rva005F977D.
struct Rva005E9601M0C
{
	int m_pad;
};

#include "../../Include/Common/Rva005FA854.h"

class Rva005F977D
{
public:
	void rva005F977D();
};

class Rva005E9601
{
public:
	virtual void v00();
	virtual void v01();
	virtual void vfunc();
	char m_pad04[8];
	Rva005E9601M0C m0c;
	char m_byte10;
	void rva005E9601();
};

void Rva005E9601::rva005E9601()
{
	((Rva005F977D *)this)->rva005F977D();
	if (m_byte10 == 0)
		return;
	if (!((Rva005FA854 *)&m0c)->rva005FA854())
		return;
	vfunc();
}
