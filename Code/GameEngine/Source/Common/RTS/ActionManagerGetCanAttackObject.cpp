// cl: /DNDEBUG /MD /EHsc
//
// Bodies ported from Open-BFME-1's
// GameEngine/Source/Common/RTS/ActionManagerGetCanAttackObject.cpp (donor
// revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1).
// Compiled that way each body below places uniquely on unclaimed game.dat
// .text by masked whole-.text search, and ./build.sh reproduces it byte for
// byte: bfmeContainedAttackVisitor originally placed at 0x0041B925 (37B). Callee addresses are read
// off retail's call sites (reverse/symbols.csv). Only the placed bodies are
// carried; the donor's other definitions are omitted.
// Native callback 0x0041B918..0x0041B94A is 50 bytes: the former 37-byte
// row covered only its fall-through tail. The preceding producer guard calls
// Object::rva002931BA, and both its taken branch and the callback body share
// the RET at 0x0041B949. Retarget the row to this complete boundary.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

#define TRUE true

enum KindOfType
{
	KINDOF_STRUCTURE = 7,
	KINDOF_SPAWNS_ARE_THE_WEAPONS = 83
};

#include "../../../../../reference/open-bfme-1/game/GameEngine/Source/GameLogic/command_source_type.h"

enum AbleToAttackType
{
	ATTACK_NEW_TARGET = 0
};

enum CanAttackResult
{
	ATTACKRESULT_NOT_POSSIBLE,
	ATTACKRESULT_INVALID_SHOT,
	ATTACKRESULT_POSSIBLE_AFTER_MOVING,
	ATTACKRESULT_POSSIBLE
};

class Object;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	float x;
	float y;
	float z;
};

typedef void (*BfmeContainIterateFunc)( Object *obj, void *userData );

// BFME's ContainModuleInterface places iterateContained at vtable +0xfc.
// Only that slot is named; the preceding entries preserve the ABI slice.
class BfmeContainModule
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot0a(); virtual void slot0b();
	virtual void slot0c(); virtual void slot0d(); virtual void slot0e(); virtual void slot0f();
	virtual void slot10(); virtual void slot11(); virtual void slot12(); virtual void slot13();
	virtual void slot14(); virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot1a(); virtual void slot1b();
	virtual void slot1c(); virtual void slot1d(); virtual void slot1e(); virtual void slot1f();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot2a(); virtual void slot2b();
	virtual void slot2c(); virtual void slot2d(); virtual void slot2e(); virtual void slot2f();
	virtual void slot30(); virtual void slot31(); virtual void slot32(); virtual void slot33();
	virtual void slot34(); virtual void slot35(); virtual void slot36(); virtual void slot37();
	virtual void slot38(); virtual void slot39(); virtual void slot3a(); virtual void slot3b();
	virtual void slot3c(); virtual void slot3d(); virtual void slot3e();
	virtual void iterateContained( BfmeContainIterateFunc func, void *userData, Bool reverse );
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Thing.h
class Thing
{
public:
	Bool isKindOf( KindOfType kind ) const;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpawnBehavior.h
class SpawnBehaviorInterface
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual Object *getClosestSlave( const Coord3D *pos );
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object : public Thing
{
public:
	Bool isEffectivelyDead() const
	{
		return (*(const unsigned char *)((const char *)this + 0x344) & 1) != 0;
	}

	Bool rva002931BA();
	Bool isAbleToAttack() const;
	CanAttackResult getAbleToAttackSpecificObject( AbleToAttackType attackType,
		const Object *target, CommandSourceType commandSource ) const;
	SpawnBehaviorInterface *getSpawnBehaviorInterface() const;
	const Coord3D *getPosition() const
	{
		return (const Coord3D *)((const char *)this + 0x38);
	}

	BfmeContainModule *getContain() const
	{
		return *(BfmeContainModule **)((const char *)this + 0x1fc);
	}
};

class ActionManager;

struct BfmeContainedAttackContext
{
	CanAttackResult result;
	ActionManager *manager;
	const Object *target;
	CommandSourceType commandSource;
	AbleToAttackType attackType;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ActionManager.h
class ActionManager
{
public:
	CanAttackResult bfmeGetCanAttackContained( const Object *obj,
		const Object *objectToAttack, CommandSourceType commandSource,
		AbleToAttackType attackType );
	CanAttackResult getCanAttackObject( const Object *obj,
		const Object *objectToAttack, CommandSourceType commandSource,
		AbleToAttackType attackType );
};

void bfmeContainedAttackVisitor( Object *obj, void *userData )
{
	if (obj->rva002931BA())
		return;
	BfmeContainedAttackContext *context =
		(BfmeContainedAttackContext *)userData;
	CanAttackResult result = context->manager->getCanAttackObject(
		obj, context->target, context->commandSource, context->attackType);
	if (result == ATTACKRESULT_POSSIBLE)
		context->result = result;
}


