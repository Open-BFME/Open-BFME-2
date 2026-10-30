// cl: /MD
//
// ?rva004B8B0F@OathbreakersFadeAwayBehavior@@QAEXXZ, retail 0x004B8B0F, 50 bytes.
// Update-module helper: if the Object at +8 is FAERIE_FIRE (0x26) return;
// else if its AI at +0x258 is null return; else issue AI command 0x31 with
// value 0 source 2 via the +0x20 subobject then setSelectable(false).
// Evidence: testStatus 0x0004E536 plus rowed rva0045003E 0x0045003E plus
// pinned setSelectable 0x0028B76D; caller at 0x004B8B6A via lea ecx,[esi-0x10];
// Object+0x258 AI plus +0x20 command subobject per ScriptActions_doNamedExitAll.

typedef bool Bool;

enum ObjectStatusTypes
{
	OBJECT_STATUS_FAERIE_FIRE = 0x26
};

enum CommandSourceType
{
	CMD_FROM_AI = 2
};

class Object;

class AICommandInterface
{
public:
	void rva0045003E(int value, CommandSourceType cmdSource);
};

class AIUpdateInterface
{
public:
	char m_pad00[0x20];
	AICommandInterface m_command;
};

class Object
{
public:
	Bool testStatus(ObjectStatusTypes bit) const;
	void setSelectable(Bool selectable);
	AIUpdateInterface *getAIUpdateInterface();
};

#include "../../Include/Common/ObjectModule.h"

class BehaviorModuleInterface { public: virtual void behaviorSlot(); };
class UpdateModuleInterface { public: virtual void updateSlot(); };

class UpdateModule : public ObjectModule,
	public BehaviorModuleInterface, public UpdateModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *data);
	virtual ~UpdateModule();
	void xfer(Xfer *xfer);

private:
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_updateState;
};

class OathbreakersFadeAwayBehavior : public UpdateModule
{
public:
	const char *name() const;
	virtual NameKeyType getModuleNameKey() const;
	void rva004B8B0F();

protected:
	virtual void xfer(Xfer *xfer);

private:
	bool m_20;
	float m_24;
};

void OathbreakersFadeAwayBehavior::rva004B8B0F()
{
	Object *obj = m_object;
	if (obj->testStatus(OBJECT_STATUS_FAERIE_FIRE))
		return;
	AIUpdateInterface *ai = *(AIUpdateInterface **)((char *)obj + 0x258);
	if (!ai)
		return;
	ai->m_command.rva0045003E(0, CMD_FROM_AI);
	obj->setSelectable(false);
}
