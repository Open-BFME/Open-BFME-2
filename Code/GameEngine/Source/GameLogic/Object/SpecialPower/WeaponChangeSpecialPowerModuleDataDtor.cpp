// cl: /Ireference/shims/bfme2_ascii /MD /EHsc /DNDEBUG
//
// ??1WeaponChangeSpecialPowerModuleData@@UAE@XZ, retail 0x004C42EE, 74 bytes.
// Target evidence: the audited scalar deleting dtor 0x004C42D2 (vtable
// 0x00C5D1F0 slot 0) calls this body. It destroys the strings at +0x98 and
// +0x94 (0x00036410), then calls the rowed base dtor 0x0049334F
// (SpecialPowerModuleData, 0x94 bytes). No derived vptr store (novtable).

#include "ascii_string.h"

class SpecialPowerModuleData
{
public:
	virtual ~SpecialPowerModuleData();

private:
	unsigned char m_tail[0x94 - 4];
};

class __declspec(novtable) WeaponChangeSpecialPowerModuleData : public SpecialPowerModuleData
{
public:
	virtual ~WeaponChangeSpecialPowerModuleData();

private:
	AsciiString m_string94;	// +0x94
	AsciiString m_string98;	// +0x98
};

WeaponChangeSpecialPowerModuleData::~WeaponChangeSpecialPowerModuleData()
{
}
