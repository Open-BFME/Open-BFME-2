// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/inputs/reference/shims/iniexception /Ireference/open-bfme-1/inputs/reference/shims/turretai /Ireference/open-bfme-1/inputs/reference/shims/aiupdatelayout /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
//
// ?privateFollowWaypointPathAsTeamExact@AIUpdateInterface@@MAEXPBVWaypoint@@W4CommandSourceType@@@Z
// retail 0x0026BA33, 81 bytes. Dedicated TU ported from the Open-BFME-1
// donor game/GameEngine/Source/GameLogic/Object/Update/AIUpdate.cpp (reference/open-bfme-1 @ 6d943426).
// The donor body does not place at BFME 1's flags; compiled /O1 it is
// byte-identical to retail once relocations are masked (unique hit on
// unclaimed .text). Only placed bodies are defined here (this one and
// privateFollowWaypointPathExact, retail 0x0026B987); the donor's other
// definitions are omitted.
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
#define __PLACEMENT_VEC_NEW_INLINE  // always.h/GameMemory.h define array placement-new themselves
// stlport
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////

// AIUpdate.cpp //
// Implementation of generic AI mechanisms
// Author: Michael S. Booth, 2001-2002
// Subsequently : John Ahlquist 2002 and a cast of thousands.

#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine
#include "Common/INIException.h"

#define DEFINE_LOCOMOTORSET_NAMES					// for TheLocomotorSetNames[]
#define DEFINE_AUTOACQUIRE_NAMES

#include "Common/ActionManager.h"
#include "Common/GameState.h"
#include "Common/CRCDebug.h"
#include "Common/GlobalData.h"
#include "Common/Player.h"
#include "Common/PlayerList.h"
#include "Common/RandomValue.h"
#include "Common/Team.h"
#include "Common/ThingFactory.h"
#include "Common/ThingTemplate.h"
#include "Common/Upgrade.h"
#include "Common/PerfTimer.h"
#include "Common/UnitTimings.h"
#include "Common/Xfer.h"
#include "Common/XferCRC.h"

#include "GameClient/ControlBar.h"
#include "GameClient/Drawable.h"
#include "GameClient/InGameUI.h"  // useful for printing quick debug strings when we need to

#include "GameLogic/AI.h"
#include "GameLogic/AIPathfind.h"
#include "GameLogic/Locomotor.h"
#include "GameLogic/Module/AIUpdate.h"
#include "GameLogic/Module/BodyModule.h"
#include "GameLogic/Module/ContainModule.h"
#include "GameLogic/Module/PhysicsUpdate.h"
#include "GameLogic/Module/ProneUpdate.h"
#include "GameLogic/Module/DeliverPayloadAIUpdate.h"
#include "GameLogic/Module/HackInternetAIUpdate.h"
#include "GameLogic/Module/HordeUpdate.h"
#include "GameLogic/Object.h"
#include "GameLogic/PartitionManager.h"
#include "GameLogic/PolygonTrigger.h"
#include "GameLogic/ScriptEngine.h"
#include "GameLogic/TurretAI.h"
#include "GameLogic/Weapon.h"
#include "Common/Radar.h"									// For TheRadar

#define SLEEPY_AI

extern unsigned char g_012F0239;
extern void *g_012ED4FC;
extern void j_0003a17a( void );
extern void j_00008a9e( void );
extern void j_00049413( void );
extern void j_000022bb( void );
extern const Real BfmeZeroRange;
extern Real g_bfmeDefaultBU;

typedef void (__cdecl *BFMEPathDebugLogFunction)( void *, const char *, ... );

// The Zero Hour shim omits BFME members before these fields, so its declared offsets cannot be used here.
// The rest of the AIUpdateInterface tail the Zero Hour shim cannot place: the
// state machine, the current victim, and the mood-check deadline with its
// randomise flag.
// BFME reaches setGoalObject through the state machine's vtable at +0x38; the
// reference StateMachine declares it as an ordinary member.
class BFMEGoalObjectMachine
{
public:
	virtual void slot00() = 0;	virtual void slot04() = 0;
	virtual void slot08() = 0;	virtual void slot0C() = 0;
	virtual void slot10() = 0;	virtual void clear() = 0;		///< vtable +0x14
	virtual void slot18() = 0;	virtual void slot1C() = 0;
	virtual void setState( StateID state ) = 0;			///< vtable +0x20
	virtual void slot24() = 0;
	virtual void slot28() = 0;	virtual void slot2C() = 0;
	virtual void slot30() = 0;	virtual void slot34() = 0;
	virtual void setGoalObject( const Object *object ) = 0;	///< vtable +0x38

	char m_unreconstructed_004[0x40 - 4];
	Bool m_locked;						///< retail this+0x40
};

struct BFMEAIUpdateFields
{
	Object *getObject() const { return m_object; }
	Real getPathExtraDistance() const { return m_pathExtraDistance; }
	BFMEGoalObjectMachine *getGoalObjectMachine() const
	{
		return reinterpret_cast<BFMEGoalObjectMachine *>( m_stateMachine );
	}

	char m_unreconstructed_000[0x08];
	Object *m_object;					///< retail this+0x08
	char m_unreconstructed_00C[0x30 - 0x0C];
	StateMachine *m_stateMachine;				///< retail this+0x30
	char m_unreconstructed_034[0x40 - 0x34];
	ObjectID m_currentVictimID;				///< retail this+0x40
	char m_unreconstructed_044[0x48 - 0x44];
	CommandSourceType m_lastCommandSource;			///< retail this+0x48
	char m_unreconstructed_04C[0x168 - 0x4C];
	Real m_pathExtraDistance;				///< retail this+0x168
	char m_unreconstructed_16C[0x1CC - 0x16C];
	Locomotor *m_curLocomotor;				///< retail this+0x1CC
	char m_unreconstructed_1D0[0x1FC - 0x1D0];
	UnsignedInt m_nextMoodCheckTime;			///< retail this+0x1FC
	char m_unreconstructed_200[0x32A - 0x200];
	Bool m_randomlyOffsetMoodCheck;				///< retail this+0x32A
	Bool m_isAiDead;					///< retail this+0x32B
	char m_unreconstructed_32C[0x330 - 0x32C];
	Bool m_isInUpdate;					///< retail this+0x330
	char m_unreconstructed_331[0x333 - 0x331];
	Bool m_forbidPlayerCommands;				///< retail this+0x333
	Bool m_forbidAICommands;				///< retail this+0x334
};

