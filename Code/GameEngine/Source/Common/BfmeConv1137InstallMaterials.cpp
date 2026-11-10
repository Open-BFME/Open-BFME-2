// platformsdk
// BfmeB1137::Install_Materials (0x00095821, 10940 B), with its EH handler 0x007603D0.
// Stack layout (c2 3077 colouring, traced): the per-mode getter is declared throw(), so its
// call carries only its scope's alias set instead of the function's last EH-state set (the
// final mode-2 RS(20,3) scope); mode-1 wind is a tight block and mode-2 det sits at mode-2
// scope, so det creates the 8-byte colour at -0xF4 that wind then joins, as retail.
// Evidence: reverse/attempt_support/0x00095821-det2-stack-colouring-20261020.md.
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
#include <windows.h>
#include "ascii_string.h"
class WWMath
{
public:
	static __forceinline float Sqrt(float radicand)
	{
		float squareRoot;
		__asm {
			fld [radicand]
			fsqrt
			fstp [squareRoot]
		}
		return squareRoot;
	}
};
typedef DWORD D3DRENDERSTATETYPE;
typedef DWORD D3DTEXTURESTAGESTATETYPE;

struct IDirect3DBaseTexture8
{
	virtual HRESULT __stdcall QueryInterface(const void *riid, void **ppv) = 0;
	virtual DWORD __stdcall AddRef(void) = 0;
	virtual DWORD __stdcall Release(void) = 0;
};

// Direct3D 9 slot order behind the dx8 names: SetTransform +0xB0,
// SetRenderState +0xE4, SetTexture +0x104, SetTextureStageState +0x10C.
struct IDirect3DDevice8
{
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
	virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31();
	virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35();
	virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39();
	virtual void s40(); virtual void s41(); virtual void s42(); virtual void s43();
	virtual HRESULT __stdcall SetTransform(DWORD state, const void *matrix) = 0;
	virtual HRESULT __stdcall GetTransform(DWORD state, void *matrix) = 0; virtual void s46(); virtual void s47();
	virtual void s48(); virtual void s49(); virtual void s50(); virtual void s51();
	virtual void s52(); virtual void s53(); virtual void s54(); virtual void s55();
	virtual void s56();
	virtual HRESULT __stdcall SetRenderState(D3DRENDERSTATETYPE state, DWORD value) = 0;
	virtual void s58(); virtual void s59();
	virtual void s60(); virtual void s61(); virtual void s62(); virtual void s63();
	virtual void s64();
	virtual HRESULT __stdcall SetTexture(DWORD stage, IDirect3DBaseTexture8 *texture) = 0;
	virtual void s66();
	virtual HRESULT __stdcall SetTextureStageState(DWORD stage, D3DTEXTURESTAGESTATETYPE type, DWORD value) = 0;
	virtual void s68();
	virtual HRESULT __stdcall SetSamplerState(DWORD stage, DWORD type, DWORD value) = 0;
};

#include "../../../Libraries/Source/WWVegas/WWMath/Vector4Data.h"

#include "../../../Libraries/Source/WWVegas/WWMath/Matrix4Data.h"

// The 0x40-byte matrix the setters build (rowed ctor 0x0007671F).
class Rva0007671F : public Matrix4
{
public:
	Rva0007671F();
};

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

class StringClass
{
public:
	inline StringClass(int initial_len = 0, bool hint_temporary = false);
	~StringClass() { Free_String(); }
private:
	char *m_Buffer;
	void Free_String();
	void Get_String(int new_len, bool is_temp);
	static char m_NullChar;
	static char *m_EmptyString;
};

inline StringClass::StringClass(int initial_len, bool hint_temporary) : m_Buffer(m_EmptyString)
{
	Get_String(initial_len, hint_temporary);
	m_Buffer[0] = m_NullChar;
}

class WW3D
{
	friend class BfmeB1137;
public:
	static bool Is_Snapshot_Activated() { return SnapshotActivated; }
private:
	static bool SnapshotActivated;
	static unsigned SyncTime;
};

