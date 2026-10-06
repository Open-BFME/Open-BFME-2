// cl: /Ireference/shims/bfme2_ascii /GX /MD /DNDEBUG /Ireference/shims/moduledata
//
// ??1W3DPropDrawModuleData@@UAE@XZ, retail 0x000CEF3C, 54 bytes.
// W3DPropDraw ModuleData dtor: reinstalls the vtable 0x00BCD420, tears
// down the m_modelName string at +0x08 through the folded AsciiString
// dtor at 0x36410 (pin ??1AsciiString@@QAE@XZ), then restores the
// Snapshot base vtable 0x00BBB554 through the shared base dtor.
// Single EH state for the one string member. Layout follows the adjacent
// ctor pin at 0xCEF2B (vptr +0, string +0x08) and the ZH W3DPropDraw.h
// donor (ModuleData base plus AsciiString m_modelName). Shape follows
// the landed W3DLightDrawModuleDataDtor TU.
#include "Common/Snapshot.h"

#include "ascii_string.h"

class W3DPropDrawModuleData : public Snapshot
{
public:
	virtual ~W3DPropDrawModuleData();

private:
	unsigned char m_pad04[0x08 - 4];
	AsciiString m_modelName;
};

W3DPropDrawModuleData::~W3DPropDrawModuleData()
{
}
