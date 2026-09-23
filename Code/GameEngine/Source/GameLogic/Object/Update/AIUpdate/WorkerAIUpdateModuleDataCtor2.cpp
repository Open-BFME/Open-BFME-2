// cl: /O1 /MD /GX /DNDEBUG /arch:SSE
//
// ??0WorkerAIUpdateModuleData@@QAE@XZ, retail 0x00254434 (101 bytes).
// Frameless ctor over the pinned Transport base (0x26E5D7): installs the
// explicit vtable 0x00BF23C8 first (DeployStyle precedent: pointer-cast
// write, no virtuals declared on the derived class so no vtable is emitted
// here; the address is unique image-wide with this ctor its sole installer),
// then zeroes voice/maxBoxes, the three float zeros, the two action-delay
// ints, the harvest-trees bool, stores scan distance 100.0, sets the two
// harvest times to 1 and stores activation range 50.0. Field identity is
// the rowed base-call buildFieldParse proc at 0x0024F299 (Transport base
// proc plus table 0x00BEF620 holding MaxBoxes at +0x64 through
// SuppliesDepletedVoice at +0x90). Sole raw caller is the rowed ModuleData
// factory 0x002544F1 which news 0x94; this row supersedes the ctor pin.

class TransportAIUpdateModuleData
{
public:
	TransportAIUpdateModuleData();
	virtual ~TransportAIUpdateModuleData();

private:
	unsigned char m_pad[0x64 - 4];
};

class WorkerAIUpdateModuleData : public TransportAIUpdateModuleData
{
public:
	WorkerAIUpdateModuleData();

private:
	int m_maxBoxes;					// +0x64
	float m_repairHealthPercentPerSecond;	// +0x68
	float m_boredTime;				// +0x6C
	float m_boredRange;				// +0x70
	int m_supplyCenterActionDelay;	// +0x74
	int m_supplyWarehouseActionDelay;	// +0x78
	float m_supplyWarehouseScanDistance;	// +0x7C
	bool m_harvestTrees;			// +0x80
	float m_harvestActivationRange;	// +0x84
	int m_harvestPreparationTime;	// +0x88
	int m_harvestActionTime;		// +0x8C
	int m_suppliesDepletedVoice;	// +0x90
};

// ??0WorkerAIUpdateModuleData@@QAE@XZ @0x00254434
WorkerAIUpdateModuleData::WorkerAIUpdateModuleData()
{
	int *voice = &m_suppliesDepletedVoice;
	int *maxBoxes = &m_maxBoxes;
	*(unsigned int *)this = 0x00BF23C8;
	*voice = 0;
	*maxBoxes = 0;
	m_repairHealthPercentPerSecond = 0.0f;
	m_boredTime = 0.0f;
	m_boredRange = 0.0f;
	m_supplyCenterActionDelay = 0;
	m_supplyWarehouseActionDelay = 0;
	m_harvestTrees = false;
	m_supplyWarehouseScanDistance = 100.0f;
	m_harvestPreparationTime = 1;
	m_harvestActionTime = 1;
	m_harvestActivationRange = 50.0f;
}