struct BFMEStateIDField
{
	StateID getID() const { return m_id; }

	char m_unreconstructed_000[4];
	StateID m_id;						///< retail this+0x04
};

struct BFMEStateMachineFields
{
	// BFME's getCurrentStateID is not the reference one-liner: an absent or
	// invalid current state falls back to a second state at machine+0x1c, which
	// is why the invalid constant appears twice -- once as the value for an
	// absent current state, once as the value the comparison tests for.
	StateID getCurrentStateID() const
	{
		StateID id = m_currentState
				? reinterpret_cast<const BFMEStateIDField *>(m_currentState)->getID()
				: (StateID)INVALID_STATE_ID;

		if (id == INVALID_STATE_ID)
			id = m_fallbackState
					? reinterpret_cast<const BFMEStateIDField *>(m_fallbackState)->getID()
					: (StateID)INVALID_STATE_ID;

		return id;
	}

	char m_unreconstructed_000[0x1C];
	State *m_fallbackState;					///< retail this+0x1C
	char m_unreconstructed_020[0x24 - 0x20];
	Coord3D m_goalPosition;					///< retail this+0x24
	char m_unreconstructed_030[0x58 - 0x30];
	State *m_currentState;					///< retail this+0x58
	Int m_goalObjectID;					///< retail this+0x5C
};

// BFME retained the hash-map lookup that ZH replaced with a flat vector.
// Keep its authentic body visible but out of line: MSVC's alias analysis then
// schedules doPathfind's repulsor-ID load before the GameLogic load. An opaque
// declaration leaves six differing bytes in the otherwise exact 2031-byte body.
// This lookup independently matches all 82 bytes at RVA 0x0009A510; its retail
// caller uses ILT 0x0001F253. See System/GameLogicFindObjectByID.cpp.
class BFMEObjectLookup
{
public:
	__declspec(noinline) Object *findObjectByID( ObjectID id )
	{
		if (id == INVALID_ID)
			return NULL;
		ObjectHash::iterator it = m_objHash.find((int)id);
		if (it == m_objHash.end())
			return NULL;
		return (*it).second;
	}

private:
	typedef _STL::hash_map<int, Object *, _STL::hash<int>, _STL::equal_to<int> > ObjectHash;
	char m_pad[0xB0];
	ObjectHash m_objHash;
};

// doPathfind uses the BFME singleton layout directly.  The reference AI
// declaration puts these members at different offsets, so keep this view local
// to the body rather than changing the shared header.
class BFMEPathAIRoot
{
public:
	Pathfinder *pathfinder() const
	{
		return *reinterpret_cast<Pathfinder * const *>(
			reinterpret_cast<const char *>( this ) + 0x0C);
	}

	const TAiData *getAiData() const
	{
		return *reinterpret_cast<TAiData * const *>(
			reinterpret_cast<const char *>( this ) + 0x14);
	}
};

extern void j_000082ba(void);
extern void j_000016a4(void);
extern void j_00001bae(void);
extern void j_00001fd7(void);
extern void j_00003b1b(void);
extern void j_00004c37(void);
extern void j_000051be(void);
extern void j_0000572c(void);
extern void j_0000666d(void);
extern void j_000187a0(void);
extern void j_0001bb3f(void);
extern void j_0001f253(void);
extern void j_00020824(void);
extern void j_000209fa(void);
extern void j_0002253e(void);
extern void j_00026cf6(void);
extern void j_000296a9(void);
extern void j_0002e85c(void);
extern void j_0002fe0f(void);
extern void j_00031a7f(void);
extern void j_0003251f(void);
extern void j_0003f990(void);
extern void j_00043ced(void);
class BFMEPathfinderMoveAllies
{
public:
	typedef Bool (BFMEPathfinderMoveAllies::*Call)(Object *, Path *, Bool);
	__forceinline Bool moveAllies(Object *object, Path *path, Bool moveAllies)
	{
		// Retail cleans three stack arguments. The ZH declaration has only two.
		union { void (*address)(); Call member; } route = { j_000082ba };
		return (this->*route.member)(object, path, moveAllies);
	}
};

typedef Bool (__fastcall *BFMEComputeAttackPathCall)( AIUpdateInterface *,
	PathfindServicesInterface *, PathfindServicesInterface *, Object *,
	const Coord3D * );
typedef void (__fastcall *BFMEUpdateGoalCall)( Pathfinder *, Object *, Object *,
	const Coord3D *, PathfindLayerEnum, const char *, Int );
typedef Bool (__fastcall *BFMEAdjustDestinationCall)( Pathfinder *, LocomotorSet *,
	Object *, LocomotorSet *, Coord3D * );
// VC7.1 reserves __thiscall in a free-function-pointer typedef.  This call
// has only the receiver, so fastcall gives the same ECX/no-stack ABI.
typedef void (__fastcall *BFMEWakeCall)( AIUpdateInterface * );

// The computePath implementation remains a dump. Preserve its proven ILT
// identity and use a single-inheritance PMF to express the two-argument ABI.
extern void j_00023209( void );
extern void j_00005637( void );
extern void j_00011252( void );
extern void j_000294e2( void );
extern void j_0003611a( void );

__forceinline BFMEPathAIRoot *bfmePathAI()
{
	return reinterpret_cast<BFMEPathAIRoot *>( TheAI );
}

__forceinline BFMEObjectLookup *bfmePathGameLogic()
{
	return reinterpret_cast<BFMEObjectLookup *>( TheGameLogic );
}

#define BFME_PATH_AI bfmePathAI()
#define BFME_PATH_GAME_LOGIC bfmePathGameLogic()

// BFME's pathfinder position test takes the position first and the object
// last, and asks nothing about crush level; the reference Pathfinder declares
// Zero Hour's argument list. The layer accessor is a call here, not the
// reference class's inline member read.
class BFMEPathfinderMove
{
public:
	Bool validMovementPosition( const Coord3D *pos, PathfindLayerEnum layer,
			UnsignedInt validSurfaces, Object *obj );	///< retail ILT 0x0003b359
};

