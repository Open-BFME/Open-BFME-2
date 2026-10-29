// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// dxsdk
// platformsdk
//
// reset is slot 6 of this vftable (0x007CF3E0 -> 0x000FC8B4).
// Native 0x000FC8B4..0x000FC903 is the complete 79B no-argument body,
// ending in Invalidate_Cached_Render_States before the next shutdown.
// BFME 1 f98983a7 game/GameEngineDevice/Source/W3DDevice/GameClient/
// ScreenFilterResets.cpp supplies the texture-first reset pattern.
// BFME 2's matched Rva007D85C0 slot-6 and Rva007D6B70 reset units establish
// the cached-texture Release/null update and the D3D9 slots/counters.
// This body clears stage 0 before the pixel shader; all bytes and relocations
// agree. The class remains the existing neutral address-derived owner.
//
// ?set@Rva000FC63DFilter@@MAEHW4FilterModes@@@Z, retail 0x000FC63D..0x000FC8B4
// (631B), thiscall ret 4; slot 5 (set) of the screen filter vtable at
// VA 0x00BCF3C8 (the entry at 0x007CF3DC).
//
// A BFME 2 screen filter's set: clears TheWritableGlobalData +0xD34, notes
// whether the logic frame advanced (file static last frame), and while its
// file-static counter runs steps a time-of-day swap -- on entry (fade
// direction negative, not yet swapped) it restores the remembered time of
// day (+0x0C) through GlobalData::setTimeOfDay 0x002352BC and the game
// client's slot 30, then counts down by three per frame to drop the view
// filter (mode 0 / filter 0), or counts up to 30 to raise view filter mode 15
// / filter 7 and switch to time of day 4 remembering the old one. With a
// filter mode the fade value is stepped as Zero Hour's ScreenBWFilter::set
// does (the frame counter only advances on a new logic frame), then the
// quad state is set: the PRELIT_DIFFUSE preset material (rowed Get_Preset
// 0x0013D230, swapped into ScreenMaterial with the material-changed bit),
// ShaderClass::_PresetOpaqueShader (rowed Set_Shader 0x000662E5), the
// filter's texture (+0x08) on stage 0 (rowed BFME2Set_Texture 0x0011F4B0),
// Apply_Render_State_Changes 0x0011D930, ZFUNC ALWAYS and ZWRITEENABLE off
// (rowed Set_DX8_Render_State 0x0006615F), Apply_Render_State_Changes.
// The normalized fade value has a byte-verified neutral role name below.
// The remaining frame/direction/swap statics retain their ledger names;
// class and method names stay address-derived.

#include <string.h>
#include <d3d9.h>

typedef int Int;
typedef float Real;
typedef bool Bool;
typedef unsigned int UnsignedInt;

enum FilterModes
{
	FM_NULL_MODE = 0
};

class Coord2D;

enum TimeOfDay
{
	TIME_OF_DAY_INVALID = 0
};

enum FilterTypes
{
	FT_NULL_FILTER = 0
};

class GlobalData
{
public:
	Bool setTimeOfDay(TimeOfDay tod);

	unsigned char m_pad000[0x134];
	TimeOfDay m_timeOfDay;			// +0x134
	unsigned char m_pad138[0xD34 - 0x138];
	Bool m_D34;				// +0xD34
};
extern GlobalData *TheWritableGlobalData;

#include "../../../../GameEngine/Source/Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;

#define PAD_VIRTUALS10(p) \
	virtual void p##0(); virtual void p##1(); virtual void p##2(); virtual void p##3(); virtual void p##4(); \
	virtual void p##5(); virtual void p##6(); virtual void p##7(); virtual void p##8(); virtual void p##9();

class GameClient
{
public:
	PAD_VIRTUALS10(s0) PAD_VIRTUALS10(s1) PAD_VIRTUALS10(s2)
	virtual void setTimeOfDay(TimeOfDay tod);	// slot 30
};
extern GameClient *TheGameClient;

class View
{
public:
	PAD_VIRTUALS10(s0) PAD_VIRTUALS10(s1) PAD_VIRTUALS10(s2) PAD_VIRTUALS10(s3)
	virtual void s40(); virtual void s41(); virtual void s42(); virtual void s43(); virtual void s44();
	virtual void setViewFilterMode(FilterModes mode);	// slot 45 (+0xB4)
	virtual void s46();
	virtual void setViewFilter(FilterTypes filter);	// slot 47 (+0xBC)
};
extern View *TheTacticalView;

class VertexMaterialClass
{
public:
	enum PresetType
	{
		PRELIT_DIFFUSE = 0
	};
	virtual void Delete_This();
	static VertexMaterialClass *Get_Preset(PresetType type);
	void Release_Ref()
	{
		NumRefs--;
		if (NumRefs == 0)
			Delete_This();
	}
	Int NumRefs;
};
extern VertexMaterialClass *ScreenMaterial;

class ShaderClass
{
public:
	static ShaderClass _PresetOpaqueShader;
	static ShaderClass _PresetAlphaShader;
	unsigned bits;
	ShaderClass(unsigned value) : bits(value) {}
	static __forceinline void Force_Dirty() { ShaderDirty = true; }
protected:
	friend class DX8Wrapper;
	static bool ShaderDirty;
};

class TextureBaseClass { public: void Release_Ref(); };
class StringClass {
public:
 StringClass(int initial_len = 0, bool hint_temporary = false);
 __forceinline ~StringClass() { Free_String(); }
private:
 void Free_String();
 char *m_Buffer;
};
class WW3D {
public: static bool Is_Snapshot_Activated() { return SnapshotActivated; }
private: static bool SnapshotActivated;
};
struct RenderStateStruct { ShaderClass shader; };
struct BFME2TextureResource;
struct BFME2TextureRef
{
 BFME2TextureRef() : Ptr(0) {}
 ~BFME2TextureRef() { if (Ptr) ((TextureBaseClass *)Ptr)->Release_Ref(); }
	BFME2TextureResource *Ptr;
};
void BFME2Set_Texture(unsigned stage, const BFME2TextureRef &texture);

