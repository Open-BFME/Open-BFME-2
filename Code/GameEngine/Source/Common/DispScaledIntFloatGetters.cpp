// Scaled-int float getters: ten-byte __thiscall members with one shape:
//
//     fild dword [ecx+<DISP>] / fmul dword [global] / ret
//
// One int is read at a fixed displacement from `this`, converted to float
// and scaled by an engine float global. MSVC 7.1 emits the disp8 convert
// `DB 41 XX` plus the absolute multiply `D8 0D <VA>`, plus `ret`, for ten
// bytes total. Identity is not recovered: every name is derived from its
// address.
// No // cl: line (defaults match the frameless ten-byte shape).
extern float g_Va00BCF628;

#define BFME_SCALED_INT_FLOAT_GETTER(NAME, DISP) \
	class NAME \
	{ \
	public: \
		float get() const; \
		char m_lead[DISP]; \
		int m_value; \
	}; \
	float NAME::get() const \
	{ \
		return m_value * g_Va00BCF628; \
	}

BFME_SCALED_INT_FLOAT_GETTER(Rva0028A9B5ScaledIntField, 0x10)
BFME_SCALED_INT_FLOAT_GETTER(Rva0028A9BFScaledIntField, 0x14)
BFME_SCALED_INT_FLOAT_GETTER(Rva0028A9C9ScaledIntField, 0x18)
