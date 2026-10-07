// cl: /O1 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// stlport
//
// fxshadersetup.cpp -- FXShaderSetup, the per-material FX shader binding.
// WorldBuilder's debug build names the class and its functions through its
// asserts (FXShaderSetup::Begin_Rendering .. End_Rendering,
// UpdateParameterList, Load_W3D, InitializeShader; vtable pairing for the
// pass hooks) and the member m_ShaderAsset at +0x08; retail supplies the
// bytes.
//
// Layout, 0x34 bytes (operator new in Create 0x00152C47), from the ctors
// 0x001525FB / 0x00152DE9 and the dtor 0x00152411: the vtable 0x00BD3B1C
// over the ref-count base 0x00BC650C (slot 0 Delete_This, count at +4),
// the asset holder at +0x08, the parameter list at +0x0C (out-of-line ctor
// 0x001F81BF, vector dtor 0x0007C5D5), the technique name at +0x18, the LOD
// at +0x1C (4 = unset), the technique handle at +0x20, the effect parameter
// block at +0x24 and the texture bindings at +0x28 (8-byte elements, vector
// dtor 0x00152118).
//
// m_ShaderAsset is a reference holder whose first dword is the asset; its
// out-of-line getter (0x0015148D, rowed under a placeholder name) ensures the
// asset is loaded and returns the D3DX effect. Effect calls are COM stdcall
// virtuals in d3dx9effect.h's ID3DXEffect order.

#include <vector>
#include "ascii_string.h"

typedef unsigned int UINT;
typedef unsigned long DWORD;
typedef long HRESULT;
typedef int BOOL;
typedef const char *D3DXHANDLE;
#define FAILED(hr) ((HRESULT)(hr) < 0)

struct IDirect3DBaseTexture8;

struct D3DXTECHNIQUE_DESC
{
	const char *Name;
	UINT Passes;
	UINT Annotations;
};

struct D3DXVECTOR4
{
	D3DXVECTOR4(float fx, float fy, float fz, float fw) : x(fx), y(fy), z(fz), w(fw) {}
	operator float *() { return &x; }

	float x, y, z, w;
};

class TextureBaseClass
{
public:
	IDirect3DBaseTexture8 *Peek_D3D_Base_Texture() const;	// 0x0013270C
};

class DX8Wrapper
{
public:
	static void Apply_Render_State_Changes();		// 0x0011D930
};

void Rva00129670Inc();						// 0x00129670, render statistics counter

void BFME_DX8_Thread_Lock();
bool BFME_DX8_Thread_Assert();

class BFMEDX8DeviceLock
{
public:
	BFMEDX8DeviceLock() { BFME_DX8_Thread_Lock(); }
	~BFMEDX8DeviceLock() { BFME_DX8_Thread_Assert(); }
};

class ChunkLoadClass
{
public:
	bool Open_Chunk();
	bool Close_Chunk();
	unsigned long Read(void *buf, unsigned long nbytes);
};

// W3D_CHUNK_FX_SHADER_INFO, after its version byte.
struct W3dFXShaderInfoStruct
{
	char ShaderName[32];
	unsigned char Technique;
	unsigned char Padding[3];
};

#define FX_SLOT(n) virtual HRESULT __stdcall slot##n() = 0;

