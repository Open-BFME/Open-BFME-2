// Disp8 dword getters: four-byte __thiscall members with one shape:
//
//     mov eax,[ecx+<DISP>] / ret
//
// One dword is read at a fixed displacement from `this` and returned. Every
// displacement here fits in a signed byte, so MSVC 7.1 emits the disp8 form
// `8B 41 XX` (three bytes) plus `ret`, for four bytes total. This is the
// small-offset sibling of the disp32 DispDwordFieldGetters family (seven
// bytes per body); the encoding itself is why the two families are kept in
// separate translation units. The accessed member is spelled as an `int`
// right after the lead array; the bytes cannot distinguish `int` from
// `unsigned int`, a pointer, or anything else four bytes wide moved with a
// plain load. Members before the accessed one are spelled as a lead array
// because their types are not witnessed here, only their total size.
// Identity is not recovered: every name is derived from its address (BFME1
// pioneered the same opaque-holder pattern in
// reference/open-bfme-1/Code/GameEngine/Source/Common/DispDwordFieldGetters.cpp).
// No // cl: line (defaults match the frameless four-byte shape).
#define BFME_DISP8_DWORD_GETTER(NAME, DISP) \
	class NAME \
	{ \
	public: \
		int get() const; \
		char m_lead[DISP]; \
		int m_value; \
	}; \
	int NAME::get() const \
	{ \
		return m_value; \
	}

BFME_DISP8_DWORD_GETTER(Rva0013E9F0DwordField, 0x10)
BFME_DISP8_DWORD_GETTER(Rva0013EDC0DwordField, 0x2C)
BFME_DISP8_DWORD_GETTER(Rva00143290DwordField, 0x48)
BFME_DISP8_DWORD_GETTER(Rva00143430DwordField, 0x18)
BFME_DISP8_DWORD_GETTER(Rva00143D80DwordField, 0x0C)
BFME_DISP8_DWORD_GETTER(Rva00149580DwordField, 0x34)
BFME_DISP8_DWORD_GETTER(Rva00661E60DwordField, 0x64)
BFME_DISP8_DWORD_GETTER(Rva00661FD0DwordField, 0x40)
BFME_DISP8_DWORD_GETTER(Rva0066D450DwordField, 0x14)
BFME_DISP8_DWORD_GETTER(Rva0066D490DwordField, 0x1C)
BFME_DISP8_DWORD_GETTER(Rva0066D520DwordField, 0x20)
BFME_DISP8_DWORD_GETTER(Rva0066D590DwordField, 0x28)
BFME_DISP8_DWORD_GETTER(Rva0066D5A0DwordField, 0x6C)
BFME_DISP8_DWORD_GETTER(Rva0066D5B0DwordField, 0x30)
BFME_DISP8_DWORD_GETTER(Rva0066D5C0DwordField, 0x60)
BFME_DISP8_DWORD_GETTER(Rva0066D5D0DwordField, 0x50)
BFME_DISP8_DWORD_GETTER(Rva0066D5E0DwordField, 0x54)
BFME_DISP8_DWORD_GETTER(Rva0066D5F0DwordField, 0x58)
BFME_DISP8_DWORD_GETTER(Rva0066D600DwordField, 0x5C)
BFME_DISP8_DWORD_GETTER(Rva0066D630DwordField, 0x68)
BFME_DISP8_DWORD_GETTER(Rva0066D650DwordField, 0x4C)
BFME_DISP8_DWORD_GETTER(Rva0066D680DwordField, 0x78)
BFME_DISP8_DWORD_GETTER(Rva0066D730DwordField, 0x44)
BFME_DISP8_DWORD_GETTER(Rva0066DD00DwordField, 0x24)
BFME_DISP8_DWORD_GETTER(Rva0066EA50DwordField, 0x38)
BFME_DISP8_DWORD_GETTER(Rva0066EA60DwordField, 0x3C)
BFME_DISP8_DWORD_GETTER(Rva0009AAA4DwordField, 0x54)
BFME_DISP8_DWORD_GETTER(Rva002004A1DwordField, 0x64)
BFME_DISP8_DWORD_GETTER(Rva00091A56DwordField, 0x24)
BFME_DISP8_DWORD_GETTER(Rva00225A98DwordField, 0x50)
BFME_DISP8_DWORD_GETTER(Rva0030C896DwordField, 0x7C)
BFME_DISP8_DWORD_GETTER(Rva0036750CDwordField, 0x6C)
BFME_DISP8_DWORD_GETTER(Rva003F3FCEDwordField, 0x58)
BFME_DISP8_DWORD_GETTER(Rva003F3FE8DwordField, 0x30)
BFME_DISP8_DWORD_GETTER(Rva0057E556DwordField, 0x14)
BFME_DISP8_DWORD_GETTER(Rva005C4AE9DwordField, 0x34)
BFME_DISP8_DWORD_GETTER(Rva005C4AEDDwordField, 0x38)
BFME_DISP8_DWORD_GETTER(Rva005C4AF1DwordField, 0x3C)
BFME_DISP8_DWORD_GETTER(Rva005C4AF5DwordField, 0x40)
BFME_DISP8_DWORD_GETTER(Rva005C4AF9DwordField, 0x44)
// Negative-displacement sibling: the disp8 byte sign-extends, so a disp byte
// above 0x7F reads *before* `this` (e.g. D4 = -44, an embedded member view).
// Spelled as a negative word index from `this`, which MSVC 7.1 folds to the
// same `8B 41 XX` disp8 load. Identity is not recovered: names stay
// address-derived like the forward getters above.
#define BFME_DISP8_NEG_DWORD_GETTER(NAME, INDEX) \
	class NAME \
	{ \
	public: \
		int get() const; \
	}; \
	int NAME::get() const \
	{ \
		return ((const int *)this)[INDEX]; \
	}

