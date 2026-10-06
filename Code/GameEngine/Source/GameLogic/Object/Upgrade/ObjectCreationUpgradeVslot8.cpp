// cl: /DNDEBUG /MD /EHsc
//
// ?rva004B463C@ObjectCreationUpgrade@@QAEXXZ, retail 0x004B463C, 189 bytes.
// Vslot 8 of vtable 0x00857660 for ObjectCreationUpgrade (ctor 0x004B40A6).
// Calls slot 9 with 0, stores 0x3fffffff at +0x28 and 0 at +0x2C, checks
// ModuleData at +0x0C (byte +0x13C, ints +0x140/+0x144), static SlaveWatcher
// key via TheNameKeyGenerator, findModule on Object at +0x10, data-length
// as ObjectID, TheGameLogic find, kill and model-condition update.
// Evidence: callees rowed, vtable slot, string SlaveWatcherBehavior.
enum NameKeyType
{
	NK_UNKNOWN = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class Module
{
};

class NetWrapperCommandMsg
{
public:
	unsigned getDataLength();
};

enum DamageType
{
	DT_DAMAGE_8 = 8
};

enum DeathType
{
	DT_DEATH_0 = 0
};

enum ModelConditionFlagType
{
	MCF_0 = 0
};

enum ObjectID
{
	OID_NONE = -1
};

class Object
{
protected:
	Module *findModule(NameKeyType key) const;
	friend class ObjectCreationUpgrade;
public:
	void kill(DamageType damageType, DeathType deathType);
	void setSpecialModelConditionState(ModelConditionFlagType flag, unsigned value);
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;

class UpgradeData0C
{
public:
	unsigned char m_pad[0x13C];
	unsigned char m_flag13C;
	unsigned char m_pad13D[3];
	ModelConditionFlagType m_cond140;
	unsigned m_val144;
};

class ObjectCreationUpgrade
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09(int x);
	void rva004B463C();
private:
	char m_pad04[0x0C - 0x04];
	UpgradeData0C *m_data0C;
	Object *m_object10;
	char m_pad14[0x28 - 0x14];
	int m_status28;
	bool m_flag2C;
};

// ?rva004B463C@ObjectCreationUpgrade@@QAEXXZ
void ObjectCreationUpgrade::rva004B463C()
{
	v09(0);
	UpgradeData0C *data = m_data0C;
	m_status28 = 0x3fffffff;
	m_flag2C = false;
	if (!data)
		return;
	if (!data->m_flag13C)
		return;
	static NameKeyType key = TheNameKeyGenerator->nameToKey("SlaveWatcherBehavior");
	Module *mod = m_object10->findModule(key);
	if (!mod)
		return;
	unsigned len = ((NetWrapperCommandMsg *)mod)->getDataLength();
	Object *target = TheGameLogic->findObjectByID((ObjectID)len);
	if (!target)
		return;
	target->kill((DamageType)8, (DeathType)0);
	if (data->m_cond140 == (ModelConditionFlagType)-1)
		return;
	target->setSpecialModelConditionState(data->m_cond140, data->m_val144);
}
