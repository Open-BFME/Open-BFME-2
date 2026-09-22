// cl: /O1 /arch:SSE /GX /MD /DNDEBUG
// stlport
//
// ??0ReplenishUnitsBehaviorModuleData@@QAE@XZ, retail 0x004841CC, 91 bytes.
// Frameless ctor: explicit vtable 0x00C4ED70, shared member-construct at +0x08
// (rowed 0x25342C, 0x110-byte Rva0025342CMember), exempt-status-style bitset
// at +0x124 reset through the ledger-known bitset<128>::reset body (rowed at
// 0x24CA24, GrantUpgrade precedent), 100.0f at +0x118 from the float pool,
// zeros at +0x11C/+0x120, the dword global 0x00DBA4E4 (value 5) at +0x134 via
// address-derived extern (ColdGlobalDwordGetters g_Va precedent; DIR32-masked)
// and false bytes at +0x138/+0x139. No other globals, two callees. Factory
// news 0x13C.

#include <bitset>

namespace _STL {
template<> bitset<128> &bitset<128>::reset();
}

extern int g_Va00DBA4E4;

class Rva0025342CMember
{
public:
	Rva0025342CMember *construct();

private:
	unsigned char m_body[0x110];
};

class __declspec(novtable) ReplenishUnitsBehaviorModuleData
{
public:
	ReplenishUnitsBehaviorModuleData();

private:
	void *m_vtable;			// +0x00
	unsigned int m_04;		// +0x04 (retail never stores)
	Rva0025342CMember m_08;		// +0x08
	float m_118;			// +0x118
	float m_11C;			// +0x11C
	int m_120;			// +0x120
	unsigned long m_124[4];		// +0x124 bitset<128>
	int m_134;			// +0x134
	bool m_138;			// +0x138
	bool m_139;			// +0x139
};

// ??0ReplenishUnitsBehaviorModuleData@@QAE@XZ @0x4841CC
ReplenishUnitsBehaviorModuleData::ReplenishUnitsBehaviorModuleData()
{
	*(void **)this = reinterpret_cast<void *>(0x00C4ED70);
	m_08.construct();
	((_STL::bitset<128> *)m_124)->reset();
	m_138 = false;
	m_134 = g_Va00DBA4E4;
	m_118 = 100.0f;
	m_120 = 0;
	m_139 = false;
	m_11C = 0.0f;
}
