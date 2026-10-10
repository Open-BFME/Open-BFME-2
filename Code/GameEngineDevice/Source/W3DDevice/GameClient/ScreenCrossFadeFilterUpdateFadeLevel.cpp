// cl: /MD /G7 /arch:SSE
// ?updateFadeLevel@ScreenCrossFadeFilter@@IAE_NXZ @0x000F633A 193B
// Evidence: named lane pin, BFME1 donor W3DShaderManager.cpp ScreenCrossFadeFilter::updateFadeLevel, caller preRender 0x000F63FB, globals g_00DEBFF8 g_00DEBFFC g_00DEC000 g_00DEBFF4.
extern int g_00DEBFF8;
extern int g_00DEBFFC;
extern int g_00DEC000;
extern float g_00DEBFF4;
extern float g_Va00BBB8D8;

class TacticalView
{
public:
	virtual void unused0();
	virtual void unused1();
	virtual void unused2();
	virtual void unused3();
	virtual void unused4();
	virtual void unused5();
	virtual void unused6();
	virtual void unused7();
	virtual void unused8();
	virtual void unused9();
	virtual void unused10();
	virtual void unused11();
	virtual void unused12();
	virtual void unused13();
	virtual void unused14();
	virtual void unused15();
	virtual void unused16();
	virtual void unused17();
	virtual void unused18();
	virtual void unused19();
	virtual void unused20();
	virtual void unused21();
	virtual void unused22();
	virtual void unused23();
	virtual void unused24();
	virtual void unused25();
	virtual void unused26();
	virtual void unused27();
	virtual void unused28();
	virtual void unused29();
	virtual void unused30();
	virtual void unused31();
	virtual void unused32();
	virtual void unused33();
	virtual void unused34();
	virtual void unused35();
	virtual void unused36();
	virtual void unused37();
	virtual void unused38();
	virtual void unused39();
	virtual void unused40();
	virtual void unused41();
	virtual void unused42();
	virtual void unused43();
	virtual void unused44();
	virtual bool setViewFilterMode(int mode);
	virtual void unused46();
	virtual bool setViewFilter(int filter);
};

extern TacticalView *TheTacticalView;

typedef int Int;typedef float Real;typedef bool Bool;
#include "../../../../Libraries/Include/Lib/Coord2D.h"
struct IDirect3DDevice8;
extern unsigned number_of_DX8_calls;
struct D3DXVECTOR4 {float x,y,z,w;D3DXVECTOR4(){} D3DXVECTOR4(float a,float b,float c,float d):x(a),y(b),z(c),w(d){} };
struct BfmeTextureRef;
struct BfmeTextureRefVt {void *query;unsigned (__stdcall *addRef)(BfmeTextureRef *);unsigned (__stdcall *release)(BfmeTextureRef *);};
struct BfmeTextureRef {BfmeTextureRefVt *vt;};
struct IDirect3DBaseTexture8;
struct IDirect3DTexture8;

enum FilterModes
{
	FM_NULL_MODE = 0,
	FM_VIEW_CROSSFADE_CIRCLE = 4
};

struct BfmeDevice;

struct BfmeDeviceVt
{
	char pad000[0x104];
	int (__stdcall *SetTexture)(BfmeDevice *, unsigned int, void *);
	char pad108[4];
	int (__stdcall *SetTextureStageState)(BfmeDevice *, unsigned int,
		unsigned int, unsigned int);
	char pad110[0x3c];
	int (__stdcall *DrawPrimitiveUP)(BfmeDevice *, unsigned int,
		unsigned int, const void *, unsigned int);
	char pad150[0x14];
	int (__stdcall *SetVertexShader)(BfmeDevice *, unsigned int);
};

struct BfmeDevice
{
	BfmeDeviceVt *vt;
};



class DX8Wrapper
{
public:
	static BfmeDevice *_Get_D3D_Device8(void)
	{
		return (BfmeDevice *)D3DDevice;
	}


 static __forceinline void Set_Texture(unsigned stage,IDirect3DBaseTexture8 *texture) {
  if(Textures[stage]!=texture) {
   if(Textures[stage])reinterpret_cast<BfmeTextureRef *>(Textures[stage])->vt->release(reinterpret_cast<BfmeTextureRef *>(Textures[stage]));
   Textures[stage]=texture;
   if(texture)reinterpret_cast<BfmeTextureRef *>(texture)->vt->addRef(reinterpret_cast<BfmeTextureRef *>(texture));
   _Get_D3D_Device8()->vt->SetTexture(_Get_D3D_Device8(),stage,texture);
   ++number_of_DX8_calls;
   ++texture_changes;
  }
 }
protected:
 static IDirect3DDevice8 *D3DDevice;
 static IDirect3DBaseTexture8 *Textures[16];
 static unsigned texture_changes;
};

class BfmeTacticalView
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual Int getWidth() = 0;
	virtual void slot16() = 0;
	virtual Int getHeight() = 0;
	virtual void slot18() = 0;
	virtual void getOrigin(Int *, Int *) = 0;
};

// Preserve the existing TheTacticalView binding at native DFEA3C; this
// accessed-slot view is used only for origin and dimensions.
static inline BfmeTacticalView *tacticalView() { return (BfmeTacticalView *)TheTacticalView; }

class TextureBaseClass
{
public:
	IDirect3DBaseTexture8 *Peek_D3D_Base_Texture(void) const;
};

// Existing opaque global spelling; its first four-byte texture handle is
// independently consumed by Peek_D3D_Base_Texture at native F65ED.
class BfmeSrcUDC;
extern BfmeSrcUDC *g_bfmeObjUDC;



