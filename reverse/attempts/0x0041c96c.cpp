// ?rva0041C96C@ActionManager@@QAE_NPBVObject@@0W4CommandSourceType@@@Z
// partial score=0.99 date=2026-10-08
// cl: /O1 /arch:SSE /G7 /MD /GX
// Banked native 41C96C 88B target predicate: compiles to 89B, final AND
// EAX,1 instead of AND AL,1. Surrounding bytes and all callees agree.
// Reference canSnipeVehicle is only a semantic lead; its original name
// and class ownership remain unconfirmed. Native has two Object pointers,
// a command-source stack argument, unused ECX and a normalized AL result.
// The complete boundary is RET12 ending at 41C9C4.
#include "../reference/open-bfme-1/game/GameEngine/Source/GameLogic/command_source_type.h"
enum CellShroudStatus { ACTION_OBJECT_SHROUD_FOGGED = 3 };
enum Relationship { ENEMIES, NEUTRAL, ALLIES };
class Player;
class Object
{
public:
	Player *getControllingPlayer() const;
	CellShroudStatus getShroudStatusForPlayer(int) const;
	Relationship getRelationship(const Object *) const;
};
class ActionManager
{
public:
	bool rva0041C96C(const Object *, const Object *, CommandSourceType);
};
struct ShroudPlayerView
{
	char pad[0x54];
	int index;
	char pad58[4];
	int type;
};

static __declspec(noinline) bool isObjectShroudedForAction(
	const Object *a, const Object *b, CommandSourceType c)
{
	if (b) {
		int id = *reinterpret_cast<const int *>(reinterpret_cast<const char *>(b) + 0x74);
		if (id >= 0x05f5e0fc && id <= 0x05f5e0ff)
			return false;
	}
	if (a && b && a->getControllingPlayer()) {
		if (reinterpret_cast<ShroudPlayerView *>(a->getControllingPlayer())->type == 0 &&
			c != CMD_FROM_SCRIPT &&
			b->getShroudStatusForPlayer(reinterpret_cast<ShroudPlayerView *>(
				a->getControllingPlayer())->index) >= ACTION_OBJECT_SHROUD_FOGGED)
			return true;
	}
	return false;
}

static __forceinline bool actionTargetStatusBit6(const Object *target)
{
	return (*reinterpret_cast<const unsigned int *>(reinterpret_cast<const char *>(target) + 0x94) >> 6) & 1;
}
// BFME1 ba7ddda7 canSnipeVehicle is a semantic lead, but native callers
// do not establish that name. Native omits the donor's vehicle/drone tests;
// tests +94 bit6 and +1C8 bit5 after the enemy and visibility checks.
// ECX is unused. ActionManager ownership is inferred from the adjacent
// action family. Complete 88-byte control flow ends at 41C9C4.
bool ActionManager::rva0041C96C(
	const Object *obj, const Object *target, CommandSourceType source)
{
	if (!obj || !target)
		return false;
	if (*reinterpret_cast<const unsigned char *>(reinterpret_cast<const char *>(target) + 0x438) & 1)
		return false;
	if (isObjectShroudedForAction(obj, target, source))
		return false;
	if (obj->getRelationship(target) != ENEMIES)
		return false;
	if (actionTargetStatusBit6(target))
		return false;
	unsigned char flags = *reinterpret_cast<const unsigned char *>(reinterpret_cast<const char *>(target) + 0x1c8);
	return static_cast<unsigned char>(~static_cast<unsigned char>(flags >> 5)) & 1;
}
