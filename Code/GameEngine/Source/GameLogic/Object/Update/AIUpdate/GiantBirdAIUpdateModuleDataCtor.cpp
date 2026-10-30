// cl: /DNDEBUG /MD /GX-
//
// ??0GiantBirdAIUpdateModuleData@@QAE@XZ, retail 0x0036812E (84 bytes).
// Frameless ModuleData ctor over the pinned TransportAIUpdateModuleData
// base (0x0026E5D7, size 0x64): installs vtable 0x00C4B6C8 explicitly
// (novtable), zeroes two int slots, zeroes two float slots, loads three
// float slots from compiler literals (100.0/10.0/1.0, DIR32-masked like the
// retail globals), and zeroes a trailing int slot. /GX- keeps the body
// frameless (declared virtual dtor plus calls would otherwise emit an
// __EH_prolog frame); /arch:SSE selects the retail movss/xorps float idiom.
// Donor: BFME1 GiantBirdAIUpdate.cpp (BFME2 layout shifted past the 0x64
// base with its own float/int tail).

extern "C" const void *const __identifier("??_7AnimalAIUpdateModuleData@@6B@")[];  // folded vftable 0x00C4B6C8 (3 classes), by its data-ledger name

class FXList;

class __declspec(novtable) TransportAIUpdateModuleData
{
public:
	TransportAIUpdateModuleData();
	virtual ~TransportAIUpdateModuleData();

private:
	unsigned char m_opaque[0x64 - 4];
};

class __declspec(novtable) GiantBirdAIUpdateModuleData : public TransportAIUpdateModuleData
{
public:
	GiantBirdAIUpdateModuleData();

	// Field names are the INI tokens of the retail parse table 0x00C178D8.
	int m_attackLocomotorType;	// +0x64 AttackLocomotorType
	int m_returnForAmmoLocomotorType;	// +0x68 ReturnForAmmoLocomotorType
	float m_grabTossTimeTrigger;	// +0x6C GrabTossTimeTrigger
	float m_grabTossHeightTrigger;	// +0x70 GrabTossHeightTrigger
	float m_followThroughDistance;	// +0x74 FollowThroughDistance
	float m_followThroughCheckStep;	// +0x78 FollowThroughCheckStep
	float m_followThroughGradient;	// +0x7C FollowThroughGradient
	const FXList *m_tossFX;	// +0x80 TossFX
};

GiantBirdAIUpdateModuleData::GiantBirdAIUpdateModuleData()
{
	*(unsigned int *)this = ((unsigned int)__identifier("??_7AnimalAIUpdateModuleData@@6B@"));
	m_attackLocomotorType = 0;
	m_returnForAmmoLocomotorType = 0;
	m_grabTossTimeTrigger = 0.0f;
	m_grabTossHeightTrigger = 0.0f;
	m_followThroughDistance = 100.0f;
	m_followThroughCheckStep = 10.0f;
	m_followThroughGradient = 1.0f;
	m_tossFX = 0;
}
