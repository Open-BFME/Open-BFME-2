// cl: /O1 /arch:SSE /GX /MD /DNDEBUG
//
// ??0ObjectCreationUpgradeModuleData@@QAE@XZ, retail 0x004B425B, 128 bytes.
// Frameless zero-init ctor: explicit vtable 0x00C577C8, two zero ints at
// +0x08/+0x0C, shared member-construct at +0x10 (rowed 0x25342C, 0x110-byte
// Rva0025342CMember), then zero ints/floats through +0x138, false at +0x13C,
// -1/0/0 at +0x140 (tail-pointer plus direct duplicate, OpenContain
// precedent: mixed paths are not folded), zeros at +0x144/+0x148/+0x14C and
// false at +0x150. No globals, one callee. Factory news 0x154.

class Rva0025342CMember
{
public:
	Rva0025342CMember *construct();

private:
	unsigned char m_body[0x110];
};

class __declspec(novtable) ObjectCreationUpgradeModuleData
{
public:
	ObjectCreationUpgradeModuleData();

private:
	void *m_vtable;			// +0x00
	unsigned int m_04;		// +0x04 (retail never stores)
	int m_08;			// +0x08
	int m_0C;			// +0x0C
	Rva0025342CMember m_10;		// +0x10
	int m_120;			// +0x120
	int m_124;			// +0x124
	int m_128;			// +0x128
	float m_12C;			// +0x12C
	float m_130;			// +0x130
	float m_134;			// +0x134
	float m_138;			// +0x138
	bool m_13C;			// +0x13C
	unsigned char m_pad13D[3];
	int m_140;			// +0x140
	int m_144;			// +0x144
	int m_148;			// +0x148
	int m_14C;			// +0x14C
	bool m_150;			// +0x150
};

// ??0ObjectCreationUpgradeModuleData@@QAE@XZ @0x4B425B
ObjectCreationUpgradeModuleData::ObjectCreationUpgradeModuleData()
{
	*(void **)this = reinterpret_cast<void *>(0x00C577C8);
	m_08 = 0;
	m_0C = 0;
	m_10.construct();
	m_120 = 0;
	m_124 = 0;
	m_128 = 0;
	float *fp = &m_12C;
	fp[0] = 0.0f;
	fp[1] = 0.0f;
	fp[2] = 0.0f;
	m_138 = 0.0f;
	m_13C = false;
	int *tail = &m_140;
	tail[0] = -1;
	tail[1] = 0;
	tail[2] = 0;
	m_140 = -1;
	m_14C = 0;
	m_150 = false;
	m_144 = 0;
	m_148 = 0;
}
