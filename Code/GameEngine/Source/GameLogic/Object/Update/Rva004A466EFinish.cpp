// cl: /O1 /DNDEBUG /MD
// StructureCollapseUpdate::onDie retail body 0x004A466E, 81 bytes.
// The object's Module base holds m_moduleData at +4 (this-0x1c) and m_object at
// +8 (this-0x18) relative to the behavior subobject at +0x20; beginStructureCollapse
// is called on the full object at this-0x20. Object m_ai is at +0x258. BFME2
// PlayerMaskType is 32-bit (0xfffff).
class DamageInfo;

class AIUpdateInterface
{
public:
	void markAsDead();
};

class Object;

class GameLogic
{
public:
	void deselectObject(Object *obj, unsigned int mask, bool affectClient);
};

extern GameLogic *TheGameLogic;

class DieMuxData
{
public:
	bool isDieApplicable(const Object *obj, const DamageInfo *damageInfo) const;
};

struct StructureCollapseUpdateModuleData
{
	char m_pad[8];
	DieMuxData m_dieMuxData;
};

class StructureCollapseUpdate
{
public:
	StructureCollapseUpdate();
	virtual void onDie(const DamageInfo *damageInfo);
protected:
	void beginStructureCollapse(const DamageInfo *damageInfo);	// protected, as rowed (StructureCollapseUpdateUpdate.cpp)
};

struct SCUView
{
	StructureCollapseUpdateModuleData *m_moduleData; // +0  => this-0x1c
	Object *m_object;                                // +4  => this-0x18
};

struct ObjectView
{
	char m_pad[0x258];
	AIUpdateInterface *m_ai;
};

// ?StructureCollapseUpdate::StructureCollapseUpdate present-unmatched
StructureCollapseUpdate::StructureCollapseUpdate()
{
}

void StructureCollapseUpdate::onDie(const DamageInfo *damageInfo)
{
	SCUView *v = (SCUView *)((char *)this - 0x1c);
	Object *obj = v->m_object;
	StructureCollapseUpdateModuleData *d = v->m_moduleData;
	if (!d->m_dieMuxData.isDieApplicable(obj, damageInfo))
		return;

	AIUpdateInterface *ai = ((ObjectView *)v->m_object)->m_ai;
	if (ai)
		ai->markAsDead();

	// deselect this object for all players.
	TheGameLogic->deselectObject(v->m_object, 0xfffff, true);

	((StructureCollapseUpdate *)((char *)this - 0x20))->beginStructureCollapse(damageInfo);
}
