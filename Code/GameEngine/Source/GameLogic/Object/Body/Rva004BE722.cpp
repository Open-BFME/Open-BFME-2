// cl: /DNDEBUG /MD
// ?rva004BE722@Rva004BE722@@QAEXPAX@Z @0x004BE722 95B evidence: unlock; bit-copy 21 bits from this dword at +0 via m_bits[i>>5] and 1<<(i&31) into 3-byte memset local via buf[i/8] |= 1<<(i%8) then virtual slot 0x24 on arg with (buf 3); callees rowed memset import 0x006291AE; caller 0x004BE781
#include <string.h>

class Rva004BE722Arg
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void s06();
	virtual void s07();
	virtual void s08();
	virtual void v24(void *buf, int len);
};

class Rva004BE722
{
public:
	void rva004BE722(void *arg);
private:
	unsigned int m_bits[1];
};

void Rva004BE722::rva004BE722(void *arg)
{
	unsigned char buf[3];
	memset(buf, 0, 3);
	for (int i = 0; i < 0x15; ++i)
	{
		if (m_bits[((unsigned int)i >> 5)] & (1u << (i & 31)))
		{
			buf[i / 8] |= (unsigned char)(1 << (i % 8));
		}
	}
	((Rva004BE722Arg *)arg)->v24(buf, 3);
}
