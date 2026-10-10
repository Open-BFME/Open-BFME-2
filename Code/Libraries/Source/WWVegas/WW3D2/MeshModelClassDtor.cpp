// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// ??1MeshModelClass@@UAE@XZ at retail 0x00172AB0 (306 bytes).
//
// MeshModelClass destructor. BFME1 donor:
// reference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2/meshmdl.cpp
// (MeshModelClass::~MeshModelClass). Same spine as the copy/default TUs
// (same TU context, same /G7 tell) with BFME 2's teardown shape:
//
// - vptr reinstall, then the renderer unregister and the GapFiller delete
//   helper, both guarded by their global availability pointers (pointer
//   null-checks compile to mov+test, which is how the shape proves both
//   globals are pointers; the GapFiller helper ignores its own this and
//   only takes the model, but the caller still passes the global as this).
// - CurMatDesc UV[0] guard around the renderer-teardown helper (UV[0] sits
//   at +0xC per the meshmatdesclayout shim; the helper re-checks it).
// - Reset(0, 0, 0, skin) where skin is the SKIN bit (Flags 0x400, bit 10).
//   The extraction is (Flags >> 10) with a bool mask: cl7.1 keeps `& true`
//   byte-wide (and al,1) while `& 1` widens to and eax,1 and mismatches;
//   micro-probes prove the rule. Reset's fourth parameter and the
//   Reset_Geometry third it forwards to are therefore bool; the chunk
//   reader at 0x18BAB9 passes its own header-attribute bool the same way.
// - MatInfo REF_PTR_RELEASE inlined (decref at +4, slot-0 Delete_This),
//   explicit Def/Alternate deletes (MeshMatDesc has no virtual dtor, so
//   delete emits the dtor call plus the operator delete call), the global
//   instance-list unlink (PrevMeshLink only; NextMesh is left alone),
//   then the automatic PolygonRendererList and base destructions.
//
// Callees: Unregister pin 0x1445E0, GapFiller-helper pin 0x1732E2,
// renderer-teardown pin 0x199FA5, Reset pin 0x171F70, MeshMatDesc dtor pin
// 0x15DC40 (same folded bytes as the BfmeHolderBY row at that address),
// the shared 0x144690 list-dtor pin, the 0x16CCC0 base-dtor pin and the
// matched scalar operator delete.

typedef unsigned int size_t;
void __cdecl operator delete(void *block);

#define NULL 0
#define SKIN_BIT_INDEX 10

class W3DMPO
{
};

class RefCountClass
{
public:
	virtual void Delete_This();
	virtual ~RefCountClass();

private:
	int NumRefs;
};

class MultiListNodeClass
{
public:
	MultiListNodeClass() { Prev = Next = NextList = NULL; Object = NULL; List = NULL; }

	MultiListNodeClass *Prev;
	MultiListNodeClass *Next;
	MultiListNodeClass *NextList;
	void *Object;
	void *List;
};

class MultiListObjectClass
{
public:
	virtual ~MultiListObjectClass();

private:
	MultiListNodeClass *ListNode;
};

class GenericMultiListClass
{
public:
	GenericMultiListClass() { Head.Next = Head.Prev = &Head; Head.Object = NULL; Head.NextList = NULL; }
	virtual ~GenericMultiListClass();

	MultiListNodeClass Head;
};

class DX8PolygonRendererList : public GenericMultiListClass
{
public:
	virtual ~DX8PolygonRendererList();
};

struct UVBufferClass;

class MeshMatDescClass
{
public:
	~MeshMatDescClass();

	int PassCount;
	int VertexCount;
	int PolyCount;
	UVBufferClass *UV[8];
};

class MaterialInfoClass
{
public:
	virtual void Delete_This();
	void Release_Ref() const
	{
		NumRefs--;
		if (NumRefs == 0)
			const_cast<MaterialInfoClass *>(this)->Delete_This();
	}

private:
	mutable int NumRefs;
	char m_pad[0x38 - 8];
};

