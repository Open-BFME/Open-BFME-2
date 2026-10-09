// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/iniexception
//
// ??0TurretAI@@QAE@PAVObject@@PBVTurretAIData@@W4WhichTurretType@@@Z retail
// 0x004D85B6..0x004D86B1 (251 bytes EH RET 0x0C). The only caller is at
// 0x0026ED1D. It stores the TurretAI vtables 0x00C60D78 (+0) and 0x00C60D64 (+4)
// that the rowed dtor 0x004D86C1 and deleting dtor 0x004D8974 restore. The
// +4 notify base's own vtable 0x00C078DC is stored first. Retail EH map
// 0x00D43234 has two states: the Snapshot-style base (0x0049B47C) and the
// new-expression cleanup (operator delete).
// Shape follows Zero Hour / Open-BFME-1 TurretAI::TurretAI (donor
// game/GameEngine/Source/GameLogic/AI/TurretAI_ctor_Thunk.cpp at
// 9cbfb551fe20dae985f91f2319d8997287b6a705). Fields are data +8 / turret +0x0C /
// owner +0x10 / machine +0x14 / enabled = !data+0x64 / firesWhileTurning =
// data+0x65 / continuousFireExpirationFrame +0x30 = -1. Retail has no
// sound member and no null-data check. It throws INIException(3 / "TurretAI
// MUST specify controlled weapon slots!") when data+0x4C is zero. The
// natural angle and pitch (data +8/+0xC) are read through Real getters as
// movss. The machine is built with plain new (0x40 bytes / rowed
// TurretStateMachine ctor 0x004D7CE6 with name key 0xA503DF7E) and started
// through its slot 7 (initDefaultState). WB 0x0134FED0 is the same body
// with the debug null-data check and the 0x48-byte machine.
// The base and notify-interface views repeat TurretAIDtor.cpp so both
// units emit identical vtable COMDATs. Fields at +0x20..+0x2C / +0x34 and
// +0x3F stay unnamed.
#include "Common/INIException.h"

class Object;
class Xfer;

enum WhichTurretType
{
	TURRET_INVALID = -1,
	TURRET_MAIN = 0,
	TURRET_ALT,
	MAX_TURRETS
};

class TurretAIData
{
public:
	unsigned char m_pad00[0x08];
	float m_naturalTurretAngle;			// +0x08
	float m_naturalTurretPitch;			// +0x0C
	unsigned char m_pad10[0x4C - 0x10];
	unsigned int m_turretWeaponSlots;	// +0x4C
	unsigned char m_pad50[0x64 - 0x50];
	bool m_initiallyDisabled;			// +0x64
	bool m_firesWhileTurning;			// +0x65
};

class TurretAI;

class TurretStateMachine
{
public:
	TurretStateMachine(TurretAI *owner, Object *obj, unsigned int nameKey);
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
	virtual int initDefaultState();		// slot 7
private:
	unsigned char m_pad04[0x40 - 0x04];
};

class TurretAISnapshotBase
{
public:
	virtual ~TurretAISnapshotBase() {}
};

class TurretAINotifyBase
{
public:
	virtual void onWeaponFired() = 0;
};

class TurretAI : public TurretAISnapshotBase, public TurretAINotifyBase
{
public:
	TurretAI(Object *owner, const TurretAIData *data, WhichTurretType tur);
protected:
	virtual ~TurretAI();
public:
	virtual void onWeaponFired();
	float getNaturalTurretAngle() const { return m_data->m_naturalTurretAngle; }
	float getNaturalTurretPitch() const { return m_data->m_naturalTurretPitch; }
private:
	const TurretAIData *m_data;					// +0x08
	WhichTurretType m_whichTurret;				// +0x0C
	Object *m_owner;							// +0x10
	TurretStateMachine *m_turretStateMachine;	// +0x14
	float m_angle;								// +0x18
	float m_pitch;								// +0x1C
	int m_20;
	int m_24;
	int m_28;
	int m_2C;
	int m_continuousFireExpirationFrame;		// +0x30
	int m_34;
	bool m_playRotSound;						// +0x38
	bool m_playPitchSound;						// +0x39
	bool m_positiveSweep;						// +0x3A
	bool m_didFire;								// +0x3B
	bool m_enabled;								// +0x3C
	bool m_firesWhileTurning;					// +0x3D
	bool m_isForceAttacking;					// +0x3E
	bool m_3F;									// +0x3F
};

TurretAI::TurretAI(Object *owner, const TurretAIData *data, WhichTurretType tur) :
	m_data(data),
	m_whichTurret(tur),
	m_owner(owner),
	m_turretStateMachine(0),
	m_20(1),
	m_24(0),
	m_28(0),
	m_2C(0),
	m_34(0),
	m_playRotSound(false),
	m_playPitchSound(false),
	m_positiveSweep(true),
	m_didFire(false),
	m_enabled(!data->m_initiallyDisabled),
	m_firesWhileTurning(data->m_firesWhileTurning),
	m_isForceAttacking(false),
	m_3F(false)
{
	m_continuousFireExpirationFrame = -1;
	if (m_data->m_turretWeaponSlots == 0)
		throw INIException(3, "TurretAI MUST specify controlled weapon slots!");
	m_angle = getNaturalTurretAngle();
	m_pitch = getNaturalTurretPitch();
	m_turretStateMachine = new TurretStateMachine(this, m_owner, 0xA503DF7E);
	m_turretStateMachine->initDefaultState();
}
