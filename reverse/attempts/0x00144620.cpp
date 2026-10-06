// ?Invalidate_FVF_Category_Container_List@@YAXAAVFVFCategoryList@@@Z
// partial score=0.7901 date=2026-10-06
// cl: /G7 /DNDEBUG /MD /EHsc
// ?Invalidate@DX8MeshRendererClass@@QAEX_N@Z @ 0x00145FA0 (265B).
// BFME2 port of the BFME1 thunk (reference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2/
// DX8MeshRendererClass_Invalidate_Thunk.cpp, itself the ZH dx8renderer.cpp body).
// Retail 0x00145FA0 (265 bytes) vs BFME1 0x00947BD0 (289 bytes); the 24-byte delta is the
// dropped _RegisteredMeshList.Reset_List() prologue plus the delete-idiom swap below.
// Proven BFME2 deltas from the retail body:
// - No RegisteredMeshList reset: retail opens with the rigid-list loop. The MeshModelClass
//   list unlink block (BFME1 0xD47BD0-0xD47C16) is gone, so its decls are not carried.
// - Container deletes dispatch the slot-0 destructor with the no-free flag and free its
//   result (push 0 / call [vf0] / push eax / call operator delete); a folded `delete`
//   passes flag 1 with no separate free (probe-proven in build/probe_invalidate_delete.*).
//   The TU-local scalarDeletingDestructor stand-in carries that shape; the true BFME2
//   slot-0 name is unknown (same vf0(0)+free family as Return_File and TeamFactoryClear).
// - Null list elements free 0 through the same idiom (conditional operator delete).
// Layout from retail: rigid vector at this+8 (vptr, vector, max, count), skin list at
// this+0x18, bool shutdown arg (ret 4). Callees Internal_Remove_List_Head (matched
// 0x6109A0) and operator new/delete (matched 0x2FDA0/0x2FD60) resolve with no new pins.

class MultiListNodeClass
{
public:
	MultiListNodeClass *prev;
	MultiListNodeClass *next;
	MultiListNodeClass *next_list;
	void *object;
	void *list;

	MultiListNodeClass()
	{
		prev = next = next_list = 0;
		object = 0;
		list = 0;
	}
};

class MultiListObjectClass
{
	// NOTE: the true BFME2 MultiListObjectClass carries the virtual destructor (matched
	// ??1MultiListObjectClass 0x6109C0), which would occupy vtable slot 0 in any derived
	// replica. Retail destroys the containers through slot 0 with the no-free flag and
	// frees the result (??_G(0)+free shape), so the replica base stays non-polymorphic and
	// the slot-0 shape is named explicitly on DX8FVFCategoryContainer below. The base is
	// only a pointee type here (Remove_Head's return for the static_cast); its destructor
	// is never referenced by this body.
};

class GenericMultiListClass
{
public:
	// Slot-0 stand-in for the deleting destructor: retail destroys both the containers
	// and the category lists themselves by calling this slot with flag 0 and freeing the
	// returned pointer (see the container note below), and the tail Delete_All path calls
	// slot 1 (Resize). The true BFME2 slot-0 member name is unknown, so the TU-local
	// scalarDeletingDestructor shape stands in for it (Return_File / TeamFactoryClear
	// precedent for the vf0(0)+free family). No virtual destructor is declared here on
	// purpose: it would take slot 0 and push Resize to slot 2.
	virtual void *scalarDeletingDestructor(unsigned int flags);
	virtual bool Resize(int size);
	GenericMultiListClass()
	{
		head.next = head.prev = &head;
		head.object = 0;
		head.next_list = 0;
	}

protected:
	MultiListNodeClass head;
	MultiListObjectClass *Internal_Remove_List_Head();
};

class DX8FVFCategoryContainer
{
public:
	// Standalone (deliberately NOT derived from MultiListObjectClass): the true BFME2
	// container derives from it (ZH), but inheriting any polymorphic base would pull that
	// base's destructor into vtable slot 0, while retail destroys the containers through
	// slot 0 with the no-free flag and frees the result (??_G(0)+free shape, same as the
	// lists themselves). The TU-local scalarDeletingDestructor stand-in therefore sits
	// alone at slot 0; the true BFME2 slot-0 member name is unknown (Return_File /
	// TeamFactoryClear precedent for the vf0(0)+free family). The reinterpret_cast in
	// Remove_Head below is free and documents the same modeling choice.
	virtual void *scalarDeletingDestructor(unsigned int flags);
};

class FVFCategoryList : public GenericMultiListClass
{
public:
	DX8FVFCategoryContainer *Remove_Head()
	{
		// reinterpret_cast: the replica container stands alone (see its note), so the
		// base-to-replica conversion cannot be spelled as a static_cast. Free, like the
		// ZH static_cast it replaces.
		return reinterpret_cast<DX8FVFCategoryContainer *>(Internal_Remove_List_Head());
	}
};

class SimpleDynVecFVFLists
{
public:
	virtual ~SimpleDynVecFVFLists();
	virtual bool Resize(int size);

	FVFCategoryList **vector;
	int vector_max;
	int active_count;

	int Count() const
	{
		return active_count;
	}

	FVFCategoryList *operator[](int index)
	{
		return vector[index];
	}

	void Delete_All(bool allow_shrink = true)
	{
		active_count = 0;
		if (allow_shrink && active_count < vector_max / 4) {
			Resize(active_count);
		}
	}
};

class CameraClass;

void *__cdecl operator new(unsigned int size);
void __cdecl operator delete(void *ptr);

class DX8MeshRendererClass
{
public:
	void Invalidate(bool shutdown = false);

protected:
	bool enable_lighting;
	CameraClass *camera;
	SimpleDynVecFVFLists texture_category_container_lists_rigid;
	FVFCategoryList *texture_category_container_list_skin;
};

static __forceinline void Invalidate_FVF_Category_Container_List(FVFCategoryList &list)
{
	DX8FVFCategoryContainer *container;
	container = list.Remove_Head();
	while (container != 0) {
		::operator delete(container->scalarDeletingDestructor(0));
		container = list.Remove_Head();
	}
}

void DX8MeshRendererClass::Invalidate(bool shutdown)
{
	for (int i = 0; i < texture_category_container_lists_rigid.Count(); ++i) {
		Invalidate_FVF_Category_Container_List(*texture_category_container_lists_rigid[i]);
		::operator delete(texture_category_container_lists_rigid[i] != 0 ? texture_category_container_lists_rigid[i]->scalarDeletingDestructor(0) : 0);
	}

	if (texture_category_container_list_skin != 0) {
		Invalidate_FVF_Category_Container_List(*texture_category_container_list_skin);
		::operator delete(texture_category_container_list_skin != 0 ? texture_category_container_list_skin->scalarDeletingDestructor(0) : 0);
		texture_category_container_list_skin = 0;
	}

	if (!shutdown) {
		texture_category_container_list_skin = new FVFCategoryList;
	}

	texture_category_container_lists_rigid.Delete_All();
}
