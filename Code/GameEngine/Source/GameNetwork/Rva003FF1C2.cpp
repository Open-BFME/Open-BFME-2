// cl: /DNDEBUG /MD /EHsc
// ?rva003FF1C2@Rva003FF1C2@@QBE_NXZ @0x003FF1C2 (24B):
// Honest-address predicate: 16B nonzero check at +0xCC (xor/inc/cmp/jl loop,
// true on first nonzero, false after 0x10). Owner unproven; five callers.
// No callees, no pins.

typedef int Int;
typedef bool Bool;

class Rva003FF1C2
{
public:
	Bool rva003FF1C2() const;

private:
	char m_pad[0xCC];
	unsigned char m_data[0x10];
};

Bool Rva003FF1C2::rva003FF1C2() const
{
	for (Int i = 0; i < 0x10; ++i)
	{
		if (m_data[i] != 0)
			return true;
	}
	return false;
}
