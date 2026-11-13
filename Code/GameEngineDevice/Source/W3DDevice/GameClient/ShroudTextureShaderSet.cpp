// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// dxsdk
// platformsdk
// ?set@ShroudTextureShader@@EAEHH@Z retail 0x000F5D3B..0x000F630C (1489 bytes).
// Slot 4 of the shader vftable at 0x007CF1C8: the next slots are reset
// (0x000F5B5F: clears the texture of the stage saved at +8 and restores
// ZFUNC LESSEQUAL) and init (0x000F5B43: stores the instance 0x00DB5A34 in the
// shader table with one pass). Donor: Open-BFME-1 ShroudTextureShaderSet.cpp
// (BFME 1 retail 0x007C3FD0) whose body has the same order: preset material
// through the inlined Set_Material, stage texture 0 from the indexed
// AssetReference getter 0x000F5D1B, the multiplicative sprite shader for
// stage 0, Apply_Render_State_Changes, TEXCOORDINDEX camera-space position,
// TEXTURETRANSFORMFLAGS COUNT2, ZFUNC EQUAL, then the shroud texture and the
// texture matrix, finally m_stageOfSet = stage and TRUE.
// BFME 2 deltas read from retail: the DX8 cache inlines take the stage >= 16
// device path (as in the matched setShroudTex 0x00076C14), the texture matrix
// tail is byte-for-byte the matched setShroudTex tail (GetView then
// transpose; inverse view; draw-origin translation; texel scaling; two
// D3DXMatrixMultiply temporaries) and the terrain shroud/map fields are the
// BFME 2 offsets 3878/37C0 proven there.
#include <d3d9.h>

struct IDirect3DBaseTexture8;

// Direct3D 9 objects behind the dx8 names (IDirect3DDevice9 / IDirect3DBaseTexture9
// from the vendored SDK): SetTransform +0xB0, SetRenderState +0xE4, SetTexture
// +0x104, SetTextureStageState +0x10C.
struct IDirect3DDevice8;

#include "../../../../Libraries/Source/WWVegas/WWMath/Vector4Data.h"

#include "../../../../Libraries/Source/WWVegas/WWMath/Matrix4Data.h"

// The 0x40-byte matrix the setters build (rowed ctor 0x0007671F).
#include "../../../../GameEngine/Include/GameClient/Rva0007671F.h"

struct D3DXMATRIX;
extern "C" D3DXMATRIX *__stdcall D3DXMatrixMultiply(D3DXMATRIX *, const D3DXMATRIX *, const D3DXMATRIX *);
struct D3DXMATRIX
{
	float m[4][4];
	D3DXMATRIX() {}
	__forceinline D3DXMATRIX operator*(const D3DXMATRIX &other) const
	{
		D3DXMATRIX result;
		D3DXMatrixMultiply(&result, this, &other);
		return result;
	}
};
extern "C" D3DXMATRIX *__stdcall D3DXMatrixInverse(D3DXMATRIX *, float *, const D3DXMATRIX *);
extern "C" D3DXMATRIX *__stdcall D3DXMatrixTranslation(D3DXMATRIX *, float, float, float);
extern "C" D3DXMATRIX *__stdcall D3DXMatrixScaling(D3DXMATRIX *, float, float, float);

#include "../../../../Libraries/Source/WWVegas/WW3D2/VertexMaterialClass.h"

class WW3D
{
public:
	static bool Is_Snapshot_Activated() { return SnapshotActivated; }
private:
	static bool SnapshotActivated;
};


#include "../../../../Libraries/Source/WWVegas/WW3D2/ShaderClass.h"

class TextureBaseClass
{
public:
	void Release_Ref();
	IDirect3DBaseTexture8 *Peek_D3D_Base_Texture() const;
};
class TextureClass : public TextureBaseClass
{
public:
	void Release_Ref();	// rowed ICF alias of the TextureBaseClass body (0x0061ED10)
};

template <class T> class RefCountPtr
{
public:
	T *ptr;
	~RefCountPtr()
	{
		if (ptr)
			ptr->Release_Ref();
	}
};
// The shroud texture getter's by-value handle; its storage is read as the texture.
class RvaTextureHandleView : public RefCountPtr<TextureClass>
{
public:
	const TextureBaseClass &texture() const { return *reinterpret_cast<const TextureBaseClass *>(this); }
};

