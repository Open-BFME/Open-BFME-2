// cl: /O1 /DNDEBUG /MD /GX- /arch:SSE
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

private:
	int m_int64;	// +0x64
	int m_int68;	// +0x68
	float m_float6C;	// +0x6C
	float m_float70;	// +0x70
	float m_float74;	// +0x74
	float m_float78;	// +0x78
	float m_float7C;	// +0x7C
	int m_int80;	// +0x80
};

GiantBirdAIUpdateModuleData::GiantBirdAIUpdateModuleData()
{
	*(unsigned int *)this = 0x00C4B6C8;
	m_int64 = 0;
	m_int68 = 0;
	m_float6C = 0.0f;
	m_float70 = 0.0f;
	m_float74 = 100.0f;
	m_float78 = 10.0f;
	m_float7C = 1.0f;
	m_int80 = 0;
}
