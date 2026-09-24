// Disp32 float setters: seventeen-byte __thiscall members with one shape:
//
//     movss xmm0,[esp+4] / movss [ecx+<DISP>],xmm0 / ret 4
//
// One float argument is stored at a fixed 32-bit displacement from `this`.
// MSVC 7.1 emits `F3 0F 10 44 24 04` plus `F3 0F 11 81 DISP32` plus
// `C2 04 00` for seventeen bytes total with /arch:SSE. Identity is not
// recovered: every name is derived from its address.
// cl: /arch:SSE /MD /DNDEBUG
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
BFME_DISP32_FLOAT_SETTER(Rva002633F3FloatField, 0x168)
BFME_DISP32_FLOAT_SETTER(Rva00167F15FloatField, 0xFC)
BFME_DISP32_FLOAT_SETTER(Rva00167F37FloatField, 0x100)
BFME_DISP32_FLOAT_SETTER(Rva001D972BFloatField, 0x94)
