// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// dxsdk
// platformsdk
//
// ?flushDecals@W3DProjectedShadowManager@@QAEXW4ShadowType@@PAVW3DShadowTexture@@1H@Z
// retail 0x00109E11..0x0010A736 (2341 B), __EH_prolog frame, thiscall, ret 0x10.
//
// W3DProjectedShadowManager::flushDecals: draws the queued decal batch.
// Donor: Zero Hour / BFME 1 W3DProjectedShadow.cpp flushDecals (static
// identity mWorld, empty-batch early out, PRELIT_DIFFUSE material, stage 0
// texture, the SHADOW_DECAL / ALPHA / ADDITIVE preset shader switch and the
// batch counter reset). BFME 2 deltas read from retail:
//   * the batch counters and the decal vertex/index buffers are manager
//     members (+0x254..+0x270) drawn through DX8Wrapper::Set_Index_Buffer
//     0x0011D530, Set_Vertex_Buffer 0x0011D4A0, the inlined Set_World_Identity
//     and Draw_Triangles 0x00120620 between two bfmeSetProjectionDepthBias
//     0x0011F1C0 calls (9.0 then 0.0) instead of the raw D3D device;
//   * two more arguments: a second W3DShadowTexture bound to stage 1 with
//     fixed shader bits per type (types 0x400 0x800 0x2000 share the alpha /
//     additive arms) and a stencil mode used by type 0x1000, which sets the
//     stencil func/pass render states (and an alpha test from GlobalData
//     +0x9A7/+0x9A8 when that flag is set) and binds shader presets from the
//     unnamed ShaderClass table at 0x00DB5E98 (+0x40 +0x44 +0x48);
//   * with fog enabled the current shader gets Enable_Fog("HardwareFog")
//     unless the stencil path already bound its own shader.
// W3DShadowTexture::getTexture is the rowed placeholder rva001085B4
// (returns the texture handle at +0x30 by value); its temporaries unwind
// through ??1AssetReference / ??1BFME2TextureRef (0x0017098D). Callers: 13
// REL32 sites in 0x0010B3B6..0x0010E465 pass (shadow+0x34 type, texture,
// second texture, mode). WorldBuilder twin 0x008C8720 (callgraph match)
// has the same switch arms and shader constants.

#include <d3d9.h>

typedef float Real;
typedef bool Bool;
typedef int Int;



// The device keeps its D3D8 type name but is a Direct3D 9 device
// (SetRenderState, vtable slot 57). The wrapper's state parameter is the
// DWORD its decorations carry (?Get_DX8_Render_State_Value_Name@...KI@Z).
struct IDirect3DDevice8;

class StringClass
{
public:
	StringClass(int initial_len = 0, bool hint_temporary = false);
	~StringClass() { Free_String(); }
private:
	char *m_Buffer;
private:
	void Free_String();
};

#include "../../../../../Libraries/Source/WWVegas/WWMath/Vector4Data.h"

class Matrix4
{
public:
	__forceinline explicit Matrix4(bool identity) { if (identity) Make_Identity(); }
	__forceinline void Make_Identity(void)
	{
		Row[0].Set(1.0, 0.0, 0.0, 0.0);
		Row[1].Set(0.0, 1.0, 0.0, 0.0);
		Row[2].Set(0.0, 0.0, 1.0, 0.0);
		Row[3].Set(0.0, 0.0, 0.0, 1.0);
	}
	Vector4 Row[4];
};

class VertexMaterialClass
{
public:
	enum PresetType { PRELIT_DIFFUSE = 0 };
	static VertexMaterialClass *Get_Preset(PresetType type);
	virtual void Delete_This(void);
	void Add_Ref(void) { NumRefs++; }
	void Release_Ref(void) { NumRefs--; if (NumRefs == 0) Delete_This(); }
private:
	int NumRefs;
};

#define REF_PTR_RELEASE(x)		{ if (x) x->Release_Ref(); x = 0; }

// Zero Hour shader.h's SHADE_CNST field packing (SHIFT_DEPTHCOMPARE 0, DEPTHMASK 3, COLORMASK 4,
// DSTBLEND 5, FOG 8, PRIGRADIENT 10, SECGRADIENT 13, SRCBLEND 14, TEXTURING 16, ALPHATEST 18,
// CULLMODE 19, POSTDETAILCOLORFUNC 20, POSTDETAILALPHAFUNC 24). The shader words below are field
// packings, not image addresses.
#define BFME_SHADE_CNST(depth_compare, depth_mask, color_mask, src_blend, dst_blend, fog, pri_grad, sec_grad, texture, alpha_test, cullmode, post_det_color, post_det_alpha) \
	(	(depth_compare) << 0 | (depth_mask) << 3 | (color_mask) << 4 | (dst_blend) << 5 | (fog) << 8 | \
		(pri_grad) << 10 | (sec_grad) << 13 | (src_blend) << 14 | (texture) << 16 | \
		(alpha_test) << 18 | (cullmode) << 19 | (post_det_color) << 20 | (post_det_alpha) << 24)

