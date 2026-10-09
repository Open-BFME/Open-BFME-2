// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
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

typedef int Int;
typedef float Real;
typedef bool Bool;
typedef unsigned int UnsignedInt;

enum FilterModes
{
	FM_NULL_MODE = 0
};

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

struct IDirect3DBaseTexture8
{
	virtual long __stdcall QueryInterface(const void *, void **) = 0;
	virtual unsigned long __stdcall AddRef() = 0;
	virtual unsigned long __stdcall Release() = 0;
};

struct IDirect3DDevice8
{
	virtual long __stdcall QueryInterface(const void *, void **) = 0;
	virtual unsigned long __stdcall AddRef() = 0;
	virtual unsigned long __stdcall Release() = 0;
#define S(n) virtual void __stdcall slot##n() = 0;
	S(03) S(04) S(05) S(06) S(07) S(08) S(09) S(10) S(11) S(12) S(13) S(14) S(15) S(16) S(17)
	S(18) S(19) S(20) S(21) S(22) S(23) S(24) S(25) S(26) S(27) S(28) S(29) S(30) S(31) S(32)
	S(33) S(34) S(35) S(36) S(37) S(38) S(39) S(40) S(41) S(42) S(43) S(44) S(45) S(46) S(47)
	S(48) S(49) S(50) S(51) S(52) S(53) S(54) S(55) S(56)
	virtual long __stdcall SetRenderState(unsigned long state, unsigned long value) = 0; // 57
	S(58) S(59) S(60) S(61) S(62)
	S(63) S(64)
	virtual long __stdcall SetTexture(unsigned stage, IDirect3DBaseTexture8 *texture) = 0;	// 65
	S(66) S(67) S(68)
	virtual long __stdcall SetSamplerState(unsigned sampler, unsigned type, unsigned value) = 0;	// 69
	S(70) S(71) S(72) S(73) S(74) S(75) S(76) S(77) S(78) S(79) S(80) S(81) S(82) S(83) S(84)
	S(85) S(86)
	virtual long __stdcall SetVertexDeclaration(unsigned decl) = 0;	// 87
	S(88) S(89) S(90) S(91)
	virtual long __stdcall SetVertexShader(unsigned shader) = 0;	// 92
	S(93) S(94) S(95) S(96) S(97) S(98) S(99) S(100) S(101) S(102) S(103) S(104) S(105) S(106)
	virtual long __stdcall SetPixelShader(unsigned shader) = 0;	// 107
	S(108)
	virtual long __stdcall SetPixelShaderConstantF(unsigned reg, const void *data, unsigned count) = 0;	// 109
#undef S
};

extern unsigned number_of_DX8_calls;

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
			_Get_D3D_Device8()->SetTexture(stage, texture);
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
		_Get_D3D_Device8()->SetTexture(stage, texture);
		number_of_DX8_calls++;
		texture_changes++;
	}
	static void Set_Shader(const ShaderClass &shader);
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
  _Get_D3D_Device8()->SetRenderState(state, value);
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
	static DX8Caps *CurrentCaps;
};

#define REF_PTR_RELEASE(x) { if (x) x->Release_Ref(); x = 0; }

extern Int g_00DEC1BC;		// current fade frame
extern Int g_00DEC1B4;		// fade direction
extern Int g_00DEC1B8;		// fade frames
extern unsigned char g_00DEC1C4;	// time of day swapped
extern Int g_00DB5B88;		// swap counter
// Shared transition fade scalar: native setup writes normalized progress and
// DOT3 postRender converts (1 - progress) to alpha. The neutral role name
// preserves uncertainty about the original identifier. Retail stores 0.0f
// initially; data_rows verifies this source's complete four-byte definition.
Real BfmeScreenTransitionFadeValue = 0.0f;
extern UnsignedInt g_Va00DEC1C0;	// last logic frame

class Rva000FC63DFilter
{
public:
	virtual int slot00();
	virtual int slot01();
	virtual bool slot02();
	virtual bool slot03();
	virtual bool slot04(int);
protected:
	virtual Int set(FilterModes mode);
	virtual void reset();

private:
	unsigned char m_pad04[0x08 - 0x04];
	BFME2TextureRef m_texture;		// +0x08
	TimeOfDay m_savedTimeOfDay;		// +0x0C
};

