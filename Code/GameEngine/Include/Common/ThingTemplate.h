// FILE: ThingTemplate.h //////////////////////////////////////////////////////////////////////////
// Desc:   Canonical BFME2 ThingTemplate: the native 0x640-byte layout and its one-slot vftable.
//
// Written from target evidence; tools/header_adopt_lane.py cannot generate it:
// the 497 compiled private views hold 422 layouts, the commonest "size" is an
// empty class (63 pointer-only views), so class_contract freezes nothing past
// offset 0 (reverse/class_contracts/ThingTemplate.json is the lane's record of
// that, not this header's source). Target facts:
//  - the constructor ??0ThingTemplate@@QAE@XZ (0x0033E1B8, 1875 B, matched in
//    ThingTemplateConstructor.cpp) stores the vftable 0x00C10C4C (RVA
//    0x00810C4C) and initializes every member below; the allocation at
//    0x002D1AB4 is 0x640 bytes;
//  - that vftable holds ONE slot, 0x0073E90B = ??_GThingTemplate@@UAEPAXI@Z
//    (0x0033E90B); the string "PlayerUpgrade" follows it. So ThingTemplate
//    declares no virtual besides its destructor, and its base Overridable
//    contributes only a virtual destructor (Zero Hour's MemoryPoolObject glue,
//    getObjectMemoryPool and the protected destructor, is not BFME2's);
//  - the destructor ??1ThingTemplate@@UAE@XZ (0x0033DDA1, matched in
//    Rva0033DDA1Dtor.cpp) tears the members down in reverse order and ends in
//    ~Overridable (0x001E3624);
//  - the inline Overridable constructor in 0x0033E1B8 stores +0x04 = 0,
//    byte +0x08 = 0 and +0x0C = -1, so the first own member is at +0x10;
//  - the member offsets are the constructor view's offset checks
//    (0x14 0xA0 0xFC 0x108 0x124 0x2E4 0x354 0x364 0x388 0x3AC 0x3C4 0x404
//    0x484 0x620 0x638) and the copy assignment ??4 (0x002D1101) extents.
// Names: Zero Hour's where the retail FieldParse table (RVA 0x009BECD8) joins an
// INI key to them, the lower-cased native INI key otherwise, an offset name
// (mXXX) where nothing names the member. Members whose native type has no
// shared header yet are opaque storage of the native size, named and
// commented with the type the constructor view spells; giving one a real type
// keeps the layout. Every member is public: the consumers read them directly.
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef __BFME2_THINGTEMPLATE_H_
#define __BFME2_THINGTEMPLATE_H_

#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"
#include "Overridable.h"

class AIUpdateModuleData;
class Image;
class INI;
class LocomotorTemplate;
class ModuleData;
class Player;
enum BuildableStatus;
enum LocomotorSetType;

//-------------------------------------------------------------------------------------------------
class ThingTemplate : public Overridable
{
public:

	ThingTemplate();												// 0x0033E1B8
	virtual ~ThingTemplate();										// 0x0033DDA1; slot 0 ??_G 0x0033E90B
	ThingTemplate &operator=( const ThingTemplate &that );		// 0x002D1101

	const AsciiString &getName() const { return m_nameString; }

	int calcTimeToBuild( const Player *player, int second, int third ) const;			// 0x0033AA1F
	void copyFrom( const ThingTemplate *that );											// 0x0033EBEB
	AIUpdateModuleData *friend_getAIModuleInfo();											// 0x0033B387
	const ThingTemplate *getBuildFacilityTemplate( const Player *player ) const;			// 0x0033A97F
	BuildableStatus getBuildable() const;													// 0x0033A632
	const Image *getButtonImage();															// 0x0033B580
	void *getCurrentLivingWorldAutoResolveWeapon( const void *key ) const;				// 0x0033A9E2
	int getPrereqCount() const;															// 0x002AA3BF
	void GetAssetList( int a, int b );														// 0x0033CF34
	bool isEquivalentTo( const ThingTemplate *that ) const;								// 0x0033BB04
	void resolveNames();																	// 0x0033C2C2
	void setCopiedFromDefault();															// 0x0033B539
	void validate();																		// 0x0033B4CD
	int rva0033A69A( const Player *player, int a, int b ) const;							// 0x0033A69A
	const ModuleData *rva0033B3D7() const;													// 0x0033B3D7
	const ModuleData *rva0033B427( int index ) const;										// 0x0033B427
	int rva0033B479() const;																// 0x0033B479
	const Image *rva0033BA46();															// 0x0033BA46
	float rva0033C259( int index ) const;													// 0x0033C259
	void Rva0033D396StoreFloat( int index, float value );									// 0x0033D396
	void rva0033E17D( LocomotorSetType type, const LocomotorTemplate *locomotor );		// 0x0033E17D

protected:

