// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// preRender is slot 2, native 0x000F9C9D..0x000F9D94 (247B; RET8).
// Clean donor: BFME 1 f98983a7 game/GameEngineDevice/Source/W3DDevice/
// GameClient/ScreenFilterRva007DCA80PreRender.cpp. Target bytes independently
// prove six scene passes, the +0x14 amount and +0x18 sample count, the +0x1C
// saved glow flag, +0x30 restore flag, +0x34 kernel and +0x4C target surface.
// BFME 2's GlobalData flag is +0xD34 and its named Gaussian helper consumes
// the same six-word block as init. The parameter assignment order preserves
// retail's SSE scheduling; the entire body and its relocations match.
//
// ?init@Rva007DCA80@@UAEHXZ, retail 0x000F9D94..0x000F9F82 (494 bytes).
// Slot 0 of vftable 0x007CF2F8 whose slot 1 is the rowed shutdown 0x000FA8AE
// (?shutdown@Rva007DCA80@@UAEHXZ) and whose ctor-style init 0x000FA83B
// installs it. WorldBuilder places the twin in W3DScreenSmokeGlowFilter.cpp
// (its debug strings name W3DScreenSmokeGlowFilter::m_renderTexture1/2); the
// address-derived class name of the shutdown row is kept.
//
// When render to texture is available it loads the ExVapor01/02 textures
// into the holders at +0x58/+0x5C (clearing filter words +0x0C/+0x10 of
// each) and the hilight filter vertex/pixel shaders into +0x08/+0x04; then
// creates two square A8R8G8B8 render targets of the settings size (+0x0C of
// the block behind 0x00309E4B, stored at +0x2C) into +0x40/+0x44 with their
// level-0 surfaces at +0x4C/+0x50, builds the gaussian kernel at +0x34 and
// registers itself in W3DFilters[5] (0x00DE1F40). Retail shutdown's
// filter loop starts at 0x00DE1F2C, so this is slot 5 of its ten entries.
// A shader or texture
// creation failure calls shutdown (slot 1) and returns FALSE.
//
// Callees are the ledger's rows: 0x00132D89 BFME2LoadParticleTexture,
// 0x000424D0 RefCountPtr<TextureClass>::operator=, 0x0061ED10 Release_Ref,
// 0x00132856 ShroudTexture::getFilter, 0x00077C19/0x00077D0F shader loads,
// 0x00309E4B settings getter; 0x000F630C is called by its pinned bool name
// (callers test AL) and 0x000780BC createGaussianVector by its pin.

class TextureClass
{
public:
	void Release_Ref();
};

template <class T> class RefCountPtr
{
public:
	~RefCountPtr()
	{
		if (Ptr)
			Ptr->Release_Ref();
	}
	const RefCountPtr &operator=(const RefCountPtr &other);
	T *Ptr;
};

class BFME2ParticleTextureHandle : public RefCountPtr<TextureClass>
{
};

BFME2ParticleTextureHandle BFME2LoadParticleTexture(const char *name, int a, int b);

class ShroudFilter
{
public:
	int m_pad00[3];
	int m_0C;
	int m_10;
};

class ShroudTexture
{
public:
	ShroudFilter *getFilter(void);
};

class W3DShaderManager
{
public:
	static bool canRenderToTexture(void);
	static void createGaussianVector(void *kernel, struct BfmeGaussianParams *params);
};

long __cdecl Rva00077C19Load(const char *path, unsigned *shader);
long __cdecl Rva00077D0FLoad(const char *path, unsigned long *shader);

// The settings block behind Rva00309E4BGet.
struct BfmeGaussianSettings
{
	char m_pad00[4];
	int m_taps; // +0x04
	char m_pad08[0x0C - 0x08];
	int m_size; // +0x0C
	float m_10;
	float m_14;
	float m_18;
	float m_1C;
};
int Rva00309E4BGet();

struct BfmeGaussianParams
{
	int m_mode;
	int m_taps;
	float m_10;
	float m_14;
	float m_18;
	float m_1C;
};

// IDirect3DTexture9::GetSurfaceLevel is slot 18; IDirect3DDevice9::
// CreateTexture is slot 23.
struct BfmeD3DSurface;
struct BfmeD3DTexture
{
	virtual long __stdcall QueryInterface(const void *riid, void **ppv) = 0;
	virtual unsigned long __stdcall AddRef() = 0;
	virtual unsigned long __stdcall Release() = 0;
#define G(n) virtual void __stdcall s##n() = 0;
	G(03) G(04) G(05) G(06) G(07) G(08) G(09) G(10) G(11) G(12) G(13) G(14)
	G(15) G(16) G(17)
#undef G
	virtual long __stdcall GetSurfaceLevel(unsigned int level, BfmeD3DSurface **surface) = 0;
};

struct IDirect3DDevice8
{
#define G(n) virtual void __stdcall s##n() = 0;
	G(00) G(01) G(02) G(03) G(04) G(05) G(06) G(07) G(08) G(09) G(10) G(11)
	G(12) G(13) G(14) G(15) G(16) G(17) G(18) G(19) G(20) G(21) G(22)
#undef G
	virtual long __stdcall CreateTexture(unsigned int width, unsigned int height,
		unsigned int levels, unsigned long usage, int format, int pool,
		BfmeD3DTexture **texture, void **sharedHandle) = 0;
};

struct IDirect3DSurface8;
class Vector3
{
public:
	float X, Y, Z;
};
class GlobalData;
extern GlobalData *TheWritableGlobalData;
struct BfmeSmokeGlobalDataView
{
	char m_pad[0xD34];
	bool m_glowActive;
};

