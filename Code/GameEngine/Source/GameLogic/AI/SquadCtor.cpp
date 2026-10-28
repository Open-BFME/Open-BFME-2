// cl: /O1 /MD
// stlport
// Squad::Squad, native 0x00268CAC..0x00268CD6 (42B).
// Identity: AIStateMachine::setGoalTeam 0x0035042D and setGoalAIGroup 0x00350462
// call it on a fresh 0x1C-byte operator new block; the body installs vftable
// 0x00BF9D60, whose slot 0 is the rowed deleting destructor 0x0026AF6A, slot 2
// the name getter returning "Squad" (0x00268CD6) and slot 3 the rowed
// Squad::xfer 0x004D6EC4.
// Layout: two STLport vectors at +4 and +0x10 (the Zero Hour Squad members
// m_objectIDs and m_objectsCached), both built through the ICF-shared
// _Vector_base constructor 0x00211E58. Retail has no EH state between the two
// member constructions, so this unit compiles without an EH option, like the
// verified PlayerAITypeSet sibling.
#include <vector>
// Suppress this TU's non-retail copy of ??1?$vector@PAVObject@@V?$allocator@PAVObject@@@_STL@@@_STL@@QAE@XZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class Object;
namespace _STL { template <> vector<Object *,allocator<Object *> >::~vector(); }
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@PAVObject@@@_STL@@QBEXPAPAVObject@@I@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class Object;
namespace _STL { template <> void allocator<Object *>::deallocate(Object **, size_t) const; }
// Suppress this TU's non-retail copy of ??1?$_Vector_base@PAVObject@@V?$allocator@PAVObject@@@_STL@@@_STL@@QAE@XZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class Object;
namespace _STL { template <> _Vector_base<Object *, allocator<Object *> >::~_Vector_base(); }

enum ObjectID
{
	INVALID_ID = 0
};
// Bind allocator<ObjectID>::deallocate to the kept retail copy.
namespace _STL { template <> void allocator<ObjectID>::deallocate(ObjectID *, size_t) const; }
// Likewise the ObjectID vector's destructors (called only by the implicit
// ~Squad, not by the rowed constructor): this unit's unproven copies would
// be the first from 0x00268CAC and lose to the retail ones.
namespace _STL { template <> vector<ObjectID, allocator<ObjectID> >::~vector(); }
namespace _STL { template <> _Vector_base<ObjectID, allocator<ObjectID> >::~_Vector_base(); }

class Object;
class Xfer;

class Squad
{
public:
	Squad();
	// Retail 0x0026AF86 (via ??_G 0x0026AF6A): frees the two vectors' storage.
	virtual ~Squad() {}

protected:
	// Slot 1 is the shared empty body 0x000B3FD0; slot 2 (0x00268CD6) returns "Squad".
	virtual void loadPostProcess() {}
	virtual const char *getSnapshotName() const { return "Squad"; }
	virtual void xfer(Xfer *xfer);

private:
	_STL::vector<ObjectID> m_objectIDs;
	_STL::vector<Object *> m_objectsCached;
};

Squad::Squad()
{
}

