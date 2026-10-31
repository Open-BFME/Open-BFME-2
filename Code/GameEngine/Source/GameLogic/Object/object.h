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
// whose class has no canonical header yet (AsciiString under its several include
// setups, GeometryInfo, WeaponSet, the STLport containers, BitFlags) are opaque storage
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
	int rva0028AF76() const;
	void *rva0028C197() const;

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
	unsigned char m_name[4];						// +0x088 AsciiString
	int m_8c;										// +0x08C
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