Int Rva000FC63DFilter::set(FilterModes mode)
{
	TheWritableGlobalData->m_D34 = false;
	Bool newFrame = false;
	UnsignedInt frame = TheGameLogic->getFrame();
	if (g_Va00DEC1C0 != frame)
	{
		newFrame = true;
		g_Va00DEC1C0 = frame;
	}
	if (g_00DB5B88 != 0 && newFrame)
	{
		if (g_00DEC1B4 < 0 && !g_00DEC1C4)
		{
			g_00DEC1C4 = true;
			g_00DB5B88 = 30;
			TheWritableGlobalData->setTimeOfDay(m_savedTimeOfDay);
			TheGameClient->setTimeOfDay(m_savedTimeOfDay);
		}
		if (g_00DEC1C4)
		{
			g_00DB5B88 -= 3;
			if (g_00DB5B88 < 1)
			{
				g_00DEC1C4 = false;
				g_00DB5B88 = 0;
				TheTacticalView->setViewFilterMode(FM_NULL_MODE);
				TheTacticalView->setViewFilter(FT_NULL_FILTER);
			}
		}
		else
		{
			g_00DB5B88 += 3;
			if (g_00DB5B88 >= 30)
			{
				g_00DEC1C4 = true;
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
		if (g_00DEC1B4 > 0)
		{
			if (newFrame)
				g_00DEC1BC++;
			Int fade = g_00DEC1BC;
			if (fade < g_00DEC1B8)
			{
				BfmeScreenTransitionFadeValue = (Real)fade / (Real)g_00DEC1B8;
			}
			else
			{
				g_00DEC1BC = 0;
				BfmeScreenTransitionFadeValue = 1.0f;
				g_00DEC1B4 = 0;
			}
		}
		else if (g_00DEC1B4 < 0)
		{
			if (newFrame)
				g_00DEC1BC++;
			Int fade = g_00DEC1BC;
			if (fade < g_00DEC1B8)
			{
				BfmeScreenTransitionFadeValue = 1.0f - (Real)fade / (Real)g_00DEC1B8;
			}
			else
			{
				BfmeScreenTransitionFadeValue = 0.0f;
				TheTacticalView->setViewFilterMode(FM_NULL_MODE);
				TheTacticalView->setViewFilter(FT_NULL_FILTER);
				g_00DEC1BC = 0;
				g_00DEC1B4 = 0;
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
	DX8Wrapper::_Get_D3D_Device8()->SetPixelShader(0);
	++number_of_DX8_calls;
	DX8Wrapper::Invalidate_Cached_Render_States();
}

#include "../../../../Libraries/Include/Lib/Coord2D.h"
struct D3DXVECTOR4
{
	float x, y, z, w;
	D3DXVECTOR4() {}
	D3DXVECTOR4(float a, float b, float c, float d) : x(a), y(b), z(c), w(d) {}
};
struct IDirect3DTexture8 : IDirect3DBaseTexture8 {};
class W3DShaderManager
{
public:
	static IDirect3DTexture8 *endRenderToTexture();
};
struct BfmeDevice;

struct BfmeDeviceVtable
{
	char pad000[0x104];
	long (__stdcall *SetTexture)(BfmeDevice *, unsigned int, void *);
	char pad108[0x44];
	long (__stdcall *DrawPrimitiveUP)(BfmeDevice *, unsigned int,
		unsigned int, const void *, unsigned int);
	char pad150[0x14];
	long (__stdcall *SetVertexShader)(BfmeDevice *, unsigned int);
};

struct BfmeDevice
{
	BfmeDeviceVtable *v;
};

// The matched viewport calls use TheTacticalView at VA 0x00DFEA3C.
class View;
extern View *TheTacticalView;
#define BfmeDeviceGlobal ((BfmeDevice *)DX8Wrapper::_Get_D3D_Device8())



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

// DOT3 postRender: native 0x000FCF54..0x000FD257 (771B; RET16).
// Slot 3 of vftable 0x007CF3F4, beside the unrowed set at 0x000FD257.
// BFME 1 f98983a7 game/GameEngineDevice/Source/W3DDevice/GameClient/
// ScreenFilterRva007D3580PostRender.cpp supplies the clean two-pass contract.
// Target evidence proves capability byte +0x2A8, D3D9 slots 65/83/89,
// cached texture ownership, shader dirty flag and the same fade value used
// by the setup above. Constant half-pixel and 255 alpha factors are native.
// The owner stays address-derived; no original class name or inheritance
// is asserted. Complete body bytes and every relocation match.
class Rva000FCF54Filter
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
// ?postRender@Rva000FCF54Filter@@UAE_NW4FilterModes@@AAVCoord2D@@AA_NPAV3@@Z @0x000FCF54
Bool Rva000FCF54Filter::postRender(FilterModes mode, Coord2D &scrollDelta,
	Bool &doExtraRender, Coord2D *displaySize)
{
	IDirect3DTexture8 *tex = W3DShaderManager::endRenderToTexture();
	if (!tex)
		return false;
	if (!set(mode))
		return false;

	BfmeDevice *pDev = BfmeDeviceGlobal;
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

	BfmeDevice *fvfDevice = BfmeDeviceGlobal;
	fvfDevice->v->SetVertexShader(fvfDevice, 0x144);
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
	pDev->v->DrawPrimitiveUP(pDev, 5, 2, v,
		sizeof(Vertex));

	ShaderClass::Force_Dirty();
	DX8Wrapper::Set_Shader(
		ShaderClass(ShaderClass::_PresetAlphaShader.bits | 7));
	DX8Wrapper::Apply_Render_State_Changes();
	DX8Wrapper::Set_DX8_Texture_Stage_State(0, 4, 3);
	pDev->v->DrawPrimitiveUP(pDev, 5, 2, v,
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
  if (g_00DEC1B4 > 0) {
   Int fade = ++g_00DEC1BC;
   if (fade < g_00DEC1B8)
    BfmeScreenTransitionFadeValue = (Real)fade / (Real)g_00DEC1B8;
   else { BfmeScreenTransitionFadeValue = 1; g_00DEC1BC=0; g_00DEC1B4=0; }
  } else if (g_00DEC1B4 < 0) {
   Int fade = ++g_00DEC1BC;
   if (fade < g_00DEC1B8)
    BfmeScreenTransitionFadeValue = 1 - (Real)fade / (Real)g_00DEC1B8;
   else {
    BfmeScreenTransitionFadeValue=0;
    TheTacticalView->setViewFilterMode(FM_NULL_MODE);
    TheTacticalView->setViewFilter(FT_NULL_FILTER);
    g_00DEC1BC=0; g_00DEC1B4=0;
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
  if (g_00DEC1B4 > 0) {
   Int fade = ++g_00DEC1BC;
   if (fade < g_00DEC1B8)
    BfmeScreenTransitionFadeValue = (Real)fade / (Real)g_00DEC1B8;
   else { BfmeScreenTransitionFadeValue = 1; g_00DEC1BC=0; g_00DEC1B4=0; }
  } else if (g_00DEC1B4 < 0) {
   Int fade = ++g_00DEC1BC;
   if (fade < g_00DEC1B8)
    BfmeScreenTransitionFadeValue = 1 - (Real)fade / (Real)g_00DEC1B8;
   else {
    BfmeScreenTransitionFadeValue=0;
    TheTacticalView->setViewFilterMode(FM_NULL_MODE);
    TheTacticalView->setViewFilter(FT_NULL_FILTER);
    g_00DEC1BC=0; g_00DEC1B4=0;
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


// ?set@Rva000F9989Filter@@MAEHW4FilterModes@@@Z @0x000F9989
// Native 590B RET4 body byte-identical in shape to Rva000FCF54Filter::set above (same fade ladder,
// preset material, opaque shader, empty texture and depth-state setup); another screen filter of the
// same family. Owner remains unknown; the class is a neutral address-derived view.
class Rva000F9989Filter
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
Int Rva000F9989Filter::set(FilterModes mode) {
 if (mode > FM_NULL_MODE) {
  if (g_00DEC1B4 > 0) {
   Int fade = ++g_00DEC1BC;
   if (fade < g_00DEC1B8)
    BfmeScreenTransitionFadeValue = (Real)fade / (Real)g_00DEC1B8;
   else { BfmeScreenTransitionFadeValue = 1; g_00DEC1BC=0; g_00DEC1B4=0; }
  } else if (g_00DEC1B4 < 0) {
   Int fade = ++g_00DEC1BC;
   if (fade < g_00DEC1B8)
    BfmeScreenTransitionFadeValue = 1 - (Real)fade / (Real)g_00DEC1B8;
   else {
    BfmeScreenTransitionFadeValue=0;
    TheTacticalView->setViewFilterMode(FM_NULL_MODE);
    TheTacticalView->setViewFilter(FT_NULL_FILTER);
    g_00DEC1BC=0; g_00DEC1B4=0;
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

