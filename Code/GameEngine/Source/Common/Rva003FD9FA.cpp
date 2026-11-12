// cl: /DNDEBUG /MD
// ?rva003FD9FA@Rva003FD9FA@@QAEXPBVRvaSmartPtr12@@UVec3@@@Z @0x003FD9FA 31B:
// Native21173C passes three float components as one copied12B vector.
// Chain from 0x003FC7C7: calls rowed rva003FC7C7 with first arg then copies 12B stack args to +0xAC.
// Evidence: callee row Rva003FC7FCClear.cpp, ret 0x10, copy 3x movsd.
#include "../../Include/Common/RvaSmartPtr12.h"

class Rva003FC7FC
{
public:
	void rva003FC7C7(const RvaSmartPtr12 &src);
private:
	unsigned char m_pad[0x1C];
	void *m_h0;
	void *m_h1;
	void *m_h2;
	int m_id;
};

#include "../../Include/Common/Vec3.h"

class Rva003FD9FA : public Rva003FC7FC
{
public:
	void rva003FD9FA(const RvaSmartPtr12 *p, Vec3 position);
private:
	char m_pad2[0xAC - 0x2C];
	Vec3 m_holder;
};

void Rva003FD9FA::rva003FD9FA(const RvaSmartPtr12 *p, Vec3 position)
{
	rva003FC7C7(*p);
	m_holder = position;
}
