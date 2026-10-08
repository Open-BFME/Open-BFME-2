// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS /Ireference/shims/moduledata
// ??1RadarMarkerClientUpdateModuleData@@UAE@XZ, retail 0x004C9CA5, 54 bytes.
// Explicit dtor reinstalling derived vtable 0x00C5EDF8 then tearing down
// MarkerType at +0x08 via 0x00036410 then restoring Snapshot base vtable
// 0x00BBB554 with no base call. Layout from ctor TU 0x004C9C98 (tag +4,
// string +0x08, factory news 0x0C) and INI table 0x00C5ED98 (parseAsciiString
// at +0x08). Vtable 0x00C5EDF8 slot 0 is ??_G 0x004C9D77.
// StrafeAreaUpdateModuleDataDtor precedent.

#include "ascii_string.h"
#include "Common/Snapshot.h"
class __declspec(novtable) RadarMarkerClientUpdateModuleDataBase : public Snapshot
{
public:
	RadarMarkerClientUpdateModuleDataBase() {}
};
class RadarMarkerClientUpdateModuleData : public RadarMarkerClientUpdateModuleDataBase
{
public:
	virtual ~RadarMarkerClientUpdateModuleData();
private:
	int m_unused04;
	AsciiString m_markerType;
};
RadarMarkerClientUpdateModuleData::~RadarMarkerClientUpdateModuleData()
{
}