class BFMEObjectLayerQuery
{
public:
	Int getLayer() const;					///< retail ILT 0x0003a391
};

// BFME reads the held-disabled and dead flags out of the object's own bytes
// rather than through isDisabledByType and isEffectivelyDead.
struct BFMEObjectDisabledMask
{
	__forceinline Bool isNotHeldDisabled() const
	{
		UnsignedByte disabled = m_disabledMask;
		disabled >>= 3;
		disabled = ~disabled;
		disabled &= 1;
		return disabled;
	}

	char m_unreconstructed_000[0x1A4];
	UnsignedByte m_disabledMask;				///< retail this+0x1A4
};

struct BFMEObjectDeadFlags
{
	Bool isEffectivelyDead() const { return (m_deadFlags & 1) != 0; }

	char m_unreconstructed_000[0x344];
	UnsignedByte m_deadFlags;				///< retail this+0x344
};

// BFME's legal-surface read walks the locomotor's override chain; the
// reference Locomotor reads its template's surface mask instead.
class BFMELocomotorOverride
{
public:
	BFMELocomotorOverride *friend_getFinalOverride();	///< retail ILT 0x000022bb

	Real getWanderWidthFactor() const
	{
		BFMELocomotorOverride *locoTemplate = m_nextOverride;
		if (locoTemplate && locoTemplate->m_nextOverride)
		{
			typedef BFMELocomotorOverride *(BFMELocomotorOverride::*FinalOverrideCall)();
			union { void *asVoid; FinalOverrideCall asMember; } overrideCast;
			overrideCast.asVoid = (void *)j_000022bb;
			locoTemplate = (locoTemplate->m_nextOverride->*overrideCast.asMember)();
		}
		return *(const Real *)((const char *)locoTemplate + 0xEC);
	}

	UnsignedInt getLegalSurfaces() const
	{
		BFMELocomotorOverride *finalOverride = m_nextOverride;
		if (finalOverride && finalOverride->m_nextOverride)
			finalOverride = finalOverride->m_nextOverride->friend_getFinalOverride();
		return finalOverride->m_legalSurfaces;
	}

	BFMELocomotorOverride *bfmeFinalOverride()
	{
		if (m_nextOverride)
			return m_nextOverride->friend_getFinalOverride();
		return this;
	}

	// Retail carries a null template through rather than guarding it, so the
	// appearance read below happens off a null base and stays an invalid
	// locomotor instead of silently meaning this one.
	BFMELocomotorOverride *bfmeTemplate() const
	{
		if (m_nextOverride == NULL)
			return NULL;
		return m_nextOverride->bfmeFinalOverride();
	}

	Int getAppearance() const { return bfmeTemplate()->m_appearance; }

	char m_unreconstructed_000[4];				///< the vtable pointer
	BFMELocomotorOverride *m_nextOverride;			///< retail this+0x04
	char m_unreconstructed_008[0x10 - 8];
	UnsignedInt m_legalSurfaces;				///< retail this+0x10
	char m_unreconstructed_014[0x70 - 0x14];
	Int m_appearance;					///< retail this+0x70
};

// The two locomotor appearance values these bodies test. Only the VALUES are
// proven; the names are not. This file's donors called them LOCO_HOVER and
// LOCO_WINGS against the reference enum's 3 and 5, but Drawable.cpp's
// calcPhysicsXform jump table -- which is the only place the whole enum is
// visible at once -- numbers them with the reference's own ordering, where 2 and
// 3 are TREADS and HOVER. The two readings cannot both be right and neither
// body's bytes decide it, so the values are named for what they are.
enum { BFME_LOCO_APPEARANCE_2 = 2, BFME_LOCO_APPEARANCE_3 = 3 };

// BFME's AI state ids are not the reference enum's: it has no ENTER_HORDE,
// ENTER_GARRISON or ENTER_TRANSPORT and numbers the rest differently.
enum BFMEAIStateType
{
	BFME_AI_ENTER				= 0x0F,
	BFME_AI_GET_REPAIRED			= 0x18,
	BFME_AI_ENTER_GARRISON			= 0x19,
	BFME_AI_ENTER_HORDE			= 0x2B,
	BFME_AI_ENTER_TUNNEL			= 0x31,
	BFME_AI_ENTER_TRANSPORT			= 0x34
};

// The object status word, whose IS_ATTACKING bit is 22.
struct BFMEObjectStatusWord
{
	char m_unreconstructed_000[0x90];
	UnsignedInt m_status;					///< retail this+0x90
};

#define BFME_AIUPDATE_SLOT(N) virtual void slot##N() = 0

