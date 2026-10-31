// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// dxsdk
// platformsdk
// ScreenMotionBlurFilter::postRender
// ?postRender@ScreenMotionBlurFilter@@UAE_NW4FilterModes@@AAVCoord2D@@AA_NPAV3@@Z
// Retail 0x000FD5B7..0x000FDB21 (1386 bytes) RET16; vftable 0x007CF410 slot 3
// (init/shutdown/preRender/postRender/setup/set/reset as in Zero Hour).
// Ends the render-to-texture pass and draws the captured screen as a
// textured quad: zoom-in/out blur (count stepped by 5 per logic frame and
// optional lookAt of the stored zoom-to position) or pan blur (count from
// the scroll length and pan factor; end-pan aims the blur centre along the
// prior scroll delta), then up to 30 alpha-faded rescaled copies.
// Provenance: Zero Hour W3DShaderManager.cpp ScreenMotionBlurFilter::postRender
// and the BFME1 donor ScreenMotionBlurFilterPostRender.cpp (f98983a7) as
// semantic guides; BFME2 device calls, render-state helpers and the tactical
// view slots read from retail.
// Shape note: the end-pan length reads the prior delta x through a const
// float reference, which is what lets cl keep that value in a register and
// multiply it in place (retail movss xmm2 [ebx+0x10] before the count
// decrement, then mulss xmm2 xmm1); the direct member spelling multiplies a
// copy of the reciprocal by memory instead.
#include <math.h>
#include "../../../../Libraries/Include/Lib/Coord2D.h"
struct D3DXVECTOR4
{
    float x, y, z, w;
    D3DXVECTOR4() {}
    D3DXVECTOR4(float xValue, float yValue, float zValue, float wValue) : x(xValue), y(yValue), z(zValue), w(wValue) {}
};
#include <d3d9.h>

struct IDirect3DBaseTexture8 {};

struct IDirect3DTexture8 : IDirect3DBaseTexture8
{
};

// The device and textures keep their D3D8 type names (DX8Wrapper's static
// decorations) but are Direct3D 9 objects: SetTexture 65, DrawPrimitiveUP 83,
// SetFVF 89; texture AddRef / Release 1 / 2.
struct IDirect3DDevice8;

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
			IDirect3DDevice9 *device = reinterpret_cast<IDirect3DDevice9 *>(_Get_D3D_Device8());
			device->SetTexture(stage, reinterpret_cast<IDirect3DBaseTexture9 *>(texture));
			number_of_DX8_calls++;
			return;
		}
		if (Textures[stage] == texture)
			return;
		if (Textures[stage])
			reinterpret_cast<IDirect3DBaseTexture9 *>(Textures[stage])->Release();
		Textures[stage] = texture;
		if (Textures[stage])
			reinterpret_cast<IDirect3DBaseTexture9 *>(Textures[stage])->AddRef();
		IDirect3DDevice9 *device = reinterpret_cast<IDirect3DDevice9 *>(_Get_D3D_Device8());
		device->SetTexture(stage, reinterpret_cast<IDirect3DBaseTexture9 *>(texture));
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

#include "../../../../Libraries/Include/Lib/Coord3D.h"



enum FilterModes
{
	FM_VIEW_MB_END_PAN_ALPHA = 13,
	FM_VIEW_MB_PAN_ALPHA = 16
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

#include "../../../../GameEngine/Source/Common/GameLogicObjectLookupView.h"
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

Bool ScreenMotionBlurFilter::postRender(FilterModes mode, Coord2D &scrollDelta,
	Bool &doExtraRender, Coord2D *displaySize)
{
	IDirect3DTexture8 *tex = W3DShaderManager::endRenderToTexture();
	if (!tex)
		return false;
	if (!set(mode))
		return false;

	IDirect3DDevice9 *pDev = reinterpret_cast<IDirect3DDevice9 *>(DX8Wrapper::_Get_D3D_Device8());
	Bool continueEffect = true;
	struct _TRANS_LIT_TEX_VERTEX
	{
		D3DXVECTOR4 p;
		unsigned int color;
		Real u;
		Real v;
	} v[4];

	Int xpos, ypos, width, height;

	IDirect3DDevice9 *textureDevice = reinterpret_cast<IDirect3DDevice9 *>(DX8Wrapper::_Get_D3D_Device8());
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
	IDirect3DDevice9 *fvfDevice = reinterpret_cast<IDirect3DDevice9 *>(DX8Wrapper::_Get_D3D_Device8());
	fvfDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);
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
		const Real &px = m_priorDelta.x;
		Real len = sqrt(px * px +
			m_priorDelta.y * m_priorDelta.y);
		center.x += 0.5f * (px / len);
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
	pDev->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(_TRANS_LIT_TEX_VERTEX));
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
			pDev->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v,
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

// Static members (data_ledger RVAs 0x9EC20C/0x9EC1EC, zero .data, unowned);
// defined here, nothing else defines them.
Coord3D ScreenMotionBlurFilter::m_zoomToPos = { 0.0f, 0.0f, 0.0f };
Bool ScreenMotionBlurFilter::m_zoomToValid = false;
