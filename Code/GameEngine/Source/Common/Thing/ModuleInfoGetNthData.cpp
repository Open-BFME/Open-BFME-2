// cl: /O1 /G7 /MD /DNDEBUG
// ModuleInfo indexed accessor (Locomotor/AIUpdate parse cluster).

class ModuleData;

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
	const void *m_begin;
	const void *m_end;

public:
	const ModuleData *getNthData(int i) const;
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
