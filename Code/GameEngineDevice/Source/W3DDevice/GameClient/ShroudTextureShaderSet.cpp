// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
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
typedef unsigned long DWORD;
typedef long HRESULT;
typedef unsigned int UINT;
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
	virtual void s45(); virtual void s46(); virtual void s47();
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
};

class Vector4
{
public:
	__forceinline Vector4() {}
	__forceinline Vector4(float x, float y, float z, float w) { X = x; Y = y; Z = z; W = w; }
	float &operator[](int i) { return (&X)[i]; }
	const float &operator[](int i) const { return (&X)[i]; }
	__forceinline Vector4 &operator=(const Vector4 &v) { X = v.X; Y = v.Y; Z = v.Z; W = v.W; return *this; }
	__forceinline void Set(float x, float y, float z, float w) { X = x; Y = y; Z = z; W = w; }

	float X;
	float Y;
	float Z;
	float W;
};

class Matrix4
{
public:
	__forceinline Matrix4() {}
	__forceinline Matrix4(const Matrix4 &m)
	{
		Row[0] = m.Row[0]; Row[1] = m.Row[1]; Row[2] = m.Row[2]; Row[3] = m.Row[3];
	}
	__forceinline Matrix4(const Vector4 &r0, const Vector4 &r1, const Vector4 &r2, const Vector4 &r3)
	{
		Init(r0, r1, r2, r3);
	}
	__forceinline void Init(const Vector4 &r0, const Vector4 &r1, const Vector4 &r2, const Vector4 &r3)
	{
		Row[0] = r0; Row[1] = r1; Row[2] = r2; Row[3] = r3;
	}
	__forceinline void Make_Identity()
	{
		Row[0].Set(1.0f, 0.0f, 0.0f, 0.0f);
		Row[1].Set(0.0f, 1.0f, 0.0f, 0.0f);
		Row[2].Set(0.0f, 0.0f, 1.0f, 0.0f);
		Row[3].Set(0.0f, 0.0f, 0.0f, 1.0f);
	}
	__forceinline Matrix4 Transpose() const
	{
		return Matrix4(
			Vector4(Row[0][0], Row[1][0], Row[2][0], Row[3][0]),
			Vector4(Row[0][1], Row[1][1], Row[2][1], Row[3][1]),
			Vector4(Row[0][2], Row[1][2], Row[2][2], Row[3][2]),
			Vector4(Row[0][3], Row[1][3], Row[2][3], Row[3][3]));
	}
	__forceinline Matrix4 &operator=(const Matrix4 &m)
	{
		Row[0] = m.Row[0]; Row[1] = m.Row[1]; Row[2] = m.Row[2]; Row[3] = m.Row[3];
		return *this;
	}

protected:
	Vector4 Row[4];
};

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
	StringClass(int initial_len = 0, bool hint_temporary = false);
	~StringClass() { Free_String(); }
private:
	char *m_Buffer;
	void Free_String();
};

class WW3D
{
public:
	static bool Is_Snapshot_Activated() { return SnapshotActivated; }
private:
	static bool SnapshotActivated;
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

class ShaderClass
{
	friend class DX8Wrapper;
public:
	static ShaderClass _PresetMultiplicativeSpriteShader;
	unsigned ShaderBits;
protected:
	static bool ShaderDirty;
};

class TextureBaseClass
{
public:
	void Release_Ref();
	IDirect3DBaseTexture8 *Peek_D3D_Base_Texture() const;
};
class TextureClass : public TextureBaseClass
{
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
	RvaTextureHandleView rva00072B3A() const;
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

struct RenderStateStruct
{
	ShaderClass shader;
	VertexMaterialClass *material;
	char pad08[0x1EC - 0x08];
	Matrix4 world, view;
};

class DX8Wrapper
{
public:
	enum ChangedStates { MATERIAL_CHANGED = 1 << 14, SHADER_CHANGED = 1 << 15 };
	static void Apply_Render_State_Changes(void);
	static void Get_DX8_Render_State_Value_Name(StringClass &name, D3DRENDERSTATETYPE state, unsigned value);
	static void Get_DX8_Texture_Stage_State_Value_Name(StringClass &name, D3DTEXTURESTAGESTATETYPE state, unsigned value);

	static __forceinline void Set_Material(const VertexMaterialClass *material)
	{
		VertexMaterialClass *m = const_cast<VertexMaterialClass *>(material);
		if (m) m->Add_Ref();
		if (render_state.material) render_state.material->Release_Ref();
		render_state.material = m;
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
	static __forceinline void Set_DX8_Render_State(D3DRENDERSTATETYPE state, unsigned value)
	{
		if (RenderStates[state] == value) return;
		if (WW3D::Is_Snapshot_Activated()) {
			StringClass value_name(0, true);
			Get_DX8_Render_State_Value_Name(value_name, state, value);
		}
		RenderStates[state] = value;
		D3DDevice->SetRenderState(state, value);
		number_of_DX8_calls++;
		render_state_changes++;
	}
	static __forceinline void Set_DX8_Texture_Stage_State(unsigned stage, D3DTEXTURESTAGESTATETYPE state, unsigned value)
	{
		if (stage >= 16) {
			D3DDevice->SetTextureStageState(stage, state, value);
			number_of_DX8_calls++;
			return;
		}
		if (TextureStageStates[stage][state] == value) return;
		if (WW3D::Is_Snapshot_Activated()) {
			StringClass value_name(0, true);
			Get_DX8_Texture_Stage_State_Value_Name(value_name, state, value);
		}
		TextureStageStates[stage][state] = value;
		D3DDevice->SetTextureStageState(stage, state, value);
		number_of_DX8_calls++;
		texture_stage_state_changes++;
	}
	static __forceinline void Set_DX8_Texture(unsigned int stage, IDirect3DBaseTexture8 *texture)
	{
		if (stage >= 16) {
			D3DDevice->SetTexture(stage, texture);
			number_of_DX8_calls++;
			return;
		}
		if (Textures[stage] == texture) return;
		if (Textures[stage]) Textures[stage]->Release();
		Textures[stage] = texture;
		if (Textures[stage]) Textures[stage]->AddRef();
		D3DDevice->SetTexture(stage, texture);
		number_of_DX8_calls++;
		texture_changes++;
	}
	static __forceinline void GetView(Matrix4 &m)
	{
		if (render_state_changed & (1 << 19))
			m.Make_Identity();
		else
			m = render_state.view.Transpose();
	}
	static __forceinline void SetMatrix(unsigned state, const D3DXMATRIX &m)
	{
		++matrix_changes;
		D3DDevice->SetTransform(state, &m);
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
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual int set(int stage);
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

	DX8Wrapper::Set_DX8_Texture_Stage_State(stage, 11, 0x20000);	// TEXCOORDINDEX, TCI_CAMERASPACEPOSITION
	DX8Wrapper::Set_DX8_Texture_Stage_State(stage, 24, 2);		// TEXTURETRANSFORMFLAGS, TTFF_COUNT2
	DX8Wrapper::Set_DX8_Render_State(23, 3);				// ZFUNC, CMP_EQUAL

	Rva00072B3A *shroud;
	if ((shroud = TheTerrainRenderObject->shroud) != 0)
	{
		if (shroud->rva00072B3A().ptr != 0)
			DX8Wrapper::Set_DX8_Texture(stage, shroud->rva00072B3A().texture().Peek_D3D_Base_Texture());

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
		DX8Wrapper::SetMatrix(16 + stage, *((D3DXMATRIX *)&curView));
	}
	m_stageOfSet = stage;
	return 1;
}