struct ID3DXEffectView
{
	FX_SLOT(00) FX_SLOT(01) FX_SLOT(02) FX_SLOT(03) FX_SLOT(04)
	virtual HRESULT __stdcall GetTechniqueDesc(D3DXHANDLE technique, D3DXTECHNIQUE_DESC *desc) = 0;	// +0x14
	FX_SLOT(06) FX_SLOT(07) FX_SLOT(08)
	virtual D3DXHANDLE __stdcall GetParameterByName(D3DXHANDLE parent, const char *name) = 0;	// +0x24
	FX_SLOT(10) FX_SLOT(11)
	virtual D3DXHANDLE __stdcall GetTechnique(UINT index) = 0;		// +0x30
	virtual D3DXHANDLE __stdcall GetTechniqueByName(const char *name) = 0;	// +0x34
	FX_SLOT(14) FX_SLOT(15) FX_SLOT(16) FX_SLOT(17) FX_SLOT(18) FX_SLOT(19) FX_SLOT(20) FX_SLOT(21)
	virtual HRESULT __stdcall SetBool(D3DXHANDLE parameter, BOOL value) = 0;	// +0x58
	FX_SLOT(23) FX_SLOT(24) FX_SLOT(25)
	virtual HRESULT __stdcall SetInt(D3DXHANDLE parameter, int value) = 0;	// +0x68
	FX_SLOT(27) FX_SLOT(28) FX_SLOT(29)
	virtual HRESULT __stdcall SetFloat(D3DXHANDLE parameter, float value) = 0;	// +0x78
	FX_SLOT(31) FX_SLOT(32) FX_SLOT(33)
	virtual HRESULT __stdcall SetVector(D3DXHANDLE parameter, const D3DXVECTOR4 *vector) = 0;	// +0x88
	FX_SLOT(35) FX_SLOT(36) FX_SLOT(37) FX_SLOT(38) FX_SLOT(39)
	FX_SLOT(40) FX_SLOT(41) FX_SLOT(42) FX_SLOT(43) FX_SLOT(44) FX_SLOT(45) FX_SLOT(46) FX_SLOT(47)
	FX_SLOT(48) FX_SLOT(49) FX_SLOT(50) FX_SLOT(51)
	virtual HRESULT __stdcall SetTexture(D3DXHANDLE parameter, IDirect3DBaseTexture8 *texture) = 0;	// +0xD0
	FX_SLOT(53) FX_SLOT(54) FX_SLOT(55)
	FX_SLOT(56) FX_SLOT(57)
	virtual HRESULT __stdcall SetTechnique(D3DXHANDLE technique) = 0;	// +0xE8
	FX_SLOT(59) FX_SLOT(60) FX_SLOT(61)
	virtual BOOL __stdcall IsParameterUsed(D3DXHANDLE parameter, D3DXHANDLE technique) = 0;	// +0xF8
	virtual HRESULT __stdcall Begin(UINT *passes, DWORD flags) = 0;	// +0xFC
	virtual HRESULT __stdcall BeginPass(UINT pass) = 0;	// +0x100
	FX_SLOT(65)
	virtual HRESULT __stdcall EndPass() = 0;		// +0x108
	virtual HRESULT __stdcall End() = 0;			// +0x10C
	FX_SLOT(68) FX_SLOT(69) FX_SLOT(70) FX_SLOT(71)
	FX_SLOT(72)
	virtual HRESULT __stdcall BeginParameterBlock() = 0;	// +0x124
	virtual D3DXHANDLE __stdcall EndParameterBlock() = 0;	// +0x128
	virtual HRESULT __stdcall ApplyParameterBlock(D3DXHANDLE block) = 0;	// +0x12C
	virtual HRESULT __stdcall DeleteParameterBlock(D3DXHANDLE block) = 0;	// +0x130
};

#undef FX_SLOT

// The asset and texture holders release through the shared Release_Ref
// body at 0x0061ED10 (rowed as TextureClass::Release_Ref).
class TextureClass
{
public:
	void Add_Ref();
	void Release_Ref();
};

template <class T>
class RefCountPtr
{
public:
	RefCountPtr() : m_ptr(0) {}
	explicit RefCountPtr(T *ptr) : m_ptr(ptr) {}
	RefCountPtr(const RefCountPtr &that) : m_ptr(that.m_ptr)
	{
		if (m_ptr)
			m_ptr->Add_Ref();
	}
	~RefCountPtr()
	{
		if (m_ptr)
			m_ptr->Release_Ref();
	}
	const RefCountPtr &operator=(const RefCountPtr &that);	// 0x000424D0 for TextureClass
	T *operator->() const { return m_ptr; }

	T *m_ptr;
};

class BFME2ParticleTextureHandle : public RefCountPtr<TextureClass>
{
};

BFME2ParticleTextureHandle BFME2LoadParticleTexture(const char *filename, int a, int b);	// 0x00132D89

// One FX shader parameter (FXShader::Parameter, 0x24 bytes); the vector
// helpers are rowed under this placeholder element name.
struct Rva0007BB16Record
{
	Rva0007BB16Record();
	Rva0007BB16Record(const Rva0007BB16Record &that);
	~Rva0007BB16Record();
	Rva0007BB16Record &operator=(const Rva0007BB16Record &that);

