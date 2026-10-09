// ?postRender@ScreenMotionBlurFilter@@UAE_NW4FilterModes@@AAVCoord2D@@AA_NPAV3@@Z
// partial score=0.99 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
#include <math.h>
#include "../../Code/Libraries/Include/Lib/Coord2D.h"
struct D3DXVECTOR4
{
    float x, y, z, w;
    D3DXVECTOR4() {}
    D3DXVECTOR4(float a, float b, float c, float d) : x(a), y(b), z(c), w(d) {}
};
struct IDirect3DBaseTexture8
{
	virtual long __stdcall QueryInterface(const void *, void **) = 0;
	virtual unsigned long __stdcall AddRef() = 0;
	virtual unsigned long __stdcall Release() = 0;
};

struct IDirect3DTexture8 : IDirect3DBaseTexture8
{
};

struct IDirect3DDevice8
{
	virtual long __stdcall QueryInterface(const void *, void **) = 0;
	virtual unsigned long __stdcall AddRef() = 0;
	virtual unsigned long __stdcall Release() = 0;
#define RVA000FBA57_D3D_SLOT(n) virtual void slot##n() = 0;
	RVA000FBA57_D3D_SLOT(03) RVA000FBA57_D3D_SLOT(04) RVA000FBA57_D3D_SLOT(05)
	RVA000FBA57_D3D_SLOT(06) RVA000FBA57_D3D_SLOT(07) RVA000FBA57_D3D_SLOT(08)
	RVA000FBA57_D3D_SLOT(09) RVA000FBA57_D3D_SLOT(10) RVA000FBA57_D3D_SLOT(11)
	RVA000FBA57_D3D_SLOT(12) RVA000FBA57_D3D_SLOT(13) RVA000FBA57_D3D_SLOT(14)
	RVA000FBA57_D3D_SLOT(15) RVA000FBA57_D3D_SLOT(16) RVA000FBA57_D3D_SLOT(17)
	RVA000FBA57_D3D_SLOT(18) RVA000FBA57_D3D_SLOT(19) RVA000FBA57_D3D_SLOT(20)
	RVA000FBA57_D3D_SLOT(21) RVA000FBA57_D3D_SLOT(22) RVA000FBA57_D3D_SLOT(23)
	RVA000FBA57_D3D_SLOT(24) RVA000FBA57_D3D_SLOT(25) RVA000FBA57_D3D_SLOT(26)
	RVA000FBA57_D3D_SLOT(27) RVA000FBA57_D3D_SLOT(28) RVA000FBA57_D3D_SLOT(29)
	RVA000FBA57_D3D_SLOT(30) RVA000FBA57_D3D_SLOT(31) RVA000FBA57_D3D_SLOT(32)
	RVA000FBA57_D3D_SLOT(33) RVA000FBA57_D3D_SLOT(34) RVA000FBA57_D3D_SLOT(35)
	RVA000FBA57_D3D_SLOT(36) RVA000FBA57_D3D_SLOT(37) RVA000FBA57_D3D_SLOT(38)
	RVA000FBA57_D3D_SLOT(39) RVA000FBA57_D3D_SLOT(40) RVA000FBA57_D3D_SLOT(41)
	RVA000FBA57_D3D_SLOT(42) RVA000FBA57_D3D_SLOT(43) RVA000FBA57_D3D_SLOT(44)
	RVA000FBA57_D3D_SLOT(45) RVA000FBA57_D3D_SLOT(46) RVA000FBA57_D3D_SLOT(47)
	RVA000FBA57_D3D_SLOT(48) RVA000FBA57_D3D_SLOT(49) RVA000FBA57_D3D_SLOT(50)
	RVA000FBA57_D3D_SLOT(51) RVA000FBA57_D3D_SLOT(52) RVA000FBA57_D3D_SLOT(53)
	RVA000FBA57_D3D_SLOT(54) RVA000FBA57_D3D_SLOT(55) RVA000FBA57_D3D_SLOT(56)
	RVA000FBA57_D3D_SLOT(57) RVA000FBA57_D3D_SLOT(58) RVA000FBA57_D3D_SLOT(59)
	RVA000FBA57_D3D_SLOT(60) RVA000FBA57_D3D_SLOT(61) RVA000FBA57_D3D_SLOT(62)
	RVA000FBA57_D3D_SLOT(63) RVA000FBA57_D3D_SLOT(64)
	virtual long __stdcall SetTexture(unsigned, IDirect3DBaseTexture8 *) = 0;
	RVA000FBA57_D3D_SLOT(66) RVA000FBA57_D3D_SLOT(67) RVA000FBA57_D3D_SLOT(68)
	RVA000FBA57_D3D_SLOT(69) RVA000FBA57_D3D_SLOT(70) RVA000FBA57_D3D_SLOT(71)
	RVA000FBA57_D3D_SLOT(72) RVA000FBA57_D3D_SLOT(73) RVA000FBA57_D3D_SLOT(74)
	RVA000FBA57_D3D_SLOT(75) RVA000FBA57_D3D_SLOT(76) RVA000FBA57_D3D_SLOT(77)
	RVA000FBA57_D3D_SLOT(78) RVA000FBA57_D3D_SLOT(79) RVA000FBA57_D3D_SLOT(80)
	RVA000FBA57_D3D_SLOT(81) RVA000FBA57_D3D_SLOT(82)
	virtual long __stdcall DrawPrimitiveUP(unsigned, unsigned, const void *, unsigned) = 0;
	RVA000FBA57_D3D_SLOT(84) RVA000FBA57_D3D_SLOT(85) RVA000FBA57_D3D_SLOT(86)
	RVA000FBA57_D3D_SLOT(87) RVA000FBA57_D3D_SLOT(88)
	virtual long __stdcall SetVertexShader(unsigned long) = 0;
#undef RVA000FBA57_D3D_SLOT
};

