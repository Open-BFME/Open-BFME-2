// cl: /DNDEBUG /MD /EHsc /Ob2
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

class MultiListObjectClass;

class MultiListNodeClass
{
public:
	MultiListNodeClass *Prev;
	MultiListNodeClass *Next;
	MultiListNodeClass *NextList;
	MultiListObjectClass *Object;
	void *List;
};

class GenericMultiListClass
{
public:
	virtual ~GenericMultiListClass();

	bool Is_Empty()
	{
		return (Head.Next == &Head);
	}

protected:
	MultiListObjectClass *Internal_Remove_List_Head();

	// NOTE: protected (not WW-private) in this TU-local view: the drain
	// loop below names Head.Next directly so the emptiness check emits a
	// memory compare (cmp [esi+8],edi). The header-inline !Is_Empty()
	// spelling routes the same test through a register instead.
	MultiListNodeClass Head;
};

class BfmeNonRefSceneList : public GenericMultiListClass
{
public:
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