BFME_DISP8_DWORD_GETTER(Rva001DB09DDwordField, 0x10)
BFME_DISP8_DWORD_GETTER(Rva002A98A7DwordField, 0x4C)
BFME_DISP8_DWORD_GETTER(Rva002A98ABDwordField, 0x60)
BFME_DISP8_NEG_DWORD_GETTER(Rva0030BCAEDwordField, -11)
BFME_DISP8_DWORD_GETTER(Rva0030D377DwordField, 0x20)
BFME_DISP8_DWORD_GETTER(Rva0030F2C7DwordField, 0x1C)
BFME_DISP8_NEG_DWORD_GETTER(Rva00330BD7DwordField, -3)
BFME_DISP8_NEG_DWORD_GETTER(Rva0044467CDwordField, -2)
BFME_DISP8_DWORD_GETTER(Rva0008BB81DwordField, 0x5C)
BFME_DISP8_DWORD_GETTER(Rva0049CB8ADwordField, 0x70)
BFME_DISP8_DWORD_GETTER(Rva005C4AE1DwordField, 0x28)
BFME_DISP8_DWORD_GETTER(Rva005C4AFDDwordField, 0x48)
BFME_DISP8_DWORD_GETTER(Rva0013B150DwordField, 0x7C)
BFME_DISP8_DWORD_GETTER(Rva002A79A1DwordField, 0x18)
BFME_DISP8_DWORD_GETTER(Rva00367508DwordField, 0x68)
BFME_DISP8_DWORD_GETTER(Rva004F04F1DwordField, 0x78)
BFME_DISP8_DWORD_GETTER(Rva000A8AA2DwordField, 0x04)
BFME_DISP8_DWORD_GETTER(Rva00201ADEDwordField, 0x08)
BFME_DISP8_DWORD_GETTER(Rva0040CA36DwordField, 0x24)
BFME_DISP8_DWORD_GETTER(Rva004E062EDwordField, 0x40)
BFME_DISP8_DWORD_GETTER(Rva004E063BDwordField, 0x44)
BFME_DISP8_NEG_DWORD_GETTER(Rva00464825DwordField, -6)
