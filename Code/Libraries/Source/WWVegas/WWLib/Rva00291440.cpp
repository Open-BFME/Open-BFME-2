// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?rva00291440@Rva00291440@@QAEXPAVSink00291440@@@Z
// 0x00291440 111B leaf dword-bitset to byte-bitset plus virtual sink.
// Evidence: memset 0x80 via ji_006291AE; loop 0x400 test [this+idx>>5] bit 1<<(i&31); set buf[i/8] bit 1<<(i%8) via idiv; virtual [eax+0x24] with buf 0x80; callers 0x002977F8 0x004846BC; prev stlport_pod_list next stlport_copy.
#pragma function(memset)
extern "C" void *memset(void *dst, int value, unsigned int size);

class Sink00291440
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
	virtual void v9(unsigned char *buf, int len);
};

class Rva00291440
{
public:
	void rva00291440(Sink00291440 *sink);
private:
	unsigned int m_bits[32];
};

void Rva00291440::rva00291440(Sink00291440 *sink)
{
	unsigned char buf[0x80];
	memset(buf, 0, 0x80);
	for (int i = 0; i < 0x400; ++i) {
		if (m_bits[(unsigned)i >> 5] & (1u << (i & 31)))
			buf[i / 8] |= (unsigned char)(1u << (i % 8));
	}
	sink->v9(buf, 0x80);
}
