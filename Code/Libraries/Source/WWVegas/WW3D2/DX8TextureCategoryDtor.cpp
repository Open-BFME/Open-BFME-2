// cl: /G7 /DNDEBUG /MD /EHsc
//
// ??1DX8TextureCategoryClass@@UAE@XZ at retail 0x00144AF0 (212B).
// BFME2 destructor for DX8TextureCategoryClass (vtable 0x007D3508, ctor at
// 0x00144A00 in DX8TextureCategoryCtor.cpp). BFME1 donor is
// reference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2/dx8renderer.cpp
// DX8TextureCategoryClass::~DX8TextureCategoryClass (while Get_Head then
// TheDX8MeshRenderer.Unregister_Mesh_Type plus REF_PTR_RELEASE textures and
// material). Retail differs: TheDX8MeshRenderer is a pointer global at data
// 0x009F363C (null-checked, never dereferenced here because the unregister
// drain is inline), the mesh-model list at +0x9C is drained with ::delete
// (virtual vf0(0) plus scalar delete 0x2FD60, same idiom as the matched
// Unregister at 0x001445E0), material at +0x18 releases via inline refcount,
// then automatic PolygonRendererList at +0x1C (dtor pin 0x00144690),
// RefCountPtr<TextureClass> textures[2] at +0x0C (element dtor 0x0017098D
// via eh vector destructor 0x00629110) and base MultiListObjectClass
// (0x006109C0). Caller is the deleting dtor at 0x001460C0 (slot 0).

class MultiListObjectClass
{
public:
	virtual ~MultiListObjectClass();
private:
	void *ListNode;
};

class MultiListNodeClass
{
public:
	MultiListNodeClass *Prev;
	MultiListNodeClass *Next;
	MultiListNodeClass *NextList;
	void *Object;
	void *List;
};

class GenericMultiListClass
{
public:
	GenericMultiListClass() { Head.Next = Head.Prev = &Head; Head.Object = 0; Head.NextList = 0; }
	virtual ~GenericMultiListClass();
	MultiListNodeClass Head;
protected:
	MultiListObjectClass *Internal_Remove_List_Head();
};

class RefCountClass
{
public:
	void Add_Ref() const { NumRefs++; }
	void Release_Ref() const
	{
		NumRefs--;
		if (NumRefs == 0)
			const_cast<RefCountClass *>(this)->Delete_This();
	}
	virtual void Delete_This();
protected:
	virtual ~RefCountClass() {}
private:
	mutable int NumRefs;
};

class VertexMaterialClass : public RefCountClass
{
};

class TextureClass : public RefCountClass
{
};

template <class T> class RefCountPtr
{
public:
	RefCountPtr() : Referent(0) {}
	~RefCountPtr()
	{
		if (Referent != 0) {
			Referent->Release_Ref();
			Referent = 0;
		}
	}
	T *Referent;
};

class ShaderClass
{
public:
	unsigned int ShaderBits;
};

class DX8PolygonRendererClass;
class MeshModelClass;
class DX8FVFCategoryContainer;

class DX8PolygonRendererList : public GenericMultiListClass
{
public:
	virtual ~DX8PolygonRendererList();
	DX8PolygonRendererClass *Get_Head() const
	{
		if (Head.Next == &Head)
			return 0;
		return (DX8PolygonRendererClass *)Head.Next->Object;
	}
	DX8PolygonRendererClass *Remove_Head()
	{
		return (DX8PolygonRendererClass *)Internal_Remove_List_Head();
	}
};

class DX8PolygonRendererClass : public MultiListObjectClass
{
public:
	virtual ~DX8PolygonRendererClass();
	MeshModelClass *Get_Mesh_Model_Class() { return mmc; }
private:
	MeshModelClass *mmc;
};

class MeshModelClass
{
public:
	char _pad[0x9C];
	DX8PolygonRendererList PolygonRendererList;
};

class DX8MeshRendererClass
{
public:
	void Unregister_Mesh_Type(MeshModelClass *mmc);
};

extern DX8MeshRendererClass *TheDX8MeshRenderer;

class DX8TextureCategoryClass : public MultiListObjectClass
{
public:
	DX8TextureCategoryClass(DX8FVFCategoryContainer *container_, TextureClass **textures_,
		ShaderClass shader_, VertexMaterialClass *material_, int pass_);
	virtual ~DX8TextureCategoryClass();
private:
	int pass;
	RefCountPtr<TextureClass> textures[2];
	ShaderClass shader;
	VertexMaterialClass *material;
	DX8PolygonRendererList PolygonRendererList;
	DX8FVFCategoryContainer *container;
	void *render_task_head;
};

DX8TextureCategoryClass::~DX8TextureCategoryClass()
{
	if (TheDX8MeshRenderer != 0) {
		while (DX8PolygonRendererClass *p_renderer = PolygonRendererList.Get_Head()) {
			MeshModelClass *mmc = p_renderer->Get_Mesh_Model_Class();
			while (DX8PolygonRendererClass *n = mmc->PolygonRendererList.Remove_Head()) {
				::delete n;
			}
		}
	}
	if (material != 0)
		material->Release_Ref();
}