class BFMEDestroyPathAIUpdate
{
public:
	BFME_AIUPDATE_SLOT(000); BFME_AIUPDATE_SLOT(001); BFME_AIUPDATE_SLOT(002); BFME_AIUPDATE_SLOT(003);
	BFME_AIUPDATE_SLOT(004); BFME_AIUPDATE_SLOT(005); BFME_AIUPDATE_SLOT(006); BFME_AIUPDATE_SLOT(007);
	BFME_AIUPDATE_SLOT(008); BFME_AIUPDATE_SLOT(009); BFME_AIUPDATE_SLOT(010); BFME_AIUPDATE_SLOT(011);
	BFME_AIUPDATE_SLOT(012); BFME_AIUPDATE_SLOT(013); BFME_AIUPDATE_SLOT(014); BFME_AIUPDATE_SLOT(015);
	BFME_AIUPDATE_SLOT(016); BFME_AIUPDATE_SLOT(017); BFME_AIUPDATE_SLOT(018); BFME_AIUPDATE_SLOT(019);
	BFME_AIUPDATE_SLOT(020); BFME_AIUPDATE_SLOT(021); BFME_AIUPDATE_SLOT(022); BFME_AIUPDATE_SLOT(023);
	BFME_AIUPDATE_SLOT(024); BFME_AIUPDATE_SLOT(025); BFME_AIUPDATE_SLOT(026); BFME_AIUPDATE_SLOT(027);
	BFME_AIUPDATE_SLOT(028); BFME_AIUPDATE_SLOT(029); BFME_AIUPDATE_SLOT(030); BFME_AIUPDATE_SLOT(031);
	BFME_AIUPDATE_SLOT(032); BFME_AIUPDATE_SLOT(033); BFME_AIUPDATE_SLOT(034); BFME_AIUPDATE_SLOT(035);
	BFME_AIUPDATE_SLOT(036); BFME_AIUPDATE_SLOT(037); BFME_AIUPDATE_SLOT(038); BFME_AIUPDATE_SLOT(039);
	BFME_AIUPDATE_SLOT(040); BFME_AIUPDATE_SLOT(041); BFME_AIUPDATE_SLOT(042); BFME_AIUPDATE_SLOT(043);
	BFME_AIUPDATE_SLOT(044); BFME_AIUPDATE_SLOT(045); BFME_AIUPDATE_SLOT(046); BFME_AIUPDATE_SLOT(047);
	BFME_AIUPDATE_SLOT(048); BFME_AIUPDATE_SLOT(049); BFME_AIUPDATE_SLOT(050); BFME_AIUPDATE_SLOT(051);
	BFME_AIUPDATE_SLOT(052); BFME_AIUPDATE_SLOT(053); BFME_AIUPDATE_SLOT(054); BFME_AIUPDATE_SLOT(055);
	BFME_AIUPDATE_SLOT(056); BFME_AIUPDATE_SLOT(057); BFME_AIUPDATE_SLOT(058); BFME_AIUPDATE_SLOT(059);
	BFME_AIUPDATE_SLOT(060); BFME_AIUPDATE_SLOT(061); BFME_AIUPDATE_SLOT(062); BFME_AIUPDATE_SLOT(063);
	BFME_AIUPDATE_SLOT(064); BFME_AIUPDATE_SLOT(065); BFME_AIUPDATE_SLOT(066); BFME_AIUPDATE_SLOT(067);
	BFME_AIUPDATE_SLOT(068); BFME_AIUPDATE_SLOT(069); BFME_AIUPDATE_SLOT(070); BFME_AIUPDATE_SLOT(071);
	BFME_AIUPDATE_SLOT(072); BFME_AIUPDATE_SLOT(073); BFME_AIUPDATE_SLOT(074); BFME_AIUPDATE_SLOT(075);
	virtual Bool isGiantBird() const = 0;				///< vtable +0x130
	BFME_AIUPDATE_SLOT(077); BFME_AIUPDATE_SLOT(078); BFME_AIUPDATE_SLOT(079);
	BFME_AIUPDATE_SLOT(080); BFME_AIUPDATE_SLOT(081); BFME_AIUPDATE_SLOT(082); BFME_AIUPDATE_SLOT(083);
	BFME_AIUPDATE_SLOT(084); BFME_AIUPDATE_SLOT(085); BFME_AIUPDATE_SLOT(086); BFME_AIUPDATE_SLOT(087);
	BFME_AIUPDATE_SLOT(088); BFME_AIUPDATE_SLOT(089); BFME_AIUPDATE_SLOT(090); BFME_AIUPDATE_SLOT(091);
	BFME_AIUPDATE_SLOT(092); BFME_AIUPDATE_SLOT(093); BFME_AIUPDATE_SLOT(094); BFME_AIUPDATE_SLOT(095);
	BFME_AIUPDATE_SLOT(096); BFME_AIUPDATE_SLOT(097); BFME_AIUPDATE_SLOT(098); BFME_AIUPDATE_SLOT(099);
	BFME_AIUPDATE_SLOT(100); BFME_AIUPDATE_SLOT(101); BFME_AIUPDATE_SLOT(102); BFME_AIUPDATE_SLOT(103);
	BFME_AIUPDATE_SLOT(104); BFME_AIUPDATE_SLOT(105); BFME_AIUPDATE_SLOT(106); BFME_AIUPDATE_SLOT(107);
	BFME_AIUPDATE_SLOT(108); BFME_AIUPDATE_SLOT(109); BFME_AIUPDATE_SLOT(110); BFME_AIUPDATE_SLOT(111);
	BFME_AIUPDATE_SLOT(112); BFME_AIUPDATE_SLOT(113); BFME_AIUPDATE_SLOT(114); BFME_AIUPDATE_SLOT(115);
	BFME_AIUPDATE_SLOT(116); BFME_AIUPDATE_SLOT(117); BFME_AIUPDATE_SLOT(118); BFME_AIUPDATE_SLOT(119);
	BFME_AIUPDATE_SLOT(120); BFME_AIUPDATE_SLOT(121);
	virtual void setLocomotorGoalNone(void) = 0;
	virtual Bool isDoingGroundMovement(void) const = 0;
};

struct Rva00279A50ObjectIntBoolCall
{
	typedef Bool (Rva00279A50ObjectIntBoolCall::*Function)(Int);
};

static __forceinline Bool rva00279A50ObjectIntBool(const void *object, Int value)
{
	union { void (*raw)(void); Rva00279A50ObjectIntBoolCall::Function member; } route;
	route.raw = j_000016a4;
	return (reinterpret_cast<Rva00279A50ObjectIntBoolCall *>(const_cast<void *>(object))->*route.member)(value);
}

struct Rva00279A50FlagsIntBoolCall
{
	typedef Bool (Rva00279A50FlagsIntBoolCall::*Function)(Int);
};

static __forceinline Bool rva00279A50FlagsIntBool(const void *flags, Int value)
{
	union { void (*raw)(void); Rva00279A50FlagsIntBoolCall::Function member; } route;
	route.raw = j_0000666d;
	return (reinterpret_cast<Rva00279A50FlagsIntBoolCall *>(const_cast<void *>(flags))->*route.member)(value);
}

struct Rva00279A50ObjectIntBool3BCall
{
	typedef Bool (Rva00279A50ObjectIntBool3BCall::*Function)(Int);
};

static __forceinline Bool rva00279A50ObjectIntBool3B(const void *object, Int value)
{
	union { void (*raw)(void); Rva00279A50ObjectIntBool3BCall::Function member; } route;
	route.raw = j_00003b1b;
	return (reinterpret_cast<Rva00279A50ObjectIntBool3BCall *>(const_cast<void *>(object))->*route.member)(value);
}

