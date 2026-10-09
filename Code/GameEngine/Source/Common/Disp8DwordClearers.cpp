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


// Receiver-return zero-field leaves from clean BFME1 9cbfb551 donor leads:
// WorldHeightMap.cpp and W3DBridgeBufferCtorThunk.cpp supply the source pattern.
// Retail independently fixes complete RET boundaries, raw32 fields14/0C and
// EAX=receiver. The donor class names and complete layouts remain unproven;
// address-owned carriers preserve that uncertainty without aliases or pins.
// ?clear@Rva004D9A35Fields@@QAEPAU1@XZ
struct Rva004D9A35Fields { char pad[0x14]; unsigned int word14; Rva004D9A35Fields *clear(); };
Rva004D9A35Fields *Rva004D9A35Fields::clear() { word14=0; return this; }

// ?clear@Rva002175C7Fields@@QAEPAU1@XZ
struct Rva002175C7Fields { char pad[0xC]; unsigned int wordC; Rva002175C7Fields *clear(); };
Rva002175C7Fields *Rva002175C7Fields::clear() { wordC=0; return this; }

// Complete native 2C8E52..2C8E5A follows RET8 and precedes a new leaf.
// It returns the old receiver word at +4 in EAX and clears that word to zero.
// Whole clean BF1 f98983a7d3bb405f1a4ba94bb6a2a168062a819d's
// GameLogic/Object/WeaponStore_reset.cpp supplies friend_clearNextTemplate's
// take-and-clear expression. Its pointer type and WeaponTemplate identity
// are donor facts only. This consumed-prefix view preserves the raw 32 bits;
// original receiver, field type and pointer/ownership meanings remain unknown.
class Rva002C8E52WordField
{
public:
    unsigned int take();
private:
    char m_unknown0[4];
    unsigned int m_word4;
};

unsigned int Rva002C8E52WordField::take()
{
    unsigned int previous = m_word4;
    m_word4 = 0;
    return previous;
}

// Complete native 2E6C8D..2E6C94 follows the preceding member's final RET
// and precedes a distinct word setter. It loads the receiver's pointer at
// +0 and clears the pointee's raw word at +8; no original owner is proven.
// The whole clean BF1 f98983a7d3bb405f1a4ba94bb6a2a168062a819d
// GameLogic/Pathfinder/PathfindPrependCells.cpp supplies
// PathfindCell::clearParentCellForPrepend's expression as a source lead.
// Its class, parent-cell name and pointer meaning remain donor facts only.
struct Rva002E6C8DWordNode {
    char unknown0[8];
    unsigned int word8;
};
class Rva002E6C8DWordChase {
public:
    void clear();
private:
    Rva002E6C8DWordNode *node;
};
void Rva002E6C8DWordChase::clear() { node->word8 = 0; }

// Whole native 405A1C..405A25 is bracketed by the predecessor's RET at
// 405A1B and the next constructor's entry at 405A25. It loads the receiver's
// pointer at +0, clears that pointee's raw DWORD, and returns the raw word +4.
// Clean BF1 f98983a7d3bb405f1a4ba94bb6a2a168062a819d Common/
// R2SmallMemberOps.cpp, compiled O1/SSE2/G6, supplies the pointer-clear/return
// expression. Donor Rva004C1280::run and its result pointer type are source
// facts only: target receiver, field meanings and complete layout are unknown.
class Rva00405A1CWordClearResult {
public:
    unsigned int clear();
private:
    unsigned int *target;
    unsigned int result;
};
unsigned int Rva00405A1CWordClearResult::clear() {
    *target = 0;
    return result;
}

// Complete native 4DE52C..4DE536 follows RET8 at4DE529 and precedes the
// distinct word-copy leaf4DE536. ECX supplies the accessed prefix; EAX keeps
// that receiver while raw DWORD+4 then DWORD+0 are zeroed before RET0.
// Clean BF1 f98983a7d3bb405f1a4ba94bb6a2a168062a819d GameLogic/Object/
// WeaponNuggetParse.cpp, compiled O1/SSE2/G6, supplies Made001E5D60::Tail's
// two-zero expression. Its Tail/WeaponNugget identity and constructor role
// are donor facts only; target owner, field meanings and complete class
// bounds remain unknown. This ordinary method models only the physical
// receiver/return and two raw32 accesses, with no original lifetime claim.
class Rva004DE52CWordPair {
public:
    Rva004DE52CWordPair *clear();
private:
    unsigned int word0;
    unsigned int word4;
};
Rva004DE52CWordPair *Rva004DE52CWordPair::clear() {
    word4 = 0;
    word0 = 0;
    return this;
}

// Whole clean BF1 f98983a7d3bb405f1a4ba94bb6a2a168062a819d WWLib/
// msgloop.cpp supplies AcceleratorTracker's ordered two-zero expression.
// Other donor names emit the same bytes; no tracker identity or constructor
// role is asserted. Native306761..306769 begins after the prior tail-JMP
// wrapper and ends before a distinct global-guarded entry. It clears raw32
// receiver words+0 then+4 and returns RET0 without calls or relocations.
// Original receiver, field meanings and complete layout remain unknown.
class Rva00306761WordPair
{
public:
    void clear();
private:
    unsigned int word0;
    unsigned int word4;
};
void Rva00306761WordPair::clear()
{
    word0 = 0;
    word4 = 0;
}
