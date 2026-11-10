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

#include "../../../../../Libraries/Include/Lib/Coord3D.h"

class ModuleData;

#include "../../../../Include/GameLogic/Module/AttributeModifierAuraUpdateModuleData.h"

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

#include "../../../../Include/GameLogic/TerrainLogic.h"

extern TerrainLogic *TheTerrainLogic;

#include "../../../../Include/Common/Module.h"
#include "../../../../Include/Common/ObjectModule.h"

#include "../../../../Include/GameLogic/Module/BehaviorModule.h"

#include "../../../../Include/GameLogic/Module/UpdateModule.h"


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
public:
	// retail slot 4: the rowed ?getModuleNameKey@AttributeModifierAuraUpdate@@UBE?AW4NameKeyType@@XZ
	virtual NameKeyType getModuleNameKey() const;
protected:
	// retail vftable slot: the rowed override
	virtual void xfer(Xfer *);
public:
	// retail vftable slot: the rowed override
	virtual UpdateSleepTime update();
public:
	// BehaviorModuleInterface table 0x00C49F78 (+0x0C): the receiver converted to the
	// class's own interface, the null-preserving casts retail folds across the module family.
	virtual UpgradeModuleInterface *getUpgrade();			// slot 10: retail 0x004543A9, the +0x20 UpgradeMux
};

AttributeModifierAuraUpdate::~AttributeModifierAuraUpdate()
{
	Object *obj = getObject();
	const AttributeModifierAuraUpdateModuleData *data = reinterpret_cast<const AttributeModifierAuraUpdateModuleData *>(getModuleData());
	if (obj->getTemplate()->m_flags11B & 1)
	{
		TheTerrainLogic->rva00282CFB(obj->getPosition(), data->m_range, obj->getID());
	}
}

// Placeholder virtuals this unit's vftables hold.  In retail each such slot
// holds a rowed function; the vftable's address is proven by the vptr stores in
// the matched destructors, so bind the placeholder to that row's name.
#pragma comment(linker, "/alternatename:?upgradeSlot@UpgradeMux@@UAEXXZ=?Is_Valid@RegistryClass@@QAE_NXZ")

// Slot 10 of AttributeModifierAuraUpdate's BehaviorModuleInterface table 0x00C49F78: retail 0x004543A9, the +0x20 UpgradeMux.
UpgradeModuleInterface *AttributeModifierAuraUpdate::getUpgrade()
{
	return reinterpret_cast<UpgradeModuleInterface *>(static_cast<UpgradeMux *>(this));
}
