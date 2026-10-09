// Disp0 dword OR setters: four-byte __thiscall members with one shape:
//
//     or dword ptr [ecx],<IMM8> / ret      (83 09 FF C3)
//
// The dword at `this` itself is ORed in place with a sign-extended byte
// immediate and nothing is read back. The zero-displacement member of an
// OR family: MSVC 7.1 uses the [ecx]-without-displacement form when the
// offset is zero, so there is no lead array. Only the class names follow
// this tree's Disp* convention (address-derived Rva<addr>DwordOrSetter,
// identity unrecoverable from 4 bytes). Retail cleans none (`ret`, not
// `ret 4`), so the members take no parameters.
// cl: (at defaults MSVC 7.1 folds `x |= -1` into `mov [ecx],-1`;
// /O1 keeps the read-modify-write OR form, as in Disp8DwordClearers.cpp).
class Rva002620FADwordOrSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva002620FADwordOrSetter::apply()
{
	m_value |= -1;
}

// BFME1 9cbfb551 Object.cpp emits _Base_bitset<1>::_M_do_or.
// Native 3FA381..3FA38C is the complete ret4 leaf immediately after ret4
// at 3FA37E; it ORs the receiver word with the pointed-to argument word.
// Neither the donor template spelling nor its owner is claimed as target fact.
class Rva003FA381WordMask
{
public:
    void combine(const unsigned int *other);
    unsigned int m_word;
};
void Rva003FA381WordMask::combine(const unsigned int *other)
{
    m_word |= *other;
}

// Whole clean BF1 f98983a7 Common/Bfme/Rva000B5E90_orValues.cpp is
// the source lead. Native2257E9..2257F2/9 follows a complete RET4 and
// endsRET immediately before a separate AND leaf. It returns the raw32-bit
// OR of stack arguments4/8; ECX is unused and the caller cleans the stack.
// Eight-section direct scans found no call; the sole raw VA occurrence at
// 6429F0 is a JMP encoding, not a pointer witness. Original owner and whether
// its original declaration was free or a member remain unknown. This ordinary
// cdecl behavior view claims only the independently bounded argument/result.
unsigned Rva002257E9OrValues(unsigned first, unsigned second) {
    return first | second;
}

// Whole clean BF1 f98983a7 Common/Rva00694BB0Or.cpp supplies this source
// lead. Native50E45..50E52/13 followsRET8 and endsRET before a new prologue.
// It reads sourceword0 through stack8 then ORs destinationword0 through
// stack4. ECX is a temporary and stack cleanup is the caller's. Eight-section
// direct/address scans found no witnesses. Original owner and declaration's
// return type remain unknown; donor's void cdecl behavior view asserts the
// raw32-bit read/modify/write only, without a name or payload interpretation.
void Rva00050E45OrInto(unsigned *destination, const unsigned *source) {
    *destination |= *source;
}
