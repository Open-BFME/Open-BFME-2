// cl: /O1 /DNDEBUG /MD /EHsc
// stlport
#include <list>
#include "../../../../Include/GameLogic/ContainmentListView.h"

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}


// Target evidence: CaveContainCtor installs the secondary vftable at +0x20;
// its slots +0xA4/+0xA8 target 0x004666C9/0x00466A50. The former takes an
// object plus Bool and removes that object from the current tunnel tracker.
// 0x00466A50 copies the tracker list into an owned list view, advances before
// each removal, and dispatches each entry through slot +0xA4. The CaveContain
// index is at +0x104 complete-object offset, hence +0xE4 from this view.
//
// Donor provenance: Open-BFME-1 revision
// 6583b3c1ff21db4a561285717028fdafc780b7db, GameEngine/Include/
// GameLogic/Module/CaveContain.h declares removeFromContain(Object*, Bool)
// immediately before removeAllContained(Bool). The donor declarations support
// these names; target slots, index access, list operations and call flow are
// established independently from BFME2 evidence.

class Object;
typedef bool Bool;


class Rva00466398
{
public:
	Rva0036AE51ListView rva00466398();
};

class Rva004F56FC : public Rva00466398
{
};

class CaveSystem
{
public:
	Rva004F56FC *getTunnelTrackerForCaveIndex(int index);
};

// Target data_xrefs.tsv records this pointer at RVA 0x00A031F4; existing
// engine code declares the same SAGE global as TheCaveSystem.
extern CaveSystem *TheCaveSystem;

class CaveContainBaseView
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;
	virtual void slot27() = 0;
	virtual void slot28() = 0;
	virtual void slot29() = 0;
	virtual void slot30() = 0;
	virtual void slot31() = 0;
	virtual void slot32() = 0;
	virtual void slot33() = 0;
	virtual void slot34() = 0;
	virtual void slot35() = 0;
	virtual void slot36() = 0;
	virtual void slot37() = 0;
	virtual void slot38() = 0;
	virtual void slot39() = 0;
	virtual void slot40() = 0;
};

// This view preserves the target secondary vtable slot order and derived
// cave-index offset; the preceding slots are intentionally opaque.
class CaveContain : public CaveContainBaseView
{
public:
	virtual void removeFromContain(Object *obj, Bool exposeStealthUnits) = 0;
	virtual void removeAllContained(Bool exposeStealthUnits);

private:
	unsigned char m_pad[0xE0];
	int m_caveIndex;
};

template <> void _STL::_List_base<Rva0036ADF9Element, _STL::allocator<Rva0036ADF9Element> >::clear();
template <> _STL::_List_base<Rva0036ADF9Element, _STL::allocator<Rva0036ADF9Element> >::~_List_base();

// ?removeAllContained@CaveContain@@UAEX_N@Z
void CaveContain::removeAllContained(Bool exposeStealthUnits)
{
	Rva004F56FC *tracker = TheCaveSystem->getTunnelTrackerForCaveIndex(m_caveIndex);
	ContainmentList objects = tracker->rva00466398().rva0036AE51();
	ContainmentList::iterator it = objects.begin();
	while (it != objects.end())
	{
		Object *obj = (Object *)containmentFirstWord(*it);
		++it;
		removeFromContain(obj, exposeStealthUnits);
	}
}
