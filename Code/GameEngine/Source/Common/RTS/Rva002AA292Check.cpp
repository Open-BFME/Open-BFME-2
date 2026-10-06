// cl: /DNDEBUG /MD /EHsc
// ?rva002AA292@Rva002AA292@@QBE_NPBH@Z 0x002AA292 41B
// Checks 32 dwords: (m_bits[i] & mask[i]) == mask[i] for all i.
// Evidence: callers 0x40C739 0x480C2E 0x4B419B etc.; lane unlock.
class Rva002AA292
{
	int m_bits[32];
public:
	bool rva002AA292(const int* mask) const;
};

bool Rva002AA292::rva002AA292(const int* mask) const
{
	for (unsigned i = 0; i < 32; ++i) {
		if ((m_bits[i] & mask[i]) != mask[i])
			return false;
	}
	return true;
}
