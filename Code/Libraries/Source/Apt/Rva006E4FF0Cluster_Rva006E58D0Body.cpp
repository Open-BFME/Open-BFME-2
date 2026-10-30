// cl: /O2 /MD
// Split from Rva006E4FF0Cluster.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
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

class AptActionQueueC
{
	Rva006E3230Action *m_aActionPool;
	Rva006E3230Action *m_pCurrent;
	Rva006E3230Action *m_pEnd;
	char _padC[4];
	int m_iActionPoolSize;

public:
	void rva006E3230(Rva006E3230Action *pCur);
	void ClearActions();
	AptActionQueueC(int nSize);
};


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
	void rva006E58D0Body(void *a, void *constFile, void *c);
};

// ?rva006E58D0Body@Rva006E58D0@@QAEXPAX00@Z @0x006E58D0 (105B). Fixes up the
// pConstFile->aConstants offset into a pointer, asserts it is below 0xfffff at
// AptAnimation.cpp:0xC3, clears this+0x30 and forwards to rva006E5050, then
// restores the offset. Address-derived name; arg2 is the constant file.
void Rva006E58D0::rva006E58D0Body(void *a, void *constFile, void *c)
{
	Rva006E58D0ConstFile *pConstFile = (Rva006E58D0ConstFile *)constFile;
	if (!(pConstFile->aConstants < 0xfffff))
	{
		g_bfmeAptAssertAtE17734("(unsigned)pConstFile->aConstants < 0xfffff", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptAnimation.cpp", 0xC3);
		if (g_bfmeAptBreakOnAssertAtDDC01C)
			__debugbreak();
	}
	if (pConstFile->aConstants != 0)
		pConstFile->aConstants += (unsigned int)pConstFile;
	m_field30 = 0;
	rva006E5050(a, constFile, c);
	if (pConstFile->aConstants != 0)
		pConstFile->aConstants -= (unsigned int)pConstFile;
}

