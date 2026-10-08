// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// ScreenHilightFilter::preRender, slot 2 of its vftable (0x007CF31C, after
// the rowed shutdown 0x000FB8EB). Zero Hour's preRender contract (clear
// skipRender, return true) with BFME 2's gaussian kernel rebuild at +0x18 on
// g_bfmeDirtyCU, as in the sibling filter's preRender 0x000FAFF8. When the
// global data byte at +0xD34 is set the back buffer is stretched into the
// current surface of the pair at +0x30 (a square of side +0x0C); otherwise
// rendering is redirected to the target at +0x2C and cleared.
#include <string.h>

class Vector3
{
public:
	Vector3(float x, float y, float z) : X(x), Y(y), Z(z) {}
	float X;
	float Y;
	float Z;
};

struct IDirect3DSurface8;

class DX8Wrapper
{
public:
	static IDirect3DSurface8 *_Get_D3D_Device8() { return (IDirect3DSurface8 *)D3DDevice; }
	static void Set_Render_Target(IDirect3DSurface8 *render_target, bool use_default_depth_buffer);
	static void Clear(bool clear_color, bool clear_z_stencil, bool clear_stencil, const Vector3 &color, float dest_alpha, float z, unsigned int stencil);
protected:
	static struct IDirect3DDevice8 *D3DDevice;
};

// IDirect3DSurface9::GetDesc is slot 12; IDirect3DDevice9::StretchRect is 34.
struct BfmeD3DSurfaceDesc
{
	unsigned int Format;
	unsigned int Type;
	unsigned int Usage;
	unsigned int Pool;
	unsigned int MultiSampleType;
	unsigned int MultiSampleQuality;
	unsigned int Width;
	unsigned int Height;
};

struct BfmeD3DSurface
{
	virtual long __stdcall QueryInterface(const void *riid, void **ppv) = 0;
	virtual unsigned long __stdcall AddRef() = 0;
	virtual unsigned long __stdcall Release() = 0;
	virtual void __stdcall s3() = 0; virtual void __stdcall s4() = 0; virtual void __stdcall s5() = 0;
	virtual void __stdcall s6() = 0; virtual void __stdcall s7() = 0; virtual void __stdcall s8() = 0;
	virtual void __stdcall s9() = 0; virtual void __stdcall s10() = 0; virtual void __stdcall s11() = 0;
	virtual long __stdcall GetDesc(BfmeD3DSurfaceDesc *desc) = 0;
};

struct BfmeRect
{
	long left;
	long top;
	long right;
	long bottom;
};

struct IDirect3DDevice8
{
#define G(n) virtual void __stdcall s##n() = 0;
	G(00) G(01) G(02) G(03) G(04) G(05) G(06) G(07) G(08) G(09) G(10) G(11) G(12) G(13) G(14) G(15)
	G(16) G(17) G(18) G(19) G(20) G(21) G(22) G(23) G(24) G(25) G(26) G(27) G(28) G(29) G(30) G(31)
	G(32) G(33)
#undef G
	virtual long __stdcall StretchRect(BfmeD3DSurface *src, const BfmeRect *srcRect, BfmeD3DSurface *dst, const BfmeRect *dstRect, int filter) = 0;
};

class W3DRadarResetSurface
{
public:
	~W3DRadarResetSurface();
	BfmeD3DSurface *peek() const { return m_surface; }
private:
	BfmeD3DSurface *m_surface;
};
W3DRadarResetSurface getBackBufferSurface006e(int index);

// The settings block behind Rva00309E4BGet.
struct BfmeGaussianSettings
{
	char m_pad00[4];
	int m_taps; // +0x04
	char m_pad08[0x10 - 0x08];
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

extern bool g_bfmeDirtyCU;

class GlobalData;
extern GlobalData *TheWritableGlobalData;
struct BfmeHilightGlobalDataView
{
	char m_pad[0xD34];
	bool m_D34;
};

enum CustomScenePassModes
{
	SCENE_PASS_DEFAULT
};

class ScreenHilightFilter
{
public:
	virtual bool preRender(bool &skipRender, CustomScenePassModes &scenePassMode);
private:
	char m_pad04[0x0C - 0x04];
	int m_size; // +0x0C
	int m_current; // +0x10
	bool m_14; // +0x14
	int m_kernel[(0x2C - 0x18) / 4]; // +0x18
	IDirect3DSurface8 *m_renderTarget; // +0x2C
	BfmeD3DSurface *m_surfaces[2]; // +0x30
};

// ?preRender@ScreenHilightFilter@@UAE_NAA_NAAW4CustomScenePassModes@@@Z @0x000FAAC5
bool ScreenHilightFilter::preRender(bool &skipRender, CustomScenePassModes &scenePassMode)
{
	skipRender = false;
	if (g_bfmeDirtyCU) {
		BfmeGaussianParams params;
		params.m_mode = 2;
		params.m_taps = ((BfmeGaussianSettings *)Rva00309E4BGet())->m_taps;
		params.m_14 = ((BfmeGaussianSettings *)Rva00309E4BGet())->m_14;
		params.m_1C = ((BfmeGaussianSettings *)Rva00309E4BGet())->m_1C;
		params.m_10 = ((BfmeGaussianSettings *)Rva00309E4BGet())->m_10;
		params.m_18 = ((BfmeGaussianSettings *)Rva00309E4BGet())->m_18;
		W3DShaderManager::createGaussianVector(m_kernel, &params);
		g_bfmeDirtyCU = false;
	}
	if (TheWritableGlobalData && ((BfmeHilightGlobalDataView *)TheWritableGlobalData)->m_D34) {
		BfmeD3DSurface *dest = m_surfaces[m_current];
		BfmeD3DSurface *backBuffer = getBackBufferSurface006e(0).peek();
		IDirect3DDevice8 *device = (IDirect3DDevice8 *)DX8Wrapper::_Get_D3D_Device8();
		BfmeD3DSurfaceDesc desc;
		memset(&desc, 0, sizeof(desc));
		if (backBuffer)
			backBuffer->GetDesc(&desc);
		BfmeRect srcRect;
		srcRect.right = desc.Width;
		srcRect.bottom = desc.Height;
		srcRect.top = 0;
		srcRect.left = 0;
		BfmeRect dstRect;
		dstRect.top = 0;
		dstRect.left = 0;
		dstRect.bottom = m_size;
		dstRect.right = m_size;
		device->StretchRect(backBuffer, &srcRect, dest, &dstRect, 2);
		m_current++;
		if (m_current == 1)
			m_current = 0;
	} else {
		DX8Wrapper::Set_Render_Target(m_renderTarget, true);
		Vector3 color(0.0f, 0.0f, 0.0f);
		DX8Wrapper::Clear(true, false, false, color, 0.0f, 1.0f, 0);
	}
	m_14 = true;
	return true;
}
