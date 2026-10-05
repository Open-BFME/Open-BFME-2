// ?resolveNames@ThingTemplate@@QAEXXZ
// partial score=0.95 date=2026-10-05
// cl: /O1 /DNDEBUG /MD
class Image;
class ThingTemplate;

typedef int Int;

class ProductionPrerequisite
{
public:
	void resolveNames();
	Int getAllPossibleBuildFacilityTemplates(const ThingTemplate *tmpls[], Int maxtmpls) const;

private:
	char m_pad[0x24];
};

class ProductionPrerequisiteVector
{
public:
	unsigned size() const { return _M_finish - _M_start; }
	ProductionPrerequisite &operator[](int i) { return _M_start[i]; }

private:
	ProductionPrerequisite *_M_start;
	ProductionPrerequisite *_M_finish;
	ProductionPrerequisite *_M_end;
};

class ThingTemplate
{
public:
	void resolveNames();
	const Image *rva0033BA46();
	const Image *rva0033B580();
	bool isKindOf(int mask) const { return (m_kindofByte & mask) != 0; }

	static const int KINDOF_COMMANDCENTER = 2;

private:
	char m_pad00[0x10a];
	unsigned char m_kindofByte;
	char m_pad0B[0x324 - 0x10b];
	ProductionPrerequisiteVector m_prereqInfo;
	char m_pad30[0x5e6 - 0x330];
	bool m_isBuildFacility;
};

void ThingTemplate::resolveNames()
{
	int i, j;

	for (i = 0; i < m_prereqInfo.size(); i++) {
		m_prereqInfo[i].resolveNames();
	}

	const int MAX_BF = 32;
	const ThingTemplate *tmpls[MAX_BF];
	for (i = 0; i < m_prereqInfo.size(); i++) {
		int count = m_prereqInfo[i].getAllPossibleBuildFacilityTemplates(tmpls, MAX_BF);
		for (j = 0; j < count; j++) {
			if (tmpls[j])
				((ThingTemplate *)tmpls[j])->m_isBuildFacility = true;
		}
	}

	if (isKindOf(KINDOF_COMMANDCENTER)) {
		m_isBuildFacility = true;
	}

	rva0033BA46();
	rva0033B580();
}
