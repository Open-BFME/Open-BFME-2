// cl: /DNDEBUG /MD /GX /Ireference/shims/moduledata
//
// ??1AutoPickUpUpdateModuleData@@UAE@XZ, retail 0x0049647C, 63 bytes, and
// the destructor of its EatObjectEntry vector, retail 0x004962AB, 63 bytes.
//
// Identity: the rowed ??_GAutoPickUpUpdateModuleData 0x00496460 (slot 0 of
// vtable 0x00C4F108, the table the rowed ctor 0x00496308 installs) calls
// 0x0049647C. That body tears down the vector at +0x14 through 0x004962AB
// and the pick-up filter at +0x0C through the pinned 0x00360D26, then
// restores the Snapshot base vtable 0x00BBB554; no entry vtable store, so
// the derived class is novtable as in LargeGroupBonusUpdateModuleDataDtor.
//
// 0x004962AB is the STLport vector destructor inlined over its base: the
// rowed 12-byte-stride range destroy 0x00496292 over [start, finish) under
// EH state 0, then the base frees start through the CRT free. The element
// type is unproven (the ctor TU's BfmeE16 stand-in has no destructor), so
// the vector keeps a stand-in name; only its layout and calls are claimed.

#include "Common/Snapshot.h"

extern "C" void __cdecl free(void *);

void Rva00496292Destroy(void *first, void *last);

class Rva00360D26Member
{
public:
	~Rva00360D26Member();

private:
	unsigned char m_data[4];
};

class Rva004962ABVectorBase
{
public:
	~Rva004962ABVectorBase()
	{
		if (m_start)
			free(m_start);
	}

protected:
	void *m_start;
	void *m_finish;
	void *m_endOfStorage;
};

class Rva004962ABVector : public Rva004962ABVectorBase
{
public:
	~Rva004962ABVector();
};

Rva004962ABVector::~Rva004962ABVector()
{
	Rva00496292Destroy(m_start, m_finish);
}

class __declspec(novtable) AutoPickUpUpdateModuleData : public Snapshot
{
public:
	virtual ~AutoPickUpUpdateModuleData();

private:
	int m_unused04; // +4
	int m_scanDelayTime; // +8
	Rva00360D26Member m_pickUpFilter; // +0xC
	float m_scanDistance; // +0x10
	Rva004962ABVector m_eatObjectEntries; // +0x14
	unsigned char m_autoThrowObject; // +0x20
	unsigned char m_runFromButton; // +0x21
	unsigned char m_pad22[2]; // +0x22
	int m_runFromButtonNumber; // +0x24
	unsigned char m_canScanWhileAttackingOrMoving; // +0x28
	unsigned char m_tail[3]; // +0x29..+0x2B
};

// ??1AutoPickUpUpdateModuleData@@UAE@XZ @0x49647C
AutoPickUpUpdateModuleData::~AutoPickUpUpdateModuleData()
{
}