class VertexMaterialClass
{
public:
	enum PresetType { PRELIT_DIFFUSE = 0 };
	static VertexMaterialClass *Get_Preset(PresetType type);
	virtual void Delete_This(void);
	void Add_Ref(void) { ++NumRefs; }
	void Release_Ref(void) { if (--NumRefs == 0) Delete_This(); }
private:
	int NumRefs;
};

#include "../../../Libraries/Source/WWVegas/WW3D2/RenderStateStruct.h"

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
	const RefCountPtr &operator=(const RefCountPtr &other);
	~RefCountPtr()
	{
		if (ptr)
			ptr->Release_Ref();
	}
};
class BaseHeightMapRenderObjClass
{
public:
	char pad[0x37C0];
	struct WorldHeightMap *map;
};
struct WorldHeightMap
{
	char pad[8];
	int width;
	int height;
};
extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;

extern unsigned number_of_DX8_calls;


class DX8Wrapper
{
public:
	enum ChangedStates { MATERIAL_CHANGED = 1 << 14, SHADER_CHANGED = 1 << 15 };
	static void Apply_Render_State_Changes(void);
	static void Get_DX8_Render_State_Value_Name(StringClass &name, D3DRENDERSTATETYPE state, unsigned value);
	static void Get_DX8_Texture_Stage_State_Value_Name(StringClass &name, D3DTEXTURESTAGESTATETYPE state, unsigned value);

