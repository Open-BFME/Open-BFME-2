// FILE: TAiData.h
// Desc: Canonical BFME2 AI configuration and Snapshot interface.
//
// Target facts (code addresses are RVAs; table addresses are VAs):
// - ??0TAiData (0x002FE382, 670 bytes) stores 0x00C071E4 at +0
//   (0x002FE3E8). ??1TAiData (0x002FDF72, 201 bytes) stores that same
//   table at 0x002FDF85, then restores Snapshot's 0x00BBB554 at
//   0x002FE02A after member cleanup. This final store belongs to the base.
// - 0x00C071E4 has four slots: deleting destructor 0x002FE041,
//   loadPostProcess 0x000B3FD0 (empty RET), GetSnapshotName 0x002FE03B
//   (returns "TAiData" at 0x00C071F4), and xfer 0x002FDD94.
//   The name string immediately follows the fourth slot. Snapshot's
//   0x00BBB554 has its destructor followed by three purecall entries.
// - AI::AI (0x002FEA85) pushes 0x114 at 0x002FEACD, allocates at
//   0x002FEAD6, and calls ??0TAiData at 0x002FEAE9: sizeof is 0x114.
// - The FieldParse table at 0x00C06650..0x00C06AF0 supplies the scalar
//   offsets and INI names used below: float parser 0x0002EFC0, integer
//   parser 0x0002EF56, bool parser 0x0002E850, duration parser 0x00338B30,
//   string parser 0x0002F11E, percent parser 0x0002F1BA. In particular,
//   +0x58 is SkirmishGroupFudgeDistance, +0x5C MaxRecruitRadius, +0x98
//   WadeWaterDepth, +0x9C DeepWaterDepth, and +0x104..+0x110 are four Ints.
// - ??0TAiData constructs strings at +0xDC/+0xE0/+0xE4; ??1TAiData
//   releases them through 0x00036410 at 0x002FE004/0x002FE013/0x002FE021.
//   Its three list heads are +0xF4/+0xF8/+0xFC; node links are +0x1BC,
//   +0x0C and +0x10, respectively. AI::newOverride (0x002FFDC3) stores
//   the preceding TAiData at +0x100. Padding carries no additional fields.
// - Out-of-line methods: assignment 0x002FD7EF (703 bytes), addSideInfo
//   0x002FD73B, addNamedList 0x002FD752, addFactionBuildList 0x002FE8CC.
//   The parser at 0x002FEA67 calls addFactionBuildList; AI::newOverride
//   calls the constructor and assignment. These rowed bodies stay declared.
// Donor facts: Zero Hour GameLogic/AI.h declares class TAiData : Snapshot
// and the shared member names. BFME2-only names follow the retail INI tokens;
// node type spellings follow the BFME2 ledger's method signatures.

#pragma once

#ifndef __BFME2_TAIDATA_H_
#define __BFME2_TAIDATA_H_

#if !defined(__SNAPSHOT_H_) && !defined(BFME_SNAPSHOT_NAME_SLOT)
#define BFME_SNAPSHOT_NAME_SLOT
#endif
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"
class Xfer;
#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"

class Rva002FE620;
class Gen0014AE40;
class Rva002FED8D;

class TAiData : public Snapshot
{
public:
	TAiData();
	virtual ~TAiData();
	TAiData &operator=(const TAiData &other);
	void addSideInfo(Rva002FE620 *info);
	void addFactionBuildList(Gen0014AE40 *buildList);
	void addNamedList(Rva002FED8D *list);