struct IDirect3DBaseTexture8 {};

// The device and textures keep their D3D8 type names (DX8Wrapper's static
// decorations) but are Direct3D 9 objects: SetRenderState 57, SetTexture 65,
// SetSamplerState 69, DrawPrimitiveUP 83, SetFVF 89, SetPixelShader 107,
// SetPixelShaderConstantF 109; texture AddRef / Release 1 / 2.
struct IDirect3DDevice8;

extern unsigned number_of_DX8_calls;

#include "../../../../Libraries/Source/WWVegas/WWMath/Vector4Data.h"

class DX8Caps;

class DX8Wrapper
{
public:
	static DX8Caps *_Get_DX8_Caps() { return CurrentCaps; }
	static void Set_DX8_Texture_Stage_State(unsigned, unsigned long, unsigned);
	static IDirect3DDevice8 *_Get_D3D_Device8() { return D3DDevice; }
	static void Invalidate_Cached_Render_States();
	static __forceinline void Set_DX8_Texture(unsigned stage, IDirect3DBaseTexture8 *texture)
	{
		if (stage >= 16) {
			reinterpret_cast<IDirect3DDevice9 *>(_Get_D3D_Device8())->SetTexture(stage, reinterpret_cast<IDirect3DBaseTexture9 *>(texture));
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
		reinterpret_cast<IDirect3DDevice9 *>(_Get_D3D_Device8())->SetTexture(stage, reinterpret_cast<IDirect3DBaseTexture9 *>(texture));
		number_of_DX8_calls++;
		texture_changes++;
	}
	static void Set_Shader(const ShaderClass &shader);
	static __forceinline void Set_DX8_Sampler_State(unsigned stage, unsigned type, unsigned value)
	{
		reinterpret_cast<IDirect3DDevice9 *>(_Get_D3D_Device8())->SetSamplerState(stage, (D3DSAMPLERSTATETYPE)type, value);
		number_of_DX8_calls++;
		texture_stage_state_changes++;
	}
	static __forceinline void Set_Pixel_Shader_Constant(int reg, const void *data, int count)
	{
		int memsize = sizeof(Vector4) * count;
		if (memcmp(data, &Pixel_Shader_Constants[reg], memsize) == 0)
			return;
		memcpy(&Pixel_Shader_Constants[reg], data, memsize);
		reinterpret_cast<IDirect3DDevice9 *>(_Get_D3D_Device8())->SetPixelShaderConstantF(reg, (const float *)data, count);
		number_of_DX8_calls++;
	}
 static void Get_DX8_Render_State_Value_Name(StringClass &, unsigned long, unsigned int);
 static __forceinline void Set_Dot3_Shader(const ShaderClass &shader) {
  if (!ShaderClass::ShaderDirty && shader.bits == render_state.shader.bits) return;
  render_state.shader.bits = shader.bits;
  render_state_changed |= 0x8000;
  StringClass str;
 }
 static __forceinline void Set_Dot3_Render_State(unsigned long state, unsigned value) {
  if (RenderStates[state] == value) return;
  if (WW3D::Is_Snapshot_Activated()) {
   StringClass value_name(0, true);
   Get_DX8_Render_State_Value_Name(value_name, state, value);
  }
  RenderStates[state] = value;
  reinterpret_cast<IDirect3DDevice9 *>(_Get_D3D_Device8())->SetRenderState((D3DRENDERSTATETYPE)state, value);
  number_of_DX8_calls++;
  render_state_changes++;
 }

	static void Apply_Render_State_Changes();
	static void Set_DX8_Render_State(unsigned long state, unsigned int value);
	static __forceinline void Mark_Material_Changed() { render_state_changed |= 0x4000; }
protected:
	static unsigned RenderStates[256];
	static unsigned render_state_changes;
	static RenderStateStruct render_state;
	static unsigned int render_state_changed;
	static IDirect3DDevice8 *D3DDevice;
	static IDirect3DBaseTexture8 *Textures[16];
	static unsigned texture_changes;
	static unsigned texture_stage_state_changes;
	static Vector4 Pixel_Shader_Constants[8];
	static DX8Caps *CurrentCaps;
};

#define REF_PTR_RELEASE(x) { if (x) x->Release_Ref(); x = 0; }

// The transition's remaining state shares the fade value's zero-filled group
// (0x00DEC1B4..0x00DEC1C7, retail zeros); the swap counter is initialised
// .data at 0x00DB5B88 holding 1, the value Rva00085553Get re-arms it to.
// Neutral role names, as for the fade value: the original identifiers are
// unknown.
Int BfmeScreenTransitionCurFadeFrame;		// current fade frame
Int BfmeScreenTransitionFadeDirection;		// fade direction
Int BfmeScreenTransitionFadeFrames;		// fade frames
unsigned char BfmeScreenTransitionTimeOfDaySwapped;	// time of day swapped
Int BfmeScreenTransitionSwapCounter = 1;		// swap counter
// Shared transition fade scalar: native setup writes normalized progress and
// DOT3 postRender converts (1 - progress) to alpha. The neutral role name
// preserves uncertainty about the original identifier. Retail stores 0.0f
// initially; data_rows verifies this source's complete four-byte definition.
Real BfmeScreenTransitionFadeValue = 0.0f;
UnsignedInt BfmeScreenTransitionLastLogicFrame;	// last logic frame

class Coord2D;

class Rva000FC63DFilter
{
public:
	Rva000FC63DFilter();
	virtual int init();
	virtual int shutdown();
	virtual bool preRender(bool &, int &);
	virtual bool postRender(FilterModes mode, Coord2D &scrollDelta, Bool &doExtraRender, Coord2D *displaySize);
	virtual bool setup(FilterModes);
protected:
	virtual Int set(FilterModes mode);
	virtual void reset();

private:
	unsigned long m_shader;			// +0x04
	BFME2TextureRef m_texture;		// +0x08
	TimeOfDay m_savedTimeOfDay;		// +0x0C
};

// ??0Rva000FC63DFilter@@QAE@XZ, retail 0x000FC946 (24B): installs the
// vftable at VA 0x00BCF3C8 (slot 5 is set above, slot 6 reset), clears +0x04
// and the texture reference and remembers TIME_OF_DAY_AFTERNOON (2). The
// static initializer at 0x007AC9B0 builds the instance at VA 0x00DEC1CC with
// it, and the derived DOT3 filter's constructor (0x000FD4A5, vftable
// 0x00BCF3F4) calls it first.
Rva000FC63DFilter::Rva000FC63DFilter() :
	m_shader(0),
	m_savedTimeOfDay((TimeOfDay)2)
{
}

Int Rva000FC63DFilter::set(FilterModes mode)
{
	TheWritableGlobalData->m_D34 = false;
	Bool newFrame = false;
	UnsignedInt frame = TheGameLogic->getFrame();
	if (BfmeScreenTransitionLastLogicFrame != frame)
	{
		newFrame = true;
		BfmeScreenTransitionLastLogicFrame = frame;
	}
	if (BfmeScreenTransitionSwapCounter != 0 && newFrame)
	{
		if (BfmeScreenTransitionFadeDirection < 0 && !BfmeScreenTransitionTimeOfDaySwapped)
		{
			BfmeScreenTransitionTimeOfDaySwapped = true;
			BfmeScreenTransitionSwapCounter = 30;
			TheWritableGlobalData->setTimeOfDay(m_savedTimeOfDay);
			TheGameClient->setTimeOfDay(m_savedTimeOfDay);
		}
		if (BfmeScreenTransitionTimeOfDaySwapped)
		{
			BfmeScreenTransitionSwapCounter -= 3;
			if (BfmeScreenTransitionSwapCounter < 1)
			{
				BfmeScreenTransitionTimeOfDaySwapped = false;
				BfmeScreenTransitionSwapCounter = 0;
				TheTacticalView->setViewFilterMode(FM_NULL_MODE);
				TheTacticalView->setViewFilter(FT_NULL_FILTER);
			}
		}
		else
		{
			BfmeScreenTransitionSwapCounter += 3;
			if (BfmeScreenTransitionSwapCounter >= 30)
			{
				BfmeScreenTransitionTimeOfDaySwapped = true;
				TheTacticalView->setViewFilterMode((FilterModes)15);
				TheTacticalView->setViewFilter((FilterTypes)7);
				m_savedTimeOfDay = TheWritableGlobalData->m_timeOfDay;
				TheWritableGlobalData->setTimeOfDay((TimeOfDay)4);
				TheGameClient->setTimeOfDay((TimeOfDay)4);
			}
		}
	}

	if (mode > FM_NULL_MODE)
	{
		if (BfmeScreenTransitionFadeDirection > 0)
		{
			if (newFrame)
				BfmeScreenTransitionCurFadeFrame++;
			Int fade = BfmeScreenTransitionCurFadeFrame;
			if (fade < BfmeScreenTransitionFadeFrames)
			{
				BfmeScreenTransitionFadeValue = (Real)fade / (Real)BfmeScreenTransitionFadeFrames;
			}
			else
			{
				BfmeScreenTransitionCurFadeFrame = 0;
				BfmeScreenTransitionFadeValue = 1.0f;
				BfmeScreenTransitionFadeDirection = 0;
			}
		}
		else if (BfmeScreenTransitionFadeDirection < 0)
		{
			if (newFrame)
				BfmeScreenTransitionCurFadeFrame++;
			Int fade = BfmeScreenTransitionCurFadeFrame;
			if (fade < BfmeScreenTransitionFadeFrames)
			{
				BfmeScreenTransitionFadeValue = 1.0f - (Real)fade / (Real)BfmeScreenTransitionFadeFrames;
			}
			else
			{
				BfmeScreenTransitionFadeValue = 0.0f;
				TheTacticalView->setViewFilterMode(FM_NULL_MODE);
				TheTacticalView->setViewFilter(FT_NULL_FILTER);
				BfmeScreenTransitionCurFadeFrame = 0;
				BfmeScreenTransitionFadeDirection = 0;
			}
		}

		VertexMaterialClass *vmat = VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_DIFFUSE);
		if (vmat) ++vmat->NumRefs;
		if (ScreenMaterial) ScreenMaterial->Release_Ref();
		ScreenMaterial = vmat;
		DX8Wrapper::Mark_Material_Changed();
		REF_PTR_RELEASE(vmat);
		DX8Wrapper::Set_Shader(ShaderClass::_PresetOpaqueShader);
		BFME2Set_Texture(0, m_texture);
		DX8Wrapper::Apply_Render_State_Changes();
		DX8Wrapper::Set_DX8_Render_State(23, 8);	// D3DRS_ZFUNC, D3DCMP_ALWAYS
		DX8Wrapper::Set_DX8_Render_State(14, 0);	// D3DRS_ZWRITEENABLE, FALSE
		DX8Wrapper::Apply_Render_State_Changes();
		return true;
	}
	return false;
}

