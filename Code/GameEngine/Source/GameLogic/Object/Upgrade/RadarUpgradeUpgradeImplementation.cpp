// cl: /DNDEBUG /MD
//
// RadarUpgrade::upgradeImplementation, retail 0x004B488F (68 bytes): slot 10
// of the +0x10 UpgradeMux vtable 0x00C57848 installed by the matched
// RadarUpgrade ctor. The body is the Zero Hour RadarUpgrade.cpp one: the
// controlling player's addRadar (pinned 0x002AA91F) with the module data
// disable-proof bool (+0x118), then the object's RadarUpdate module, found by
// the RadarUpdate name key, extends its radar (rowed 0x004A0D0F).
// /G7: retail pushes the bool without the P6 partial-register xor.
//
// RadarUpgrade::onCapture, retail 0x004B4828 (103 bytes): primary-vtable
// slot 9 of 0x00857890 (slots 8/9 are 0x004B47DB/0x004B4828, then DisableProof
// field table at 0x008578C0 with parseBool 0x002E850 and offset 0x118).
// BFME1 donor RadarUpgradeOnCapture.cpp (rev 6583b3c1): isAlreadyUpgraded
// gate (mux slot0 at +0x10), disabledMask any() gate (Object+0x1C8 via rowed
// BitFlags<11>::any 0x0023C58B), oldOwner removeRadar (rowed 0x002AA9C2) +
// setUpgradeExecuted(false), newOwner addRadar (rowed 0x002AA91F) +
// setUpgradeExecuted(true), all with ModuleData DisableProof bool +0x118.
// BFME2 deltas: ModuleData pad 0x118 (not donor 0x70), mux slot9 (not donor
// slot8). Sibling 0x004B47DB already matched elsewhere; dumped both tables
// (0x00857890 full 12-slot + interior 0x008578A8) to prove adjacency but
// NOT co-landed without identity proof.
class Thing;

class ModuleData;

class Object;

typedef bool Bool;

class MultiIniFieldParse;

class RadarUpgradeModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
	unsigned char m_pad[0x118];
	bool m_isDisableProof; // +0x118
};

class BehaviorModule
{
public:
	virtual void behaviorModuleAnchor();

protected:
	Object *getObject() const { return m_object; }
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};

class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};

class UpgradeMux
{
public:
	virtual Bool isAlreadyUpgraded() const = 0;
	virtual void m01() = 0;
	virtual void m02() = 0;
	virtual void m03() = 0;
	virtual void m04() = 0;
	virtual void m05() = 0;
	virtual void m06() = 0;
	virtual void m07() = 0;

protected:
	virtual void upgradeRemovalImplementation() = 0;
	virtual void setUpgradeExecuted(Bool executed) = 0;
	virtual void upgradeImplementation() = 0;

private:
	bool m_upgradeExecuted;
};

class ModuleInterface
{
public:
	virtual void moduleInterfaceAnchor();
};

class UpgradeModule : public BehaviorModule,
	public BehaviorModuleInterface,
	public UpgradeMux,
	public ModuleInterface
{
public:
	UpgradeModule( Thing *thing, const ModuleData *moduleData );
};

enum NameKeyType
{
	NK_UNKNOWN = 0
};

template<unsigned int N> class BitFlags
{
public:
	bool any() const;
};

class Player
{
public:
	void removeRadar(bool b);
	void addRadar(bool disableProof);
};

class Module;

class UpdateModule;

class Object
{
public:
	Player *getControllingPlayer() const;
	UpdateModule *findUpdateModule(NameKeyType key) const { return (UpdateModule *)findModule(key); }
protected:
	Module *findModule(NameKeyType key) const;
private:
	char m_pad[0x1C8];
public:
	BitFlags<11> m_flags1C8;
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class RadarUpdate
{
public:
	void extendRadar();
};

class RadarUpgrade : public UpgradeModule
{
public:
	RadarUpgrade( Thing *thing, const ModuleData *moduleData );
public:
	virtual NameKeyType getModuleNameKey() const;
	virtual void onCapture(Player *oldOwner, Player *newOwner);
protected:
	virtual void upgradeImplementation();
private:
	const RadarUpgradeModuleData *getRadarUpgradeModuleData() const { return (const RadarUpgradeModuleData *)m_moduleData; }
};

// Object +0x1C8 as byte-pointer arithmetic on the Object pointer, so cl 7.1
// emits mov ecx,[reg+8] / add ecx,0x1C8 (not lea) like retail 0x004B4828.
#define OBJECT_DISABLED_MASK(object) \
	((const BitFlags<11> *)((const char *)(object) + 0x1C8))
void RadarUpgrade::upgradeImplementation()
{
	const RadarUpgradeModuleData *data = getRadarUpgradeModuleData();
	Player *player = getObject()->getControllingPlayer();

	// update the radar count
	player->addRadar(data->m_isDisableProof);

	// find the radar update module of this object
	NameKeyType radarUpdateKey = TheNameKeyGenerator->nameToKey("RadarUpdate");
	RadarUpdate *radarUpdate = (RadarUpdate *)getObject()->findUpdateModule(radarUpdateKey);
	if (radarUpdate)
		radarUpdate->extendRadar();
}
void RadarUpgrade::onCapture(Player *oldOwner, Player *newOwner)
{
	const RadarUpgradeModuleData *data = getRadarUpgradeModuleData();
	if (!isAlreadyUpgraded())
		return;
	if (OBJECT_DISABLED_MASK(m_object)->any())
		return;
	if (oldOwner)
	{
		oldOwner->removeRadar(data->m_isDisableProof);
		setUpgradeExecuted(false);
	}
	if (newOwner)
	{
		newOwner->addRadar(data->m_isDisableProof);
		setUpgradeExecuted(true);
	}
}
