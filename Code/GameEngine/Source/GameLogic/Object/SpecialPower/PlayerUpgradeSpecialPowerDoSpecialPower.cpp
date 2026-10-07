// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /GX /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
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

struct Coord3D;

template <int N> class BitFlags
{
public:
	bool any() const;
private:
	unsigned int m_bits[(N + 31) / 32];
};

class UpgradeTemplate
{
public:
	char m_pad00[0x04];
	int m_type; // +0x04 (0 a player upgrade)
};

class UpgradeCenter
{
public:
	const UpgradeTemplate *findUpgrade(const AsciiString &name) const;
};
extern UpgradeCenter *TheUpgradeCenter;

class Player
{
public:
	Upgrade *rva002AE329(const UpgradeTemplate *upgrade, UpgradeStatusType status, int flag);
};

class Object
{
public:
	Player *getControllingPlayer() const;
	bool isDisabled() const { return m_disabled.any(); }
private:
	unsigned char m_pad000[0x1C8];
	BitFlags<11> m_disabled; // +0x1C8
};

struct PlayerUpgradeSpecialPowerModuleData
{
	unsigned char m_pad00[0x7C];
	_STL::vector<AsciiString> m_upgradeNames; // +0x7C
};

class ModuleBase
{
public:
	virtual ~ModuleBase();
protected:
	const PlayerUpgradeSpecialPowerModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};

class BehaviorModuleInterface
{
public:
	virtual void b00() = 0;
};

class SpecialPowerModuleInterface
{
public:
	virtual void s00() = 0;
	virtual void s01() = 0;
	virtual void s02() = 0;
	virtual void s03() = 0;
	virtual void s04() = 0;
	virtual void s05() = 0;
	virtual void s06() = 0;
	virtual void s07() = 0;
	virtual void s08() = 0;
	virtual void s09() = 0;
	virtual void doSpecialPower(unsigned int options) = 0;
	virtual void s11() = 0;
	virtual void s12() = 0;
	virtual void s13() = 0;
	virtual void s14() = 0;
	virtual void s15(float value) = 0;
};

class SpecialPowerModule : public ModuleBase, public BehaviorModuleInterface,
	public SpecialPowerModuleInterface
{
public:
	void triggerSpecialPower(const Coord3D *location);
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
	s15(1.0f);
	_STL::vector<AsciiString> names(m_moduleData->m_upgradeNames);
	for (unsigned int i = 0; i < names.size(); ++i)
	{
		const UpgradeTemplate *upgrade = TheUpgradeCenter->findUpgrade(names[i]);
		if (!upgrade)
			return;
		if (upgrade->m_type == 0)
		{
			Player *player = m_object->getControllingPlayer();
			player->rva002AE329(upgrade, UPGRADE_STATUS_COMPLETE, 0);
		}
	}
	triggerSpecialPower(0);
}
