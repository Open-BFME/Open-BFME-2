// Disp32 float setters: seventeen-byte __thiscall members with one shape:
//
//     movss xmm0,[esp+4] / movss [ecx+<DISP>],xmm0 / ret 4
//
// One float argument is stored at a fixed 32-bit displacement from `this`.
// MSVC 7.1 emits `F3 0F 10 44 24 04` plus `F3 0F 11 81 DISP32` plus
// `C2 04 00` for seventeen bytes total with /arch:SSE. Identity is not
// recovered: every name is derived from its address.
// cl: /MD /DNDEBUG
#define BFME_DISP32_FLOAT_SETTER(NAME, DISP) \
	class NAME \
	{ \
	public: \
		void set(float newValue); \
		char m_leadingPadding[DISP]; \
		float m_floatValue; \
	}; \
	void NAME::set(float newValue) \
	{ \
		m_floatValue = newValue; \
	}
BFME_DISP32_FLOAT_SETTER(Rva00167F15FloatField, 0xFC)
BFME_DISP32_FLOAT_SETTER(Rva00167F37FloatField, 0x100)
BFME_DISP32_FLOAT_SETTER(Rva001D972BFloatField, 0x94)
BFME_DISP32_FLOAT_SETTER(Rva0029A767FloatField, 0x764)
BFME_DISP32_FLOAT_SETTER(Rva002A9E25FloatField, 0x314)
BFME_DISP32_FLOAT_SETTER(Rva002AA0CDFloatField, 0x6F8)

// BF1 9cbfb551fe Common/INI/AudioEventInfoConstructor.cpp One::set is the
// clean 1.0f-store semantic guide; its AudioEventInfo and helper identities
// are not target facts. Complete native177F00..177F0D lies after RET177EFF
// and before the already-rowed177F0D body. It writes ECX+0 from independently
// verified BBB8D8=0000803F and returns without stack arguments. Original owner,
// field purpose, qualifiers and complete class bounds remain unresolved.
struct Rva00177F00Fields {
    float value00;
    void setOne();
};
void Rva00177F00Fields::setOne() { value00=1.0f; }

// Native30F2BA..30F2C7 is a complete float-argument store at ECX+0,
// between independently bounded RET4 at30F2B7 and known getter30F2C7.
// Found beside the BF1 9cb WaterRenderObjConstructor Boxed<float> placement;
// adjacency does not establish its original class or field purpose.
class Rva0030F2BAFloatField
{
public:
    void set(float value);
    float m_value;
};
void Rva0030F2BAFloatField::set(float value)
{
    m_value=value;
}

// BF1 f98983a7d3 GameLogic/Object/Body/InactiveBodyCtorThunk.cpp is the
// clean store-and-return source guide, compiled at /O1 /arch:SSE2 /G6.
// Its InactiveBody identity and 1.0f initializer are not target facts.
// Native432E4E..432E5D follows the complete jump/lookup tables of432B18:
// seven DWORD targets at432E22 and sixteen byte selectors at432E3E,
// bounded by CMP 0xF. Known independent432E5D follows its own RET.
// The body writes ECX+0 from actual BD5E50=00004842 (50.0f), returns
// the same pointer in EAX and takes no stack arguments. No calls or
// image address references establish its original owner/constructor role.
// This free fastcall view states only the observed float output contract.
float *__fastcall Rva00432E4EInitialize(float *output)
{
    *output = 50.0f;
    return output;
}

// BF1 f98983a7d3 WW3D2/animobj.cpp supplies only the clean float-store
// source shape (fresh /O2 /arch:SSE2 /G6 donor sweep). Its animation method
// is already owned at target1A5440 and is not the identity of this body.
// Native39D470..39D481 copies the raw argument word to ECX+120 with MOVSS,
// takes one four-byte stack argument and returns with RET4. Independent
// RET4 at39D46D precedes it; the next byte setter starts at39D481.
// Float is the source ABI used for this bit-preserving store; original
// owner, field meaning and bounds beyond the accessed word are unresolved.
BFME_DISP32_FLOAT_SETTER(Rva0039D470FloatField, 0x120)
