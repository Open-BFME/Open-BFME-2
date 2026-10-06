// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD
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

class Rva001447B0 : public GenericMultiListClass
{
public:
	virtual ~Rva001447B0();
};

// ??1Rva001447B0@@UAE@XZ
Rva001447B0::~Rva001447B0()
{
	while (Head.Next != (void *)&Head) {
		Internal_Remove_List_Head();
	}
}
