// cl: /O2 /MD
//
// AptActionQueueC action-pool neighbours next to Rva006E4D50.cpp. Layout and
// assert triple are shared with Rva006E3230Validate.cpp: pool at +0, current
// at +4, end at +8, size at +0x10, 24-byte action stride.

extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)

void *__cdecl Rva006CD440Alloc(int size);

struct Rva006E3230Action
{
	char data[24];
};

#include "AptValue.h"

struct Rva006E3230ActionFull
{
	int eActionType;
	char _pad4[8];
	AptValue *m_pValues[3];
};

#include "AptActionQueueC.h"

// Native6E6060 new-expression allocates20 bytes and invokes this86B ctor.
// The former return-this initializer body stays exact with the honest ctor ABI.
// AptActionQueueC ctor @0x006E4FF0 (86B). Allocates the
// 24-byte-stride action pool for nSize slots, points pool/current/end at it,
// records the size and resets the queue; asserts nSize != 0 at _Apt.h:0x48C.
AptActionQueueC::AptActionQueueC(int nSize)
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
	ClearActions();
}

// AptActionQueueC::ClearActions (WorldBuilder name, its __FUNCTION__ string) @0x006E4A90 (239B). Drains the action pool
// from m_pCurrent to m_pEnd: validates the cursor via rowed rva006E3230, then
// per action calls AptValue::Release of values[2] (type 1) or values[0]
// and values[1] (type 2), asserting at AptAnimation.cpp:0x62D otherwise;
// clears the type, advances with wrap at pool+size and revalidates the cursor
// with the _Apt.h 0x4E0/0x4E1 asserts, then resets current/end to the pool.
// Layout/stride/virtual shape shared with Rva006E3230Validate.cpp; slot 1
// is AptValue::Release (rowed 0x006DCB20). Caller 0x006E503A is this constructor.
void AptActionQueueC::ClearActions()
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
				a->m_pValues[2]->Release();
			}
			else if (t == 2)
			{
				a->m_pValues[0]->Release();
				a->m_pValues[1]->Release();
			}
			else
			{
				g_bfmeAptAssertAtE17734("0", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptAnimation.cpp", 0x62d);
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
