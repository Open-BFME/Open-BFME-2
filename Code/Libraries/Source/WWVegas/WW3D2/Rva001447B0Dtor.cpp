// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD C:/Program Files/Git/ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
//
// ??1Rva001447B0@@UAE@XZ at retail 0x001447B0 (95B) with its scalar
// deleting destructor ??_GRva001447B0@@UAEPAXI@Z at 0x001448B0 (27B).
// Opaque identity: fourth of four byte-identical list-dtor shapes alongside
// the named TextureCategoryList/FVFCategoryList pair (vtable 0xBD34EC;
// callers 0x1465A2/0x146917 unidentified). True class name open:
// DX8PolygonRendererList vs TextureTrackerList (dx8list.h's remaining
// typedefs). FVF TU recipe.
//
// Minimal TU-local hierarchy with real manglings for the two resolved
// callees: Remove_Head inlines to matched Internal_Remove_List_Head
// @0x6109A0; the base dtor resolves to matched ??1GenericMultiListClass
// @0x610640. Base flags (-EHsc-) kept: the retail dtor carries an SEH
// prolog with states that /EHsc does not reproduce.

#include <new.h>

class MultiListObjectClass
{
public:
	virtual ~MultiListObjectClass();
	void *ListNode;
};

#include "../WWLib/GenericMultiListClass.h"

// Only derived lists are constructed here; their native constructors install
// the derived vptr. Keep the base table and its SEH deleting dtor external.

class Rva001447B0 : public GenericMultiListClass
{
public:
	Rva001447B0(void);
	virtual ~Rva001447B0();
};

// ??1Rva001447B0@@UAE@XZ
Rva001447B0::~Rva001447B0()
{
	while (Head.Next != (void *)&Head) {
		Internal_Remove_List_Head();
	}
}

// ??0Rva001447B0@@QAE@XZ at retail 0x00143DF0 (39B): the constructor, the Zero
// Hour multilist node and list-head constructors inlined (an empty circular
// head) before the vtable store. No direct caller remains in retail.
inline Rva001447B0::Rva001447B0(void)
{
}

// Emit the native inline constructor with the same COMDAT linkage as its consumers.
// ?bfmeAnchorRva001447B0Ctor absent-from-retail
void *bfmeAnchorRva001447B0Ctor(void *where)
{
	return ::new (where) Rva001447B0();
}
