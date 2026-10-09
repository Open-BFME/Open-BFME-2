// ?init@ScreenHilightFilter@@UAEHXZ
// partial score=0.9 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// ScreenHilightFilter::init, slot 0 of its vftable (0x007CF314). When the
// hardware check (Rva000F630CGet) passes it loads the filter's vertex and
// pixel shaders, creates the +0x24 result render texture (its top surface at
// +0x2C) and the +0x28 work texture (surface +0x30, cleared to black through
// D3DXLoadSurfaceFromMemory) at the configured size, builds the gaussian
// kernel as the sibling preRender does, and publishes itself. Any failure
// runs slot 1 (shutdown, rowed 0x000FB8EB) and returns 0. Device calls use the
// D3D9 slot numbers (CreateTexture 23; texture GetSurfaceLevel 18).

struct IDirect3DSurface8;
struct IDirect3DTexture8
{
	virtual long __stdcall QueryInterface(const void *, void **) = 0;
	virtual unsigned long __stdcall AddRef() = 0;
	virtual unsigned long __stdcall Release() = 0;
	virtual void __stdcall s3() = 0; virtual void __stdcall s4() = 0; virtual void __stdcall s5() = 0;
	virtual void __stdcall s6() = 0; virtual void __stdcall s7() = 0; virtual void __stdcall s8() = 0;
	virtual void __stdcall s9() = 0; virtual void __stdcall s10() = 0; virtual void __stdcall s11() = 0;
	virtual void __stdcall s12() = 0; virtual void __stdcall s13() = 0; virtual void __stdcall s14() = 0;
	virtual void __stdcall s15() = 0; virtual void __stdcall s16() = 0; virtual void __stdcall s17() = 0;
	virtual long __stdcall GetSurfaceLevel(unsigned level, IDirect3DSurface8 **surface) = 0;	// 18
};
struct IDirect3DDevice8
{
	virtual long __stdcall QueryInterface(const void *, void **) = 0;
	virtual unsigned long __stdcall AddRef() = 0;
	virtual unsigned long __stdcall Release() = 0;
#define S(n) virtual void __stdcall slot##n() = 0;
	S(03) S(04) S(05) S(06) S(07) S(08) S(09) S(10) S(11) S(12) S(13) S(14) S(15) S(16) S(17)
	S(18) S(19) S(20) S(21) S(22)
#undef S
	virtual long __stdcall CreateTexture(unsigned width, unsigned height, unsigned levels, unsigned long usage,
		unsigned format, unsigned pool, IDirect3DTexture8 **texture, void *sharedHandle) = 0;	// 23
};

class DX8Wrapper
{
public:
	static IDirect3DDevice8 *_Get_D3D_Device8() { return D3DDevice; }
protected:
	static IDirect3DDevice8 *D3DDevice;
};

struct BfmeRect
{
	long left;
	long top;
	long right;
	long bottom;
};
extern "C" long __stdcall D3DXLoadSurfaceFromMemory(IDirect3DSurface8 *destSurface, const void *destPalette,
	const BfmeRect *destRect, const void *srcMemory, unsigned srcFormat, unsigned srcPitch,
	const void *srcPalette, const BfmeRect *srcRect, unsigned long filter, unsigned long colorKey);

int Rva000F630CGet();
long Rva00077C19Load(const char *fileName, unsigned int *shader);
long Rva00077D0FLoad(const char *fileName, unsigned long *shader);

// The settings block behind Rva00309E4BGet: +0x04 kernel taps, +0x0C target
// size, +0x10..+0x1C the gaussian parameters (as the sibling preRender).
struct BfmeGaussianSettings
{
	char m_pad00[4];
	int m_taps;	// +0x04
	char m_pad08[0x0C - 0x08];
	int m_size;	// +0x0C
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
class W3DShaderManager
{
public:
	static void createGaussianVector(void *kernel, BfmeGaussianParams *params);
};

class ScreenHilightFilter;
// The active hilight filter, published by init (retail [0x00DE1F3C]).
extern ScreenHilightFilter *TheScreenHilightFilter;

class ScreenHilightFilter
{
public:
	virtual int init();
	virtual int shutdown();
private:
	unsigned long m_pixelShader;	// +0x04
	unsigned int m_vertexShader;	// +0x08
	int m_size;	// +0x0C
	int m_current;	// +0x10
	bool m_14;	// +0x14
	int m_kernel[3];	// +0x18
	IDirect3DTexture8 *m_result;	// +0x24
	IDirect3DTexture8 *m_textures[1];	// +0x28
	IDirect3DSurface8 *m_renderTarget;	// +0x2C
	IDirect3DSurface8 *m_surfaces[1];	// +0x30
};

#define HILIGHT_TEXTURES 1

// ?init@ScreenHilightFilter@@UAEHXZ @0x000FA935
int ScreenHilightFilter::init()
{
	if ((unsigned char)Rva000F630CGet() == 0)
		return 0;
	if (Rva00077C19Load("shaders\\hilightfilter.vso", &m_vertexShader) < 0
		|| Rva00077D0FLoad("shaders\\hilightfilter.pso", &m_pixelShader) < 0) {
		shutdown();
		return 0;
	}
	m_size = ((BfmeGaussianSettings *)Rva00309E4BGet())->m_size;
	if (DX8Wrapper::_Get_D3D_Device8()->CreateTexture(m_size, m_size, 1, 1, 0x15, 0, &m_result, 0) < 0) {
		shutdown();
		return 0;
	}
	if (m_result->GetSurfaceLevel(0, &m_renderTarget)) {
		if (m_result)
			m_result->Release();
		m_result = 0;
		m_renderTarget = 0;
	}
	for (int i = 0; i < HILIGHT_TEXTURES; i++) {
		if (DX8Wrapper::_Get_D3D_Device8()->CreateTexture(m_size, m_size, 1, 1, 0x15, 0, &m_textures[i], 0) < 0) {
			shutdown();
			return 0;
		}
		if (m_textures[i]->GetSurfaceLevel(0, &m_surfaces[i])) {
			m_textures[i]->Release();
			m_textures[i] = 0;
			m_surfaces[i] = 0;
		} else {
			unsigned long black = 0;
			BfmeRect rect;
			rect.left = 0;
			rect.top = 0;
			rect.right = 1;
			rect.bottom = 1;
			D3DXLoadSurfaceFromMemory(m_surfaces[i], 0, 0, &black, 0x15, 4, 0, &rect, 2, 0);
		}
	}
	BfmeGaussianParams params;
	params.m_mode = 2;
	params.m_taps = ((BfmeGaussianSettings *)Rva00309E4BGet())->m_taps;
	params.m_14 = ((BfmeGaussianSettings *)Rva00309E4BGet())->m_14;
	params.m_1C = ((BfmeGaussianSettings *)Rva00309E4BGet())->m_1C;
	params.m_10 = ((BfmeGaussianSettings *)Rva00309E4BGet())->m_10;
	params.m_18 = ((BfmeGaussianSettings *)Rva00309E4BGet())->m_18;
	W3DShaderManager::createGaussianVector(m_kernel, &params);
	TheScreenHilightFilter = this;
	return 1;
}
