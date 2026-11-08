// platformsdk
// Open-BFME5 conversions.

#include <windows.h>
#include <new>

// VA 0x00CE0F20 is the FESL message base table, emitted as BfmeMsgVJH's.
extern "C" char __identifier("??_7BfmeMsgVJH@@6B@");

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
	s->m_bfmeVft = (void **)&__identifier("??_7BfmeMsgVJH@@6B@");
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

class GenAlloc; GenAlloc *Gen007EFFC0();
void bfmeFreeTVC(void *p, int n);


