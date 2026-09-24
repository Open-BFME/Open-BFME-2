// cl: /O1
// Disp32 dword clearers: eight-byte __thiscall members with one shape:
//
//     and dword ptr [ecx+<DISP32>],0 / ret     (83 A1 XX XX XX XX 00 C3)
//
// A dword counter at a fixed displacement from `this` is cleared in place.
// The zero is applied as an AND-immediate (not a MOV-immediate): under /O1
// MSVC 7.1 emits the RMW form for `m_counter = 0` (defaults emit the longer
// MOV-imm form). The displacements here do not fit in a signed byte, hence
// disp32. Sibling TU to the field-clearer family, kept separate to avoid
// churning a live file. Identity is not recovered: every name is derived
// from its address.
#define BFME_DISP32_DWORD_CLEAR(NAME, DISP) \
	class NAME \
	{ \
	public: \
		void clear(); \
		char m_lead[DISP]; \
		int m_counter; \
	}; \
	void NAME::clear() \
	{ \
		m_counter = 0; \
	}
BFME_DISP32_DWORD_CLEAR(Rva000685DADwordClearer, 0x37AC)
BFME_DISP32_DWORD_CLEAR(Rva00262CB6DwordClearer, 0x1FC)
BFME_DISP32_DWORD_CLEAR(Rva002A9F0FDwordClearer, 0x31C)
BFME_DISP32_DWORD_CLEAR(Rva00381DB5DwordClearer, 0x1638)
BFME_DISP32_DWORD_CLEAR(Rva0039D761DwordClearer, 0x1D8)
BFME_DISP32_DWORD_CLEAR(Rva003ECB0BDwordClearer, 0x564)
BFME_DISP32_DWORD_CLEAR(Rva0044E5B8DwordClearer, 0x80)
BFME_DISP32_DWORD_CLEAR(Rva004A750ADwordClearer, 0xC8)
BFME_DISP32_DWORD_CLEAR(Rva004ACD43DwordClearer, 0x44C)
