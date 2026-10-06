// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// ?rva002AAD23@Rva002AAD23@@QAE_NPBD@Z @0x002AAD23 47B: BitFlags-style set via getSingleBitFromName then or bit; caller 0x002AC15B; unblocks 0x002AC06A.
template <unsigned int NUMBITS>
class BitFlags
{
public:
	static int getSingleBitFromName(char const* token);
};

int BitFlags<218>::getSingleBitFromName(char const* token);

class Rva002AAD23
{
public:
	bool rva002AAD23(char const* token);
private:
	unsigned long m_bits[8];
};

bool Rva002AAD23::rva002AAD23(char const* token)
{
	int bit = BitFlags<218>::getSingleBitFromName(token);
	if (bit >= 0) {
		m_bits[(unsigned int)bit >> 5] |= 1UL << (bit & 31);
		return true;
	}
	return false;
}
