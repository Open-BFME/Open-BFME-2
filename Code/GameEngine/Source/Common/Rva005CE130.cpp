// cl: /O1 /arch:SSE /G7 /MD
// ?NotifyBuildingAboutToBeDestroyedByUI@Rva005CE130@@QAEXH@Z @0x005CE130 38B
// evidence: VTABLE slot 2 table 0x00875148; callees ?rva004E05F0@Rva004E05F0@@QAEPAVCreateAHeroData@@XZ rowed and ?fwd@Rva005E683EMid@@QAEXHH@Z rowed; callers none

class CreateAHeroData;

class Rva003F1093
{
public:
	CreateAHeroData *rva003F083A(void *arg);
};

class Rva004E05F0
{
public:
	CreateAHeroData *rva004E05F0();
	char m_lead[0x18];
	void *m_18;
	char m_mid[0x08];
	Rva003F1093 *m_24;
};

class Rva005E683EMid
{
public:
	void fwd(int a, int b);
};

class Rva005E67FE { public: virtual ~Rva005E67FE(); int m_04; };
#include "../../Include/Common/LivingWorldObservers.h"
namespace StrategicInGameUI { class PlanningPhaseBuildingSelection; }
class StrategicInGameUI::PlanningPhaseBuildingSelection : public Rva005E67FE, public LivingWorldBuildingObserver
{
public:
	virtual void NotifyBuildingAboutToBeDestroyedByUI(int arg);
	char m_lead[0x0C];
	Rva004E05F0 *m_region;
};

void StrategicInGameUI::PlanningPhaseBuildingSelection::NotifyBuildingAboutToBeDestroyedByUI(int arg)
{
	(void)arg;
	Rva004E05F0 *region = m_region;
	Rva003F1093 *f1 = region->m_24;
	if (f1 == 0)
		return;
	CreateAHeroData *createAHeroData = region->rva004E05F0();
	if (createAHeroData == 0)
		return;
	Rva005E683EMid *outer = (Rva005E683EMid *)this;
	outer->fwd((int)f1, (int)createAHeroData);
}
