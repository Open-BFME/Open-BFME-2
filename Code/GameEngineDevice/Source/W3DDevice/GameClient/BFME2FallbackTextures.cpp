// cl: /O1 /DNDEBUG /MD /EHsc
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
class SurfaceClass { public: void DrawPixel(unsigned,unsigned,unsigned); private: void *surface; };
class W3DRadarResetSurface {
public:
 W3DRadarResetSurface():surface(0){}
 ~W3DRadarResetSurface();
 __forceinline void DrawPixel(unsigned x,unsigned y,unsigned color) { ((SurfaceClass *)this)->DrawPixel(x,y,color); }
 void *surface;
};
struct CursorTextureSlot { void *Ptr; W3DRadarResetSurface Get_Surface_Level(); };
struct IDirect3DBaseTexture8;
class TextureBaseClass { public: IDirect3DBaseTexture8 *Peek_D3D_Base_Texture() const; };
class Rva00131DFC { public: void rva00131DFC(void *,void *,void *,void *,int,int); };
void BFME_DX8_Thread_Lock();
bool BFME_DX8_Thread_Assert();
class BfmeFallbackTextureLock {
public:
 BfmeFallbackTextureLock() { BFME_DX8_Thread_Lock(); }
 ~BfmeFallbackTextureLock() { BFME_DX8_Thread_Assert(); }
};
RefCountPtr<TextureClass> Rva00132E76WhiteTexture() {
 static RefCountPtr<TextureClass> texture;
 if(!texture.Ptr) {
  BfmeFallbackTextureLock lock;
  ((Rva00131DFC *)&texture)->rva00131DFC((void *)1,(void *)1,(void *)21,(void *)1,1,0);
  if(((TextureBaseClass *)&texture)->Peek_D3D_Base_Texture()) {
   ((CursorTextureSlot *)&texture)->Get_Surface_Level().DrawPixel(0,0,0xFFFFFFFF);
  }
 }
 return RefCountPtr<TextureClass>(texture, RefCountPtr<TextureClass>::COPY_INLINE);
}
RefCountPtr<TextureClass> Rva00132F30BlackTexture() {
 static RefCountPtr<TextureClass> texture;
 if(!texture.Ptr) {
  BfmeFallbackTextureLock lock;
  ((Rva00131DFC *)&texture)->rva00131DFC((void *)1,(void *)1,(void *)21,(void *)1,1,0);
  if(((TextureBaseClass *)&texture)->Peek_D3D_Base_Texture()) {
   ((CursorTextureSlot *)&texture)->Get_Surface_Level().DrawPixel(0,0,0);
  }
 }
 return RefCountPtr<TextureClass>(texture, RefCountPtr<TextureClass>::COPY_INLINE);
}


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
class BfmeDeferredTexture {
public:
 virtual long __stdcall QueryInterface(void *,void **);
 virtual unsigned long __stdcall AddRef();
 virtual unsigned long __stdcall Release();
};
class Rva009EB960;
extern Rva009EB960 *Rva0134FAA0;
extern unsigned g_Va00DF2984;
extern unsigned g_Va00DF29A8;
class Rva0020FB8BVec20 { public: void vecPushBack(void *&); };
class Rva0013331A {
 unsigned char prefix[8]; BfmeDeferredTexture *texture;
public: void rva0013331A();
};
void Rva0013331A::rva0013331A() {
 if(!texture)return;
 if(Rva0134FAA0) {
  ScopedCriticalSection guard(reinterpret_cast<CriticalSection *>(&g_Va00DF2984));
  reinterpret_cast<Rva0020FB8BVec20 *>(&g_Va00DF29A8)->vecPushBack(reinterpret_cast<void *&>(texture));
 } else {
  texture->Release();
 }
 texture=0;
}
