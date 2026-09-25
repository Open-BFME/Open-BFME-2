// cl: /arch:SSE /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// ?Unregister_Mesh_Type@DX8MeshRendererClass@@QAEXPAVMeshModelClass@@@Z at
// retail 0x001445E0 (54B). Dedicated TU: BFME1's dx8renderer.cpp body also
// removes the model from _RegisteredMeshList and deletes the GapFiller, but
// retail is trimmed to just the PolygonRendererList drain, so the body
// cannot ride the donor TU verbatim.
//
// Minimal TU-local hierarchy copied from the matched Clear_Pending_Delete_
// Lists TU in this folder: MultiListClass<T>::Remove_Head is the
// header-inline forwarder to the matched Internal_Remove_List_Head @0x6109A0
// (27B, multilist.cpp); the polygon-renderer list lives at MeshModelClass
// +0x9C; `::delete` lowers to the virtual vf0(0) call plus the matched
// scalar operator delete @0x2FD60, the same idiom as the matched Invalidate
// and Clear loops. No pins needed (both callees already matched).

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

class DX8PolygonRendererClass : public MultiListObjectClass
{
public:
	virtual ~DX8PolygonRendererClass();
};

class MeshModelClass
{
public:
	char _pad[0x9C];
	MultiListClass<DX8PolygonRendererClass> PolygonRendererList;
};

class DX8MeshRendererClass
{
public:
	void Unregister_Mesh_Type(MeshModelClass *mmc);
};

// ?Unregister_Mesh_Type@DX8MeshRendererClass@@QAEXPAVMeshModelClass@@@Z
void DX8MeshRendererClass::Unregister_Mesh_Type(MeshModelClass *mmc)
{
	while (DX8PolygonRendererClass *n = mmc->PolygonRendererList.Remove_Head()) {
		::delete n;
	}
}
