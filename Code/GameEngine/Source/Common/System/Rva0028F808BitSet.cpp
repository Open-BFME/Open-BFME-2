// cl: /DNDEBUG /MD
// ?rva0028F808@Rva0028F808@@QAEXPAUIface0028F808@@@Z @ 0x0028F808 97B:
// 104-bit (0x68) DWORD bitset to 13-byte (0xD) array then virtual slot 0x24
// (f09) with (buf, 0xD). Zeroes local via CRT memset thunk 0x006291AE,
// tests m_bits[i>>5] & (1<<(i&31)), sets buf[i/8] |= 1<<(i%8) via idiv
// divmod. Caller 0x002914AF. Prev V3Poly neighbours are address-only.
extern "C" void *memset(void *dst, int val, unsigned size);

struct Iface0028F808
{
	virtual void f00();
	virtual void f01();
	virtual void f02();
	virtual void f03();
	virtual void f04();
	virtual void f05();
	virtual void f06();
	virtual void f07();
	virtual void f08();
	virtual void f09(void *buf, int len);
};

class Rva0028F808
{
public:
	void rva0028F808(Iface0028F808 *out);
private:
	unsigned m_bits[19];
};

void Rva0028F808::rva0028F808(Iface0028F808 *out)
{
	unsigned char buf[0x0D];
	memset(buf, 0, 0x0D);
	for (int i = 0; i < 0x68; ++i)
	{
		if (m_bits[(unsigned)i >> 5] & (1u << (i & 31)))
			buf[i / 8] |= (unsigned char)(1 << (i % 8));
	}
	out->f09(buf, 0x0D);
}
