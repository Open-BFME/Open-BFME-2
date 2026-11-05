// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /DNDEBUG /MD /GX /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /D_STLP_NO_EXCEPTIONS
// stlport
//
// ?doSpecialPower@PlayerUpgradeSpecialPower@@UAEXI@Z, retail 0x004C7CAD,
// 187 bytes: slot 10 of PlayerUpgradeSpecialPower's +0x10 special-power
// interface vftable 0x00C5E120 (the doSpecialPower slot of the family, as in
// PlayerHealSpecialPowerSlots.cpp), so `this` is that subobject. Nothing
// while the Object's +0x1C8 disabled flags are set (BitFlags<11>::any);
// otherwise interface slot 15 with 1.0f, then over a copy of the module
// data's +0x7C upgrade names: each must name an UpgradeTemplate (else the
// power stops untriggered), and a player upgrade (type 0) is granted to the
// controlling Player (0x002AE329 with 2, 0, as in SalvageCrateCollide.cpp);
// then the rowed SpecialPowerModule::triggerSpecialPower with no location.
#include <vector>

#include "../../../Common/RTS/PlayerUpgradeStatus.h"

template <typename T> struct BfmeStringData;

#include "ascii_string.h"

namespace _STL {
template<> vector<AsciiString>::vector(const vector<AsciiString> &);
}

struct Coord3D;

template <int N> class BitFlags
{
public:
	bool any() const;
private:
	unsigned int m_bits[(N + 31) / 32];
};

#include "../../../../Include/Common/Upgrade.h"

extern UpgradeCenter *TheUpgradeCenter;

#include "../../../../Include/Common/Player.h"

class Object
{
public:
	Player *getControllingPlayer() const;
	bool isDisabled() const { return m_disabled.any(); }
private:
	unsigned char m_pad000[0x1C8];
	BitFlags<11> m_disabled; // +0x1C8
};

#include "../../../../Include/GameLogic/Module/SpecialPowerModuleData.h"

class PlayerUpgradeSpecialPowerModuleData : public SpecialPowerModuleData
{
public:
	PlayerUpgradeSpecialPowerModuleData();
	virtual ~PlayerUpgradeSpecialPowerModuleData();
	_STL::vector<AsciiString> m_upgradeNames; // +0x7C
};

#include "../../../../Include/GameLogic/Module/BehaviorModule.h"

#include "../../../../Include/GameLogic/Module/SpecialPowerModule.h"

class SpecialPowerModule : public BehaviorModule, public SpecialPowerModuleInterface
{
public:
	SpecialPowerModule( Thing *thing, const ModuleData *moduleData );
	void triggerSpecialPower(const Coord3D *location);
	// Public: the rowed dtor at 0x00493DEF is ??1SpecialPowerModule@@UAE@XZ.
	virtual ~SpecialPowerModule();
};

class PlayerUpgradeSpecialPower : public SpecialPowerModule
{
public:
	virtual void doSpecialPower(unsigned int options);
};

void PlayerUpgradeSpecialPower::doSpecialPower(unsigned int)
{
	if (m_object->isDisabled())
		return;
	startPowerRecharge(1.0f);
	_STL::vector<AsciiString> names(
		static_cast<const PlayerUpgradeSpecialPowerModuleData *>(m_moduleData)->m_upgradeNames);
	for (unsigned int i = 0; i < names.size(); ++i)
	{
		const UpgradeTemplate *upgrade = TheUpgradeCenter->findUpgrade(names[i]);
		if (!upgrade)
			return;
		if (upgrade->m_type == 0)
		{
			Player *player = m_object->getControllingPlayer();
			player->addUpgrade(upgrade, UPGRADE_STATUS_COMPLETE, 0);
		}
	}
	triggerSpecialPower(0);
}
