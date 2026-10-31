// Open-BFME5 conversions.

#include <string.h>
#pragma intrinsic(memset)

struct BfmeRecVFA
{
	int m_bfme00;
	int m_bfme04;
	int m_bfme08;
	int m_bfme0c;
};

int bfmeSendVFA(void *h, int a, int b, int c, int d);

class BfmeThingVFA
{
public:
	int bfmeGoVFA(BfmeRecVFA *r);
	char m_bfmePad[8];
	void *m_handle;
	char m_bfmePad2[4];
	char m_ready;
};

int BfmeThingVFA::bfmeGoVFA(BfmeRecVFA *r)
{
	if (!m_ready)
		return 0xffffff33;
	return bfmeSendVFA(m_handle, r->m_bfme00, r->m_bfme04, r->m_bfme08, r->m_bfme0c);
}

class BfmeBufVFD
{
public:
	void bfmeAppendVFD(const char *s);
	char m_bfmePad[8];
};

struct BfmeThingVFD
{
	char m_bfmePad[8];
	int m_bfme08;
	int m_bfme0c;
	int m_bfme10;
	char m_bfme14;
	char m_bfmePad2[3];
	int m_bfme18;
	BfmeBufVFD m_bfmeBuf;
	int m_bfme24;
	int m_bfme28;
	char m_bfmePad3[0x40];
	char m_bfme6c;
};

void __stdcall bfmeGoVFD(BfmeThingVFD *p)
{
	p->m_bfme08 = 0;
	p->m_bfme0c = 0;
	p->m_bfme10 = 0;
	p->m_bfme14 = 0;
	p->m_bfme18 = 0;
	p->m_bfmeBuf.bfmeAppendVFD((char *)"");
	p->m_bfme24 = 0;
	p->m_bfme28 = 0;
	p->m_bfme6c = 0;
}
