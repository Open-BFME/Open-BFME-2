// cl: /Ireference/shims/bfme2_ascii /MD
// ??1SalvageCrateCollideModuleData@@UAE@XZ @0x002563EF, 53B.
// Virtual dtor slot evidence: ??_G at 0x002563D3 (rowed, slot 0 of vtable 0x00BF3A40) calls here. Destroys AsciiString at +0x78 via pinned 0x00036410 then base CrateCollideModuleData via ICF twin of rowed ??1UpgradeModuleData at 0x00255A42 (both destroy string at +0x4C then restore Snapshot base 0x00BBB554). Layout from rowed ctor 0x00255B7E (base 0x5C, floats at +0x5C/+0x60/+0x64/+0x68/+0x6C, ints at +0x70/+0x74, string slot at +0x78 zeroed via AND, flag at +0x7C, factory news 0x80 at 0x00255BD2) plus own INI table 0x00BEFC28. Donor ZH SalvageCrateCollide.h (3 floats + 2 ints, BFME2 appends float/int tail plus string at +0x78). Shape follows DeployStyleAIUpdateModuleDataDtor (single string plus EH base, novtable suppresses derived store).
#include "ascii_string.h"

class __declspec(novtable) CrateCollideModuleData
{
public:
	CrateCollideModuleData();
	virtual ~CrateCollideModuleData();

private:
	unsigned char m_pad[0x5C - 4];
};

class __declspec(novtable) SalvageCrateCollideModuleData : public CrateCollideModuleData
{
public:
	virtual ~SalvageCrateCollideModuleData();

private:
	unsigned char m_gap[0x78 - 0x5C];
	AsciiString m_str78; // +0x78
	bool m_flag7C; // +0x7C
	unsigned char m_pad7D[0x80 - 0x7D];
};

SalvageCrateCollideModuleData::~SalvageCrateCollideModuleData()
{
}
