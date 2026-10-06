// cl: /Ireference/shims/bfme2_ascii /MD /Ireference/shims/moduledata
// ??1SlavedUpdateModuleData@@UAE@XZ @0x00255FC1, 63B.
// Virtual dtor slot evidence: ??_G at 0x00255FA5 (rowed, slot 0 of vtable 0x00BF34C0) calls here. Destroys AsciiStrings at +0x50 then +0x4C via pinned 0x00036410 then restores base vtable 0x00BBB554 with trivial base inlined (no base call). Layout from rowed ctor 0x002552D7 (WeldingSys +0x4C WeldingFXBone +0x50 inline-ctor AsciiStrings, factory news 0x70 at 0x00255340). Donor BFME1 SlavedUpdateModuleDataDestructorThunk.
#include "Common/Snapshot.h"

#include "ascii_string.h"

class __declspec(novtable) SlavedUpdateModuleData : public Snapshot
{
public:
	virtual ~SlavedUpdateModuleData();

private:
	unsigned char m_pad[0x4C - 4];
	AsciiString m_weldingSysName; // +0x4C
	AsciiString m_weldingFXBone; // +0x50
	unsigned char m_rest[0x70 - 0x54];
};

SlavedUpdateModuleData::~SlavedUpdateModuleData()
{
}
