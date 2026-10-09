// cl: /O2 /arch:SSE /G7 /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
#include "vector2i.h"
// BFME1 9cbfb551fe20 render2dsentence.cpp Build_Textures semantic source.
// Target 154FD0..1551C0/496B: one-pointer surface and texture owners;
// sentence pending surfaces +1C and current surface+7C, no locked pointer;
// format is read from SurfaceDescription rather than donor fixed A4R4G4B4.
// The native device vslot78 uses four UpdateSurface arguments. Native
// Render2D texture+40/current-batch+44 follows the reference smart-pointer
// assignment; keeping that structure closes the NEG/MOV/SBB ordering.
// EH states and cleanup bodies reproduce native exactly. Font texture
// constructor, filter and surface fetch use existing independently rowed
// ABI views; no new callee name or pin is asserted by their use.
// Existing native entry name retained; original Build_Textures identity is
// supported semantically by its renderer caller and pending-surface fields.
class BfmeFontSurfaceResource {
public:
 virtual void slot00();
 virtual unsigned __stdcall AddRef();
 virtual unsigned __stdcall Release();
};
class W3DRadarResetSurface {
public:
 W3DRadarResetSurface(const W3DRadarResetSurface &o){surface=o.surface;if(surface)surface->AddRef();}
 ~W3DRadarResetSurface();
 BfmeFontSurfaceResource *surface;
};
class SurfaceClass : public W3DRadarResetSurface {
public:
 struct SurfaceDescription { unsigned Format,Width,Height; };
 void Get_Description(SurfaceDescription &);
 void Release() { if(surface){surface->Release();surface=0;} }
};
class TextureBaseClass { public: void Release_Ref(); };
class TextureClass : public TextureBaseClass { };
template<class T> class RefCountPtr {
public:
 RefCountPtr():texture(0) {}
 ~RefCountPtr(){if(texture)texture->Release_Ref();}
 RefCountPtr &operator=(const RefCountPtr &p){
  if(p.texture)++*reinterpret_cast<unsigned short *>(reinterpret_cast<char *>(p.texture)+4);
  if(texture)texture->Release_Ref();texture=p.texture;return *this;
 }
 T *texture;
};
class Rva00131DFC { public: void rva00131DFC(void *,void *,void *,void *,int,int); };
class Rva00154FD0;
namespace _STL { class ios_base { friend class ::Rva00154FD0; protected: void _M_clear_nothrow(int); }; }
// Native shared setter 13ED10 owns the existing ios_base spelling; this
// filter view only uses its measured one-int thiscall ABI, without a pin.
class ShroudFilter : public _STL::ios_base {
public:
 void Set_Mip_Mapping(int n) { _M_clear_nothrow(n); }
 int MinFilter,MagFilter,MipFilter,UAddrMode,VAddrMode;
};
class ShroudTexture { public: ShroudFilter *getFilter(); };
class CursorTextureSlot { public: W3DRadarResetSurface Get_Surface_Level(); };
class FontTextureOwner : public RefCountPtr<TextureClass> {
public:
 FontTextureOwner() {}
 // ?FontTextureOwnerLifetime present-unmatched
 ~FontTextureOwner() {}
 void Create(unsigned w,unsigned h,unsigned fmt,unsigned mips,int a,int b) {
  reinterpret_cast<Rva00131DFC *>(this)->rva00131DFC((void*)w,(void*)h,(void*)fmt,(void*)mips,a,b);
 }
 ShroudFilter *Get_Filter() { return reinterpret_cast<ShroudTexture *>(this)->getFilter(); }
 W3DRadarResetSurface Get_Surface_Level(){ return reinterpret_cast<CursorTextureSlot *>(this)->Get_Surface_Level(); }
 void Release() { if(texture){texture->Release_Ref();texture=0;} }
};
class Render2DClass {
public:
 void Set_Texture(const FontTextureOwner &p) {
  if(p.texture==Texture.texture)return;
  Texture=p;CurrentBatch=Texture.texture?-1:0;
 }
 char fields00[0x40];RefCountPtr<TextureClass> Texture;int CurrentBatch;
};
class FontRendererVector {
public:
 virtual ~FontRendererVector();
 virtual bool Equal(const FontRendererVector &);
 virtual bool Resize(int,Render2DClass * const *);
 virtual void Clear();
 Render2DClass **items;int capacity;bool valid,allocated;short pad;int count,growth;
};
struct FontPendingSurface { SurfaceClass surface;FontRendererVector renderers; };
class FontPendingVector {
public:
 virtual ~FontPendingVector();
 virtual bool Equal(const FontPendingVector &);
 virtual bool Resize(int,const FontPendingSurface *);
 virtual void Clear();
 void Delete_All(){int size=capacity;Clear();Resize(size,0);}
 FontPendingSurface *items;int capacity;bool valid,allocated;short pad;int count,growth;
};
class BfmeFontD3DDevice {
public:
 virtual void __stdcall slot00();
 virtual void __stdcall slot04();
 virtual void __stdcall slot08();
 virtual void __stdcall slot0c();
 virtual void __stdcall slot10();
 virtual void __stdcall slot14();
 virtual void __stdcall slot18();
 virtual void __stdcall slot1c();
 virtual void __stdcall slot20();
 virtual void __stdcall slot24();
 virtual void __stdcall slot28();
 virtual void __stdcall slot2c();
 virtual void __stdcall slot30();
 virtual void __stdcall slot34();
 virtual void __stdcall slot38();
 virtual void __stdcall slot3c();
 virtual void __stdcall slot40();
 virtual void __stdcall slot44();
 virtual void __stdcall slot48();
 virtual void __stdcall slot4c();
 virtual void __stdcall slot50();
 virtual void __stdcall slot54();
 virtual void __stdcall slot58();
 virtual void __stdcall slot5c();
 virtual void __stdcall slot60();
 virtual void __stdcall slot64();
 virtual void __stdcall slot68();
 virtual void __stdcall slot6c();
 virtual void __stdcall slot70();
 virtual void __stdcall slot74();
 virtual long __stdcall UpdateSurface(BfmeFontSurfaceResource *,const void *,BfmeFontSurfaceResource *,const void *);
};
class IDirect3DDevice8;
class DX8Wrapper { public: static IDirect3DDevice8 *D3DDevice; };
extern unsigned number_of_DX8_calls;
class Rva00154FD0 {
public:
 void rva00154FD0();
 char fields00[0x1c];FontPendingVector pending;
 char fields34[0x34];Vector2i offset;int startX;char fields74[8];
 W3DRadarResetSurface current;
};
void Rva00154FD0::rva00154FD0()
{
 if(current.surface){current.surface->Release();current.surface=0;}
 offset.Set(0,0);startX=0;
 for(int index=0;index<pending.count;++index){
  FontPendingSurface &surface_info=pending.items[index];
  W3DRadarResetSurface curr_surface(surface_info.surface);
  SurfaceClass::SurfaceDescription desc;
  reinterpret_cast<SurfaceClass *>(&curr_surface)->Get_Description(desc);
  FontTextureOwner new_texture;
  new_texture.Create(desc.Width,desc.Width,desc.Format,1,0,0);
  W3DRadarResetSurface texture_surface=reinterpret_cast<CursorTextureSlot *>(&new_texture)->Get_Surface_Level();
  new_texture.Get_Filter()->UAddrMode=1;
  new_texture.Get_Filter()->VAddrMode=1;
  new_texture.Get_Filter()->MinFilter=2;
  new_texture.Get_Filter()->MagFilter=2;
  reinterpret_cast<_STL::ios_base *>(new_texture.Get_Filter())->_M_clear_nothrow(2);
  reinterpret_cast<BfmeFontD3DDevice *>(DX8Wrapper::D3DDevice)->UpdateSurface(curr_surface.surface,0,texture_surface.surface,0);
  ++number_of_DX8_calls;
  for(int renderer_index=0;renderer_index<surface_info.renderers.count;++renderer_index)
   surface_info.renderers.items[renderer_index]->Set_Texture(new_texture);
  new_texture.Release();
 }
 if(pending.count>0)pending.Delete_All();
}