	static void parseAddModule( INI *ini, void *instance, void *store, const void *userData );			// 0x0033A50D
	static void parseInheritableModule( INI *ini, void *instance, void *store, const void *userData );	// 0x0033A561
	static void parseFlammability( INI *ini, void *instance, void *store, const void *userData );		// 0x0033BC6A
	static void parseRemoveModule( INI *ini, void *instance, void *store, const void *userData );		// 0x0033CD41
	static void parseReplaceModule( INI *ini, void *instance, void *store, const void *userData );		// 0x0033CE18
	static void parseModuleName( INI *ini, void *instance, void *store, const void *userData );		// 0x0033D865
	static void parsePrerequisites( INI *ini, void *instance, void *store, const void *userData );		// 0x0033EBB5

public:

	float m_camouflageDetectionMultiplier;						// +0x010
	unsigned char m_formationPreviewDecal[12];					// +0x014 AsciiString + two floats (50.0)
	unsigned char m_formationPreviewItemDecal[12];				// +0x020 AsciiString + two floats (50.0)
	unsigned char m_displayName[8];								// +0x02C AsciiString + UnicodeString (Rva0033B352Record)
	unsigned char m_description[8];								// +0x034 Rva0033B352Record
	unsigned char m_descriptionStrategic[8];					// +0x03C Rva0033B352Record
	unsigned char m_reviveText[8];								// +0x044 Rva0033B352Record
	unsigned char m_recruitText[8];								// +0x04C Rva0033B352Record
	unsigned char m_displayNameStrategic[8];					// +0x054 Rva0033B352Record
	AsciiString m_displayNameInvisibleForEnemy;					// +0x05C
	AsciiString m_hotkey;										// +0x060
	AsciiString m_nameString;									// +0x064
	AsciiString m_editorName;									// +0x068
	AsciiString m_defaultOwningSide;							// +0x06C
	AsciiString m_commandSetString;								// +0x070
	AsciiString m_selectedPortraitImageName;					// +0x074
	AsciiString m_buttonImageName;								// +0x078
	AsciiString m_upgradeCameoUpgradeNames[5];					// +0x07C
	AsciiString m_shadowTextureName;							// +0x090
	AsciiString m094;											// +0x094
	AsciiString m098;											// +0x098
	AsciiString m_experienceScalarTable;						// +0x09C
	unsigned char m_geometryInfo[0x5C];							// +0x0A0 GeometryInfo (vftable + 0x58)
	unsigned char m_geometryOther[12];							// +0x0FC vector (Rva0033C3F3)
	unsigned int m_kindof[7];									// +0x108 KindOf mask words (KindOfMaskType)
	unsigned char m124[0x1C0];									// +0x124 56 eight-byte records (Rva00254FE4Member)
	unsigned char m_behaviorModuleInfo[12];						// +0x2E4 ModuleInfo (Behavior)
	unsigned char m_drawModuleInfo[12];							// +0x2F0 ModuleInfo (Draw)
	unsigned char m_clientUpdateModuleInfo[12];					// +0x2FC ModuleInfo (ClientUpdate)
	unsigned char m_clientBehaviorModuleInfo[12];				// +0x308 ModuleInfo (ClientBehavior)
	unsigned int m_flammability[4];								// +0x314
	unsigned char m_prereqInfo[12];								// +0x324 vector<ProductionPrerequisite>
	unsigned char m_buildVariations[12];						// +0x330 vector<AsciiString>
	unsigned char m_equivalentTo[12];							// +0x33C vector<AsciiString>
	unsigned char m_buildFadeInOnCreateList[12];				// +0x348 vector<AsciiString>
	float m_buildFadeInOnCreateTime;							// +0x354
	unsigned char m_armorTemplateSets[12];						// +0x358 vector of 872-byte armor sets
	unsigned char m_armorTemplateSetFinder[12];					// +0x364 armor-set finder map
	unsigned char m_weaponTemplateSets[12];						// +0x370 vector<Rva002DFC30>
	unsigned char m_weaponTemplateSetFinder[12];				// +0x37C weapon-set finder map
	unsigned char m_perUnitSounds[12];							// +0x388 sound record set (Rva0025753F)
	unsigned char m_perUnitFX[12];								// +0x394 no-case AsciiString map
	unsigned char m3A0[12];										// +0x3A0 map (TemplateNameMapView)
	unsigned char m_locomotorSets[12];							// +0x3AC map<LocomotorSetType, vector<LocomotorTemplate *> >
	unsigned char m_browser[12];								// +0x3B8 vector
	unsigned char m3C4[2][0x14];								// +0x3C4 AssetList[2]
	unsigned char m_autoResolveArmor[12];						// +0x3EC vector of 260-byte records
	unsigned char m_autoResolveWeapon[12];						// +0x3F8 vector of 260-byte records
	unsigned int m_worldMapArmoryUpgradesAllowed[32];			// +0x404 128-byte mask
	unsigned int m484;											// +0x484
	unsigned int m488;											// +0x488
	unsigned int m48C;											// +0x48C
	unsigned int m_autoResolveBody;								// +0x490
	unsigned int m_autoResolveLeadership;						// +0x494
	unsigned int m_autoResolveCombatChain;						// +0x498
	unsigned int m_crowdResponseKey;							// +0x49C
	float m_fenceWidth;											// +0x4A0
	float m_fenceXOffset;										// +0x4A4
	float m_removeTerrainRadius;								// +0x4A8
	float m_visionRange;										// +0x4AC
	float m_shroudClearingRange;								// +0x4B0
	float m_visionSide;											// +0x4B4
	float m_visionRear;											// +0x4B8
	float m_visionBonusPercentPerFoot;							// +0x4BC
	float m_maxVisionBonusPercent;								// +0x4C0
	float m_minVisionBonusPercent;								// +0x4C4
	float m_visionBonusTestRadius;								// +0x4C8
	float m_emotionRange;										// +0x4CC
	float m_placementViewAngle;									// +0x4D0
	float m_factoryExitWidth;									// +0x4D4
	float m_factoryExtraBibWidth;								// +0x4D8
	float m_buildTime;											// +0x4DC
	float m_assetScale;											// +0x4E0
	float m_instanceScaleFuzziness;								// +0x4E4
	float m_shadowSizeX;										// +0x4E8
	float m_shadowSizeY;										// +0x4EC
	float m_shadowOffsetX;										// +0x4F0
	float m_shadowOffsetY;										// +0x4F4
	float m_shadowOpacityFadeInTime;							// +0x4F8
	float m_shadowOpacityFadeOutTime;							// +0x4FC
	float m_shadowSunAngle;										// +0x500
	float m_shadowMaxHeight;									// +0x504
	float m_maxDistanceForEngaged;								// +0x508
	float m_minCrushVelocityPercent;							// +0x50C
	float m_crushDecelerationPercent;							// +0x510
	float m_crushKnockback;										// +0x514
	float m_crushZFactor;										// +0x518
	float m_threatLevel;										// +0x51C
	unsigned int m_threatBreakdown;								// +0x520 all bits set by the constructor
	float m_minZIncreaseForVoiceMoveToHigherGround;				// +0x524
	float m_geometryFrontAngle;									// +0x528
	float m_pathfindDiameter;									// +0x52C
	float m_threatRadius;										// +0x530
	float m_healthBoxScale;										// +0x534
	float m_healthBoxHeightOffset;								// +0x538
	float m_firingArc;											// +0x53C
	float m_campnessValueRadius;								// +0x540
	unsigned int m_visionBonusTestSegments;						// +0x544
	unsigned int m_energyProduction;							// +0x548
	unsigned int m_energyBonus;									// +0x54C
	unsigned int m_displayColor;								// +0x550
	unsigned int m_occlusionDelay;								// +0x554
	unsigned int m_voiceAttackChargeTimeout;					// +0x558
	unsigned int m_engagedStateTimeout;							// +0x55C
	unsigned int m_voicePriority;								// +0x560
	unsigned int m_formationDepth;								// +0x564
	unsigned int m_formationWidth;								// +0x568
	unsigned int m_slopeLimitIndex;								// +0x56C
	unsigned int m_bountyValue;									// +0x570
	unsigned int m_evaEventDieOwner;							// +0x574
	unsigned int m_evaEventDieAlly;								// +0x578
	unsigned int m_evaEventDieEnemy;							// +0x57C
	unsigned int m_evaEventDamagedOwner;						// +0x580
	unsigned int m_evaEventDamagedFromShroudedSourceOwner;		// +0x584
	unsigned int m_evaEventDamagedByFireOwner;					// +0x588
	unsigned int m_evaEventSecondDamageFarFromFirstOwner;		// +0x58C
	float m_evaEventSecondDamageFarFromFirstScanRange;			// +0x590
	unsigned int m_evaEventSecondDamageFarFromFirstTimeoutMS;	// +0x594
	unsigned int m_evaEventAmbushed;							// +0x598
	unsigned int m_evaEnemyObjectSightedEvent;					// +0x59C
	unsigned int m_evaEnemyObjectSightedAfterRespawnEvent;		// +0x5A0
	unsigned int m_evaOnFirstSightingEventEnemy;				// +0x5A4
	unsigned int m_evaOnFirstSightingEventNonEnemy;				// +0x5A8
	unsigned int m_shadowOpacityStart;							// +0x5AC
	unsigned int m_shadowOpacityPeak;							// +0x5B0
	unsigned int m_shadowOpacityEnd;							// +0x5B4
	unsigned int m_supplyOverride;								// +0x5B8
	unsigned int m_displayMeleeDamage;							// +0x5BC
	unsigned int m_displayRangedDamage;							// +0x5C0
	unsigned int m_autoResolveUnitType;							// +0x5C4
	unsigned int m_evaEventDetectedEnemy;						// +0x5C8
	unsigned int m_evaEventDetectedAlly;						// +0x5CC
	unsigned int m_evaEventDetectedOwner;						// +0x5D0
	unsigned int m_campnessValue;								// +0x5D4
	unsigned short m5D8;										// +0x5D8
	unsigned short m_buildCost;									// +0x5DA
	unsigned short m_refundValue;								// +0x5DC
	unsigned short m_threatValue;								// +0x5DE
	unsigned short m_maxSimultaneousOfType;						// +0x5E0
	unsigned short m_shadowType;								// +0x5E2
	unsigned char m_isPrerequisite;								// +0x5E4
	unsigned char m_isBridge;									// +0x5E5
	unsigned char m5E6;											// +0x5E6
	unsigned char m_isTrainable;								// +0x5E7
	unsigned char m_isForbidden;								// +0x5E8
	unsigned char m5E9;											// +0x5E9
	unsigned char m5EA;											// +0x5EA
	unsigned char m_isGrabbable;								// +0x5EB
	unsigned char m_isHarvestable;								// +0x5EC
	unsigned char m_shadowOverrideLODVisibility;				// +0x5ED
	unsigned char m_shadowUseHouseColor;						// +0x5EE
	unsigned char m_shadowIsRotatingWithObject;					// +0x5EF
	unsigned char m_radarPriority;								// +0x5F0
	unsigned char m_transportSlotCount;							// +0x5F1
	unsigned char m_buildable;									// +0x5F2
	unsigned char m_buildCompletion;							// +0x5F3
	unsigned char m_editorSorting;								// +0x5F4
	unsigned char m_deadCollideSize;							// +0x5F5
	unsigned char m_thingClass;									// +0x5F6
	signed char m_structureRubbleHeight;						// +0x5F7 Byte: consumers sign-extend it
	unsigned char m5F8;											// +0x5F8
	unsigned char m_crusherLevel;								// +0x5F9
	unsigned char m_crushableLevel;								// +0x5FA
	unsigned char m_mountedCrusherLevel;						// +0x5FB
	unsigned char m_mountedCrushableLevel;						// +0x5FC
	unsigned char m_useCrushAttack;								// +0x5FD
	unsigned char m_crushOnlyWhileCharging;						// +0x5FE
	unsigned int m_crushWeapon;									// +0x600
	unsigned int m_crushRevengeWeapon;							// +0x604
	float m_ramPower;											// +0x608
	float m_ramZMult;											// +0x60C
	float m_shockwaveResistance;								// +0x610
	unsigned char m_crushAllies;								// +0x614
	unsigned int m_commandPoints;								// +0x618
	unsigned int m_commandPointBonus;							// +0x61C
	float m_liveCameraOffset[3];								// +0x620 Coord3D
	float m_liveCameraPitch;									// +0x62C
	unsigned char m_forceLuaRegistration;						// +0x630
	unsigned char m_showHealthInSelectionDecal;					// +0x631
	unsigned char m_keepSelectableWhenDead;						// +0x632
	unsigned char m_isAutoBuilt;								// +0x633
	unsigned char m_canPathThroughGates;						// +0x634
	unsigned char m_shouldClearShotsOnIdle;						// +0x635
	unsigned int m_heroSortOrder;								// +0x638
	unsigned int m_selectionPriority;							// +0x63C

};

typedef char ThingTemplateCanonicalSize[sizeof(ThingTemplate) == 0x640 ? 1 : -1];

#endif // __BFME2_THINGTEMPLATE_H_
