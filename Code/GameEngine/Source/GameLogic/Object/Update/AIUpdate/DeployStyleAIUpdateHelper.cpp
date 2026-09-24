// cl: /O1 /DNDEBUG /MD /arch:SSE
//
// ?Rva0048E65BHelper@DeployStyleAIUpdate@@QAEXXZ, retail 0x0048E65B
// (80 bytes). DeployStyle trailing-state zeroing shared by three DeployStyle
// methods (raw callers 0x48E9E8 in DeployStyleAIUpdate's ctor, 0x48EA4A and
// 0x48F1F9): int zero at +0x4BC, byte flags at +0x4D0..0x4D6 in
// retail-scrambled order, int zero at +0x4C0, then three float zeros at
// +0x4C4/0x4C8/0x4CC through a pointer-local base (/arch:SSE movss - direct
// member stores address through ecx and miss the lea). Sharded here because
// the DeployStyle home TU is red at HEAD (its 0x26AFDA initMember call was
// never landed); the row carries the file-unit forward until that TU heals.
// The layout below mirrors DeployStyleAIUpdateCtor.cpp through +0x4D6.

class Thing;
class ModuleData;

static int s_vtable;
static int s_secondary0C;
static int s_secondary10;
static int s_secondary20;
static int s_secondary24;

class Rva0026E9BDBase
{
public:
	Rva0026E9BDBase(Thing *thing, const ModuleData *moduleData);

protected:
	const void *m_vtable;			// +0x00
	unsigned char m_pad04[0x0C - 4];
	const void *m_p0C;			// +0x0C
	const void *m_p10;			// +0x10
	unsigned char m_pad14[0x20 - 0x14];
	const void *m_p20;			// +0x20
	const void *m_p24;			// +0x24
	unsigned char m_pad28[0x3E4 - 0x28];
};

class Rva0026AFDAMember
{
public:
	void initMember();

private:
	unsigned char m_pad[0xC4];
};

class DeployStyleAIUpdate : public Rva0026E9BDBase
{
public:
	DeployStyleAIUpdate(Thing *thing, const ModuleData *moduleData);
	void Rva0048E65BHelper();

protected:
	Rva0026AFDAMember m_member3E4;		// +0x3E4 (init 0x26AFDA, banked 0.9)
	bool m_flag4A8;				// +0x4A8
	bool m_flag4A9;				// +0x4A9
	unsigned char m_pad4AA[0x4AC - 0x4AA];
	int m_4AC;				// +0x4AC
	int m_4B0;				// +0x4B0
	int m_4B4;				// +0x4B4
	int m_4B8;				// +0x4B8
	int m_4BC;				// +0x4BC (helper zero)
	int m_4C0;				// +0x4C0 (helper zero)
	float m_float4C4[3];			// +0x4C4 (helper float zeros)
	bool m_flag4D0;				// +0x4D0
	bool m_flag4D1;				// +0x4D1
	bool m_flag4D2;				// +0x4D2
	bool m_flag4D3;				// +0x4D3
	bool m_flag4D4;				// +0x4D4
	bool m_flag4D5;				// +0x4D5
	bool m_flag4D6;				// +0x4D6
};

// ?Rva0048E65BHelper@DeployStyleAIUpdate@@QAEXXZ @0x48E65B
void DeployStyleAIUpdate::Rva0048E65BHelper()
{
	m_4BC = 0;
	m_flag4D0 = false;
	m_flag4D4 = false;
	m_flag4D3 = false;
	m_flag4D1 = false;
	m_4C0 = 0;
	m_flag4D2 = false;
	m_flag4D5 = false;
	m_flag4D6 = false;
	float *float4C4 = m_float4C4;
	float4C4[0] = 0.0f;
	float4C4[1] = 0.0f;
	float4C4[2] = 0.0f;
}
