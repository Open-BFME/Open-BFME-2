// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva0040C598@Rva0040C598@@QAEXPBH@Z, retail 0x0040C598, 25 bytes.
// Target evidence: leaf bit-AND loop over 32 dwords; 1 caller at 0x0040C85B; no vtable;
// prev ConstIntGetters4 next DispDwordLeaFieldGetters.
class Rva0040C598
{
public:
	void rva0040C598(const int *src);
	void rva0040C5B1(const int *src);

private:
	int m_bits[32];
};

void Rva0040C598::rva0040C598(const int *src)
{
	for (int i = 0; i < 32; ++i)
		m_bits[i] &= src[i];
}

void Rva0040C598::rva0040C5B1(const int *src)
{
	for (int i = 0; i < 32; ++i)
		m_bits[i] &= ~src[i];
}

// Whole clean BF1 f98983a7d3 Common/S1BitwiseAndPrimitives.cpp is the source
// guide. Native2257F2..2257FB follows the complete OR9 leaf2257E9 and ends
// RET before a new prologue. It returns stackword4 AND stackword8 as raw32;
// ECX is unused, and the caller owns stack cleanup. Original owner, declaration
// and signedness remain unknown; this cdecl behavior view asserts no donor name.
unsigned Rva002257F2AndValues(unsigned first, unsigned second) {
    return first & second;
}

// Whole BF1 f98983a7d3 Common/S1BitwiseAndPrimitives.cpp supplies the bit-AND
// expression, with FlagWordOrHelpers.cpp supplying the pointer/value shape.
// Retail005C4B10..005C4B1B independently proves stackword4 points to a raw32
// word ANDed in place with stackword8, then RET0. The adjacent OR11 ends at
// this start; a fresh receiver-vptr initializer follows. Original owner,
// declaration and signedness remain unknown; only raw bits are asserted.
void Rva005C4B10AndInto(unsigned *destination, unsigned mask) {
    *destination &= mask;
}
