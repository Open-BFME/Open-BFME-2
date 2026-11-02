// Target facts: ctor RVA 0x004D85B6 stores VA 0x00C078DC at +4, then 0x00C60D78 at +0 and 0x00C60D64 at +4; dtor RVA 0x004D86C1 restores the latter pair and finally Snapshot's 0x00BBB554 (0x004D8707); unwind 0x00791212 calls ~Snapshot at 0x0049B47C. Primary slots at 0x00C60D78 are deleting dtor 0x004D8974, loadPostProcess 0x004D80D4, name 0x004D86BB ("TurretAI" at VA 0x00C60D88), xfer 0x004D7FAD. The name row is nonvirtual; GetSnapshotName declares the inherited slot separately.
// Target facts: 0x00C078DC has five purecall entries; 0x00C60D64 has notifyFired 0x004D81D2 ([ecx+0x37]=1), notifyNewVictimChosen 0x004D8B3F (ecx-=4), 0x004D8717 (ecx-=4; jump isWeaponSlotOnTurret), 0x004D86B1 ([ecx+0x28]==1), and zero-return 0x000D43D0. Zero Hour AIStateMachine.h names these five NotifyWeaponFiredInterface slots; there is no interface destructor. Allocation 0x0026ED00 pushes 0x40 before the ctor call at 0x0026ED1D. Ctor stores prove all fields below; xfer 0x004D7FAD independently addresses +0x18 through +0x3F, including eight separate bool bytes. 0x002626FA reads angle/pitch +0x18/+0x1C, 0x00262730 reads data+0, and 0x00262683 reads enabled +0x3C.
// Target facts: TurretAIData ctor 0x004D7E6C writes floats +0..+0x48, six-element arrays +0x10/+0x28, words +0x4C/+0x58/+0x5C/+0x60, bytes +0x64..+0x66, floats +0x68/+0x6C; no vptr. TurretAI ctor reads natural angles at data+8/+0xC and flags +0x64/+0x65; sound stop 0x004D82F6 consumes the four-byte handle +0x20. Member declarations follow the matched ledger; field and accessor names follow Zero Hour TurretAI.h where supported, with neutral names for the two target-only data fields. Neither Zero Hour's AudioEventRTS member nor its packed bools describe this target.

#pragma once

#ifndef BFME2_TURRETAI_H
#define BFME2_TURRETAI_H

#if !defined(__SNAPSHOT_H_) && !defined(BFME_SNAPSHOT_NAME_SLOT)
#define BFME_SNAPSHOT_NAME_SLOT
#endif
#include "../../../../../reference/shims/moduledata/Common/Snapshot.h"
class Xfer;

#if !defined(BFME_SNAPSHOT_NAME_SLOT) || defined(BFME_SNAPSHOT_CAPITALIZED_SLOTS) || defined(BFME_SNAPSHOT_NONCONST_NAME_SLOT)
#error TurretAI requires Snapshot's loadPostProcess, const GetSnapshotName and xfer slots
#endif

class Object;
class Team;
class TurretStateMachine;
struct Coord3D;
enum WeaponSlotType;
enum WhichTurretType;
enum UpdateSleepTime;
enum TurretTargetType;

class TurretAIData
{
public:
	TurretAIData();
	float m_turnRate;
	float m_pitchRate;
	float m_naturalTurretAngle;
	float m_naturalTurretPitch;
	float m_turretFireAngleSweep[6];
	float m_turretSweepSpeedModifier[6];
	float m_firePitch;
	float m_minPitch;
	float m_groundUnitPitch;
	unsigned int m_turretWeaponSlots;
	float m_minIdleScanAngle;
	float m_maxIdleScanAngle;
	unsigned int m_minIdleScanInterval;
	unsigned int m_maxIdleScanInterval;
	unsigned int m_recenterTime;
	bool m_initiallyDisabled;
	bool m_firesWhileTurning;
	bool m_isAllowsPitch;
	float field68;
	float field6C;
};

class NotifyWeaponFiredInterface
{
public:
	virtual void notifyFired() = 0;
	virtual void notifyNewVictimChosen(Object *victim) = 0;
	virtual bool isWeaponSlotOkToFire(WeaponSlotType slot) const = 0;
	virtual bool isAttackingObject() const = 0;
	virtual const Coord3D *getOriginalVictimPos() const = 0;
};

