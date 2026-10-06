// cl: /Ireference/shims/bfme2_ascii /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/moduledata
// stlport
//
// ??1CostModifierUpgradeModuleData@@UAE@XZ, retail 0x004B5C80, 105 bytes.
// Target evidence: the audited scalar deleting dtor 0x004B5C64 calls this
// body (registration CostModifierUpgrade -> factory 0x00250316 -> ctor
// 0x004B5BAC). Teardown: AsciiString vector at +0x130 (0x0002CC70), string
// at +0x12C (0x00036410), inline null-checked free of the POD vector buffer
// at +0x11C (0x00030830), filter member at +0x118 (0x00360D26), then the
// Snapshot base stores 0x00BBB554. No derived vptr store (novtable).
// Element type of the +0x11C vector is unrecovered (trivial, 4 bytes here).
#include <vector>
#include "Common/Snapshot.h"

#include "ascii_string.h"

class Rva003623E5Member
{
public:
	~Rva003623E5Member();

private:
	int m_x;
};

class RvaVecAscii
{
public:
	~RvaVecAscii();

private:
	int m_x[3];
};

class __declspec(novtable) CostModifierUpgradeModuleData : public Snapshot
{
public:
	virtual ~CostModifierUpgradeModuleData();

private:
	unsigned char m_pad04[0x118 - 4];
	Rva003623E5Member m_filter118;		// +0x118
	_STL::vector<int> m_vector11C;		// +0x11C
	int m_128;
	AsciiString m_string12C;		// +0x12C
	RvaVecAscii m_vector130;		// +0x130
};

CostModifierUpgradeModuleData::~CostModifierUpgradeModuleData()
{
}
