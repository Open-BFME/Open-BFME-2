// FILE: object.h /////////////////////////////////////////////////////////////////////////////////
// Desc:   Canonical BFME2 Object (draft; not registered in reverse/canonical_classes.csv yet:
//         most merge donors still carry private Object views and class_gate would refuse
//         their merges). Evidence: reverse/attempt_support/object_header_evidence.md.
//
// Target facts:
//  - Object::Object (0x00298EA9, 3,525 bytes, ObjectConstructor.cpp) returns RET 0x14: four
//    arguments plus the hidden most-derived flag of a class with a virtual base. It
//    constructs Thing at +0, then every own member from +0x74 to +0x4CC.
//  - Object::~Object (0x00299CE4, ObjectDestructor.cpp) installs five vftables:
//    0x00BFC300 at +0x00 (Thing), 0x00BFC2F0 at +0x60 (Snapshot), 0x00BFC2D8 at +0x64,
//    0x00BFC2B8 at +0x6C and 0x00BFC290 at +0x70, the virtual base's 0x00BFC27C through
//    the vbptr at +0x68 with a vtordisp at vbase-4, and ends in ~Snapshot and ~Thing.
//  - Layout engine (build/fleet/layouts, retail_layouts.json; tools/retail_layout.py,
//    commit e1cef4cdb7): the constructor calls ??0Thing at +0 and ??0BfmeCtor001B3A20
//    (0x0028AADF) at +0x64 and stores the vftables of Rva005EEE6B (0x005EEE6B) at +0x6C
//    and Rva0028AB0D (0x0028AB0D) at +0x70, whose matched constructors store the same
//    tables; the vbtable at +0x68 places the one virtual base at +0x4D4. sizeof is 0x4D8:
//    `push 0x4D8; call operator new` at 0x0023CAF2 precedes the constructor call. The
//    non-virtual part ends at +0x4D0; the vtordisp sits at +0x4D0.
//  - The ledger's rows name the overriders by base: the +0x64 base's slot 0 is
//    rva00290EE0 (0x00290EE0), the +0x70 base's slots 0-1 rva0028C037 / rva0028C08D,
//    the +0x6C base's slot 0 getGeometryInfo (gen-alias 0x005FBE57), the virtual base's
//    slot() (0x00299C99); Snapshot's loadPostProcess (0x00293EFF), GetSnapshotName
//    (0x00299C6E) and xfer (0x00297684).
// Inferences: the bases past Thing and Snapshot have no recovered names; they take the
// placeholder names of their matched constructors, and the virtual base (no matched
// constructor of its own) the placeholder the +0x64 constructor's source gives it. Members
// whose class has no canonical header yet (GeometryInfo, WeaponSet, the STLport containers, BitFlags) are opaque storage
// of the constructor's size; the comment gives the type the constructor builds there.
// Field names follow the constructor and destructor, which took Zero Hour's names where
// the statement matched (m_id, m_team, m_ai, m_partitionData, ...); +0x438 is Zero
// Hour's m_privateStatus (isEffectivelyDead tests its bit 0); the rest are offset names.
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef __BFME2_OBJECT_H_
#define __BFME2_OBJECT_H_

#include "../../Common/Thing/thing.h"
#include "../../Common/GameLogicObjectLookupView.h"
#include "../../../../../reference/shims/moduledata/Common/Snapshot.h"
#include "../../../../../reference/shims/bfme2_ascii/ascii_string.h"

