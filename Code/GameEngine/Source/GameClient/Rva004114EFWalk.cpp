// cl: /DNDEBUG /MD /EHsc
// ?rva004114EF@Rva004114EF@@SAXXZ, retail 0x004114EF (52B).
// Eva-table walk over global at 0x00E02FE4 via pinned first 0x00427195 and
// rowed next 0x00411084, virtual-calling slot 0x14 on object at node+0x18
// when non-null. Same first/next shape as 0x00411523; per-node action is
// the virtual call. Owner unproven so honest-address class; static, as the
// body never reads ecx and its caller 0x002251E5 calls it with no this setup.

class Rva000411084
{
public:
	void *next();
	void *m_current;
	void *m_owner;
};

#include "../../Include/GameLogic/Rva000427195.h"

// Shared storage is defined by AptComponentWindowLookup.cpp.
extern unsigned int AptComponentWindowDataTableStorage[5];

struct Rva004114EFObj
{
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
};

struct Rva004114EFNode
{
	char m_pad[0x18];
	Rva004114EFObj *m_obj;
};

class Rva004114EF
{
public:
	static void rva004114EF();
};

void Rva004114EF::rva004114EF()
{
	Rva000411084 iter;
	reinterpret_cast<Rva000427195 *>(AptComponentWindowDataTableStorage)->first(&iter);
	while (iter.m_current != 0) {
		Rva004114EFObj *obj = ((Rva004114EFNode *)iter.m_current)->m_obj;
		if (obj != 0)
			obj->v5();
		iter.next();
	}
}
