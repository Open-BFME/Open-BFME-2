// cl: /O1 /MD
// Native 00046827..0004686F RET0, a leaf popcount over 32 dwords.
// The mask fold and the unsigned 0..31 loop are native evidence. The
// two nibble temporaries follow the verified 7-word sibling 002AACDB;
// only its independently observed loop limit differs. The owner is open.
class Rva00046827
{
public:
	unsigned m_bits[32];
	int rva00046827();
};

int Rva00046827::rva00046827()
{
	int total = 0;
	for (unsigned i = 0; i < 32; ++i)
	{
		unsigned v = m_bits[i];
		v = v - ((v >> 1) & 0x55555555);
		unsigned orig = v;
		unsigned low = orig & 0x33333333;
		unsigned high = (orig >> 2) & 0x33333333;
		v = high + low;
		v = ((v >> 4) + v) & 0x0F0F0F0F;
		v = (v * 0x01010101) >> 24;
		total += (int)v;
	}
	return total;
}