	AsciiString m_name;	// +0x00
	int m_type;		// +0x04, the parameter type (1 texture .. 7 bool)
	AsciiString m_08;	// +0x08, the texture name of a texture parameter
	float m_vector[4];	// +0x0C
	int m_int;		// +0x1C
	bool m_bool;		// +0x20
};

typedef _STL::vector<Rva0007BB16Record> FXShaderParameterVector;

namespace FXShader
{
struct Parameter
{
	bool Load_W3D(ChunkLoadClass *cload);	// 0x0015115C
};
}

struct Rva00082EB8Rec;

// The setup's parameter list: the vector plus its set-or-append (0x00082EB8,
// a case-insensitive name match replaces the record, else push_back).
class Rva00082EB8 : public FXShaderParameterVector
{
public:
	void rva00082EB8(const Rva00082EB8Rec &rec);
};

// One texture binding: the effect parameter and its texture.
class Rva00151DAB
{
public:
	D3DXHANDLE m_parameter;			// +0
	RefCountPtr<TextureClass> m_texture;	// +4
};

class FXShaderAsset
{
public:
	virtual const char *Get_Name() const;	// +0x00, the name the asset is looked up by
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual bool Is_Initialized();	// +0x28
};

class CreateAHeroData;
struct BfmeE16;

// The asset holder's out-of-line members, rowed under placeholder classes.
class Rva0015168C
{
public:
	bool rva0015168C(CreateAHeroData *technique);	// 0x0015168C: the asset validated the technique
};

class Rva001518D1
{
public:
	_STL::vector<BfmeE16> *rva001518D1();		// 0x001518D1: the asset's default parameters
};

class BfmeResetTextureRef
{
public:
	void clear();					// 0x0004D75B
};

// Reference holder for the shader asset (placeholder-named in the ledger).
class Rva0015148D
{
public:
	Rva0015148D() : m_asset(0) {}
	~Rva0015148D()
	{
		if (m_asset)
			((TextureClass *)m_asset)->Release_Ref();
	}
	Rva0015148D &operator=(const Rva0015148D &that)
	{
		*(RefCountPtr<TextureClass> *)this = *(const RefCountPtr<TextureClass> *)&that;
		return *this;
	}

	void *rva0015148D();			// 0x0015148D, loaded effect or NULL
	void *rva001514B2(int arg, int technique);	// 0x001514B2
	bool IsValid() const { return m_asset != 0; }
	const char *Get_Name() const { return m_asset ? m_asset->Get_Name() : 0; }
	bool Is_Loaded() const { return m_asset ? m_asset->Is_Initialized() : false; }
	ID3DXEffectView *Peek_Effect() { return (ID3DXEffectView *)rva0015148D(); }
	bool Has_Technique(D3DXHANDLE technique)
	{
		return ((Rva0015168C *)this)->rva0015168C((CreateAHeroData *)technique);
	}
	const Rva00082EB8 &Default_Parameters()
	{
		return *(const Rva00082EB8 *)((Rva001518D1 *)this)->rva001518D1();
	}
	void Clear() { ((BfmeResetTextureRef *)this)->clear(); }

private:
	FXShaderAsset *m_asset;
};

// The holder returned by the asset lookup.
class Rva0015145C : public Rva0015148D
{
};

Rva0015145C Rva001514F5_MakeOwner(const char *name);	// 0x001514F5

// A substring view {string, start, length}: built by 0x000B6AA9, copied
// out by 0x000B980E.
struct Rva000B6AA9Rec
{
	operator AsciiString();

	AsciiString *m_string;
	int m_start;
	int m_len;
};

Rva000B6AA9Rec *__cdecl Rva000B6AA9Build(Rva000B6AA9Rec *dest, void **srcpp, int val);
int Rva00151ECDLen(const char *src);

class Rva000B980E
{
public:
	void rva000B980E(char *dest, int start, int len);
};

class Rva000B3F84Pair
{
public:
	const char *m_ptr;
	int m_len;
};

struct AsciiStringRef
{
	const AsciiString *m_string;
};

// "string + text"
struct AsciiStringPlusText : AsciiStringRef
{
	operator AsciiString();

	Rva000B3F84Pair m_right;
};

AsciiStringPlusText operator+(const AsciiString &left, const char *right);

// The shader LOD (2 = high), read through the getter 0x0006E16F elsewhere.
extern int g_Va00DB5FA0;

// The technique-name suffix per LOD: low, medium, high, ultra.
static const char s_lodSuffixes[4][4] = { "_L", "_M", "", "_U" };

