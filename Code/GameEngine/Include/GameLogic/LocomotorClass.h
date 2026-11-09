// FILE: LocomotorClass.h /////////////////////////////////////////////////////////////////////////
// Desc:   Canonical BFME2 Locomotor. Named LocomotorClass.h so that units including shim
//         headers spelled GameLogic/Locomotor.h never reach this file.
//
// Target facts (RVAs unless marked VA):
//  - LocomotorStore::newLocomotor (0x001E4A81) pushes 0xB0 to operator new 0x0002FDA0 and
//    calls the ctor 0x001E449A (ret 8; its bool argument is never read): sizeof 0xB0, no
//    memory pool as in Zero Hour. The deleting dtor 0x001E4625 frees through 0x0002FD60.
//  - The ctor 0x001E449A and the copy ctor 0x001E4641 store VA 0x00BDE888 at +0 and raise
//    the live counter VA 0x00DFDC64; the dtor 0x001E3E43 stores VA 0x00BDE888, lowers the
//    counter, then stores Snapshot's VA 0x00BBB554. One Snapshot base at +0. The copy ctor,
//    the dtor, the deleting dtor and the assignment 0x001E3CF4 (called at 0x001E4679) are
//    rowed on this class.
//  - Table VA 0x00BDE888 has four slots: 0 deleting dtor 0x001E4625, 1 the shared empty body
//    0x000B3FD0, 2 0x001E3E56 returning "Locomotor" (VA 0x00BDE898), 3 xfer 0x001E525A.
//    0x00341E2D is AIGoingIdleState::xfer, slot 3 of table VA 0x00C11798 instead.
//  - Ctor stores: +0x04 the template's final override (inline getFinalOverride over
//    0x001E35DF), +0x08 and +0x14 zeroed triples, +0x20 1.0, +0x24/+0x28/+0x30/+0x34/+0x38
//    BIGNUM, +0x2C -1.0, +0x3C template +0xC4, +0x40 0.0, +0x44 0, +0x48/+0x4C/+0x50 template
//    +0x58/+0x5C/+0x60, +0x54 0.0, +0x58 PI/40, +0x5C 0.0, +0x60/+0x64 0, the identity
//    matrix at +0x68 (three 16-byte rows through the vector ctor iterator 0x00001423 with
//    0x0047A6A9), bytes +0x98..+0x9A, +0x9C 0, +0xA0/+0xA4 0.0, +0xA8 0, +0xAC 100, then
//    setFlag(10, template +0xC8) at 0x001E460D.
//  - xfer 0x001E525A transfers the triples at +0x08 and +0x14 through one Xfer slot (+0x60),
//    the floats +0x20..+0x58 (not +0x2C), +0x5C, +0xA0 and +0xA4 through slot +0x70, +0x44,
//    +0x60 and +0x64 through slot +0x78, bytes +0x98..+0x9A through slot +0x90 and 4 raw
//    bytes at +0x9C.
//  - Clamps: getMaxSpeed 0x001E46E1 by +0x28 and by +0x2C when not -1, getMaxTurnRate
//    0x001E3E9F by +0x38, 0x001E3F4D by +0x24, 0x001E4845 by +0x30, 0x001E488A by +0x34;
//    0x001E48CF returns +0x5C while the frame stamp +0x60 is current.
//  - setFlag 0x001E3459 sets bit f of +0x44; it is called with 1 (0x00343095), 3 (0x002638E4,
//    0x004A25EF), 4 (0x001E43C1), 6 (0x002638CC), 7 (0x001E7A72) and 10 (0x001E460D).
//  - LocomotorSet::addLocomotor (0x001E88FB, 0x001E8907) reads template +0x14 and +0xD3
//    through +0x04 inline: getLegalSurfaces and getIsDownhillOnly are inline. The row at
//    0x002BEDBE named getLegalSurfaces reads an OVERRIDE at +0x08 and is not this method.
// Donor (Zero Hour Locomotor.h) facts: the class, the Snapshot override names, LocoFlag, setFlag,
// getFlag and the inline accessors, and the fields m_template, m_maintainPos, m_brakingFactor,
// m_maxLift, m_maxSpeed, m_maxAccel, m_maxBraking, m_maxTurnRate, m_closeEnoughDist, m_flags,
// m_preferredHeight, m_preferredHeightDamping, m_angleOffset and m_offsetIncrement, matched to
// the offsets above by Zero Hour's ctor and xfer order and by the clamps. Fields Zero Hour lacks
// keep offset names. Methods follow the Locomotor ledger rows' decorated names.
// LocomotorTemplate stays forward-declared, so the inline accessors that read the template
// (getLegalSurfaces and the others) are left to units that include LocomotorTemplate.h.
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef CANONICAL_LOCOMOTOR_H
#define CANONICAL_LOCOMOTOR_H

