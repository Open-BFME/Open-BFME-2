// cl: /DNDEBUG /MD /EHsc /arch:SSE /G7 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/shims/sweep
//
// MeshClass::Render (MeshClass vtable 0xBD35A8), 0x0014BB90, and the two
// RefCountPtr Create_Peek instances it calls (0x0014BA40, 0x0014BAB0).
//
// Donor: Zero Hour mesh.cpp MeshClass::Render
// (reference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/
// Code/Libraries/Source/WWVegas/WW3D2/mesh.cpp). BFME2 keeps its static sort,
// frustum, lighting, base-pass, material-pass and skin structure and adds:
// a sort-level override (+0x98, inherited from the container when negative),
// a skin exemption from the frustum rejection, a lazily registered polygon
// renderer list, an FX-shader material path that hands the mesh to
// TheFXShaderRenderer under the material's rendering method, a shadow-map
// early out and an emissive-only draw filter. No decal or renderer-debugger
// tail.
//
// Target evidence: WorldBuilder's debug build of this body (0x009C9990)
// calls every inline helper out of line, which gives the call order and the
// helper boundaries; its assert strings name FXShaderRenderer::
// Add_Rendering_Task (0x00174AAD here), RenderInfoClass::Pop_Rendering_Method,
// RefCountPtr<class FXShader::RenderingMethod>, TheFXShaderRenderer,
// Model->Is_FX_Shader_Material() and WW3D::Is_Currently_Rendering_Shadow_Map()
// (the byte at 0x00DEC404, set around W3DShadowMapManager::UpdateShadowMap).
// The RenderInfoClass view below is the BFME2 layout rinfo.cpp defines
// (pass array +0x30, count +0xB0, override flag stack +0xB8 indexed by
// +0x138, rendering-method stack vector at +0x13C), reduced to what Render
// touches.

#include "colmath.h"
#include "colmathinlines.h"
#include "frustum.h"
#include "aabox.h"

namespace _STL {
template <class _Tp> class allocator;
template <class _Tp, class _Alloc> class vector;
}

class DummyPtrType;

// The SAGE smart pointer: Create_Peek takes a reference through operator=
// and returns a copy, so its body (WorldBuilder 0x009CD400) is ctor(0),
// operator=(T *), copy ctor and dtor.
template <class T>
class RefCountPtr
{
public:
	friend RefCountPtr<T> Create_Peek(T *t)
	{
		RefCountPtr<T> ptr(0);
		ptr = t;
		return ptr;
	}

	RefCountPtr(DummyPtrType *) : Referent(0) {}
	RefCountPtr(const RefCountPtr &rhs) : Referent(rhs.Referent)
	{
		if (Referent) {
			Referent->Add_Ref();
		}
	}
	~RefCountPtr(void)
	{
		if (Referent) {
			Referent->Release_Ref();
		}
	}
	const RefCountPtr<T> &operator =(T *object)
	{
		if (object) {
			object->Add_Ref();
		}
		if (Referent) {
			Referent->Release_Ref();
		}
		Referent = object;
		return *this;
	}

private:
	T *Referent;
};

class RefCountClass
{
public:
	virtual void Delete_This(void);
	void Add_Ref(void) { NumRefs++; }
	void Release_Ref(void) { NumRefs--; if (NumRefs == 0) Delete_This(); }

protected:
	int NumRefs;
};

namespace FXShader {
class RenderingMethod : public RefCountClass
{
};
}

class FXShaderSetup : public FXShader::RenderingMethod
{
};

typedef _STL::vector<RefCountPtr<FXShader::RenderingMethod>, _STL::allocator<RefCountPtr<FXShader::RenderingMethod> > > RenderingMethodStackType;

class LightEnvironmentClass;

class MaterialPassClass
{
public:
	bool Is_Enabled_On_Translucent_Meshes(void) { return EnableOnTranslucentMeshes; }

private:
	char _bfme_unk_00[0x30];
	bool EnableOnTranslucentMeshes;	// +0x30
};

class CameraClass
{
public:
	const FrustumClass &Get_Frustum(void) const { Update_Frustum(); return Frustum; }

protected:
	void Update_Frustum(void) const;

	char _bfme_unk_00[0x100];
	mutable FrustumClass Frustum;	// +0x100
};

class RenderInfoClass
{
public:
	enum RINFO_OVERRIDE_FLAGS {
		RINFO_OVERRIDE_DEFAULT = 0x0000,
		RINFO_OVERRIDE_FORCE_TWO_SIDED = 0x0001,
		RINFO_OVERRIDE_FORCE_SORTING = 0x0002,
		RINFO_OVERRIDE_ADDITIONAL_PASSES_ONLY = 0x0004,
		RINFO_OVERRIDE_SHADOW_RENDERING = 0x0008
	};