class ShaderClass
{
public:
	ShaderClass(void) {}
	ShaderClass(unsigned int bits) : ShaderBits(bits) {}
	void Enable_Fog(const char *source);
	static ShaderClass _PresetAdditiveShader;
	static ShaderClass _PresetAlphaShader;
	static ShaderClass _PresetMultiplicativeShader;
	unsigned int ShaderBits;
protected:
	friend class DX8Wrapper;
	static bool ShaderDirty;	// ?ShaderDirty@ShaderClass@@1_NA (ShaderClassApply.cpp)
};

// BFME 2's stencil-pass shaders: this unit's initialised .data at VA 0x00DB5ED8, 0x00DB5EDC and
// 0x00DB5EE0 (retail words 0x00150023, 0x00155813, 0x005598B3; the 0x00DB5E98 ledger entry spans
// another unit's shader word and header-static name tables -- NONE/HOLD/KILL/SPAWN,
// NONE/CATAPULT_ROCK/TREBUCHET_ROCK, NONE/FRONT_DESTROYED.. -- before and after them).
// Names describe their use in flushDecals (structural, not retail spellings).
ShaderClass BfmeShadowStencilWriteShader(BFME_SHADE_CNST(3, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 1, 0));
ShaderClass BfmeShadowStencilTestShader(BFME_SHADE_CNST(3, 0, 1, 1, 0, 0, 6, 0, 1, 1, 0, 1, 0));
ShaderClass BfmeShadowStencilAlphaTestShader(BFME_SHADE_CNST(3, 0, 1, 2, 5, 0, 6, 0, 1, 1, 0, 5, 0));

class TextureBaseClass
{
public:
	void Release_Ref(void);
};

struct BFME2TextureRef
{
	TextureBaseClass *Ptr;
	BFME2TextureRef(TextureBaseClass *textureBase) : Ptr(textureBase) {}
	~BFME2TextureRef() { if (Ptr) Ptr->Release_Ref(); }
};
void BFME2Set_Texture(unsigned int stage, const BFME2TextureRef &texture);

// W3DShadowTexture::getTexture returns the texture handle by value under the
// rowed placeholder type AssetReference; both names are TU views of one
// RefCountPtr<TextureClass>, so the returned temporary binds to Set_Texture's
// reference directly (retail builds it in the dead argument slot).
class AssetReference : public BFME2TextureRef
{
public:
	AssetReference(const AssetReference &that);
};

class W3DShadowTexture;
class Rva001085B4
{
public:
	AssetReference rva001085B4();
};

extern unsigned number_of_DX8_calls;

class WW3D
{
public:
	static bool Is_Snapshot_Activated(void) { return SnapshotActivated; }
private:
	static bool SnapshotActivated;
};

class VertexBufferClass;
class IndexBufferClass;

// DX8Wrapper::render_state (VA 0x00DEE5D8, dx8wrapper.cpp): Zero Hour's
// RenderStateStruct (bfmestages/dx8wrapper.h) -- shader, material,
// Textures[16], Lights[4] and LightEnable[4], then world at +0x1EC
// (0x00DEE7C4).
struct RenderStateStruct
{
	ShaderClass shader;
	VertexMaterialClass *material;
	unsigned char m_pad08[0x1EC - 0x08];
	Matrix4 world;
};

class DX8Wrapper
{
public:
	enum ChangedStates {
		WORLD_CHANGED = 1 << 0,
		MATERIAL_CHANGED = 1 << 14,
		SHADER_CHANGED = 1 << 15,
		WORLD_IDENTITY = 1 << 18
	};
	static bool Has_Stencil(void);
	static bool Get_Fog_Enable(void) { return FogEnable; }
	static void Apply_Render_State_Changes(void);
	static void Get_DX8_Render_State_Value_Name(StringClass &name, unsigned long state, unsigned value);
	static void Set_Vertex_Buffer(const VertexBufferClass *vb, unsigned stream);
	static void Set_Index_Buffer(const IndexBufferClass *ib, unsigned short index_base_offset);
	static void Draw_Triangles(unsigned int start_index, unsigned int polygon_count, unsigned int min_vertex_index, unsigned int vertex_count);
	static const ShaderClass &Get_Shader(void) { return render_state.shader; }

