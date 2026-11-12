// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// dxsdk
// platformsdk
//
// ScreenHilightFilter::preRender, slot 2 of its vftable (0x007CF31C, after
// the rowed shutdown 0x000FB8EB). Zero Hour's preRender contract (clear
// skipRender, return true) with BFME 2's gaussian kernel rebuild at +0x18 on
// g_bfmeDirtyCU, as in the sibling filter's preRender 0x000FAFF8. When the
// global data byte at +0xD34 is set the back buffer is stretched into the
// current surface of the pair at +0x30 (a square of side +0x0C); otherwise
// rendering is redirected to the target at +0x2C and cleared.
#include <string.h>
// Keep the SDK typedef separate from the two native transform enum tags
// declared by the canonical DX8Wrapper interface. The SDK enum tag is unchanged.
#define D3DTRANSFORMSTATETYPE D3D9TransformStateType
#include <d3dx9tex.h>
#undef D3DTRANSFORMSTATETYPE

#include "../../../../Libraries/Source/WWVegas/WWMath/Vector3Data.h"

struct IDirect3DSurface8;
struct IDirect3DDevice8;

#include "../../../../Libraries/Source/WWVegas/WW3D2/DX8WrapperClass.h"

// The device keeps its D3D8 type name but is a Direct3D 9 device: StretchRect
// is slot 34 and CreateTexture slot 23. The back buffer and render targets are
// IDirect3DSurface9 objects (GetDesc, slot 12) and IDirect3DTexture9 objects
// (GetSurfaceLevel, slot 18; Release, slot 2).

class W3DRadarResetSurface
{
public:
	~W3DRadarResetSurface();
	IDirect3DSurface9 *peek() const { return m_surface; }
private:
	IDirect3DSurface9 *m_surface;
};
W3DRadarResetSurface getBackBufferSurface006e(int index);

long __cdecl Rva00077C19Load(const char *, unsigned *);
long __cdecl Rva00077D0FLoad(const char *, unsigned long *);
class W3DFilterInterface;
extern W3DFilterInterface *W3DFilters[10];

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

#include "../../../Include/W3DDevice/GameClient/BfmeGaussianParams.h"

#include "../../../Include/W3DDevice/GameClient/W3DShaderManagerClass.h"

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

struct IDirect3DBaseTexture8;
class Coord2D;
enum FilterModes { FM_NULL_MODE = 0 };

class ScreenHilightFilter
{
public:
	int shutdown();
	virtual int init();
	virtual int slot04();
	virtual bool preRender(bool &skipRender, CustomScenePassModes &scenePassMode);
	virtual bool postRender(int mode, Coord2D &scrollDelta, bool &doExtraRender, Coord2D *viewportSize);
	virtual void slot10();
protected:
	virtual int set(FilterModes mode);
public:
	virtual void reset();
private:
	unsigned m_pixelShader;	// +0x04
	unsigned m_vertexShader;	// +0x08
	int m_size;	// +0x0C
	int m_current;	// +0x10
	bool m_14;	// +0x14
	int m_kernel[3];	// +0x18
	IDirect3DBaseTexture8 *m_result;	// +0x24
	IDirect3DBaseTexture8 *m_textures[1];	// +0x28, indexed by m_current
	IDirect3DSurface8 *m_renderTarget;	// +0x2C
	void *m_surfaces[2];	// +0x30
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
		IDirect3DSurface9 *dest = reinterpret_cast<IDirect3DSurface9 *>(reinterpret_cast<IDirect3DSurface8 **>(&m_renderTarget)[m_current + 1]);
		IDirect3DSurface9 *backBuffer = getBackBufferSurface006e(0).peek();
		IDirect3DDevice9 *device = reinterpret_cast<IDirect3DDevice9 *>(DX8Wrapper::_Get_D3D_Device8());
		D3DSURFACE_DESC desc;
		memset(&desc, 0, sizeof(desc));
		if (backBuffer)
			backBuffer->GetDesc(&desc);
		RECT srcRect;
		srcRect.right = desc.Width;
		srcRect.bottom = desc.Height;
		srcRect.top = 0;
		srcRect.left = 0;
		RECT dstRect;
		dstRect.top = 0;
		dstRect.left = 0;
		dstRect.bottom = m_size;
		dstRect.right = m_size;
		device->StretchRect(backBuffer, &srcRect, dest, &dstRect, D3DTEXF_LINEAR);
		m_current++;
		if (m_current == 1)
			m_current = 0;
	} else {
		DX8Wrapper::Set_Render_Target(reinterpret_cast<IDirect3DSurface8 **>(&m_renderTarget)[0], true);
		Vector3 color(0.0f, 0.0f, 0.0f);
		DX8Wrapper::Clear(true, false, false, color, 0.0f, 1.0f, 0);
	}
	m_14 = true;
	return true;
}