struct Rva00279A50ObjectPlayerCall
{
	typedef Player *(Rva00279A50ObjectPlayerCall::*Function)(void);
};

static __forceinline Player *rva00279A50ControllingPlayer(const void *object)
{
	union { void (*raw)(void); Rva00279A50ObjectPlayerCall::Function member; } route;
	route.raw = j_00020824;
	return (reinterpret_cast<Rva00279A50ObjectPlayerCall *>(const_cast<void *>(object))->*route.member)();
}

struct Rva00279A50ObjectKindCall
{
	typedef Bool (Rva00279A50ObjectKindCall::*Function)(Int);
};

static __forceinline Bool rva00279A50KindOf(const void *object, Int kind)
{
	union { void (*raw)(void); Rva00279A50ObjectKindCall::Function member; } route;
	route.raw = j_0003251f;
	return (reinterpret_cast<Rva00279A50ObjectKindCall *>(const_cast<void *>(object))->*route.member)(kind);
}

struct Rva00279A50GameLogicFindCall
{
	typedef Object *(Rva00279A50GameLogicFindCall::*Function)(ObjectID);
};

static __forceinline Object *rva00279A50FindObject(void *gameLogic, ObjectID id)
{
	union { void (*raw)(void); Rva00279A50GameLogicFindCall::Function member; } route;
	route.raw = j_0001f253;
	return (reinterpret_cast<Rva00279A50GameLogicFindCall *>(gameLogic)->*route.member)(id);
}

struct Rva00279A50NoArgObjectCall
{
	typedef Object *(Rva00279A50NoArgObjectCall::*Function)(void);
};

static __forceinline Object *rva00279A50TeamTarget(void *team)
{
	union { void (*raw)(void); Rva00279A50NoArgObjectCall::Function member; } route;
	route.raw = j_000296a9;
	return (reinterpret_cast<Rva00279A50NoArgObjectCall *>(team)->*route.member)();
}

struct Rva00279A50MoodStateCall
{
	typedef Int (Rva00279A50MoodStateCall::*Function)(void);
};

static __forceinline Int rva00279A50MoodState(const void *aiUpdate)
{
	union { void (*raw)(void); Rva00279A50MoodStateCall::Function member; } route;
	route.raw = j_000187a0;
	return (reinterpret_cast<Rva00279A50MoodStateCall *>(const_cast<void *>(aiUpdate))->*route.member)();
}

struct Rva00279A50MoodFlagsCall
{
	typedef UnsignedInt (Rva00279A50MoodFlagsCall::*Function)(void);
};

static __forceinline UnsignedInt rva00279A50MoodFlags(const void *aiUpdate)
{
	union { void (*raw)(void); Rva00279A50MoodFlagsCall::Function member; } route;
	route.raw = j_0001bb3f;
	return (reinterpret_cast<Rva00279A50MoodFlagsCall *>(const_cast<void *>(aiUpdate))->*route.member)();
}

struct Rva00279A50ObjectByteAddressCall
{
	typedef unsigned char *(Rva00279A50ObjectByteAddressCall::*Function)(void);
};

static __forceinline unsigned char *rva00279A50ByteAddress(const void *object)
{
	union { void (*raw)(void); Rva00279A50ObjectByteAddressCall::Function member; } route;
	route.raw = j_000209fa;
	return (reinterpret_cast<Rva00279A50ObjectByteAddressCall *>(const_cast<void *>(object))->*route.member)();
}

struct Rva00279A50ObjectWeaponCall
{
	typedef Weapon *(Rva00279A50ObjectWeaponCall::*Function)(Int *);
};

static __forceinline Weapon *rva00279A50CurrentWeapon(const void *object)
{
	union { void (*raw)(void); Rva00279A50ObjectWeaponCall::Function member; } route;
	route.raw = j_00031a7f;
	return (reinterpret_cast<Rva00279A50ObjectWeaponCall *>(const_cast<void *>(object))->*route.member)(NULL);
}

struct Rva00279A50WeaponRangeCall
{
	typedef Bool (Rva00279A50WeaponRangeCall::*Function)(const Object *, const Object *, Int);
};

static __forceinline Bool rva00279A50WeaponInRange(void *weapon, const Object *source,
	const Object *target)
{
	union { void (*raw)(void); Rva00279A50WeaponRangeCall::Function member; } route;
	route.raw = j_0002e85c;
	return (reinterpret_cast<Rva00279A50WeaponRangeCall *>(weapon)->*route.member)(source, target, 0);
}

struct Rva00279A50ObjectPostCall
{
	typedef Object *(Rva00279A50ObjectPostCall::*Function)(const Object *, Bool);
};

static __forceinline Object *rva00279A50PostObject(void *object, const Object *owner, Bool add)
{
	union { void (*raw)(void); Rva00279A50ObjectPostCall::Function member; } route;
	route.raw = j_000051be;
	return (reinterpret_cast<Rva00279A50ObjectPostCall *>(object)->*route.member)(owner, add);
}

struct Rva00279A50ObjectDistanceCall
{
	typedef Real (Rva00279A50ObjectDistanceCall::*Function)(const Object *);
};

static __forceinline Real rva00279A50ObjectDistance(void *object, const Object *other)
{
	union { void (*raw)(void); Rva00279A50ObjectDistanceCall::Function member; } route;
	route.raw = j_0002253e;
	return (reinterpret_cast<Rva00279A50ObjectDistanceCall *>(object)->*route.member)(other);
}

struct Rva00279A50ObjectGapCall
{
	typedef Real (Rva00279A50ObjectGapCall::*Function)(const Object *);
};

static __forceinline Real rva00279A50ObjectGap(void *object, const Object *other)
{
	union { void (*raw)(void); Rva00279A50ObjectGapCall::Function member; } route;
	route.raw = j_00043ced;
	return (reinterpret_cast<Rva00279A50ObjectGapCall *>(object)->*route.member)(other);
}

struct Rva00279A50CoordLengthCall
{
	typedef Real (Rva00279A50CoordLengthCall::*Function)(void);
};