// ?reset@Rva000FC63DFilter@@MAEXXZ @0x000FC8B4
void Rva000FC63DFilter::reset()
{
	DX8Wrapper::Set_DX8_Texture(0, 0);
	reinterpret_cast<IDirect3DDevice9 *>(DX8Wrapper::_Get_D3D_Device8())->SetPixelShader(0);
	++number_of_DX8_calls;
	DX8Wrapper::Invalidate_Cached_Render_States();
}

#include "../../../../Libraries/Include/Lib/Coord2D.h"
struct D3DXVECTOR4
{
	float x, y, z, w;
	D3DXVECTOR4() {}
	D3DXVECTOR4(float a, float b, float c, float d) : x(a), y(b), z(c), w(d) {}
	operator const float *() const { return &x; }
};
struct IDirect3DTexture8 : IDirect3DBaseTexture8 {};
class W3DShaderManager
{
public:
	static IDirect3DTexture8 *endRenderToTexture();
	static Bool canRenderToTexture(void);
};
// The matched viewport calls use TheTacticalView at VA 0x00DFEA3C.
class View;
extern View *TheTacticalView;
#define BfmeDeviceGlobal (reinterpret_cast<IDirect3DDevice9 *>(DX8Wrapper::_Get_D3D_Device8()))



class BfmeTacticalView
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual Int getWidth();
	virtual void slot16();
	virtual Int getHeight();
	virtual void slot18();
	virtual void getOrigin(Int *, Int *);
};

