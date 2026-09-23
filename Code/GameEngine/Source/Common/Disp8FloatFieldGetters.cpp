// Disp8 float getters: four-byte __thiscall members with one shape:
//
//     fld dword ptr [ecx+<DISP>] / ret
//
// One float is read at a fixed displacement from `this` and returned on the
// x87 stack. Every displacement here fits in a signed byte, so MSVC 7.1
// encodes it as a disp8. This is the small-offset sibling of the disp32
// family in DispFloatFieldGetters.cpp, spelled with the same BFME1-pioneered
// lead-array idiom (see
// reference/open-bfme-1/Code/GameEngine/Source/Common/DispFloatFieldGetters.cpp).
// Identity is not recovered: every name is derived from its address.
// No // cl: line (defaults match the frameless 4-byte shape).
// Negative-displacement sibling: the disp8 byte sign-extends, so a disp byte
// above 0x7F reads *before* `this` (e.g. 98 = -104). Spelled as a negative
// float index from `this`, which MSVC 7.1 folds to the same disp8 fld.
#define BFME_DISP8_FLOAT_GETTER(NAME, DISP) \
	class NAME \
	{ \
	public: \
		float get() const; \
		char m_lead[DISP]; \
		float m_value; \
	}; \
	float NAME::get() const \
	{ \
		return m_value; \
	}

#define BFME_DISP8_NEG_FLOAT_GETTER(NAME, INDEX) \
	class NAME \
	{ \
	public: \
		float get() const; \
	}; \
	float NAME::get() const \
	{ \
		return ((const float *)this)[INDEX]; \
	}

BFME_DISP8_FLOAT_GETTER(Rva0015DF10FloatField, 0x1C)
BFME_DISP8_FLOAT_GETTER(Rva0015DF20FloatField, 0x18)
BFME_DISP8_FLOAT_GETTER(Rva0015DF30FloatField, 0x24)
BFME_DISP8_FLOAT_GETTER(Rva0015DF40FloatField, 0x28)
BFME_DISP8_FLOAT_GETTER(Rva0015DF50FloatField, 0x2C)
BFME_DISP8_FLOAT_GETTER(Rva00178FB0FloatField, 0x34)
BFME_DISP8_FLOAT_GETTER(Rva0018D340FloatField, 0x4C)
BFME_DISP8_FLOAT_GETTER(Rva0018F180FloatField, 0x50)
BFME_DISP8_FLOAT_GETTER(Rva006C03E0FloatField, 0x0C)
BFME_DISP8_FLOAT_GETTER(Rva00723490FloatField, 0x08)
BFME_DISP8_FLOAT_GETTER(Rva0073A1C0FloatField, 0x20)
BFME_DISP8_FLOAT_GETTER(Rva0008BB38FloatField, 0x40)
BFME_DISP8_NEG_FLOAT_GETTER(Rva0030592FFloatField, -26)
BFME_DISP8_FLOAT_GETTER(Rva004987FEFloatField, 0x38)
BFME_DISP8_FLOAT_GETTER(Rva00094A94FloatField, 0x1C)
BFME_DISP8_FLOAT_GETTER(Rva00094A98FloatField, 0x28)
BFME_DISP8_FLOAT_GETTER(Rva00094A9CFloatField, 0x2C)
BFME_DISP8_FLOAT_GETTER(Rva00094AEAFloatField, 0x60)
BFME_DISP8_FLOAT_GETTER(Rva0008BD0FFloatField, 0x6C)
BFME_DISP8_FLOAT_GETTER(Rva0008BD27FloatField, 0x70)
BFME_DISP8_FLOAT_GETTER(Rva00091A44FloatField, 0x24)
BFME_DISP8_NEG_FLOAT_GETTER(Rva00299CC2FloatField, -10)
BFME_DISP8_FLOAT_GETTER(Rva0041B801FloatField, 0x74)
BFME_DISP8_FLOAT_GETTER(Rva00437603FloatField, 0x58)
BFME_DISP8_FLOAT_GETTER(Rva004987FAFloatField, 0x34)
BFME_DISP8_FLOAT_GETTER(Rva0049CB5BFloatField, 0x18)
BFME_DISP8_FLOAT_GETTER(Rva004F5F8AFloatField, 0x0C)
BFME_DISP8_FLOAT_GETTER(Rva00542BDEFloatField, 0x64)
BFME_DISP8_FLOAT_GETTER(Rva005C4ADDFloatField, 0x20)
BFME_DISP8_FLOAT_GETTER(Rva005C4B01FloatField, 0x4C)
BFME_DISP8_FLOAT_GETTER(Rva0008BB23FloatField, 0x30)
BFME_DISP8_FLOAT_GETTER(Rva0008BB46FloatField, 0x54)
BFME_DISP8_FLOAT_GETTER(Rva0008BB58FloatField, 0x50)
BFME_DISP8_FLOAT_GETTER(Rva0008BB7DFloatField, 0x68)
BFME_DISP8_FLOAT_GETTER(Rva0008E10EFloatField, 0x3C)
BFME_DISP8_FLOAT_GETTER(Rva005D870DFloatField, 0x10)
