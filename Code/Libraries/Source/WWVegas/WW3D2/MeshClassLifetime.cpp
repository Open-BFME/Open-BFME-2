// cl: /Ireference/shims/bfme2renderobj /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
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

#include "rendobj.h"

typedef char RenderObjSizeMatchesRetail[(sizeof(RenderObjClass) == 0xC4) ? 1 : -1];

class MeshModelClass : public RefCountClass
{
};

class DecalMeshClass;

// Reduced view: the constructor 0x0013F410 and the 0x228-byte size are
// established by LightEnvironmentClassConstructor.cpp.
class LightEnvironmentClass
{
public:
	LightEnvironmentClass(void);
	~LightEnvironmentClass(void);

private:
	unsigned char Data[0x228];
};

struct MeshRuntimeData;

// upstream identity and virtual interface:
// reference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/mesh.h
class MeshClass : public RenderObjClass
{
public:
	MeshClass(void);
	MeshClass(const MeshClass &src);
	virtual ~MeshClass(void);

	virtual RenderObjClass *Clone(void) const;
	virtual void Render(RenderInfoClass &rinfo);
	virtual float _bfme_get_factor_product(void) const;

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