// TU-local view of the tactical view singleton; the witnessed slots are read here.
static inline BfmeTacticalView *theTacticalView() { return (BfmeTacticalView *)TheTacticalView; }

struct BfmeCaps
{
	char pad[0x2A8];
	Bool dot3;
};

// ?postRender@Rva000FC63DFilter@@UAE_NW4FilterModes@@AAVCoord2D@@AA_NPAV3@@Z @0x000FC95E
// Native 0x000FC95E..0x000FCF54 is the complete 1526B RET16 body: slot 3 of
// vftable 0x007CF3C8 (entry 0x007CF3D4), beside slot 0 init 0x000FC5B7 (which
// loads "shaders\\monochromezoom.nvp" into +0x04), slot 5 set and slot 6 reset.
// Zero Hour W3DShaderManager.cpp ScreenMotionBlurFilter::postRender supplies
// the transformed quad and the 0.99 shrink-and-blend pass loop (here capped
// at 30 passes of 0x15ffffff); target bytes give the second texture stage
// (u2/v2 zoomed by 0.15 / fade, clamped below 0.02, scaled by the view's
// aspect), the four pixel shader constants and the swap-counter stepping.
// The separate aspect local reproduces retail's SSE allocation and frame.
Bool Rva000FC63DFilter::postRender(FilterModes mode, Coord2D &scrollDelta,
	Bool &doExtraRender, Coord2D *displaySize)
{
	IDirect3DTexture8 *tex = W3DShaderManager::endRenderToTexture();
	BFME2Set_Texture(1, m_texture);
	DX8Wrapper::Apply_Render_State_Changes();
	if (!tex)
		return false;
	if (!set(mode))
		return false;

	IDirect3DDevice9 *pDev = reinterpret_cast<IDirect3DDevice9 *>(DX8Wrapper::_Get_D3D_Device8());
	DX8Wrapper::Set_DX8_Texture(0, tex);

	struct _TRANS_LIT_TEX2_VERTEX
	{
		D3DXVECTOR4 p;
		unsigned long color;
		float u;
		float v;
		float u2;
		float v2;
	} v[4];
	Int xpos, ypos, width, height;

	theTacticalView()->getOrigin(&xpos, &ypos);
	width = theTacticalView()->getWidth();
	height = theTacticalView()->getHeight();

	Real zoom;
	if (BfmeScreenTransitionFadeValue < 0.02f)
		zoom = 10.0f;
	else
		zoom = 0.15f / BfmeScreenTransitionFadeValue;
	Real aspect = (Real)width / (Real)height;

	v[0].p = D3DXVECTOR4(xpos + width - 0.5f, ypos + height - 0.5f, 0.0f, 1.0f);
	v[0].u = (Real)(xpos + width) / displaySize->x;
	v[0].v = (Real)(ypos + height) / displaySize->y;
	v[0].u2 = aspect * zoom + 0.5f;
	v[0].v2 = zoom + 0.5f;
	v[1].p = D3DXVECTOR4(xpos + width - 0.5f, ypos - 0.5f, 0.0f, 1.0f);
	v[1].u = (Real)(xpos + width) / displaySize->x;
	v[1].v = (Real)ypos / displaySize->y;
	v[1].u2 = aspect * zoom + 0.5f;
	v[1].v2 = 0.5f - zoom;
	v[2].p = D3DXVECTOR4(xpos - 0.5f, ypos + height - 0.5f, 0.0f, 1.0f);
	v[2].u = (Real)xpos / displaySize->x;
	v[2].v = (Real)(ypos + height) / displaySize->y;
	v[2].u2 = 0.5f - aspect * zoom;
	v[2].v2 = zoom + 0.5f;
	v[3].p = D3DXVECTOR4(xpos - 0.5f, ypos - 0.5f, 0.0f, 1.0f);
	v[3].u = (Real)xpos / displaySize->x;
	v[3].v = (Real)ypos / displaySize->y;
	v[3].u2 = 0.5f - aspect * zoom;
	v[3].v2 = 0.5f - zoom;
	v[0].color = 0xffffffff;
	v[1].color = 0xffffffff;
	v[2].color = 0xffffffff;
	v[3].color = 0xffffffff;

	// Retail's constants are the float products (0x3EF5C290, 0x3F23D70B), not 0.48f / 0.64f.
	D3DXVECTOR4 color(0.6f * 0.8f, 0.6f * 0.8f, 1.0f * 0.8f, 0.8f * 0.8f);
	reinterpret_cast<IDirect3DDevice9 *>(DX8Wrapper::_Get_D3D_Device8())->SetPixelShader(reinterpret_cast<IDirect3DPixelShader9 *>(m_shader));
	++number_of_DX8_calls;
	DX8Wrapper::Set_Pixel_Shader_Constant(0, D3DXVECTOR4(0.3f, 0.59f, 0.11f, 1.0f), 1);
	DX8Wrapper::Set_Pixel_Shader_Constant(1, color, 1);
	DX8Wrapper::Set_Pixel_Shader_Constant(3, D3DXVECTOR4(0.4f, 0.4f, 0.4f, 1.0f), 1);
	Real fade = ((1.0f - BfmeScreenTransitionFadeValue) + 1.0f) * 0.5f;
	DX8Wrapper::Set_Pixel_Shader_Constant(2, D3DXVECTOR4(fade, fade, fade, 1.0f), 1);
	DX8Wrapper::Set_DX8_Sampler_State(1, 1, 3);	// D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP
	DX8Wrapper::Set_DX8_Sampler_State(1, 2, 3);	// D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP
	reinterpret_cast<IDirect3DDevice9 *>(DX8Wrapper::_Get_D3D_Device8())->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX2);
	++number_of_DX8_calls;
	DX8Wrapper::Set_DX8_Render_State(27, 0);	// D3DRS_ALPHABLENDENABLE
	pDev->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(_TRANS_LIT_TEX2_VERTEX));

	if (BfmeScreenTransitionSwapCounter)
	{
		UnsignedInt frame = TheGameLogic->getFrame();
		if (BfmeScreenTransitionLastLogicFrame != frame)
		{
			BfmeScreenTransitionLastLogicFrame = frame;
			if (BfmeScreenTransitionTimeOfDaySwapped)
			{
				BfmeScreenTransitionSwapCounter -= 3;
				if (BfmeScreenTransitionSwapCounter < 1)
				{
					BfmeScreenTransitionSwapCounter = 0;
					BfmeScreenTransitionTimeOfDaySwapped = false;
				}
			}
			else
			{
				BfmeScreenTransitionSwapCounter += 3;
				if (BfmeScreenTransitionSwapCounter >= 30)
					BfmeScreenTransitionTimeOfDaySwapped = true;
			}
		}
		DX8Wrapper::Set_DX8_Render_State(27, 1);
		DX8Wrapper::Apply_Render_State_Changes();
		Int passes = BfmeScreenTransitionSwapCounter;
		if (BfmeScreenTransitionSwapCounter > 30)
			passes = 30;
		for (Int i = 0; i < passes; i++)
		{
			for (Int j = 0; j < 4; j++)
			{
				v[j].u = (v[j].u - 0.5f) * 0.99f + 0.5f;
				v[j].color = 0x15ffffff;
				v[j].v = (v[j].v - 0.5f) * 0.99f + 0.5f;
			}
			DX8Wrapper::Set_DX8_Render_State(19, 5);	// D3DRS_SRCBLEND, D3DBLEND_SRCALPHA
			DX8Wrapper::Set_DX8_Render_State(20, 6);	// D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA
			DX8Wrapper::Set_DX8_Render_State(27, 1);
			pDev->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(_TRANS_LIT_TEX2_VERTEX));
		}
	}
	reset();
	return true;
}

