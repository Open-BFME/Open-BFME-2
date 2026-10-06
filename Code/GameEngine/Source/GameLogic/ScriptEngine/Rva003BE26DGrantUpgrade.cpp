// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?doUnitReceiveUpgrade@ScriptActions@@IAEXPAVParameter@@ABVAsciiString@@@Z @0x003BE26D 110B.
// Grants an upgrade to a named unit: ScriptEngine::getUnitNamed(arg1), then
// UpgradeCenter::findUpgrade(arg2). When the Object+4 flag byte carries 0x20,
// the rva0028C197 provider target is probed through vtable slot 0xB4 and
// granted through slot 0xB8; otherwise Object::rva00293077 applies it.
// Caller 0x003CD380 in huge dispatch. Callee views are TU-local; slot indices
// and signatures come from the retail immediates and rowed manglings.
class Parameter;
class AsciiString;
class UpgradeTemplate;

class ObjectP04Flags
{
public:
	char m_pad[0x115];
	unsigned char m_flag115;
};

class Object
{
public:
	void *rva0028C197() const;
	void rva00293077(const void *info);
	char m_pad0[4];
	ObjectP04Flags *m_p04;
};

class ScriptEngine
{
public:
	Object *getUnitNamed(Parameter *param);
};
extern ScriptEngine *TheScriptEngine;


class UpgradeCenter
{
public:
	const UpgradeTemplate *findUpgrade(const AsciiString &name) const;
};
extern UpgradeCenter *TheUpgradeCenter;


class Rva0028C197Target
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03(); virtual void s04();
	virtual void s05(); virtual void s06(); virtual void s07(); virtual void s08(); virtual void s09();
	virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
	virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24();
	virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29();
	virtual void s30(); virtual void s31(); virtual void s32(); virtual void s33(); virtual void s34();
	virtual void s35(); virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39();
	virtual void s40(); virtual void s41(); virtual void s42(); virtual void s43(); virtual void s44();
	virtual bool slot45(const UpgradeTemplate *upgrade);
	virtual void slot46(const UpgradeTemplate *upgrade, int extra);
};

class ScriptActions
{
protected:
	void doUnitReceiveUpgrade(Parameter *unit, const AsciiString &upgradeName);
};

void ScriptActions::doUnitReceiveUpgrade(Parameter *unit, const AsciiString &upgradeName)
{
	Object *obj = TheScriptEngine->getUnitNamed(unit);
	if (obj == 0)
		return;
	const UpgradeTemplate *upgrade = TheUpgradeCenter->findUpgrade(upgradeName);
	if (upgrade == 0)
		return;
	if ((obj->m_p04->m_flag115 & 0x20) != 0)
	{
		Rva0028C197Target *target = (Rva0028C197Target *)obj->rva0028C197();
		if (target == 0)
			return;
		if (target->slot45(upgrade))
			return;
		target->slot46(upgrade, 0);
	}
	else
	{
		obj->rva00293077(upgrade);
	}
}
