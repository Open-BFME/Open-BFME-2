// Disp8 byte setters: five-byte __thiscall members with one shape:
//
//     mov byte [ecx+<DISP>],<IMM8> / ret
//
// One byte at a fixed displacement from `this` is overwritten with a small
// constant (0 or 1 throughout this family) and nothing is read back.
// MSVC 7.1 emits `C6 41 XX YY`, plus `ret`, for five bytes total. Identity
// is not recovered: every name is derived from its address.
// No // cl: line (defaults match the frameless five-byte shape).
#define BFME_DISP8_BYTE_SETTER(NAME, METHOD, DISP, IMM) \
	class NAME \
	{ \
	public: \
		void METHOD(); \
		char m_lead[DISP]; \
		unsigned char m_flag; \
	}; \
	void NAME::METHOD() \
	{ \
		m_flag = IMM; \
	}
BFME_DISP8_BYTE_SETTER(Rva00042687ByteSetter, disable, 0x48, 0x0)
BFME_DISP8_BYTE_SETTER(Rva0006E293ByteSetter, enable, 0x42, 0x1)
BFME_DISP8_BYTE_SETTER(Rva0008BB6AByteSetter, enable, 0x76, 0x1)
BFME_DISP8_BYTE_SETTER(Rva00250A49ByteSetter, disable, 0x4, 0x0)
BFME_DISP8_BYTE_SETTER(Rva002A9911ByteSetter, enable, 0x47, 0x1)
BFME_DISP8_BYTE_SETTER(Rva002C5803ByteSetter, enable, 0x19, 0x1)
BFME_DISP8_BYTE_SETTER(Rva0033F2D7ByteSetter, disable, 0x49, 0x0)
BFME_DISP8_BYTE_SETTER(Rva00368129ByteSetter, enable, 0x40, 0x1)
BFME_DISP8_BYTE_SETTER(Rva00421744ByteSetter, disable, 0x34, 0x0)
BFME_DISP8_BYTE_SETTER(Rva0046191DByteSetter, disable, 0xD, 0x0)
BFME_DISP8_BYTE_SETTER(Rva004A808CByteSetter, disable, 0x22, 0x0)
BFME_DISP8_BYTE_SETTER(Rva004D3765ByteSetter, enable, 0x48, 0x1)
BFME_DISP8_BYTE_SETTER(Rva004D81D2ByteSetter, enable, 0x37, 0x1)
BFME_DISP8_BYTE_SETTER(Rva005975F2ByteSetter, enable, 0x34, 0x1)
