// cl: /O1 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_CRTIMP=
// stlport
// Split from BFME2FallbackTextures.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
#define _STLP_BFME_COPY_TRIVIAL_EXTERN  // call retail's one __copy_trivial (vendor/stlport/stl/_algobase.h)
#include <vector>
#include "BFME2ParticleTextureHandles.h"

// Native fallback getters 0x00132E76..0x00132F30 and 0x00132F30..0x00132FE9.
// Target evidence: the matched particle and terrain callbacks use these handles
// as absent-texture fallbacks. Each constructs a lazy one-pixel format-21 texture
// via the already recovered 0x00131DFC setter, takes the DX8 mutex around creation,
// paints white or black through the surface holder, and returns a counted copy.
// No donor name is claimed: the existing getter names are address-derived.
// Local static ownership and initialization guards are inferred independently
// from the native atexit call, guard bit, and pointer globals at DF2974/DF297C.
// SurfaceClass and W3DRadarResetSurface are both the established one-pointer COM
// holder view; DrawPixel takes the holder address rather than its COM pointer.
#include "../../../../Libraries/Source/WWVegas/WW3D2/W3DSurfaceClass.h"
#include "../../../../GameEngine/Include/Common/W3DRadarResetSurface.h"
struct IDirect3DBaseTexture8;
void BFME_DX8_Thread_Lock();
bool BFME_DX8_Thread_Assert();
class BfmeFallbackTextureLock {
public:
 BfmeFallbackTextureLock() { BFME_DX8_Thread_Lock(); }
 ~BfmeFallbackTextureLock() { BFME_DX8_Thread_Assert(); }
};
RefCountPtr<TextureClass> Rva00132E76WhiteTexture();

RefCountPtr<TextureClass> Rva00132F30BlackTexture();



// ?rva0013331A@Rva0013331A@@QAEXXZ
// Native 0x0013331A..0x00133380 (102 bytes). WorldBuilder gives the
// TextureAsset::Impl::Unload lead; retain the existing neutral owner name.
// The resource at +8 is queued under DF2984 when the deferred-release owner
// exists, otherwise released through IUnknown slot 2, then cleared. The
// inline scoped guard uses the already matched Lock/Unlock providers.
class CriticalSection;
class ScopedCriticalSection {
 CriticalSection *m_cs; bool m_locked;
 void Lock(); void Unlock() throw();
public:
 __forceinline ScopedCriticalSection(CriticalSection *cs):m_cs(cs),m_locked(false){Lock();}
 __forceinline ~ScopedCriticalSection(){if(m_locked)Unlock();}
};
#include "../../../Include/W3DDevice/GameClient/BfmeDeferredTexture.h"
class Rva009EB960;
extern Rva009EB960 *Rva0134FAA0;
extern unsigned int g_Va00DF2984[9];
extern unsigned g_Va00DF29A8;
static __forceinline CriticalSection *deferredDeviceMutex() {
 return reinterpret_cast<CriticalSection *>(&g_Va00DF2984);
}
static __forceinline _STL::vector<void *> &deferredDeviceQueue() {
 return *reinterpret_cast<_STL::vector<void *> *>(&g_Va00DF29A8);
}
class Rva0013331A {
 unsigned char prefix[8]; BfmeDeferredTexture *texture;
public: void rva0013331A();
};


// Native 0x00133283..0x0013331A (151 bytes); the corrected whole boundary
// includes both guard lifetimes and the final EH epilogue. Callers include
// the matched shadow-map update and game-start paths. The adjacent unload
// body above enqueues pointers into this same three-pointer range at DF29A8
// under the same critical section at DF2984. These are views of the existing
// globals, with no additional data owner or donor class identity claimed.
void bfmeReleaseQueuedDeviceInterfaces() {
 _STL::vector<void *> &queue=deferredDeviceQueue();
 if(queue.empty())return;
 BfmeFallbackTextureLock device;
 ScopedCriticalSection guard(deferredDeviceMutex());
 void **i=queue.begin();
 if(i!=queue.end()) {
  do {
   reinterpret_cast<BfmeDeferredTexture *>(*i)->Release();
   ++i;
  } while(i!=queue.end());
  i=queue.begin();
 }
 queue.erase(i,queue.end());
}
