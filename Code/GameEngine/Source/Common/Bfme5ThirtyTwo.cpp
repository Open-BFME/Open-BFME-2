// A bounded element read, a colour built from a flag, and a constructor.
//
// BFME1 byte-identical donor (reference/open-bfme-1
// Code/GameEngine/Source/Common/Bfme5ThirtyTwo.cpp); trimmed to the three T1
// bodies the sweep places. The donor's sibling bfmeCurrent (under 16B) and
// bfmeLookup are declared, never defined.

class BfmeThingCX
{
public:
	int m_bfmeHead;						// +0x00
	unsigned short m_bfmeRefs;				// +0x04
};

class BfmeHandleCX
{
public:
	BfmeHandleCX(void)
	{
		m_bfmeThing = 0;
	}

	BfmeHandleCX(const BfmeHandleCX &other)
	{
		BfmeThingCX *thing = other.m_bfmeThing;

		m_bfmeThing = thing;

		if (thing)
			++thing->m_bfmeRefs;
	}

	~BfmeHandleCX(void)
	{
		if (m_bfmeThing)
			--m_bfmeThing->m_bfmeRefs;
	}

	BfmeThingCX *m_bfmeThing;				// +0x00
};

#include "../../Include/Common/BfmeSlotCZ.h"

#include "../../Include/Common/BfmeVecCZ.h"

// The out-of-range slot stays null and is read anyway, which is what puts the
// load in both paths.
// ?bfmeAt@@YGPAHPAVBfmeVecCZ@@H@Z
int * __stdcall bfmeAt(BfmeVecCZ *vector, int index)
{
	BfmeSlotCZ *slot;

	if (index >= vector->m_bfmeCount)
		slot = 0;
	else
		slot = vector->m_bfmeStart + index;

	return slot->m_bfmePointer;
}

class BfmeThingCZ
{
public:
	int m_bfmeHead[10];					// +0x00
	int m_bfmeColor;					// +0x28
};

// ?bfmeColor@@YGHPBVBfmeThingCZ@@H_N@Z
int __stdcall bfmeColor(const BfmeThingCZ *thing, int unused, bool bright)
{
	int color = thing->m_bfmeColor & 0xFFFFFF;

	color = color | 0x80000000;

	if (bright)
		color = color | 0x30000000;

	return color;
}

// Slots 2-6 and 8-18 are retail VA 0x0043B810, the rowed _purecall. Slots 0, 1 and 7
// belong to other placeholder classes (LINK-617).
extern "C" int __cdecl _purecall(void);
#define BFME_PURECALL ((int)&_purecall)
int g_bfmeVtableCZ[30] = {
	11051360, 11682992, BFME_PURECALL, BFME_PURECALL, BFME_PURECALL, BFME_PURECALL, BFME_PURECALL, 11051312,
	BFME_PURECALL, BFME_PURECALL, BFME_PURECALL, BFME_PURECALL, BFME_PURECALL, BFME_PURECALL, BFME_PURECALL, BFME_PURECALL,
	BFME_PURECALL, BFME_PURECALL, BFME_PURECALL, 1348887890, 7037793, 1663070030, 1919970671, 1769173861,
	28271, 1699897188, 1667321958, 107, 1867407204, 25966
};					// retail 0x008E4A10					// retail 0x008E4A10

class Gen_0081E480
{
public:
	Gen_0081E480(int first, int second);

private:
	int *m_bfmeVtable;					// +0x00
	int m_bfmeCount;					// +0x04
	int m_bfmeFirst;					// +0x08
	int m_bfmeSecond;					// +0x0C
	int m_bfmeFlags;					// +0x10
};

// ??0Gen_0081E480@@QAE@HH@Z
Gen_0081E480::Gen_0081E480(int first, int second)
{
	m_bfmeVtable = g_bfmeVtableCZ;
	m_bfmeCount = 0;
	m_bfmeFirst = first;
	m_bfmeSecond = second;
	m_bfmeFlags = 0;
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?rva007F76D0@Rva00801670Host@@QAEPAHPAVBfmeVecCZ@@H@Z=?bfmeAt@@YGPAHPAVBfmeVecCZ@@H@Z")
#pragma comment(linker, "/alternatename:?rva007F76D0@Rva00802550Host@@QAEPAHPAVBfmeVecCZ@@H@Z=?bfmeAt@@YGPAHPAVBfmeVecCZ@@H@Z")
