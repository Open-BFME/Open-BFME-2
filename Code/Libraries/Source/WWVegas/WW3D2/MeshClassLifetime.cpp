// cl: /Ireference/shims/bfme2renderobj /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil
#define BFME_RENDOBJ_MESH_SLOTS
// Retail's slot spellings differ from other units', so this one must not emit the base's table.
#define BFME_RO_DTOR_DECL_ONLY
//
// BFME2 MeshClass lifetime: default ctor 0x001495A0, copy ctor 0x00149680,
// destructor 0x0014A5B0, Clone 0x001498E0 (primary vtable slot 2) and the
// slot-25 factor override 0x00149670.
//
// Target evidence: vtables 0xBD35A8/0xBD35A0 are stored by all three
// lifetime bodies (MeshTextureReplacement.cpp ties 0xBD35A8 to MeshClass);
// slot 2 is the 0x324-byte new + copy-ctor Clone; the base ctors are the
// matched RenderObjClass ctors 0x0013BF00/0x0013B430 and the embedded
// +0xCC member is built by the matched LightEnvironmentClass ctor
// 0x0013F410. The destructor releases Model at +0xC4, then destroys the
// +0xCC member through the empty, ICF-folded destructor at 0x0069E440, then
// chains to ~RenderObjClass 0x0013BE20.
//
// Donor: Open-BFME-1 MeshClassConstructor.cpp / MeshClassBaseDestructor.cpp
// (BFME1 0x0092C270, 0x0092CD00, 0x0092D990). BFME2 removed the W3DMPO base,
// so every member sits four bytes lower, and appended three floats and a
// bool after RuntimeData (+0x314..+0x320, zeroed by both ctors, the bool
// copied by the copy ctor; meaning unknown). mesh.cpp keeps the Zero Hour
// layout of the shared header, which does not fit these bodies.
// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it. Retail links one
// copy, the /O1 body at 0x00001423; this unemitted anchor makes this unit's
// copy that same body, so it no longer loses to retail's at link time.
struct BfmeVciAnchorElem { BfmeVciAnchorElem(); };
#pragma optimize("gsy", on)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
#pragma optimize("", on)

// RefCountClass's inline members and deleting destructor are retail's
// size-optimised bodies: compile them for size, as hlod.cpp does.
#pragma optimize("s", on)
#include "refcount.h"
#pragma optimize("", on)
#include "rendobj.h"

typedef char RenderObjSizeMatchesRetail[(sizeof(RenderObjClass) == 0xC4) ? 1 : -1];

class MeshModelClass : public RefCountClass
{
};

class DecalMeshClass;

// Reduced view: the constructor 0x0013F410 and the 0x228-byte size are
// established by LightEnvironmentClassConstructor.cpp.
#include "LightEnvironmentClass.h"

struct MeshRuntimeData;

// upstream identity and virtual interface:
// reference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/mesh.h
class MeshClass : public RenderObjClass
{
public:
	MeshClass(void);
	MeshClass(const MeshClass &src);
	MeshClass &operator = (const MeshClass &that);
	virtual ~MeshClass(void);

	virtual RenderObjClass *Clone(void) const;
	virtual void Render(RenderInfoClass &rinfo);
	virtual float _bfme_get_factor_product(void) const;

