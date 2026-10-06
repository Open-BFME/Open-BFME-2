// cl: /O1 /EHsc /MD /arch:SSE
// fxshadersetup.cpp -- FXShaderSetup pass/rendering hooks recovered from
// WorldBuilder leads (reverse/wb_name_leads.csv): WB's debug build names the
// functions (vtable pairing) and the member m_ShaderAsset at +0x08; retail
// supplies the bytes.
//
// m_ShaderAsset is a reference holder whose first dword is the asset; its
// out-of-line getter (0x0015148D, rowed under a placeholder name) ensures the
// asset is loaded and returns the D3DX effect. Effect calls are COM stdcall
// virtuals: BeginPass at +0x100, EndPass at +0x108, End at +0x10C.

typedef unsigned int UINT;
typedef unsigned long DWORD;
typedef long HRESULT;
typedef const char *D3DXHANDLE;
#define FAILED(hr) ((HRESULT)(hr) < 0)

struct IDirect3DBaseTexture8;

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

#define FX_SLOT(n) virtual HRESULT __stdcall slot##n() = 0;

struct ID3DXEffectView
{
	FX_SLOT(00) FX_SLOT(01) FX_SLOT(02) FX_SLOT(03) FX_SLOT(04) FX_SLOT(05) FX_SLOT(06) FX_SLOT(07)
	FX_SLOT(08) FX_SLOT(09) FX_SLOT(10) FX_SLOT(11) FX_SLOT(12) FX_SLOT(13) FX_SLOT(14) FX_SLOT(15)
	FX_SLOT(16) FX_SLOT(17) FX_SLOT(18) FX_SLOT(19) FX_SLOT(20) FX_SLOT(21) FX_SLOT(22) FX_SLOT(23)
	FX_SLOT(24) FX_SLOT(25) FX_SLOT(26) FX_SLOT(27) FX_SLOT(28) FX_SLOT(29) FX_SLOT(30) FX_SLOT(31)
	FX_SLOT(32) FX_SLOT(33) FX_SLOT(34) FX_SLOT(35) FX_SLOT(36) FX_SLOT(37) FX_SLOT(38) FX_SLOT(39)
	FX_SLOT(40) FX_SLOT(41) FX_SLOT(42) FX_SLOT(43) FX_SLOT(44) FX_SLOT(45) FX_SLOT(46) FX_SLOT(47)
	FX_SLOT(48) FX_SLOT(49) FX_SLOT(50) FX_SLOT(51)
	virtual HRESULT __stdcall SetTexture(D3DXHANDLE parameter, IDirect3DBaseTexture8 *texture) = 0;	// +0xD0
	FX_SLOT(53) FX_SLOT(54) FX_SLOT(55)
	FX_SLOT(56) FX_SLOT(57)
	virtual HRESULT __stdcall SetTechnique(D3DXHANDLE technique) = 0;	// +0xE8
	FX_SLOT(59) FX_SLOT(60) FX_SLOT(61) FX_SLOT(62)
	virtual HRESULT __stdcall Begin(UINT *passes, DWORD flags) = 0;	// +0xFC
	virtual HRESULT __stdcall BeginPass(UINT pass) = 0;	// +0x100
	FX_SLOT(65)
	virtual HRESULT __stdcall EndPass() = 0;		// +0x108
	virtual HRESULT __stdcall End() = 0;			// +0x10C
	FX_SLOT(68) FX_SLOT(69) FX_SLOT(70) FX_SLOT(71)
	FX_SLOT(72) FX_SLOT(73) FX_SLOT(74)
	virtual HRESULT __stdcall SetStateManager(void *manager) = 0;	// +0x12C
};

#undef FX_SLOT

// Reference holder for the shader asset (placeholder-named in the ledger).
class Rva0015148D
{
public:
	void *rva0015148D();			// 0x0015148D, loaded effect or NULL
	void *rva001514B2(int arg, int technique);	// 0x001514B2
	bool IsValid() const { return m_asset != 0; }
	ID3DXEffectView *Peek_Effect() { return (ID3DXEffectView *)rva0015148D(); }

private:
	void *m_asset;
};

// One texture binding: effect parameter handle plus a texture reference.
struct FXTextureBinding
{
	D3DXHANDLE m_parameter;
	TextureBaseClass m_texture;
	unsigned char m_pad[3];
};

class FXShaderSetup
{
public:
	virtual bool Begin_Rendering(UINT *passes, int arg);
	virtual void Begin_Pass(UINT pass);
	virtual void End_Pass();
	virtual void End_Rendering();

private:
	unsigned char m_pad04[4];
	Rva0015148D m_ShaderAsset;		// +0x08
	unsigned char m_pad0C[0x20 - 0xc];
	D3DXHANDLE m_Technique;			// +0x20
	void *m_StateManager;			// +0x24
	FXTextureBinding *m_texturesStart;	// +0x28
	FXTextureBinding *m_texturesFinish;	// +0x2C
};

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
	if (m_StateManager)
		effect->SetStateManager(m_StateManager);
	for (FXTextureBinding *it = m_texturesStart; it != m_texturesFinish; ++it)
		effect->SetTexture(it->m_parameter, it->m_texture.Peek_D3D_Base_Texture());
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
