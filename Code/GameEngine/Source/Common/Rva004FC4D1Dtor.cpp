// ??1Rva004FC4D1@@UAE@XZ
// partial score=0.85 date=2026-10-10
// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /Ireference/shims/moduledata /O1 /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
//
// ??1Rva004FC4D1@@UAE@XZ, retail 0x004FC4D1..0x004FC55D (140 bytes, EH);
// pinned until now as the opaque ??1Rva004FC4D1@@UAE@XZ. A living-world
// listener holder with three bases (the Snapshot at +0, a 4-byte interface
// at +4 under vtable 0x00C63528 that the object registers with the
// listener list at +0x1C of TheLivingWorldLogic, and the listener list at
// +8) and two owned pointers at +0x20 / +0x24: it tells its listeners (the
// rowed forEach 0x004FC320 with the slot-1 vcall thunk 0x005CB260),
// unregisters the interface (rowed 0x002B7250) and releases the pointers;
// the bases then unwind (declaration order Snapshot, list, interface: MSVC lays
// the polymorphic interface out at +4 yet constructs it last). Class name address-derived; the list is a 4-byte
// POD stand-in whose buffer retail frees.
#include <stdlib.h>
void Rva00030830FreeAllocation(void *);
#define free Rva00030830FreeAllocation
#include <vector>
#undef free
#include "Common/Snapshot.h"

enum ObjectID { INVALID_ID = 0 };

class Gen_uwm_004edfff
{
public:
	virtual void slot00();
	~Gen_uwm_004edfff() {}
};

class Rva004FC320Listener
{
public:
	virtual void slot0();
	virtual void notify(void *);
};

class Rva004FC320List
{
public:
	void forEach(void (Rva004FC320Listener::*notify)(void *), void *arg);
};

class Rva000AD6F4
{
public:
	__forceinline Rva000AD6F4() : m_ptr(0) {}
	void clear();
	~Rva000AD6F4();
private:
	void *m_ptr;
};

class CreateAHeroData;

class Rva002B7250
{
public:
	void rva002B7250(CreateAHeroData *v);
};

class LivingWorldLogic
{
public:
	char m_pad[0x1C];
	Rva002B7250 m_1C;
};
extern LivingWorldLogic *TheLivingWorldLogic;

class Rva004FC4D1 : public Snapshot, public _STL::vector<ObjectID>, public Gen_uwm_004edfff
{
public:
	virtual ~Rva004FC4D1();
private:
	char m_pad14[0x20 - 0x14];
	Rva000AD6F4 m_20;
	Rva000AD6F4 m_24;
};

Rva004FC4D1::~Rva004FC4D1()
{
	((Rva004FC320List *)static_cast<_STL::vector<ObjectID> *>(this))->forEach(&Rva004FC320Listener::notify, this);
	TheLivingWorldLogic->m_1C.rva002B7250((CreateAHeroData *)static_cast<Gen_uwm_004edfff *>(this));
}