	static __forceinline void Set_Material(const VertexMaterialClass *material)
	{
		VertexMaterialClass *vertexMaterial = const_cast<VertexMaterialClass *>(material);
		if (vertexMaterial) vertexMaterial->Add_Ref();
		if (render_state.material) render_state.material->Release_Ref();
		render_state.material = vertexMaterial;
		render_state_changed |= MATERIAL_CHANGED;
	}

	static __forceinline void Set_Shader(const ShaderClass &shader)
	{
		if (!ShaderClass::ShaderDirty && shader.ShaderBits == render_state.shader.ShaderBits)
			return;
		render_state.shader = shader;
		render_state_changed |= SHADER_CHANGED;
		StringClass str;
	}

	static __forceinline void Set_Texture(unsigned stage, const BFME2TextureRef &texture) { BFME2Set_Texture(stage, texture); }

	static __forceinline void Set_DX8_Render_State(unsigned long state, unsigned value)
	{
		if (RenderStates[state] == value) return;
		if (WW3D::Is_Snapshot_Activated()) {
			StringClass value_name(0, true);
			Get_DX8_Render_State_Value_Name(value_name, state, value);
		}
		RenderStates[state] = value;
		reinterpret_cast<IDirect3DDevice9 *>(D3DDevice)->SetRenderState((D3DRENDERSTATETYPE)state, value);
		number_of_DX8_calls++;
		render_state_changes++;
	}

	static __forceinline void Set_World_Identity(void)
	{
		if (render_state_changed & (unsigned)WORLD_IDENTITY) return;
		render_state.world.Make_Identity();
		render_state_changed |= (unsigned)WORLD_CHANGED | (unsigned)WORLD_IDENTITY;
	}

protected:
	static IDirect3DDevice8 *D3DDevice;
	static unsigned RenderStates[256];
	static RenderStateStruct render_state;
	static unsigned render_state_changed;
	static unsigned render_state_changes;
	static bool FogEnable;
};

void bfmeSetProjectionDepthBias(float bias);

class GlobalData
{
public:
	char m_pad[0x9A7];
	Bool m_useSimpleMergeDecals;	// +0x9A7
	Real m_opacityOfSimpleMergeDecals;	// +0x9A8
};
extern GlobalData *TheWritableGlobalData;

enum ShadowType
{
	SHADOW_NONE = 0x0000,
	SHADOW_DECAL = 0x0001,
	SHADOW_VOLUME = 0x0002,
	SHADOW_PROJECTION = 0x0004,
	SHADOW_DYNAMIC_PROJECTION = 0x0008,
	SHADOW_DIRECTIONAL_PROJECTION = 0x0010,
	SHADOW_ALPHA_DECAL = 0x0020,
	SHADOW_ADDITIVE_DECAL = 0x0040,
	SHADOW_BFME_0400 = 0x0400,
	SHADOW_BFME_0800 = 0x0800,
	SHADOW_BFME_1000 = 0x1000,
	SHADOW_BFME_2000 = 0x2000
};

class W3DProjectedShadowManager
{
public:
	void flushDecals(ShadowType type, W3DShadowTexture *texture, W3DShadowTexture *texture2, Int stencilMode);

private:
	char m_pad[0x254];
	VertexBufferClass *m_decalVertexBuffer;	// +0x254
	IndexBufferClass *m_decalIndexBuffer;	// +0x258
	Int m_nShadowDecalVertsInBuf;	// +0x25C
	Int m_nShadowDecalStartBatchVertex;	// +0x260
	Int m_nShadowDecalIndicesInBuf;	// +0x264
	Int m_nShadowDecalStartBatchIndex;	// +0x268
	Int m_nShadowDecalPolysInBatch;	// +0x26C
	Int m_nShadowDecalVertsInBatch;	// +0x270
};

