// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD
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

class FVFCategoryList : public GenericMultiListClass
{
public:
	virtual ~FVFCategoryList();
};

// ??1FVFCategoryList@@UAE@XZ
FVFCategoryList::~FVFCategoryList()
{
	while (Head.Next != (void *)&Head) {
		Internal_Remove_List_Head();
	}
}
