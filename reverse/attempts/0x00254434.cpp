// ??0WorkerAIUpdateModuleData@@QAE@XZ
// partial score=0.99 date=2026-09-23
// cl: /O1 /MD /DNDEBUG /arch:SSE
//
// ??0WorkerAIUpdateModuleData@@QAE@XZ, retail 0x00254434 (101 bytes).
// Frameless derived ctor over the pinned TransportAIUpdateModuleData base
// (0x0026E5D7, size 0x64): int and float zeros share xor-eax/xorps with a
// single inc for the two one-valued int slots, the derived installs vtable
// 0x00BF23C8 explicitly (Defector law; the classes carry no virtuals so the
// compiler emits no store of its own), then the int/float tail stores
// (100.0/1.0/50.0 literals, DIR32-masked like the retail globals). No EH
// (the lone base call precedes any construction). Shard TU: the
// WorkerAIUpdateModuleDataCtor.cpp path carries the twin-owned
// SupplyTruckAIUpdateModuleData file-unit. Identity is the ModuleFactory
// registration under "WorkerAIUpdate" (sole-caller data factory per the
// superseded ctor pin).

class TransportAIUpdateModuleData
{
public:
	TransportAIUpdateModuleData();

private:
	// No virtuals are declared (Defector law), so the pad spans the full
	// 0x64 base ahead of the derived tail.
	unsigned char m_opaque[0x64];
};

class WorkerAIUpdateModuleData : public TransportAIUpdateModuleData
{
public:
	WorkerAIUpdateModuleData();

private:
	int m_int64;	// +0x64
	float m_float68;	// +0x68
	float m_float6C;	// +0x6C
	float m_float70;	// +0x70
	int m_int74;	// +0x74
	int m_int78;	// +0x78
	float m_float7C;	// +0x7C
	bool m_flag80;	// +0x80
	float m_float84;	// +0x84
	int m_int88;	// +0x88
	int m_int8C;	// +0x8C
	int m_int90;	// +0x90
};

WorkerAIUpdateModuleData::WorkerAIUpdateModuleData()
	: TransportAIUpdateModuleData()
{
	*(unsigned int *)this = 0x00BF23C8;
	m_int90 = 0;
	m_int64 = 0;
	m_float68 = 0.0f;
	m_float6C = 0.0f;
	m_float70 = 0.0f;
	m_int74 = 0;
	m_int78 = 0;
	m_flag80 = false;
	m_float7C = 100.0f;
	m_float84 = 50.0f;
	m_int88 = 1;
	m_int8C = 1;
}