extern unsigned number_of_DX8_calls;

class DX8Wrapper
{
public:
	static IDirect3DDevice8 *_Get_D3D_Device8() { return D3DDevice; }
	static void Invalidate_Cached_Render_States();
	static void Set_DX8_Render_State(unsigned long, unsigned);
	static void Set_DX8_Texture_Stage_State(unsigned, unsigned long, unsigned);
	static void Apply_Render_State_Changes();
	// Retain the native inline state update; omit the competing external copy.
	static __forceinline void Set_DX8_Texture(unsigned stage, IDirect3DBaseTexture8 *texture)
	{
		if (stage >= 16) {
			IDirect3DDevice8 *device = _Get_D3D_Device8();
			device->SetTexture(stage, texture);
			number_of_DX8_calls++;
			return;
		}
		if (Textures[stage] == texture)
			return;
		if (Textures[stage])
			Textures[stage]->Release();
		Textures[stage] = texture;
		if (Textures[stage])
			Textures[stage]->AddRef();
		IDirect3DDevice8 *device = _Get_D3D_Device8();
		device->SetTexture(stage, texture);
		number_of_DX8_calls++;
		texture_changes++;
	}

protected:
	// Existing data-ledger owners: DX8Wrapper::Textures, texture_changes and
	// D3DDevice. number_of_DX8_calls is the existing global owner.
	static IDirect3DBaseTexture8 *Textures[16];
	static unsigned texture_changes;
	static IDirect3DDevice8 *D3DDevice;
};

class W3DShaderManager
{
public:
	static IDirect3DTexture8 *endRenderToTexture();
};

typedef int Int;
typedef float Real;
typedef bool Bool;

struct Coord3D;



enum FilterModes
{
	FM_VIEW_MB_END_PAN_ALPHA = 13,
	FM_VIEW_MB_PAN_ALPHA = 16
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

struct IDirect3DDevice8;


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
	virtual void slot20() = 0;
	virtual void lookAt(void *) = 0;
};

// 012F1600 is EA's tactical view singleton, defined once as
// View *TheTacticalView in game/GameEngine/Source/GameClient/View.cpp.
class View;
extern View *TheTacticalView;
// TU-local view of that singleton; the witnessed slots are the ones read here.
static inline BfmeTacticalView *theTacticalView() { return (BfmeTacticalView *)TheTacticalView; }

#include "../../Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
#define ZoomToValid (ScreenMotionBlurFilter::m_zoomToValid)
#define ZoomToPosition ((void *)&ScreenMotionBlurFilter::m_zoomToPos)



