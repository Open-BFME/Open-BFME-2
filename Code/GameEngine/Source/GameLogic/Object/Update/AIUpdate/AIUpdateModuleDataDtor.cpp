// cl: /GX /DNDEBUG /MD /Ireference/shims/moduledata
//
// ??1AIUpdateModuleData@@UAE@XZ, retail 0x00494BE4, 52 bytes.
// AIUpdate ModuleData dtor: releases the +0x10 holder through the rowed
// Release_Ref at 0x00050ED3 when non-null, then restores the Snapshot base
// vtable 0x00BBB554. Holder dtor is inline and throwing (EH-tracked state
// 0, EH prolog with funclet 0xB8CEE6); remaining members are trivial pads.
// Layout from the rowed ctor TU (AIUpdateModuleDataCtor.cpp, base size
// 0x18 per WeaponModeSpecialPowerUpdateModuleDataCtor.cpp derived offsets
// +0x18/+0x1C) and vtable 0x00870220 with slot 0 ??_G at 0x0058957E.
// Shape follows AudioLoopUpgradeModuleDataDtor / BloodthirstyUpdateModuleDataDtor
// (shared Snapshot base with BBB554-restoring dtor; novtable suppresses the
// derived vtable store retail lacks, leaving an empty derived body).

#include "Common/Snapshot.h"

class OpaqueRefCounted
{
public:
	void Release_Ref();
};

struct RefHolder
{
	~RefHolder()
	{
		if (m_ptr)
			m_ptr->Release_Ref();
	}

	OpaqueRefCounted *m_ptr;
};

class __declspec(novtable) AIUpdateModuleData : public Snapshot
{
public:
	virtual ~AIUpdateModuleData();

private:
	int m_unused04; // +0x04
	int m_unused08; // +0x08
	int m_unused0C; // +0x0C
	RefHolder m_holder10; // +0x10
	bool m_unused14; // +0x14
	unsigned char m_pad15[3];
};

AIUpdateModuleData::~AIUpdateModuleData()
{
}
