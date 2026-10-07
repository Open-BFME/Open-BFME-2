// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /GX /MD /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/moduledata
// stlport
// ??1CivilianSpawnUpdateModuleData@@UAE@XZ @ 0x0047FABF 63B
// Two-member dtor restoring Snapshot base vtable 0x00BBB554: vector at +0x14
// via rowed AsciiString vector dtor 0x0002CC70 (state 1) then filter at +0x0C
// via pinned 0x00360D26 (state 0). Layout from ctor TU 0x0047FA55 (base 0x0C
// filter +0x0C int +0x10 vector +0x14). Vtable 0x00848530 slot 0 is ??_G
// 0x0047FAA3. LargeGroupBonusUpdateModuleDataDtor precedent with novtable
// suppressing derived store and the shared Snapshot base dtor restoring BBB554.
#include <vector>
#include "Common/Snapshot.h"
#include "ascii_string.h"
class Rva003623E5Filter
{
public:
	~Rva003623E5Filter();
private:
	unsigned char m_data[4];
};
class __declspec(novtable) CivilianSpawnUpdateModuleData : public Snapshot
{
public:
	virtual ~CivilianSpawnUpdateModuleData();
private:
	int m_unsourced04;
	int m_int08;
	Rva003623E5Filter m_filter0C;
	int m_int10;
	_STL::vector<AsciiString> m_vec14;
};
CivilianSpawnUpdateModuleData::~CivilianSpawnUpdateModuleData()
{
}
