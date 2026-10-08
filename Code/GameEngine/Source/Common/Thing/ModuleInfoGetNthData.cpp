// cl: /MD /DNDEBUG
// ModuleInfo indexed accessor (Locomotor/AIUpdate parse cluster).

class ModuleData
{
public:
	virtual void bfmeReservedV0();
	virtual void bfmeReservedV1();
	virtual void bfmeReservedV2();
	virtual void bfmeReservedV3();
	virtual bool isAiModuleData() const;
};

class AIUpdateModuleData;

struct BfmeModuleNugget
{
	char m_name[4];
	char m_tag[4];
	const ModuleData *m_data;
	int m_interfaceMask;
	int m_tail;
};

class ModuleInfo
{
public:
	const void *m_begin;
	const void *m_end;
	const void *m_storage;

public:
	__declspec(noinline) const ModuleData *getNthData(int i) const;
};

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
};

inline const ModuleData *ModuleInfo::getNthData(int i) const
{
	if (i >= 0)
	{
		const char *b = (const char *)m_begin;
		const char *e = (const char *)m_end;
		unsigned int n = (e - b) / 20;
		if (i < n)
			return *(const ModuleData * const *)(b + i * 20 + 8);
	}
	return 0;
}

AIUpdateModuleData *ThingTemplate::friend_getAIModuleInfo()
{
	int numModInfos = moduleRecordCount(&m_behaviorModuleInfo);
	for (int j = 0; j < numModInfos; ++j)
	{
		if (m_behaviorModuleInfo.getNthData(j) && m_behaviorModuleInfo.getNthData(j)->isAiModuleData())
			return (AIUpdateModuleData *)m_behaviorModuleInfo.getNthData(j);
	}
	return 0;
}

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. Taking each one's
// address keeps this unit's copy for its row; these pointers are not retail
// data.
static const ModuleData * (ModuleInfo::*const _bfmeInlineAnchor0_getNthData)(int i) const = &ModuleInfo::getNthData;