// The indexed stage texture getter 0x000F5D1B returns a counted reference.
class AssetReference
{
public:
	__declspec(dllimport) __forceinline AssetReference() : m_object(0) {}
	AssetReference(const AssetReference &other);
	~AssetReference()
	{
		if (m_object)
			m_object->Release_Ref();
	}
	TextureBaseClass *m_object;
};
AssetReference Rva000F5D1BGet(int index);

struct BFME2TextureRef;
void BFME2Set_Texture(unsigned int stage, const BFME2TextureRef &texture);
static __forceinline const BFME2TextureRef &AsTextureRef(const AssetReference &ref)
{
	return reinterpret_cast<const BFME2TextureRef &>(ref);
}

class Rva00072B3A
{
public:
	RvaTextureHandleView getShroudTexture() const;
	char pad[0x10];
	float cellWidth, cellHeight;
	char pad18[8];
	int textureWidth, textureHeight;
	char pad28[4];
	float drawOriginX, drawOriginY;
};
class BaseHeightMapRenderObjClass
{
public:
	char pad[0x37C0];
	void *map;
	char pad37C4[0xB4];
	Rva00072B3A *shroud;
};
extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;

extern unsigned number_of_DX8_calls;

#include "../../../../Libraries/Source/WWVegas/WW3D2/RenderStateStruct.h"

class DX8Wrapper
{
public:
	enum ChangedStates { MATERIAL_CHANGED = 1 << 14, SHADER_CHANGED = 1 << 15 };
	static void Apply_Render_State_Changes(void);
	static void Get_DX8_Render_State_Value_Name(StringClass &name, unsigned long state, unsigned value);
	static void Get_DX8_Texture_Stage_State_Value_Name(StringClass &name, unsigned long state, unsigned value);

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
	static __forceinline void Set_DX8_Texture_Stage_State(unsigned stage, unsigned long state, unsigned value)
	{
		if (stage >= 16) {
			reinterpret_cast<IDirect3DDevice9 *>(D3DDevice)->SetTextureStageState(stage, (D3DTEXTURESTAGESTATETYPE)state, value);
			number_of_DX8_calls++;
			return;
		}
		if (TextureStageStates[stage][state] == value) return;
		if (WW3D::Is_Snapshot_Activated()) {
			StringClass value_name(0, true);
			Get_DX8_Texture_Stage_State_Value_Name(value_name, state, value);
		}
		TextureStageStates[stage][state] = value;
		reinterpret_cast<IDirect3DDevice9 *>(D3DDevice)->SetTextureStageState(stage, (D3DTEXTURESTAGESTATETYPE)state, value);
		number_of_DX8_calls++;
		texture_stage_state_changes++;
	}
	friend class ShroudTextureShader;
	static __forceinline void Set_DX8_Texture(unsigned int stage, IDirect3DBaseTexture8 *texture)
	{
		if (stage >= 16) {
			reinterpret_cast<IDirect3DDevice9 *>(D3DDevice)->SetTexture(stage, reinterpret_cast<IDirect3DBaseTexture9 *>(texture));
			number_of_DX8_calls++;
			return;
		}
		if (Textures[stage] == texture) return;
		if (Textures[stage]) reinterpret_cast<IDirect3DBaseTexture9 *>(Textures[stage])->Release();
		Textures[stage] = texture;
		if (Textures[stage]) reinterpret_cast<IDirect3DBaseTexture9 *>(Textures[stage])->AddRef();
		reinterpret_cast<IDirect3DDevice9 *>(D3DDevice)->SetTexture(stage, reinterpret_cast<IDirect3DBaseTexture9 *>(texture));
		number_of_DX8_calls++;
		texture_changes++;
	}
	static __forceinline void GetView(Matrix4 &matrix4)
	{
		if (render_state_changed & (1 << 19))
			matrix4.Make_Identity();
		else
			matrix4 = render_state.view.Transpose();
	}
	static __forceinline void SetMatrix(unsigned state, const D3DXMATRIX &d3DXMATRIX)
	{
		++matrix_changes;
		reinterpret_cast<IDirect3DDevice9 *>(D3DDevice)->SetTransform((D3DTRANSFORMSTATETYPE)state, reinterpret_cast<const D3DMATRIX *>(&d3DXMATRIX));
		++number_of_DX8_calls;
	}

protected:
	static IDirect3DDevice8 *D3DDevice;
	static unsigned RenderStates[];
	static unsigned TextureStageStates[][32];
	static IDirect3DBaseTexture8 *Textures[];
	static RenderStateStruct render_state;
	static unsigned render_state_changed;
	static unsigned render_state_changes;
	static unsigned texture_stage_state_changes;
	static unsigned texture_changes;
	static unsigned matrix_changes;
};

