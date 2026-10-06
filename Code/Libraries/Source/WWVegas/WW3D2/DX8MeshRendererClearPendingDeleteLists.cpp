// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// ?Clear_Pending_Delete_Lists@DX8MeshRendererClass@@QAEXXZ at retail
// 0x00144580 (91B). Dedicated TU: retail keeps the two pending-delete lists
// as MEMBERS at +0x1C (TextureCategoryList) and +0x34 (FVFCategoryList) —
// BFME1's dx8renderer.h declares them as members too — while the Code/
// dx8renderer.cpp TU builds against the ZH header (file-static lists, no
// such members), so this body cannot live there.
//
// Minimal TU-local hierarchy (documented stand-ins, real manglings only
// where the linker must resolve): MultiListClass<T>::Remove_Head is the
// header-inline forwarder to the matched Internal_Remove_List_Head @0x6109A0
// (27B, multilist.cpp); `delete` lowers to the virtual vf0(0) call plus the
// matched scalar operator delete @0x2FD60, the same idiom as the matched
// Invalidate loops. No pins needed (both callees already matched).

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
	void *Vptr;
	MultiListNodeClass Head;

protected:
	MultiListObjectClass *Internal_Remove_List_Head();
};

template <class ObjectType>
class MultiListClass : public GenericMultiListClass
{
public:
	ObjectType *Remove_Head()
	{
		return (ObjectType *)Internal_Remove_List_Head();
	}
};

class DX8TextureCategoryClass : public MultiListObjectClass
{
public:
	virtual ~DX8TextureCategoryClass();
};

class DX8FVFCategoryContainer : public MultiListObjectClass
{
public:
	virtual ~DX8FVFCategoryContainer();
};

class DX8MeshRendererClass
{
public:
	void Shutdown();
	void Clear_Pending_Delete_Lists();
	void Invalidate(bool shutdown);

private:
	char _pad0[0x1C];
public:
	MultiListClass<DX8TextureCategoryClass> texture_category_delete_list;
	MultiListClass<DX8FVFCategoryContainer> fvf_category_container_delete_list;
};

// ?Clear_Pending_Delete_Lists@DX8MeshRendererClass@@QAEXXZ
void DX8MeshRendererClass::Clear_Pending_Delete_Lists()
{
	while (DX8TextureCategoryClass *category = texture_category_delete_list.Remove_Head()) {
		::delete category;
	}
	while (DX8FVFCategoryContainer *container = fvf_category_container_delete_list.Remove_Head()) {
		::delete container;
	}
}

// ?Shutdown@DX8MeshRendererClass@@QAEXXZ at retail 0x00148010 (18B):
// Invalidate(true) plus a Clear_Pending_Delete_Lists tail-call. BFME1's
// Shutdown verbatim minus the _TempVertexBuffer/_TempNormalBuffer Clear
// pair, which retail does not emit. Invalidate resolves via the ledger row
// (same-TU Clear needs no pin).
void DX8MeshRendererClass::Shutdown()
{
	Invalidate(true);
	Clear_Pending_Delete_Lists();
}
