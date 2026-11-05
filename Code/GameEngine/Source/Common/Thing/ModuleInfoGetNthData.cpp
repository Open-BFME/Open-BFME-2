// cl: /MD /DNDEBUG
// ModuleInfo indexed accessor (Locomotor/AIUpdate parse cluster).

#include "../../../Include/Common/ModuleData.h"

class AIUpdateModuleData;


#include "../../../Include/Common/ModuleInfoClass.h"

// Local stride calculation avoids emitting a competing ModuleInfo::getCount.
static __forceinline int moduleRecordCount(const ModuleInfo *info)
{
    return ((const char *)info->m_end - (const char *)info->m_begin) / 20;
}

class ThingTemplate
{
	char m_pad[0x2E4];
	ModuleInfo m_behaviorModuleInfo;

public:
	AIUpdateModuleData *friend_getAIModuleInfo();
	int rva0033B479() const;
	const ModuleData *rva0033B3D7() const;
	const ModuleData *rva0033B427(int unused) const;
};

inline const ModuleData *ModuleInfo::getNthData(int i) const
{
	if (i >= 0)
	{
		const char *recordBegin = (const char *)m_begin;
		const char *recordEnd = (const char *)m_end;
		unsigned int recordCount = (recordEnd - recordBegin) / 20;
		if (i < recordCount)
			return *(const ModuleData * const *)(recordBegin + i * 20 + 8);
	}
	return 0;
}

AIUpdateModuleData *ThingTemplate::friend_getAIModuleInfo()
{
	int numModInfos = moduleRecordCount(&m_behaviorModuleInfo);
	for (int j = 0; j < numModInfos; ++j)
	{
		if (m_behaviorModuleInfo.getNthData(j) && m_behaviorModuleInfo.getNthData(j)->slot04())
			return (AIUpdateModuleData *)m_behaviorModuleInfo.getNthData(j);
	}
	return 0;
}

// Native 33B3D7..33B428, between friend_getAIModuleInfo and rva0033B479:
// the same 20-byte record scan, testing virtual slot +14 and returning the
// first module data that passes, or null. isLocationClearOfObjects reads its
// +0x2C float as the query filter's range; the predicate is unnamed.
const ModuleData *ThingTemplate::rva0033B3D7() const
{
	int numModInfos = moduleRecordCount(&m_behaviorModuleInfo);
	for (int j = 0; j < numModInfos; ++j)
	{
		if (m_behaviorModuleInfo.getNthData(j) && m_behaviorModuleInfo.getNthData(j)->slot05())
			return m_behaviorModuleInfo.getNthData(j);
	}
	return 0;
}

// Native 33B427..33B479 RET4, between rva0033B3D7 and rva0033B479 (callers
// InGameUI::handleBuildPlacements and BuildAssistant::isLocationLegalToBuild):
// the same scan testing virtual slot +18; its int argument is never read.
const ModuleData *ThingTemplate::rva0033B427(int unused) const
{
	int numModInfos = moduleRecordCount(&m_behaviorModuleInfo);
	for (int j = 0; j < numModInfos; ++j)
	{
		if (m_behaviorModuleInfo.getNthData(j) && m_behaviorModuleInfo.getNthData(j)->slot06())
			return m_behaviorModuleInfo.getNthData(j);
	}
	return 0;
}

// Native 33B479..33B4CD RET0. The verified revival-entry caller uses this
// existing const int callee. Like friend_getAIModuleInfo, it scans the
// 20-byte behavior records at +2E4, but tests virtual slot +24 and returns
// the selected module's word at +8, or 1 when none qualifies. The predicate
// and field remain unnamed target facts; no module subtype is inferred.
int ThingTemplate::rva0033B479() const
{
	int numModInfos = moduleRecordCount(&m_behaviorModuleInfo);
	for (int j = 0; j < numModInfos; ++j)
	{
		if (m_behaviorModuleInfo.getNthData(j) && m_behaviorModuleInfo.getNthData(j)->slot09())
			return *(const int *)((const char *)m_behaviorModuleInfo.getNthData(j) + 8);
	}
	return 1;
}

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. Taking each one's
// address keeps this unit's copy for its row; these pointers are not retail
// data.
static const ModuleData * (ModuleInfo::*const _bfmeInlineAnchor0_getNthData)(int i) const = &ModuleInfo::getNthData;