// DOT3 postRender: native 0x000FCF54..0x000FD257 (771B; RET16).
// Slot 3 of vftable 0x007CF3F4, beside the unrowed set at 0x000FD257.
// BFME 1 f98983a7 game/GameEngineDevice/Source/W3DDevice/GameClient/
// ScreenFilterRva007D3580PostRender.cpp supplies the clean two-pass contract.
// Target evidence proves capability byte +0x2A8, D3D9 slots 65/83/89,
// cached texture ownership, shader dirty flag and the same fade value used
// by the setup above. Constant half-pixel and 255 alpha factors are native.
// The owner stays address-derived. Its constructor (0x000FD4A5) calls the
// base filter constructor 0x000FC946 and then installs 0x00BCF3F4, so it
// derives from Rva000FC63DFilter; slot names follow this vftable's.
// Complete body bytes and every relocation match.
class Rva000FCF54Filter : public Rva000FC63DFilter
{
public:
	Rva000FCF54Filter();
	virtual int init();
	virtual int shutdown();
	virtual bool preRender(bool &, int &);
	virtual bool postRender(FilterModes, Coord2D &, bool &, Coord2D *);
	virtual bool setup(FilterModes);
protected:
	virtual int set(FilterModes);
	virtual void reset();
};
// ??0Rva000FCF54Filter@@QAE@XZ, retail 0x000FD4A5 (14B): the base
// constructor (visible in this unit, so ecx is reused after the call), then
// the vftable at VA 0x00BCF3F4.
Rva000FCF54Filter::Rva000FCF54Filter()
{
}

