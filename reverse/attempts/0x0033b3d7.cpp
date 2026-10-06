// ?rva0033B3D7@Rva0033B3D7@@QAEPAVAIUpdateModuleData@@XZ
// partial score=0.9 date=2026-10-06
// cl: /MD /DNDEBUG
// Retail RE: ?rva0033B3D7@ThingTemplate@@QAEPAUAIUpdateModuleData@@XZ @0x0033B3D7 (162B).
// Identity: ThingTemplate is supported by the neighboring validate() unit and
// the callers' shared template-processing role. The module-data list at +0x2E4
// and 20-byte entry stride are target disassembly evidence. The donor's AI
// module predicate name/type is retained as structural inference; retail calls
// vtable slot +0x14 here.

class ModuleData
{
public:
	virtual void bfmeReservedV0();
	virtual void bfmeReservedV1();
	virtual void bfmeReservedV2();
	virtual void bfmeReservedV3();
	virtual void bfmeReservedV4();
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

	const ModuleData *getNthData(int i) const;
};

class Rva0033B3D7
{
	char m_pad[0x2E4];
	ModuleInfo m_behaviorModuleInfo;

public:
	AIUpdateModuleData *rva0033B3D7();
};

const ModuleData *ModuleInfo::getNthData(int i) const
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

AIUpdateModuleData *Rva0033B3D7::rva0033B3D7()
{
	const char *begin = (const char *)m_behaviorModuleInfo.m_begin;
	const char *end = (const char *)m_behaviorModuleInfo.m_end;
	int numModInfos = (end - begin) / 20;
	for (int j = 0; j < numModInfos; ++j)
	{
		if (m_behaviorModuleInfo.getNthData(j) && m_behaviorModuleInfo.getNthData(j)->isAiModuleData())
			return (AIUpdateModuleData *)m_behaviorModuleInfo.getNthData(j);
	}
	return 0;
}