class AIGroup;
class AIUpdateInterface;
class AsciiString;
class BehaviorModule;
class BodyModuleInterface;
class ContainModuleInterface;
class Drawable;
class ExperienceTracker;
class FiringTracker;
class GeometryInfo;
class Module;
class UpdateModule;
class ModuleData;
class PartitionData;
class Player;
class Team;
class Xfer;
enum AbleToAttackType;
enum CanAttackResult;
enum CommandSourceType;
enum ObjectStatusTypes;
enum Relationship;
class Dict;
class Image;
class PolygonTrigger;
class Rva00346BC0;
class SpawnBehaviorInterface;
class ThingTemplate;
enum ArmorSetType;
enum WeaponChoiceCriteria;
struct BfmeCopyElementA;
struct Rva00290EABElem;
struct Rva00297612Entry;
class AttributeModifierPoolUpdate;
class CommandButton;
class Coord2D;
class DamageInfo;
class DockUpdateInterface;
class ExitInterface;
class Matrix3D;
class RadarObject;
class Rva0028C570;
class Rva00373EC6;
class Rva004B555F;
class SpecialAbilityUpdate;
class SpecialPowerCompletionDie;
class SpecialPowerModuleInterface;
class SpecialPowerTemplate;
class UpgradeTemplate;
class Weapon;
enum CellShroudStatus;
enum DamageType;
enum DeathType;
enum DisabledType;
enum KindOfType;
enum ModelConditionFlagType;
enum NameKeyType;
enum ObjectID;
enum ObjectScriptStatusBit;
enum PathfindLayerEnum;
enum SpecialPowerType;
enum VeterancyLevel;
enum WeaponBonusConditionType;
enum WeaponLockType;
enum WeaponSetType;
enum WeaponSlotType;
enum WhichTurretType;
struct Arg1_004DEA70;
struct Coord3D;
struct Coord3DBase;
struct Rva0028AC4EEntry;

// The +0x64 base's own vftable comes from its first base (Object overrides slot 0 with
// rva00290EE0); its vbptr follows.
class BfmeCtorFirstBase001B3A20
{
public:
	virtual AsciiString rva00290EE0() = 0;
};

// The virtual base, at Object+0x4D4 (vftable 0x00BFC27C) through the vbptr at +0x68.
class BfmeCtorVirtualBase001B3A20
{
public:
	virtual void *slot() const = 0;
};

// Object+0x64: ??0BfmeCtor001B3A20@@QAE@XZ (0x0028AADF).
class BfmeCtor001B3A20 : public BfmeCtorFirstBase001B3A20, public virtual BfmeCtorVirtualBase001B3A20
{
public:
	BfmeCtor001B3A20();
};

// Object+0x6C: ??0Rva005EEE6B@@QAE@XZ (0x005EEE6B); Object's table 0x00BFC2B8.
class Rva005EEE6B
{
public:
	virtual const GeometryInfo &getGeometryInfo() const = 0;
};

// Object+0x70: ??0Rva0028AB0D@@QAE@XZ (0x0028AB0D); Object's table 0x00BFC290.
class Rva0028AB0D
{
public:
	virtual Coord3D rva0028C037() = 0;
	virtual Coord3D rva0028C08D() = 0;
};

