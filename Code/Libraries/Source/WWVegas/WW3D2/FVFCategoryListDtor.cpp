// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
//
// ??1FVFCategoryList@@UAE@XZ at retail 0x00144750 (95B) with its scalar
// deleting destructor ??_GFVFCategoryList@@UAEPAXI@Z at 0x00144890 (27B).
// Dedicated TU: BFME2 made the category lists real classes (vtables
// 0xBD34E8/0xBD34E4/0xBD34E0 with ICF-folded tails) instead of ZH/BFME1
// MultiListClass typedefs, so neither dx8renderer.cpp (ZH header, statics)
// nor dx8fvf.cpp can host these bodies.
//
// Minimal TU-local hierarchy with real manglings for the two resolved
// callees: Remove_Head inlines to matched Internal_Remove_List_Head
// @0x6109A0; the base dtor resolves to matched ??1GenericMultiListClass
// @0x610640. Base flags (-EHsc-) kept: the retail dtor carries an SEH
// prolog with states that /EHsc does not reproduce.

#include <new.h>

#include "../WWLib/MultiListObjectClass.h"

#include "../WWLib/GenericMultiListClass.h"

// Only derived lists are constructed here; their native constructors install
// the derived vptr. Keep the base table and its SEH deleting dtor external.

class FVFCategoryList : public GenericMultiListClass
{
public:
	FVFCategoryList(void);
	virtual ~FVFCategoryList();
	bool rva00143E40(MultiListObjectClass *obj);
	MultiListObjectClass *rva00143E50();
};

// ??1FVFCategoryList@@UAE@XZ
FVFCategoryList::~FVFCategoryList()
{
	while (Head.Next != (void *)&Head) {
		Internal_Remove_List_Head();
	}
}

// ??0FVFCategoryList@@QAE@XZ at retail 0x00143D90 (39B): the constructor, the Zero
// Hour multilist node and list-head constructors inlined (an empty circular
// head) before the vtable store. No direct caller remains in retail.
inline FVFCategoryList::FVFCategoryList(void)
{
}

// Retail 0x00143E40 and 0x00143E50 (5-byte tail jumps): the
// typed remove and remove-head forwards of a category list (ZH
// MultiListClass<T>::Remove / Remove_Head shape) into the matched
// GenericMultiListClass::Internal_Remove 0x00610930 and
// Internal_Remove_List_Head 0x006109A0, placed after the FVFCategoryList
// constructor. Which BFME 2 list class owns these ICF-shared copies is not
// established, so the names are address-derived.
bool FVFCategoryList::rva00143E40(MultiListObjectClass *obj)
{
	return Internal_Remove(obj);
}

MultiListObjectClass *FVFCategoryList::rva00143E50()
{
	return Internal_Remove_List_Head();
}

// Emit the native inline constructor with the same COMDAT linkage as its consumers.
// ?bfmeAnchorFVFCategoryListCtor absent-from-retail
void *bfmeAnchorFVFCategoryListCtor(void *where)
{
	return ::new (where) FVFCategoryList();
}
