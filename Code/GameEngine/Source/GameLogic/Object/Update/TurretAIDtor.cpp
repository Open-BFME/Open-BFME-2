// cl: /O1 /MD /EHsc
// ??1TurretAI@@MAE@XZ retail 0x004D86C1 86B
// Zero Hour TurretAI::~TurretAI shape: stopRotOrPitchSound (the rowed
// ?rva004D82F6@TurretAI 0x004D82F6) then delete the turret state machine at
// +0x14 and clear it. Own vptrs C60D78 (+0) and C60D64 (+4, an interface base
// with no dtor); the inline Snapshot-style base dtor restores BBB554.
// Retail deletes through the slot-0 deleting dtor with flag 0 followed by the
// global ??3@YAXPAX@Z (a global-scope delete). Identity from the pin (slot 2
// of vtable 0x00C60D78 returns "TurretAI"). Helper class names are local.

class TurretAIStateMachine
{
public:
	virtual ~TurretAIStateMachine();
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
protected:
	virtual ~TurretAI();

public:
	void rva004D82F6();
	virtual void onWeaponFired();

private:
	unsigned char m_pad08[0x14 - 8];
	TurretAIStateMachine *m_turretStateMachine; // +0x14
};

TurretAI::~TurretAI()
{
	rva004D82F6();
	::delete m_turretStateMachine;
	m_turretStateMachine = 0;
}