	static __forceinline void Set_Material(const VertexMaterialClass *material)
	{
		VertexMaterialClass *newMaterial = const_cast<VertexMaterialClass *>(material);
		if (newMaterial) newMaterial->Add_Ref();
		if (render_state.material) render_state.material->Release_Ref();
		render_state.material = newMaterial;
		render_state_changed |= MATERIAL_CHANGED;
		if (WW3D::Is_Snapshot_Activated()) {}
	}
	static __forceinline void Set_Shader(const ShaderClass &shader)
	{
		if (!ShaderClass::ShaderDirty && shader.ShaderBits == render_state.shader.ShaderBits)
			return;
		render_state.shader = shader;
		render_state_changed |= SHADER_CHANGED;
		StringClass str;
		if (WW3D::Is_Snapshot_Activated()) {}
	}
	static __forceinline void Set_DX8_Render_State(D3DRENDERSTATETYPE state, unsigned value)
	{
		if (RenderStates[state] == value) return;
		if (WW3D::Is_Snapshot_Activated()) {
			StringClass value_name(0, true);
			Get_DX8_Render_State_Value_Name(value_name, state, value);
			if (WW3D::Is_Snapshot_Activated()) {}
		}
		RenderStates[state] = value;
		_Get_D3D_Device8()->SetRenderState(state, value);
		number_of_DX8_calls++;
		render_state_changes++;
	}
	static __forceinline void Set_DX8_Texture_Stage_State(unsigned stage, D3DTEXTURESTAGESTATETYPE state, unsigned value)
	{
		if (stage >= 16) {
			_Get_D3D_Device8()->SetTextureStageState(stage, state, value);
			number_of_DX8_calls++;
			return;
		}
		if (TextureStageStates[stage][state] == value) return;
		if (WW3D::Is_Snapshot_Activated()) {
			StringClass value_name(0, true);
			Get_DX8_Texture_Stage_State_Value_Name(value_name, state, value);
		}
		TextureStageStates[stage][state] = value;
		_Get_D3D_Device8()->SetTextureStageState(stage, state, value);
		number_of_DX8_calls++;
		texture_stage_state_changes++;
	}
	static __forceinline void Set_DX8_Sampler_State(unsigned stage, DWORD type, unsigned value)
	{
		_Get_D3D_Device8()->SetSamplerState(stage, type, value);
		number_of_DX8_calls++;
		texture_stage_state_changes++;
	}
	static void Invalidate_Cached_Render_States(void);
	static __forceinline void Set_DX8_Texture(unsigned int stage, IDirect3DBaseTexture8 *texture)
	{
		if (stage >= 16) {
			_Get_D3D_Device8()->SetTexture(stage, texture);
			number_of_DX8_calls++;
			return;
		}
		if (Textures[stage] == texture) return;
		if (WW3D::Is_Snapshot_Activated()) {}
		if (Textures[stage]) Textures[stage]->Release();
		Textures[stage] = texture;
		if (Textures[stage]) Textures[stage]->AddRef();
		_Get_D3D_Device8()->SetTexture(stage, texture);
		number_of_DX8_calls++;
		texture_changes++;
	}
	static __forceinline void Get_Transform(DWORD transformType, Matrix4 &outputMatrix)
	{
		D3DXMATRIX deviceTransform;
		switch ((int)transformType) {
		case 256:
			if (render_state_changed & (1 << 18)) outputMatrix.Make_Identity();
			else outputMatrix = render_state.world.Transpose();
			break;
		case 2:
			if (render_state_changed & (1 << 19)) outputMatrix.Make_Identity();
			else outputMatrix = render_state.view.Transpose();
			break;
		default:
			_Get_D3D_Device8()->GetTransform(transformType, &deviceTransform);
			number_of_DX8_calls++;
			outputMatrix = *(Matrix4 *)&deviceTransform;
			outputMatrix = outputMatrix.Transpose();
			break;
		}
	}
	static __forceinline void _Get_DX8_Transform(DWORD transformType, Matrix4 &outputMatrix)
	{
		Get_Transform(transformType, outputMatrix);
		outputMatrix = outputMatrix.Transpose();
	}
	static __forceinline void SetMatrix(unsigned state, const D3DXMATRIX &matrix)
	{
		if (WW3D::Is_Snapshot_Activated()) {}
		++matrix_changes;
		_Get_D3D_Device8()->SetTransform(state, &matrix);
		++number_of_DX8_calls;
	}

public:
	static IDirect3DDevice8 *_Get_D3D_Device8() { return D3DDevice; }
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


class BFME2ParticleTextureHandle : public RefCountPtr<TextureClass>
{
};

class ShroudFilter
{
public:
	int m_minFilter;
	int m_magFilter;
	int m_mipFilter;
	int m_uAddressMode;
	int m_vAddressMode;
	void SetMip(int mip);
	void Set_U_Addr_Mode(int mode) { m_uAddressMode = mode; }
	void Set_V_Addr_Mode(int mode) { m_vAddressMode = mode; }
};

#include "../../../GameEngineDevice/Include/W3DDevice/GameClient/ShroudTexture.h"

#include "../../../GameEngineDevice/Include/W3DDevice/GameClient/TextureAsset.h"

struct BFME2TextureRef;
void BFME2Set_Texture(unsigned int stage, const BFME2TextureRef &texture);

struct D3DXVECTOR3 { float x, y, z; };
struct D3DXVECTOR4 { float x, y, z, w; };
struct D3DXPLANE { float a, b, c, d; };
extern "C" D3DXMATRIX *__stdcall D3DXMatrixRotationZ(D3DXMATRIX *, float);
extern "C" D3DXVECTOR4 *__stdcall rva0062AF56D3DXVec3Transform(D3DXVECTOR4 *, const D3DXVECTOR3 *, const D3DXMATRIX *);
extern "C" D3DXPLANE *__stdcall rva0062AF50D3DXPlaneFromPointNormal(D3DXPLANE *, const D3DXVECTOR3 *, const D3DXVECTOR3 *);

__inline D3DXMATRIX *__stdcall D3DXMatrixIdentity(D3DXMATRIX *pOut)
{
	pOut->m[0][1] = pOut->m[0][2] = pOut->m[0][3] =
	pOut->m[1][0] = pOut->m[1][2] = pOut->m[1][3] =
	pOut->m[2][0] = pOut->m[2][1] = pOut->m[2][3] =
	pOut->m[3][0] = pOut->m[3][1] = pOut->m[3][2] = 0.0f;

	pOut->m[0][0] = pOut->m[1][1] = pOut->m[2][2] = pOut->m[3][3] = 1.0f;
	return pOut;
}

#include "../../../Libraries/Include/Lib/RGBColor.h"

// The cloud settings object at 0x00DFE1E4 and its rowed getters.
class Rva0027070CGlobal;
extern Rva0027070CGlobal *TheCloudEffectManager;
struct CloudFields
{
	char pad00[0x1C];
	float m_rotation;	// +0x1C
	char pad20[8];
	float m_28;
	float m_2C;
	float getM28() const { return m_28; }
	float getM2C() const { return m_2C; }
	char pad30[0x94];
	int m_C4;
};
class Rva00564E0D { public: AsciiString rva00564E0D(); };
#include "../../Include/Common/VersionClass.h"
class Rva0056394A { public: AsciiString rva0056394A(); };
namespace FXParticleSystem {
class ParticleSystemTemplate { public: AsciiString getTextureFilename() const; };
}
class Rva00214D4A { public: float rva00214D4A(); };
struct Rva00094DD3Val { float x, y; };
class Rva00094DD3 { public: void rva00094DD3(Rva00094DD3Val *out) throw(); };

extern int g_Va00DB47EC;
class GlobalWeatherSystem;
extern GlobalWeatherSystem *TheGlobalWeatherSystem;
struct GlobalWeatherSystemView { char pad[0x10]; int m_10; };
class GameLogic;
extern GameLogic *TheGameLogic;
struct GameLogicView { char pad[0x40]; int m_frame; };

class BfmeB1137
{
public:
	virtual void s00(void);
	virtual void s01(void);
	virtual void Install_Materials(void) const;
	virtual void UnInstall_Materials(void) const;

