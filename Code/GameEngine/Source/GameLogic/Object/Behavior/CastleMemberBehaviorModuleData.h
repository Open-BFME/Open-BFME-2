#pragma once

#include "../../../../Include/Common/ModuleData.h"
#include "../../../../../Libraries/Source/WWVegas/WWLib/OpaqueRefCounted.h"

struct BeingBuiltSoundHolder
{
	~BeingBuiltSoundHolder()
	{
		if (m_ptr)
			m_ptr->Release_Ref();
	}

	OpaqueRefCounted *m_ptr;
};

class CastleMemberBehaviorModuleData : public ModuleData
{
public:
	CastleMemberBehaviorModuleData();
	virtual ~CastleMemberBehaviorModuleData();

private:
	int m_campDestroyedOwnerEvaEvent; // +0x08
	int m_campDestroyedAllyEvaEvent; // +0x0C
	int m_campDestroyedAttackerEvaEvent; // +0x10
	BeingBuiltSoundHolder m_beingBuiltSound; // +0x14
	bool m_storeUpgradePrice; // +0x18
	bool m_countsForEvaCastleBreached; // +0x19
	char m_pad1A[0x1C - 0x1A];
};
