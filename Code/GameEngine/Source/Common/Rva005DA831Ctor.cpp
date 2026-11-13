// cl: /DNDEBUG /MD /EHsc
// ??0Rva005DA831@@QAE@PAX@Z @0x005DA831 35B evidence: base Rva005DAA36 holder void* rowed in V3PolyCopyCtors; derived vtable 0x00876518; or -1 at +0x08 and 3 at +0x0C; caller 0x00597227; cross-TU base call forces esi save

#include "../../Include/Common/Rva005DAA36.h"

class Rva005DA831 : public Rva005DAA36
{
public:
	Rva005DA831(void *held);
	virtual ~Rva005DA831();
private:
	int m_08;
	int m_0C;
};

Rva005DA831::Rva005DA831(void *held)
	: Rva005DAA36(held)
{
	m_08 = -1;
	m_0C = 3;
}

// vftable 0x00C76518 slot 1 is the deleting dtor 0x005DA663, whose dtor call is the 7-byte vptr-store body at 0x005970E6.
#pragma comment(linker, "/alternatename:??1Rva005DA831@@UAE@XZ=?apply@Rva0005970E6DwordImmSetter@@QAEXXZ")