class W3DShaderManager
{
public:
	static IDirect3DTexture8 *endRenderToTexture();
};


int __cdecl Rva00075E36Get();
extern unsigned number_of_DX8_calls;
class ScreenCrossFadeFilter
{
public:
	virtual Int init();
	virtual Int shutdown();
	virtual void unusedPreRenderSlot();
	virtual Bool postRender(FilterModes, Coord2D &, Bool &, Coord2D *);
	virtual Bool setup(FilterModes);
	virtual Int set(FilterModes);
	virtual void reset();

protected:
	static Bool m_skipRender;
 bool updateFadeLevel();
};



bool ScreenCrossFadeFilter::updateFadeLevel()
{
	if (g_00DEBFF8 > 0)
	{
		g_00DEC000++;
		int fade = g_00DEC000;
		if (fade < g_00DEBFFC)
		{
			g_00DEBFF4 = (float)fade / (float)g_00DEBFFC;
		}
		else
		{
			g_00DEC000 = 0;
			g_00DEBFF4 = g_Va00BBB8D8;
			g_00DEBFF8 = 0;
			return false;
		}
	}
	else if (g_00DEBFF8 < 0)
	{
		int fade = g_00DEC000;
		if (fade < g_00DEBFFC)
		{
			g_00DEBFF4 = g_Va00BBB8D8 - (float)fade / (float)g_00DEBFFC;
			g_00DEC000++;
		}
		else
		{
			g_00DEBFF4 = 0.0f;
			TheTacticalView->setViewFilterMode(0);
			TheTacticalView->setViewFilter(0);
			g_00DEC000 = 0;
			g_00DEBFF8 = 0;
			return false;
		}
	}
	return true;
}

// Clean donor575ba2b0 ScreenCrossFadeFilterPostRender.cpp plus target cached
// texture reference ABI and counters. BFME2 F6544..F685E RET16 full794B.
Bool ScreenCrossFadeFilter::postRender(FilterModes mode, Coord2D &scrollDelta,
	Bool &doExtraRender, Coord2D *displaySize)
{
	IDirect3DTexture8 *tex;

	if (m_skipRender)
	{
		m_skipRender = false;
		doExtraRender = true;
		tex = W3DShaderManager::endRenderToTexture();
		return true;
	}

	tex = reinterpret_cast<IDirect3DTexture8 *>(Rva00075E36Get());
	if (!tex)
		return false;
	if (!set(mode))
		return false;

	BfmeDevice *pDev = DX8Wrapper::_Get_D3D_Device8();
	struct _TRANS_LIT_TEX_VERTEX
	{
		D3DXVECTOR4 p;
		unsigned int color;
		Real u;
		Real v;
		Real u1;
		Real v1;
	} v[4];

	Int xpos, ypos, width, height;
	Real radius = 0.0f;

	DX8Wrapper::Set_Texture(0,reinterpret_cast<IDirect3DBaseTexture8 *>(tex));
	if (mode == FM_VIEW_CROSSFADE_CIRCLE)
	{
		DX8Wrapper::Set_Texture(1,reinterpret_cast<TextureBaseClass &>(g_bfmeObjUDC).Peek_D3D_Base_Texture());

		radius = (1.0f - g_00DEBFF4) * 2.0f;
		if (radius <= 0)
			radius = 0.01f;
		radius = 0.5f / radius;
	}

	tacticalView()->getOrigin(&xpos, &ypos);
	width = tacticalView()->getWidth();
	height = tacticalView()->getHeight();

	// bottom right
	v[0].p = D3DXVECTOR4(xpos + width - 0.5f,
		ypos + height - 0.5f, 0.0f, 1.0f);
	v[0].u = (Real)(xpos + width) / displaySize->x;
	v[0].v = (Real)(ypos + height) / displaySize->y;
	v[0].u1 = 0.5f + radius;
	v[0].v1 = 0.5f + radius;
	// top right
	v[1].p = D3DXVECTOR4(xpos + width - 0.5f,
		ypos - 0.5f, 0.0f, 1.0f);
	v[1].u = (Real)(xpos + width) / displaySize->x;
	v[1].v = (Real)ypos / displaySize->y;
	v[1].u1 = 0.5f + radius;
	v[1].v1 = 0.5f - radius;
	// bottom left
	v[2].p = D3DXVECTOR4(xpos - 0.5f,
		ypos + height - 0.5f, 0.0f, 1.0f);
	v[2].u = (Real)xpos / displaySize->x;
	v[2].v = (Real)(ypos + height) / displaySize->y;
	v[2].u1 = 0.5f - radius;
	v[2].v1 = 0.5f + radius;
	// top left
	v[3].p = D3DXVECTOR4(xpos - 0.5f,
		ypos - 0.5f, 0.0f, 1.0f);
	v[3].u = (Real)xpos / displaySize->x;
	v[3].v = (Real)ypos / displaySize->y;
	v[3].u1 = 0.5f - radius;
	v[3].v1 = 0.5f - radius;

	unsigned int diffuse = 0xffffffff;
	v[0].color = diffuse;
	v[1].color = diffuse;
	v[2].color = diffuse;
	v[3].color = diffuse;

	DX8Wrapper::_Get_D3D_Device8()->vt->SetVertexShader(DX8Wrapper::_Get_D3D_Device8(),
		0x244);
	++number_of_DX8_calls;
	pDev->vt->DrawPrimitiveUP(pDev, 5, 2, v,
		sizeof(_TRANS_LIT_TEX_VERTEX));

	reset();
	return true;
}
