// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// ??0MeshModelClass@@QAE@XZ at retail 0x001727E0 (335 bytes).
//
// MeshModelClass default constructor. BFME1 donor:
// reference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2/meshmdl.cpp
// (MeshModelClass::MeshModelClass(void)). Same spine as the copy ctor in the
// sibling MeshModelClassCopyCtor TU (same TU context, same /G7 tell): base
// default, NULL members, the inlined GenericMultiList init at +0x9C, the
// global instance-list link through the .data head, then Set_Flag,
// a fresh 0x118 MeshMatDescClass aliased to CurMatDesc and a fresh 0x38
// MaterialInfoClass. Differences from the copy: no that argument, the flag
// or (DIRTY_BOUNDS, from the meshgeom shim's proven Flags at +0x18), and no
// Alternate branch. Trailing int3 pad excluded (335, not 336).
//
// Callees resolve to matched MeshGeometryClass default 0x168F30, the
// MeshMatDescClass default pin 0x15B480, the MaterialInfoClass default pin
// 0x1708D0, the game operator new and the 0x144690 list-dtor pin shared
// with the copy ctor.

typedef unsigned int size_t;
void *__cdecl operator new(size_t bytes);

#define NULL 0

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

class Rva00144690 : public GenericMultiListClass
{
public:
	virtual ~Rva00144690();
};
// The proven DX8PolygonRendererList vtable slot 0 is rowed at 0x00144690.
typedef Rva00144690 DX8PolygonRendererList;

class MeshMatDescClass
{
public:
	MeshMatDescClass();
	virtual ~MeshMatDescClass();

private:
	// Retail news 0x118 for this (proven by the copy ctor's push).
	char m_pad[0x118 - 4];
};

class MaterialInfoClass
{
public:
	MaterialInfoClass();

private:
	// Retail news 0x38 for this (proven by the push below).
	char m_pad[0x38];
};

// Stands in for MeshGeometryClass: W3DMPO (empty) + RefCountClass (vptr +0)
// + MultiListObjectClass (vptr +8); Flags int at +0x18 per the meshgeom
// shim; total 0x8C per the proven sizeof.
class MeshGeometryClass : public W3DMPO, public RefCountClass, public MultiListObjectClass
{
public:
	enum FlagsType
	{
		DIRTY_BOUNDS = 0x00000001
	};

	MeshGeometryClass();
	virtual ~MeshGeometryClass();

	void Set_Flag(FlagsType flag, bool onoff) { if (onoff) { Flags |= flag; } else { Flags &= ~flag; } }

private:
	char m_pad10[0x18 - sizeof(RefCountClass) - sizeof(MultiListObjectClass)];
	int Flags;
	char m_pad1C[0x8C - 0x1C];
};

class GapFillerClass;

class MeshModelClass : public MeshGeometryClass
{
public:
	MeshModelClass();
	virtual ~MeshModelClass();

protected:
	void clone_materials(const MeshModelClass &srcmesh);

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

// Head of the global MeshModelClass instance list (retail .data head).
MeshModelClass *MeshModelListHead;

// ??0MeshModelClass@@QAE@XZ
MeshModelClass::MeshModelClass(void) :
	MeshGeometryClass(),
	DefMatDesc(NULL),
	AlternateMatDesc(NULL),
	CurMatDesc(NULL),
	MatInfo(NULL),
	PrevMeshLink(NULL),
	NextMesh(NULL),
	GapFiller(NULL)
{
	HasBeenInUse = false;

	NextMesh = MeshModelListHead;
	PrevMeshLink = &MeshModelListHead;
	MeshModelListHead = this;
	if (NextMesh != NULL) {
		NextMesh->PrevMeshLink = &NextMesh;
	}

	Set_Flag(DIRTY_BOUNDS, true);

	DefMatDesc = new MeshMatDescClass;
	CurMatDesc = DefMatDesc;

	MatInfo = new MaterialInfoClass;
}
