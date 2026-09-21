// ??0DeployStyleAIUpdateModuleData@@QAE@XZ
// partial score=0.95 date=2026-09-21
// cl: /O2 /MD /GX /DNDEBUG /arch:SSE
//
// ??0DeployStyleAIUpdateModuleData@@QAE@XZ, retail 0x00255154 (42 bytes).
// Frameless ctor over the pinned Transport base (0x26E5D7): installs the
// explicit vtable 0x00BF3440 first (Defector precedent: pointer-cast
// write, no virtuals declared anywhere so no vtable is emitted here; the
// address is unique image-wide with this ctor its sole installer), then
// zeroes m_unpackTime at +0x64 plus m_packTime at +0x68, clears the three
// turret bools at +0x6C/+0x6D/+0x6E, sets m_mustDeployToAttack at +0x6F,
// and nulls m_deployedAttributeModifier at +0x70. The _WriteBarrier
// between the vtable store and the member stores pins the vtable below
// the shared xor-zero register but above the zero stores (MarkerType
// _ReadWriteBarrier precedent refined: the full barrier traps the xor
// below the vtable, the write-only barrier lets the reg-only xor float
// above it). Flat classes throughout (no declared dtors anywhere) keep
// the body frameless. Field identity is the base-call buildFieldParse
// table 0x00BEECB0 (UnpackTime/PackTime/ResetTurretBeforePacking/
// TurretsFunctionOnlyWhenDeployed/TurretsMustCenterBeforePacking at
// +0x64/+0x68/+0x6C/+0x6D/+0x6E match BFME1's DeployStyleAIUpdateModuleData
// table verbatim at identical offsets, votes 5/3; BFME2 appends
// MustDeployToAttack plus DeployedAttributeModifier). Sole raw caller is
// the ModuleData factory 0x25517E which news 0x74.

class TransportAIUpdateModuleData
{
public:
	TransportAIUpdateModuleData();
	virtual ~TransportAIUpdateModuleData();

private:
	unsigned char m_pad[0x64 - 4];
};

class DeployStyleAIUpdateModuleData : public TransportAIUpdateModuleData
{
public:
	DeployStyleAIUpdateModuleData();

private:
	int m_unpackTime;				// +0x64
	int m_packTime;				// +0x68
	bool m_resetTurretBeforePacking;		// +0x6C
	bool m_turretsFunctionOnlyWhenDeployed;	// +0x6D
	bool m_turretsMustCenterBeforePacking;	// +0x6E
	bool m_mustDeployToAttack;			// +0x6F
	void *m_deployedAttributeModifier;		// +0x70
};

// ??0DeployStyleAIUpdateModuleData@@QAE@XZ @0x255154
DeployStyleAIUpdateModuleData::DeployStyleAIUpdateModuleData()
	: TransportAIUpdateModuleData()
{
	*(unsigned int *)this = 0x00BF3440;
	m_deployedAttributeModifier = 0;
	m_unpackTime = 0;
	m_packTime = 0;
	m_resetTurretBeforePacking = false;
	m_turretsFunctionOnlyWhenDeployed = false;
	m_turretsMustCenterBeforePacking = false;
	m_mustDeployToAttack = true;
}
