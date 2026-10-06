// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD
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

class MultiListObjectClass
{
public:
	virtual ~MultiListObjectClass();
	void *ListNode;
};

class MultiListNodeClass
{
public:
	void *Prev;
	void *Next;
	void *NextList;
	void *Object;
	void *List;
};

class GenericMultiListClass
{
public:
	MultiListNodeClass Head;

	virtual ~GenericMultiListClass();

protected:
	MultiListObjectClass *Internal_Remove_List_Head();
};

class Rva00144690 : public GenericMultiListClass
{
public:
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
