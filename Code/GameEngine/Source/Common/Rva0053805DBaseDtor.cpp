// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /G7 /EHsc
//
// ??1Rva0053805DBase@@UAE@XZ, retail 0x00538133..0x005381B9 (134 bytes, EH),
// and the scalar deleting destructor ??_GRva0053805DBase@@UAEPAXI@Z,
// 0x005381B9 (35 bytes, slot 0 of the primary table 0x00C691EC), of the
// listener-broadcasting base whose constructor Rva0053805DBaseCtor.cpp rows.
// Target facts: the dtor restores 0x00C691EC and the shared virtual base's
// table 0x00C6EE28 through the vbtable at +0x18, tells every listener of the
// +8 list through slot 0 (generic vcall thunk 0x001FF3A9, forEach 0x00537F56),
// then destroys the +0x24 and +0x20 strings (releaseBuffer 0x00036410), the
// +0x1C list (_List_base dtor 0x004EC395), the +8 list's storage (GameFree;
// out-of-line copy 0x0007FAB3) and the counted root (table 0x00BC6F20; copy
// 0x004E84A4). Five EH states, one per subobject. The deleting dtor resets
// the virtual base at +0x30 to 0x00C6EE28 after ??1 (inlined ??_D).
//
// A separate unit from the constructor: retail's constructor never stores the
// root's table, which that unit models with a novtable root; novtable also
// drops the root destructor's table store this body needs. The +8 list goes
// by two ledger names: its constructor 0x00330757 is Rva00330757Member, its
// broadcast 0x00537F56 Rva00537F56List; the cast bridges them. Names are
// address-derived; the fields' meanings are not established.
#include "ascii_string.h"

void __cdecl Rva00030830GameFree(void *);

#include "../../../Libraries/Include/Lib/Region2D.h"
#include "../../Include/Common/Rva0030B72CPoint.h"

// Native seven-slot polygon interface, as in Rva00330C50Ctor.cpp.
#include "../../Include/Common/Rva00330C50Interface.h"

class Rva0053805DBase;

#include "../../Include/Common/Rva0053805DListener.h"

class Rva00537F56List
{
public:
	void forEach(void (Rva0053805DListener::*notify)(Rva0053805DBase *), Rva0053805DBase *owner);
};

#include "../../Include/Common/Rva00330757Member.h"

inline Rva00330757Member::~Rva00330757Member()
{
    if (field00) Rva00030830GameFree(field00);
}

struct Rva004FA1FObserver;
namespace _STL
{
template <class T> class allocator
{
public:
	allocator() {}
};
template <class T, class A> class _List_base
{
public:
	~_List_base();
private:
	void *m_node;
};
}

#include "../../Include/Common/Rva0007DF07.h"

class Rva0053805DBase : public Rva0007DF07, public Rva00330757Member,
	public virtual Rva00330C50Interface
{
public:
	virtual ~Rva0053805DBase();
	virtual bool slot1() const;
	virtual void rva0053805D();
	virtual void rva0053806C();
private:
	_STL::_List_base<Rva004FA1FObserver *, _STL::allocator<Rva004FA1FObserver *> > m_observers;	// +0x1C
	AsciiString m_20;
	AsciiString m_24;
	float m_28;
	bool m_2C;
};

Rva0053805DBase::~Rva0053805DBase()
{
	((Rva00537F56List *)(Rva00330757Member *)this)->forEach(&Rva0053805DListener::notify00, this);
}

// Placeholder virtuals this unit's vftables hold.  In retail each such slot
// holds a rowed function; the vftable's address is proven by the vptr stores in
// the matched destructors, so bind the placeholder to that row's name.
#pragma comment(linker, "/alternatename:?rva0053805D@Rva0053805DBase@@UAEXXZ=?rva0053805D@Rva0053805DBase@@QAEXXZ")
#pragma comment(linker, "/alternatename:?rva0053806C@Rva0053805DBase@@UAEXXZ=?rva0053806C@Rva0053805DBase@@QAEXXZ")
#pragma comment(linker, "/alternatename:?slot1@Rva0053805DBase@@UBE_NXZ=?IsCRC@Xfer@@UBE_NXZ")