#if !defined(__SNAPSHOT_H_) && !defined(BFME_SNAPSHOT_NAME_SLOT)
#define BFME_SNAPSHOT_NAME_SLOT
#endif
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"
#include "../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../Libraries/Source/WWVegas/WWMath/Matrix3DData.h"

class AsciiString;
class LocomotorTemplate;
class Object;
class Rva00375A73Context;
class Waypoint;
class Xfer;

class Locomotor : public Snapshot
{
	friend class LocomotorStore;

public:
	// Zero Hour's order; retail's setFlag calls confirm values 1, 3, 4, 6, 7 and 10.
	enum LocoFlag
	{
		IS_BRAKING = 0,
		ALLOW_INVALID_POSITION,
		MAINTAIN_POS_IS_VALID,
		PRECISE_Z_POS,
		NO_SLOW_DOWN_AS_APPROACHING_DEST,
		OVER_WATER,
		ULTRA_ACCURATE,
		MOVING_BACKWARDS,
		DOING_THREE_POINT_TURN,
		CLIMBING,
		IS_CLOSE_ENOUGH_DIST_3D,
		OFFSET_INCREASING
	};

	Locomotor(const LocomotorTemplate *tmpl, bool flag);		// 0x001E449A
	Locomotor(const Locomotor &that);							// 0x001E4641
	Locomotor &operator=(const Locomotor &that);				// 0x001E3CF4
	virtual ~Locomotor();										// 0x001E3E43 (slot 0: 0x001E4625)

protected:
	// Snapshot slots, spelled the way the unit selected Snapshot.h's (as Drawable.h does).
#ifdef BFME_SNAPSHOT_CAPITALIZED_SLOTS
	virtual void LoadPostProcess();								// slot 1, 0x000B3FD0
#else
	virtual void loadPostProcess();								// slot 1, 0x000B3FD0
#endif
#ifdef BFME_SNAPSHOT_NAME_SLOT
#ifdef BFME_SNAPSHOT_NONCONST_NAME_SLOT
	virtual const char *GetSnapshotName();						// slot 2, 0x001E3E56
#else
	virtual const char *GetSnapshotName() const;				// slot 2, 0x001E3E56
#endif
#else
	virtual void crc(Xfer *xfer);								// slot 2, 0x001E3E56
#endif
#ifdef BFME_SNAPSHOT_CAPITALIZED_SLOTS
#ifdef BFME_SNAPSHOT_REFERENCE_XFER
	virtual void DoXfer(Xfer &xfer);							// slot 3, 0x001E525A
#else
	virtual void DoXfer(Xfer *xfer);							// slot 3, 0x001E525A
#endif
#else
	virtual void xfer(Xfer *xfer);								// slot 3, 0x001E525A
#endif

public:
	float getMaxSpeed(Object *obj) const;						// 0x001E46E1
	float getMaxTurnRate(Object *obj) const;					// 0x001E3E9F
	AsciiString getTemplateName() const;						// 0x001E4A63
	void locoUpdate_moveTowardsAngle(Object *obj, float angle);	// 0x001EA0F4
	bool locoUpdate_maintainCurrentPosition(Object *obj);		// 0x001E84E5
	void moveTowardsPositionHorde(Object *obj, const Coord3D &goalPos, float onPathDistToGoal, float desiredSpeed);	// 0x001E756D
	bool moveTowardsPositionHordeOnClimbPortal(Object *obj, Waypoint *way);	// 0x001E7389
	bool rva001E4194(Object *obj);								// 0x001E4194
	void rva001E41FA(float angle);								// 0x001E41FA
	float rva001E6532(Object *obj, const Coord3D *goalPos, float height);	// 0x001E6532
	void rva001E68D7(Object *obj, const Coord3D *goalPos, float onPathDistToGoal, float desiredSpeed);	// 0x001E68D7
	void rva001E6B8B(Object *obj, const Coord3D *goalPos, float onPathDistToGoal, float desiredSpeed);	// 0x001E6B8B
	bool rva001E7ECA(Object *obj, const Coord3D *goalPos);		// 0x001E7ECA
	void rva001E9083(Object *obj, const Coord3D *goalPos, float onPathDistToGoal, float desiredSpeed);	// 0x001E9083
	bool rva001E9A00(Object *obj, float goalSpeed, float *pathDistance, Rva00375A73Context *path);	// 0x001E9A00
	void rva002638CC(bool value);								// 0x002638CC, setFlag(6)
	void rva002638E4(bool value);								// 0x002638E4, setFlag(3)
	void rva00343095(bool value);								// 0x00343095, setFlag(1)

