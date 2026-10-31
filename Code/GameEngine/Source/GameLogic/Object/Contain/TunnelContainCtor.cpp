// cl: /MD /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /I.
// stlport
//
// ??0TunnelContain@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x0047DBF7, 98 bytes.
// TunnelContain behavior ctor over the pinned HordeGarrisonContain
// intermediate base (0x47A040, thing plus data): forwards both args to the
// base, then re-stores the primary vtable slot and eight secondary slots at
// +0x0C/+0x10/+0x20/+0x24/+0x28/+0x2C/+0x30/+0x34, then stores the bytes at
// +0x9E4/+0x9E5. The rowed name getter at 0x47DB88 and ModuleData factory
// 0x257A0A prove the class;
// the rowed instance factory 0x24BCED (news 0x9E8) is the sole raw caller.
// Row supersedes the ctor pin.

#include "TunnelContainView.h"

// ??0TunnelContain@@QAE@PAVThing@@PBVModuleData@@@Z @0x47DBF7
TunnelContain::TunnelContain(Thing *thing, const ModuleData *moduleData)
	: HordeGarrisonContain(thing, moduleData)
{
	m_flag9B0 = 1;
	pending = 0;
}
