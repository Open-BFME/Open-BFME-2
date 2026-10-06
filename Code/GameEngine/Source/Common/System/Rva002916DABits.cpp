// cl: /Ireference/shims/bfme2_ascii /Oy- /DNDEBUG /MD /GX /Oi-
// ?rva002916DA@Rva002916DA@@QAEXPAVRva002916DAArg@@@Z
// 0x002916DA 100B unlock bitset 154 plus memset 20 plus virt 0x24.
// Evidence: memset rowed 0x006291AE; loop 0x9A with 1<<i test plus idiv 8; virt 0x24 with 20 plus buf;
// caller 0x002926C1; prev Rva00291679Bits next AsciiStringRvoGetters.
#include <cstring>

class Rva002916DAArg
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

class Rva002916DA
{
public:
	void rva002916DA(Rva002916DAArg *arg);
private:
	unsigned int m_bits[8];
};

void Rva002916DA::rva002916DA(Rva002916DAArg *arg)
{
	unsigned char buf[20];
	memset(buf, 0, 20);
	for (int i = 0; i < 154; ++i) {
		if ((m_bits[(unsigned int)i >> 5] & (1u << (i & 0x1f))) != 0)
			buf[i / 8] |= (unsigned char)(1u << (i % 8));
	}
	arg->v9(buf, 20);
}