class TurretAI : public Snapshot, public NotifyWeaponFiredInterface
{
public:
	TurretAI(Object *owner, const TurretAIData *data, WhichTurretType turret);
protected:
	virtual ~TurretAI();
	virtual void xfer(Xfer *xfer);
public:
	virtual void loadPostProcess();
#ifdef BFME_SNAPSHOT_NAME_SLOT
	virtual const char *GetSnapshotName() const;
#else
	virtual void crc(Xfer *xfer);
#endif
	const char *name() const;
	virtual void notifyFired();
	virtual void notifyNewVictimChosen(Object *victim);
	virtual bool isWeaponSlotOkToFire(WeaponSlotType slot) const { return isWeaponSlotOnTurret(slot); }
	virtual bool isAttackingObject() const { return m_target == 1; }
	virtual const Coord3D *getOriginalVictimPos() const { return 0; }

	float getTurretFireAngleSweepForWeaponSlot(WeaponSlotType slot) const;
	float getTurretSweepSpeedModifierForWeaponSlot(WeaponSlotType slot) const;
	bool isWeaponSlotOnTurret(WeaponSlotType slot) const;
	bool isOwnersCurWeaponOnTurret() const;
	bool isTryingToAimAtTarget(const Object *victim) const;
	void recenterTurret();
	void setTurretEnabled(bool enabled);
	bool isTurretInNaturalPosition() const;
	void setTurretTargetObject(Object *victim, bool forceAttacking);
	void setTurretTargetPosition(const Coord3D *pos);
	UpdateSleepTime updateTurretAI();
	void rva004D82F6();
	bool friend_turnTowardsPitch(float pitch, float rateModifier);
	bool friend_turnTowardsAngle(float angle, float rateModifier, float relativeThreshold);
	TurretTargetType friend_getTurretTarget(Object *&object, Coord3D &position) const;
	bool friend_isSweepEnabled() const;
	bool friend_isAnyWeaponInRangeOf(const Object *object) const;
	void friend_checkForIdleMoodTarget();
	unsigned int rva004D837D();

	float getTurretAngle() const { return m_angle; }
	float getTurretPitch() const { return m_pitch; }
	float getTurnRate() const { return m_data->m_turnRate; }
	float getPitchRate() const { return m_data->m_pitchRate; }
	float getNaturalTurretAngle() const { return m_data->m_naturalTurretAngle; }
	float getNaturalTurretPitch() const { return m_data->m_naturalTurretPitch; }
	float getFirePitch() const { return m_data->m_firePitch; }
	float getMinPitch() const { return m_data->m_minPitch; }
	float getGroundUnitPitch() const { return m_data->m_groundUnitPitch; }
	float getMinIdleScanAngle() const { return m_data->m_minIdleScanAngle; }
	float getMaxIdleScanAngle() const { return m_data->m_maxIdleScanAngle; }
	unsigned int getMinIdleScanInterval() const { return m_data->m_minIdleScanInterval; }
	unsigned int getMaxIdleScanInterval() const { return m_data->m_maxIdleScanInterval; }
	unsigned int getRecenterTime() const { return m_data->m_recenterTime; }
	bool isAllowsPitch() const { return m_data->m_isAllowsPitch; }
	bool isTurretEnabled() const { return m_enabled; }
	bool isForceAttacking() const { return m_isForceAttacking; }
	Object *getOwner() { return m_owner; }
	const Object *getOwner() const { return m_owner; }
	bool friend_getPositiveSweep() const { return m_positiveSweep; }
	void friend_setPositiveSweep(bool positive) { m_positiveSweep = positive; }
	WhichTurretType friend_getWhichTurret() const { return m_whichTurret; }
	bool friend_getTargetWasSetByIdleMood() const { return m_targetWasSetByIdleMood; }
	const Team *friend_getVictimInitialTeam() const { return m_victimInitialTeam; }

private:
	void removeSelfAsTargeter();
	void startRotOrPitchSound();
public:
	const TurretAIData *m_data; // +0x08
	WhichTurretType m_whichTurret; // +0x0C
	Object *m_owner; // +0x10
	TurretStateMachine *m_turretStateMachine; // +0x14
	float m_angle; // +0x18
	float m_pitch; // +0x1C
	unsigned int m_audio20; // +0x20
	unsigned int m_enableSweepUntil; // +0x24
	Team *m_victimInitialTeam; // +0x28
	mutable TurretTargetType m_target; // +0x2C
	unsigned int m_continuousFireExpirationFrame; // +0x30
	unsigned int m_sleepUntil; // +0x34
	bool m_playRotSound; // +0x38
	bool m_playPitchSound; // +0x39
	bool m_positiveSweep; // +0x3A
	bool m_didFire; // +0x3B
	bool m_enabled; // +0x3C
	bool m_firesWhileTurning; // +0x3D
	bool m_isForceAttacking; // +0x3E
	mutable bool m_targetWasSetByIdleMood; // +0x3F
};

#endif
