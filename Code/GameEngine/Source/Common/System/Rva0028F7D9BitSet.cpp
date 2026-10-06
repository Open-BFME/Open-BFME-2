// cl: /DNDEBUG /MD
// ?rva0028F7D9@Rva0028F7D9@@QAE_NPBD@Z @ 0x0028F7D9 47B: set bit from name
// via rowed BitFlags<154>::getSingleBitFromName (0x0028C84F SpecialPower table);
// returns false if bit<0 else sets m_bits[bit>>5] |= 1<<(bit&31) and returns true.
// Caller 0x0029268C. Prev/next own Rva bitset TUs same flags.
template <unsigned NUMBITS>
class BitFlags
{
public:
	static int getSingleBitFromName(const char *token);
};

class Rva0028F7D9
{
public:
	bool rva0028F7D9(const char *name);
private:
	unsigned m_bits[4];
};

bool Rva0028F7D9::rva0028F7D9(const char *name)
{
	int bit = BitFlags<154>::getSingleBitFromName(name);
	if (bit >= 0)
	{
		m_bits[(unsigned)bit >> 5] |= 1u << (bit & 31);
		return true;
	}
	return false;
}
