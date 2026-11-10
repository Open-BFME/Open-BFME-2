// cl: /DNDEBUG /MD
// ?rva0028F733@Rva0028F733@@QAE_NPBD@Z @ 0x0028F733 47B: set bit from name
// via rowed BitFlags<104>::getSingleBitFromName (0x0028C7E3); returns false
// if bit<0 else sets m_bits[bit>>5] |= 1<<(bit&31) and returns true.
// Caller 0x0029159D. Next is own Rva0028F808 bitset same flags.
#include "../../../Include/Common/BitFlagsTemplate.h"

class Rva0028F733
{
public:
	bool rva0028F733(const char *name);
private:
	unsigned m_bits[4];
};

bool Rva0028F733::rva0028F733(const char *name)
{
	int bit = BitFlags<104>::getSingleBitFromName(name);
	if (bit >= 0)
	{
		m_bits[(unsigned)bit >> 5] |= 1u << (bit & 31);
		return true;
	}
	return false;
}
