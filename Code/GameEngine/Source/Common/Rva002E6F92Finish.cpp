// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva002E6F92@Rva002E6F92@@QAEHHPAUIn002E6F92@@HH@Z, retail 0x002E6F92, 77 bytes.
// Float select on low nibble at input +0x0C: 7/1 scales two ints by 10 to
// +0x00/+0x04 with zero at +0x08 else byte 1 at +0x0C; first int arg unused
// per ret 0x10. Caller at 0x002E840D.
//
// The two scaled floats are held in one temporary aggregate before the stores:
// that is what keeps both conversions in xmm0/xmm1 (retail converts the second
// to xmm1 and stores afterwards) instead of storing the first to free xmm0.
struct In002E6F92
{
	char m_pad[0x0C];
	int m_bits;
};

class Rva002E6F92
{
public:
	int rva002E6F92(int unused, In002E6F92 *in, int a, int b);

private:
	float m_00;
	float m_04;
	float m_08;
	unsigned char m_0C;
};

int Rva002E6F92::rva002E6F92(int unused, In002E6F92 *in, int a, int b)
{
	(void)unused;
	int bits = in->m_bits & 0xF;
	if (bits == 7 || bits == 1) {
		struct TwoFloats { float a, b; };
		TwoFloats t;
		t.a = (float)(a * 10);
		t.b = (float)(b * 10);
		m_00 = t.a;
		m_04 = t.b;
		m_08 = 0.0f;
		return 0;
	}
	if (bits == 0)
		m_0C = 1;
	return 1;
}
