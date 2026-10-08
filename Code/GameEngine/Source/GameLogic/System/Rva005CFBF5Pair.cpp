// cl: /MD /DNDEBUG /EHsc
// ?rva005CFBF5@@YAXPAURva005CFBF5Pair@@HF@Z @0x005CFBF5 29B: store the int into the pair's first word
// and the 16-bit value, widened through a 4-byte temporary, into the second word.
struct Rva005CFBF5Pair
{
	int m_00;
	int m_04;
};

union Rva005CFBF5Word
{
	int m_i;
	short m_s;
};

// ?rva005CFBF5@@YAXPAURva005CFBF5Pair@@HF@Z @0x005CFBF5
void __cdecl rva005CFBF5(Rva005CFBF5Pair *out, int a, short b)
{
	struct Frame
	{
		int m_pad;
		Rva005CFBF5Word word;
	} frame;
	frame.word.m_s = b;
	out->m_00 = a;
	out->m_04 = frame.word.m_i;
}
