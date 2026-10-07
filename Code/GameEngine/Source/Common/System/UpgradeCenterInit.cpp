// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// ?init@UpgradeCenter@@UAEXXZ @0x0026FAFE 190B
// UpgradeCenter::init donor ZH Upgrade.cpp creates 3 veterancy upgrades via newUpgrade empty plus friend_makeVeterancyUpgrade VETERAN ELITE HEROIC. Evidence: slot1 vtable 0x007FABB8; rowed newUpgrade 0x0026F952 friend_makeVeterancyUpgrade 0x0026F1A5 StringBase PBD 0x00037BA0 releaseBuffer 0x00036410; empty string literal; donor Upgrade.h.
#include "ascii_string.h"

enum VeterancyLevel { LEVEL_REGULAR, LEVEL_VETERAN, LEVEL_ELITE, LEVEL_HEROIC };

class UpgradeTemplate
{
public:
	void friend_makeVeterancyUpgrade(VeterancyLevel v);
};

class UpgradeCenter
{
public:
	virtual ~UpgradeCenter();
	virtual void init();
	virtual void postProcessLoad();
	virtual void reset();
	virtual void update();
	UpgradeTemplate *newUpgrade(const AsciiString &name, bool assignMaskBit);
};

void UpgradeCenter::init(void)
{
	UpgradeTemplate *up;

	up = newUpgrade("", true);
	up->friend_makeVeterancyUpgrade(LEVEL_VETERAN);

	up = newUpgrade("", true);
	up->friend_makeVeterancyUpgrade(LEVEL_ELITE);

	up = newUpgrade("", true);
	up->friend_makeVeterancyUpgrade(LEVEL_HEROIC);
}
