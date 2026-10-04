// cl: /O1 /MD
// ?rva005C87F8@Rva005C87F8@@QAEX_N@Z @0x005C87F8 85B
// __thiscall bool method: adjusts the low nibble at +0x47 of each non-null
// child in the 8-pointer array at +0xc and then its own +0x47, by +1 when the
// flag is set else -1, with the high nibble preserved. Caller 0x005C8F3B
// passes literal 0 and clears neighbouring byte +0x46 after. The nibble add
// compiles to the xor-and-xor size form. The barrier keeps the second *p
// read (shape-lever guide: member read retail performs twice).
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class Rva005C87F8
{
public:
	void rva005C87F8(bool flag);
	void rva005C879E(Rva005C87F8 **src);
	void rva005C87DB(unsigned short val);
private:
	char m_pad00[0x0c];
	Rva005C87F8 *m_kids[8]; // +0x0c
	char m_pad2c[0x18]; // +0x2c..0x43
	unsigned short m_44; // +0x44
	unsigned char m_pad46; // +0x46
	unsigned char m_47; // +0x47
};

void Rva005C87F8::rva005C87F8(bool flag)
{
	Rva005C87F8 **p = m_kids;
	signed char d = flag ? 1 : -1;
	int n = 8;
	do {
		if (*p != 0) {
			_ReadWriteBarrier();
			Rva005C87F8 *k = *p;
			k->m_47 = ((k->m_47 & 0xf0) | ((k->m_47 + d) & 0x0f));
		}
		++p;
	} while (--n != 0);
	m_47 = ((m_47 & 0xf0) | ((m_47 + d) & 0x0f));
}

void Rva005C87F8::rva005C879E(Rva005C87F8 **src)
{
	m_47 &= 0x0f;
	for (int i = 0; i < 8; ++i) {
		if (src[i] == 0) {
			unsigned char cur = m_47;
			unsigned char hi = (unsigned char)((cur & 0xf0) + 0x10);
			unsigned char lo = (unsigned char)(cur & 0x0f);
			m_47 = (unsigned char)(hi ^ lo);
		}
		m_kids[i] = src[i];
	}
}

void Rva005C87F8::rva005C87DB(unsigned short val)
{
	unsigned short old = m_44;
	if (old < val)
		m_44 = 0;
	else
		m_44 = (unsigned short)(old - val);
}
