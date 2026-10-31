// cl: /MD /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /I.
// stlport
// Retail 0x0047DF81, 88 bytes, RET. Object +8 and pending +9E5 are
// fixed by native loads. The controlling Player supplies a TunnelTracker
// at +2E8; the containment interface at +20 dispatches slots 42 and 68.
// TunnelContain identity follows the rowed ctor/dtor, xfer state +9E5,
// approved TU map and adjacent containment overrides; method name unresolved.
// ZH TunnelContain/TunnelTracker sources corroborate unregister/iteration flow.
// Callback 0x0047DE6C
// has a complete 117-byte cdecl boundary and reads two Object pointers.
#include "TunnelContainView.h"
// LINK: 0x4F571B is rowed as Rva004F56FC::rva004F571B (const Object *) and 0x47DE6C as the
// callback Rva0047DE6CVisit(Object *, void *); both are bound under those names.
void __cdecl Rva0047DE6CVisit(Object *object, void *userData);
void TunnelContain::rva0047DF81()
{
 if (pending)
 {
  Player *player = m_object->getControllingPlayer();
  if (player == 0)
   return;
  TunnelTracker *tracker = player->m_tunnelSystem;
  if (tracker != 0)
  {
   if (((Rva004F56FC *)tracker)->rva004F571B(m_object))
    dispatch42(false);
   else
    dispatch68((void (__cdecl *)(Object *, Object *))Rva0047DE6CVisit, m_object, true);
  }
  pending = false;
 }
}
