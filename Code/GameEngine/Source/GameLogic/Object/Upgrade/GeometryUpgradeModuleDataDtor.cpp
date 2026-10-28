// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /Ireference/shims/moduledata
// stlport
//
// ??1GeometryUpgradeModuleData@@UAE@XZ, retail 0x004B6F81, 114 bytes.
// ModuleData dtor: destroys the three AsciiStrings at +0x138 (state 4) then
// +0x134 (state 3) then +0x130 (state 2) through the folded StringBase<char>
// teardown at 0x00036410 then the two AsciiString vectors at +0x124 (state 1)
// then +0x118 (state 0) through the rowed 0x2CC70 body then restores the
// canonical Snapshot base vtable 0x00BBB554. Empty derived body with no
// out-of-line base call; the inherited 0x118-byte state has no cleanup here.
// Layout from the rowed ctor 0x004B6EE2
// (base 0x118 via OpenContain 0x253487, vectors at +0x118/+0x124, strings at
// +0x130/+0x134/+0x138, size 0x13C via factory 0x00250642) and table 0x858918.
// Caller is the slot-0 ??_G at 0x004B6F65 (vtable 0x008589F0). Shape follows
// RemoveUpgradeUpgradeModuleDataDtor (inline Snapshot teardown, novtable
// derived, empty body, vectors via 0x2CC70). Canonical Snapshot also makes
// the EH cleanup bind the existing 0x0049B47C destructor provider.
#include "GeometryUpgradeView.h"

GeometryUpgradeModuleData::~GeometryUpgradeModuleData()
{
}
