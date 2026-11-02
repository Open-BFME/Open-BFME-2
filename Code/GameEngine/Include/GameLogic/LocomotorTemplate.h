// Target facts (all addresses below are RVAs unless explicitly marked VA):
// Default ctor 0x001E4ABE (754 bytes) initializes Overridable at +0, then
// stores VA 0x00BDE8B4 at +0 (instruction 0x001E4AEC). Copy ctor 0x001E4DEB
// calls Overridable's copy ctor 0x003664DD at 0x001E4E01, then stores the same
// derived table at 0x001E4E11. Dtor 0x001E4DB0 restores it at 0x001E4DC1,
// releases the +0x10 string at 0x001E4DCE, then calls ~Overridable at
// 0x001E4DD9. The base destructor restores VA 0x00BDDC48 at 0x001E362C.
// These are derived/base lifetime tables, not competing LocomotorTemplate ABIs.
// The table at 0x007DE8B4 has exactly one slot: scalar deleting destructor
// 0x001E67A3, which calls 0x001E4DB0. The following bytes at 0x007DE8B8 are
// UTF-16 "RIF: Locomotor reloaded"; their first dword 0x00490052 is text,
// not a second function pointer. There are no additional virtual methods.
// Allocation sites 0x001E8B6F and 0x001E8B90 push 0x154 before operator new
// 0x0002FDA0 and default ctor calls 0x001E8B80/0x001E8BA1. The final byte
// fields are +0x150 and +0x151; four-byte alignment gives sizeof 0x154.
// The default ctor writes floats with MOVSS, integer frame counts at +0x2C,
// +0x44 and +0x50 from VA 0x00DBA4E4, and individual byte flags. The copy
// ctor and assignment 0x001E3955 copy these same offsets through +0x151.
// The FieldParse table 0x007DE2F8..0x007DE878 has 16-byte records containing
// token, parser, user data and member offset. Its names and parser types,
// checked against those stores, establish the following members:
//   +0x010 (4 bytes) m_name: name assignment 0x001E8BDF/0x001E8BE6; copy 0x001E4E17.
//   +0x014 (4 bytes) m_surfaces: FieldParse 0x007DE2F8, parser RVA 0x0002EB38.
//   +0x018 (4 bytes) m_lookAheadMult: FieldParse 0x007DE318, parser RVA 0x0002EFC0.
//   +0x01C (1 bytes) m_nonDirtyTransform: FieldParse 0x007DE328, parser RVA 0x0002E850.
//   +0x020 (4 bytes) m_speed: FieldParse 0x007DE308, parser RVA 0x00338BBD.
//   +0x024 (4 bytes) m_speedDamaged: FieldParse 0x007DE338, parser RVA 0x0002F1BA.
//   +0x028 (4 bytes) m_minSpeed: FieldParse 0x007DE3E8, parser RVA 0x0002F1BA.
//   +0x02C (4 bytes) m_turnTime: FieldParse 0x007DE348, parser RVA 0x00338B30.
//   +0x030 (4 bytes) m_turnTimeDamaged: FieldParse 0x007DE358, parser RVA 0x00338B30.
//   +0x034 (4 bytes) m_slowTurnRadius: FieldParse 0x007DE368, parser RVA 0x0002EFC0.
//   +0x038 (4 bytes) m_fastTurnRadius: FieldParse 0x007DE378, parser RVA 0x0002EFC0.
//   +0x03C (4 bytes) m_turnThreshold: FieldParse 0x007DE388, parser RVA 0x0002F0D5.
//   +0x040 (4 bytes) m_turnThresholdHS: FieldParse 0x007DE398, parser RVA 0x0002F0D5.
//   +0x044 (4 bytes) m_acceleration: FieldParse 0x007DE3A8, parser RVA 0x00338B30.
//   +0x048 (4 bytes) m_lift: FieldParse 0x007DE3B8, parser RVA 0x0002F1BA.
//   +0x04C (4 bytes) m_liftDamaged: FieldParse 0x007DE3C8, parser RVA 0x0002F1BA.
//   +0x050 (4 bytes) m_braking: FieldParse 0x007DE3D8, parser RVA 0x00338B30.
//   +0x054 (4 bytes) m_minTurnSpeed: FieldParse 0x007DE3F8, parser RVA 0x0002F1BA.
//   +0x058 (4 bytes) m_preferredHeight: FieldParse 0x007DE408, parser RVA 0x0002EFC0.
//   +0x05C (4 bytes) m_preferredAttackHeight: FieldParse 0x007DE428, parser RVA 0x0002EFC0.
//   +0x060 (4 bytes) m_preferredHeightDamping: FieldParse 0x007DE418, parser RVA 0x0002EFC0.
//   +0x064 (4 bytes) m_circlingRadius: FieldParse 0x007DE438, parser RVA 0x0002EFC0.
//   +0x068 (4 bytes) m_speedLimitZ: FieldParse 0x007DE448, parser RVA 0x00338BBD.
//   +0x06C (4 bytes) m_maxThrustAngle: FieldParse 0x007DE458, parser RVA 0x0002F0D5.
//   +0x070 (4 bytes) m_zAxisBehavior: FieldParse 0x007DE468, parser RVA 0x0002EC4E.
//   +0x074 (4 bytes) m_appearance: FieldParse 0x007DE478, parser RVA 0x0002EC4E.
//   +0x078 (4 bytes) m_formationPriority: FieldParse 0x007DE488, parser RVA 0x0002EC4E.
//   +0x07C (4 bytes) m_accDecTrigger: FieldParse 0x007DE498, parser RVA 0x0002EFC0.
//   +0x080 (4 bytes) m_walkDistance: FieldParse 0x007DE4A8, parser RVA 0x0002EFC0.
//   +0x084 (4 bytes) m_maxTurnWithoutReform: FieldParse 0x007DE4C8, parser RVA 0x0002F0D5.
//   +0x088 (4 bytes) m_accelerationPitchLimit: FieldParse 0x007DE4D8, parser RVA 0x0002F0D5.
//   +0x08C (4 bytes) m_bounceAmount: FieldParse 0x007DE4E8, parser RVA 0x003389DD.
//   +0x090 (4 bytes) m_pitchStiffness: FieldParse 0x007DE4F8, parser RVA 0x0002EFC0.
//   +0x094 (4 bytes) m_rollStiffness: FieldParse 0x007DE508, parser RVA 0x0002EFC0.
//   +0x098 (4 bytes) m_pitchDamping: FieldParse 0x007DE518, parser RVA 0x0002EFC0.
//   +0x09C (4 bytes) m_rollDamping: FieldParse 0x007DE528, parser RVA 0x0002EFC0.
//   +0x0A0 (4 bytes) m_pitchInDirectionOfZVelFactor: FieldParse 0x007DE538, parser RVA 0x0002EFC0.
//   +0x0A4 (4 bytes) m_maxOverlappedHeight: FieldParse 0x007DE4B8, parser RVA 0x0002EFC0.
//   +0x0A8 (4 bytes) m_forwardVelocityPitchFactor: FieldParse 0x007DE548, parser RVA 0x0002EFC0.
//   +0x0AC (4 bytes) m_lateralVelocityRollFactor: FieldParse 0x007DE558, parser RVA 0x0002EFC0.
//   +0x0B0 (4 bytes) m_forwardAccelerationPitchFactor: FieldParse 0x007DE568, parser RVA 0x0002EFC0.
//   +0x0B4 (4 bytes) m_lateralAccelerationRollFactor: FieldParse 0x007DE578, parser RVA 0x0002EFC0.
//   +0x0B8 (4 bytes) m_uniformAxialDamping: FieldParse 0x007DE588, parser RVA 0x0002EFC0.
//   +0x0BC (4 bytes) m_turnPivotOffset: FieldParse 0x007DE598, parser RVA 0x0002EFC0.
//   +0x0C0 (4 bytes) m_airborneTargetingHeight: FieldParse 0x007DE5E8, parser RVA 0x0002EF56.
//   +0x0C4 (4 bytes) m_closeEnoughDist: FieldParse 0x007DE658, parser RVA 0x0002EFC0.
//   +0x0C8 (1 bytes) m_closeEnoughDist3D: FieldParse 0x007DE668, parser RVA 0x0002E850.
//   +0x0CC (4 bytes) m_slideIntoPlaceTime: FieldParse 0x007DE678, parser RVA 0x00338B0A.
//   +0x0D0 (1 bytes) m_locomotorWorksWhenDead: FieldParse 0x007DE5D8, parser RVA 0x0002E850.
//   +0x0D1 (1 bytes) m_allowAirborneMotiveForce: FieldParse 0x007DE5C8, parser RVA 0x0002E850.
//   +0x0D2 (1 bytes) m_apply2DFrictionWhenAirborne: FieldParse 0x007DE5A8, parser RVA 0x0002E850.
//   +0x0D3 (1 bytes) m_downhillOnly: FieldParse 0x007DE5B8, parser RVA 0x0002E850.
//   +0x0D4 (1 bytes) m_stickToGround: FieldParse 0x007DE5F8, parser RVA 0x0002E850.
//   +0x0D8 (4 bytes) m_canMoveBackwards: FieldParse 0x007DE608, parser RVA 0x001E38F9.
//   +0x0DC (1 bytes) m_hasSuspension: FieldParse 0x007DE618, parser RVA 0x0002E850.
//   +0x0E0 (4 bytes) m_maximumWheelExtension: FieldParse 0x007DE638, parser RVA 0x0002EFC0.
//   +0x0E4 (4 bytes) m_maximumWheelCompression: FieldParse 0x007DE648, parser RVA 0x0002EFC0.
//   +0x0E8 (4 bytes) m_frontWheelTurnAngle: FieldParse 0x007DE628, parser RVA 0x0002F0D5.
//   +0x0EC (1 bytes) m_crewPowered: FieldParse 0x007DE688, parser RVA 0x0002E850.
//   +0x0ED (1 bytes) m_useTerrainSmoothing: FieldParse 0x007DE698, parser RVA 0x0002E850.
//   +0x0F0 (4 bytes) m_wanderWidthFactor: FieldParse 0x007DE6A8, parser RVA 0x0002EFC0.
//   +0x0F4 (4 bytes) m_wanderLengthFactor: FieldParse 0x007DE6B8, parser RVA 0x0002EFC0.
//   +0x0F8 (4 bytes) m_wanderAboutPointRadius: FieldParse 0x007DE6C8, parser RVA 0x0002EFC0.
//   +0x0FC (4 bytes) m_burningDeathRadius: FieldParse 0x007DE6D8, parser RVA 0x0002EFC0.
//   +0x100 (1 bytes) m_burningDeathIsCavalry: FieldParse 0x007DE6E8, parser RVA 0x0002E850.
//   +0x104 (4 bytes) m_chargeSpeed: FieldParse 0x007DE6F8, parser RVA 0x0002F1BA.
//   +0x108 (1 bytes) m_chargeAvailable: FieldParse 0x007DE708, parser RVA 0x0002E850.
//   +0x109 (1 bytes) m_chargeIgnoresCondition: FieldParse 0x007DE718, parser RVA 0x0002E850.
//   +0x10A (1 bytes) m_enableHighSpeedTurnModelconditions: FieldParse 0x007DE728, parser RVA 0x0002E850.
//   +0x10B (1 bytes) m_waitForFormation: FieldParse 0x007DE738, parser RVA 0x0002E850.
//   +0x10C (4 bytes) m_rudderCorrectionDegree: FieldParse 0x007DE748, parser RVA 0x0002EFC0.
//   +0x110 (4 bytes) m_rudderCorrectionRate: FieldParse 0x007DE758, parser RVA 0x0002EFC0.
//   +0x114 (4 bytes) m_elevatorCorrectionDegree: FieldParse 0x007DE768, parser RVA 0x0002EFC0.
//   +0x118 (4 bytes) m_elevatorCorrectionRate: FieldParse 0x007DE778, parser RVA 0x0002EFC0.
//   +0x11C (4 bytes) m_aeleronCorrectionDegree: FieldParse 0x007DE788, parser RVA 0x0002EFC0.
//   +0x120 (4 bytes) m_aeleronCorrectionRate: FieldParse 0x007DE798, parser RVA 0x0002EFC0.
//   +0x124 (4 bytes) m_swoopStandoffRadius: FieldParse 0x007DE7A8, parser RVA 0x0002EFC0.
//   +0x128 (4 bytes) m_swoopStandoffHeight: FieldParse 0x007DE7B8, parser RVA 0x0002EFC0.
//   +0x12C (4 bytes) m_swoopTerminalVelocity: FieldParse 0x007DE7C8, parser RVA 0x0002EFC0.
//   +0x130 (4 bytes) m_swoopAccelerationRate: FieldParse 0x007DE7D8, parser RVA 0x0002EFC0.
//   +0x134 (4 bytes) m_swoopSpeedTuningFactor: FieldParse 0x007DE7E8, parser RVA 0x0002EFC0.
//   +0x138 (4 bytes) m_backingUpSpeed: FieldParse 0x007DE7F8, parser RVA 0x0002F1BA.
//   +0x13C (1 bytes) m_backingUpStopWhenTurning: FieldParse 0x007DE808, parser RVA 0x0002E850.
//   +0x140 (4 bytes) m_backingUpDistanceMin: FieldParse 0x007DE818, parser RVA 0x0002EFC0.
//   +0x144 (4 bytes) m_backingUpDistanceMax: FieldParse 0x007DE828, parser RVA 0x0002EFC0.
//   +0x148 (4 bytes) m_backingUpAngle: FieldParse 0x007DE838, parser RVA 0x0002EFC0.
//   +0x14C (4 bytes) m_riverModifier: FieldParse 0x007DE848, parser RVA 0x0002F1BA.
//   +0x150 (1 bytes) m_scalesWalls: FieldParse 0x007DE858, parser RVA 0x0002E850.
//   +0x151 (1 bytes) m_turnWhileMoving: FieldParse 0x007DE868, parser RVA 0x0002E850.
// validate 0x001E38B9 tests +0x74 against 3 and clamps +0x28/+0x54;
// rva001E67BF (94 bytes) calls the copy ctor twice and clears byte +0x150.
// The constructor, copy constructor, destructor, assignment, validate and
// rva001E67BF names are ledger rows. Zero Hour Locomotor.h supplies the
// class, m_name, getFieldParse and friend_setName names; retail 0x001E8BE6
// assigns the string out of line through StringBase::set at 0x000366F0.

