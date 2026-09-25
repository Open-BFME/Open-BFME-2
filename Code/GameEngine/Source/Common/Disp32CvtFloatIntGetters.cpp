// Disp32 float-to-int getters: nine-byte const __thiscall members with one
// shape:
//
//     cvttss2si eax,[ecx+<DISP>] / ret
//
// One float field is read back truncated to int. Most displacements here are
// disp32 (MSVC 7.1 uses disp8 whenever the offset fits, so most offsets
// are at least 0x80); the 0x78 sibling below compiles to the six-byte disp8
// encoding. Identity is not recovered: every name is derived from
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
BFME_DISP32_CVT_FLOAT_INT_GETTER(Rva0030C900IntGetter, 0x90)
BFME_DISP32_CVT_FLOAT_INT_GETTER(Rva0030C91AIntGetter, 0x94)
BFME_DISP32_CVT_FLOAT_INT_GETTER(Rva0030C934IntGetter, 0x98)
BFME_DISP32_CVT_FLOAT_INT_GETTER(Rva002620ADIntGetter, 0x1AC)
BFME_DISP32_CVT_FLOAT_INT_GETTER(Rva0030C890IntGetter, 0x78)
