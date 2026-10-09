// Disp8 dword immediate setters: eight-byte __thiscall members with one shape:
//
//     mov dword ptr [ecx+<DISP>],<IMM32> / ret
//
// One dword at a fixed disp8 displacement from `this` is set to a hardcoded
// immediate and nothing is read back. The disp8 mirror of the disp32 family
// (DispDwordImmSetters.cpp); MSVC 7.1 uses the C7-41 form whenever the offset
// fits in a signed byte, so every offset here is below 0x80. Only the class
// names follow this tree's Disp* convention (address-derived
// Rva<addr>DwordImmSetter, identity unrecoverable from 8 bytes). Retail
// cleans none (`ret`, not `ret 4`), so the members take no parameters.
// No // cl: line (defaults match the frameless 8-byte shape).
class Rva00050CEFDwordImmSetter
{
public:
	void apply();

	char m_lead[0x38];
	unsigned int m_value;
};

void Rva00050CEFDwordImmSetter::apply()
{
	m_value = 6;
}

class Rva002E066DDwordImmSetter
{
public:
	void apply();

	char m_lead[0x44];
	unsigned int m_value;
};

void Rva002E066DDwordImmSetter::apply()
{
	m_value = 1;
}

class Rva002E0675DwordImmSetter
{
public:
	void apply();

	char m_lead[0x44];
	unsigned int m_value;
};

void Rva002E0675DwordImmSetter::apply()
{
	m_value = 2;
}

class Rva00395583DwordImmSetter
{
public:
	void apply();

	char m_lead[0x34];
	unsigned int m_value;
};

void Rva00395583DwordImmSetter::apply()
{
	m_value = 4;
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?state1@Rva002E2903Player@@QAEXXZ=?apply@Rva002E066DDwordImmSetter@@QAEXXZ")
#pragma comment(linker, "/alternatename:?state2@Rva002E2903Player@@QAEXXZ=?apply@Rva002E0675DwordImmSetter@@QAEXXZ")

// Whole clean BF1 f98983a7 Player.cpp supplies a SpecialPowerReadyTimerType
// clear source lead via the actual shims/player/Common/Player.h definition.
// Its timer/template meanings are donor facts. Native2A9871..2A9879/8
// follows a complete RET4 and endsRET before the next leaf: word4 becomes
// allones then word0 becomes zero. Eight-section call/address scans found
// no entry witness. Original owner and full object size remain unknown; this
// independent raw two-word accessed-prefix reset uses unchanged homeflags.
struct Rva002A9871Pair
{
    unsigned word0, word4;
    void reset();
};
void Rva002A9871Pair::reset()
{
    word4 = ~0u;
    word0 = 0;
}