	// Retail's table 0x00BD35A8 holds these bodies. The view is a step: no canonical MeshClass header exists yet, with
	// private copies across the units, and registering one and adopting it here is what retires this list.
	virtual int Class_ID(void) const { return 0; }	// slot 3: the mesh class id, against the base's -1
	virtual int _bfme_ro_v2(void) const { return (int)this; }	// slot 4, 0x00181450: returns this; the name is a placeholder
	virtual int _bfme_ro_v3(void) const { return (int)this; }	// slot 5, 0x00181450: returns this; the name is a placeholder
	virtual const char *Get_Name(void) const;
	virtual void Set_Name(const char *name);
	virtual int Get_Num_Polys(void) const;
	virtual int _bfme_ro_v9(void) const;
	virtual bool Cast_Ray(RayCollisionTestClass &raytest);
	virtual bool Intersect_AABox(AABoxIntersectionTestClass &boxtest);
	virtual void Get_Obj_Space_Bounding_Box(AABoxClass &box) const;
	virtual MaterialInfoClass *Get_Material_Info(void);
	virtual void Scale(float scale);
	virtual void Scale(float scalex, float scaley, float scalez);
	virtual int Get_Sort_Level(void) const;
	virtual void Set_Sort_Level(int level);
	virtual void Replace_Texture(const RefCountPtr<TextureClass> &texture, const RefCountPtr<TextureClass> &replacement);
	virtual void Recolor_Prototype(const Rva0013101E &options);
	virtual void RecolorHouseColor(const Rva0013101E &options, const char *name);

private:
	MeshModelClass *Model;                  // +0x0C4
	DecalMeshClass *DecalMesh;              // +0x0C8
	LightEnvironmentClass LightEnvironment; // +0x0CC .. +0x2F3
	float AlphaOverride;                    // +0x2F4
	float MaterialPassEmissiveOverride;     // +0x2F8
	float MaterialPassAlphaOverride;        // +0x2FC
	int BaseVertexOffset;                   // +0x300
	MeshClass *NextVisibleSkin;             // +0x304
	unsigned int MeshDebugId;               // +0x308
	bool IsDisabledByDebugger;              // +0x30C
	MeshRuntimeData *RuntimeData;           // +0x310
	Vector3 _bfme_unk_314;                  // +0x314
	bool _bfme_unk_320;                     // +0x320
protected:
	// retail vftable slot: the rowed override
	virtual void Update_Cached_Bounding_Volumes() const;
public:
	// retail vftable slot: the rowed override
	virtual void Get_Obj_Space_Bounding_Sphere(SphereClass &) const;
};

typedef char VerifyMeshClassSize[(sizeof(MeshClass) == 0x324) ? 1 : -1];

static unsigned int MeshDebugIdCount;

MeshClass::MeshClass(void) :
	Model(NULL),
	DecalMesh(NULL),
	LightEnvironment(),
	AlphaOverride(1.0f),
	MaterialPassEmissiveOverride(1.0f),
	MaterialPassAlphaOverride(1.0f),
	BaseVertexOffset(0),
	NextVisibleSkin(NULL),
	MeshDebugId(MeshDebugIdCount++),
	IsDisabledByDebugger(false),
	RuntimeData(NULL),
	_bfme_unk_314(0.0f, 0.0f, 0.0f),
	_bfme_unk_320(false)
{
}

MeshClass::MeshClass(const MeshClass &that) :
	RenderObjClass(that),
	Model(NULL),
	DecalMesh(NULL),
	LightEnvironment(),
	AlphaOverride(1.0f),
	MaterialPassEmissiveOverride(1.0f),
	MaterialPassAlphaOverride(1.0f),
	BaseVertexOffset(that.BaseVertexOffset),
	NextVisibleSkin(NULL),
	MeshDebugId(MeshDebugIdCount++),
	IsDisabledByDebugger(false),
	RuntimeData(NULL),
	_bfme_unk_314(0.0f, 0.0f, 0.0f),
	_bfme_unk_320(that._bfme_unk_320)
{
	REF_PTR_SET(Model, that.Model);
}

// Retail 0x001497A0 (263B, ret 4), right after the copy constructor: the
// Zero Hour mesh.cpp assignment (base assignment, shared Model, vertex
// offset, decal mesh dropped, light environment left alone) with BFME2's
// clearing of DecalMesh by plain store and its copies of the remaining
// members, including the ref-counted +0x304 pointer and the appended
// +0x314..+0x320 fields.
MeshClass &MeshClass::operator = (const MeshClass &that)
{
	if (this != &that) {
		RenderObjClass::operator = (that);
		REF_PTR_SET(Model, that.Model);
		BaseVertexOffset = that.BaseVertexOffset;
		DecalMesh = NULL;
		IsDisabledByDebugger = that.IsDisabledByDebugger;
		MeshDebugId = that.MeshDebugId;
		REF_PTR_SET(NextVisibleSkin, that.NextVisibleSkin);
		AlphaOverride = that.AlphaOverride;
		MaterialPassAlphaOverride = that.MaterialPassAlphaOverride;
		MaterialPassEmissiveOverride = that.MaterialPassEmissiveOverride;
		RuntimeData = that.RuntimeData;
		_bfme_unk_314 = that._bfme_unk_314;
		_bfme_unk_320 = that._bfme_unk_320;
	}
	return *this;
}

MeshClass::~MeshClass(void)
{
	REF_PTR_RELEASE(Model);
}

RenderObjClass *MeshClass::Clone(void) const
{
	return new MeshClass(*this);
}

float MeshClass::_bfme_get_factor_product(void) const
{
	return RenderObjClass::_bfme_get_factor_product() * AlphaOverride;
}
