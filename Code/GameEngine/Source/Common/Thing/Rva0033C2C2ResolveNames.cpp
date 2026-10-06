// cl: /DNDEBUG /MD
// ?resolveNames@ThingTemplate@@QAEXXZ @0x0033C2C2 212B.
// ThingTemplate name resolution: resolve each production prerequisite, then
// mark every build-facility template they admit, set the command-center flag,
// and refresh the portrait plus button images via the rowed 0x33BA46 and
// 0x33B580 resolvers. Prereq vector at +0x324, kindof byte at +0x10a,
// build-facility flag at +0x5e6 (same holder as the 0x33DDA1 teardown).
class Image;
class ThingTemplate;

typedef int Int;

class ProductionPrerequisite
{
public:
	void resolveNames();
	int getAllPossibleBuildFacilityTemplates(const ThingTemplate *tmpls[], int maxtmpls) const;

private:
	char m_pad[0x24];
};

class ProductionPrerequisiteVector
{
public:
	unsigned size() const { return _M_finish - _M_start; }
	ProductionPrerequisite &operator[](int i) { return _M_start[i]; }
	ProductionPrerequisite *begin() { return _M_start; }

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
	const Image *getButtonImage();
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
		int count = m_prereqInfo.begin()[i].getAllPossibleBuildFacilityTemplates(tmpls, MAX_BF);
		for (j = 0; j < count; j++) {
			if (tmpls[j])
				((ThingTemplate *)tmpls[j])->m_isBuildFacility = true;
		}
	}

	if (isKindOf(KINDOF_COMMANDCENTER)) {
		m_isBuildFacility = true;
	}

	rva0033BA46();
	getButtonImage();
}
