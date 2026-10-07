// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD
//
// ?rva0028F6BC@Rva0028F6BC@@QAE_NPBD@Z @0x0028F6BC 47B:
// set bit from name via rowed BitFlags<11>::getSingleBitFromName (0x0028C7AD);
// returns false if bit<0 else sets m_bits[bit>>5] |= 1<<(bit&31) and returns true.
// Evidence: same 47B shape as sibling Rva0028F733BitSet.cpp at 0x0028F733;
// caller 0x00292502; prev 0x0028F68F abuts at start.

template <unsigned NUMBITS>
class BitFlags
{
public:
	static int getSingleBitFromName(const char *token);
};

class Rva0028F6BC
{
public:
	bool rva0028F6BC(const char *name);
private:
	unsigned m_bits[1];
};

bool Rva0028F6BC::rva0028F6BC(const char *name)
{
	int bit = BitFlags<11>::getSingleBitFromName(name);
	if (bit >= 0)
	{
		m_bits[(unsigned)bit >> 5] |= 1u << (bit & 31);
		return true;
	}
	return false;
}
