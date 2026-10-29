// cl: -O1 -arch:SSE -G7 -Ireference/open-bfme-1/game/GameEngine/Source/Common /I. /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /D_STLP_USE_STATIC_LIB /D_CRTIMP=
// stlport
#include "Code/GameEngine/Include/GameLogic/ScriptActionsBFME2.h"
// Open-BFME5 conversions.
//
// ?bfmeGoFGE@@YGXPAX00@Z, retail 0x003C38CA, 37 bytes. Both callee identities
// come from retail's own REL32 displacements and are already rowed: the call at
// +0x0B lands on 0x003588E7 (?getUnitNamed@ScriptEngine@@QAEPAVObject@@PAVParameter@@@Z)
// through the ScriptEngine singleton (0x0132116C in the donor), formerly spelled
// g_Va009FE16C, and the call at +0x1E on 0x0023DB0E
// (?setStatus@Object@@QAEXW4ObjectStatusTypes@@_N@Z).

enum ObjectStatusTypes
{
	OBJECT_STATUS_NONE,
	OBJECT_STATUS_DESTROYED,
	OBJECT_STATUS_CAN_ATTACK,
	OBJECT_STATUS_UNDER_CONSTRUCTION,
	OBJECT_STATUS_UNSELECTABLE,
	OBJECT_STATUS_NO_COLLISIONS,
	OBJECT_STATUS_NO_ATTACK,
	OBJECT_STATUS_AIRBORNE_TARGET,
	OBJECT_STATUS_PARACHUTING,
	OBJECT_STATUS_REPULSOR,
	OBJECT_STATUS_HIJACKED,
	OBJECT_STATUS_AFLAME,
	OBJECT_STATUS_BURNED,
	OBJECT_STATUS_WET,
	OBJECT_STATUS_IS_FIRING_WEAPON,
	OBJECT_STATUS_BRAKING,
	OBJECT_STATUS_STEALTHED,
	OBJECT_STATUS_DETECTED,
	OBJECT_STATUS_CAN_STEALTH,
	OBJECT_STATUS_SOLD,
	OBJECT_STATUS_UNDERGOING_REPAIR,
	OBJECT_STATUS_RECONSTRUCTING,
	OBJECT_STATUS_MASKED,
	OBJECT_STATUS_IS_ATTACKING,
	OBJECT_STATUS_IS_USING_ABILITY,
	OBJECT_STATUS_IS_AIMING_WEAPON,
	OBJECT_STATUS_NO_ATTACK_FROM_AI,
	OBJECT_STATUS_IGNORING_STEALTH,
	OBJECT_STATUS_IS_CARBOMB,
	OBJECT_STATUS_DECK_HEIGHT_OFFSET
};

class Parameter;

class Object
{
public:
	// Rowed Object::setStatus(ObjectStatusTypes, bool), 0x0023DB0E.
	void setStatus(ObjectStatusTypes status, bool value);
};

#include "../../Include/GameLogic/ScriptEngine.h"

extern class ScriptEngine *TheScriptEngine;

void ScriptActions::bfmeGoFGE(void *a, void *b, bool c)
{
	Object *object = TheScriptEngine->getUnitNamed((Parameter *)a);

	if (object)
		object->setStatus((ObjectStatusTypes)(int)b, c);
}