class ScreenMotionBlurFilter
{
public:
	virtual Int init();
	virtual Int shutdown();
	virtual Bool preRender(Bool &, Int &);
	virtual Bool postRender(FilterModes, Coord2D &, Bool &, Coord2D *);
	virtual Bool setup(FilterModes);
	virtual Int set(FilterModes);
	virtual void reset();

	Int m_maxCount;
	Int m_lastFrame;
	Bool m_decrement;
	Bool m_skipRender;
	Bool m_additive;
	Bool m_doZoomTo;
	Coord2D m_priorDelta;
	Int m_panFactor;

protected:
	static Coord3D m_zoomToPos;
	static Bool m_zoomToValid;
};

// ?postRender@ScreenMotionBlurFilter@@UAE_NW4FilterModes@@AAUCoord2D@@AA_NPAU3@@Z
Bool ScreenMotionBlurFilter::postRender(FilterModes mode, Coord2D &scrollDelta,
	Bool &doExtraRender, Coord2D *displaySize)
{
	IDirect3DTexture8 *tex = W3DShaderManager::endRenderToTexture();
	if (!tex)
		return false;
	if (!set(mode))
		return false;

	BfmeDevice *pDev = reinterpret_cast<BfmeDevice *>(DX8Wrapper::_Get_D3D_Device8());
	Bool continueEffect = true;
	struct _TRANS_LIT_TEX_VERTEX
	{
		D3DXVECTOR4 p;
		unsigned int color;
		Real u;
		Real v;
	} v[4];

	Int xpos, ypos, width, height;

	BfmeDevice *textureDevice = reinterpret_cast<BfmeDevice *>(DX8Wrapper::_Get_D3D_Device8());
	DX8Wrapper::Set_DX8_Texture(0, tex);
	BfmeTacticalView *originView = theTacticalView();
	originView->getOrigin(&xpos, &ypos);
	BfmeTacticalView *widthView = theTacticalView();
	width = widthView->getWidth();
	height = theTacticalView()->getHeight();

	// bottom right
	v[0].p = D3DXVECTOR4(xpos + width - 0.5f, ypos + height - 0.5f,
		0.0f, 1.0f);
	v[0].u = (Real)(xpos + width) / displaySize->x;
	v[0].v = (Real)(ypos + height) / displaySize->y;
	// top right
	v[1].p = D3DXVECTOR4(xpos + width - 0.5f, ypos - 0.5f, 0.0f, 1.0f);
	v[1].u = (Real)(xpos + width) / displaySize->x;
	v[1].v = (Real)ypos / displaySize->y;
	// bottom left
	v[2].p = D3DXVECTOR4(xpos - 0.5f, ypos + height - 0.5f,
		0.0f, 1.0f);
	v[2].u = (Real)xpos / displaySize->x;
	v[2].v = (Real)(ypos + height) / displaySize->y;
	// top left
	v[3].p = D3DXVECTOR4(xpos - 0.5f, ypos - 0.5f, 0.0f, 1.0f);
	v[3].u = (Real)xpos / displaySize->x;
	v[3].v = (Real)ypos / displaySize->y;
	v[0].color = 0xffffffff;
	v[1].color = 0xffffffff;
	v[2].color = 0xffffffff;
	v[3].color = 0xffffffff;

	if (m_additive) {
		(*static_cast<void (*)(unsigned long, unsigned)>(&DX8Wrapper::Set_DX8_Render_State))(0x13, 5);
		(*static_cast<void (*)(unsigned long, unsigned)>(&DX8Wrapper::Set_DX8_Render_State))(0x14, 2);
	} else {
		(*static_cast<void (*)(unsigned long, unsigned)>(&DX8Wrapper::Set_DX8_Render_State))(0x13, 5);
		(*static_cast<void (*)(unsigned long, unsigned)>(&DX8Wrapper::Set_DX8_Render_State))(0x14, 6);
	}
	(*static_cast<void (*)(unsigned long, unsigned)>(&DX8Wrapper::Set_DX8_Render_State))(0x1b, false);
	DX8Wrapper::Apply_Render_State_Changes();
	BfmeDevice *fvfDevice = reinterpret_cast<BfmeDevice *>(DX8Wrapper::_Get_D3D_Device8());
	fvfDevice->vt->SetVertexShader(fvfDevice, 0x144);
	++number_of_DX8_calls;

	Coord2D center;
	center.x = 0.5f;
	center.y = 0.5f;
	Bool pan = false;
	if (mode >= FM_VIEW_MB_PAN_ALPHA) {
		Real len = sqrt(scrollDelta.x * scrollDelta.x +
			scrollDelta.y * scrollDelta.y);
		center.y -= 0.5f;
		m_decrement = false;
		m_maxCount = (len * 200 * m_panFactor / (Real)30);
		if (m_maxCount < m_panFactor / 2)
			m_maxCount = m_panFactor / 2;
		if (m_maxCount > m_panFactor)
			m_maxCount = m_panFactor;
		pan = true;
		m_priorDelta = scrollDelta;
	} else if (mode == FM_VIEW_MB_END_PAN_ALPHA) {
		Real len = sqrt(m_priorDelta.x * m_priorDelta.x +
			m_priorDelta.y * m_priorDelta.y);
		center.x += 0.5f * (m_priorDelta.x / len);
		center.y -= 0.5f * (m_priorDelta.y / len);
		m_decrement = false;
		m_maxCount--;
		if (m_maxCount < 2)
			continueEffect = false;
		pan = true;
	}

	m_skipRender = false;
	if (!pan && m_lastFrame != TheGameLogic->getFrame()) {
		if (m_decrement) {
			m_maxCount -= 5;
			if (m_maxCount < 1) {
				m_decrement = false;
				continueEffect = false;
			} else {
				m_skipRender = true;
			}
		} else {
			m_maxCount += 5;
			if (m_maxCount >= 60) {
				m_decrement = true;
				if (m_doZoomTo && ZoomToValid) {
					theTacticalView()->lookAt(ZoomToPosition);
				} else {
					continueEffect = false;
				}
			} else {
				m_skipRender = true;
			}
		}
	}

	Int i;
	Int j;
	if (!pan) {
		for (i = 0; i < 4; i++) {
			Real factor = 1.0f - (m_maxCount / (Real)60) * 0.90f;
			factor = sqrt(factor);
			v[i].u = ((v[i].u - center.x) * factor) + center.x;
			v[i].v = ((v[i].v - center.y) * factor) + center.y;
		}
	}
	DX8Wrapper::Set_DX8_Texture_Stage_State(0, 5, 1);
	DX8Wrapper::Set_DX8_Texture_Stage_State(0, 6, 2);
	DX8Wrapper::Set_DX8_Texture_Stage_State(0, 4, 2);
	pDev->vt->DrawPrimitiveUP(pDev, 5, 2, v, sizeof(_TRANS_LIT_TEX_VERTEX));
	(*static_cast<void (*)(unsigned long, unsigned)>(&DX8Wrapper::Set_DX8_Render_State))(0x1b, true);

	DX8Wrapper::Apply_Render_State_Changes();
	{
		Int limit = m_maxCount;
		if (m_maxCount > 30)
			limit = 30;
		for (j = 0; j < limit; j++) {
			for (i = 0; i < 4; i++) {
				Real factor = 0.99f;
				if (m_additive)
					factor = 0.98f;
				Int alpha = 0x15;
				if (m_additive) {
					alpha = 0x09;
					if (m_maxCount > limit)
						alpha += (m_maxCount - limit) / 5;
					if (m_maxCount == 60)
						alpha += 60;
				}
				v[i].color = (alpha << 24) | 0x00ffffff;
				if (pan) {
					v[i].u = ((v[i].u - center.x) * (factor + .006)) + center.x;
					v[i].v = ((v[i].v - center.y) * factor) + center.y;
				} else {
					v[i].u = ((v[i].u - center.x) * factor) + center.x;
					v[i].v = ((v[i].v - center.y) * factor) + center.y;
				}
			}
			pDev->vt->DrawPrimitiveUP(pDev, 5, 2, v,
				sizeof(_TRANS_LIT_TEX_VERTEX));
		}
	}
	m_lastFrame = TheGameLogic->getFrame();
	if (pan)
		m_skipRender = false;
	reset();
	if (!continueEffect)
		ZoomToValid = false;
	return continueEffect;
}
