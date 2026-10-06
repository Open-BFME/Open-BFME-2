// cl: /Ireference/shims/bfme2_ascii /MD /EHsc /DNDEBUG
// ?friend_makeVeterancyUpgrade@UpgradeTemplate@@QAEXW4VeterancyLevel@@@Z @0x0026F1A5 113B
// ZH Upgrade.cpp friend_makeVeterancyUpgrade: m_type=OBJECT m_name=getVet(v)
// m_nameKey=NameKey m_display.clear m_buildTime=0 m_cost=0. Unlocks 0x0026FAFE.
// Evidence: getVet 0x0026F08B AsciiString-assign pin releaseBuffer nameToKey.
enum VeterancyLevel { LEVEL_REGULAR, LEVEL_VETERAN, LEVEL_ELITE, LEVEL_HEROIC };
enum UpgradeType { UPGRADE_TYPE_OBJECT = 1 };
enum NameKeyType { NAMEKEY_INVALID = 0 };
#include "ascii_string.h"
class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const AsciiString &s);
};
extern NameKeyGenerator *TheNameKeyGenerator;
AsciiString __cdecl getVetUpgradeName(VeterancyLevel v);
class UpgradeTemplate
{
public:
	void friend_makeVeterancyUpgrade(VeterancyLevel v);
private:
	char m_pad00[4];
	int m_type;
	AsciiString m_name;
	int m_nameKey;
	char m_pad10[0x18];
	AsciiString m_displayNameLabel;
	char m_pad2c[4];
	float m_buildTime;
	int m_cost;
};
void UpgradeTemplate::friend_makeVeterancyUpgrade(VeterancyLevel v)
{
	m_type = UPGRADE_TYPE_OBJECT;
	m_name = getVetUpgradeName(v);
	m_nameKey = TheNameKeyGenerator->nameToKey(m_name);
	m_displayNameLabel.clear();
	m_buildTime = 0.0f;
	m_cost = 0;
}
