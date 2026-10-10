// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
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
// The same target vftable at 0x00843A70 has recalcApparentControllingPlayer
// at +0x50 and onContaining at +0x58 (0x00466977 and 0x004664BB). The latter
// calls rowed OpenContain::onContaining (0x00463097), rowed
// Object::setDisabled (0x00291C9B), then dispatches recalc through +0x50.
//
// Donor provenance: Open-BFME-1 revision
// 6583b3c1ff21db4a561285717028fdafc780b7db, GameEngine/Include/
// GameLogic/Module/CaveContain.h declares removeFromContain(Object*, Bool)
// immediately before removeAllContained(Bool). The donor declarations support
// these names; target slots, index access, list operations and call flow are
// established independently from BFME2 evidence.
// Its CaveContainOnContaining.cpp also supports the call sequence; target
// vtable placement, rowed callees, and body bytes establish this identity/ABI.

typedef bool Bool;
typedef unsigned int UnsignedInt;
enum DisabledType
{
	DISABLED_HELD = 3
};
enum ObjectID
{
	OBJECTID_NONE = 0
};
enum ObjectStatusTypes
{
	OBJECT_STATUS_UNDER_CONSTRUCTION = 2
};
class DamageInfo;
class Object;

class BodyModuleInterfaceView
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
	virtual void slot5C(Object *) = 0;
};

// The owner's BodyModule pointer is at Object +0x250; 0x0028FB6F is rowed
// under its address-derived name.
class Object
{
public:
	void setDisabled(DisabledType type);
	void rva0028FB6F(void *owner);
	Bool testStatus(ObjectStatusTypes status) const;
	BodyModuleInterfaceView *bodyModule() const
	{
		return *reinterpret_cast<BodyModuleInterfaceView *const *>(
			reinterpret_cast<const char *>(this) + 0x250);
	}
};


class Rva00466398
{
public:
	Rva0036AE51ListView rva00466398();
};

class TunnelTracker : public Rva00466398
{
public:
	Bool rva004F550A(ObjectID value);
	void removeFromContain(ObjectID value, int exposeStealthUnits);
	Bool rva004F571B(Object *object);
	void iterateContained(void (*callback)(Object*,void*), void *data, Bool reverse);
};

class CaveSystem
{
public:
	TunnelTracker *getTunnelTrackerForCaveIndex(UnsignedInt index);
	void registerNewCave(int index);
};

// Existing target row at 0x0042755D; its address-derived spelling is kept.
class Rva0042755D
{
public:
	Bool rva0042755D(UnsignedInt oldIndex, UnsignedInt newIndex);
};

// Opaque call-site view of the already-pinned 3-byte ret-4 body at 0x0047A69C
// (donor CaveSystem::unregisterCave is empty and folds there). No layout; the
// target caller supplies CaveSystem* in ECX.
class Gen_003bcb40
{
public:
	void m(int index);
};

// Existing 31-byte target row used when adding an object to a tunnel tracker.
class Rva004F56FC
{
public:
	void rva004F56FC(Object *object);
};

class DieMuxData
{
public:
	Bool isDieApplicable(const Object *object, const DamageInfo *damageInfo) const;
};

// Target view: the CaveContain module-data pointer is this-0x24 for the
// +0x28 receiver. Retail calls isDieApplicable on its +8 DieMuxData member.
class CaveContainModuleDataView
{
public:
	unsigned char m_pad[8];
	DieMuxData m_dieMuxData;
};

// Target data_xrefs.tsv records this pointer at RVA 0x00A031F4; existing
// engine code declares the same SAGE global as TheCaveSystem.
extern CaveSystem *TheCaveSystem;

class OpenContain
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
	virtual void recalcApparentControllingPlayer() = 0;
	virtual void slot21() = 0;
	virtual void onContaining(Object *, Bool);
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

