// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ??0RTS3DScene@@QAE@XZ retail 0x0006F470..0x0006F796 (806 bytes, EH).
//
// Identity and layout:
// - "RTS3DScene" is the setName string. The donor is Zero Hour's
//   RTS3DScene::RTS3DScene (W3DScene.cpp); the BFME 1 copy is an asm dump.
// - Bases: the pinned scene base ctor 0x00142960 (Rva00142960Base, BFME 2's
//   SimpleSceneClass), then SubsystemInterface at +0x108.
// - Members:
//   - the BfmeRefSceneList at +0x114 (rowed GenericMultiListClass ctor,
//     nothrow, then vtable 0x007C6260);
//   - three LightEnvironmentClass members at +0x164 / +0x38C / +0x5B4.
//
// BFME 2 differences from Zero Hour:
// - the infantry light slots (+0x150) start NULL rather than allocated;
// - a zeroed Vector3 at +0x144;
// - a true byte at +0x7DC;
// - no occluded-material passes;
// - a trailing zero at +0x814.
//
// The heat-vision material, shader and occlusion buffers follow Zero Hour.
#include "ascii_string.h"

void *operator new[](unsigned int size);

typedef int Int;
typedef float Real;
typedef bool Bool;

class RenderObjClass;

class Rva00142960Base
{
public:
	Rva00142960Base();
	virtual ~Rva00142960Base();
	char m_pad004[0x108 - 0x04];
};

class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();
	void setName(AsciiString name);
private:
	char m_padAfterVptr[4];
	AsciiString m_name;
};

struct BfmeSceneListNode
{
	void *prev;
	void *next;
	void *next_list;
	void *object_link;
	void *list;
};

class GenericMultiListClass
{
public:
	GenericMultiListClass() throw();
	virtual ~GenericMultiListClass();
	BfmeSceneListNode head;
};

class BfmeRefSceneList : public GenericMultiListClass
{
public:
	BfmeRefSceneList() {}
	virtual ~BfmeRefSceneList();
};

class LightEnvironmentClass
{
public:
	LightEnvironmentClass();
	~LightEnvironmentClass();
	char m_data[0x228];
};

class RefCountClass
{
public:
	virtual void Delete_This();
	void Release_Ref()
	{
		if (--m_numRefs == 0)
			Delete_This();
	}
	Int m_numRefs;
};

class LightClass : public RefCountClass
{
public:
	enum LightType { POINT = 0, DIRECTIONAL = 1, SPOT = 2 };
	LightClass(LightType type);
	char m_pad08[0x120 - 0x08];
};

class VertexMaterialClass : public RefCountClass
{
public:
	VertexMaterialClass();
	void Set_Ambient(float r, float g, float b);
	void Set_Diffuse(float r, float g, float b);
	void Set_Emissive(float r, float g, float b);
	void Set_Lighting(Bool lighting)
	{
		m_useLighting = lighting;
		m_lightingDirty = true;
	}
	char m_pad08[0x68 - 0x08];
	Bool m_useLighting;									// +0x68
	Bool m_lightingDirty;								// +0x69
};

class ShaderClass
{
public:
	enum DepthCompareType { PASS_NEVER = 0, PASS_LESS, PASS_EQUAL, PASS_LEQUAL };
	enum DepthMaskType { DEPTH_WRITE_DISABLE = 0, DEPTH_WRITE_ENABLE };
	ShaderClass(const ShaderClass &s) : ShaderBits(s.ShaderBits) {}
	void Set_Depth_Compare(DepthCompareType x) { ShaderBits &= ~7; ShaderBits |= x; }
	void Set_Depth_Mask(DepthMaskType x) { ShaderBits &= ~8; ShaderBits |= x << 3; }
	static ShaderClass _PresetAdditiveSolidShader;
	unsigned int ShaderBits;
};

class MaterialPassClass : public RefCountClass
{
public:
	MaterialPassClass();
	// The material setter retail calls is the matpass-range body 0x0013EF10
	// (after Set_Shader 0x0013EEF0); the ledger rows that address as
	// MapObject::setRenderObj and gives Set_Material to 0x0030D3AD, so it is
	// reached through an address-derived pin until those rows are reconciled.
	void rva0013EF10(VertexMaterialClass *mat);
	void Set_Shader(ShaderClass shader);
	char m_pad08[0x38 - 0x08];
};

class W3DShroudMaterialPassClass
{
public:
	W3DShroudMaterialPassClass();
	char m_data[0x3C];
};

class GlobalData
{
public:
	char m_pad000[0x974];
	Int m_maxVisibleTranslucentObjects;					// +0x974
	Int m_maxVisibleOccluderObjects;					// +0x978
	Int m_maxVisibleOccludeeObjects;					// +0x97C
	Int m_maxVisibleNonOccluderOrOccludeeObjects;		// +0x980
};
extern GlobalData *TheWritableGlobalData;
#define TheGlobalData TheWritableGlobalData

