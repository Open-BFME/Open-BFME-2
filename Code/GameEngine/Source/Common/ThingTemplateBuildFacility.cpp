// cl: /O1 /arch:SSE /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?getBuildFacilityTemplate@ThingTemplate@@QBEPBV1@PBVPlayer@@@Z @0x0033A97F 38B ThingTemplate prereq vector +0x324 element 0x24 tailcalls ProductionPrerequisite::getExistingBuildFacilityTemplate callers 0x0033AB48 donor ThingTemplate.cpp Zero Hour
#include <vector>

typedef int Int;

class Player;
class ThingTemplate;

class ProductionPrerequisite
{
public:
	const ThingTemplate *getExistingBuildFacilityTemplate(const Player *player) const;
private:
	char m_unmodelled[0x24];
};

class ThingTemplate
{
public:
	const ThingTemplate *getBuildFacilityTemplate(const Player *player) const;
	Int getPrereqCount() const { return m_prereqInfo.size(); }
private:
	char m_before_prereqs[0x324];
	_STL::vector<ProductionPrerequisite> m_prereqInfo;
};

const ThingTemplate *ThingTemplate::getBuildFacilityTemplate(const Player *player) const
{
	if (getPrereqCount() > 0)
	{
		return m_prereqInfo[0].getExistingBuildFacilityTemplate(player);
	}
	else
	{
		return 0;
	}
}
