// cl: /O2 /MD
// Whole clean BFME 1 donor: game/GameEngine/Source/Common/Bfme/
// Rva009A4E30ConditionalOutput.cpp at 6583b3c1ff21db4a561285717028fdafc780b7db.
// Target boundary: the matched 176-byte initializer at 0x001B5840 ends with
// RET at 0x001B58EF. This 25-byte entry starts at 0x001B58F0 and ends with
// RET at 0x001B5908, followed by seven CC bytes before the next entry.
// No Ghidra entry or entry references were observed. Native cdecl arguments
// are source, a full-word flag, and output. A zero flag copies source+0x1A0
// to output; a nonzero flag leaves output untouched. There are no callees.
// Donor source uses signed int for value and output. Original owner, field
// type, flag meaning, and signedness are unproven. Unsigned words below
// represent the observed four-byte raw copy rather than a recovered type.
struct Rva001B58F0Source {
    char m_unmodelled[0x1a0];
    unsigned int m_word1a0;
};

void __cdecl rva001B58F0ConditionalOutput(const Rva001B58F0Source *source,
    unsigned int suppress, unsigned int *output) {
    if (suppress == 0)
        *output = source->m_word1a0;
}
