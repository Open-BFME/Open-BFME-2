// cl: /DNDEBUG /MD
// ?rva0028F762@Rva0028F762@@QAE_NPBD@Z @ 0x0028F762 47B: twin of 0x0028F733
// (same shape); set bit from name via rowed BitFlags<101>::getSingleBitFromName
// (0x0028C819 BodyState table); returns false if bit<0 else sets
// m_bits[bit>>5] |= 1<<(bit&31) and returns true. Caller 0x0029263E.
// Prev/next own bitset TUs same flags.
template <unsigned NUMBITS>
class BitFlags
{
public:
	static int getSingleBitFromName(const char *token);
};

class Rva0028F762
{
public:
	bool rva0028F762(const char *name);
private:
	unsigned m_bits[4];
};

bool Rva0028F762::rva0028F762(const char *name)
{
	int bit = BitFlags<101>::getSingleBitFromName(name);
	if (bit >= 0)
	{
		m_bits[(unsigned)bit >> 5] |= 1u << (bit & 31);
		return true;
	}
	return false;
}
