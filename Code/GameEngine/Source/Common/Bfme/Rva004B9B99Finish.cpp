// RVA 0x004B9B99  ?bfmeUseFDE@BfmeThingFDE@@QAEXPAX@Z  173 bytes, exact match.
// BFME1 donor body (BfmeConv893.cpp FDE part) adapted to the BFME2 Drawable
// sink; factoring the per-range walk into a __forceinline helper (while form)
// reproduces retail's register allocation. bfmeGoFDE is already landed in
// Code/GameEngine/Source/Common/BfmeConv893.cpp, so it is only declared here.
// ?bfmeUseFDE@BfmeThingFDE@@QAEXPAX@Z
// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /DBFME_MODULE_NO_MPO /MD /EHsc /Ireference/open-bfme-1/reference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
#include "ascii_string.h"

struct BfmeSubFDE
{
	virtual void bfmeV0();
	virtual void bfmeV1();
	virtual void bfmeV2();
	virtual void bfmeV3();
	virtual void bfmeV4();
	virtual void bfmeV5();
	virtual void bfmeV6();
	virtual void bfmeV7();
	virtual void *bfmeVirt8FDE();
};

struct BfmeHeldFDE
{
	unsigned char m_bfmeHead[0x254];
	BfmeSubFDE *m_bfmeS;
};

class Drawable
{
public:
	void rva002724FD(const AsciiString &a, int b, int c, float d, float e);
};

class Thing
{
public:
	Drawable *getDrawable() const;
};

struct BfmeEntry
{
	char m_bfmeFields[4];
};

struct BfmeRangeFDE
{
	BfmeEntry *m_bfmeBegin;
	BfmeEntry *m_bfmeEnd;
	void *m_bfmeUnused;
};

struct BfmeTableFDE
{
	unsigned char m_bfmeHead[0xfd4];
	BfmeRangeFDE m_bfmeFirst[4];
	BfmeRangeFDE m_bfmeSecond[4];
};

struct BfmeThingFDE
{
	void bfmeGoFDE();
	void bfmeUseFDE(void *r);
	unsigned char m_bfmeHead[4];
	BfmeTableFDE *m_bfmeTable;
	BfmeHeldFDE *m_bfmeP;
};

// ?bfmeUseFDE@BfmeThingFDE@@QAEXPAX@Z, retail 0x004B9B99, 173 bytes.
__forceinline void BfmeApplyRangeFDE(Drawable *sink, BfmeEntry *cur, BfmeEntry **end, int kind)
{
	while (cur != *end)
	{
		sink->rva002724FD(*(const AsciiString *)cur, kind, 1, 0.0f, 0.0f);
		++cur;
	}
}

void BfmeThingFDE::bfmeUseFDE(void *r)
{
	int idx = (int)r;
	BfmeHeldFDE *held = m_bfmeP;
	if (held != 0)
	{
		Drawable *sink = ((Thing *)held)->getDrawable();
		if (sink != 0)
		{
			BfmeTableFDE *table = m_bfmeTable;
			BfmeApplyRangeFDE(sink, table->m_bfmeFirst[idx].m_bfmeBegin, &table->m_bfmeFirst[idx].m_bfmeEnd, 0);
			BfmeApplyRangeFDE(sink, table->m_bfmeSecond[idx].m_bfmeBegin, &table->m_bfmeSecond[idx].m_bfmeEnd, 1);
		}
	}
}