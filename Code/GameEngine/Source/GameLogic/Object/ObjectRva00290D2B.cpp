// cl: /DNDEBUG /MD
// ?hasUpgrade@Object@@QBE_NPBVUpgradeTemplate@@@Z retail 0x00290D2B 23B.
// Object null-guarded UpgradeTemplate bit test via rowed ?hasUpgradeMask@Object@@QBE_NH@Z.
// Evidence: same-this preserved-ecx call to rowed Object bit query at 0x00290D3A with int at +0x38;
// UpgradeTemplate mask index at +0x38 per UpgradeCenterFindUpgradeByKey.cpp and UpgradeMuxData TU;
// twin precedent ?rva002AB87D@Player@@QBE_NPBVUpgradeTemplate@@@Z 23B same shape;
// neighbours ?isAbleToAttack@Object (0x00290B73) and ?findSpecialPowerModuleInterface@Object (0x00290E22);
// callers pass Object* in ecx plus UpgradeTemplate* on stack e.g. 0x00294B3C mov ecx ebx push edi.
#include "../../../Include/Common/Upgrade.h"

class Rva0028F633
{
public:
	Rva0028F633(int unused, int bit);
	unsigned m_bits[32]; // +0x00
};

class UpgradeModuleInterface
{
public:
	virtual void s0();
	virtual void s1();
	virtual void s2();
	virtual bool resetUpgrade(const Rva0028F633 &mask);
	virtual void s4();
	virtual void s5();
	virtual void s6();
};

#include "../../../Include/GameLogic/Module/BehaviorModule.h"


void Rva004CE245(void *p);

class Object
{
public:
	bool hasUpgradeMask(int bit) const;
	bool hasUpgrade(const UpgradeTemplate *tmpl) const;
	void removeUpgrade(const UpgradeTemplate *upgrade);

private:
	char m_pad00[0x244];
	BehaviorModule **m_modules244;
	char m_pad248[0x284 - 0x248];
	unsigned int m_bits284[4];
};

bool Object::hasUpgrade(const UpgradeTemplate *upgradeT) const
{
	if (!upgradeT)
		return false;
	return hasUpgradeMask(upgradeT->field38);
}

void Object::removeUpgrade(const UpgradeTemplate *upgrade)
{
	const unsigned int bit = upgrade->field38;
	m_bits284[bit >> 5] &= ~(1u << (bit & 31));
	for (BehaviorModule **m = m_modules244; *m; ++m)
	{
		UpgradeModuleInterface *u = (*m)->getUpgrade();
		if (!u)
			continue;
		Rva0028F633 mask(0, upgrade->field38);
		if (!u->resetUpgrade(mask))
			continue;
		Rva004CE245(u);
	}
}
