// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// set is slot 5 of the same native table as the existing shutdown:
// 0x007CF270, entries 0x007CF274 -> F884C and 0x007CF284 -> F9989.
// The complete set body is F9989..F9BD7, 590B, ending RET4; the next
// shutdown starts at F9BD7. BFME 1 f98983a7d3bb405f1a4ba94bb6a2a168062a819d
// game/GameEngineDevice/Source/W3DDevice/GameClient/
// ScreenFilterRva007DB820Set.cpp supplies the semantic fade/setup donor.
// The verified BFME 2 DOT3 setup supplies the target texture-reference ABI
// and shader/depth helpers. This group advances its fade on every call.
// All bytes and relocations agree, including the existing 156B shutdown.
// The established neutral owner spelling is retained; this partial view
// has explicit vptr storage, so its body methods are declared nonvirtual.
// Original filter and global identifiers remain unknown.

typedef int Int;
typedef float Real;
typedef bool Bool;
enum FilterModes { FM_NULL_MODE=0 };
enum FilterTypes { FT_NULL_FILTER=0 };
#define PAD_VIRTUALS10(p) \
 virtual void p##0(); virtual void p##1(); virtual void p##2(); virtual void p##3(); virtual void p##4(); \
 virtual void p##5(); virtual void p##6(); virtual void p##7(); virtual void p##8(); virtual void p##9();
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


// Independent fade group at native RVAs 9EC068/6C/70/74. The slot-5
// setup proves the roles; all four initial values are zero in retail.
// Descriptive names retain uncertainty about the original identifiers.
Real BfmeFilterFadeValue = 0.0f;
Int BfmeFilterFadeDirection = 0;
Int BfmeFilterFadeFrames = 0;
Int BfmeFilterFadeCurrentFrame = 0;
// cl: -Ireference/open-bfme-1/game/GameEngineDevice/Source/W3DDevice/GameClient

class Rva007DB820ComRef
{
public:
	virtual long __stdcall QueryInterface() = 0;
	virtual unsigned long __stdcall AddRef() = 0;
	virtual unsigned long __stdcall Release() = 0;
};

class Rva007DB820
{
public:
	int shutdown();
	Int set(FilterModes mode);
	Int init();

private:
	void *m_vptr;
	Rva007DB820ComRef *m_04;
	Rva007DB820ComRef *m_08;
	Rva007DB820ComRef *m_0C;
	unsigned char m_pad10[0x08];
	Rva007DB820ComRef *m_18;
	Rva007DB820ComRef *m_1C;
	unsigned char m_pad20[0x24];
	Rva007DB820ComRef *m_44;
	Rva007DB820ComRef *m_48;
	Rva007DB820ComRef *m_4C;
	Rva007DB820ComRef *m_50;
};

int Rva007DB820::shutdown()
{
	if (m_04) m_04->Release();
	if (m_08) m_08->Release();
	if (m_0C) m_0C->Release();
	m_04 = 0;
	m_08 = 0;
	m_0C = 0;
	if (m_1C) m_1C->Release();
	m_1C = 0;
	if (m_18) m_18->Release();
	m_18 = 0;
	if (m_4C) m_4C->Release();
	m_4C = 0;
	if (m_44) m_44->Release();
	m_44 = 0;
	if (m_50) m_50->Release();
	m_50 = 0;
	if (m_48) m_48->Release();
	m_48 = 0;
	return 1;
}

Int Rva007DB820::set(FilterModes mode) {
 if (mode > FM_NULL_MODE) {
  if (BfmeFilterFadeDirection > 0) {
   Int fade = ++BfmeFilterFadeCurrentFrame;
   if (fade < BfmeFilterFadeFrames)
    BfmeFilterFadeValue = (Real)fade / (Real)BfmeFilterFadeFrames;
   else { BfmeFilterFadeValue = 1; BfmeFilterFadeCurrentFrame=0; BfmeFilterFadeDirection=0; }
  } else if (BfmeFilterFadeDirection < 0) {
   Int fade = ++BfmeFilterFadeCurrentFrame;
   if (fade < BfmeFilterFadeFrames)
    BfmeFilterFadeValue = 1 - (Real)fade / (Real)BfmeFilterFadeFrames;
   else {
    BfmeFilterFadeValue=0;
    TheTacticalView->setViewFilterMode(FM_NULL_MODE);
    TheTacticalView->setViewFilter(FT_NULL_FILTER);
    BfmeFilterFadeCurrentFrame=0; BfmeFilterFadeDirection=0;
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

// Native 0x000F839B..0x000F83A9 is the whole slot-0 init, 14B RET0.
// Unlike BFME 1's full shader/texture initializer, BFME 2 clears the
// existing +04 COM field and this fade group's frame, then returns failure.
// The next body is the independently matched slot-2 preRender. The same
// vftable and shutdown establish the receiver and the +04 field.
Int Rva007DB820::init()
{
	m_04 = 0;
	BfmeFilterFadeCurrentFrame = 0;
	return 0;
}
