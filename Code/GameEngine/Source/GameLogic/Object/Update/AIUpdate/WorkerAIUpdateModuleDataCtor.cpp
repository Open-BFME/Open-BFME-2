// cl: /O1 /MD /GX /DNDEBUG /arch:SSE
//
// ??0WorkerAIUpdateModuleData@@QAE@XZ, retail 0x0024EE77 (65 bytes).
// Frameless ctor over the pinned Transport base (0x26E5D7): zeroes
// m_maxBoxesData at +0x64 plus m_centerDelay at +0x68 plus m_warehouseDelay
// at +0x6C, clears m_harvestTrees at +0x74, stores m_warehouseScanDistance
// 100.0 at +0x70, sets m_harvestPreparationTime at +0x7C and
// m_harvestActionTime at +0x80 to 1, sinks the folded vtable 0x00C4B6C8
// below those stores through the ??_7 pin (Wander precedent: virtual
// classes with declared-only virtual dtors and no source store), then
// stores m_harvestActivationRange 50.0 at +0x78. Field identity is the
// base-call buildFieldParse table 0x00BEF4B0 (all eight fields match BFME1's
// WorkerAIUpdateModuleData table verbatim at identical offsets). Sole raw
// caller is the ModuleData factory 0x24EF11 which news 0x84.

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
	virtual ~WorkerAIUpdateModuleData();

private:
	int m_maxBoxesData;			// +0x64
	int m_centerDelay;			// +0x68
	int m_warehouseDelay;		// +0x6C
	float m_warehouseScanDistance;	// +0x70
	bool m_harvestTrees;		// +0x74
	float m_harvestActivationRange;	// +0x78
	int m_harvestPreparationTime;	// +0x7C
	int m_harvestActionTime;	// +0x80
};

WorkerAIUpdateModuleData::WorkerAIUpdateModuleData()
{
	m_maxBoxesData = 0;
	m_centerDelay = 0;
	m_warehouseDelay = 0;
	m_harvestTrees = false;
	m_warehouseScanDistance = 100.0f;
	m_harvestPreparationTime = 1;
	m_harvestActionTime = 1;
	m_harvestActivationRange = 50.0f;
}