// ?postRender@Rva000FCF54Filter@@UAE_NW4FilterModes@@AAVCoord2D@@AA_NPAV3@@Z @0x000FCF54
Bool Rva000FCF54Filter::postRender(FilterModes mode, Coord2D &scrollDelta,
	Bool &doExtraRender, Coord2D *displaySize)
{
	IDirect3DTexture8 *tex = W3DShaderManager::endRenderToTexture();
	if (!tex)
		return false;
	if (!set(mode))
		return false;

	IDirect3DDevice9 *pDev = BfmeDeviceGlobal;
	Int xpos, ypos, width, height;
	struct Vertex
	{
		D3DXVECTOR4 p;
		unsigned int color;
		Real u;
		Real v;
	} v[4];

	theTacticalView()->getOrigin(&xpos, &ypos);
	width = theTacticalView()->getWidth();
	height = theTacticalView()->getHeight();

	v[0].p = D3DXVECTOR4(xpos + width - 0.5f,
		ypos + height - 0.5f, 0.0f, 1.0f);
	v[0].u = (1.0f / displaySize->x) *
		(Real)(xpos + width);
	v[0].v = (1.0f / displaySize->y) *
		(Real)(ypos + height);
	v[1].p = D3DXVECTOR4(xpos + width - 0.5f,
		ypos - 0.5f, 0.0f, 1.0f);
	v[1].u = (1.0f / displaySize->x) *
		(Real)(xpos + width);
	v[1].v = (1.0f / displaySize->y) * (Real)ypos;
	v[2].p = D3DXVECTOR4(xpos - 0.5f,
		ypos + height - 0.5f, 0.0f, 1.0f);
	v[2].u = (1.0f / displaySize->x) * (Real)xpos;
	v[2].v = (1.0f / displaySize->y) *
		(Real)(ypos + height);
	v[3].p = D3DXVECTOR4(xpos - 0.5f,
		ypos - 0.5f, 0.0f, 1.0f);
	v[3].u = (1.0f / displaySize->x) * (Real)xpos;
	v[3].v = (1.0f / displaySize->y) * (Real)ypos;
	unsigned int currentFade =
		((Int)((1.0f - BfmeScreenTransitionFadeValue) * 255.0f) << 24) |
		0x00ffffff;
	v[0].color = currentFade;
	v[1].color = currentFade;
	v[2].color = currentFade;
	v[3].color = currentFade;

	IDirect3DDevice9 *fvfDevice = BfmeDeviceGlobal;
	fvfDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);
	++number_of_DX8_calls;
	if (((struct BfmeCaps *)DX8Wrapper::_Get_DX8_Caps())->dot3)
	{
		DX8Wrapper::Set_DX8_Render_State(60, 0x80a5ca8e);
		DX8Wrapper::Set_DX8_Texture_Stage_State(0, 26, 35);
		DX8Wrapper::Set_DX8_Texture_Stage_State(0, 2, 2);
		DX8Wrapper::Set_DX8_Texture_Stage_State(0, 3, 35);
		DX8Wrapper::Set_DX8_Texture_Stage_State(0, 1, 25);
		DX8Wrapper::Set_DX8_Texture_Stage_State(1, 2, 1);
		DX8Wrapper::Set_DX8_Texture_Stage_State(1, 3, 3);
		DX8Wrapper::Set_DX8_Texture_Stage_State(1, 1, 24);
	}
	else
	{
		DX8Wrapper::Set_DX8_Render_State(60, 0x60606060);
		DX8Wrapper::Set_DX8_Texture_Stage_State(0, 2, 2);
		DX8Wrapper::Set_DX8_Texture_Stage_State(0, 3, 3);
		DX8Wrapper::Set_DX8_Texture_Stage_State(0, 1, 4);
	}

	DX8Wrapper::Set_DX8_Texture(0, tex);
	pDev->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v,
		sizeof(Vertex));

	ShaderClass::Force_Dirty();
	DX8Wrapper::Set_Shader(
		ShaderClass(ShaderClass::_PresetAlphaShader.bits | 7));
	DX8Wrapper::Apply_Render_State_Changes();
	DX8Wrapper::Set_DX8_Texture_Stage_State(0, 4, 3);
	pDev->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v,
		sizeof(Vertex));
	reset();
	return true;
}

// ?set@Rva000FCF54Filter@@MAEHW4FilterModes@@@Z @0x000FD257
// Native 0x000FD257..0x000FD4A5 is the complete 590B RET4 body.
// It is slot 5 of the same vftable as the verified DOT3 postRender:
// base 0x007CF3F4, entry 0x007CF408. Original owner remains unknown.
// BFME 1 f98983a7 ScreenFilterRva007D31C0Set.cpp supplies the shared
// fade ladder and material/shader/empty-texture/depth-state setup.
Int Rva000FCF54Filter::set(FilterModes mode) {
 if (mode > FM_NULL_MODE) {
  if (BfmeScreenTransitionFadeDirection > 0) {
   Int fade = ++BfmeScreenTransitionCurFadeFrame;
   if (fade < BfmeScreenTransitionFadeFrames)
    BfmeScreenTransitionFadeValue = (Real)fade / (Real)BfmeScreenTransitionFadeFrames;
   else { BfmeScreenTransitionFadeValue = 1; BfmeScreenTransitionCurFadeFrame=0; BfmeScreenTransitionFadeDirection=0; }
  } else if (BfmeScreenTransitionFadeDirection < 0) {
   Int fade = ++BfmeScreenTransitionCurFadeFrame;
   if (fade < BfmeScreenTransitionFadeFrames)
    BfmeScreenTransitionFadeValue = 1 - (Real)fade / (Real)BfmeScreenTransitionFadeFrames;
   else {
    BfmeScreenTransitionFadeValue=0;
    TheTacticalView->setViewFilterMode(FM_NULL_MODE);
    TheTacticalView->setViewFilter(FT_NULL_FILTER);
    BfmeScreenTransitionCurFadeFrame=0; BfmeScreenTransitionFadeDirection=0;
   }
  }
  VertexMaterialClass *vmat = VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_DIFFUSE);
  if (vmat) ++vmat->NumRefs;
  if (ScreenMaterial) ScreenMaterial->Release_Ref();
  ScreenMaterial = vmat;
  DX8Wrapper::Mark_Material_Changed();
  REF_PTR_RELEASE(vmat);
  DX8Wrapper::Set_Dot3_Shader(ShaderClass::_PresetOpaqueShader);
  { BFME2TextureRef texture; BFME2Set_Texture(0, texture); }
  DX8Wrapper::Apply_Render_State_Changes();
  DX8Wrapper::Set_Dot3_Render_State(23,8);
  DX8Wrapper::Set_Dot3_Render_State(14,0);
  DX8Wrapper::Apply_Render_State_Changes();
  return true;
 }
 return false;
}


