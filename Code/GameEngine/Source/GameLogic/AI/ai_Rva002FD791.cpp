// cl: -DNDEBUG -DWIN32 -MD -EHsc -Ireference/open-bfme-1/inputs/reference/shims/sweep -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Os -Ireference/open-bfme-1/game/GameEngine/Source/GameLogic/AI
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
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

// AI.cpp
// The Artificial Intelligence system
// Author: Michael S. Booth, November 2000
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

// BFME de-pooled this glue: retail's per-class `operator delete(void*, MagicEnum)`
// is one 12-byte body (0x007EFFF0) that calls the CRT free IMPORT THUNK -- a
// `call rel32` into `jmp [__imp__free]` -- where ::operator delete (0x00881EB0)
// is a different function. <stdlib.h> declares free __declspec(dllimport) under
// /MD, which compiles to the `ff 15` indirect form instead, so the C-linkage
// redeclaration below is what names `_free` for the linker's thunk; it is
// namespaced so every other free() call in this TU keeps the indirect form
// retail also uses. Same TU-scoped override Team.cpp already carries.
namespace BfmePoolGlue { extern "C" void __cdecl free(void *); }
#undef MEMORY_POOL_GLUE_WITHOUT_GCMP
#define MEMORY_POOL_GLUE_WITHOUT_GCMP(ARGCLASS) \
protected: \
	virtual ~ARGCLASS(); \
public: \
	enum ARGCLASS##MagicEnum { ARGCLASS##_GLUE_NOT_IMPLEMENTED = 0 }; \