	int Additional_Pass_Count(void);
	MaterialPassClass *Peek_Additional_Pass(int i);
	RINFO_OVERRIDE_FLAGS &Current_Override_Flags(void);
	void Push_Rendering_Method(RefCountPtr<FXShader::RenderingMethod> method);
	void Pop_Rendering_Method(void);
	const RenderingMethodStackType &Get_Rendering_Method_Stack(void) const;
	Vector3 Get_Fog_Color(void) const { return FogColor; }

	CameraClass &Camera;
	float fog_scale;	// +0x04; the fog float names follow rinfo.cpp
	Vector3 FogColor;	// +0x08; WorldBuilder copies it to the mesh by value
	float fog_start;	// +0x14
	float fog_end;	// +0x18
	float alphaOverride;	// +0x1C
	float materialPassAlphaOverride;	// +0x20
	float materialPassEmissiveOverride;	// +0x24
	LightEnvironmentClass *light_environment;	// +0x28
};

class VertexMaterialClass
{
public:
	void Get_Emissive(Vector3 *set_color) const;
};

class MaterialInfoClass
{
public:
	VertexMaterialClass *Peek_Vertex_Material(int index) const;
};

class ShaderClass
{
public:
	enum AlphaTestType { ALPHATEST_DISABLE = 0, ALPHATEST_ENABLE };
	enum SrcBlendFuncType { SRCBLEND_ZERO = 0, SRCBLEND_ONE, SRCBLEND_SRC_ALPHA };

	// BFME2 field positions (retail masks 0xC0000 and 0xC000).
	AlphaTestType Get_Alpha_Test(void) const { return (AlphaTestType)((ShaderBits & 0xC0000) >> 18); }
	SrcBlendFuncType Get_Src_Blend_Func(void) const { return (SrcBlendFuncType)((ShaderBits & 0xC000) >> 14); }

private:
	unsigned long ShaderBits;
};

class MeshMatDescClass
{
public:
	ShaderClass Get_Single_Shader(int pass = 0) const { return Shader[pass]; }
	FXShaderSetup *Peek_FX_Shader(int pass) const { return FXShader[pass]; }
	bool Has_FX_Shader(int pass) const { return FXShader[pass] != 0 || FXShaderArray[pass] != 0; }

private:
	enum { MAX_PASSES = 4 };
	char _bfme_unk_00[0x98];
	ShaderClass Shader[MAX_PASSES];	// +0x98
	void *Material[MAX_PASSES];	// +0xA8
	FXShaderSetup *FXShader[MAX_PASSES];	// +0xB8
	char _bfme_unk_c8[0x108 - 0xC8];
	void *FXShaderArray[MAX_PASSES];	// +0x108; ShareBufferClass<FXShaderSetup *>
};

class DX8FVFCategoryContainer;

class DX8PolygonRendererClass;
class MeshClass;

class DX8TextureCategoryClass
{
public:
	void Add_Render_Task(DX8PolygonRendererClass *p_renderer, MeshClass *p_mesh);
	DX8FVFCategoryContainer *Get_Container(void) { return container; }

private:
	char _bfme_unk_00[0x34];
	DX8FVFCategoryContainer *container;	// +0x34
};

class MultiListObjectClass
{
public:
	virtual ~MultiListObjectClass(void);

private:
	void *ListNode;
};

class DX8PolygonRendererClass : public MultiListObjectClass
{
public:
	DX8TextureCategoryClass *Get_Texture_Category(void) { return texture_category; }

private:
	char _bfme_unk_08[4];
	DX8TextureCategoryClass *texture_category;	// +0x0C
};

class MultiListNodeClass
{
public:
	MultiListNodeClass *Prev;
	MultiListNodeClass *Next;
	MultiListNodeClass *NextList;
	MultiListObjectClass *Object;
	void *List;
};

class DX8PolygonRendererList
{
public:
	virtual ~DX8PolygonRendererList(void);

	DX8PolygonRendererClass *Peek_Head(void)
	{
		if (Head.Next == &Head) {
			return 0;
		}
		return (DX8PolygonRendererClass *)Head.Next->Object;
	}

	MultiListNodeClass Head;
};