static __forceinline Real rva00279A50CoordLength(void *coord)
{
	union { void (*raw)(void); Rva00279A50CoordLengthCall::Function member; } route;
	route.raw = j_0002fe0f;
	return (reinterpret_cast<Rva00279A50CoordLengthCall *>(coord)->*route.member)();
}

struct Rva00279A50ObjectBoolCall
{
	typedef Bool (Rva00279A50ObjectBoolCall::*Function)(void);
};

static __forceinline Bool rva00279A50CanAttack(const void *object)
{
	union { void (*raw)(void); Rva00279A50ObjectBoolCall::Function member; } route;
	route.raw = j_00001fd7;
	return (reinterpret_cast<Rva00279A50ObjectBoolCall *>(const_cast<void *>(object))->*route.member)();
}

static __forceinline Bool rva00279A50BodyResultTest(void *result)
{
	struct Rva00279A50BodyResultTestCall
	{
		typedef Bool (Rva00279A50BodyResultTestCall::*Function)(void);
	};
	union { void (*raw)(void); Rva00279A50BodyResultTestCall::Function member; } route;
	route.raw = j_0000572c;
	return (reinterpret_cast<Rva00279A50BodyResultTestCall *>(result)->*route.member)();
}

static __forceinline Int rva00279A50RandomValue(Int low, Int high)
{
	typedef Int (__cdecl *Function)(Int, Int, const char *, Int);
	return ((Function)j_00001bae)(low, high, "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Update\\AIUpdate.cpp", 0x1D67);
}

static __forceinline Bool rva00279A50PairTest(Object *first, Object *second)
{
	typedef Bool (__cdecl *Function)(Object *, Object *);
	return ((Function)j_00004c37)(first, second);
}

class Rva00279A50FindClosestRoute
{
public:
	typedef Object *(Rva00279A50FindClosestRoute::*Function)(const Object *, Real,
		UnsignedInt, const AttackPriorityInfo *, void *);
};

static __forceinline Object *rva00279A50FindClosest(AI *ai, const Object *owner,
	Real range, UnsignedInt flags, const AttackPriorityInfo *info, void *filter)
{
	union { void (*raw)(void); Rva00279A50FindClosestRoute::Function member; } route;
	route.raw = j_0003f990;
	return (reinterpret_cast<Rva00279A50FindClosestRoute *>(ai)->*route.member)(
		owner, range, flags, info, filter);
}

class Rva00279A50StateProbe;

#define RVA00279A50_SLOT(N) virtual void slot##N(void) = 0
class Rva00279A50StateProbe
{
public:
	RVA00279A50_SLOT(00); RVA00279A50_SLOT(04); RVA00279A50_SLOT(08); RVA00279A50_SLOT(0C);
	RVA00279A50_SLOT(10); RVA00279A50_SLOT(14); RVA00279A50_SLOT(18); RVA00279A50_SLOT(1C);
	virtual Bool slot20(void) = 0;
	virtual Int slot24(void) = 0;
};

// C-linkage views of the retail tables ??_7Rva0026FA60FunctorValueWrapper@@6B@
// and ??_7PartitionFilter@@6B@; the alternate names define no table.
extern "C" void *bfmeVftRva0026FA60FunctorValueWrapper[];
extern "C" void *bfmeVftPartitionFilter[];

#undef RVA00279A50_SLOT

// addTargeter is vtable slot 115 (+0x1cc) of the AIUpdateInterface.
class BFMEAddTargeterAI
{
public:
	BFME_AIUPDATE_SLOT(000); BFME_AIUPDATE_SLOT(001); BFME_AIUPDATE_SLOT(002); BFME_AIUPDATE_SLOT(003);
	BFME_AIUPDATE_SLOT(004); BFME_AIUPDATE_SLOT(005); BFME_AIUPDATE_SLOT(006); BFME_AIUPDATE_SLOT(007);
	BFME_AIUPDATE_SLOT(008); BFME_AIUPDATE_SLOT(009); BFME_AIUPDATE_SLOT(010); BFME_AIUPDATE_SLOT(011);
	BFME_AIUPDATE_SLOT(012); BFME_AIUPDATE_SLOT(013); BFME_AIUPDATE_SLOT(014); BFME_AIUPDATE_SLOT(015);
	BFME_AIUPDATE_SLOT(016); BFME_AIUPDATE_SLOT(017); BFME_AIUPDATE_SLOT(018); BFME_AIUPDATE_SLOT(019);
	BFME_AIUPDATE_SLOT(020); BFME_AIUPDATE_SLOT(021); BFME_AIUPDATE_SLOT(022); BFME_AIUPDATE_SLOT(023);
	BFME_AIUPDATE_SLOT(024); BFME_AIUPDATE_SLOT(025); BFME_AIUPDATE_SLOT(026); BFME_AIUPDATE_SLOT(027);
	BFME_AIUPDATE_SLOT(028); BFME_AIUPDATE_SLOT(029); BFME_AIUPDATE_SLOT(030); BFME_AIUPDATE_SLOT(031);
	BFME_AIUPDATE_SLOT(032); BFME_AIUPDATE_SLOT(033); BFME_AIUPDATE_SLOT(034); BFME_AIUPDATE_SLOT(035);
	BFME_AIUPDATE_SLOT(036); BFME_AIUPDATE_SLOT(037); BFME_AIUPDATE_SLOT(038); BFME_AIUPDATE_SLOT(039);
	BFME_AIUPDATE_SLOT(040); BFME_AIUPDATE_SLOT(041); BFME_AIUPDATE_SLOT(042); BFME_AIUPDATE_SLOT(043);
	BFME_AIUPDATE_SLOT(044); BFME_AIUPDATE_SLOT(045); BFME_AIUPDATE_SLOT(046); BFME_AIUPDATE_SLOT(047);
	BFME_AIUPDATE_SLOT(048); BFME_AIUPDATE_SLOT(049); BFME_AIUPDATE_SLOT(050); BFME_AIUPDATE_SLOT(051);
	BFME_AIUPDATE_SLOT(052); BFME_AIUPDATE_SLOT(053); BFME_AIUPDATE_SLOT(054); BFME_AIUPDATE_SLOT(055);
	BFME_AIUPDATE_SLOT(056); BFME_AIUPDATE_SLOT(057); BFME_AIUPDATE_SLOT(058); BFME_AIUPDATE_SLOT(059);
	BFME_AIUPDATE_SLOT(060); BFME_AIUPDATE_SLOT(061); BFME_AIUPDATE_SLOT(062); BFME_AIUPDATE_SLOT(063);
	BFME_AIUPDATE_SLOT(064); BFME_AIUPDATE_SLOT(065); BFME_AIUPDATE_SLOT(066); BFME_AIUPDATE_SLOT(067);
	BFME_AIUPDATE_SLOT(068); BFME_AIUPDATE_SLOT(069); BFME_AIUPDATE_SLOT(070); BFME_AIUPDATE_SLOT(071);
	BFME_AIUPDATE_SLOT(072); BFME_AIUPDATE_SLOT(073); BFME_AIUPDATE_SLOT(074); BFME_AIUPDATE_SLOT(075);
	BFME_AIUPDATE_SLOT(076); BFME_AIUPDATE_SLOT(077); BFME_AIUPDATE_SLOT(078); BFME_AIUPDATE_SLOT(079);
	BFME_AIUPDATE_SLOT(080); BFME_AIUPDATE_SLOT(081); BFME_AIUPDATE_SLOT(082); BFME_AIUPDATE_SLOT(083);
	BFME_AIUPDATE_SLOT(084); BFME_AIUPDATE_SLOT(085); BFME_AIUPDATE_SLOT(086); BFME_AIUPDATE_SLOT(087);
	BFME_AIUPDATE_SLOT(088); BFME_AIUPDATE_SLOT(089); BFME_AIUPDATE_SLOT(090); BFME_AIUPDATE_SLOT(091);
	BFME_AIUPDATE_SLOT(092); BFME_AIUPDATE_SLOT(093); BFME_AIUPDATE_SLOT(094); BFME_AIUPDATE_SLOT(095);
	BFME_AIUPDATE_SLOT(096); BFME_AIUPDATE_SLOT(097); BFME_AIUPDATE_SLOT(098); BFME_AIUPDATE_SLOT(099);
	BFME_AIUPDATE_SLOT(100); BFME_AIUPDATE_SLOT(101); BFME_AIUPDATE_SLOT(102); BFME_AIUPDATE_SLOT(103);
	BFME_AIUPDATE_SLOT(104); BFME_AIUPDATE_SLOT(105); BFME_AIUPDATE_SLOT(106); BFME_AIUPDATE_SLOT(107);
	BFME_AIUPDATE_SLOT(108); BFME_AIUPDATE_SLOT(109); BFME_AIUPDATE_SLOT(110); BFME_AIUPDATE_SLOT(111);
	BFME_AIUPDATE_SLOT(112); BFME_AIUPDATE_SLOT(113); BFME_AIUPDATE_SLOT(114);
	virtual void addTargeter( ObjectID id, Bool add ) = 0;	///< vtable +0x1cc
};