#pragma once

#ifndef __BFME2_LOCOMOTORTEMPLATE_H_
#define __BFME2_LOCOMOTORTEMPLATE_H_

#include "../Common/Overridable.h"
#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"

struct FieldParse;

class LocomotorTemplate : public Overridable
{
public:
	LocomotorTemplate();
	LocomotorTemplate(const LocomotorTemplate &other);
	virtual ~LocomotorTemplate();
	LocomotorTemplate &operator=(const LocomotorTemplate &other);

	const FieldParse *getFieldParse() const;
	void friend_setName(const AsciiString &name) { m_name = name; }
	void validate();
	LocomotorTemplate rva001E67BF();

	AsciiString m_name;	// +0x010
	int m_surfaces;	// +0x014
	float m_lookAheadMult;	// +0x018
	unsigned char m_nonDirtyTransform;	// +0x01C
	float m_speed;	// +0x020
	float m_speedDamaged;	// +0x024
	float m_minSpeed;	// +0x028
	int m_turnTime;	// +0x02C
	int m_turnTimeDamaged;	// +0x030
	float m_slowTurnRadius;	// +0x034
	float m_fastTurnRadius;	// +0x038
	float m_turnThreshold;	// +0x03C
	float m_turnThresholdHS;	// +0x040
	int m_acceleration;	// +0x044
	float m_lift;	// +0x048
	float m_liftDamaged;	// +0x04C
	int m_braking;	// +0x050
	float m_minTurnSpeed;	// +0x054
	float m_preferredHeight;	// +0x058
	float m_preferredAttackHeight;	// +0x05C
	float m_preferredHeightDamping;	// +0x060
	float m_circlingRadius;	// +0x064
	float m_speedLimitZ;	// +0x068
	float m_maxThrustAngle;	// +0x06C
	int m_zAxisBehavior;	// +0x070
	int m_appearance;	// +0x074
	int m_formationPriority;	// +0x078
	float m_accDecTrigger;	// +0x07C
	float m_walkDistance;	// +0x080
	float m_maxTurnWithoutReform;	// +0x084
	float m_accelerationPitchLimit;	// +0x088
	float m_bounceAmount;	// +0x08C
	float m_pitchStiffness;	// +0x090
	float m_rollStiffness;	// +0x094
	float m_pitchDamping;	// +0x098
	float m_rollDamping;	// +0x09C
	float m_pitchInDirectionOfZVelFactor;	// +0x0A0
	float m_maxOverlappedHeight;	// +0x0A4
	float m_forwardVelocityPitchFactor;	// +0x0A8
	float m_lateralVelocityRollFactor;	// +0x0AC
	float m_forwardAccelerationPitchFactor;	// +0x0B0
	float m_lateralAccelerationRollFactor;	// +0x0B4
	float m_uniformAxialDamping;	// +0x0B8
	float m_turnPivotOffset;	// +0x0BC
	int m_airborneTargetingHeight;	// +0x0C0
	float m_closeEnoughDist;	// +0x0C4
	unsigned char m_closeEnoughDist3D;	// +0x0C8
	float m_slideIntoPlaceTime;	// +0x0CC
	unsigned char m_locomotorWorksWhenDead;	// +0x0D0
	unsigned char m_allowAirborneMotiveForce;	// +0x0D1
	unsigned char m_apply2DFrictionWhenAirborne;	// +0x0D2
	unsigned char m_downhillOnly;	// +0x0D3
	unsigned char m_stickToGround;	// +0x0D4
	int m_canMoveBackwards;	// +0x0D8
	unsigned char m_hasSuspension;	// +0x0DC
	float m_maximumWheelExtension;	// +0x0E0
	float m_maximumWheelCompression;	// +0x0E4
	float m_frontWheelTurnAngle;	// +0x0E8
	unsigned char m_crewPowered;	// +0x0EC
	unsigned char m_useTerrainSmoothing;	// +0x0ED
	float m_wanderWidthFactor;	// +0x0F0
	float m_wanderLengthFactor;	// +0x0F4
	float m_wanderAboutPointRadius;	// +0x0F8
	float m_burningDeathRadius;	// +0x0FC
	unsigned char m_burningDeathIsCavalry;	// +0x100
	float m_chargeSpeed;	// +0x104
	unsigned char m_chargeAvailable;	// +0x108
	unsigned char m_chargeIgnoresCondition;	// +0x109
	unsigned char m_enableHighSpeedTurnModelconditions;	// +0x10A
	unsigned char m_waitForFormation;	// +0x10B
	float m_rudderCorrectionDegree;	// +0x10C
	float m_rudderCorrectionRate;	// +0x110
	float m_elevatorCorrectionDegree;	// +0x114
	float m_elevatorCorrectionRate;	// +0x118
	float m_aeleronCorrectionDegree;	// +0x11C
	float m_aeleronCorrectionRate;	// +0x120
	float m_swoopStandoffRadius;	// +0x124
	float m_swoopStandoffHeight;	// +0x128
	float m_swoopTerminalVelocity;	// +0x12C
	float m_swoopAccelerationRate;	// +0x130
	float m_swoopSpeedTuningFactor;	// +0x134
	float m_backingUpSpeed;	// +0x138
	unsigned char m_backingUpStopWhenTurning;	// +0x13C
	float m_backingUpDistanceMin;	// +0x140
	float m_backingUpDistanceMax;	// +0x144
	float m_backingUpAngle;	// +0x148
	float m_riverModifier;	// +0x14C
	unsigned char m_scalesWalls;	// +0x150
	unsigned char m_turnWhileMoving;	// +0x151
};

#endif
