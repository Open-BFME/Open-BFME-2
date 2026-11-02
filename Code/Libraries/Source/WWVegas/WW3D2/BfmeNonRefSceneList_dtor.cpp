// cl: /DNDEBUG /MD /EHsc /Ob2 C:/Program Files/Git/ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// ??1BfmeNonRefSceneList@@UAE@XZ, retail 0x00141780, 96 bytes.
// Dedicated TU (SimpleSceneClass_dtor.cpp calls this dtor twice for its
// list_bc/list_d4 members; a same-TU definition would capture those REL32s
// locally).
//
// Battle for Middle-earth WWLib multilist.h donor: BfmeNonRefSceneList is a
// GenericMultiListClass whose destructor drains without releasing (the
// Ref sibling releases through Remove_Head instead):
//	while (!Is_Empty())
//		Internal_Remove_List_Head();
// Is_Empty is the header inline (Head.Next == &Head); the base destructor
// and Internal_Remove_List_Head are declared only (owned by multilist.cpp),
// so the loop and the base unwind emit the cookie-SEH shape like retail.

#include <new.h>

class MultiListObjectClass;

#include "../WWLib/GenericMultiListClass.h"

// Only derived lists are constructed here; their native constructors install
// the derived vptr. Keep the base table and its SEH deleting dtor external.

class BfmeNonRefSceneList : public GenericMultiListClass
{
public:
	BfmeNonRefSceneList();
	virtual ~BfmeNonRefSceneList();
};

// ??1BfmeNonRefSceneList@@UAE@XZ
BfmeNonRefSceneList::~BfmeNonRefSceneList()
{
	// NOTE: non-Yoda member comparison (Head.Next on the left): with the
	// address ready in edi the comparison emits cmp [esi+8],edi. (The Yoda
	// order emits the swapped cmp edi,[esi+8]; !Is_Empty() routes through
	// a register instead. Requires /G7: without it the member is loaded
	// into a register first.)
	while (Head.Next != &Head) {
		Internal_Remove_List_Head();
	}
}

// ??0BfmeNonRefSceneList@@QAE@XZ, retail 0x001410B0 (39 bytes): the constructor, the
// multilist.h inline chain (the node constructor clears all five words, the
// list constructor points the head at itself) under this class's vtable.
inline BfmeNonRefSceneList::BfmeNonRefSceneList()
{
}

// Emit the native inline constructor with the same COMDAT linkage as its consumers.
// ?bfmeAnchorBfmeNonRefSceneListCtor absent-from-retail
void *bfmeAnchorBfmeNonRefSceneListCtor(void *where)
{
	return ::new (where) BfmeNonRefSceneList();
}
