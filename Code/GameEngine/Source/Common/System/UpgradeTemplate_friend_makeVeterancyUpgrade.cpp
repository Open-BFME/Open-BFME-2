// cl: /Ireference/shims/bfme2_ascii /MD /EHsc /DNDEBUG
// ?friend_makeVeterancyUpgrade@UpgradeTemplate@@QAEXW4VeterancyLevel@@@Z @0x0026F1A5 113B
// ZH Upgrade.cpp friend_makeVeterancyUpgrade: m_type=OBJECT m_name=getVet(v)
// m_nameKey=NameKey m_display.clear m_buildTime=0 m_cost=0. Unlocks 0x0026FAFE.
// Evidence: getVet 0x0026F08B AsciiString-assign pin releaseBuffer nameToKey.
enum VeterancyLevel { LEVEL_REGULAR, LEVEL_VETERAN, LEVEL_ELITE, LEVEL_HEROIC };
enum UpgradeType { UPGRADE_TYPE_OBJECT = 1 };
enum NameKeyType { NAMEKEY_INVALID = 0 };
#include "ascii_string.h"
#include "../../../Include/Common/NameKeyGenerator.h"
extern NameKeyGenerator *TheNameKeyGenerator;
AsciiString __cdecl getVetUpgradeName(VeterancyLevel v);
#include "../../../Include/Common/Upgrade.h"
void UpgradeTemplate::friend_makeVeterancyUpgrade(VeterancyLevel v)
{
	m_type = UPGRADE_TYPE_OBJECT;
	m_name = getVetUpgradeName(v);
	m_nameKey = TheNameKeyGenerator->nameToKey(m_name);
	m_displayNameLabel.clear();
	m_buildTime = 0.0f;
	m_cost = 0;
}