class DX8PolygonRendererListIterator
{
public:
	DX8PolygonRendererListIterator(DX8PolygonRendererList *list) : List(list) { CurNode = List->Head.Next; }
	bool Is_Done(void) { return CurNode == &List->Head; }
	void Next(void) { CurNode = CurNode->Next; }
	DX8PolygonRendererClass *Peek_Obj(void) { return (DX8PolygonRendererClass *)CurNode->Object; }

private:
	DX8PolygonRendererList *List;
	MultiListNodeClass *CurNode;
};

class MeshModelClass
{
public:
	enum FlagsType { SKIN = 0x00000400 };

	int Get_Flag(FlagsType flag) { return Flags & flag; }
	int Get_Sort_Level(void) const { return SortLevel; }
	ShaderClass Get_Single_Shader(int pass = 0) const { return CurMatDesc->Get_Single_Shader(pass); }
	FXShaderSetup *Peek_FX_Shader(int pass) const { return CurMatDesc->Peek_FX_Shader(pass); }
	bool Is_FX_Shader_Material(void) const { return CurMatDesc->Has_FX_Shader(0); }
	bool rva00171720(void);
	void Register_For_Rendering(void);

	char _bfme_unk_00[0x18];
	int Flags;	// +0x18
	signed char SortLevel;	// +0x1C
	char _bfme_unk_1d[0x94 - 0x1D];
	MeshMatDescClass *CurMatDesc;	// +0x94
	MaterialInfoClass *MatInfo;	// +0x98
	DX8PolygonRendererList PolygonRendererList;	// +0x9C
};

class MeshClass;

class DX8FVFCategoryContainer
{
public:
	virtual void _bfme_slot_00(void);
	virtual void _bfme_slot_01(void);
	virtual void _bfme_slot_02(void);
	virtual void _bfme_slot_03(void);
	virtual void _bfme_slot_04(void);
	virtual void Add_Delayed_Visible_Material_Pass(MaterialPassClass *pass, MeshClass *mesh) = 0;	// +0x14
	void Add_Visible_Material_Pass(MaterialPassClass *pass, MeshClass *mesh);
};

class DX8SkinFVFCategoryContainer : public DX8FVFCategoryContainer
{
public:
	void Add_Visible_Skin(MeshClass *mesh);
};

class RenderObjClass;

class WW3D
{
public:
	static bool Are_Static_Sort_Lists_Enabled(void) { return AreStaticSortListsEnabled; }
	static bool Is_Currently_Rendering_Shadow_Map(void) { return IsCurrentlyRenderingShadowMap; }
	static void Add_To_Static_Sort_List(RenderObjClass *robj, unsigned int sort_level);

private:
	static bool AreStaticSortListsEnabled;
	static bool IsCurrentlyRenderingShadowMap;
};

class DX8Wrapper
{
public:
	static bool Get_Fog_Enable(void) { return FogEnable; }

protected:
	static bool FogEnable;
};

extern bool bfmeOnlyEmissiveDraws;

#define VSLOTS_10(p) \
	virtual void _bfme_slot_##p##0(void); virtual void _bfme_slot_##p##1(void); \
	virtual void _bfme_slot_##p##2(void); virtual void _bfme_slot_##p##3(void); \
	virtual void _bfme_slot_##p##4(void); virtual void _bfme_slot_##p##5(void); \
	virtual void _bfme_slot_##p##6(void); virtual void _bfme_slot_##p##7(void); \
	virtual void _bfme_slot_##p##8(void); virtual void _bfme_slot_##p##9(void);

// RenderObjClass, slot positions from retail: Get_Bounding_Box +0x108 (66),
// Is_Not_Hidden_At_All +0x184 (97), Render +0x1A0 (104), Is_Translucent
// +0x1B0 (108).
class RenderObjClass : public RefCountClass
{
public:
	// slot 0 is RefCountClass::Delete_This
	virtual void _bfme_slot_01(void); virtual void _bfme_slot_02(void);
	virtual void _bfme_slot_03(void); virtual void _bfme_slot_04(void);
	virtual void _bfme_slot_05(void); virtual void _bfme_slot_06(void);
	virtual void _bfme_slot_07(void); virtual void _bfme_slot_08(void);
	virtual void _bfme_slot_09(void);
	VSLOTS_10(1) VSLOTS_10(2) VSLOTS_10(3) VSLOTS_10(4) VSLOTS_10(5)
	virtual void _bfme_slot_60(void); virtual void _bfme_slot_61(void);
	virtual void _bfme_slot_62(void); virtual void _bfme_slot_63(void);
	virtual void _bfme_slot_64(void); virtual void _bfme_slot_65(void);
	virtual const AABoxClass &Get_Bounding_Box(void) const;	// 66
	virtual void _bfme_slot_67(void); virtual void _bfme_slot_68(void);
	virtual void _bfme_slot_69(void);
	VSLOTS_10(7) VSLOTS_10(8)
	virtual void _bfme_slot_90(void); virtual void _bfme_slot_91(void);
	virtual void _bfme_slot_92(void); virtual void _bfme_slot_93(void);
	virtual void _bfme_slot_94(void); virtual void _bfme_slot_95(void);
	virtual void _bfme_slot_96(void);
	virtual int Is_Not_Hidden_At_All(void);	// 97
	virtual void _bfme_slot_98(void); virtual void _bfme_slot_99(void);
	virtual void _bfme_slot_100(void); virtual void _bfme_slot_101(void);
	virtual void _bfme_slot_102(void); virtual void _bfme_slot_103(void);
	virtual void Render(RenderInfoClass &rinfo) = 0;	// 104
	virtual void _bfme_slot_105(void); virtual void _bfme_slot_106(void);
	virtual void _bfme_slot_107(void);
	virtual int Is_Translucent(void) const;	// 108

