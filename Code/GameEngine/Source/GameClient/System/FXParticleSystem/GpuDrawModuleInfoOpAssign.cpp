// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc

// GpuDrawModuleInfo assignment operator.
//
// Retail 0x003A7EF0 (45B) copies the two frame-count dwords at +4/+8,
// assigns the detail-texture string at +0xc through AsciiString::operator=
// (rowed callee 0x000366F0), then copies the speed-multiplier dword at
// +0x10. Member layout mirrors the landed DoXfer TU
// GpuDrawModuleInfoDoXfer.cpp in this folder.

#include "ascii_string.h"


#include "../../../../Include/GameClient/GpuDrawModuleInfo.h"

namespace FXParticleSystem
{

// ??4GpuDrawModuleInfo@FXParticleSystem@@QAEAAV01@ABV01@@Z @0x3A7EF0
GpuDrawModuleInfo &GpuDrawModuleInfo::operator=(const GpuDrawModuleInfo &that)
{
	m_04 = that.m_04;
	m_08 = that.m_08;
	m_0C = that.m_0C;
	m_10 = that.m_10;
	return *this;
}

}