// Stands in for MeshGeometryClass: W3DMPO (empty) + RefCountClass (vptr +0)
// + MultiListObjectClass (vptr +8); Flags unsigned at +0x18 (the skin-bit
// extraction needs the shr form); total 0x8C per the proven sizeof.
class MeshGeometryClass : public W3DMPO, public RefCountClass, public MultiListObjectClass
{
public:
	MeshGeometryClass();
	virtual ~MeshGeometryClass();

protected:
	char m_pad10[0x18 - sizeof(RefCountClass) - sizeof(MultiListObjectClass)];
	unsigned int Flags;
	char m_pad1C[0x8C - 0x1C];
};

class MeshModelClass;

class DX8MeshRendererClass
{
public:
	void Unregister_Mesh_Type(MeshModelClass *mmc);
};

extern DX8MeshRendererClass *TheDX8MeshRenderer;

// Opaque context behind the GapFiller-delete gate (retail .data pointer).
// The helper takes the model on the stack and ignores its own this, but
// the caller still passes the global through ecx, which is what proves
// the thiscall shape.
class Rva00DF6F94GapFillerContext
{
public:
	void DeleteModelGapFiller(MeshModelClass *mmc);
};

extern Rva00DF6F94GapFillerContext *TheMeshGapFillerContext;

class GapFillerClass;

class MeshModelClass : public MeshGeometryClass
{
public:
	MeshModelClass();
	virtual ~MeshModelClass();

	void Reset(int polycount, int vertcount, int passcount, bool skinned);
	void rva001716E0UnregisterMeshModel();

private:
	MeshMatDescClass *DefMatDesc;
	MeshMatDescClass *AlternateMatDesc;
	MeshMatDescClass *CurMatDesc;
	MaterialInfoClass *MatInfo;
	DX8PolygonRendererList PolygonRendererList;
	MeshModelClass **PrevMeshLink;
	MeshModelClass *NextMesh;
	GapFillerClass *GapFiller;
	bool HasBeenInUse;
};

// 0x00199FA5 is rowed as rva00199FA5 (Rva00199FA5Check.cpp); called by that name.
class Rva00199FA5Rec;
bool __cdecl rva00199FA5(Rva00199FA5Rec *p);

// ??1MeshModelClass@@UAE@XZ
MeshModelClass::~MeshModelClass(void)
{
	if (TheDX8MeshRenderer != NULL) {
		TheDX8MeshRenderer->Unregister_Mesh_Type(this);
	}
	if (TheMeshGapFillerContext != NULL) {
		TheMeshGapFillerContext->DeleteModelGapFiller(this);
	}
	if (CurMatDesc->UV[0] != NULL) {
		rva00199FA5((Rva00199FA5Rec *)CurMatDesc);
	}
	Reset(0, 0, 0, (Flags >> SKIN_BIT_INDEX) & true);
	if (MatInfo != NULL) {
		MatInfo->Release_Ref();
		MatInfo = NULL;
	}
	if (DefMatDesc != NULL) {
		delete DefMatDesc;
	}
	if (AlternateMatDesc != NULL) {
		delete AlternateMatDesc;
	}
	if (PrevMeshLink != NULL) {
		*PrevMeshLink = NextMesh;
		if (NextMesh != NULL) {
			NextMesh->PrevMeshLink = PrevMeshLink;
		}
		PrevMeshLink = NULL;
	}
}

// Retail 0x001716E0, 58 bytes. Renderer/gapfiller/UV unregister head shared
// with the destructor above, as a standalone thiscall method: the two global
// guards, then the CurMatDesc UV[0] guard around the teardown helper.
void MeshModelClass::rva001716E0UnregisterMeshModel(void)
{
	if (TheDX8MeshRenderer != NULL) {
		TheDX8MeshRenderer->Unregister_Mesh_Type(this);
	}
	if (TheMeshGapFillerContext != NULL) {
		TheMeshGapFillerContext->DeleteModelGapFiller(this);
	}
	MeshMatDescClass *curDesc = CurMatDesc;
	if (curDesc->UV[0] != NULL) {
		rva00199FA5((Rva00199FA5Rec *)curDesc);
	}
}
