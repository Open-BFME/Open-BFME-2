// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// ?xfer@SiegeDockingBehavior@@MAEXPAVXfer@@@Z, retail 0x0045A02F, 318 bytes.
// Slot 3 (offset 0x0C) of vtable 0x008414DC. xfer shape with Version1 then UpdateModule base then IsStoring branch.
// Evidence: donor game/GameEngine/Source/GameLogic/Object/Behavior/SiegeDockingBehaviorXfer.cpp (BFME1 0x00206FF0) direct reuse with Version1 repair; base model from PoisonedBehaviorXfer UpdateModule 0x20 plus secondary at 0x20; callers none; callees Version1 0x53EE UpdateModule xfer 0x44DF9F IsStoring slot8 XferSiegeTypeEnum 0x306112 XferObjectID 0x3060B2 stopDocking 0x459C27 new 0x2FDA0 push_back 0x4DFCB0 rowed.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#define _STLP_BFME_COPY_TRIVIAL_EXTERN  // call retail's one __copy_trivial (vendor/stlport/stl/_algobase.h)
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>
// Keep __node_alloc<true,0>::deallocate inline-only: every call here is inlined,
// and this TU's /O1 COMDAT copy differs from the copy the link keeps.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void _STLP_CALL __node_alloc<true, 0>::deallocate(void *__p, size_t __n)
{ if (__n > (size_t)_MAX_BYTES) __stl_delete(__p); else _M_deallocate(__p, __n); }
}
// With the bfmealloc allocator flags of its retail siblings (stlport_moduledatavector_push.cpp)
// this unit's vector<const ModuleData *> COMDATs are retail's own bodies, so they need no
// declaration-only suppression.
class ModuleData;
typedef unsigned int UnsignedInt;
typedef int Int;
typedef bool Bool;
enum ObjectID
{
	INVALID_OBJECT_ID = 0
};
class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
class Coord3DBase;
class ICoord3D;
class Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;
class Thing;
class ModuleData;
class Object;
#include "../../../../Include/Common/BfmeXfer.h"
void XferObjectID(Xfer *xfer, ObjectID *objectID);
void XferSiegeTypeEnum(Xfer *xfer, int *value);
class Coord3DBase
{
public:
	float x;
	float y;
	float z;
};
class BehaviorModuleBase
{
public:
	virtual void behaviorModuleBaseAnchor();
	const ModuleData *m_moduleData;
	Object *m_object;
};
class BehaviorModuleOther
{
public:
	virtual void behaviorModuleOtherAnchor();
};
#include "../../../../Include/GameLogic/Module/BehaviorModule.h"
class UpdateModuleInterface
{
public:
	virtual void update();
};
class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();
	void xfer(Xfer *xfer);
protected:
	unsigned m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_bfmeReserved;
};
class SiegeDockingBehaviorSecondaryBase
{
public:
	virtual void slot();
};
struct SiegeDockEntry00206FF0
{
	Int m_int00;
	Int m_enum04;
	Coord3DBase m_coord08;
	Coord3DBase m_coord14;
	ObjectID m_objectID20;
};
class SiegeDockingBehavior : public UpdateModule, public SiegeDockingBehaviorSecondaryBase
{
protected:
	virtual void xfer(Xfer *xfer);
private:
	void stopDocking();
	_STL::vector<SiegeDockEntry00206FF0 *> m_entries;
	Bool m_bool30;
};
void SiegeDockingBehavior::xfer(Xfer *xfer)
{
	xfer->Version1();
	UpdateModule::xfer(xfer);
	if (xfer->IsStoring())
	{
		UnsignedInt count = m_entries.size();
		*xfer == count;
		for (UnsignedInt index = 0; index < count; ++index)
		{
			XferSiegeTypeEnum(xfer, &m_entries[index]->m_enum04);
			*xfer == m_entries[index]->m_int00;
			*xfer == m_entries[index]->m_coord08;
			*xfer == m_entries[index]->m_coord14;
			XferObjectID(xfer, &m_entries[index]->m_objectID20);
		}
	}
	else
	{
		UnsignedInt count = 0;
		*xfer == count;
		for (UnsignedInt index = 0; index < count; ++index)
		{
			stopDocking();
			SiegeDockEntry00206FF0 *entry = new SiegeDockEntry00206FF0;
			XferSiegeTypeEnum(xfer, &entry->m_enum04);
			*xfer == entry->m_int00;
			*xfer == entry->m_coord08;
			*xfer == entry->m_coord14;
			XferObjectID(xfer, &entry->m_objectID20);
			((_STL::vector<const ModuleData *> *)&m_entries)->push_back((const ModuleData *&)entry);
		}
	}
	*xfer == m_bool30;
}