// BFME's contain interface places removeAllContained at vtable slot 37 (+0x94).
class BFMEContainRemoveAll
{
public:
	BFME_AIUPDATE_SLOT(000); BFME_AIUPDATE_SLOT(001); BFME_AIUPDATE_SLOT(002); BFME_AIUPDATE_SLOT(003);
	BFME_AIUPDATE_SLOT(004); BFME_AIUPDATE_SLOT(005); BFME_AIUPDATE_SLOT(006); BFME_AIUPDATE_SLOT(007);
	BFME_AIUPDATE_SLOT(008); BFME_AIUPDATE_SLOT(009); BFME_AIUPDATE_SLOT(010); BFME_AIUPDATE_SLOT(011);
	BFME_AIUPDATE_SLOT(012); BFME_AIUPDATE_SLOT(013); BFME_AIUPDATE_SLOT(014); BFME_AIUPDATE_SLOT(015);
	BFME_AIUPDATE_SLOT(016); BFME_AIUPDATE_SLOT(017); BFME_AIUPDATE_SLOT(018); BFME_AIUPDATE_SLOT(019);
	BFME_AIUPDATE_SLOT(020); BFME_AIUPDATE_SLOT(021); BFME_AIUPDATE_SLOT(022); BFME_AIUPDATE_SLOT(023);
	BFME_AIUPDATE_SLOT(024); BFME_AIUPDATE_SLOT(025); BFME_AIUPDATE_SLOT(026); BFME_AIUPDATE_SLOT(027);
	BFME_AIUPDATE_SLOT(028); BFME_AIUPDATE_SLOT(029); BFME_AIUPDATE_SLOT(030); BFME_AIUPDATE_SLOT(031);
	BFME_AIUPDATE_SLOT(032); BFME_AIUPDATE_SLOT(033); BFME_AIUPDATE_SLOT(034); BFME_AIUPDATE_SLOT(035);
	BFME_AIUPDATE_SLOT(036);
	virtual void removeAllContained( Bool exposeStealthUnits ) = 0;	///< vtable +0x94
};

// BFME numbers the four waypoint-following states 2..5, and clears the
// object's formation id -- at object+0x31c -- when a unit follows a path on
// its own rather than as part of a team.
enum
{
	BFME_AI_FOLLOW_WAYPOINT_PATH_AS_TEAM			= 2,
	BFME_AI_FOLLOW_WAYPOINT_PATH_AS_INDIVIDUALS		= 3,
	BFME_AI_FOLLOW_WAYPOINT_PATH_AS_TEAM_EXACT		= 4,
	BFME_AI_FOLLOW_WAYPOINT_PATH_AS_INDIVIDUALS_EXACT	= 5
};

struct BFMEObjectFormationField
{
	void setFormationID( FormationID id ) { m_formationID = id; }

	char m_unreconstructed_000[0x410];
	FormationID m_formationID;				///< BFME2 Object+0x410 (BFME1 +0x31C); privateFollowWaypointPathExact clears it
};

// The voice lines the movement and attack commands answer with. The vendored
// AIUpdate.h declares neither.
#include "../../../../Include/GameLogic/Module/BFMEMoveVoiceAI.h"

class BFMEAttackVoiceAI
{
public:
	void playAttackVoiceResponse( Object *victim );		///< retail ILT 0x00002ef0
};

