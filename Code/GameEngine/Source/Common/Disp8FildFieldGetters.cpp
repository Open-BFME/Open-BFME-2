// Disp8 fild getters: four-byte __thiscall members with one shape:
//
//     fild dword ptr [ecx+<DISP>] / ret
//
// One int is loaded from a fixed displacement from `this` onto the x87
// stack, which is the return convention for `double`, so the member reads as
// an int-to-double conversion. Every displacement here fits in a signed
// byte, so MSVC 7.1 encodes it as a disp8. Spelled with the lead-array idiom
// of the neighboring Disp* families (char pad, then the int member).
// Identity is not recovered: every name is derived from its address.
// No // cl: line (defaults match the frameless four-byte shape).
#define BFME_DISP8_FILD_GETTER(NAME, DISP) \
	class NAME \
	{ \
	public: \
		double get() const; \
		char m_lead[DISP]; \
		int m_value; \
	}; \
	double NAME::get() const \
	{ \
		return m_value; \
	}

BFME_DISP8_FILD_GETTER(Rva000CB0FFFildField, 0x38)
BFME_DISP8_FILD_GETTER(Rva004B6FF3FildField, 0x34)