	__forceinline float getPreferredHeight() const { return m_preferredHeight; }
	__forceinline float getCloseEnoughDist() const { return m_closeEnoughDist; }
	__forceinline bool isUltraAccurate() const { return getFlag(ULTRA_ACCURATE); }
	__forceinline bool isMovingBackwards() const { return getFlag(MOVING_BACKWARDS); }
	__forceinline void setAllowInvalidPosition(bool allow) { setFlag(ALLOW_INVALID_POSITION, allow); }
	__forceinline void setUsePreciseZPos(bool u) { setFlag(PRECISE_Z_POS, u); }
	__forceinline void setNoSlowDownAsApproachingDest(bool u) { setFlag(NO_SLOW_DOWN_AS_APPROACHING_DEST, u); }
	__forceinline void setUltraAccurate(bool u) { setFlag(ULTRA_ACCURATE, u); }

protected:
	void maintainCurrentPositionWings(Object *obj);				// 0x001E7CDF

private:
	__forceinline bool getFlag(LocoFlag f) const { return (m_flags & (1 << f)) != 0; }
	// Retail calls this out of line (0x001E3459); the in-class body emits that copy.
	inline void setFlag(LocoFlag f, bool b) { if (b) m_flags |= (1 << f); else m_flags &= ~(1 << f); }

public:
	const LocomotorTemplate *m_template;						// +0x04
	Coord3D m_maintainPos;										// +0x08
	Coord3D m_14;												// +0x14
	float m_brakingFactor;										// +0x20
	float m_maxLift;											// +0x24
	float m_maxSpeed;											// +0x28
	float m_2C;													// +0x2C
	float m_maxAccel;											// +0x30
	float m_maxBraking;											// +0x34
	float m_maxTurnRate;										// +0x38
	float m_closeEnoughDist;									// +0x3C
	float m_40;													// +0x40
	unsigned int m_flags;										// +0x44
	float m_preferredHeight;									// +0x48
	float m_4C;													// +0x4C
	float m_preferredHeightDamping;								// +0x50
	float m_angleOffset;										// +0x54
	float m_offsetIncrement;									// +0x58
	float m_5C;													// +0x5C
	unsigned int m_60;											// +0x60
	unsigned int m_64;											// +0x64
	Matrix3D m_68;												// +0x68
	bool m_98;													// +0x98
	bool m_99;													// +0x99
	bool m_9A;													// +0x9A
	int m_9C;													// +0x9C
	float m_A0;													// +0xA0
	float m_A4;													// +0xA4
	int m_A8;													// +0xA8
	int m_AC;													// +0xAC
};

#endif // CANONICAL_LOCOMOTOR_H
