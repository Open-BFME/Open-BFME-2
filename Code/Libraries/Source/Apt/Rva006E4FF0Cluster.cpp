// cl: /O2 /MD
//
// Rva006E3230 action-pool neighbours next to Rva006E4D50.cpp. Layout and
// assert triple are shared with Rva006E3230Validate.cpp: pool at +0, current
// at +4, end at +8, size at +0x10, 24-byte action stride.

extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
extern const char g_00BBFDDC[];
void __debugbreak();
#pragma intrinsic(__debugbreak)

void *__cdecl Rva006CD440Alloc(int size);

struct Rva006E3230Action
{
	char data[24];
};

class AptValue
{
public:
	virtual void unused0();
	virtual void unused1();
};

struct Rva006E3230ActionFull
{
	int eActionType;
	char _pad4[8];
	AptValue *m_pValues[3];
};

class Rva006E3230
{
	Rva006E3230Action *m_aActionPool;
	Rva006E3230Action *m_pCurrent;
	Rva006E3230Action *m_pEnd;
	char _padC[4];
	int m_iActionPoolSize;

public:
	void rva006E3230(Rva006E3230Action *pCur);
	void rva006E4A90();
	Rva006E3230 *rva006E4FF0(int nSize);
};

// ?rva006E4FF0@Rva006E3230@@QAEPAU1@H@Z @0x006E4FF0 (86B). Allocates the
// 24-byte-stride action pool for nSize slots, points pool/current/end at it,
// records the size and resets the queue; asserts nSize != 0 at _Apt.h:0x48C.
Rva006E3230 *Rva006E3230::rva006E4FF0(int nSize)
{
	if (nSize == 0)
	{
		g_bfmeAptAssertAtE17734("nSize != 0", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\_Apt.h", 0x48C);
		if (g_bfmeAptBreakOnAssertAtDDC01C)
			__debugbreak();
	}
	m_iActionPoolSize = nSize;
	Rva006E3230Action *pool = (Rva006E3230Action *)Rva006CD440Alloc(nSize * sizeof(Rva006E3230Action));
	m_aActionPool = pool;
	m_pEnd = pool;
	m_pCurrent = pool;
	rva006E4A90();
	return this;
}

struct Rva006E58D0ConstFile
{
	char _pad0[0x1c];
	unsigned int aConstants;
};

class Rva006E58D0
{
	char _pad0[0x30];
	int m_field30;

public:
	void rva006E5050(void *a, void *b, void *c);
	void rva006E58D0Body(void *a, void *b, void *c);
};

// ?rva006E58D0Body@Rva006E58D0@@QAEXPAX00@Z @0x006E58D0 (105B). Fixes up the
// pConstFile->aConstants offset into a pointer, asserts it is below 0xfffff at
// AptAnimation.cpp:0xC3, clears this+0x30 and forwards to rva006E5050, then
// restores the offset. Address-derived name; arg2 is the constant file.
void Rva006E58D0::rva006E58D0Body(void *a, void *b, void *c)
{
	Rva006E58D0ConstFile *pConstFile = (Rva006E58D0ConstFile *)b;
	if (!(pConstFile->aConstants < 0xfffff))
	{
		g_bfmeAptAssertAtE17734("(unsigned)pConstFile->aConstants < 0xfffff", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptAnimation.cpp", 0xC3);
		if (g_bfmeAptBreakOnAssertAtDDC01C)
			__debugbreak();
	}
	if (pConstFile->aConstants != 0)
		pConstFile->aConstants += (unsigned int)pConstFile;
	m_field30 = 0;
	rva006E5050(a, b, c);
	if (pConstFile->aConstants != 0)
		pConstFile->aConstants -= (unsigned int)pConstFile;
}

// ?rva006E4A90@Rva006E3230@@QAEXXZ @0x006E4A90 (239B). Drains the action pool
// from m_pCurrent to m_pEnd: validates the cursor via rowed rva006E3230, then
// per action releases the slot-1 virtual of values[2] (type 1) or values[0]
// and values[1] (type 2), asserting at AptAnimation.cpp:0x62D otherwise;
// clears the type, advances with wrap at pool+size and revalidates the cursor
// with the _Apt.h 0x4E0/0x4E1 asserts, then resets current/end to the pool.
// Layout/stride/virtual shape shared with Rva006E3230Validate.cpp; slot-1
// virtual name unproven so honest unused1. Caller 0x006E503A is rva006E4FF0.
void Rva006E3230::rva006E4A90()
{
	rva006E3230(m_pCurrent);
	Rva006E3230Action *pCur = m_pCurrent;
	if (pCur != m_pEnd)
	{
		do
		{
			Rva006E3230ActionFull *a = (Rva006E3230ActionFull *)pCur;
			int t = a->eActionType;
			if (t == 1)
			{
				a->m_pValues[2]->unused1();
			}
			else if (t == 2)
			{
				a->m_pValues[0]->unused1();
				a->m_pValues[1]->unused1();
			}
			else
			{
				g_bfmeAptAssertAtE17734(g_00BBFDDC, "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptAnimation.cpp", 0x62d);
				if (g_bfmeAptBreakOnAssertAtDDC01C)
					__debugbreak();
			}
			a->eActionType = 0;
			++pCur;
			if (pCur == &m_aActionPool[m_iActionPoolSize])
				pCur = m_aActionPool;
			if (!(pCur >= &m_aActionPool[0]))
			{
				g_bfmeAptAssertAtE17734("pCur >= &m_aActionPool[0]", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\_Apt.h", 0x4e0);
				if (g_bfmeAptBreakOnAssertAtDDC01C)
					__debugbreak();
			}
			if (!(pCur < &m_aActionPool[m_iActionPoolSize]))
			{
				g_bfmeAptAssertAtE17734("pCur < &m_aActionPool[ m_iActionPoolSize ]", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\_Apt.h", 0x4e1);
				if (g_bfmeAptBreakOnAssertAtDDC01C)
					__debugbreak();
			}
		} while (pCur != m_pEnd);
	}
	m_pEnd = m_aActionPool;
	m_pCurrent = m_aActionPool;
}
