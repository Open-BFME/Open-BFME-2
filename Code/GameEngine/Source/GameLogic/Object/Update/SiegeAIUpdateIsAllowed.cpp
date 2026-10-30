// cl: /DNDEBUG /MD
//
// SiegeAIUpdate::isAllowedToRespondToAiCommands, retail 0x004905D1 (60
// bytes): primary slot 148 of vtable 0x00C4D330, the slot the rowed
// AIUpdateInterface::isAllowedToRespondToAiCommands 0x0026734C fills in the
// base. After the base allows the command, a siege unit whose special power
// of type 0x2D exists but is not ready (interface slot 1, isReady in the Zero
// Hour order) only takes command 0x1B (AICMD_EVACUATE in the Zero Hour
// numbering).
typedef bool Bool;
class Object;
enum AICommandType
{
	AICMD_BFME_1B = 0x1B
};
struct AICommandParms
{
	AICommandType m_cmd;	// +0x00
};
enum SpecialPowerType
{
	SPECIAL_BFME_2D = 0x2D
};
class SpecialPowerModuleInterface
{
public:
	virtual void s00() = 0;
	virtual Bool isReady() const = 0;
};
class Object
{
public:
	SpecialPowerModuleInterface *findSpecialPowerModuleInterface(SpecialPowerType type) const;
};
enum NameKeyType
{
	NK_UNKNOWN = 0
};

class Thing;
class ModuleData;
class Object;
struct AICommandParms;
struct Coord3D;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};

// Module::m_moduleData is at +0x04; ObjectModule::m_object is at +0x08.
#include "../../../../Include/GameLogic/Module/BehaviorModule.h"

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update();
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
private:
	unsigned int m_nextCallFrameAndPhase; // +0x14
	int m_indexInLogic; // +0x18
	int m_reserved1C; // +0x1C
};

class AICommandInterface
{
public:
	virtual void aiDoCommand(const AICommandParms *parms);
};

class CollideModuleInterface
{
public:
	virtual void onCollide(Object *other, const Coord3D *loc, const Coord3D *normal);
};

class AIUpdateInterface : public UpdateModule, public AICommandInterface, public CollideModuleInterface
{
public:
	AIUpdateInterface(Thing *thing, const ModuleData *moduleData);
	virtual UpdateSleepTime update();
	virtual void aiDoCommand(const AICommandParms *parms);
	virtual void onCollide(Object *other, const Coord3D *loc, const Coord3D *normal);
	virtual Bool isAllowedToRespondToAiCommands(const AICommandParms *parms) const;

protected:
	virtual ~AIUpdateInterface();

private:
	unsigned char m_pad28[0x3E4 - 0x28];
};

class SiegeAIUpdate : public AIUpdateInterface
{
public:
	SiegeAIUpdate(Thing *thing, const ModuleData *moduleData);
	virtual ~SiegeAIUpdate();
	virtual NameKeyType getModuleNameKey() const;
	virtual Bool isAllowedToRespondToAiCommands(const AICommandParms *parms) const;
};
Bool SiegeAIUpdate::isAllowedToRespondToAiCommands(const AICommandParms *parms) const
{
	if (!AIUpdateInterface::isAllowedToRespondToAiCommands(parms))
		return false;
	SpecialPowerModuleInterface *sp = getObject()->findSpecialPowerModuleInterface(SPECIAL_BFME_2D);
	if (sp && !sp->isReady())
		return parms->m_cmd == AICMD_BFME_1B;
	return true;
}
