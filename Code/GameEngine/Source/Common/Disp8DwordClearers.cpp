// flags: region default (reverse/retail_inventory/flag_regions.csv)
// Disp8 dword clearers: five-byte __thiscall members with one shape:
//
//     and dword ptr [ecx+<DISP>],0 / ret     (83 61 XX 00 C3)
//
// A dword counter at a fixed displacement from `this` is cleared in place.
// The zero is applied as an AND-immediate (not a MOV-immediate): under /O1
// MSVC 7.1 emits the RMW form for `m_counter = 0` (defaults emit the longer
// MOV-imm form). The displacements here fit in a signed byte, hence disp8.
// Identity is not recovered: every name is derived from its address.
#define BFME_DISP8_DWORD_CLEAR(NAME, DISP) \
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
BFME_DISP8_DWORD_CLEAR(Rva0010034FDwordClearer, 0xC)
BFME_DISP8_DWORD_CLEAR(Rva0020E34FDwordClearer, 0x8)
BFME_DISP8_DWORD_CLEAR(Rva0023D2D8DwordClearer, 0x38)
BFME_DISP8_DWORD_CLEAR(Rva002E0668DwordClearer, 0x44)
BFME_DISP8_DWORD_CLEAR(Rva002FD7D7DwordClearer, 0x1C)
BFME_DISP8_DWORD_CLEAR(Rva0033F9F9DwordClearer, 0x20)
BFME_DISP8_DWORD_CLEAR(Rva004C12CBDwordClearer, 0x2C)
BFME_DISP8_DWORD_CLEAR(Rva0055059ADwordClearer, 0x4)
BFME_DISP8_DWORD_CLEAR(Rva005A9D01DwordClearer, 0x5C)
BFME_DISP8_DWORD_CLEAR(Rva005B5B07DwordClearer, 0x10)
BFME_DISP8_DWORD_CLEAR(Rva005C494DDwordClearer, 0x14)
#define BFME_DISP8_DWORD_MASK(NAME, DISP, MASK) \
	class NAME \
	{ \
	public: \
		void clear(); \
		char m_lead[DISP]; \
		int m_counter; \
	}; \
	void NAME::clear() \
	{ \
		m_counter &= MASK; \
	}
BFME_DISP8_DWORD_MASK(Rva006DBD90DwordMask, 0x04, ~0x08)
BFME_DISP8_DWORD_MASK(Rva006DBDC0DwordMask, 0x04, ~0x04)

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?ClearReleaseAtEnd@AptValue@@QAEXXZ=?clear@Rva006DBDC0DwordMask@@QAEXXZ")

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?state0@Rva002E2903Player@@QAEXXZ=?clear@Rva002E0668DwordClearer@@QAEXXZ")

// Clean BF1 9cbfb551fe20dae985f91f2319d8997287b6a705 donor
// game/GameEngine/Source/Common/R1MemberValueReads.cpp /O1 /arch:SSE /G7
// supplies the ordered two-field zeroing expression. Retail independently
// proves dword zero stores at +0x0c then +0x24 and the complete leaf
// 0x000C9286..0x000C928F between prior RET at C9285 and the next function.
// Original receiver, field purposes and signedness remain unknown.
class Rva000C9286PairClearer
{
public:
    void clear();
private:
    char m_lead[0x0c];
    unsigned m_at0c;
    char m_middle[0x24 - 0x0c - 4];
    unsigned m_at24;
};

void Rva000C9286PairClearer::clear()
{
    m_at0c = 0;
    m_at24 = 0;
}
