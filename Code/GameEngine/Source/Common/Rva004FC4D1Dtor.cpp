// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /Ireference/shims/moduledata /O1 /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
//
// ??1LivingWorldBuildPlot@@UAE@XZ, retail 0x004FC4D1..0x004FC55D (140 bytes, EH);
// pinned until now as the opaque ??1LivingWorldBuildPlot@@UAE@XZ. A living-world
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
#include <vector>
#include "Common/Snapshot.h"

enum ObjectID { INVALID_ID = 0 };

#include "../../Include/Common/RegionTurnObserverView.h"

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

class LivingWorldBuildPlot : public Snapshot, public _STL::vector<ObjectID>, public RegionTurnObserverView
{
public:
	virtual ~LivingWorldBuildPlot();
	virtual void BeginTurn(int a, int b);
private:
	char m_pad14[0x20 - 0x14];
	Rva000AD6F4 m_20;
	Rva000AD6F4 m_24;
};

LivingWorldBuildPlot::~LivingWorldBuildPlot()
{
	((Rva004FC320List *)static_cast<_STL::vector<ObjectID> *>(this))->forEach(&Rva004FC320Listener::notify, this);
	TheLivingWorldLogic->m_1C.rva002B7250((CreateAHeroData *)static_cast<RegionTurnObserverView *>(this));
}

class Rva005392C2
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08(bool a, bool b);
	void rva005392C2();
};

// Native C63528 binds BeginTurn at 4FC23E and inherited EndTurn at 50B238.
// The +4 observer adjusts the callback receiver: building +20 and icon +24
// become callback-relative +1C and +20. The Snapshot name and constructor
// 4FC807 separately identify the complete owner as LivingWorldBuildPlot.
void LivingWorldBuildPlot::BeginTurn(int a, int b)
{
	if (!a)
	{
		Rva005392C2 *icon = (Rva005392C2 *)m_24.m_ptr;
		if (icon)
			icon->v08(m_20.m_ptr != 0, true);
	}
	if (!b)
	{
		Rva005392C2 *icon = (Rva005392C2 *)m_24.m_ptr;
		if (icon)
			icon->rva005392C2();
	}
}