	char pad04[0x34];
	mutable float m_38;
	mutable float m_3C;
	mutable float m_40;
	mutable int m_44;
	char pad48[4];
	mutable float m_4C;
	mutable float m_50;
	char pad54[4];
	mutable RefCountPtr<TextureClass> m_58;
	mutable RefCountPtr<TextureClass> m_5C;
	mutable RefCountPtr<TextureClass> m_60;
	mutable RefCountPtr<TextureClass> m_64;
	mutable bool m_68;
	bool m_69;
	bool m_6A;
	mutable D3DXVECTOR3 m_6C;
	mutable D3DXVECTOR3 m_78;
	mutable D3DXPLANE m_84;
	mutable D3DXMATRIX m_94;
	mutable float m_D4;
	mutable float m_D8;
	char padDC[4];
	mutable float m_E0;
	mutable int m_E4;
};

static __forceinline const BFME2TextureRef &AsRef(const RefCountPtr<TextureClass> &texture)
{
	return reinterpret_cast<const BFME2TextureRef &>(texture);
}

#define CLOUD ((CloudFields *)TheCloudEffectManager)

static inline void SetU(D3DXMATRIX &matrix, float translationX, float translationY) { matrix.m[3][1] = translationY; matrix.m[3][0] = translationX; }
void BfmeB1137::Install_Materials(void) const
{
	if (!g_Va00DB47EC || !TheGlobalWeatherSystem)
		return;

	DX8Wrapper::Invalidate_Cached_Render_States();
	ShaderClass::ShaderDirty = true;
	VertexMaterialClass *presetMaterial = VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_DIFFUSE);
	DX8Wrapper::Set_Material(presetMaterial);
	if (presetMaterial)
		presetMaterial->Release_Ref();
	DX8Wrapper::Apply_Render_State_Changes();

