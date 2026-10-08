// Disp8 word-field getters: five-byte __thiscall members with one shape:
//
//     mov ax,[ecx+<DISP>] / ret
//
// One word is read at a fixed displacement from `this` and returned in ax.
// The small-offset sibling of the disp32 family in DispWordFieldGetters.cpp
// (MSVC 7.1 uses disp8 whenever the offset fits, so every offset here fits
// in a signed byte). Members before the accessed one are spelled as a lead
// array because their types are not witnessed here, only their total size.
// Identity is not recovered: every name is derived from its address.
// No // cl: line (defaults match the frameless five-byte shape).
#define BFME_DISP8_WORD_FIELD_GETTER(NAME, OFFSET) \
	class NAME \
	{ \
	public: \
		unsigned short get() const; \
		char m_lead[OFFSET]; \
		unsigned short m_value; \
	}; \
	unsigned short NAME::get() const \
	{ \
		return m_value; \
	}

BFME_DISP8_WORD_FIELD_GETTER(Rva004D5767WordField, 0x1C)
BFME_DISP8_WORD_FIELD_GETTER(Rva004D5973WordField, 0x20)
BFME_DISP8_WORD_FIELD_GETTER(Rva00531E0FWordField, 0x06)
BFME_DISP8_WORD_FIELD_GETTER(Rva00594F07WordField, 0x0C)
BFME_DISP8_WORD_FIELD_GETTER(Rva0011C420WordField, 0x0C)
BFME_DISP8_WORD_FIELD_GETTER(Rva0011C440WordField, 0x10)
BFME_DISP8_WORD_FIELD_GETTER(Rva004CEE9CWordField, 0x10)
BFME_DISP8_WORD_FIELD_GETTER(Rva00568645WordField, 0x44)

// BF1 9cb Rva003D4BD0Word.cpp guides this two-load leaf. Target
// 531EA5..531EAB follows RET and returns the pointed-to raw word in AX.
// Original owner, signedness and complete class bounds remain unknown.
struct Rva00531EA5Fields
{
    const unsigned short *pointer;
    unsigned short get() const;
};
unsigned short Rva00531EA5Fields::get() const { return *pointer; }