	RenderObjClass *Get_Container(void) const { return Container; }
	int Get_Sort_Level_Override(void) const { return SortLevelOverride; }

protected:
	char _bfme_unk_08[0x7C - 0x08];
	RenderObjClass *Container;	// +0x7C
	char _bfme_unk_80[0x98 - 0x80];
	int SortLevelOverride;	// +0x98; initialized -1
	char _bfme_unk_9c[0xC4 - 0x9C];
};

class MeshClass : public RenderObjClass
{
public:
	virtual void Render(RenderInfoClass &rinfo);

	void Set_Lighting_Environment(LightEnvironmentClass *light_env);
	void Set_Fog_Color(const Vector3 &color) { FogColor = color; }

private:
	MeshModelClass *Model;	// +0xC4
	LightEnvironmentClass *LightEnvironment;	// +0xC8
	char m_localLightEnv[0x2F4 - 0xCC];	// +0xCC
	float m_alphaOverride;	// +0x2F4
	float m_materialPassEmissiveOverride;	// +0x2F8
	float m_materialPassAlphaOverride;	// +0x2FC
	char _bfme_unk_300[0x314 - 0x300];
	Vector3 FogColor;	// +0x314
};

// WorldBuilder's asserts name this FXShaderRenderer and its global
// TheFXShaderRenderer; the ledger still carries the older address-derived
// names for the class (its ctor 0x0017414B, dtor 0x00174753) and the global
// at 0x00DF6F94, so the view keeps them until that rename lands.
class Rva00DF6F94GapFillerContext
{
public:
	void Add_Rendering_Task(RefCountPtr<MeshClass> mesh, const RenderingMethodStackType &renderingMethodStack);
};

extern Rva00DF6F94GapFillerContext *TheMeshGapFillerContext;

// Instantiating the pointers injects their Create_Peek friends.
typedef char RenderingMethodPtrSize[sizeof(RefCountPtr<FXShader::RenderingMethod>)];
typedef char MeshPtrSize[sizeof(RefCountPtr<MeshClass>)];

// WorldBuilder 0x009BC3A0/0x009BC3F0: a box is outside the frustum when, for
// some plane, the box corner farthest against the plane normal lies on the
// plane's positive side.  Retail inlines both; the out-of-line copy at
// 0x001338C0 is the Rva0092CC40BoxOutsideFrustum row.
static __forceinline bool Box_Outside_Plane(const PlaneClass &plane, const AABoxClass &box)
{
	Vector3 negfarpt;
	get_far_extent(plane.N, box.Extent, &negfarpt);
	Vector3::Subtract(box.Center, negfarpt, &negfarpt);
	return CollisionMath::Overlap_Test(plane, negfarpt) == CollisionMath::POS;
}

static __forceinline bool Box_Outside_Frustum(const FrustumClass &frustum, const AABoxClass &box)
{
	for (int i = 0; i < 6; i++) {
		if (Box_Outside_Plane(frustum.Planes[i], box)) {
			return true;
		}
	}
	return false;
}

