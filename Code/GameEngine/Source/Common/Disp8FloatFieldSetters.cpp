// cl: /MD /DNDEBUG
// Disp8 float setters: twelve-byte (fourteen with padding) __thiscall members with one shape:
//
//     movss xmm0,[esp+4] / movss [ecx+<DISP>],xmm0 / ret 4
//
// One float argument is stored at a fixed displacement from `this` that fits
// in a signed byte (the small-offset sibling of Disp32FloatFieldSetters.cpp,
// same lead-array idiom; /arch:SSE comes from the retail flag region).
// Identity is not recovered: every name is derived from its address.
//   0x0015DFA0 +0x1C  among the SegLineRendererClass setters (0x0015DFD0
//                     Set_Noise_Amplitude +0x24 follows)
//   0x00196100 +0x04  directly before SegLineRendererClass::Set_Width
//                     (0x00196110, +0x08)
#define BFME_DISP8_FLOAT_SETTER(NAME, DISP) \
	class NAME \
	{ \
	public: \
		void set(float newValue); \
		char m_lead[DISP]; \
		float m_value; \
	}; \
	void NAME::set(float newValue) \
	{ \
		m_value = newValue; \
	}

BFME_DISP8_FLOAT_SETTER(Rva00196100FloatField, 0x04)