// BFME refuses an attack order from a mine-clearing detail: bit 8 of the
// object's weapon-set flags, whose accessor the vendored Object.h lacks.
class BFMEWeaponSetFlags
{
public:
	Bool test( Int type ) const { return (m_words[0] & (1U << type)) != 0; }

	UnsignedInt m_words[1];
};

#include "../../../../Include/GameLogic/Module/BFMEWeaponSetOwner.h"

// BFME writes the max-shot count in place: the count at weapon+0x34 and the
// shots-fired counter at +0x20 reset together, with no call.
#include "../../../../Include/Common/BFMEWeaponShotCount.h"

// BFME keeps the object's contain module at +0x1fc and its AI module at +0x204.
struct BFMEObjectContainField
{
	BFMEContainRemoveAll *getContain() const { return m_contain; }

	char m_unreconstructed_000[0x1FC];
	BFMEContainRemoveAll *m_contain;			///< retail this+0x1fc
};

static BFMEContainRemoveAll *bfmeContainOf( const AIUpdateInterface *ai )
{
	return reinterpret_cast<const BFMEObjectContainField *>(
		reinterpret_cast<const BFMEAIUpdateFields *>(ai)->getObject() )->getContain();
}

// BFME keeps the object's AI module at +0x204.
struct BFMEObjectAIField
{
	BFMEAddTargeterAI *getAI() const { return m_ai; }

	char m_unreconstructed_000[0x204];
	BFMEAddTargeterAI *m_ai;				///< retail this+0x204
};

#undef BFME_AIUPDATE_SLOT

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

#ifdef ALLOW_SURRENDER

#endif

/* Called by the pathfinder when it processes the pathfind queue.  Basically, it's our turn
to call use the PathfindServicesInterface to do a pathfind operation.  This shouldn't be called
(and in fact is very hard to do because PathfindServicesInterace is private to the pathfinder)
except by the pathfinder during pathfind queue processing.  jba */
//-------------------------------------------------------------------------------------------------
#if 0

#endif

#define TheGameLogic BFME_PATH_GAME_LOGIC
#define TheAI BFME_PATH_AI

#undef TheAI
#undef TheGameLogic

enum {WAYPOINT_PATH_LIMIT=1024};

//=============================================================================
// BFME AIUpdateInterface::chooseLocomotorSet is vtable +0x1fc (slot 127).
#ifdef ALLOW_SURRENDER

#endif

 

  // end isPathAvailable

  // end isQuickPathAvailable

//-------------------------------------------------------------------------------------------------
/** Some aircraft (comanche in particular, which hover) shouldn't stack destinations.
Others, like missles, should stack destinations.  AdjustDestination in pathfinder unstacks
destinations, and this routine identifies non-ground units that should unstack. */

 

  // end joinTeam

//-------------------------------------------------------------------------------------------------
// AI Command Interface implementation for AIUpdateInterface
//

//----------------------------------------------------------------------------------------
/**
 * Start following the path from the given point
 */
// BFME2 aiDoCommand (0x002673F6) command 0x32, AIUpdate vtable 0x00C47B98
// slot 28, retail 0x0026B987: the donor body, with the formation id at BFME2's
// Object+0x410.
void AIUpdateInterface::privateFollowWaypointPathExact( const Waypoint *way, CommandSourceType cmdSource )
{
	BFMEAIUpdateFields *fields = reinterpret_cast<BFMEAIUpdateFields *>(this);

	if (!fields->getObject()->isMobile())
		return;

	reinterpret_cast<BFMEObjectFormationField *>( fields->getObject() )->setFormationID( NO_FORMATION_ID );

	fields->getGoalObjectMachine()->clear();
	reinterpret_cast<AIStateMachine *>( fields->m_stateMachine )->setGoalWaypoint( way );
	fields->m_lastCommandSource = cmdSource;
	fields->getGoalObjectMachine()->setState( (StateID)BFME_AI_FOLLOW_WAYPOINT_PATH_AS_INDIVIDUALS_EXACT );

	if (cmdSource == (CommandSourceType)0 || cmdSource == (CommandSourceType)1)
		reinterpret_cast<BFMEMoveVoiceAI *>(this)->playMoveVoiceResponse( way->getLocation() );
}

//----------------------------------------------------------------------------------------
/**
 * Start following the path from the given point
 */
void AIUpdateInterface::privateFollowWaypointPathAsTeamExact( const Waypoint *way, CommandSourceType cmdSource )
{
	BFMEAIUpdateFields *fields = reinterpret_cast<BFMEAIUpdateFields *>(this);

	if (!fields->getObject()->isMobile())
		return;

	fields->getGoalObjectMachine()->clear();
	reinterpret_cast<AIStateMachine *>( fields->m_stateMachine )->setGoalWaypoint( way );
	fields->m_lastCommandSource = cmdSource;
	fields->getGoalObjectMachine()->setState( (StateID)BFME_AI_FOLLOW_WAYPOINT_PATH_AS_TEAM_EXACT );

	// Retail answers with a movement voice line for the two command sources it
	// numbers 0 and 1; the reference copies have no voice response at all.
	if (cmdSource == (CommandSourceType)0 || cmdSource == (CommandSourceType)1)
		reinterpret_cast<BFMEMoveVoiceAI *>(this)->playMoveVoiceResponse( way->getLocation() );
}

#ifdef ALLOW_SURRENDER

#endif

#ifdef ALLOW_SURRENDER

#endif

  // end evaluateMoraleBonus

#ifdef ALLOW_DEMORALIZE

#endif

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

  // end crc

  // end xfer

  // end loadPostProcess

// ------------------------------------------------------------------------------------------------

// The retail call in this body reads 0x0026B403, an address the ledger already
// carries as ?playMoveVoiceResponse@AIUpdateInterface@@IAEXPBUCoord3D@@@Z. Bind the donor spelling to that rowed owner so one
// address keeps one definition and the unit links.
#pragma comment(linker, "/alternatename:?playMoveVoiceResponse@BFMEMoveVoiceAI@@QAEXPBUCoord3D@@@Z=?playMoveVoiceResponse@AIUpdateInterface@@IAEXPBUCoord3D@@@Z")