//-------------------------------------------------------------------------------------------------
class Object : public Thing, public Snapshot, public BfmeCtor001B3A20, public Rva005EEE6B,
	public Rva0028AB0D
{
public:
	Object(const ThingTemplate *thingTemplate, const struct CreateMask *mask, Team *team, ObjectID id);

	virtual void loadPostProcess();
#ifdef BFME_SNAPSHOT_NAME_SLOT
	virtual const char *GetSnapshotName() const;
#else
	virtual void crc(Xfer *xfer);
#endif
	virtual AsciiString rva00290EE0();
	virtual void *slot() const;
	virtual const GeometryInfo &getGeometryInfo() const;
	virtual Coord3D rva0028C037();
	virtual Coord3D rva0028C08D();

	ObjectID getID() const { return m_id; }
	Team *getTeam() { return m_team; }
	Player *getControllingPlayer() const;
	// ZH Object.h public API; SupplyTruck's keyed dock tests inline this call.
	UpdateModule *findUpdateModule(NameKeyType key) const { return (UpdateModule *)findModule(key); }
	bool testStatus(ObjectStatusTypes bit) const;
	void setStatus(ObjectStatusTypes bit, bool set);
	bool isEffectivelyDead() const { return (m_privateStatus & 1) != 0; }
	Relationship getRelationship(const Object *that) const;
	CanAttackResult getAbleToAttackSpecificObject(AbleToAttackType attackType, const Object *target,
		CommandSourceType commandSource) const;
	ContainModuleInterface *getContain() const { return m_contain; }
	BodyModuleInterface *getBodyModule() const { return m_body; }
	// Matched PickupStuffUpdate::update, RVA 0x0049212B: tests Object+0x258.
	AIUpdateInterface *getAI() const { return m_ai; }
	AIUpdateInterface *getAIUpdateInterface() { return m_ai; }
	const AIUpdateInterface *getAIUpdateInterface() const { return m_ai; }
	Object *getContainedBy() { return m_containedBy; }
	BehaviorModule **getBehaviorModules() const { return m_behaviors; }
	ExperienceTracker *getExperienceTracker() { return m_experienceTracker; }
	const ExperienceTracker *getExperienceTracker() const { return m_experienceTracker; }
	ObjectID getProducerID() const { return m_producerID; }

	int rva0028AF76() const;
	void *rva0028C197() const;

public:
	RadarObject * friend_getRadarData();
	Object * dlink_next_TeamMemberList() const;
	PathfindLayerEnum getLayer() const;
	void friend_setPartitionData(PartitionData *);
	Weapon const * getCurrentWeapon(WeaponSlotType *) const;
	bool isKindOf(KindOfType) const;
	bool isAbleToAttack() const;
	void friend_notifyOfNewMapBoundary();
	SpecialPowerCompletionDie * findSpecialPowerCompletionDie() const;
	void setProducer(Object *);
	CanAttackResult getAbleToUseWeaponAgainstTarget(AbleToAttackType, Object const *, Coord3D const *, CommandSourceType) const;
	DockUpdateInterface * getDockUpdateInterface();
	bool rva0028AC62() const;
	float rva0028AC7D() const;
	int rva0028ADF7(int) const;
	bool getAmmoPipShowingInfo(void **, unsigned int *) const;
	int rva0028B511() const;
	void friend_setUndetectedDefector(bool);
	void rva0028AE9B(int);
	bool rva0028AFBB() const;
	bool isLocallyControlled() const;
	bool isStructure() const;
	bool isFactionStructure() const;
	float rva0028D2C5(void *) const;
	bool isSelectable() const;
	Rva0028AC4EEntry const * rva0028AC4E() const;
	Object * rva002931F5(bool);
	bool rva00293926(KindOfType);
	int rva002933CD();
	int rva0028B38D() const;
	void * rva0029439D();
	bool rva002931BA();
	float rva0028B842() const;
	ObjectID getSoleHealingBenefactor() const;
	int rva0028B7C8() const;
	void setShroudClearingRange(float);
	void * rva0028BCF4() const;
	void * rva0028BD17() const;
	void updateUpgradeModules();
	void rva00293003(void const *);
	void rva00293077(void const *);
	bool rva0028C1CC() const;
	SpecialPowerModuleInterface * findSpecialPowerModuleInterface(SpecialPowerType) const;
	bool getSingleLogicalBonePosition(char const *, Coord3D *, Matrix3D *) const;
	bool hasUpgradeMask(int) const;
	bool rva0028C264(int *, int);
	bool rva0028C4ED() const;
	bool hasUpgrade(UpgradeTemplate const *) const;
	AsciiString const * rva00290E67() const;
	bool isOutOfAmmo() const;
	void rva0028BA85() const;
	void rva0028B265() const;
	void rva0028B3D7() const;
	void setSelectable(bool);
	void leaveGroup();
	void rva0028C0F2(unsigned int);
	void rva0028C20F(int);
	bool rva0029091E(unsigned int) const;
	void rva0028FB6F(void *);
	void rva00293275(AsciiString);
	SpecialAbilityUpdate * findSpecialAbilityUpdate(SpecialPowerType) const;
	void reactToTurretChange(WhichTurretType, float, float);
	bool rva0028B3A6() const;
	void rva0028B72A() const;
	float rva00263763(void const *) const;
	Rva00373EC6 * rva0028F4BC();
	int rva0028F4EF();
	bool rva0028F518();
	void kill(DamageType, DeathType);
	void rva0028CFB2(int const *, int const *);
	void setWeaponSetFlag(WeaponSetType);
	void clearWeaponSetFlag(WeaponSetType);
	void rva00290AC1(Rva0028C570 const &);
	bool setWeaponLock(WeaponSlotType, WeaponLockType);
	void setSpecialModelConditionState(ModelConditionFlagType, unsigned int);
	void enterGroup(AIGroup *);
	void rva0028AE6D();
	bool isSignificantlyAboveTerrain() const;
	void setWeaponBonusCondition(WeaponBonusConditionType);
	void rva0028DA28();
	bool rva002943B2(Player const *);
	void * rva0028BE7F(Arg1_004DEA70 *, Coord3DBase const *);
	ExitInterface * getObjectExitInterface() const;
	bool isMassSelectable() const;
	bool isMobile() const;
	CellShroudStatus getShroudStatusForPlayer(int) const;
	void rva0028BBF3(Object *);
	void rva00295844(float);
	void rva0028AB4E() const;
	void releaseWeaponLock(WeaponLockType);
	bool rva002922D9(CommandButton const *);
	void onDestroy();
	float getVisionRange() const;
	bool rva0028C149(int, float *, int);
	void rva0028DA67();
	void rva00290DBB(Player *, Player *);
	float rva002972B1(float);
	void maskObject(bool);
	void calcNaturalRallyPoint(Coord2D *);
	bool rva0028C15E(int, float *, int, int);
	void rva0028ACDC(int);
	void rva0028ACEE(int, int);
	void setCustomIndicatorColor(int);
	int getIndicatorColor() const;
	int getNightIndicatorColor() const;
	void setLayer(PathfindLayerEnum);
	void setCaptured(bool);
	void rva0028B701(float);
	void rva0028EC68(int, void *, int);
	void rva0028EC88(int);
	void forceEmotion(int, float, int);
	void rva00291080(bool);
	void setVisionRange(float);
	void setGeometryInfoZ(float);
	void * rva0028BC58(int);
	bool rva0029137E(AsciiString &);
	int getTransportSlotCount();
	void friend_adjustPowerForPlayer(bool);
	bool GetGoalPosition(Coord3D *) const;
	void SwapForExchange(Object *);
	void updateShroudNow();
	void onCapture(Player *, Player *);
	void AddCreateAHeroSpecialPowerUpgrade(Rva004B555F *);
	void Get2DCenterVectorTo(Coord3D *, Coord3D const *) const;
	bool dlink_isInList_TeamMemberList(Object * const *) const;
	void setCommandSetStringOverride(AsciiString const &);
	void rva0028BAC0();
	void rva00298AAD(Team *);
	void rva00295FA9(Object *);
	void teleportTo(Coord3D const *, bool);
	SpecialPowerModuleInterface * getSpecialPowerModule(SpecialPowerTemplate const *) const;
	void rva00346C53(ObjectStatusTypes, bool);
	void rva0028FC18();
	void setTeam(Team *);
	void attemptDamage(DamageInfo *);
	bool addAttributeModifierToPool(AsciiString const &, int);
	float GetRelativeAngle(Coord3D const *) const;
	bool rva0028F44C(Object const *) const;
	void defect(Team *, unsigned int);
	void clearStatus(ObjectStatusTypes);
	void doCommandButton(CommandButton const *, int, bool);
	void friend_bindToDrawable(Drawable *);
	Weapon * getCurrentWeapon(WeaponSlotType *);
	void goDownOnCorpse(Object *);
	bool isUsingAirborneLocomotor() const;
	void makeDirty();
	void onVeterancyLevelChanged(VeterancyLevel, VeterancyLevel);
	void rva0028B8A6(bool);
	void rva00291A8C(float, float, float, AsciiString const &);
	char rva00294815();
	bool rva0029493F(Object *, int);
	int rva00294ADD(int);
	void defect(Object *, bool);
	void rva0029A12B();
	void setDisabled(DisabledType);
	void setEffectivelyDead(bool);
	void setScriptStatus(ObjectScriptStatusBit, bool);
	void rva0037710C(ObjectStatusTypes);
	bool getSingleLogicalBonePositionOnTurret(WhichTurretType, char const *, Coord3D *, Matrix3D *) const;
	void rva0028DB3C();
	void rva00295A84(Object *);
	bool affectedByUpgrade(UpgradeTemplate const *) const;
	bool rva00291837() const;
	signed char rva0028CE7B() const;
	void rva002949AE(int, int, float);
	void setDisabledUntil(DisabledType, unsigned int);
	bool rva00294471(void *, int);
	bool rva0028D900(float *, float *);
protected:
	Module * findModule(NameKeyType) const;
private:
	AttributeModifierPoolUpdate * findAttributeModifierPoolUpdate() const;

public:
	SpawnBehaviorInterface * getSpawnBehaviorInterface() const;
	Coord3D * getPlanarDirectionTo(Coord3D *, Object const *) const;
	bool isCurWeaponLocked() const;
	bool isNeutralControlled() const;
	Weapon * findWaypointFollowingCapableWeapon();
	bool isInList(Object **) const;
	void setBuilder(Object const *);
	void rva0028D282(void *);
	void attemptHealing(float, Object const *);
	void healCompletely();
	float rva002C97E8(Coord3D const *, Coord3D const *) const;
	void setArmorSetFlag(ArmorSetType);
	void clearArmorSetFlag(ArmorSetType);
	void rva0028B95F();
	bool hasAnyWeapon() const;
	bool isInside(PolygonTrigger *);
	ObjectID rva0028B85B() const;
	void * rva0028BD3A() const;
	void * rva0028C1A9() const;
	ObjectID rva0028C513() const;
	unsigned char rva00290FBB() const;
	void rva002900E0(int);
	void rva002903C3();
	void rva002903EF();
	void removeUpgrade(UpgradeTemplate const *);
	void rva002900FA(int);
	int getMultiLogicalBonePosition(char const *, int, Coord3D *, Matrix3D *, bool, int) const;
	void rva0028BAAE(int);
	void rva0028B292(int) const;
	void rva0028B1D4(int, int) const;
	void * rva0028BD5D(int) const;
	bool rva002E6B89();
	void rva0028C4B6();
	float rva002637E2(Coord3D const *, Coord3D const *) const;
	float rva002636F6(Coord3D const *, void const *, Coord3D const *) const;
	void updateTriggerAreaFlags();
	void rva0028B31A(int);
	void rva00293105();
	bool didEnter(PolygonTrigger *);
	bool didExit(PolygonTrigger *);
	void rva0028BFF9(unsigned int);
	bool attemptHealingFromSoleBenefactor(float, Object const *, unsigned int);
	void rva00291298(AsciiString, int);
	void rva00290758(int, int);
	void rva0029130C(int);
	void rva00293E64(Dict *);
	void rva0028EBDA(bool);
	void rva0028CFF5(int const *, bool);
	void clearModelConditionState(unsigned int);
	void setModelConditionState(unsigned int);
	void clearAndSetModelConditionState(unsigned int, unsigned int);
	void rva0029004B();
	bool rva0028CC7C(int);
	bool rva0028B35B(Object const *) const;
	void topple(Coord3D const *, float, unsigned int);
	int rva0028B875() const;
	Object * rva0028ACA0() const;
	float getShroudClearingRange() const;
	float getLargestWeaponRange() const;
	void rva00291C84(Matrix3D const *);
	int rva0028C173() const;
	void rva0028ACCA(int);
	void rva0028AD00(int, float, int);
	void rva0028AD22();
	void rva0028AD32();
	void rva0028AD7C();
	void rva0028AD8C();
	void reloadAllAmmo(bool);
	bool chooseBestWeaponForTarget(Object const *, WeaponChoiceCriteria, CommandSourceType);
	int getLastVictimID() const;
	int rva0028AF97();
	void removeCustomIndicatorColor();
	void * rva0028BC94();
	void setEmotion(int, void *);
	void rva0028D253();
	void rva0028CDB6();
	void rva00290095();
	void rva0028AB75(bool);
	void rva0029895A(BfmeCopyElementA *);
	void clearWeaponBonusCondition(WeaponBonusConditionType);
	void rva0028BC4D();
	void setStatusForHorde(Rva00346BC0 const &, bool);
	void rva0028CDEB(Rva00346BC0 const &, bool);
	void setFiringConditionForCurrentWeapon();
	void removeFromList(Object **, Object **);
	void setWeaponSetFlagForHorde(WeaponSetType);
	void clearWeaponSetFlagForHorde(WeaponSetType);
	void clearModelConditionFlagsForHorde(int const *);
	void setModelConditionFlagsForHorde(int const *);
	void clearAndSetModelConditionFlagsForHorde(int const *, int const *);
	void replaceModelConditionFlagsForHorde(int const *, bool);
	void setReceivingDifficultyBonus(bool);
	int GetGoalLayer() const;
	float GetGoalAngle() const;
	bool GetPathfinderPos(Coord3D *) const;
	bool IsAtGoalPosition() const;
	void * getDisplayName();
	void onContainedBy(Object *);
	void WallUpgradeSell();
	void restoreObjectToWorld(Coord3D const *);
	void clearModelConditionStateForHorde(ModelConditionFlagType);
	void setModelConditionStateForHorde(ModelConditionFlagType);
	void clearAndSetModelConditionStateForHorde(ModelConditionFlagType, ModelConditionFlagType);
	void restoreOriginalTeam();
	BehaviorModule * rva0028F2C4(int) const;
	SpecialPowerTemplate const * GetCreateAHeroSpecialPower(unsigned int);
	void fireCurrentWeapon(Object *, int);
	void dlink_prependTo_TeamMemberList(Object **);
	void dlink_removeFrom_TeamMemberList(Object **);
	void fireCurrentWeapon(Coord3D const *);
	AsciiString const & rva00292330(AsciiString const &);
	int isNonFactionStructure() const;
	void rva00297612();
	void rva002975AC(Rva00297612Entry *);
	void setTemporaryTeam(Team *);
	void removeAttributeModifierFromPool(AsciiString const &);
	void rva0023D3AF(void *);
	void rva0028DAB9();
	bool rva0028DB0F(bool) const;
	Object * adjustVictim(Object *, bool, int);
	void bfmeTransferReplacementState(Object *);
	bool canCrushOrSquishNoAlly(Object *, int);
	bool clearDisabled(DisabledType);
	void doSpecialPower(SpecialPowerTemplate const *, unsigned int, bool);
	void doSpecialPowerAtLocation(SpecialPowerTemplate const *, Coord3D const *, unsigned int, bool);
	void doSpecialPowerAtMultipleLocations(SpecialPowerTemplate const *, Coord3D const *, int, unsigned int, bool);
	void doSpecialPowerAtObject(SpecialPowerTemplate const *, Object *, unsigned int, bool);
	Image const * getObjectSelectedPortraitImage();
	bool getWorldspaceBestContactPoint(Coord3D *, Coord3D const *, char const *, int, int, bool) const;
	void initObject();
	void onDie(DamageInfo *);
	void preFireCurrentWeapon(Object const *, Coord3D const *);
	void restoreObjectToWorldInternal();
	float rva0026381B(Coord3D const *) const;
	void rva0028DCC4();
	void rva0028B98B();
	Coord3D rva0028BE93() const;
	void rva0028C24C();
	void rva0028C2DD(Coord3D *) const;
	bool rva0028C428() const;
	bool rva0028CECF();
	void rva0028D412(Matrix3D const *);
	void checkDisabledStatus();
	ThingTemplate * rva002911B7();
	void rva002929F9(Object *);
	void rva00292EB3(DisabledType);
	bool rva00292ED0(DisabledType);
	void rva002930A9(void *);
	bool rva00293408();
	bool rva00295CA6();
	void rva00295F05(bool);
	void rva00297000(CommandButton const *, Object *, int, int);
	void doCommandButtonAtPosition(CommandButton const *, Coord3D const *, int, int);
	float rva0044E6B8(Object const *) const;
	void setFormationOffset(Coord2D const *);
	void setNextPosition(Coord3D const &);
	void setTriggerAreaFlagsForChangeInPosition();
	void setUserDestination(Coord2D const *);
	void tempRemoveObjectFromWorld();
	void updateObjValuesFromMapProperties(Dict *);
	Rva00290EABElem const * rva00290EAB(int) const;
	void rva0029041B(Player *);
	void rva00290496(Player *);
	float rva002C9846(Coord3D const *) const;
	float rva002C9856(Coord3D const *, Object const *) const;
	void clearMask(Rva00346BC0 const &);
	void rva00462457(Object *);
	void rva0047B985(Object *);
	float rva0028EFB8(Coord3D const *, Object const *, Coord3D const *) const;
	unsigned char rva002957FC();
	void appendToList(Object **, Object **);
	bool rva0023D39F() const;
	bool rva0023D3A7() const;
	void rva0028FCD9(int, int);
	float rva0028ED19(Coord3D const *, void const *, Coord3D const *) const;
	void rva0028E8FD(Coord3D *);
	Coord3D Get2DBorderVectorTo(Coord3D const *) const;
	Coord3D rva00265514(Object const *) const;
	bool isDisabled() const;
	void rva00296065(Rva00297612Entry *);
	void rva00294C1A(Object *, bool, float);
	void giveUpgrade(UpgradeTemplate const *);
	void rva0028D611(Object *, int, int);
	float rva0028F8A3(Object const *) const;
	void rva002934D9(ObjectScriptStatusBit);
protected:
	void setID(ObjectID);
	bool didEnterOrExit() const;
private:
	void setOrRestoreTeam(Team *, bool);

protected:
	virtual void xfer(Xfer *xfer);
	virtual void reactToTransformChange(const Matrix3D *oldMtx, const Coord3D *oldPos, float oldAngle);
	virtual Object *asObjectMeth() { return this; }
	virtual const Object *asObjectMeth() const { return this; }
	virtual ~Object();

public:
	ObjectID m_id;									// +0x074
	ObjectID m_producerID;							// +0x078
	ObjectID m_builderID;							// +0x07C
	int m_80;										// +0x080
	Drawable *m_drawable;							// +0x084
	AsciiString m_name;							// +0x088 ctor 0x00298F5A zeroes it, dtor 0x0029A077 releases it
	Object *m_next;								// +0x08C object list link (GameLogic::getFirstObject chain)
	int m_90;										// +0x090
	unsigned int m_status[4];						// +0x094 BitFlags<117>
	void *m_a4;										// +0x0A4
	unsigned char m_geometryInfo[0x5C];				// +0x0A8 GeometryInfo
	GeometryInfo *m_geometryClone;					// +0x104
	const unsigned char *m_108;						// +0x108
	unsigned char m_10c[0x4C];						// +0x10C
	Matrix3D m_158;									// +0x158
	int m_188;										// +0x188
	unsigned char m_18c[0x18];						// +0x18C
	bool m_1a4;										// +0x1A4
	bool m_1a5;										// +0x1A5
	bool m_1a6;										// +0x1A6
	AIGroup *m_group;								// +0x1A8
	float m_1ac;									// +0x1AC
	float m_visionRange;							// +0x1B0
	float m_shroudClearingRange;					// +0x1B4
	float m_1b8;									// +0x1B8
	float m_shroudRange;							// +0x1BC
	float m_1c0;									// +0x1C0
	float m_1c4;									// +0x1C4
	unsigned int m_disabledMask;					// +0x1C8 BitFlags<11>
	unsigned int m_disabledTillFrame[11];			// +0x1CC
	unsigned int m_1f8[11];							// +0x1F8
	void *m_224;									// +0x224
	void *m_228;									// +0x228
	void *m_22c;									// +0x22C
	void *m_230;									// +0x230
	void *m_234;									// +0x234
	void *m_238;									// +0x238
	void *m_23c;									// +0x23C
	FiringTracker *m_firingTracker;					// +0x240
	BehaviorModule **m_behaviors;					// +0x244
	bool m_248;										// +0x248
	bool m_249;										// +0x249
	Module *m_24c;									// +0x24C
	ContainModuleInterface *m_contain;				// +0x250
	BodyModuleInterface *m_body;					// +0x254
	AIUpdateInterface *m_ai;						// +0x258
	BehaviorModule *m_physics;						// +0x25C
	void *m_radarData;								// +0x260
	ExperienceTracker *m_experienceTracker;			// +0x264
	unsigned char m_268[0xC];						// +0x268 _STL::map<int, void *>
	Object *m_containedBy;							// +0x274
	ObjectID m_xferContainedByID;					// +0x278
	unsigned int m_containedByFrame;				// +0x27C
	float m_constructionPercent;					// +0x280
	unsigned char m_upgrades[0x80];					// +0x284
	Team *m_team;									// +0x304
	unsigned char m_originalTeamName[4];			// +0x308 AsciiString
	int m_indicatorColor;							// +0x30C
	Coord3D m_healthBoxOffset;						// +0x310
	float m_31c[2];									// +0x31C
	float m_324;									// +0x324
	int m_328[2];									// +0x328
	unsigned char m_weaponSet[0x40];				// +0x330 WeaponSet
	unsigned int m_370[4];							// +0x370 _STL::bitset<128>
	int m_380;										// +0x380
	unsigned char m_384[6];							// +0x384
	Coord3D m_38c;									// +0x38C
	void *m_398;									// +0x398
	void *m_39c;									// +0x39C
	void *m_3a0;									// +0x3A0
	unsigned char m_3a4[0x14];						// +0x3A4
	int m_3b8;										// +0x3B8
	int m_3bc;										// +0x3BC
	unsigned char m_triggerInfo[7][8];				// +0x3C0
	int m_3f8;										// +0x3F8
	int m_3fc[3];									// +0x3FC
	void *m_408;								// +0x408 _STL::list<CameraMarker>
	int m_40c;										// +0x40C
	int m_410;										// +0x410
	float m_414[2];									// +0x414
	unsigned char m_41c[4];							// +0x41C AsciiString
	unsigned char m_420[4];							// +0x420 AsciiString
	unsigned char m_424[4];							// +0x424 AsciiString
	unsigned int m_428;								// +0x428
	int m_42c;										// +0x42C
	int m_430;										// +0x430
	bool m_434;										// +0x434
	bool m_435;										// +0x435
	bool m_436;										// +0x436
	bool m_437;										// +0x437
	unsigned char m_privateStatus;					// +0x438
	bool m_439;										// +0x439
	bool m_43a;										// +0x43A
	bool m_43b;										// +0x43B
	bool m_43c;										// +0x43C
	void *m_440;								// +0x440 _STL::list<BfmePod124>
	float m_444;									// +0x444
	int m_448;										// +0x448
	int m_44c;										// +0x44C
	void *m_450;									// +0x450
	bool m_454;										// +0x454
	bool m_455;										// +0x455
	bool m_456;										// +0x456
	int m_458;										// +0x458
	int m_45c;										// +0x45C
	int m_460;										// +0x460
	int m_464;										// +0x464
	unsigned char m_468[0x18];						// +0x468
	bool m_480;										// +0x480
	int m_484;										// +0x484
	int m_488;										// +0x488
	bool m_48c;										// +0x48C
	int m_490;										// +0x490
	unsigned char m_494[4];							// +0x494 AsciiString
	int m_498;										// +0x498
	int m_49c;										// +0x49C
	int m_4a0;										// +0x4A0
	void *m_4a4[3];								// +0x4A4 _STL::vector<int>
	bool m_4b0;										// +0x4B0
	void *m_4b4[3];								// +0x4B4 _STL::vector<const ModuleData *>
	unsigned int m_4c0;								// +0x4C0
	PartitionData *m_partitionData;					// +0x4C4
	int m_4c8;										// +0x4C8
	int m_4cc;										// +0x4CC
	// +0x4D0 vtordisp, +0x4D4 the virtual base; sizeof 0x4D8
};

#endif // __BFME2_OBJECT_H_
