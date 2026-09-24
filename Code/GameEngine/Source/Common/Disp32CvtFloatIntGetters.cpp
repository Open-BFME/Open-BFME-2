// Disp32 float-to-int getters: nine-byte const __thiscall members with one
// shape:
//
//     cvttss2si eax,[ecx+<DISP>] / ret
//
// One float field is read back truncated to int. Every displacement here is
// a disp32 (MSVC 7.1 uses disp8 whenever the offset fits, so every offset
// is at least 0x80). Identity is not recovered: every name is derived from
// its address.
// cl: /arch:SSE /MD /EHsc /DNDEBUG
#define BFME_DISP32_CVT_FLOAT_INT_GETTER(NAME, DISP) \
	class NAME \
	{ \
	public: \
		int get() const; \
		char m_lead[DISP]; \
		float m_value; \
	}; \
	int NAME::get() const \
	{ \
		return (int)m_value; \
	}

BFME_DISP32_CVT_FLOAT_INT_GETTER(Rva0030C8CCIntGetter, 0x88)
BFME_DISP32_CVT_FLOAT_INT_GETTER(Rva0030C8E6IntGetter, 0x8C)
