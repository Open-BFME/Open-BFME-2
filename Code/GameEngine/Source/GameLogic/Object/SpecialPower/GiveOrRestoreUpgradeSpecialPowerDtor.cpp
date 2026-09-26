// cl: /O1 /DNDEBUG /MD /EHsc
//
// ??1GiveOrRestoreUpgradeSpecialPower@@UAE@XZ, retail 0x004CD166, 83 bytes.
// Dtor restoring four vptrs (+0 +0x0C +0x10 +0x20) then destroying AsciiString
// at +0x8C via pinned ??1 StringBase at 0x00036410 and calling pinned base
// ??1Rva0044EF5E at 0x00451F45. Layout from rowed ctor 0x4CD0DC (Rva0044EF5E
// base size 0x20, +0x20 secondary, byte +0x88, string +0x8C). Vtable 0x0085FA40
// with slot 0 ??_G at 0x004CD332. Model follows FlammableUpdateDtor (4 vptrs).

class Thing;
class ModuleData;
class Object;
class DamageInfo;

template <typename T>
class StringBase
{
public:
	~StringBase();

private:
	T *m_data;
};

class BehaviorModuleBase
{
public:
	virtual void behaviorModuleBaseAnchor();
	const ModuleData *m_moduleData;
	Object *m_object;
};

class BehaviorModuleOther
{
public:
	virtual void behaviorModuleOtherAnchor();
};

class BehaviorModule : public BehaviorModuleBase, public BehaviorModuleOther
{
public:
	BehaviorModule(Thing *thing, const ModuleData *moduleData);
};

class UpdateModuleInterface
{
public:
	virtual void update();
};

class Rva0044EF5E : public BehaviorModule, public UpdateModuleInterface
{
public:
	Rva0044EF5E(Thing *thing, const ModuleData *moduleData);
	virtual ~Rva0044EF5E();

protected:
	unsigned m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_bfmeReserved;
};

class DamageModuleInterface
{
public:
	virtual void onDamage(DamageInfo *damageInfo);
};

class GiveOrRestoreUpgradeSpecialPower : public Rva0044EF5E, public DamageModuleInterface
{
public:
	virtual ~GiveOrRestoreUpgradeSpecialPower();

private:
	unsigned char m_pad24[0x88 - 0x24];
	unsigned char m_88;
	unsigned char m_pad89[3];
	StringBase<char> m_8C;
};

GiveOrRestoreUpgradeSpecialPower::~GiveOrRestoreUpgradeSpecialPower()
{
}
