// cl: /O2 /MD
// Reference: Open-BFME-1@6583b3c1ff21db4a561285717028fdafc780b7db,
// game/Libraries/Source/Lua/Rva00997C60Truthy.cpp (whole one-body donor).
// Target 0x0074EDC0 is a complete 25-byte entry: RET/int3 before its aligned
// start, and final RET/int3 before the next aligned prologue. ECX supplies
// the receiver; the body has no stacked arguments or external dependencies.
// Native facts: word+0 is tested against 1 and 6; tag1 returns 0, tag6 returns
// word+8 unchanged, and other tags return 1. This view asserts those accesses,
// not a complete object size. Signed int spelling is carried from the donor.
// No direct/absolute entry references or named export were observed. The Lua
// role, original TObject identity and method name remain donor inferences.
class Rva0074EDC0TaggedValueView {
public:
    int tag;
    unsigned char unobserved4[4];
    int payload;
    int truthWord() const;
};

int Rva0074EDC0TaggedValueView::truthWord() const
{
    if (tag == 1)
        return 0;
    if (tag == 6)
        return payload;
    return 1;
}
