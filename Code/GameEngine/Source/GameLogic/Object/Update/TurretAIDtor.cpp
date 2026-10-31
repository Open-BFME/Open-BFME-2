// cl: /MD /EHsc
// ??1TurretAI@@MAE@XZ retail 0x004D86C1 86B
// Zero Hour TurretAI::~TurretAI shape: stopRotOrPitchSound (the rowed
// ?rva004D82F6@TurretAI 0x004D82F6) then delete the turret state machine at
// +0x14 and clear it. Own vptrs C60D78 (+0) and C60D64 (+4, an interface base
// with no dtor); the inline Snapshot base dtor restores BBB554.
// Retail deletes through the slot-0 deleting dtor with flag 0 followed by the
// global ??3@YAXPAX@Z (a global-scope delete). Identity from the pin (slot 2
// of vtable 0x00C60D78 returns "TurretAI"). The class view is the TU's.

#include "../../../../../../reference/shims/moduledata/Common/Snapshot.h"

// TurretAI.cpp TU view (one spelling in every file of the TU). The
// constructor 0x004D85B6 stores the Snapshot table 0x00BBB554 and then
// 0x00C60D78 at +0x00 and 0x00C60D64 at +0x04. 0x00C60D78 holds the deleting
// destructor 0x004D8974, loadPostProcess 0x004D80D4, the "TurretAI" name
// getter 0x004D86BB and xfer 0x004D7FAD (Snapshot's slots); 0x00C60D64 holds
// notifyFired 0x004D81D2 (+0x37 from the +0x04 base is +0x3B) and
// notifyNewVictimChosen 0x004D8B3F (ecx-4 before setTurretTargetObject).
// Field names follow the constructor, xfer 0x004D7FAD and the target setters.
class Object;
class Team;
class Xfer;
class TurretAI;
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

// TurretAIData, 0x70 bytes as TurretAIData::TurretAIData (0x004D7E6C) fills it.
class TurretAIData
{
public:
	TurretAIData();
	float m_turnRate;									// +0x00
	float m_pitchRate;									// +0x04
	float m_naturalTurretAngle;							// +0x08
	float m_naturalTurretPitch;							// +0x0C
	float m_turretFireAngleSweep[WEAPONSLOT_COUNT];		// +0x10
	float m_turretSweepSpeedModifier[WEAPONSLOT_COUNT];	// +0x28
	float m_firePitch;									// +0x40
	float m_minPitch;									// +0x44
	float m_groundUnitPitch;							// +0x48
	unsigned int m_turretWeaponSlots;					// +0x4C
	float m_minIdleScanAngle;							// +0x50
	float m_maxIdleScanAngle;							// +0x54
	unsigned int m_minIdleScanInterval;					// +0x58
	unsigned int m_maxIdleScanInterval;					// +0x5C
	unsigned int m_recenterTime;						// +0x60
	bool m_initiallyDisabled;							// +0x64
	bool m_firesWhileTurning;							// +0x65
	bool m_isAllowsPitch;								// +0x66
	float m_maxDeflectionCW;							// +0x68
	float m_maxDeflectionACW;							// +0x6C
};

// The 0x40-byte turret machine (vtable 0x00C609C8): deleting destructor in
// slot 0, initDefaultState in slot 7; getGoalObject is 0x004D7726.
class TurretStateMachine
{
public:
	TurretStateMachine(TurretAI *tai, Object *obj, unsigned int nameKey);
	virtual ~TurretStateMachine();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
	virtual int initDefaultState();		// slot 7
	Object *getGoalObject();
private:
	unsigned char m_pad04[0x40 - 0x04];
};

class TurretAINotifyBase
{
public:
	virtual void notifyFired() = 0;
	virtual void notifyNewVictimChosen(Object *victim) = 0;
};

class TurretAI : public Snapshot, public TurretAINotifyBase
{
public:
	TurretAI(Object *owner, const TurretAIData *data, WhichTurretType tur);
	TurretAI(EmitVtableTag *);
protected:
	virtual ~TurretAI();
public:
	virtual void loadPostProcess();
	virtual void notifyFired();
	virtual void notifyNewVictimChosen(Object *victim);
	float getTurretFireAngleSweepForWeaponSlot(WeaponSlotType slot) const;
	float getTurretSweepSpeedModifierForWeaponSlot(WeaponSlotType slot) const;
	void setTurretTargetObject(Object *victim, bool forceAttacking);
	void rva004D82F6();
	float getNaturalTurretAngle() const { return m_data->m_naturalTurretAngle; }
	float getNaturalTurretPitch() const { return m_data->m_naturalTurretPitch; }
protected:
	virtual void xfer(Xfer *xfer);
private:
	const TurretAIData *m_data;					// +0x08
	WhichTurretType m_whichTurret;				// +0x0C
	Object *m_owner;							// +0x10
	TurretStateMachine *m_turretStateMachine;	// +0x14
	float m_angle;								// +0x18
	float m_pitch;								// +0x1C
	unsigned int m_audio20;						// +0x20
	unsigned int m_enableSweepUntil;			// +0x24
	Team *m_victimInitialTeam;					// +0x28
	int m_target;								// +0x2C
	int m_continuousFireExpirationFrame;		// +0x30
	unsigned int m_sleepUntil;					// +0x34
	bool m_playRotSound;						// +0x38
	bool m_playPitchSound;						// +0x39
	bool m_positiveSweep;						// +0x3A
	bool m_didFire;								// +0x3B
	bool m_enabled;								// +0x3C
	bool m_firesWhileTurning;					// +0x3D
	bool m_isForceAttacking;					// +0x3E
	bool m_targetWasSetByIdleMood;				// +0x3F
};
// End of the TurretAI.cpp TU view.

TurretAI::~TurretAI()
{
	rva004D82F6();
	::delete m_turretStateMachine;
	m_turretStateMachine = 0;
}
