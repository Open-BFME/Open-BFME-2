// cl: /DNDEBUG /MD /EHsc /O1 /arch:SSE /G7
// ??0Rva005750CF@@QAE@HPAX@Z retail 0x005750CF 86B
// Evidence: target calls rowed base ctor 0x005746AF with int arg; installs vtables 0x0086E4A4 and 0x0086E360 at the primary and +0x10 subobjects; stores manager at +0x14 and appends this+0x10 through rowed helper 0x005A0B4C. Class identity is address-derived; base relationship follows target offsets and vtable stores.
#include "../../../Libraries/Source/Apt/AptRefTarget.h"
class Rva005746AF
{
public:
	Rva005746AF(int arg);
	virtual ~Rva005746AF();
private:
	int m_04;
	unsigned long m_08;
	TreeHintRef00217D4C m_0C;
};
struct Rva002BA8F1Listener
{
	char opaque[4];
};
#include "../../Include/Common/Rva005A0B4CList.h"
// The +0x10 base is the one Rva00575125 has: the ctor installs its one-slot
// table 0x0086E360 (a RET 4 callback) and retail's unwind funclet 0x0079B108
// destroys it through 0x00574293, rowed as ??1Rva00575125Second (nonvirtual).
class Rva00575125Second
{
public:
	virtual void slot0(int);
	~Rva00575125Second();
};
class Rva005750CF : public Rva005746AF, public Rva00575125Second
{
public:
	Rva005750CF(int a, void *mgr);
private:
	void *m_14;
};

Rva005750CF::Rva005750CF(int a, void *mgr)
	: Rva005746AF(a)
	, Rva00575125Second()
	, m_14(mgr)
{
	((Rva005A0B4CList *)((char *)mgr + 4))->append((Rva002BA8F1Listener *)((char *)this + 0x10));
}
