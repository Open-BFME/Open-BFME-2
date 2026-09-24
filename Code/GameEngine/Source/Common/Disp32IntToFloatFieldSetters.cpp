// Disp32 int-to-float setters: seventeen-byte __thiscall members with one shape:
//
//     cvtsi2ss xmm0,[esp+4] / movss [ecx+<DISP>],xmm0 / ret 4
//
// An int argument is converted to float and stored at a fixed 32-bit
// displacement from `this`. MSVC 7.1 emits `F3 0F 2A 44 24 04` plus
// `F3 0F 11 81 DISP32` plus `C2 04 00` for seventeen bytes total with
// /arch:SSE. Five sit interleaved with the float-to-int getters in
// Disp32CvtFloatIntGetters.cpp (each setter immediately precedes its getter
// at +0x11); a sixth pairs with Rva002620ADIntGetter at 0x2620AD/0x2620B6.
// Identity is not recovered: every name is derived from its
// address.
// cl: /arch:SSE /MD /DNDEBUG
#define BFME_DISP32_INT_TO_FLOAT_SETTER(NAME, DISP) \
	class NAME \
	{ \
	public: \
		void set(int newValue); \
		char m_leadingPadding[DISP]; \
		float m_floatValue; \
	}; \
	void NAME::set(int newValue) \
	{ \
		m_floatValue = (float)newValue; \
	}
BFME_DISP32_INT_TO_FLOAT_SETTER(Rva0030C8BBIntFloatField, 0x88)
BFME_DISP32_INT_TO_FLOAT_SETTER(Rva0030C8D5IntFloatField, 0x8C)
BFME_DISP32_INT_TO_FLOAT_SETTER(Rva0030C8EFIntFloatField, 0x90)
BFME_DISP32_INT_TO_FLOAT_SETTER(Rva0030C909IntFloatField, 0x94)
BFME_DISP32_INT_TO_FLOAT_SETTER(Rva0030C923IntFloatField, 0x98)
BFME_DISP32_INT_TO_FLOAT_SETTER(Rva002620B6IntFloatField, 0x1AC)
