// cl: /DNDEBUG /MD
// ?rva00290D2B@Object@@QBE_NPBVUpgradeTemplate@@@Z retail 0x00290D2B 23B.
// Object null-guarded UpgradeTemplate bit test via rowed ?rva0028D9E5@Object@@QBE_NH@Z.
// Evidence: same-this preserved-ecx call to rowed Object bit query at 0x00290D3A with int at +0x38;
// UpgradeTemplate mask index at +0x38 per UpgradeCenterFindUpgradeByKey.cpp and UpgradeMuxData TU;
// twin precedent ?rva002AB87D@Player@@QBE_NPBVUpgradeTemplate@@@Z 23B same shape;
// neighbours ?isAbleToAttack@Object (0x00290B73) and ?findSpecialPowerModuleInterface@Object (0x00290E22);
// callers pass Object* in ecx plus UpgradeTemplate* on stack e.g. 0x00294B3C mov ecx ebx push edi.
class UpgradeTemplate
{
public:
	char m_pad[0x38];
	unsigned int m_bitIndex;
};

struct Rva0028F633
{
	unsigned int m_bits[32];
	Rva0028F633(int unused, int bit);
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

class BfmeObjectModule
{
public:
	virtual void slot0();

private:
	unsigned int m_data[2];
};

class BehaviorModuleInterface
{
public:
	virtual void b0();
	virtual void b1();
	virtual void b2();
	virtual void b3();
	virtual void b4();
	virtual void b5();
	virtual void b6();
	virtual void b7();
	virtual void b8();
	virtual void b9();
	virtual UpgradeModuleInterface *getUpgrade();
};

class BehaviorModule : public BfmeObjectModule, public BehaviorModuleInterface
{
};

void Rva004CE245(void *p);

class Object
{
public:
	bool rva0028D9E5(int bit) const;
	bool rva00290D2B(const UpgradeTemplate *tmpl) const;
	void rva00290D42(const UpgradeTemplate *upgrade);

private:
	char m_pad00[0x244];
	BehaviorModule **m_modules244;
	char m_pad248[0x284 - 0x248];
	unsigned int m_bits284[4];
};

bool Object::rva00290D2B(const UpgradeTemplate *tmpl) const
{
	if (!tmpl)
		return false;
	return rva0028D9E5(tmpl->m_bitIndex);
}

void Object::rva00290D42(const UpgradeTemplate *upgrade)
{
	m_bits284[upgrade->m_bitIndex >> 5] &= ~(1u << (upgrade->m_bitIndex & 31));
	for (BehaviorModule **m = m_modules244; *m; ++m)
	{
		UpgradeModuleInterface *u = (*m)->getUpgrade();
		if (!u)
			continue;
		Rva0028F633 mask(0, upgrade->m_bitIndex);
		if (!u->resetUpgrade(mask))
			continue;
		Rva004CE245(u);
	}
}
