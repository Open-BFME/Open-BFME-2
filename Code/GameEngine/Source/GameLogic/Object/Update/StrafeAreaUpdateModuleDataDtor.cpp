// cl: /Ireference/shims/bfme2_ascii /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS
// ??1StrafeAreaUpdateModuleData@@UAE@XZ @ 0x003A4ECF 54B
// Explicit dtor reinstalling derived vtable 0x00C1B268 then tearing down
// WeaponName at +0x08 via 0x00036410 then restoring Snapshot base vtable
// 0x00BBB554 with no base call. Layout from ctor TU 0x003A4E5A (pad +4
// string +0x08). Vtable 0x0081B268 slot 0 is ??_G 0x003A4F05.
// LargeGroupBonusUpdateModuleDataDtor precedent.
extern "C" const void *const vtbl_00BBB554[];  // folded, 23 classes; via ??_7BfmeBaseVUQ@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BBB554=??_7BfmeBaseVUQ@@6B@")

#include "ascii_string.h"
class Snapshot
{
public:
	virtual ~Snapshot();
	virtual void crc();
	virtual void loadPostProcess();
	virtual void xfer();
};
inline Snapshot::~Snapshot()
{
	*(const void **)this = reinterpret_cast<const void *>(((unsigned int)vtbl_00BBB554));
}
class __declspec(novtable) StrafeAreaUpdateModuleDataBase : public Snapshot
{
public:
	StrafeAreaUpdateModuleDataBase() {}
};
class StrafeAreaUpdateModuleData : public StrafeAreaUpdateModuleDataBase
{
public:
	virtual ~StrafeAreaUpdateModuleData();
private:
	int m_unused04;
	AsciiString m_weaponName;
};
StrafeAreaUpdateModuleData::~StrafeAreaUpdateModuleData()
{
}