class DX8Wrapper
{
public:
	static IDirect3DDevice8 *_Get_D3D_Device8() { return D3DDevice; }
	static void Set_Render_Target(IDirect3DSurface8 *, bool);
	static void Clear(bool, bool, bool, const Vector3 &, float, float, unsigned);
protected:
	static IDirect3DDevice8 *D3DDevice;
};

class W3DFilterInterface
{
public:
	virtual int init(void) = 0;
	virtual int shutdown(void) = 0;
};

// Indexed selectors at RVA756BF and shutdown at RVA7684A establish base
// VADE1F2C. The smoke-glow store VADE1F40 is slot5; BW uses slot1.
extern W3DFilterInterface *W3DFilters[10];

class Rva007DCA80 : public W3DFilterInterface
{
public:
	virtual int init(void);
	virtual int shutdown(void);
	virtual bool preRender(bool &skipRender, int &scenePassMode);

private:
	unsigned long m_pixelShader; // +0x04
	unsigned m_vertexShader; // +0x08
	char m_pad0C[0x14 - 0x0C];
	float m_amount; // +0x14
	int m_glowSamples; // +0x18
	bool m_glowActive; // +0x1C
	char m_pad1D[0x2C - 0x1D];
	int m_size; // +0x2C
	bool m_restoreTarget; // +0x30
	char m_pad31[3];
	char m_kernel[0x0C]; // +0x34
	BfmeD3DTexture *m_texture[3]; // +0x40
	BfmeD3DSurface *m_surface[3]; // +0x4C
	RefCountPtr<TextureClass> m_vapor1; // +0x58
	RefCountPtr<TextureClass> m_vapor2; // +0x5C
};

int Rva007DCA80::init(void)
{
	if (!W3DShaderManager::canRenderToTexture())
		return 0;

	m_vapor1 = BFME2LoadParticleTexture("ExVapor01.tga", 0, 0);
	m_vapor2 = BFME2LoadParticleTexture("ExVapor02.tga", 0, 0);
	((ShroudTexture *)&m_vapor1)->getFilter()->m_0C = 0;
	((ShroudTexture *)&m_vapor1)->getFilter()->m_10 = 0;
	((ShroudTexture *)&m_vapor2)->getFilter()->m_0C = 0;
	((ShroudTexture *)&m_vapor2)->getFilter()->m_10 = 0;

	if (Rva00077C19Load("shaders\\hilightfilter.vso", &m_vertexShader) < 0) {
		shutdown();
		return 0;
	}
	if (Rva00077D0FLoad("shaders\\hilightfilter.pso", &m_pixelShader) < 0) {
		shutdown();
		return 0;
	}

	m_size = ((BfmeGaussianSettings *)Rva00309E4BGet())->m_size;
	if (DX8Wrapper::_Get_D3D_Device8()->CreateTexture(m_size, m_size, 1, 1, 0x15, 0, &m_texture[0], 0) < 0) {
		shutdown();
		return 0;
	}
	if (m_texture[0]->GetSurfaceLevel(0, &m_surface[0]) != 0) {
		if (m_texture[0])
			m_texture[0]->Release();
		m_texture[0] = 0;
		m_surface[0] = 0;
	}
	if (DX8Wrapper::_Get_D3D_Device8()->CreateTexture(m_size, m_size, 1, 1, 0x15, 0, &m_texture[1], 0) < 0) {
		shutdown();
		return 0;
	}
	if (m_texture[1]->GetSurfaceLevel(0, &m_surface[1]) != 0) {
		if (m_texture[1])
			m_texture[1]->Release();
		m_texture[1] = 0;
		m_surface[1] = 0;
	}

	BfmeGaussianParams params;
	params.m_mode = 2;
	params.m_taps = ((BfmeGaussianSettings *)Rva00309E4BGet())->m_taps;
	params.m_14 = ((BfmeGaussianSettings *)Rva00309E4BGet())->m_14;
	params.m_1C = ((BfmeGaussianSettings *)Rva00309E4BGet())->m_1C;
	params.m_10 = ((BfmeGaussianSettings *)Rva00309E4BGet())->m_10;
	params.m_18 = ((BfmeGaussianSettings *)Rva00309E4BGet())->m_18;
	W3DShaderManager::createGaussianVector(m_kernel, &params);
	W3DFilters[5] = this;
	return 1;
}

// ?preRender@Rva007DCA80@@UAE_NAA_NAAH@Z @0x000F9C9D
bool Rva007DCA80::preRender(bool &skipRender, int &scenePassMode)
{
	skipRender = false;
	if (scenePassMode != 0)
		return false;
	scenePassMode = 6;
	float scale = 18.0f / m_glowSamples;
	BfmeGaussianParams params;
	params.m_mode = 2;
	params.m_14 = 0.06f * scale;
	params.m_taps = m_glowSamples * 2;
	params.m_1C = 0.11f * scale;
	params.m_10 = 0.18f;
	params.m_18 = 4.5f;
	m_amount = 0.8f;
	W3DShaderManager::createGaussianVector(m_kernel, &params);
	m_glowActive = ((BfmeSmokeGlobalDataView *)TheWritableGlobalData)->m_glowActive;
	((BfmeSmokeGlobalDataView *)TheWritableGlobalData)->m_glowActive = false;
	DX8Wrapper::Set_Render_Target((IDirect3DSurface8 *)m_surface[0], true);
	Vector3 black;
	black.X = 0.0f;
	black.Y = 0.0f;
	black.Z = 0.0f;
	DX8Wrapper::Clear(true, false, false, black, 0.0f, 1.0f, 0);
	m_restoreTarget = true;
	return true;
}
