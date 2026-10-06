// cl: /Ireference/shims/bfme2_ascii /Oy- /DNDEBUG /MD /GX /Oi-
// ?rva00291679@Rva00291679@@QAEXPAVRva00291679Arg@@@Z
// 0x00291679 97B unlock bitset 101 plus memset 13 plus virt 0x24.
// Evidence: memset rowed 0x006291AE; loop 0x65 with 1<<i test plus idiv 8; virt 0x24 with 13 plus buf;
// caller 0x00292585; prev Rva0029161ABits next AsciiStringRvoGetters.
#include <cstring>

class Rva00291679Arg
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

class Rva00291679
{
public:
	void rva00291679(Rva00291679Arg *arg);
private:
	unsigned int m_bits[8];
};

void Rva00291679::rva00291679(Rva00291679Arg *arg)
{
	unsigned char buf[13];
	memset(buf, 0, 13);
	for (int i = 0; i < 101; ++i) {
		if ((m_bits[(unsigned int)i >> 5] & (1u << (i & 0x1f))) != 0)
			buf[i / 8] |= (unsigned char)(1u << (i % 8));
	}
	arg->v9(buf, 13);
}
