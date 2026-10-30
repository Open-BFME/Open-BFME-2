// cl: /DNDEBUG /MD /EHs-c- /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmelist /Ireference/shims/bfmealloc
// stlport
//
// ?xfer@FloodUpdate@@MAEXPAVXfer@@@Z, retail 0x0048E4E2, 289 bytes.
// Slot 3 of ??_7FloodUpdate 0x00C4C948 (slot-2 name getter returns
// "FloodUpdate"; installed by the rowed ctor 0x0048E09F). The rowed
// UpdateModule::xfer 0x0044DF9F first, then the light-CRC out, Version(1,1),
// the element count of the pointer list at +0x20 (int, Xfer slot 0x7C).
// Loading news 0x14-byte records through the rowed ctor 0x0048E16C and
// pushes them (list push_back 0x0005548F); each record is an ObjectID
// (rowed XferObjectID), the coord vector at +4 (rowed
// Rva00390911XferCoordVector) and an int at +0x10. Saving walks the list
// with the same three transfers. Finally the bool at +0x24. Member names
// not recovered.

#include <list>
#include <vector>

// vector<int> fill/insert otherwise instantiates the _Construct<int,int>
// COMDAT (one byte shape per TU flags); a file-static overload takes those
// calls instead so this TU emits no external copy.
#include <new>
namespace _STL {
static inline void _Construct(int *__p, const int &__val)
{ new (__p) int(__val); }
}

// __malloc_alloc<0> allocate/deallocate otherwise instantiate per-TU
// COMDATs (one byte shape per TU malloc/free wiring); explicit
// dllimport+forceinline specializations take those calls inline so this
// TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void *__malloc_alloc<0>::allocate(size_t __n)
{ void *__r = malloc(__n); if (!__r) __r = _S_oom_malloc(__n); return __r; }
template <> __declspec(dllimport) __forceinline
void __malloc_alloc<0>::deallocate(void *__p, size_t)
{ free((char *)__p); }
}

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class _IterTp, class _LeftTraits, class _RightTraits>
static inline bool operator!=(const _List_iterator<_IterTp, _LeftTraits> &a,
                              const _List_iterator<_IterTp, _RightTraits> &b)
{ return a._M_node != b._M_node; }
}


// Retail calls the separately rowed four-byte-element append at 0x5548F.
// The list<void*> instance owned by the 3D pool TU is 0x526103 and calls
// a different insertion provider. Preserve it, but select the retail call.
// The int-element view selects that verified four-byte ABI instance.
// The target sample/record remains a pointer; no int-container identity is claimed.


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

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};

#include "../../../../../Libraries/Include/Lib/Coord3DCtorView.h"
#include "../../../Common/GameLogicObjectLookupView.h"
typedef bool Bool;
typedef int Int;
enum UpdateSleepTime { UPDATE_SLEEP_NONE = 1 };
enum NameKeyType { NK_UNKNOWN = 0 };
struct FloodMember;
class FloodUpdateModuleData;

struct AICommandCoordVector;

void XferObjectID(Xfer *xfer, ObjectID *id);
Xfer *Rva00390911XferCoordVector(Xfer *xfer, AICommandCoordVector *vec); // returns xfer, as rowed

class Rva0048E16C
{
public:
	Rva0048E16C() throw();

	ObjectID m_id; // +0
	_STL::vector<Coord3D> m_path; // +4
	Int m_index; // +0x10
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

class BehaviorModule : public BehaviorModuleBase, public BehaviorModuleOther
{
public:
	Object *getObject() const { return m_object; }
	BehaviorModule(Thing *thing, const ModuleData *moduleData);
};

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update();
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();
	void xfer(Xfer *xfer);
protected:
	void setWakeFrame(Object *obj, unsigned int frame);
	unsigned m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_bfmeReserved;
};

class FloodUpdate : public UpdateModule
{
public:
	FloodUpdate(Thing *thing, const ModuleData *moduleData);
	virtual ~FloodUpdate();
	virtual UpdateSleepTime update();
	void rva0048DC51(const FloodMember *member, Rva0048E16C *record);
	void rva0048E189();

protected:
	virtual void xfer(Xfer *xfer);
	const FloodUpdateModuleData *getFloodUpdateModuleData() const
	{
		return (const FloodUpdateModuleData *)m_moduleData;
	}

private:
	_STL::list<Rva0048E16C *> m_records; // +0x20
	Bool m_membersCreated; // +0x24
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?xfer@FloodUpdate@@MAEXPAVXfer@@@Z @0x0048E4E2
void FloodUpdate::xfer(Xfer *xfer)
{
	UpdateModule::xfer(xfer);

	if (xfer->IsLightCRC())
		return;

	Xfer::Version version(1, 1);
	*xfer == version;

	int count = m_records.size();
	*xfer == count;

	if (xfer->IsLoading())
	{
		for (int i = 0; i < count; ++i)
		{
			Rva0048E16C *record = new Rva0048E16C;
			XferObjectID(xfer, &record->m_id);
			Rva00390911XferCoordVector(xfer, reinterpret_cast<AICommandCoordVector *>(&record->m_path));
			*xfer == record->m_index;
			reinterpret_cast<_STL::list<int> *>(&m_records)->push_back(reinterpret_cast<const int &>(record));
		}
	}
	else if (xfer->IsStoring())
	{
		for (_STL::list<Rva0048E16C *>::iterator it = m_records.begin(); it != m_records.end(); ++it)
		{
			Rva0048E16C *record = (Rva0048E16C *)*it;
			XferObjectID(xfer, &record->m_id);
			Rva00390911XferCoordVector(xfer, reinterpret_cast<AICommandCoordVector *>(&record->m_path));
			*xfer == record->m_index;
		}
	}

	*xfer == m_membersCreated;
}
