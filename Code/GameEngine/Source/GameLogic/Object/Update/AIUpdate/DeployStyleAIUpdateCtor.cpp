// cl: /O1 /arch:SSE /DNDEBUG /MD
//
// ??0DeployStyleAIUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, retail
// 0x0048E983 (112 bytes). Behavior ctor over the pinned opaque Transport
// base (0x26E9BD, thing plus data): installs the five behavior vtable slots
// (+0x00/+0x0C/+0x10/+0x20/+0x24 via explicit members with TU-local dummy
// statics, DIR32-masked) over a 0x3E4 member (ctor 0x26AFDA, size 0xC4
// ending at 0x4A8) plus zeros at +0x4A8..0x4B8 in retail order
// (0x4B4 before 0x4B0), then runs the pinned class helper (0x48E65B).
// The class declares no virtuals of its own: the stores land from explicit
// members in body order (AssaultTransport precedent). Row supersedes the
// sole-caller pin; the instance factory at 0x24D1E6 is the single raw caller.

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
	void reset();

protected:
	Rva0026AFDAMember m_member3E4;		// +0x3E4 (init 0x26AFDA via TU method pin)
	bool m_flag4A8;				// +0x4A8
	bool m_flag4A9;				// +0x4A9
	unsigned char m_pad4AA[0x4AC - 0x4AA];
	int m_4AC;				// +0x4AC
	int m_4B0;				// +0x4B0
	int m_4B4;				// +0x4B4
	int m_4B8;				// +0x4B8
	int m_4BC;				// +0x4BC
	int m_4C0;				// +0x4C0
	float m_4C4;			// +0x4C4
	float m_4C8;			// +0x4C8
	float m_4CC;			// +0x4CC
	unsigned char m_4D0;		// +0x4D0
	unsigned char m_4D1;		// +0x4D1
	unsigned char m_4D2;		// +0x4D2
	unsigned char m_4D3;		// +0x4D3
	unsigned char m_4D4;		// +0x4D4
	unsigned char m_4D5;		// +0x4D5
	unsigned char m_4D6;		// +0x4D6
};

// ??0DeployStyleAIUpdate@@QAE@PAVThing@@PBVModuleData@@@Z @0x48E983
DeployStyleAIUpdate::DeployStyleAIUpdate(Thing *thing, const ModuleData *moduleData)
	: Rva0026E9BDBase(thing, moduleData)
{
	m_vtable = &s_vtable;
	m_p0C = &s_secondary0C;
	m_p10 = &s_secondary10;
	m_p20 = &s_secondary20;
	m_p24 = &s_secondary24;
	m_member3E4.initMember();
	int zero = 0;
	m_flag4A8 = false;
	m_flag4A9 = false;
	m_4AC = zero;
	m_4B4 = zero;
	m_4B0 = zero;
	m_4B8 = zero;
	reset();
}

// ?reset@DeployStyleAIUpdate@@QAEXXZ @0x48E65B (80 bytes). Clears the
// transient deploy-motion block (+0x4BC..0x4D6): two ints, three floats and
// seven flag bytes. Runs at the end of the ctor, on new AI commands and
// from update. The float triple is zeroed through one address-taken pointer
// (retail lea plus three movss); separate stores would use direct offsets.
void DeployStyleAIUpdate::reset()
{
	m_4BC = 0;
	m_4D0 = 0;
	m_4D4 = 0;
	m_4D3 = 0;
	m_4D1 = 0;
	m_4C0 = 0;
	m_4D2 = 0;
	m_4D5 = 0;
	m_4D6 = 0;
	float *goal = &m_4C4;
	goal[0] = 0.0f;
	goal[1] = 0.0f;
	goal[2] = 0.0f;
}