// This interface view preserves the target secondary vtable slot order and
// derived cave-index offset; unrelated slots remain intentionally opaque.
class CaveContain : public OpenContain
{
public:
	virtual void onContaining(Object *, Bool);
	virtual void removeFromContain(Object *obj, Bool exposeStealthUnits);
	virtual void removeAllContained(Bool exposeStealthUnits);
	virtual void iterateContained(void (*callback)(Object*,void*), void *data, unsigned int flags);
	// Implemented for the CaveInterface subobject at complete-object +0xFC.
	virtual void tryToSetCaveIndex(int newIndex);
	// Implemented for the one-entry die interface at complete-object +0x28.
	virtual void onDie(const DamageInfo *damageInfo);

	Object *getObject() const
	{
		return *reinterpret_cast<Object *const *>(
			reinterpret_cast<const char *>(this) - 0x18);
	}
	Object *getDieObject() const
	{
		return *reinterpret_cast<Object *const *>(
			reinterpret_cast<const char *>(this) - 0x20);
	}

private:
	unsigned char m_pad[0xE0];
	int m_caveIndex;
};

template <> void _STL::_List_base<Rva0036ADF9Element, _STL::allocator<Rva0036ADF9Element> >::clear();
template <> _STL::_List_base<Rva0036ADF9Element, _STL::allocator<Rva0036ADF9Element> >::~_List_base();

// ?onContaining@CaveContain@@UAEXPAVObject@@_N@Z
void CaveContain::onContaining(Object *obj, Bool wasSelected)
{
	OpenContain::onContaining(obj, wasSelected);
	obj->setDisabled(DISABLED_HELD);
	recalcApparentControllingPlayer();
}

// The 91-byte slot +0xA4 body gets the tracker by the cave index, checks and
// removes the object's 32-bit list value through rowed TunnelTracker helpers,
// then calls the owner body's +0x5C slot and Object helper 0x0028FB6F. This
// view's owner pointer is at this-0x18; the +0x5C callee is unresolved.
// ?removeFromContain@CaveContain@@UAEXPAVObject@@_N@Z
void CaveContain::removeFromContain(Object *obj, Bool exposeStealthUnits)
{
	if (obj == 0)
		return;

	TunnelTracker *tracker =
		TheCaveSystem->getTunnelTrackerForCaveIndex(m_caveIndex);
	// Retail passes the Object* word unchanged to the ObjectID list helpers;
	// removeAllContained reads these 32-bit list values back as Object pointers.
	ObjectID objectID = static_cast<ObjectID>(
		reinterpret_cast<UnsignedInt>(obj));
	if (tracker->rva004F550A(objectID))
	{
		// The helper's second int is unused; retail forwards the whole Bool
		// stack word, so preserve that call shape here.
		int exposeFlag = *reinterpret_cast<const int *>(&exposeStealthUnits);
		tracker->removeFromContain(objectID, exposeFlag);
		BodyModuleInterfaceView *body = getObject()->bodyModule();
		if (body != 0)
			body->slot5C(obj);
		obj->rva0028FB6F(getObject());
	}
}

// ?removeAllContained@CaveContain@@UAEX_N@Z
void CaveContain::removeAllContained(Bool exposeStealthUnits)
{
	TunnelTracker *tracker = TheCaveSystem->getTunnelTrackerForCaveIndex(m_caveIndex);
	ContainmentList objects = tracker->rva00466398().rva0036AE51();
	ContainmentList::iterator it = objects.begin();
	while (it != objects.end())
	{
		Object *obj = (Object *)containmentFirstWord(*it);
		++it;
		removeFromContain(obj, exposeStealthUnits);
	}
}