class RefCountClass
{
public:
	RefCountClass() : NumRefs(1) {}
	void Add_Ref() { NumRefs++; }
	void Release_Ref()
	{
		if (--NumRefs == 0)
			Delete_This();
	}
	virtual void Delete_This();

protected:
	virtual ~RefCountClass() {}

	int NumRefs;
};

class FXShaderSetup : public RefCountClass
{
public:
	FXShaderSetup();
	FXShaderSetup(const FXShaderSetup &that);
	FXShaderSetup &operator=(const FXShaderSetup &that);

	virtual bool Begin_Rendering(UINT *passes, int arg);
	virtual void Begin_Pass(UINT pass);
	virtual void UpdateDynamicParameterSet(UINT pass);
	virtual void End_Pass();
	virtual void End_Rendering();

	static RefCountPtr<FXShaderSetup> Create(const char *shaderName, const char *techniqueName,
		const FXShaderParameterVector *parameters, int lod);
	bool InitializeShader(const char *shaderName, const char *techniqueName,
		const FXShaderParameterVector *parameters, int lod);
	bool UpdateParameterList(const FXShaderParameterVector &parameters);
	bool Load_W3D(ChunkLoadClass &cload);

protected:
	virtual ~FXShaderSetup();

private:
	Rva0015148D m_ShaderAsset;		// +0x08
	Rva00082EB8 m_Parameters;		// +0x0C
	AsciiString m_TechniqueName;		// +0x18
	int m_LOD;				// +0x1C
	D3DXHANDLE m_Technique;			// +0x20
	D3DXHANDLE m_ParameterBlock;		// +0x24
	_STL::vector<Rva00151DAB> m_Textures;	// +0x28
};

// Rva000B6AA9Rec::operator AsciiString, retail 0x001520B4.
Rva000B6AA9Rec::operator AsciiString()
{
	AsciiString result;
	((Rva000B980E *)this)->rva000B980E(((StringBase<char> *)&result)->getBufferForRead(m_len), m_start, m_len);
	return result;
}

// FXShaderSetup::Begin_Rendering, retail 0x00151EE2.
bool FXShaderSetup::Begin_Rendering(UINT *passes, int arg)
{
	*passes = 0;
	if (!m_ShaderAsset.IsValid() || !m_ShaderAsset.Peek_Effect() || !m_Technique)
		return false;
	DX8Wrapper::Apply_Render_State_Changes();
	ID3DXEffectView *effect = m_ShaderAsset.Peek_Effect();
	if (FAILED(effect->SetTechnique(m_Technique)))
		return false;
	if (m_ParameterBlock)
		effect->ApplyParameterBlock(m_ParameterBlock);
	for (Rva00151DAB *it = m_Textures.begin(); it != m_Textures.end(); ++it)
		effect->SetTexture(it->m_parameter, ((const TextureBaseClass *)&it->m_texture)->Peek_D3D_Base_Texture());
	m_ShaderAsset.rva001514B2(arg, (int)m_Technique);
	if (FAILED(effect->Begin(passes, 6)))
		return false;
	Rva00129670Inc();
	return true;
}

// FXShaderSetup::Begin_Pass, retail 0x00151CEE.
void FXShaderSetup::Begin_Pass(UINT pass)
{
	if (m_ShaderAsset.IsValid() && m_ShaderAsset.Peek_Effect())
		m_ShaderAsset.Peek_Effect()->BeginPass(pass);
}

// FXShaderSetup::End_Pass, retail 0x00151D5F.
void FXShaderSetup::End_Pass()
{
	if (m_ShaderAsset.IsValid() && m_ShaderAsset.Peek_Effect())
		m_ShaderAsset.Peek_Effect()->EndPass();
}

// FXShaderSetup::End_Rendering, retail 0x00151D85.
void FXShaderSetup::End_Rendering()
{
	if (m_ShaderAsset.IsValid() && m_ShaderAsset.Peek_Effect())
		m_ShaderAsset.Peek_Effect()->End();
}

// FXShaderSetup::~FXShaderSetup, retail 0x00152411.
// ??1FXShaderSetup@@MAE@XZ present-unmatched
FXShaderSetup::~FXShaderSetup()
{
	if (m_ParameterBlock) {
		BFMEDX8DeviceLock lock;
		if (m_ShaderAsset.Is_Loaded())
			m_ShaderAsset.Peek_Effect()->DeleteParameterBlock(m_ParameterBlock);
		m_ParameterBlock = 0;
	}
}