public: \
	inline void *operator new(size_t s, ARGCLASS##MagicEnum e DECLARE_LITERALSTRING_ARG2) \
	{ return MP_GLUE_ALLOCATE(ARGCLASS); } \
public: \
	inline void operator delete(void *p, ARGCLASS##MagicEnum e DECLARE_LITERALSTRING_ARG2) \
	{ BfmePoolGlue::free(p); } \
protected: \
	inline void *operator new(size_t s) { return ::operator new(s); } \
	inline void operator delete(void *p) { ::operator delete(p); } \
private: \
	virtual MemoryPool *getObjectMemoryPool() { return ARGCLASS::getClassMemoryPool(); } \
public:

#include "Common/CRCDebug.h"
#include "Common/GameState.h"
#include "Common/PerfTimer.h"
#include "Common/Player.h"
#include "Common/PlayerList.h"
#include "Common/ThingTemplate.h"
#include "Common/Xfer.h"
#include "Common/XferCRC.h"

#include "GameLogic/AI.h"
#include "GameLogic/PartitionManager.h"
#include "GameLogic/Module/AIUpdate.h"
#include "GameLogic/Module/ContainModule.h"
#include "GameLogic/ScriptEngine.h"
#include "GameLogic/SidesList.h"
#include "GameLogic/AIPathfind.h"
#include "GameLogic/Weapon.h"

extern void addIcon(const Coord3D *pos, Real width, Int numFramesDuration, RGBColor color);

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////
// PRIVATE CLASS ///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
// ?addSideInfo@TAiData@@QAEXPAVAISideInfo@@@Z present-unmatched

// ?addFactionBuildList@TAiData@@QAEXPAVAISideBuildList@@@Z present-unmatched

// ??1TAiData@@QAE@XZ present-unmatched

///////////////////////////////////////////////////////////////////////////////////////////////////
// PRIVATE CLASS ///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
// ??0AISideBuildList@@QAE@VAsciiString@@@Z present-unmatched

// ??1AISideBuildList@@MAE@XZ present-unmatched

// ?addInfo@AISideBuildList@@QAEXPAVBuildListInfo@@@Z present-unmatched

///////////////////////////////////////////////////////////////////////////////////////////////////
// PRIVATE DATA ///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
static const FieldParse TheAIFieldParseTable[] = 
{
																	 
	{ "StructureSeconds",				INI::parseReal,NULL,		offsetof( TAiData, m_structureSeconds ) },
	{ "TeamSeconds",						INI::parseReal,NULL,		offsetof( TAiData, m_teamSeconds ) },
	{ "Wealthy",								INI::parseInt,NULL,			offsetof( TAiData, m_resourcesWealthy ) },
	{ "Poor",										INI::parseInt,NULL,		  offsetof( TAiData, m_resourcesPoor ) },
	{ "ForceIdleMSEC",					INI::parseDurationUnsignedInt,NULL,offsetof( TAiData, m_forceIdleFramesCount )	},
	{ "StructuresWealthyRate",	INI::parseReal,NULL,		offsetof( TAiData, m_structuresWealthyMod ) },
	{ "TeamsWealthyRate",				INI::parseReal,NULL,		offsetof( TAiData, m_teamWealthyMod ) },
	{ "StructuresPoorRate",			INI::parseReal,NULL,		offsetof( TAiData, m_structuresPoorMod ) },
	{ "TeamsPoorRate",					INI::parseReal,NULL,		offsetof( TAiData, m_teamPoorMod ) },
	{ "TeamResourcesToStart",		INI::parseReal,NULL,		offsetof( TAiData, m_teamResourcesToBuild ) },
	{ "GuardInnerModifierAI",		INI::parseReal,NULL,		offsetof( TAiData, m_guardInnerModifierAI ) },
	{ "GuardOuterModifierAI",		INI::parseReal,NULL,		offsetof( TAiData, m_guardOuterModifierAI ) },
	{ "GuardInnerModifierHuman",INI::parseReal,NULL,		offsetof( TAiData, m_guardInnerModifierHuman ) },
	{ "GuardOuterModifierHuman",INI::parseReal,NULL,		offsetof( TAiData, m_guardOuterModifierHuman ) },
	{ "GuardChaseUnitsDuration",				INI::parseDurationUnsignedInt,NULL,		offsetof( TAiData, m_guardChaseUnitFrames ) },
	{ "GuardEnemyScanRate",				INI::parseDurationUnsignedInt,NULL,		offsetof( TAiData, m_guardEnemyScanRate ) },
	{ "GuardEnemyReturnScanRate",				INI::parseDurationUnsignedInt,NULL,		offsetof( TAiData, m_guardEnemyReturnScanRate ) },
	{ "SkirmishGroupFudgeDistance",	INI::parseReal,NULL,		offsetof( TAiData, m_skirmishGroupFudgeValue ) },

	{ "RepulsedDistance",				INI::parseReal,NULL,		offsetof( TAiData, m_repulsedDistance ) },
	{ "EnableRepulsors",				INI::parseBool,NULL,		offsetof( TAiData, m_enableRepulsors ) },

	{	"AlertRangeModifier",			INI::parseReal,NULL,		offsetof( TAiData, m_alertRangeModifier)	},
	{	"AggressiveRangeModifier",INI::parseReal,NULL,		offsetof( TAiData, m_aggressiveRangeModifier)	},

	{ "ForceSkirmishAI",				INI::parseBool,NULL,		offsetof( TAiData, m_forceSkirmishAI ) },
	{ "RotateSkirmishBases",		INI::parseBool,NULL,		offsetof( TAiData, m_rotateSkirmishBases ) },

	{ "AttackUsesLineOfSight",	INI::parseBool,NULL,		offsetof( TAiData, m_attackUsesLineOfSight ) },
	{ "AttackIgnoreInsignificantBuildings",	INI::parseBool,NULL,		offsetof( TAiData, m_attackIgnoreInsignificantBuildings ) },

	
	{ "AttackPriorityDistanceModifier", INI::parseReal,NULL, offsetof( TAiData, m_attackPriorityDistanceModifier) },
 	{ "MaxRecruitRadius",				INI::parseReal,NULL,		offsetof( TAiData, m_maxRecruitDistance ) },
	{ "SkirmishBaseDefenseExtraDistance",	INI::parseReal,NULL,	offsetof( TAiData, m_skirmishBaseDefenseExtraDistance ) },

 	{ "WallHeight",							INI::parseReal,NULL,		offsetof( TAiData, m_wallHeight ) },

	{ "SideInfo",			AI::parseSideInfo,			NULL, NULL },


	{ "SkirmishBuildList",			AI::parseSkirmishBuildList,			NULL, NULL },


 	{ "MinInfantryForGroup",		INI::parseInt,NULL,			offsetof( TAiData, m_minInfantryForGroup ) },
 	{ "MinVehiclesForGroup",		INI::parseInt,NULL,			offsetof( TAiData, m_minVehiclesForGroup ) },

 	{ "MinDistanceForGroup",		INI::parseReal,NULL,			offsetof( TAiData, m_minDistanceForGroup ) },
 	{ "DistanceRequiresGroup",	INI::parseReal,NULL,			offsetof( TAiData, m_distanceRequiresGroup ) },
 	{ "MinClumpDensity",				INI::parseReal,NULL,			offsetof( TAiData, m_minClumpDensity ) },

 	{ "InfantryPathfindDiameter",		INI::parseInt,NULL,			offsetof( TAiData, m_infantryPathfindDiameter ) },
 	{ "VehiclePathfindDiameter",		INI::parseInt,NULL,			offsetof( TAiData, m_vehiclePathfindDiameter ) },
 	{ "RebuildDelayTimeSeconds",		INI::parseInt,NULL,			offsetof( TAiData, m_rebuildDelaySeconds ) },
 	{ "SupplyCenterSafeRadius",			INI::parseReal,NULL,			offsetof( TAiData, m_supplyCenterSafeRadius ) },

 	{ "AIDozerBoredRadiusModifier",	INI::parseReal,NULL,			offsetof( TAiData, m_aiDozerBoredRadiusModifier ) },
 	{ "AICrushesInfantry",	INI::parseBool,NULL,			offsetof( TAiData, m_aiCrushesInfantry ) },

 	{ "MaxRetaliationDistance",	INI::parseReal,NULL,			offsetof( TAiData, m_maxRetaliateDistance ) },
 	{ "RetaliationFriendsRadius",	INI::parseReal,NULL,			offsetof( TAiData, m_retaliateFriendsRadius ) },


	{ NULL,					NULL,						NULL,						0 }  // keep this last

};

// Body in ai_parseSideInfo.asm (exact 516B retail): ?parseSideInfo@AI@@SAXPAVINI@@PAX1PBX@Z
// (one line, and prose-first: a `// ?` line binds to the NEXT definition, and
// this one documents a body in another file, not parseSkillSet below.)

void AI::parseScience(INI *ini, void *instance, void* /*store*/, const void* /*userData*/)
{
	TSkillSet *skillset = ((TSkillSet*)instance);
	if (skillset->m_numSkills>=MAX_AI_UPGRADES) {
#ifdef DEBUG_CRASHING
		const char* c = ini->getNextToken();
		DEBUG_CRASH(("Too many SCIENCE skills in skillset. Skill = %s, max is %d", c, MAX_AI_UPGRADES));
#endif
		return;
	}
	skillset->m_skills[skillset->m_numSkills] = SCIENCE_INVALID;
	INI::parseScience(ini, instance, skillset->m_skills+skillset->m_numSkills, NULL);
	ScienceType science = skillset->m_skills[skillset->m_numSkills];
	if (science != SCIENCE_INVALID) {
		if (TheScienceStore->getSciencePurchaseCost(science)==0) {
			DEBUG_CRASH(("Science %s is not purchaseable, can't be bought.", 
				TheScienceStore->getInternalNameForScience(science).str()));
			return;
		}
		skillset->m_numSkills++;
	}
}

// ?parseSkirmishBuildList@AI@@ present-unmatched

//--------------------------------------------------------------------------------------------------------

/// The AI system singleton
AI *TheAI = NULL;


/**
 * Constructor for the AI system
 */
// ??0AI@@QAE@XZ present-unmatched

/**
 * Initialize the AI system
 */
// ?init@AI@@UAEXXZ present-unmatched

/**
 * Reset the AI system in preparation for a new map
 */
class BfmeTAiDataDeleteView
{
public:
	virtual void deleteThis(int);
};

class BfmeTAiDataResetView
{
private:
	char m_padding[0xf8];

public:
	TAiData *m_next;
};

extern "C" void Gen0002857EFreeListNode(void *, unsigned int);
#pragma comment(linker, "/alternatename:_Gen0002857EFreeListNode=?_M_deallocate@?$__node_alloc@$00$0A@@_STL@@CAXPAXI@Z")

struct BfmeAIResetGroupNode
{
	BfmeAIResetGroupNode *m_next;
	BfmeAIResetGroupNode *m_previous;
	AIGroup *m_group;

	__forceinline BfmeAIResetGroupNode *findGroup(AIGroup *group)
	{
		BfmeAIResetGroupNode *node = m_next;
		while (node != this && node->m_group != group)
			node = node->m_next;
		return node;
	}
};

class BfmeAIResetGroupList
{
public:
	__forceinline unsigned int size()
	{
		unsigned int count = 0;
		BfmeAIResetGroupNode *node = m_sentinel->m_next;
		while (node != m_sentinel)
		{
			node = node->m_next;
			++count;
		}
		return count;
	}

	__forceinline AIGroup *front()
	{
		return m_sentinel->m_next->m_group;
	}

	__forceinline void erase(BfmeAIResetGroupNode *node)
	{
		BfmeAIResetGroupNode *next = node->m_next;
		BfmeAIResetGroupNode *previous = node->m_previous;
		previous->m_next = next;
		next->m_previous = previous;
		Gen0002857EFreeListNode(node, 0xc);
	}

	__forceinline void pop_front()
	{
		erase(m_sentinel->m_next);
	}

	BfmeAIResetGroupNode *m_sentinel;
};

class BfmeAIResetListView
{
private:
	char m_padding[0x10];

public:
	BfmeAIResetGroupList m_groupList;
};

/**
 * Update the AI system
 */
// ?update@AI@@UAEXXZ present-unmatched

/**
 * Destroy the AI system
 */
// ??1AI@@UAE@XZ present-unmatched


// ?newOverride@AI@@IAEXXZ present-unmatched

// ?addSideInfo@AI@@IAEXPAVAISideInfo@@@Z present-unmatched

//-------------------------------------------------------------------------------------------------
/** Parse GameData entry */
//-------------------------------------------------------------------------------------------------
class AIParseDefinitionAIShim
{
public:
	unsigned char padding[0x14];
	void *data;
	void newOverride();
};

extern "C" AIParseDefinitionAIShim *TheAIParseDefinitionAI;

// The second initFromINI argument is the address of the AI FieldParse table
// at 0x01094B00 (the row the parseTarget work at retail 0x0014C8E0 identified
// by content), not a computed value. dir32_addresses.csv records no name for
// it, so keep the address-derived one. The body only passes the base, so an
// opaque array of one record is enough. INI::initFromINI itself is declared by
// Common/INI/INI.h, so this call no longer needs a stand-in class.
extern const FieldParse g_01094B00[];
//--------------------------------------------------------------------------------------------------------
/**
 * Create a new AI Group
 */
// byte-exact reconstruction: game/GameEngine/Source/GameLogic/AI/AI_createGroup.cpp
// ?createGroup@AI@@QAEPAVAIGroup@@XZ present-unmatched

/**
 * Destroy the given AI Group
 */
// ?destroyGroup@AI@@QAEXPAVAIGroup@@@Z present-unmatched

/**
 * Given an ID, return the associated AIGroup
 */

//--------------------------------------------------------------------------------------------------------
/**
 * Get the next formation id.
 */

//-----------------------------------------------------------------------------
class PartitionFilterLiveMapEnemies : public PartitionFilter
{
private:
	const Object *m_obj;
public:
	PartitionFilterLiveMapEnemies(const Object *obj) : m_obj(obj) { }

	virtual Bool allow(Object *objOther)
	{
		// this is way fast (bit test) so do it first.
		if (objOther->isEffectivelyDead())
			return false;

		// this is also way fast (bit test) so do it next.
		if (objOther->isOffMap() != m_obj->isOffMap())
			return false;

		Relationship r = m_obj->getRelationship(objOther);
		if (r != ENEMIES)
			return false;

		return true;
	}

#if defined(_DEBUG) || defined(_INTERNAL)
	virtual const char* debugGetName() { return "PartitionFilterLiveMapEnemies"; }
#endif
};

//-----------------------------------------------------------------------------
class PartitionFilterWithinAttackRange : public PartitionFilter
{
private:
	const Object* m_obj;
public:
	PartitionFilterWithinAttackRange(const Object* obj) : m_obj(obj) { }

	virtual Bool allow(Object* objOther)
	{
		for (Int i = 0; i < WEAPONSLOT_COUNT;	i++ )
		{
			// ignore empty slots.
			const Weapon* w = m_obj->getWeaponInWeaponSlot((WeaponSlotType)i);
			if (w == NULL)
				continue;

			if (w->isWithinAttackRange(m_obj, objOther))
			{
				return true;
			}
		}
		return false;
	}

#if defined(_DEBUG) || defined(_INTERNAL)
	virtual const char* debugGetName() { return "PartitionFilterWithinAttackRange"; }
#endif
};


typedef struct 
{
	Int priority;
	const AttackPriorityInfo *info;
} TPriorityInfo;


//-----------------------------------------------------------------------------
/**
 * Return the closest enemy, according to the qualifiers.
 */
// ?findClosestEnemy@AI@@QAEPAVObject@@PBV2@MIPBVAttackPriorityInfo@@PAVPartitionFilter@@@Z present-unmatched




 /////////////////////////////
/**
 * Return the closest ally, according to the qualifiers.
 */
// ?findClosestAlly@AI@@QAEPAVObject@@PBV2@MI@Z present-unmatched
/////////////////////////////



 /////////////////////////////
/**
 * Return the closest repulsor.
 */
// ?findClosestRepulsor@AI@@QAEPAVObject@@PBV2@M@Z present-unmatched
/////////////////////////////

//-------------------------------------------------------------------------------------------------
// byte-exact reconstruction: game/GameEngine/Source/GameLogic/AI/TAiDataCtor.cpp
// ??0TAiData@@QAE@XZ present-unmatched
TAiData::TAiData() : 
m_next(NULL), 
m_sideInfo(NULL), 
m_attackIgnoreInsignificantBuildings(false),
m_skirmishGroupFudgeValue(0.0f),
m_structureSeconds(0), 
m_teamSeconds(0), 
m_resourcesWealthy(0), 
m_resourcesPoor(0), 
m_forceIdleFramesCount(1),
m_structuresWealthyMod(0),
m_teamPoorMod(0),
m_teamResourcesToBuild(0),
m_guardInnerModifierAI(0),
m_guardOuterModifierAI(0),
m_guardInnerModifierHuman(0),
m_guardOuterModifierHuman(0),
m_guardChaseUnitFrames(0),
m_guardEnemyScanRate(LOGICFRAMES_PER_SECOND/2),
m_guardEnemyReturnScanRate(LOGICFRAMES_PER_SECOND),
m_wallHeight(0),
m_alertRangeModifier(0),
m_aggressiveRangeModifier(0),
m_attackPriorityDistanceModifier(0),
m_maxRecruitDistance(0),
m_skirmishBaseDefenseExtraDistance(0),
m_repulsedDistance(0),
m_enableRepulsors(false),
m_forceSkirmishAI(false),
m_rotateSkirmishBases(false),
m_attackUsesLineOfSight(true),
m_minInfantryForGroup(3),
m_minVehiclesForGroup(4),
m_minDistanceForGroup(100),
m_minClumpDensity(0.5f),
m_infantryPathfindDiameter(6),
m_vehiclePathfindDiameter(6),
m_supplyCenterSafeRadius(250),
m_rebuildDelaySeconds(10),
//Added By Sadullah Nader
//Initialization(s) inserted
m_distanceRequiresGroup(0.0f),
m_sideBuildLists(NULL),
m_structuresPoorMod(0.0f),
m_teamWealthyMod(0.0f),
m_aiDozerBoredRadiusModifier(2.0),
m_aiCrushesInfantry(true), 
m_maxRetaliateDistance(210.0f), 
m_retaliateFriendsRadius(120.0f)
//
{
}

//-------------------------------------------------------------------------------------------------
// ?crc@TAiData@@UAEXPAVXfer@@@Z present-unmatched

//-----------------------------------------------------------------------------
// ?xfer@TAiData@@UAEXPAVXfer@@@Z present-unmatched

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// byte-exact reconstruction: game/GameEngine/Source/Common/AI_crc_Thunk.cpp
// ?crc@AI@@UAEXPAVXfer@@@Z present-unmatched

//-----------------------------------------------------------------------------
// ?xfer@AI@@UAEXPAVXfer@@@Z present-unmatched

//-----------------------------------------------------------------------------
// ?loadPostProcess@AI@@UAEXXZ present-unmatched
