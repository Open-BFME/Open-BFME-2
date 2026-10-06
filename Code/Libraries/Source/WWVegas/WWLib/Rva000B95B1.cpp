// cl: /Ireference/shims/bfme2_ascii /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// ?rva000B95B1@Rva000B95B1@@QAEXPAX@Z 0x000B95B1 100B
// Evidence: unlock lane; contiguous after 0x000B9596; bitfield loop 0x24F over dword array at this, byte buf[74] via idiv /8 %8, then vcall slot 0x24 with (buf, 0x4A); caller 0x000BB710 unclaimed.

void *__cdecl ji_006291ae(void *dest, int val, unsigned int count);
#pragma comment(linker, "/alternatename:?ji_006291ae@@YAPAXPAXHI@Z=?ji_006291ae@@YAXXZ")

struct Rva000B95B1Slot
{
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void v6();
	virtual void v7();
	virtual void v8();
	virtual void apply(unsigned char *buf, int len);
};

class Rva000B95B1
{
public:
	void rva000B95B1(void *arg);
private:
	unsigned int m_bits[19];
};

void Rva000B95B1::rva000B95B1(void *arg)
{
	unsigned char buf[74];
	ji_006291ae(buf, 0, 0x4a);
	for (int i = 0; i < 0x24f; ++i)
	{
		if (m_bits[((unsigned int)i >> 5)] & (1 << (i & 31)))
			buf[i / 8] |= (unsigned char)(1 << (i % 8));
	}
	((Rva000B95B1Slot *)arg)->apply(buf, 0x4a);
}