// ?set@Rva000FC34FFilter@@MAEHW4FilterModes@@@Z @0x000FC34F
// Native 590B RET4 body byte-identical in shape to Rva000FCF54Filter::set above (same fade ladder,
// preset material, opaque shader, empty texture and depth-state setup); another screen filter of the
// same family. Owner remains unknown; the class is a neutral address-derived view.
// Its fade ladder reads the ScreenBWFilter statics at 0x00DEC1A0/A4/A8/AC (the group the matched
// ScreenBWFilter::init 0x000FB9D4 and ::set 0x000FBC67 use), not this unit's 0x00DEC1B0 group: Zero
// Hour's ScreenBWFilterDOT3::set likewise steps ScreenBWFilter's fade statics.
class ScreenBWFilter
{
public:
	static Int m_fadeFrames;
	static Int m_fadeDirection;
	static Int m_curFadeFrame;
	static Real m_curFadeValue;
};
// Zero Hour W3DShaderManager.cpp's ScreenBWFilter fade statics, zero-filled
// at 0x00DEC1A0..0x00DEC1AF just ahead of this unit's transition group.
Int ScreenBWFilter::m_fadeFrames;
Int ScreenBWFilter::m_fadeDirection;
Int ScreenBWFilter::m_curFadeFrame;
Real ScreenBWFilter::m_curFadeValue;
class Rva000FC34FFilter
{
public:
	virtual int init();
	virtual int shutdown();
	virtual bool preRender(bool &, int &);
	virtual bool postRender(FilterModes, Coord2D &, bool &, Coord2D *);
	virtual bool setup(FilterModes);
protected:
	virtual int set(FilterModes);
	virtual void reset();
};
Int Rva000FC34FFilter::set(FilterModes mode) {
 if (mode > FM_NULL_MODE) {
  if (ScreenBWFilter::m_fadeDirection > 0) {
   Int fade = ++ScreenBWFilter::m_curFadeFrame;
   if (fade < ScreenBWFilter::m_fadeFrames)
    ScreenBWFilter::m_curFadeValue = (Real)fade / (Real)ScreenBWFilter::m_fadeFrames;
   else { ScreenBWFilter::m_curFadeValue = 1; ScreenBWFilter::m_curFadeFrame=0; ScreenBWFilter::m_fadeDirection=0; }
  } else if (ScreenBWFilter::m_fadeDirection < 0) {
   Int fade = ++ScreenBWFilter::m_curFadeFrame;
   if (fade < ScreenBWFilter::m_fadeFrames)
    ScreenBWFilter::m_curFadeValue = 1 - (Real)fade / (Real)ScreenBWFilter::m_fadeFrames;
   else {
    ScreenBWFilter::m_curFadeValue=0;
    TheTacticalView->setViewFilterMode(FM_NULL_MODE);
    TheTacticalView->setViewFilter(FT_NULL_FILTER);
    ScreenBWFilter::m_curFadeFrame=0; ScreenBWFilter::m_fadeDirection=0;
   }
  }
  VertexMaterialClass *vmat = VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_DIFFUSE);
  if (vmat) ++vmat->NumRefs;
  if (ScreenMaterial) ScreenMaterial->Release_Ref();
  ScreenMaterial = vmat;
  DX8Wrapper::Mark_Material_Changed();
  REF_PTR_RELEASE(vmat);
  DX8Wrapper::Set_Dot3_Shader(ShaderClass::_PresetOpaqueShader);
  { BFME2TextureRef texture; BFME2Set_Texture(0, texture); }
  DX8Wrapper::Apply_Render_State_Changes();
  DX8Wrapper::Set_Dot3_Render_State(23,8);
  DX8Wrapper::Set_Dot3_Render_State(14,0);
  DX8Wrapper::Apply_Render_State_Changes();
  return true;
 }
 return false;
}

// ?postRender@Rva000FC34FFilter@@UAE_NW4FilterModes@@AAVCoord2D@@AA_NPAV3@@Z @0x000FC04C
// Native 771B RET16 body: instruction-for-instruction the DOT3 postRender
// above (0x000FCF54) except that the two-pass alpha comes from
// ScreenBWFilter::m_curFadeValue (0x00DEC1A0), the fade value this
// filter's own set (0x000FC34F, slot 5 of the same table) steps. Zero
// Hour's ScreenBWFilterDOT3::postRender is the matching two-pass contract.
Bool Rva000FC34FFilter::postRender(FilterModes mode, Coord2D &scrollDelta,
	Bool &doExtraRender, Coord2D *displaySize)
{
	IDirect3DTexture8 *tex = W3DShaderManager::endRenderToTexture();
	if (!tex)
		return false;
	if (!set(mode))
		return false;

	IDirect3DDevice9 *pDev = BfmeDeviceGlobal;
	Int xpos, ypos, width, height;
	struct Vertex
	{
		D3DXVECTOR4 p;
		unsigned int color;
		Real u;
		Real v;
	} v[4];

	theTacticalView()->getOrigin(&xpos, &ypos);
	width = theTacticalView()->getWidth();
	height = theTacticalView()->getHeight();

	v[0].p = D3DXVECTOR4(xpos + width - 0.5f,
		ypos + height - 0.5f, 0.0f, 1.0f);
	v[0].u = (1.0f / displaySize->x) *
		(Real)(xpos + width);
	v[0].v = (1.0f / displaySize->y) *
		(Real)(ypos + height);
	v[1].p = D3DXVECTOR4(xpos + width - 0.5f,
		ypos - 0.5f, 0.0f, 1.0f);
	v[1].u = (1.0f / displaySize->x) *
		(Real)(xpos + width);
	v[1].v = (1.0f / displaySize->y) * (Real)ypos;
	v[2].p = D3DXVECTOR4(xpos - 0.5f,
		ypos + height - 0.5f, 0.0f, 1.0f);
	v[2].u = (1.0f / displaySize->x) * (Real)xpos;
	v[2].v = (1.0f / displaySize->y) *
		(Real)(ypos + height);
	v[3].p = D3DXVECTOR4(xpos - 0.5f,
		ypos - 0.5f, 0.0f, 1.0f);
	v[3].u = (1.0f / displaySize->x) * (Real)xpos;
	v[3].v = (1.0f / displaySize->y) * (Real)ypos;
	unsigned int currentFade =
		((Int)((1.0f - ScreenBWFilter::m_curFadeValue) * 255.0f) << 24) |
		0x00ffffff;
	v[0].color = currentFade;
	v[1].color = currentFade;
	v[2].color = currentFade;
	v[3].color = currentFade;

	IDirect3DDevice9 *fvfDevice = BfmeDeviceGlobal;
	fvfDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);
	++number_of_DX8_calls;
	if (((struct BfmeCaps *)DX8Wrapper::_Get_DX8_Caps())->dot3)
	{
		DX8Wrapper::Set_DX8_Render_State(60, 0x80a5ca8e);
		DX8Wrapper::Set_DX8_Texture_Stage_State(0, 26, 35);
		DX8Wrapper::Set_DX8_Texture_Stage_State(0, 2, 2);
		DX8Wrapper::Set_DX8_Texture_Stage_State(0, 3, 35);
		DX8Wrapper::Set_DX8_Texture_Stage_State(0, 1, 25);
		DX8Wrapper::Set_DX8_Texture_Stage_State(1, 2, 1);
		DX8Wrapper::Set_DX8_Texture_Stage_State(1, 3, 3);
		DX8Wrapper::Set_DX8_Texture_Stage_State(1, 1, 24);
	}
	else
	{
		DX8Wrapper::Set_DX8_Render_State(60, 0x60606060);
		DX8Wrapper::Set_DX8_Texture_Stage_State(0, 2, 2);
		DX8Wrapper::Set_DX8_Texture_Stage_State(0, 3, 3);
		DX8Wrapper::Set_DX8_Texture_Stage_State(0, 1, 4);
	}

	DX8Wrapper::Set_DX8_Texture(0, tex);
	pDev->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v,
		sizeof(Vertex));

	ShaderClass::Force_Dirty();
	DX8Wrapper::Set_Shader(
		ShaderClass(ShaderClass::_PresetAlphaShader.bits | 7));
	DX8Wrapper::Apply_Render_State_Changes();
	DX8Wrapper::Set_DX8_Texture_Stage_State(0, 4, 3);
	pDev->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v,
		sizeof(Vertex));
	reset();
	return true;
}

