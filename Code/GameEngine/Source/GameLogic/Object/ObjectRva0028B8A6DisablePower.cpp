// cl: /O1 /G7 /DNDEBUG /MD /EHs
// ?rva0028B8A6@Object@@QAEX_N@Z @0x0028B8A6 185B.
// Target evidence: Object::getControllingPlayer and findModule select the
// "RadarUpgrade" module. Its secondary base is at module+0x10; the data
// pointer is at +4 and DisableProof is at data+0x118. Power uses the template
// value at +0x548 and the controller's Energy view at +0x1BC. The method name
// stays address-derived; its relationship to the donor method is unproven.
// Donor semantics: GeneralsMD Object::onDisabledEdge (Object.cpp, BFME 1
// revision 6583b3c1) contains the radar and energy-update sequence. The
// target-specific offsets and method identity below come from BFME2 bytes.

enum NameKeyType
{
	NK_UNKNOWN = 0
};

#include "../../../Include/Common/NameKeyGenerator.h"

extern NameKeyGenerator *TheNameKeyGenerator;

class Player;

#include "../../../Include/GameLogic/Module/UpgradeModule.h"

struct RadarUpgradeDataView
{
	unsigned char m_pad00[0x118];
	bool m_disableProof;
};

class RadarUpgrade : public UpgradeModule
{
public:
	bool getIsDisableProof() const
	{
		return ((RadarUpgradeDataView *)m_moduleData)->m_disableProof;
	}
};

#include "../../../Include/Common/ThingTemplate.h"

#include "../../../Include/Common/Player.h"

class Object;
class Energy
{
public:
	void objectEnteringInfluence(Object *obj);
	void objectLeavingInfluence(Object *obj);
	void adjustPower(int amount, bool incoming);
};

#include "object.h"

// ?rva0028B8A6@Object@@QAEX_N@Z
void Object::rva0028B8A6(bool becomingDisabled)
{
	Player *controller = getControllingPlayer();
	if (controller)
	{
		static NameKeyType radar = TheNameKeyGenerator->nameToKey("RadarUpgrade");
		Module *mod = findModule(radar);
		if (mod)
		{
			RadarUpgrade *radarMod = (RadarUpgrade *)mod;
			if (radarMod->isAlreadyUpgraded())
			{
				if (becomingDisabled)
					controller->removeRadar(radarMod->getIsDisableProof());
				else
					controller->addRadar(radarMod->getIsDisableProof());
			}
		}
	}

	int powerToAdjust = m_template->m_energyProduction;
	if (powerToAdjust > 0)
	{
		if (controller)
		{
			Energy *energy = (Energy *)((char *)controller + 0x1BC);
			energy->adjustPower(powerToAdjust, !becomingDisabled);
		}
	}
}
