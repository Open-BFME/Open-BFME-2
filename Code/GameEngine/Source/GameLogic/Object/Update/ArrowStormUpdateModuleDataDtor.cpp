// cl: /Ireference/shims/bfme2_ascii /MD /EHsc /DNDEBUG
//
// ??1ArrowStormUpdateModuleData@@UAE@XZ, retail 0x00490695, 56 bytes.
// Target evidence: the audited scalar deleting dtor 0x00490679 (vtable
// 0x00C4D5A0 slot 0) calls this body. It destroys the string at +0xC8
// (0x00036410), then calls the opaque module-data base dtor 0x0044ECCE
// (Rva0044ECCE, 0xC8 prefix). No derived vptr store (novtable).

#include "ascii_string.h"

class Rva0044ECCE
{
public:
	virtual ~Rva0044ECCE();

private:
	unsigned char m_tail[0xC8 - 4];
};

class __declspec(novtable) ArrowStormUpdateModuleData : public Rva0044ECCE
{
public:
	virtual ~ArrowStormUpdateModuleData();

private:
	AsciiString m_stringC8;	// +0xC8
};

ArrowStormUpdateModuleData::~ArrowStormUpdateModuleData()
{
}