// The CaveInterface secondary vftable is installed at complete-object +0xFC
// (target table RVA 0x00843A54); slot 0 points to 0x004667D1. Its 119-byte
// body reads the cave index at interface-this +8, owner Object at
// interface-this -0xF4, and ends in ret 4. Open-BFME-1's CaveInterface
// declares tryToSetCaveIndex(Int) as its first virtual (revision
// 6583b3c1ff21db4a561285717028fdafc780b7db, CaveContainTryToSetCaveIndex.cpp);
// the donor supplies the switch/unregister/destroy/register/create sequence.
// ?tryToSetCaveIndex@CaveContain@@UAEXH@Z
void CaveContain::tryToSetCaveIndex(int newIndex)
{
	// This vtable entry receives the CaveInterface subobject pointer at +0xFC,
	// unlike the +0x20 ContainModuleInterface view used by sibling methods.
	char *interfaceThis = reinterpret_cast<char *>(this);
	int *caveIndex = reinterpret_cast<int *>(interfaceThis + 8);
	if (reinterpret_cast<Rva0042755D *>(TheCaveSystem)->rva0042755D(
		static_cast<UnsignedInt>(*caveIndex), static_cast<UnsignedInt>(newIndex)))
	{
		TunnelTracker *oldTracker =
			TheCaveSystem->getTunnelTrackerForCaveIndex(
				static_cast<UnsignedInt>(*caveIndex));
		reinterpret_cast<Gen_003bcb40 *>(TheCaveSystem)->m(*caveIndex);
		oldTracker->rva004F571B(
			*reinterpret_cast<Object **>(interfaceThis - 0xF4));

		*caveIndex = newIndex;
		TheCaveSystem->registerNewCave(*caveIndex);
		TunnelTracker *newTracker =
			TheCaveSystem->getTunnelTrackerForCaveIndex(
				static_cast<UnsignedInt>(*caveIndex));
		reinterpret_cast<Rva004F56FC *>(newTracker)->rva004F56FC(
			*reinterpret_cast<Object **>(interfaceThis - 0xF4));
	}
}

// Target evidence: CaveContainCtor.cpp installs the one-entry vftable at
// 0x00843A6C at complete-object +0x28; its slot 0 is 0x00466724. The 92-byte
// body receives this as that +0x28 view (ret 4) and uses the module-data
// pointer at this-0x24, owner Object at this-0x20, and cave index at this+0xDC
// (complete-object +0x104). Donor provenance: Open-BFME-1 revision
// 6583b3c1ff21db4a561285717028fdafc780b7db, Generals CaveContain::onDie, which
// supplies the ordered die-check/unregister/destroy semantics only.
// ?onDie@CaveContain@@UAEXPBVDamageInfo@@@Z
void CaveContain::onDie(const DamageInfo *damageInfo)
{
	char *interfaceThis = reinterpret_cast<char *>(this);
	CaveContainModuleDataView *moduleData =
		*reinterpret_cast<CaveContainModuleDataView **>(interfaceThis - 0x24);
	if (!moduleData->m_dieMuxData.isDieApplicable(getDieObject(), damageInfo))
		return;
	if (getDieObject()->testStatus(OBJECT_STATUS_UNDER_CONSTRUCTION))
		return;
	int *caveIndex = reinterpret_cast<int *>(interfaceThis + 0xDC);
	TunnelTracker *myTracker = TheCaveSystem->getTunnelTrackerForCaveIndex(
		static_cast<UnsignedInt>(*caveIndex));
	reinterpret_cast<Gen_003bcb40 *>(TheCaveSystem)->m(*caveIndex);
	myTracker->rva004F571B(getDieObject());
}

// Native466486..4664BB full53 RET12. The CaveContain wrapper extends
// the ZH iteration interface with observed bit flags: bit0 gates traversal
// and bit3 supplies the tracker reverse argument. Flag names stay unknown.
void CaveContain::iterateContained(void (*callback)(Object*,void*), void *data, unsigned int flags)
{
 if (flags & 1) {
  TunnelTracker *tracker=TheCaveSystem->getTunnelTrackerForCaveIndex(m_caveIndex);
  tracker->iterateContained(callback,data,(flags >> 3)&1);
 }
}