// ?init@ScreenHilightFilter@@UAEHXZ
// BFME 1 f98983a7 W3DShader/ScreenHilightFilterInit.cpp supplies the shader,
// render-target and surface initialization sequence. Native FA935..FAAC5
// establishes capability replacement, size +0x0C, textures +0x24/+0x28,
// surfaces +0x2C/+0x30, 24-byte Gaussian parameters and registry index 4.
// Existing BFME 2 pre/postRender and shutdown rows establish this receiver;
// ScreenHilightFilter remains the donor's descriptive class spelling.
int ScreenHilightFilter::init()
{
	if (!W3DShaderManager::canRenderToTexture())
		return 0;
	if (Rva00077C19Load("shaders\\hilightfilter.vso", &m_vertexShader) < 0) {
		slot04();
		return 0;
	}
	if (Rva00077D0FLoad("shaders\\hilightfilter.pso", reinterpret_cast<unsigned long *>(&m_pixelShader)) < 0) {
		slot04();
		return 0;
	}
	m_size = ((BfmeGaussianSettings *)Rva00309E4BGet())->m_size;
	if (FAILED(reinterpret_cast<IDirect3DDevice9 *>(DX8Wrapper::_Get_D3D_Device8())->CreateTexture(
		m_size, m_size, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &reinterpret_cast<IDirect3DTexture9 **>(&m_result)[0], 0))) {
		slot04();
		return 0;
	}
	if (reinterpret_cast<IDirect3DTexture9 **>(&m_result)[0]->GetSurfaceLevel(0, reinterpret_cast<IDirect3DSurface9 **>(&reinterpret_cast<IDirect3DSurface8 **>(&m_renderTarget)[0])) != D3D_OK) {
		if (reinterpret_cast<IDirect3DTexture9 **>(&m_result)[0])
			reinterpret_cast<IDirect3DTexture9 **>(&m_result)[0]->Release();
		reinterpret_cast<IDirect3DTexture9 **>(&m_result)[0] = 0;
		reinterpret_cast<IDirect3DSurface8 **>(&m_renderTarget)[0] = 0;
	}
	for (int i = 0; i < 1; ++i) {
		IDirect3DDevice9 *dev = reinterpret_cast<IDirect3DDevice9 *>(DX8Wrapper::_Get_D3D_Device8());
		if (FAILED(dev->CreateTexture(m_size, m_size, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8,
				D3DPOOL_DEFAULT, &reinterpret_cast<IDirect3DTexture9 **>(&m_result)[i + 1], 0))) {
			slot04();
			return 0;
		}
		if (reinterpret_cast<IDirect3DTexture9 **>(&m_result)[i + 1]->GetSurfaceLevel(0, reinterpret_cast<IDirect3DSurface9 **>(&reinterpret_cast<IDirect3DSurface8 **>(&m_renderTarget)[i + 1])) != D3D_OK) {
			reinterpret_cast<IDirect3DTexture9 **>(&m_result)[i + 1]->Release();
			reinterpret_cast<IDirect3DTexture9 **>(&m_result)[i + 1] = 0;
			reinterpret_cast<IDirect3DSurface8 **>(&m_renderTarget)[i + 1] = 0;
		} else {
			unsigned color = 0;
			RECT rect;
			rect.top = 0;
			rect.left = 0;
			rect.bottom = 1;
			rect.right = 1;
			D3DXLoadSurfaceFromMemory(reinterpret_cast<IDirect3DSurface9 *>(reinterpret_cast<IDirect3DSurface8 **>(&m_renderTarget)[i + 1]), 0, 0, &color,
				D3DFMT_A8R8G8B8, 4, 0, &rect, D3DX_FILTER_POINT, 0);
		}
	}
	BfmeGaussianParams params;
	params.m_mode = 2;
	params.m_taps = ((BfmeGaussianSettings *)Rva00309E4BGet())->m_taps;
	params.m_14 = ((BfmeGaussianSettings *)Rva00309E4BGet())->m_14;
	params.m_1C = ((BfmeGaussianSettings *)Rva00309E4BGet())->m_1C;
	params.m_10 = ((BfmeGaussianSettings *)Rva00309E4BGet())->m_10;
	params.m_18 = ((BfmeGaussianSettings *)Rva00309E4BGet())->m_18;
	W3DShaderManager::createGaussianVector((char *)this + 0x18, &params);
	W3DFilters[4] = (W3DFilterInterface *)this;
	return 1;
}
