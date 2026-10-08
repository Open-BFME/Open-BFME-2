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