struct RTS3DSceneVector3
{
	Real X, Y, Z;
	void Set(Real x, Real y, Real z) { X = x; Y = y; Z = z; }
};

class RTS3DScene : public Rva00142960Base, public SubsystemInterface
{
public:
	RTS3DScene();
	virtual ~RTS3DScene();
private:
	BfmeRefSceneList m_list114;							// +0x114
	Bool m_drawTerrainOnly;								// +0x12C
	LightClass *m_globalLight[4];						// +0x130
	LightClass *m_scratchLight;							// +0x140
	RTS3DSceneVector3 m_144;							// +0x144
	LightClass *m_infantryLight[4];						// +0x150
	Int m_numGlobalLights;								// +0x160
	LightEnvironmentClass m_lightEnv164;				// +0x164
	LightEnvironmentClass m_lightEnv38C;				// +0x38C
	LightEnvironmentClass m_lightEnv5B4;				// +0x5B4
	Bool m_7DC;											// +0x7DC
	W3DShroudMaterialPassClass *m_shroudMaterialPass;	// +0x7E0
	MaterialPassClass *m_heatVisionMaterialPass;		// +0x7E4
	MaterialPassClass *m_heatVisionOnlyPass;			// +0x7E8
	Int m_customPassMode;								// +0x7EC
	Int m_translucentObjectsCount;						// +0x7F0
	RenderObjClass **m_translucentObjectsBuffer;		// +0x7F4
	Int m_occludedObjectsCount;							// +0x7F8
	RenderObjClass **m_potentialOccluders;				// +0x7FC
	RenderObjClass **m_potentialOccludees;				// +0x800
	RenderObjClass **m_nonOccludersOrOccludees;			// +0x804
	Int m_numPotentialOccluders;						// +0x808
	Int m_numPotentialOccludees;						// +0x80C
	Int m_numNonOccluderOrOccludee;						// +0x810
	Int m_814;											// +0x814
};

RTS3DScene::RTS3DScene()
{
	setName("RTS3DScene");
	m_drawTerrainOnly = false;
	m_numGlobalLights = 0;
	m_7DC = true;
	for (Int i = 0; i < 4; i++)
	{
		m_globalLight[i] = 0;
		m_infantryLight[i] = 0;
	}
	m_144.Set(0.0f, 0.0f, 0.0f);
	m_scratchLight = new LightClass(LightClass::DIRECTIONAL);
	m_shroudMaterialPass = new W3DShroudMaterialPassClass();
	m_customPassMode = 0;
	m_heatVisionMaterialPass = new MaterialPassClass();
	m_heatVisionOnlyPass = new MaterialPassClass();
	VertexMaterialClass *heatVisionMtl = new VertexMaterialClass();
	heatVisionMtl->Set_Lighting(true);
	heatVisionMtl->Set_Ambient(0, 0, 0);
	heatVisionMtl->Set_Diffuse(0.02f, 0.01f, 0.00f);
	heatVisionMtl->Set_Emissive(0.5f, 0.2f, 0.0f);
	m_heatVisionMaterialPass->rva0013EF10(heatVisionMtl);
	ShaderClass heatVisionShader = ShaderClass::_PresetAdditiveSolidShader;
	heatVisionShader.Set_Depth_Compare(ShaderClass::PASS_EQUAL);
	m_heatVisionMaterialPass->Set_Shader(heatVisionShader);
	heatVisionMtl->Release_Ref();
	m_heatVisionOnlyPass->rva0013EF10(heatVisionMtl);
	heatVisionShader.Set_Depth_Compare(ShaderClass::PASS_LEQUAL);
	heatVisionShader.Set_Depth_Mask(ShaderClass::DEPTH_WRITE_DISABLE);
	m_heatVisionOnlyPass->Set_Shader(heatVisionShader);

	m_translucentObjectsCount = 0;
	if (TheGlobalData && TheGlobalData->m_maxVisibleTranslucentObjects)
		m_translucentObjectsBuffer = new RenderObjClass *[TheGlobalData->m_maxVisibleTranslucentObjects];
	else
		m_translucentObjectsBuffer = 0;

	m_numPotentialOccluders = 0;
	m_numPotentialOccludees = 0;
	m_numNonOccluderOrOccludee = 0;
	m_occludedObjectsCount = 0;

	m_potentialOccluders = 0;
	m_potentialOccludees = 0;
	m_nonOccludersOrOccludees = 0;

	m_potentialOccluders = new RenderObjClass *[TheGlobalData->m_maxVisibleOccluderObjects];
	m_potentialOccludees = new RenderObjClass *[TheGlobalData->m_maxVisibleOccludeeObjects];
	m_nonOccludersOrOccludees = new RenderObjClass *[TheGlobalData->m_maxVisibleNonOccluderOrOccludeeObjects];
	m_814 = 0;
}
