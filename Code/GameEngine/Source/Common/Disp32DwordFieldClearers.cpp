// Disp32 dword clearers: eight-byte __thiscall members with one shape:
//
//     and dword ptr [ecx+<DISP32>],0 / ret     (83 A1 XX XX XX XX 00 C3)
//
// A dword counter at a fixed displacement from `this` is cleared in place.
// The zero is applied as an AND-immediate (not a MOV-immediate): under /O1
// MSVC 7.1 emits the RMW form `83 A1 <disp32> 00` for `m_counter = 0` (probe-
// proven: defaults emit the 11-byte MOV-imm form `C7 81 <disp32> 00000000`).
// The displacements here do not fit in a signed byte, hence disp32. This is
// the clearing sibling of the Disp32DwordFieldIncDec family (kept in a
// separate TU so that TU keeps its flagless defaults; same-class-in-2-TUs is
// precedented). Identity is not recovered: every name is derived from its
// address.
// cl: /O1
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

BFME_DISP32_DWORD_CLEAR(Rva00085285DwordClearer, 0xC4)
BFME_DISP32_DWORD_CLEAR(Rva00210D15DwordClearer, 0x264)
BFME_DISP32_DWORD_CLEAR(Rva0033F90FDwordClearer, 0x160)
BFME_DISP32_DWORD_CLEAR(Rva004CF406DwordClearer, 0x12130)
BFME_DISP32_DWORD_CLEAR(Rva0059EE7FDwordClearer, 0x488)