	virtual void loadPostProcess();
#ifdef BFME_SNAPSHOT_NAME_SLOT
	virtual const char *GetSnapshotName() const;
#else
	virtual void crc(Xfer *xfer);
#endif
protected:
	virtual void xfer(Xfer *xfer);
public:
	float m_structureSeconds;                         // +0x004
	float m_teamSeconds;                              // +0x008
	int m_resourcesWealthy;                            // +0x00C
	int m_resourcesPoor;                               // +0x010
	unsigned int m_forceIdleFramesCount;               // +0x014
	float m_structuresWealthyMod;                      // +0x018
	float m_teamWealthyMod;                            // +0x01C
	float m_structuresPoorMod;                         // +0x020
	float m_teamPoorMod;                              // +0x024
	float m_teamResourcesToBuild;                      // +0x028
	float m_guardInnerModifierAI;                      // +0x02C
	float m_guardOuterModifierAI;                      // +0x030
	float m_guardInnerModifierHuman;                   // +0x034
	float m_guardOuterModifierHuman;                   // +0x038
	unsigned int m_guardChaseUnitFrames;               // +0x03C
	unsigned int m_guardEnemyScanRate;                 // +0x040
	unsigned int m_guardEnemyReturnScanRate;           // +0x044
	float m_wallHeight;                               // +0x048
	float m_alertRangeModifier;                       // +0x04C
	float m_aggressiveRangeModifier;                  // +0x050
	float m_attackPriorityDistanceModifier;           // +0x054
	float m_skirmishGroupFudgeValue;                  // +0x058
	float m_maxRecruitDistance;                       // +0x05C
	float m_repulsedDistance;                         // +0x060
	bool m_enableRepulsors;                           // +0x064
	bool m_forceSkirmishAI;                           // +0x065
	bool m_rotateSkirmishBases;                       // +0x066
	bool m_attackUsesLineOfSight;                     // +0x067
	bool m_attackIgnoreInsignificantBuildings;        // +0x068
	float m_minDistanceForGroup;                      // +0x06C
	float m_distanceRequiresGroup;                    // +0x070
	float m_minClumpDensity;                          // +0x074
	int m_infantryPathfindDiameter;                    // +0x078
	int m_vehiclePathfindDiameter;                    // +0x07C
	int m_rebuildDelaySeconds;                        // +0x080
	float m_supplyCenterSafeRadius;                   // +0x084
	float m_aiDozerBoredRadiusModifier;               // +0x088
	bool m_aiCrushesInfantry;                         // +0x08C
	float m_meleeApproachTolerance;                   // +0x090
	float m_meleeApproachDist;                        // +0x094
	float m_wadeWaterDepth;                           // +0x098
	float m_deepWaterDepth;                           // +0x09C
	float m_formationColumnWidth;                     // +0x0A0
	float m_formationRowDepth;                        // +0x0A4
	float m_formationSquadSpacing;                    // +0x0A8
	float m_narrowPassageScale;                       // +0x0AC
	float m_minFlightHeight;                          // +0x0B0
	int m_formationColumns;                          // +0x0B4
	bool m_waitForOthers;                            // +0x0B8
	bool m_hordesWaitForHordes;                       // +0x0B9
	bool m_attackMoveUsesFormations;                  // +0x0BA
	bool m_forceHordesToLowLOD;                       // +0x0BB
	bool m_allowForestFires;                         // +0x0BC
	bool m_useFormations;                            // +0x0BD
	float m_altCameraZoomOverride;                   // +0x0C0
	float m_altCameraPitchOverride;                  // +0x0C4
	float m_maxRetaliateDistance;                     // +0x0C8
	float m_retaliateFriendsRadius;                   // +0x0CC
	float m_chaseFromBehindLimit;                     // +0x0D0
	float m_castleSiegeStandBackDistance;             // +0x0D4
	bool m_useLowLODTrees;                           // +0x0D8
	AsciiString m_lowLodTreeName;                     // +0x0DC
	AsciiString m_lowLodTreeNameNoGrab;               // +0x0E0
	AsciiString m_lowLodTreeNameNoHarvest;            // +0x0E4
	float m_lowLodTreeScale;                          // +0x0E8
	bool m_disableTrees;                             // +0x0EC
	float m_artilleryMaxFriendlyFire;                // +0x0F0
	Rva002FE620 *m_sideInfo;                          // +0x0F4
	Gen0014AE40 *m_sideBuildLists;                    // +0x0F8
	Rva002FED8D *m_namedLists;                        // +0x0FC
	TAiData *m_next;                                 // +0x100
	int m_buildPhase1PerSecondPriorityModifier;       // +0x104
	int m_buildPhase2PerSecondPriorityModifier;       // +0x108
	int m_buildPhase3PerSecondPriorityModifier;       // +0x10C
	int m_buildPhaseNPerSecondPriorityModifier;       // +0x110
};

#endif
