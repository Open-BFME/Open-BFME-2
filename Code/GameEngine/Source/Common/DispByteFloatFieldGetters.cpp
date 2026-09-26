// cl: /O1
//
// ?get@Rva002C8EF9ByteFloatField@@QBEMXZ, retail 0x002C8EF9, 19 bytes.
// Byte-to-float getter between two DispByteFieldGetters rows (prev 0x2C8EF2/7
// next 0x2C8F0C/7): movzx byte at +0x168, fild via ebp-4 temp, EBP frame.
// New file beside DispByteFieldGetters.cpp (which is 7B mov-al-only); /O1
// gives the 19B EBP shape (frameless esp-temp would be 20B). Identity is
// address-derived honest name (byte field returning float).

#define BFME_DISP_BYTE_FLOAT_GETTER(NAME, DISP) \
	class NAME \
	{ \
	public: \
		float get() const; \
		char m_lead[DISP]; \
		unsigned char m_value; \
	}; \
	float NAME::get() const \
	{ \
		return m_value; \
	}

BFME_DISP_BYTE_FLOAT_GETTER(Rva002C8EF9ByteFloatField, 0x168)
