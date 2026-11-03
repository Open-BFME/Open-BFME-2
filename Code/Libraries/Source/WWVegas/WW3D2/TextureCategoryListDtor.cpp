// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
//
// ??1TextureCategoryList@@UAE@XZ at retail 0x001446F0 (95B) with its scalar
// deleting destructor ??_GTextureCategoryList@@UAEPAXI@Z at 0x00144870 (27B).
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

#include "../WWLib/MultiListObjectClass.h"

#include "../WWLib/GenericMultiListClass.h"


class TextureCategoryList : public GenericMultiListClass
{
public:
	virtual ~TextureCategoryList();
};

// ??1TextureCategoryList@@UAE@XZ
TextureCategoryList::~TextureCategoryList()
{
	while (Head.Next != (void *)&Head) {
		Internal_Remove_List_Head();
	}
}
