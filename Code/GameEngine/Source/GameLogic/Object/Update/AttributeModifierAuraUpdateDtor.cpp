// cl: /DNDEBUG /MD /GX
//
// ??1AttributeModifierAuraUpdate@@UAE@XZ, retail 0x0049B6DD, 115 bytes.
//
// Identity: the rowed ??_GAttributeModifierAuraUpdate 0x0049B884 (slot 0 of
// vtable 0x00C50D2C, the table the rowed ctor 0x0049B560 installs) calls
// it; the body re-stores the ctor's four vptrs (+0x00 0x00C50D2C, +0x0C the
// shared 0x00C49F78, +0x10 0x00C50D20, +0x20 0x00C50CD8) and ends in the
// pinned UpdateModule base destructor 0x0024A797.
//
// BFME 2 adds a teardown step the BFME 1 donor's empty destructor lacks:
// when the object's template has bit 0 of its +0x11B flags set, it hands
// TheTerrainLogic (0x00DFEC50) the object's position (+0x38), the module
// data's radius (+0x1C) and the object ID (+0x74) through the unnamed
// TerrainLogic member 0x00282CFB (pinned under an address name).
// Base layout follows the ctor TU: Module (+0 vptr, +4 module data, +8
// object), interface vptrs at +0x0C/+0x10, UpdateModule data to +0x20, the
// upgrade mux base at +0x20.

typedef float Real;
typedef unsigned int ObjectID;

struct Coord3D
{
	Real x, y, z;
};

class ModuleData;

struct AttributeModifierAuraUpdateModuleData
{
	unsigned char m_pad00[0x1C];
	Real m_range; // +0x1C
};

struct Rva0049B6DDTemplate
{
	unsigned char m_pad000[0x11B];
	unsigned char m_flags11B; // +0x11B
};

class Object
{
public:
	const Rva0049B6DDTemplate *getTemplate() const { return m_template; }
	const Coord3D *getPosition() const { return &m_position; }
	ObjectID getID() const { return m_id; }

private:
	void *m_vtable; // +0x00
	const Rva0049B6DDTemplate *m_template; // +0x04
	unsigned char m_pad08[0x38 - 0x08];
	Coord3D m_position; // +0x38
	unsigned char m_pad44[0x74 - 0x44];
	ObjectID m_id; // +0x74
};

class TerrainLogic
{
public:
	void rva00282CFB(const Coord3D *pos, Real radius, ObjectID id);
};

extern TerrainLogic *TheTerrainLogic;

class Module
{
public:
	virtual ~Module();

protected:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};

class BehaviorModuleInterface
{
public:
	virtual void behaviorSlot();
};

class UpdateModuleInterface
{
public:
	virtual void updateSlot();
};

class UpdateModule : public Module, public BehaviorModuleInterface, public UpdateModuleInterface
{
public:
	virtual ~UpdateModule();

private:
	unsigned int m_nextCallFrameAndPhase; // +0x14
	int m_indexInLogic; // +0x18
	int m_reserved1C; // +0x1C
};

class UpgradeMux
{
public:
	virtual void upgradeSlot();

private:
	unsigned int m_executed; // +0x24
};

class AttributeModifierAuraUpdate : public UpdateModule, public UpgradeMux
{
public:
	virtual ~AttributeModifierAuraUpdate();
};

AttributeModifierAuraUpdate::~AttributeModifierAuraUpdate()
{
	Object *obj = m_object;
	const AttributeModifierAuraUpdateModuleData *data = (const AttributeModifierAuraUpdateModuleData *)m_moduleData;
	if (obj->getTemplate()->m_flags11B & 1)
	{
		TheTerrainLogic->rva00282CFB(obj->getPosition(), data->m_range, obj->getID());
	}
}
