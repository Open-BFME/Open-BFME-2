// cl: /MD /EHsc
// ??1TurretAI@@MAE@XZ retail 0x004D86C1 86B
// Zero Hour TurretAI::~TurretAI shape: stopRotOrPitchSound (the rowed
// ?rva004D82F6@TurretAI 0x004D82F6) then delete the turret state machine at
// +0x14 and clear it. Own vptrs C60D78 (+0) and C60D64 (+4, an interface base
// with no dtor); the inline Snapshot base dtor restores BBB554.
// Retail deletes through the slot-0 deleting dtor with flag 0 followed by the
// global ??3@YAXPAX@Z (a global-scope delete). Identity from the pin (slot 2
// of vtable 0x00C60D78 returns "TurretAI"). The class view is the TU's.

#include "../../../../Include/Common/StateMachine.h"
#include "../../../Common/GameLogicObjectLookupView.h"

extern GameLogic *TheGameLogic;

// TurretAI.cpp TU view (one spelling in every file of the TU). The
// constructor 0x004D85B6 stores the Snapshot table 0x00BBB554 and then
// 0x00C60D78 at +0x00 and 0x00C60D64 at +0x04. 0x00C60D78 holds the deleting
// destructor 0x004D8974, loadPostProcess 0x004D80D4, the "TurretAI" name
// getter 0x004D86BB and xfer 0x004D7FAD (Snapshot's slots); 0x00C60D64 holds
// notifyFired 0x004D81D2 (+0x37 from the +0x04 base is +0x3B) and
// notifyNewVictimChosen 0x004D8B3F (ecx-4 before setTurretTargetObject).
// Field names follow the constructor, xfer 0x004D7FAD and the target setters.
class Team;
class Object;
class Xfer;
class Weapon;
class AIUpdateInterface;
class TurretAI;
struct Coord3D;
struct EmitVtableTag;

enum WeaponSlotType
{
	WEAPONSLOT_PRIMARY = 0,
	WEAPONSLOT_COUNT = 6
};

enum WhichTurretType
{
	TURRET_INVALID = -1,
	TURRET_MAIN = 0,
	TURRET_ALT,
	MAX_TURRETS
};

enum WeaponChoiceCriteria
{
	WEAPON_CHOICE_CRITERIA_5 = 5
};

enum CommandSourceType
{
	CMD_FROM_PLAYER,
	CMD_FROM_SCRIPT,
	CMD_FROM_AI
};

// Object as the TU's bodies read it: id +0x74, AI +0x258, team +0x304 and
// the effectively-dead bit at +0x438.
#include "../object.h"

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

// TurretAIData, 0x70 bytes as TurretAIData::TurretAIData (0x004D7E6C) fills it.
class INI;
class MultiIniFieldParse;
#include "../../../../Include/GameLogic/Module/TurretAI.h"

enum TurretStateType
{
	TURRETAI_IDLE = 0,
	TURRETAI_IDLESCAN = 1,
	TURRETAI_AIM = 2,
	TURRETAI_FIRE = 3,
	TURRETAI_RECENTER = 4,
	TURRETAI_HOLD = 5
};

enum { INVALID_STATE_ID = 999999 };

enum TurretTargetType
{
	TARGET_NONE = 0,
	TARGET_OBJECT = 1,
	TARGET_POSITION = 2
};

// StateMachine as the turret machine's table 0x00C609C8 shows it: Snapshot's
// slots 0-3, updateStateMachine 4 (0x004D7321), clear 5, resetToDefaultState
// 6, initDefaultState 7 (0x004D770F), setState 8, isInAttackState 11
// (0x002621B8), isInBusyState 12 (0x004D7309), 13 (0x004D7395) and the goal
// object setter 14; the current state at +0x04. setGoalPosition is 0x00262224.
#include "../../../../Include/Common/StateMachineClass.h"

// The 0x40-byte turret machine (vtable 0x00C609C8); getGoalObject is 0x004D7726.
#include "../../../../Include/GameLogic/Module/TurretStateMachine.h"

#include "../../../../Include/Common/TurretAINotifyBase.h"

// End of the TurretAI.cpp TU view.

TurretAI::~TurretAI()
{
	rva004D82F6();
	::delete m_turretStateMachine;
	m_turretStateMachine = 0;
}
