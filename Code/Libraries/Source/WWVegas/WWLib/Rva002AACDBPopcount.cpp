// cl: /Ireference/shims/bfmelist /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?rva002AACDB@Rva002AACDB@@QAEHXZ @0x002AACDB 72B: popcount of 7 dwords via SWAR. Evidence: retail constants 0x33333333 0x55555555 0x0F0F0F0F 0x01010101; loop edi 0-6 jb; caller 0x002AC06A.
class Rva002AACDB
{
public:
	unsigned m_bits[7];
	int rva002AACDB();
};

int Rva002AACDB::rva002AACDB()
{
	int total = 0;
	for (unsigned i = 0; i < 7; ++i)
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