// FXShaderSetup::UpdateParameterList, retail 0x0015265E: the asset's
// defaults overridden by the given records, recorded into a parameter block.
bool FXShaderSetup::UpdateParameterList(const FXShaderParameterVector &parameters)
{
	if (!m_ShaderAsset.IsValid() || !m_ShaderAsset.Peek_Effect() || !m_Technique)
		return false;
	if (m_ParameterBlock) {
		m_ShaderAsset.Peek_Effect()->DeleteParameterBlock(m_ParameterBlock);
		m_ParameterBlock = 0;
	}
	m_Textures.clear();
	m_Parameters = m_ShaderAsset.Default_Parameters();
	for (const Rva0007BB16Record *it = parameters.begin(); it != parameters.end(); ++it)
		m_Parameters.rva00082EB8(*(const Rva00082EB8Rec *)it);
	if (!m_Parameters.empty()) {
		ID3DXEffectView *effect = m_ShaderAsset.Peek_Effect();
		if (FAILED(effect->BeginParameterBlock()))
			return false;
		for (Rva0007BB16Record *parameter = m_Parameters.begin(); parameter != m_Parameters.end(); ++parameter) {
			D3DXHANDLE handle = effect->GetParameterByName(0, parameter->m_name.str());
			if (handle && effect->IsParameterUsed(handle, m_Technique)) {
				if (parameter->m_type == 1) {
					Rva00151DAB binding;
					binding.m_parameter = handle;
					binding.m_texture = BFME2LoadParticleTexture(parameter->m_08.str(), 0, 0);
					m_Textures.push_back(binding);
				} else if (parameter->m_type == 2) {
					effect->SetFloat(handle, parameter->m_vector[0]);
				} else if (parameter->m_type >= 3 && parameter->m_type <= 5) {
					D3DXVECTOR4 vector(0.0f, 0.0f, 0.0f, 0.0f);
					memcpy((float *)vector, parameter->m_vector, (parameter->m_type - 1) * sizeof(float));
					effect->SetVector(handle, &vector);
				} else if (parameter->m_type == 6) {
					effect->SetInt(handle, parameter->m_int);
				} else if (parameter->m_type == 7) {
					effect->SetBool(handle, parameter->m_bool);
				} else {
					return false;
				}
			}
		}
		m_ParameterBlock = effect->EndParameterBlock();
		if (!m_ParameterBlock)
			return false;
	}
	return true;
}

// FXShaderSetup::InitializeShader, retail 0x0015288F: binds the named
// shader and the technique closest to the requested LOD.
bool FXShaderSetup::InitializeShader(const char *shaderName, const char *techniqueName,
	const FXShaderParameterVector *parameters, int lod)
{
	BFMEDX8DeviceLock lock;
	if (m_ParameterBlock) {
		if (m_ShaderAsset.IsValid())
			m_ShaderAsset.Peek_Effect()->DeleteParameterBlock(m_ParameterBlock);
		m_ParameterBlock = 0;
	}
	m_ShaderAsset.Clear();
	m_Parameters.clear();
	m_TechniqueName.clear();
	m_LOD = 4;
	m_Technique = 0;
	m_Textures.clear();

	Rva0015145C asset = Rva001514F5_MakeOwner(shaderName);
	if (!asset.IsValid() || !asset.Peek_Effect())
		return false;
	ID3DXEffectView *effect = asset.Peek_Effect();

	int lodLimit = g_Va00DB5FA0;
	if (lod != 4)
		lodLimit = lod;

	AsciiString name(techniqueName);
	int nameLOD = 2;
	int i;
	for (i = 0; i < 4; i++) {
		if (s_lodSuffixes[i][0] && name.endsWithNoCase(s_lodSuffixes[i])) {
			Rva000B6AA9Rec left;
			name = *Rva000B6AA9Build(&left, (void **)&name, name.getLength() - Rva00151ECDLen(s_lodSuffixes[i]));
			nameLOD = i;
			break;
		}
	}
	if (nameLOD == 2 && lodLimit == 3)
		nameLOD = 3;
	nameLOD = _STL::min(nameLOD, lodLimit);

	D3DXHANDLE technique = 0;
	for (i = nameLOD; i >= 0; i--) {
		AsciiString fullName = name + s_lodSuffixes[i];
		technique = effect->GetTechniqueByName(fullName.str());
		if (technique && asset.Has_Technique(technique))
			break;
		technique = 0;
	}
	if (!technique) {
		for (i = nameLOD + 1; i < 4; i++) {
			AsciiString fullName = name + s_lodSuffixes[i];
			technique = effect->GetTechniqueByName(fullName.str());
			if (technique && asset.Has_Technique(technique))
				break;
			technique = 0;
		}
	}
	if (!technique)
		return false;

	m_ShaderAsset = asset;
	m_TechniqueName = techniqueName;
	m_LOD = i;
	m_Technique = technique;
	if (parameters && !UpdateParameterList(*parameters))
		return false;
	return true;
}

