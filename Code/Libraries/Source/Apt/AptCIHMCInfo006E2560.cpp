// cl: /O2 /MD
// ?rva006E2560@AptCIH@@QAEXH@Z @0x006E2560 224B (includes jump table)
// Chain from 0x006CFCD0: AptCIH type-dispatch counter plus sprite tail.
// Evidence: pMCInfo assert line 0x931 via AptCIH.cpp string; type via rowed
// get 0x006DBB30 minus 0x0C with 7-way jump table; button case 0x0E calls rowed
// 0x006E1090 then rowed 0x006F7AF0; tail calls rowed isSpriteInstBase 0x006CFCD0
// twice with 0x7D AptCIH.h assert then rowed 0x006F7AF0 via +0x4C/+0x24.
// Caller 0x006F7B03. Prev/next Apt TUs use /O2 /MD.
// Retail table at RVA 0x006E2624 maps kinds 0x0C..0x12 to counter offsets
// 0x18, 0x04, 0x08, 0x10, 0x0C, 0x14, 0x00 respectively. These offsets
// are target evidence; the counters' semantic names remain unknown.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)

class Rva006DBB30SarDwordField
{
public:
	int get() const;
};

class Rva006CFCD0
{
public:
	bool isSpriteInstBase() const;
};

class Rva006F7AC0List
{
public:
	void rva006F7AF0(int arg);
};

struct AptMCInfo
{
	int m00;
	int m04;
	int m08;
	int m0c;
	int m10;
	int m14;
	int m18;
};

struct AptButtonPayload
{
	char m_pad[0x1c];
	Rva006F7AC0List *m_list;
};

struct AptTailBlock
{
	char m_pad[0x24];
	Rva006F7AC0List *m_list;
};

class AptCIH
{
public:
	virtual void vtableSlot0();
	void *rva006E1090() const;
	void rva006E2560(int arg);

private:
	unsigned char m_pad40[0x40];
	void *m_44;
	AptCIH *m_parent;
	void *m_4C;
	unsigned char m_pad2[8];
	int m_code;
};

void AptCIH::rva006E2560(int pMCInfoArg)
{
	AptMCInfo *pMCInfo = (AptMCInfo *)pMCInfoArg;
	if (pMCInfo == 0)
	{
		g_bfmeAptAssertAtE17734("pMCInfo", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptCIH.cpp", 0x931);
		if (g_bfmeAptBreakOnAssertAtDDC01C)
			__debugbreak();
	}
	int kind = ((const Rva006DBB30SarDwordField *)this)->get();
	switch (kind - 0x0c)
	{
	case 0:
		pMCInfo->m18++;
		break;
	case 1:
		pMCInfo->m04++;
		break;
	case 2:
		pMCInfo->m08++;
		{
			void *btn = rva006E1090();
			Rva006F7AC0List **ppList = (Rva006F7AC0List **)((char *)btn + 0x1c);
			(*ppList)->rva006F7AF0(pMCInfoArg);
		}
		break;
	case 3:
		pMCInfo->m10++;
		break;
	case 4:
		pMCInfo->m0c++;
		break;
	case 5:
		pMCInfo->m14++;
		break;
	case 6:
		pMCInfo->m00++;
		break;
	default:
		break;
	}
	if (((const Rva006CFCD0 *)this)->isSpriteInstBase())
	{
		if (!((const Rva006CFCD0 *)this)->isSpriteInstBase())
		{
			g_bfmeAptAssertAtE17734("isSpriteInstBase()", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h", 0x7d);
			if (g_bfmeAptBreakOnAssertAtDDC01C)
				__debugbreak();
		}
		((AptTailBlock *)m_4C)->m_list->rva006F7AF0(pMCInfoArg);
	}
}
