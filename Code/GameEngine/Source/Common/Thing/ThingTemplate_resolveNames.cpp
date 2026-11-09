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

#include "../../../Include/Common/ThingTemplate.h"

static __forceinline ProductionPrerequisiteVector &prerequisiteView(unsigned char (&storage)[12])
{
	return *reinterpret_cast<ProductionPrerequisiteVector *>(storage);
}


void ThingTemplate::resolveNames()
{
	int i, j;
	const int COMMANDCENTER_MASK = 2;

	for (i = 0; i < prerequisiteView(m_prereqInfo).size(); i++) {
		prerequisiteView(m_prereqInfo)[i].resolveNames();
	}

	const int MAX_BF = 32;
	const ThingTemplate *thingTemplate[MAX_BF];
	for (i = 0; i < prerequisiteView(m_prereqInfo).size(); i++) {
		int count = prerequisiteView(m_prereqInfo).begin()[i].getAllPossibleBuildFacilityTemplates(thingTemplate, MAX_BF);
		for (j = 0; j < count; j++) {
			if (thingTemplate[j])
				((ThingTemplate *)thingTemplate[j])->m5E6 = true;
		}
	}

	if ((reinterpret_cast<const unsigned char *>(m_kindof)[2] & COMMANDCENTER_MASK) != 0) {
		m5E6 = true;
	}

	rva0033BA46();
	getButtonImage();
}