void W3DProjectedShadowManager::flushDecals(ShadowType type, W3DShadowTexture *texture, W3DShadowTexture *w3DShadowTexture, Int stencilMode)
{
	static Matrix4 mWorld(true);	//initialize to identity matrix

	if (m_nShadowDecalVertsInBatch == 0 && m_nShadowDecalPolysInBatch == 0)
	{	//nothing to render
		return;
	}

	VertexMaterialClass *vmat = VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_DIFFUSE);
	DX8Wrapper::Set_Material(vmat);
	REF_PTR_RELEASE(vmat);
	DX8Wrapper::Set_Texture(0, reinterpret_cast<Rva001085B4 *>(texture)->rva001085B4());

	Bool shaderSet = false;
	if (w3DShadowTexture)
	{
		switch (type)
		{
			case SHADOW_DECAL:
				DX8Wrapper::Set_Texture(1, reinterpret_cast<Rva001085B4 *>(w3DShadowTexture)->rva001085B4());
				DX8Wrapper::Set_Shader(ShaderClass(BFME_SHADE_CNST(3, 0, 1, 0, 2, 0, 6, 0, 1, 0, 0, 5, 0)));
				break;
			case SHADOW_ALPHA_DECAL:
			case SHADOW_BFME_0400:
			case SHADOW_BFME_2000:
				DX8Wrapper::Set_Texture(1, reinterpret_cast<Rva001085B4 *>(w3DShadowTexture)->rva001085B4());
				DX8Wrapper::Set_Shader(ShaderClass(BFME_SHADE_CNST(3, 0, 1, 2, 5, 0, 6, 0, 1, 0, 0, 5, 0)));
				break;
			case SHADOW_ADDITIVE_DECAL:
			case SHADOW_BFME_0800:
				DX8Wrapper::Set_Texture(1, reinterpret_cast<Rva001085B4 *>(w3DShadowTexture)->rva001085B4());
				DX8Wrapper::Set_Shader(ShaderClass(BFME_SHADE_CNST(3, 0, 1, 1, 1, 0, 6, 0, 1, 0, 0, 5, 0)));
				break;
		}
	}
	else
	{
		switch (type)
		{
			case SHADOW_DECAL:
				DX8Wrapper::Set_Shader(ShaderClass::_PresetMultiplicativeShader);
				break;
			case SHADOW_ALPHA_DECAL:
			case SHADOW_BFME_0400:
			case SHADOW_BFME_2000:
				DX8Wrapper::Set_Shader(ShaderClass::_PresetAlphaShader);
				break;
			case SHADOW_ADDITIVE_DECAL:
			case SHADOW_BFME_0800:
				DX8Wrapper::Set_Shader(ShaderClass::_PresetAdditiveShader);
				break;
		}
	}

	if (type == SHADOW_BFME_1000)
	{
		if (DX8Wrapper::Has_Stencil())
		{
			if (TheWritableGlobalData->m_useSimpleMergeDecals)
			{
				DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILFUNC, D3DCMP_NOTEQUAL);
				DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE);
				DX8Wrapper::Set_Texture(1, 0);
				DX8Wrapper::Set_Shader(BfmeShadowStencilAlphaTestShader);
				DX8Wrapper::Apply_Render_State_Changes();
				DX8Wrapper::Set_DX8_Render_State(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);
				Int alphaRef = (Int)(TheWritableGlobalData->m_opacityOfSimpleMergeDecals * 255.0f);
				if (alphaRef < 0)
					alphaRef = 0;
				else if (alphaRef > 255)
					alphaRef = 255;
				DX8Wrapper::Set_DX8_Render_State(D3DRS_ALPHAREF, alphaRef);
			}
			else if (stencilMode == 0)
			{
				DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);
				DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE);
				DX8Wrapper::Set_Texture(0, reinterpret_cast<Rva001085B4 *>(w3DShadowTexture)->rva001085B4());
				DX8Wrapper::Set_Texture(1, 0);
				DX8Wrapper::Set_Shader(BfmeShadowStencilWriteShader);
				shaderSet = true;
			}
			else if (stencilMode == 1)
			{
				DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILFUNC, D3DCMP_NOTEQUAL);
				DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);
				DX8Wrapper::Set_Texture(1, 0);
				DX8Wrapper::Set_Shader(BfmeShadowStencilTestShader);
			}
		}
		else
		{
			DX8Wrapper::Set_Texture(1, 0);
			DX8Wrapper::Set_Shader(BfmeShadowStencilTestShader);
		}
	}

	if (DX8Wrapper::Get_Fog_Enable() && !shaderSet)
	{
		ShaderClass shader = DX8Wrapper::Get_Shader();
		shader.Enable_Fog("HardwareFog");
		DX8Wrapper::Set_Shader(shader);
	}

	bfmeSetProjectionDepthBias(9.0f);
	DX8Wrapper::Set_Index_Buffer(m_decalIndexBuffer, m_nShadowDecalStartBatchVertex);
	DX8Wrapper::Set_Vertex_Buffer(m_decalVertexBuffer, 0);
	DX8Wrapper::Set_World_Identity();
	DX8Wrapper::Draw_Triangles(m_nShadowDecalStartBatchIndex, m_nShadowDecalPolysInBatch, 0, m_nShadowDecalVertsInBatch);
	bfmeSetProjectionDepthBias(0.0f);
	DX8Wrapper::Set_Index_Buffer(0, 0);
	DX8Wrapper::Set_Vertex_Buffer(0, 0);

	m_nShadowDecalStartBatchVertex = m_nShadowDecalVertsInBuf;
	m_nShadowDecalStartBatchIndex = m_nShadowDecalIndicesInBuf;
	m_nShadowDecalPolysInBatch = 0;	//reset number of polys in texture batch
	m_nShadowDecalVertsInBatch = 0;
}
