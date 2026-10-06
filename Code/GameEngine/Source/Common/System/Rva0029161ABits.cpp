// cl: /Ireference/shims/bfme2_ascii /Oy- /DNDEBUG /MD /GX /Oi-
// ?rva0029161A@Rva0029161A@@QAEX PAV Rva0029161AArg@@@Z placehold
// 0x0029161A 95B unlock bitset 11 plus memset 2 plus virt 0x24.
// Evidence: memset rowed 0x006291AE; loop 0xB with 1<<i test plus idiv 8; virt 0x24 with 2 plus buf;
// caller 0x00292449; prev stlport_construct next AsciiStringRvoGetters.
#include <cstring>

class Rva0029161AArg
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void v6();
	virtual void v7();
	virtual void v8();
	virtual void v9(void *b, int a);
};

class Rva0029161A
{
public:
	void rva0029161A(Rva0029161AArg *arg);
private:
	unsigned int m_bits[8];
};

void Rva0029161A::rva0029161A(Rva0029161AArg *arg)
{
	unsigned char buf[2];
	memset(buf, 0, 2);
	for (int i = 0; i < 11; ++i) {
		if ((m_bits[(unsigned int)i >> 5] & (1u << (i & 0x1f))) != 0)
			buf[i / 8] |= (unsigned char)(1u << (i % 8));
	}
	arg->v9(buf, 2);
}
