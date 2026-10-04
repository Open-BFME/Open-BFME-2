// cl: /O1 /DNDEBUG /MD
//
// CommandPointsUpgrade::upgradeImplementation, retail 0x004B86AE (44 bytes),
// and upgradeRemovalImplementation, retail 0x004B86DA (54 bytes): slots 10
// and 8 of the +0x10 UpgradeMux vtable 0x00C59060 (the recipe of
// RemoveUpgradeUpgradeRemovalImplementation.cpp). Both work on the
// controlling Player's +0x60 holder, keyed by the module data's +0x118 value
// and our Object's ID: applying adds an entry carrying the data's +0x11C
// block (0x002A77C1), removal, only when the upgrade is in effect (mux slot
// 0), drops the entry (0x002A7611, which searches the holder's +0x20 vector
// of 12-byte {value, ID, ...} records) and clears the executed flag (mux slot
// 9). Neither touches the UpgradeModule condition state. The holder's two
// members are pinned by address on these call sites.
typedef bool Bool;
class ModuleData;
enum ObjectID
{
	INVALID_ID = 0
};
class Rva002A7611Holder
{
public:
	void rva002A77C1(int value, ObjectID id, const void *block);
	void rva002A7611(int value, ObjectID id);
};
class Player
{
public:
	Rva002A7611Holder *getRva060() { return &m_60; }
private:
	unsigned char m_pad00[0x60];
	Rva002A7611Holder m_60; // +0x60
};
class Object
{
public:
	Player *getControllingPlayer() const;
	unsigned char m_pad00[0x74];
	ObjectID m_id; // +0x74
};
struct CommandPointsUpgradeModuleData
{
	unsigned char m_pad00[0x118];
	int m_118; // +0x118
	unsigned char m_11C[4]; // +0x11C
};
class ObjectModuleBase
{
public:
	virtual ~ObjectModuleBase();
protected:
	Object *getObject() const { return m_object; }
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};
class UpgradeModuleInterface
{
public:
	virtual void upgradeModuleInterfaceAnchor();
};
// UpgradeMux interface at +0x10: slot 0 isAlreadyUpgraded, slot 8
// upgradeRemovalImplementation, slot 9 setUpgradeExecuted, slot 10
// upgradeImplementation.
class UpgradeMuxIface
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
};
class UpgradeModule : public ObjectModuleBase, public UpgradeModuleInterface, public UpgradeMuxIface
{
};
class CommandPointsUpgrade : public UpgradeModule
{
protected:
	virtual void upgradeRemovalImplementation();
	virtual void upgradeImplementation();
	const CommandPointsUpgradeModuleData *getData() const
	{
		return (const CommandPointsUpgradeModuleData *)m_moduleData;
	}
};
void CommandPointsUpgrade::upgradeImplementation()
{
	Object *object = getObject();
	Player *player = object->getControllingPlayer();
	const CommandPointsUpgradeModuleData *data = getData();
	player->getRva060()->rva002A77C1(data->m_118, object->m_id, data->m_11C);
}
void CommandPointsUpgrade::upgradeRemovalImplementation()
{
	if (isAlreadyUpgraded())
	{
		Object *object = getObject();
		Player *player = object->getControllingPlayer();
		player->getRva060()->rva002A7611(getData()->m_118, object->m_id);
		setUpgradeExecuted(false);
	}
}