void MeshClass::Render(RenderInfoClass &rinfo)
{
	if (Is_Not_Hidden_At_All() == false) {
		return;
	}

	int sort_level = Model->Get_Sort_Level();
	int sort_level_override = Get_Sort_Level_Override();
	if (sort_level_override < 0 && Get_Container() != 0) {
		sort_level_override = Get_Container()->Get_Sort_Level_Override();
	}
	if (sort_level_override >= 0) {
		sort_level = sort_level_override;
	}

	if (WW3D::Are_Static_Sort_Lists_Enabled() && sort_level != 0) {
		Set_Lighting_Environment(rinfo.light_environment);
		m_alphaOverride = rinfo.alphaOverride;
		m_materialPassAlphaOverride = rinfo.materialPassAlphaOverride;
		m_materialPassEmissiveOverride = rinfo.materialPassEmissiveOverride;
		WW3D::Add_To_Static_Sort_List(this, sort_level);
		return;
	}

	const FrustumClass &frustum = rinfo.Camera.Get_Frustum();
	if (Box_Outside_Frustum(frustum, Get_Bounding_Box())) {
		if (!Model->Get_Flag(MeshModelClass::SKIN)) {
			return;
		}
	}

	if (!Model->rva00171720()) {
		Model->Register_For_Rendering();
		if (!Model->rva00171720()) {
			return;
		}
	}

	if (Model->Is_FX_Shader_Material()) {
		if (sort_level == 0) {
			Set_Lighting_Environment(rinfo.light_environment);
			m_alphaOverride = rinfo.alphaOverride;
		}
		if (DX8Wrapper::Get_Fog_Enable()) {
			Set_Fog_Color(rinfo.Get_Fog_Color());
		}
		rinfo.Push_Rendering_Method(Create_Peek((FXShader::RenderingMethod *)Model->Peek_FX_Shader(0)));
		TheMeshGapFillerContext->Add_Rendering_Task(Create_Peek(this), rinfo.Get_Rendering_Method_Stack());
		rinfo.Pop_Rendering_Method();
		return;
	}

	if (WW3D::Is_Currently_Rendering_Shadow_Map()) {
		return;
	}

	if (bfmeOnlyEmissiveDraws) {
		bool draw = false;
		if (Model != 0 && Model->MatInfo != 0) {
			Vector3 emissive;
			VertexMaterialClass *material = Model->MatInfo->Peek_Vertex_Material(0);
			if (material != 0) {
				material->Get_Emissive(&emissive);
				if (emissive.X > 0.01f || emissive.Y > 0.01f || emissive.Z > 0.01f) {
					draw = true;
				}
			}
		}
		if (!draw) {
			return;
		}
	}

	bool rendered_something = false;

	if (sort_level == 0) {
		Set_Lighting_Environment(rinfo.light_environment);
		m_alphaOverride = rinfo.alphaOverride;
		m_materialPassAlphaOverride = rinfo.materialPassAlphaOverride;
		m_materialPassEmissiveOverride = rinfo.materialPassEmissiveOverride;
	}

	DX8FVFCategoryContainer *fvf_container = Model->PolygonRendererList.Peek_Head()->Get_Texture_Category()->Get_Container();

	bool render_base_passes = ((rinfo.Current_Override_Flags() & RenderInfoClass::RINFO_OVERRIDE_ADDITIONAL_PASSES_ONLY) == 0);
	bool is_alpha = (Model->Get_Single_Shader().Get_Alpha_Test() == ShaderClass::ALPHATEST_ENABLE) ||
		(Model->Get_Single_Shader().Get_Src_Blend_Func() == ShaderClass::SRCBLEND_SRC_ALPHA);

	if ((rinfo.Current_Override_Flags() & RenderInfoClass::RINFO_OVERRIDE_SHADOW_RENDERING) &&
		(is_alpha == true))
	{
		render_base_passes = true;
	}

	if (render_base_passes) {
		DX8PolygonRendererListIterator it(&(Model->PolygonRendererList));
		while (!it.Is_Done()) {
			DX8PolygonRendererClass *polygon_renderer = it.Peek_Obj();
			polygon_renderer->Get_Texture_Category()->Add_Render_Task(polygon_renderer, this);
			it.Next();
		}
		rendered_something = true;
	}

	for (int i = 0; i < rinfo.Additional_Pass_Count(); i++) {
		MaterialPassClass *matpass = rinfo.Peek_Additional_Pass(i);
		if ((!Is_Translucent()) || (matpass->Is_Enabled_On_Translucent_Meshes())) {
			if (rinfo.Current_Override_Flags() & RenderInfoClass::RINFO_OVERRIDE_ADDITIONAL_PASSES_ONLY) {
				fvf_container->Add_Delayed_Visible_Material_Pass(matpass, this);
			} else {
				fvf_container->Add_Visible_Material_Pass(matpass, this);
			}
			rendered_something = true;
		}
	}

	if (rendered_something && Model->Get_Flag(MeshModelClass::SKIN)) {
		static_cast<DX8SkinFVFCategoryContainer *>(fvf_container)->Add_Visible_Skin(this);
	}
}