// FXShaderSetup::FXShaderSetup, retail 0x001525FB.
FXShaderSetup::FXShaderSetup() : m_LOD(4), m_Technique(0), m_ParameterBlock(0)
{
}

// FXShaderSetup::Create, retail 0x00152C47.
// ?Create@FXShaderSetup@@SA?AV?$RefCountPtr@VFXShaderSetup@@@@PBD0PBV?$vector@URva0007BB16Record@@V?$allocator@URva0007BB16Record@@@_STL@@@_STL@@H@Z present-unmatched
RefCountPtr<FXShaderSetup> FXShaderSetup::Create(const char *shaderName, const char *techniqueName,
	const FXShaderParameterVector *parameters, int lod)
{
	BFMEDX8DeviceLock lock;
	RefCountPtr<FXShaderSetup> setup(new FXShaderSetup);
	if (!setup->InitializeShader(shaderName, techniqueName, parameters, lod))
		return RefCountPtr<FXShaderSetup>();
	return setup;
}

// FXShaderSetup::FXShaderSetup(const FXShaderSetup &), retail 0x00152DE9.
// ??0FXShaderSetup@@QAE@ABV0@@Z present-unmatched
FXShaderSetup::FXShaderSetup(const FXShaderSetup &that) : m_Technique(0), m_ParameterBlock(0)
{
	*this = that;
}

// FXShaderSetup::operator=, retail 0x00152CDA: re-initialises from the
// other setup's shader, technique and parameters at the default LOD.
FXShaderSetup &FXShaderSetup::operator=(const FXShaderSetup &that)
{
	if (this != &that)
		InitializeShader(that.m_ShaderAsset.Get_Name(), that.m_TechniqueName.str(), &that.m_Parameters, 4);
	return *this;
}

// FXShaderSetup::Load_W3D, retail 0x00152E4D: W3D_CHUNK_FX_SHADER_INFO and
// one W3D_CHUNK_FX_SHADER_CONSTANT chunk per parameter.
bool FXShaderSetup::Load_W3D(ChunkLoadClass &cload)
{
	if (!cload.Open_Chunk())
		return false;
	unsigned char versionNumber = 0;
	if (cload.Read(&versionNumber, sizeof(versionNumber)) != sizeof(versionNumber))
		return false;
	W3dFXShaderInfoStruct info;
	if (cload.Read(&info, sizeof(info)) != sizeof(info))
		return false;
	cload.Close_Chunk();

	BFMEDX8DeviceLock lock;
	Rva0015145C asset = Rva001514F5_MakeOwner(info.ShaderName);
	if (!asset.IsValid() || !asset.Peek_Effect())
		return false;
	ID3DXEffectView *effect = asset.Peek_Effect();
	D3DXHANDLE initialTechnique = effect->GetTechnique(info.Technique);
	if (!initialTechnique)
		return false;
	D3DXTECHNIQUE_DESC initialTechniqueDesc;
	if (FAILED(effect->GetTechniqueDesc(initialTechnique, &initialTechniqueDesc)))
		return false;

	FXShaderParameterVector parameters;
	parameters.reserve(8);
	while (cload.Open_Chunk()) {
		parameters.resize(parameters.size() + 1);
		if (!((FXShader::Parameter &)parameters.back()).Load_W3D(&cload))
			return false;
		cload.Close_Chunk();
	}
	if (!InitializeShader(info.ShaderName, initialTechniqueDesc.Name, &parameters, 4))
		return false;
	return true;
}
