// cl: /Ob1
// stlport
//
// Bodies ported from Open-BFME-1's
// GameEngineDevice/Source/W3DDevice/GameClient/ScreenHilightFilterShutdown.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus
// /O1). Compiled that way each body below places uniquely on unclaimed
// game.dat .text by masked whole-.text search, and ./build.sh reproduces it
// byte for byte: ScreenHilightFilter::shutdown 0x000FB8EB (121B). Callee
// addresses are read off retail's call sites (reverse/symbols.csv). Only the
// placed bodies are carried; the donor's other definitions are omitted.

#include <vector>

struct Gen_p12pod { int a[3]; };

class ScreenHilightFilterComRef
{
public:
	virtual long __stdcall QueryInterface() = 0;
	virtual unsigned long __stdcall AddRef() = 0;
	virtual unsigned long __stdcall Release() = 0;
};

struct IDirect3DBaseTexture8;
struct IDirect3DSurface8;
class Coord2D;
enum FilterModes { FM_NULL_MODE = 0 };

// Use the seed's consumed storage offsets; shutdown views the same +0x18
// kernel header and +0x24..+0x30 COM references without adding lifetime providers.
class ScreenHilightFilter
{
public:
	int shutdown();
	virtual int slot00();
	virtual int slot04();
	virtual bool preRender(bool &skipRender, int &scenePassMode);
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

int ScreenHilightFilter::shutdown()
{
	if( m_pixelShader ) ((ScreenHilightFilterComRef *)m_pixelShader)->Release();
	if( m_vertexShader ) ((ScreenHilightFilterComRef *)m_vertexShader)->Release();
	m_pixelShader = 0;
	m_vertexShader = 0;
	((_STL::vector<Gen_p12pod> *)m_kernel)->clear();
	if( m_renderTarget ) ((ScreenHilightFilterComRef *)m_renderTarget)->Release();
	m_renderTarget = 0;
	if( m_result ) ((ScreenHilightFilterComRef *)m_result)->Release();
	ScreenHilightFilterComRef **screenHilightFilterComRef = (ScreenHilightFilterComRef **)&m_result;
	*screenHilightFilterComRef = 0;
	if( m_textures[0] ) ((ScreenHilightFilterComRef *)m_textures[0])->Release();
	m_textures[0] = 0;
	if( m_surfaces[0] ) ((ScreenHilightFilterComRef *)m_surfaces[0])->Release();
	m_surfaces[0] = 0;
	return 1;
}
