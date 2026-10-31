// platformsdk
// Open-BFME5 conversions.

#include <windows.h>
#include <new>

extern void *g_bfmeVftTUA[];

class BfmeSubTUA
{
public:
	void bfmeInitTUA();
	void *m_bfmeVft;
	int m_bfme04;
	int m_bfme08;
	int m_bfme0c;
};

class BfmeThingTUA
{
public:
	BfmeThingTUA();
	int m_bfme00;
	int m_bfme04;
	char m_bfme08;
	char m_bfmePad[3];
	int m_bfme0c;
	BfmeSubTUA m_bfmeSub;
	int m_bfme20;
};

BfmeThingTUA::BfmeThingTUA()
{
	BfmeSubTUA *s = &m_bfmeSub;
	s->bfmeInitTUA();
	s->m_bfme08 = 0;
	s->m_bfme0c = 0;
	s->m_bfme04 = 0;
	s->m_bfmeVft = g_bfmeVftTUA;
	m_bfme00 = 0;
	m_bfme04 = 0;
	m_bfme0c = 0;
	m_bfme20 = 0;
	m_bfme08 = 0;
}

extern "C" void *__identifier("??_7Rva00CE12FCMutex@@6B@")[];

// BFME2 releases the TVA handle with CloseHandle (kernel32 slot 0xBBA180)
// and frees the vector with scalar operator delete (0x2FD60), where BFME1
// calls its own release/free helpers.
// The rowed base cleanup restores the base vtable at retail 0x65D180.
class Rva00CE1E14Base { public: virtual ~Rva00CE1E14Base(); };

class BfmeThingTVA
{
public:
	void *bfmeDelTVA(unsigned char flags);
	void bfmeDtorTVA();
	void *m_bfmeVft;
	HANDLE m_handle;
};

void *BfmeThingTVA::bfmeDelTVA(unsigned char flags)
{
	HANDLE h = m_handle;
	m_bfmeVft = __identifier("??_7Rva00CE12FCMutex@@6B@");
	if (h)
		CloseHandle(h);
	reinterpret_cast<Rva00CE1E14Base *>(this)->Rva00CE1E14Base::~Rva00CE1E14Base();
	if (flags & 1)
		operator delete(this);
	return this;
}

// BFME2 frees the TVB object string with SysFreeString (oleaut32 slot
// 0xBBA78C), the buffer with array delete (0x2FD80) and the vector with
// scalar delete (0x2FD60).
class BfmeThingTVB
{
public:
	void *bfmeDelTVB(unsigned char flags);
	BSTR m_bfmeObj;
	void *m_buffer;
};

void *BfmeThingTVB::bfmeDelTVB(unsigned char flags)
{
	if (m_bfmeObj)
		SysFreeString(m_bfmeObj);
	if (m_buffer)
		operator delete[](m_buffer);
	if (flags & 1)
		operator delete(this);
	return this;
}

class BfmeSinkTVC
{
public:
	virtual void bfmeV0TVC() = 0;
	virtual void bfmeV1TVC() = 0;
	virtual void bfmeV2TVC() = 0;
	virtual void bfmeDropTVC(void *p, int f) = 0;
};

class GenAlloc; GenAlloc *Gen007EFFC0();
void bfmeFreeTVC(void *p, int n);

class BfmeThingTVC
{
public:
	void *bfmeDelTVC(unsigned char flags);
	int m_bfme00;
	int m_bfme04;
	void *m_bfmeItem;
};

void *BfmeThingTVC::bfmeDelTVC(unsigned char flags)
{
	((BfmeSinkTVC *)Gen007EFFC0())->bfmeDropTVC(m_bfmeItem, 1);
	m_bfme04 = 0;
	m_bfme00 = 0;
	m_bfmeItem = 0;
	if (flags & 1)
		bfmeFreeTVC(this, 0xc);
	return this;
}
// ?g_bfmeVftTUA@@3PAPAXA: the global at VA 0xce0f20 is ?vftable_011296B0@@3HA.
#pragma comment(linker, "/alternatename:?g_bfmeVftTUA@@3PAPAXA=?vftable_011296B0@@3HA")

