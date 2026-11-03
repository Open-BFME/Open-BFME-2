// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
//
// ??1Rva00144690@@UAE@XZ at retail 0x00144690 (95B) with its scalar
// deleting destructor ??_GRva00144690@@UAEPAXI@Z at 0x00144850 (27B).
// Opaque identity: fourth of four byte-identical list-dtor shapes alongside
// the named TextureCategoryList/FVFCategoryList pair (vtable 0xBD34E0;
// member +0x1C of the 0xBD3508-hosted 0x144AF0 body). True class name open:
// DX8PolygonRendererList vs TextureTrackerList (dx8list.h's remaining
// typedefs); host archaeology needed. FVF TU recipe.
//
// Minimal TU-local hierarchy with real manglings for the two resolved
// callees: Remove_Head inlines to matched Internal_Remove_List_Head
// @0x6109A0; the base dtor resolves to matched ??1GenericMultiListClass
// @0x610640. Base flags (-EHsc-) kept: the retail dtor carries an SEH
// prolog with states that /EHsc does not reproduce.

#include <new.h>

#include "../WWLib/MultiListObjectClass.h"

#include "../WWLib/GenericMultiListClass.h"

// This unit constructs only the derived list. Its native constructor installs
// the derived vptr; the base view must not emit a competing base vtable or
// scalar deleting destructor under this unit's SEH compiler settings.

class Rva00144690 : public GenericMultiListClass
{
public:
	Rva00144690();
	virtual ~Rva00144690();
};

// ??1Rva00144690@@UAE@XZ
Rva00144690::~Rva00144690()
{
	while (Head.Next != (void *)&Head) {
		Internal_Remove_List_Head();
	}
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??1DX8PolygonRendererList@@UAE@XZ=??1Rva00144690@@UAE@XZ")

// ??0Rva00144690@@QAE@XZ, retail 0x00143D10 (39 bytes): the constructor, the
// multilist.h inline chain (the node constructor clears all five words, the
// list constructor points the head at itself) under this class's vtable.
// Inline, as the MeshModelClass ctor units see it (they inline it and emit the
// same COMDAT); a strong copy here duplicated theirs at link.
inline Rva00144690::Rva00144690()
{
}

// ?bfmeAnchorRva00144690Ctor absent-from-retail
void *bfmeAnchorRva00144690Ctor(void *where)
{
	return ::new (where) Rva00144690();
}
