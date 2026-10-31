// cl: /MD /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /I.
// stlport
// Retail 0x0047DFFF, 16 bytes, RET.
// Shape: this is kept in esi across one member call (0x00464120, address-derived
// name: its only evidence is the __thiscall with ecx = this), then the last
// statement tail-jumps into TunnelContain::rva0047DF81 (0x0047DF81, matched in
// TunnelContainRva0047DF81.cpp). The owner is inferred from the tail callee and
// the file neighbours; the class name is not otherwise established.
#include "TunnelContainView.h"
class OpenContain
{
public:
 virtual void onDelete();
};
// Slot 8 of TunnelContain's vftable 0x00C47740: virtual.
void TunnelContain::onDelete()
{
 ((OpenContain *)this)->OpenContain::onDelete();
 rva0047DF81();
}