class ShroudTextureShader
{
	virtual void s00();
	virtual void rva000F5AD4();
	virtual void s02();
	virtual void s03();
	virtual int set(int stage);
	virtual void reset();
	int m_numPasses;
	int m_stageOfSet;
};

int ShroudTextureShader::set(int stage)
{
	VertexMaterialClass *vmat = VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_DIFFUSE);
	DX8Wrapper::Set_Material(vmat);
	if (vmat) { vmat->Release_Ref(); vmat = 0; }

	BFME2Set_Texture(stage, AsTextureRef(Rva000F5D1BGet(0)));

	if (stage == 0)
		DX8Wrapper::Set_Shader(ShaderClass::_PresetMultiplicativeSpriteShader);
	DX8Wrapper::Apply_Render_State_Changes();

	DX8Wrapper::Set_DX8_Texture_Stage_State(stage, D3DTSS_TEXCOORDINDEX, D3DTSS_TCI_CAMERASPACEPOSITION);
	DX8Wrapper::Set_DX8_Texture_Stage_State(stage, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT2);
	DX8Wrapper::Set_DX8_Render_State(D3DRS_ZFUNC, D3DCMP_EQUAL);

	Rva00072B3A *shroud;
	if ((shroud = TheTerrainRenderObject->shroud) != 0)
	{
		if (shroud->getShroudTexture().ptr != 0)
			DX8Wrapper::Set_DX8_Texture(stage, shroud->getShroudTexture().texture().Peek_D3D_Base_Texture());

		D3DXMATRIX inv;
		float det;
		Rva0007671F curView;
		DX8Wrapper::GetView(curView);
		static_cast<Matrix4 &>(curView) = curView.Transpose();
		D3DXMatrixInverse(&inv, &det, reinterpret_cast<D3DXMATRIX *>(&curView));
		D3DXMATRIX scale, offset;
		float xoffset = 0, yoffset = 0, width = shroud->cellWidth, height = shroud->cellHeight;
		if (TheTerrainRenderObject->map)
		{
			xoffset = width - shroud->drawOriginX;
			yoffset = height - shroud->drawOriginY;
		}
		D3DXMatrixTranslation(&offset, xoffset, yoffset, 0);
		width = 1.0f / (width * shroud->textureWidth);
		height = 1.0f / (height * shroud->textureHeight);
		D3DXMatrixScaling(&scale, width, height, 1);
		*((D3DXMATRIX *)&curView) = (inv * offset) * scale;
		DX8Wrapper::SetMatrix(D3DTS_TEXTURE0 + stage, *((D3DXMATRIX *)&curView));
	}
	m_stageOfSet = stage;
	return 1;
}

// Retail 0x000F5AD4 (111 bytes), slot 1 of the same vftable (no direct callers): mark the
// shader state dirty and clear device texture stages 0 and 1 through the inlined
// Set_DX8_Texture cache (Textures[] 0x00DEC4B0). Its declared name is not recovered.
void ShroudTextureShader::rva000F5AD4()
{
	ShaderClass::ShaderDirty = true;
	DX8Wrapper::Set_DX8_Texture(0, 0);
	DX8Wrapper::Set_DX8_Texture(1, 0);
}

// Retail 0x000F5B5F (444 bytes), slot 5 (reset): unbind the texture of the stage set() saved
// at +8 through an empty stage reference, restore ZFUNC LESSEQUAL, then the stage's
// TEXCOORDINDEX (passthru to itself) and TEXTURETRANSFORMFLAGS DISABLE, as in Zero Hour.
void ShroudTextureShader::reset()
{
	BFME2Set_Texture(m_stageOfSet, AsTextureRef(AssetReference()));
	DX8Wrapper::Set_DX8_Render_State(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	DX8Wrapper::Set_DX8_Texture_Stage_State(m_stageOfSet, D3DTSS_TEXCOORDINDEX, m_stageOfSet);
	DX8Wrapper::Set_DX8_Texture_Stage_State(m_stageOfSet, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE);
}