// ?init@Rva000FCF54Filter@@UAEHXZ @0x000FC91C (42B): slot 0 of the same
// vftable. Zero Hour's filter init shape: the shared fade frame is reset,
// render to texture and the rowed shader-manager setting 0x00075E3C must
// both be available, then the filter instance at 0x00DEC1DC registers itself
// as W3DFilters[6] (0x00DE1F44). Instance and table keep their ledger names.
class W3DFilterInterface;
extern W3DFilterInterface *W3DFilters[];
extern UnsignedInt g_Va00DEC1DC;
Int Rva00075E3CGet();

Int Rva000FCF54Filter::init()
{
	BfmeScreenTransitionCurFadeFrame = 0;
	if (W3DShaderManager::canRenderToTexture() && Rva00075E3CGet())
	{
		W3DFilters[6] = reinterpret_cast<W3DFilterInterface *>(&g_Va00DEC1DC);
		return true;
	}
	return false;
}

// ?init@Rva000FC5B7Filter@@UAEHXZ @0x000FC5B7 (134B, EH): a Ghidra-unlisted
// filter init slot, Zero Hour's cross-fade init shape: the shared fade frame
// and the pixel-shader handle (+0x04) are reset, render to texture must be
// available and the "shaders\monochromezoom.nvp" shader (rowed loader
// 0x00077E05) must load; the instance at 0x00DEC1CC then registers as
// W3DFilters[6] and the "circleFade.tga" mask (rowed TextureAsset::Get)
// is kept at +0x08.
class TextureClass : public TextureBaseClass {};

template <class T>
class RefCountPtr
{
public:
	~RefCountPtr() { if (m_ptr) m_ptr->Release_Ref(); }
	const RefCountPtr &operator=(const RefCountPtr &that);	// 0x000424D0 for TextureClass
	T *m_ptr;
};

class BFME2ParticleTextureHandle : public RefCountPtr<TextureClass>
{
};

class TextureAsset
{
public:
	static BFME2ParticleTextureHandle Get(const char *filename, int a, int b);	// 0x00132D89
};
long Rva00077E05Load(const char *name, unsigned long *handle);	// 0x00077E05
extern UnsignedInt g_Va00DEC1CC;

class Rva000FC5B7Filter
{
public:
	virtual Int init();
private:
	unsigned long m_shader;									// +0x04
	BFME2ParticleTextureHandle m_fadeTexture;				// +0x08
};

Int Rva000FC5B7Filter::init()
{
	long hr;
	m_shader = 0;
	BfmeScreenTransitionCurFadeFrame = 0;
	if (!W3DShaderManager::canRenderToTexture())
		return false;
	hr = Rva00077E05Load("shaders\\monochromezoom.nvp", &m_shader);
	if (hr < 0)
		return false;
	W3DFilters[6] = reinterpret_cast<W3DFilterInterface *>(&g_Va00DEC1CC);
	m_fadeTexture = TextureAsset::Get("circleFade.tga", 0, 0);
	return true;
}

// Placeholder virtuals this unit's vftables hold.  In retail each such slot
// holds a rowed function; the vftable's address is proven by the vptr stores in
// the matched destructors, so bind the placeholder to that row's name.
#pragma comment(linker, "/alternatename:?init@Rva000FC63DFilter@@UAEHXZ=?init@Rva000FC5B7Filter@@UAEHXZ")
#pragma comment(linker, "/alternatename:?preRender@Rva000FC63DFilter@@UAE_NAA_NAAH@Z=?rva000FBA0F@Rva000FBA0F@@QAE_NPA_NH@Z")
#pragma comment(linker, "/alternatename:?preRender@Rva000FCF54Filter@@UAE_NAA_NAAH@Z=?rva000FBA0F@Rva000FBA0F@@QAE_NPA_NH@Z")
#pragma comment(linker, "/alternatename:?reset@Rva000FCF54Filter@@MAEXXZ=?reset@Rva000FBA4ASecondary@@UAEXXZ")
#pragma comment(linker, "/alternatename:?setup@Rva000FC63DFilter@@UAE_NW4FilterModes@@@Z=?_bfme_ro_v50@RenderObjClass@@UAE_NH@Z")
#pragma comment(linker, "/alternatename:?setup@Rva000FCF54Filter@@UAE_NW4FilterModes@@@Z=?_bfme_ro_v50@RenderObjClass@@UAE_NH@Z")
#pragma comment(linker, "/alternatename:?shutdown@Rva000FC63DFilter@@UAEHXZ=?bfmeDropDF@BfmeThingDF@@QAEHXZ")
#pragma comment(linker, "/alternatename:?shutdown@Rva000FCF54Filter@@UAEHXZ=?Create@GameFileClass@@UAEHXZ")
