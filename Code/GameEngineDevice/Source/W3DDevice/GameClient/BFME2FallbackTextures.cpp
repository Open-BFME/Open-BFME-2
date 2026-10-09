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
 void DrawPixel(unsigned x,unsigned y,unsigned color) { ((SurfaceClass *)this)->DrawPixel(x,y,color); }
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


// ?Load_Texture@@YA?AVBFME2ParticleTextureHandle@@AAVChunkLoadClass@@@Z
// Native 0x00132FFB..0x00133283: chunk 0x31 texture handle loader.
// Reference: GeneralsMD WW3D2/texture.cpp via Open-BFME-1 6583b3c1ff.
// Retail establishes the counted return, tga/dds/jpg fallback, texture-info
// masks, capability layout, and the inline U/V setters. The mip setter uses
// the existing measured 10-byte folded store ABI at 0x0013ED10; no additional
// name or template identity is asserted at that address.
#include <string.h>
class ChunkLoadClass {
public:
 bool Open_Chunk(); bool Close_Chunk(); unsigned long Cur_Chunk_ID();
 unsigned long Cur_Chunk_Length(); unsigned long Read(void *, unsigned long);
};
extern BFME2ParticleTextureHandle BFME2LoadParticleTexture(const char *, int, int);
bool Render_Obj_Exists(const char *);
enum WW3DFormat { WW3D_FORMAT_UNKNOWN=0 };
class W3DRadarFormatCaps {
public:
 char before[0x13c]; bool bump;
 bool supportTextureFormat(WW3DFormat);
};
class DX8Caps;
class DX8Wrapper { public: static DX8Caps *CurrentCaps; static bool IsInitted; };
namespace _STL { class ios_base { protected: void _M_clear_nothrow(int); }; }
// Same measured folded setter ABI view used by Render2DSentenceBuildTexturesBFME2.
// This does not assert the original texture filter inherits from STL ios_base.
class ShroudFilter : public _STL::ios_base {
public:
 int unused[2], mip, u, v;
 using _STL::ios_base::_M_clear_nothrow;
 void SetU(bool value) { u=value?1:0; }
 void SetV(bool value) { v=value?1:0; }
};
class ShroudTexture {
public: ShroudFilter *getFilter();
};
struct TextureInfo { unsigned short Attributes, AnimType; unsigned int FrameCount; float FrameRate; };
BFME2ParticleTextureHandle Load_Texture(ChunkLoadClass &cload)
{
 char name[256];
 if(cload.Open_Chunk() && cload.Cur_Chunk_ID()==0x31) {
  TextureInfo texinfo;
  bool hastexinfo=false;
  name[0]=0;
  while(cload.Open_Chunk()) {
   switch(cload.Cur_Chunk_ID()) {
    case 0x32: cload.Read(name,cload.Cur_Chunk_Length()); break;
    case 0x33: cload.Read(&texinfo,sizeof(texinfo)); hastexinfo=true; break;
   }
   cload.Close_Chunk();
  }
  cload.Close_Chunk();
  char *ext=strrchr(name,'.');
  if(ext && !_strcmpi(ext,".tga")) {
   char alternate[256];
   strcpy(alternate,name);
   char *altExt=alternate+(ext-name);
   strcpy(altExt,".dds");
   if(!Render_Obj_Exists(alternate)) {
    strcpy(altExt,".jpg");
    if(!Render_Obj_Exists(alternate)) goto keep_name;
   }
   strcpy(name,alternate);
  }
keep_name:
  if(hastexinfo) {
   int mipcount=4;
   bool no_lod=(texinfo.Attributes&4)==4;
   if(no_lod) mipcount=1;
   else switch(texinfo.Attributes&0xc0) {
    case 0: mipcount=0;break;
    case 0x40: mipcount=2;break;
    case 0x80: mipcount=3;break;
    case 0xc0: break;
    default:mipcount=0;break;
   }
   int format=0;
   if((texinfo.Attributes&0x1000) && DX8Wrapper::IsInitted && reinterpret_cast<W3DRadarFormatCaps *>(DX8Wrapper::CurrentCaps)->bump) {
    mipcount=1;
    if(reinterpret_cast<W3DRadarFormatCaps *>(DX8Wrapper::CurrentCaps)->supportTextureFormat((WW3DFormat)60)) format=60;
    else if(reinterpret_cast<W3DRadarFormatCaps *>(DX8Wrapper::CurrentCaps)->supportTextureFormat((WW3DFormat)62)) format=62;
    else if(reinterpret_cast<W3DRadarFormatCaps *>(DX8Wrapper::CurrentCaps)->supportTextureFormat((WW3DFormat)61)) format=61;
   }
   BFME2ParticleTextureHandle tex=BFME2LoadParticleTexture(name,mipcount,format);
   if(no_lod) reinterpret_cast<ShroudTexture*>(&tex)->getFilter()->_M_clear_nothrow(0);
   bool u=(texinfo.Attributes&8)!=0;
   reinterpret_cast<ShroudTexture*>(&tex)->getFilter()->SetU(u);
   bool v=(texinfo.Attributes&16)!=0;
   reinterpret_cast<ShroudTexture*>(&tex)->getFilter()->SetV(v);
   return BFME2ParticleTextureHandle(tex.Ptr, BFME2ParticleTextureHandle::ACQUIRE_INLINE);
  } else return BFME2LoadParticleTexture(name,0,0);
 }
 return BFME2ParticleTextureHandle();
}