	if (g_Va00DB47EC == 1)
	{
		if (!m_58.ptr)
		{
			m_58 = TextureAsset::Get(((Rva00564E0D *)TheCloudEffectManager)->rva00564E0D().str(), 0, 0);
			((ShroudTexture *)&m_58)->getFilter()->Set_U_Addr_Mode(0);
			((ShroudTexture *)&m_58)->getFilter()->Set_V_Addr_Mode(0);
			((ShroudTexture *)&m_58)->getFilter()->SetMip(0);
		}
		if (!m_60.ptr)
		{
			m_60 = TextureAsset::Get(((Version *)TheCloudEffectManager)->getAsciiBuildLocation().str(), 0, 0);
			((ShroudTexture *)&m_60)->getFilter()->Set_U_Addr_Mode(1);
			((ShroudTexture *)&m_60)->getFilter()->Set_V_Addr_Mode(1);
			((ShroudTexture *)&m_60)->getFilter()->SetMip(0);
		}
		if (!m_64.ptr)
		{
			m_64 = TextureAsset::Get(((Rva0056394A *)TheCloudEffectManager)->rva0056394A().str(), 0, 0);
			((ShroudTexture *)&m_64)->getFilter()->Set_U_Addr_Mode(1);
			((ShroudTexture *)&m_64)->getFilter()->Set_V_Addr_Mode(1);
			((ShroudTexture *)&m_64)->getFilter()->SetMip(0);
		}
		BFME2Set_Texture(0, AsRef(m_58));
		BFME2Set_Texture(1, AsRef(m_58));
		BFME2Set_Texture(2, AsRef(m_60));
		BFME2Set_Texture(3, AsRef(m_64));

		DX8Wrapper::Set_DX8_Render_State(15, 0);
		if (!m_69)
		{
			DX8Wrapper::Set_DX8_Texture_Stage_State(0, 1, 1);
			return;
		}
		DX8Wrapper::Set_DX8_Texture_Stage_State(0, 1, 2);
		DX8Wrapper::Set_DX8_Texture_Stage_State(0, 2, 2);
		DX8Wrapper::Set_DX8_Texture_Stage_State(0, 3, 1);
		DX8Wrapper::Set_DX8_Texture_Stage_State(0, 4, 2);
		DX8Wrapper::Set_DX8_Texture_Stage_State(0, 5, 2);
		DX8Wrapper::Set_DX8_Texture_Stage_State(0, 6, 1);
		DX8Wrapper::Set_DX8_Texture_Stage_State(1, 1, 3);
		DX8Wrapper::Set_DX8_Texture_Stage_State(1, 2, 2);
		DX8Wrapper::Set_DX8_Texture_Stage_State(1, 3, 1);
		DX8Wrapper::Set_DX8_Texture_Stage_State(1, 4, 2);
		DX8Wrapper::Set_DX8_Texture_Stage_State(1, 5, 2);
		DX8Wrapper::Set_DX8_Texture_Stage_State(1, 6, 1);
		DX8Wrapper::Set_DX8_Texture_Stage_State(2, 1, 0x13);
		DX8Wrapper::Set_DX8_Texture_Stage_State(2, 2, 2);
		DX8Wrapper::Set_DX8_Texture_Stage_State(2, 3, 1);
		DX8Wrapper::Set_DX8_Texture_Stage_State(2, 4, 2);
		DX8Wrapper::Set_DX8_Texture_Stage_State(2, 5, 2);
		DX8Wrapper::Set_DX8_Texture_Stage_State(2, 6, 1);
		if (!m_6A)
			DX8Wrapper::Set_DX8_Texture_Stage_State(3, 1, 1);
		else
		{
			DX8Wrapper::Set_DX8_Texture_Stage_State(3, 1, 0x13);
			DX8Wrapper::Set_DX8_Texture_Stage_State(3, 2, 2);
			DX8Wrapper::Set_DX8_Texture_Stage_State(3, 3, 1);
			DX8Wrapper::Set_DX8_Texture_Stage_State(3, 4, 2);
			DX8Wrapper::Set_DX8_Texture_Stage_State(3, 5, 2);
			DX8Wrapper::Set_DX8_Texture_Stage_State(3, 6, 1);
		}
		DX8Wrapper::Set_DX8_Render_State(23, 4);
		DX8Wrapper::Set_DX8_Render_State(14, 0);
		DX8Wrapper::Set_DX8_Texture_Stage_State(0, 11, 0x20000);
		DX8Wrapper::Set_DX8_Texture_Stage_State(0, 24, 2);
		DX8Wrapper::Set_DX8_Texture_Stage_State(2, 11, 0x20000);
		DX8Wrapper::Set_DX8_Texture_Stage_State(2, 24, 2);
		if (!m_6A)
			DX8Wrapper::Set_DX8_Texture_Stage_State(3, 24, 0);
		else
		{
			DX8Wrapper::Set_DX8_Texture_Stage_State(3, 11, 0x20000);
			DX8Wrapper::Set_DX8_Texture_Stage_State(3, 24, 2);
		}

		D3DXMATRIX inv;
		float det;
		Rva0007671F view;
		DX8Wrapper::_Get_DX8_Transform(2, view);
		D3DXMatrixInverse(&inv, &det, reinterpret_cast<D3DXMATRIX *>(&view));

		D3DXMATRIX driftTransform;
		D3DXMatrixIdentity(&driftTransform);
		WorldHeightMap *map = TheTerrainRenderObject->map;
		int width = map->width;
		int height = map->height;
		bool alreadyUpdatedThisFrame = false;
		int currentFrame = ((GameLogicView *)TheGameLogic)->m_frame;
		if (m_E4 == currentFrame)
			alreadyUpdatedThisFrame = true;
		m_E4 = currentFrame;
		if (!alreadyUpdatedThisFrame)
			m_38 += ((Rva00214D4A *)TheCloudEffectManager)->rva00214D4A();
		if (m_38 > 1.0f)
			m_38 = 1.0f;
		float mapDiagonal = WWMath::Sqrt((float)(height * height + width * width));
		driftTransform.m[3][0] -= mapDiagonal * m_38 * 10.0f;

		float mapWidthFloat = (float)width;
		float mapHeightFloat = (float)height;
		float worldWidth = mapWidthFloat * 10.0f;
		float worldHeight = mapHeightFloat * 10.0f;
		double halfWorldWidth;
		float halfWorldHeight;
		D3DXMATRIX rotationTransform;
		D3DXMATRIX centerTranslation;
		D3DXMATRIX shiftTransform;
		D3DXMATRIX negativeCenterTranslation;
		D3DXMATRIX centeredRotation;
		D3DXMATRIX scaledWorldTransform;
		D3DXMATRIX worldTransform;
		D3DXMATRIX scroll;
		D3DXMATRIX scale;
		D3DXMatrixScaling(&scale, 1.0f / worldWidth, 1.0f / worldHeight, 1.0f);
		D3DXMatrixRotationZ(&rotationTransform, CLOUD->m_rotation);
		halfWorldWidth = worldWidth * 0.5f;
		halfWorldHeight = worldHeight * 0.5f;
		D3DXMatrixTranslation(&centerTranslation, halfWorldWidth, halfWorldHeight, 0.0f);
		D3DXMatrixTranslation(&shiftTransform, mapDiagonal * 5.0f, 0.0f, 0.0f);
		D3DXMatrixIdentity(&negativeCenterTranslation);
		negativeCenterTranslation.m[3][0] = worldWidth * -0.5f;
		negativeCenterTranslation.m[3][1] = worldHeight * -0.5f;

		centeredRotation = negativeCenterTranslation * rotationTransform * centerTranslation;
		worldTransform = centeredRotation * shiftTransform * driftTransform;
		scaledWorldTransform = worldTransform * scale;
		*reinterpret_cast<D3DXMATRIX *>(&view) = inv * scaledWorldTransform;
		DX8Wrapper::SetMatrix(0x12, *reinterpret_cast<D3DXMATRIX *>(&view));

		float centerX = mapWidthFloat * 0.5f;
		centerX *= 10.0f;
		float centerY = mapHeightFloat * 0.5f;
		centerY *= 10.0f;
		m_94 = worldTransform;
		D3DXMatrixInverse(&worldTransform, &det, &worldTransform);
		D3DXVECTOR3 centerPoint;
		centerPoint.x = centerX;
		centerPoint.y = centerY;
		centerPoint.z = 0.0f;
		D3DXVECTOR4 transformedCenter;
		rva0062AF56D3DXVec3Transform(&transformedCenter, &centerPoint, &worldTransform);
		m_6C.x = transformedCenter.x;
		m_6C.y = transformedCenter.y;
		m_6C.z = transformedCenter.z;
		m_78.x = worldTransform.m[0][0];
		m_78.y = worldTransform.m[0][1];
		m_78.z = worldTransform.m[0][2];
		rva0062AF50D3DXPlaneFromPointNormal(&m_84, &m_6C, &m_78);

		int last = m_44;
		m_44 = WW3D::SyncTime;
		int elapsed = m_44 - last;
		if (alreadyUpdatedThisFrame)
			elapsed = 0;
		{
		Rva00094DD3Val wind;
		((Rva00094DD3 *)TheCloudEffectManager)->rva00094DD3(&wind);
		float elapsedSyncTicksFloat = (float)elapsed;
		m_4C += wind.x * elapsedSyncTicksFloat * 0.002f;
		m_50 += wind.y * elapsedSyncTicksFloat * 0.002f;
		}
		while (m_4C > 1.0f)
			m_4C -= 1.0f;
		while (m_50 > 1.0f)
			m_50 -= 1.0f;
		while (m_4C < -1.0f)
			m_4C += 1.0f;
		while (m_50 < -1.0f)
			m_50 += 1.0f;

		D3DXMatrixTranslation(&scroll, m_4C, m_50, 0.0f);
		D3DXMatrixScaling(&scale, 0.0031746032f, 0.0031746032f, 1.0f);
		*reinterpret_cast<D3DXMATRIX *>(&view) = inv * scale * scroll;
		DX8Wrapper::SetMatrix(0x10, *reinterpret_cast<D3DXMATRIX *>(&view));

		if (m_6A)
		{
			m_D4 = halfWorldWidth;
			m_D8 = halfWorldHeight;
			D3DXMATRIX originTranslation;
			D3DXMatrixTranslation(&originTranslation, 0.0f - m_D4, 0.0f - m_D8, 0.0f);
			D3DXMATRIX textureCenterTranslation;
			D3DXMatrixTranslation(&textureCenterTranslation, 0.5f, 0.5f, 0.0f);
			float cloudRadius = CLOUD->getM28() + m_3C * 0.1f + 0.15000000596046448 * m_3C * m_3C;
			m_40 = cloudRadius;
			if (!m_68)
			{
				if (cloudRadius > 100.0f)
					m_40 = 100.0f;
				else if (!alreadyUpdatedThisFrame)
				{
					float growthIncrement = CLOUD->getM2C();
					const float &growthAccumulator = m_3C;
					m_3C = growthAccumulator + growthIncrement;
				}
			}
			float worldTexelWidth = m_40;
			float worldTexelHeight = m_40;
			float widthScale = 1.0f / (worldTexelWidth * 128.0f);
			float heightScale = 1.0f / (worldTexelHeight * 128.0f);
			D3DXMatrixScaling(&scale, widthScale, heightScale, 1);
			*reinterpret_cast<D3DXMATRIX *>(&view) = inv * originTranslation * scale * textureCenterTranslation;
			DX8Wrapper::SetMatrix(0x13, *reinterpret_cast<D3DXMATRIX *>(&view));
			m_E0 = m_40 * 64.0f;
		}
		DX8Wrapper::Set_DX8_Render_State(27, 1);
		DX8Wrapper::Set_DX8_Render_State(19, 1);
		DX8Wrapper::Set_DX8_Render_State(20, 3);
		m_68 = true;
	}
	else if (g_Va00DB47EC == 2)
	{
		if (!m_58.ptr)
		{
			m_58 = TextureAsset::Get(((Rva00564E0D *)TheCloudEffectManager)->rva00564E0D().str(), 0, 0);
			((ShroudTexture *)&m_58)->getFilter()->Set_U_Addr_Mode(0);
			((ShroudTexture *)&m_58)->getFilter()->Set_V_Addr_Mode(0);
			((ShroudTexture *)&m_58)->getFilter()->SetMip(0);
		}
		if (!m_5C.ptr)
		{
			m_5C = TextureAsset::Get(((FXParticleSystem::ParticleSystemTemplate *)TheCloudEffectManager)->getTextureFilename().str(), 0, 0);
			((ShroudTexture *)&m_5C)->getFilter()->Set_U_Addr_Mode(0);
			((ShroudTexture *)&m_5C)->getFilter()->Set_V_Addr_Mode(0);
			((ShroudTexture *)&m_5C)->getFilter()->SetMip(0);
		}
		if (((GlobalWeatherSystemView *)TheGlobalWeatherSystem)->m_10 == 1)
			BFME2Set_Texture(0, AsRef(m_5C));
		else
			BFME2Set_Texture(0, AsRef(m_58));
		DX8Wrapper::Set_DX8_Texture_Stage_State(0, 1, 7);
		DX8Wrapper::Set_DX8_Texture_Stage_State(0, 2, 2);
		DX8Wrapper::Set_DX8_Texture_Stage_State(0, 3, 3);
		DX8Wrapper::Set_DX8_Texture_Stage_State(0, 4, 7);
		DX8Wrapper::Set_DX8_Texture_Stage_State(0, 5, 2);
		DX8Wrapper::Set_DX8_Texture_Stage_State(0, 6, 3);
		DX8Wrapper::Set_DX8_Sampler_State(0, 6, 2);
		DX8Wrapper::Set_DX8_Sampler_State(0, 5, 2);
		DX8Wrapper::Set_DX8_Sampler_State(0, 7, 2);
		DX8Wrapper::Set_DX8_Texture_Stage_State(0, 11, 0x20000);
		DX8Wrapper::Set_DX8_Texture_Stage_State(0, 24, 2);

		D3DXMATRIX inv;
		Rva0007671F view;
		DX8Wrapper::_Get_DX8_Transform(2, view);
		float det;
		D3DXMatrixInverse(&inv, &det, reinterpret_cast<D3DXMATRIX *>(&view));

		int last = m_44;
		m_44 = WW3D::SyncTime;
		int elapsed = m_44 - last;
		{
		Rva00094DD3Val wind;
		((Rva00094DD3 *)TheCloudEffectManager)->rva00094DD3(&wind);
		m_4C += elapsed * wind.x * 0.001f;
		m_50 += elapsed * wind.y * 0.001f;
		}
		while (m_4C > 1.0f)
			m_4C -= 1.0f;
		while (m_50 > 1.0f)
			m_50 -= 1.0f;
		while (m_4C < -1.0f)
			m_4C += 1.0f;
		while (m_50 < -1.0f)
			m_50 += 1.0f;

		D3DXMATRIX scroll;
		D3DXMatrixTranslation(&scroll, m_4C, m_50, 0.0f);
		D3DXMATRIX scale;
		D3DXMatrixScaling(&scale, 0.00078125f, 0.00078125f, 1.0f);
		*reinterpret_cast<D3DXMATRIX *>(&view) = inv * scale * scroll;
		DX8Wrapper::SetMatrix(0x10, *reinterpret_cast<D3DXMATRIX *>(&view));

		DX8Wrapper::Set_DX8_Render_State(23, 4);
		DX8Wrapper::Set_DX8_Render_State(14, 0);
		DX8Wrapper::Set_DX8_Texture_Stage_State(1, 1, 1);
		DX8Wrapper::Set_DX8_Texture_Stage_State(1, 4, 1);
		CloudFields *cloudSettings = CLOUD;
		DX8Wrapper::Set_DX8_Render_State(15, 1);
		DX8Wrapper::Set_DX8_Render_State(24, cloudSettings->m_C4);
		DX8Wrapper::Set_DX8_Render_State(25, 7);
		DX8Wrapper::Set_DX8_Render_State(26, 1);
		{
		RGBColor renderColor;
		renderColor.red = renderColor.green = renderColor.blue = (float)cloudSettings->m_C4 * (1.0f / 255.0f);
		unsigned packedRenderColor = renderColor.getAsInt();
		DX8Wrapper::Set_DX8_Render_State(60, packedRenderColor | 0xFF000000);
		}
		DX8Wrapper::Set_DX8_Render_State(27, 1);
		DX8Wrapper::Set_DX8_Render_State(19, 1);
		DX8Wrapper::Set_DX8_Render_State(20, 3);
		m_68 = true;
	}
}
