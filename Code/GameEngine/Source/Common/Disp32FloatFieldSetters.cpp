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
