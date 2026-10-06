// flags: region default (reverse/retail_inventory/flag_regions.csv)
// Disp8 dword OR setters: five-byte __thiscall members with one shape:
//
//     or dword ptr [ecx+<DISP>],<IMM8> / ret   (83 49 XX YY C3)
//
// A dword at a fixed disp8 displacement from `this` is ORed in place with a
// sign-extended byte immediate and nothing is read back. The disp8 member of
// the OR family (see Disp0DwordOrSetters.cpp for the zero-displacement form
// and Disp8DwordClearers.cpp for the AND-mask sibling under the same /O1).
// Only the class names follow this tree's Disp* convention (address-derived
// Rva<addr>DwordOrSetter, identity unrecoverable from 5 bytes). Retail
// cleans none (`ret`, not `ret 4`), so the members take no parameters.
//
// ?apply@Rva006DBDB0DwordOrSetter@@QAEXXZ, retail 0x006DBDB0, 5 bytes.
// Evidence: LINK BONUS unblocks 6 callers (0x006D8520 0x006D88C0 0x006D8700
// 0x006D7090 0x006D7210 0x006E2690); neighbours are disp8 bitfield
// getters/clearers at +4 (Rva006DBDA0ShrNAndField Disp8ShrAndDwordGetters.cpp
// and Rva006DBDC0DwordMask Disp8DwordClearers.cpp); AptValue bitfield cluster.
class Rva006DBDB0DwordOrSetter
{
public:
	void apply();

	char m_lead[0x04];
	unsigned int m_value;
};

void Rva006DBDB0DwordOrSetter::apply()
{
	m_value |= 4;
}
