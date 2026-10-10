// ?rva001321A7@BfmeThing937B@@QAEXPAX@Z
// partial score=0.827430394046116 date=2026-10-10
// ?rva001321A7@BfmeThing937B@@QAEXPAX@Z
// cl: /O1 /Ob1 /G7 /DNDEBUG /MD /EHsc
// Full reconstruction emits 1335B versus native1347B; fitness .827430394.
// All actual callees now resolve. Remaining: initial this EBX vs ESI;
// query-output and pitch stack slots (-1C/-18) exchanged; format-guard
// branch placement; early dynamic-option extraction; loop/color stack roles.
// 15 isolated source/configuration shapes: unsigned bitfields, bool/getter
// temporaries, union flag view, format guards, pointer and local ordering,
// coefficient read order, allocation product order and G6. No exact shape.
// The actual QueryInterface GUID was read from retail: 85c31227-3de5-4f00-
// 9b3a-f11ac38c18b5. Existing IID_TexSurface's zero initializer in the cursor
// TU is a placeholder and must not be reused as link/data proof for this bank.
// The matched Rva000B4653 helper returns an opaque pointer-typed DWORD:
// native passes its raw bits to the RGB-unpack helper, not a dereference.
// TextureRecolorSurfaceLock retains the native surface-reference lifetime.
// Count0/1/2/3 BGR paths preserve alpha; A4R4G4B4 uses signed product/divide
// of the entire input WORD followed by the native nibble masks. No invented
// input-validation path or change to the retail iteration bounds.
// Complete native 0x001321A7..0x001326EA (1347 bytes), RET 4.
// WB 0x009D2F80 explicitly identifies TextureAsset::RecolorFactoryDecal::
// RecolorTexture at texture.cpp:1129..1334. The ZH texture class does not
// contain this BFME factory path; target/WB are the semantic source here.
// All offsets, COM slots, packed flags and pixel arithmetic are retail facts.
// The descriptive/neutral ABI names below reuse the existing helper providers.
#include <string.h>
void *operator new[](unsigned);
struct TextureRecolorGUID {unsigned long a;unsigned short b,c;unsigned char d[8];};
// Read directly from native VA 0x00CE0AD8; IID_IDirect3DTexture9.
static const TextureRecolorGUID TextureRecolorIID={0x85c31227,0x3de5,0x4f00,{0x9b,0x3a,0xf1,0x1a,0xc3,0x8c,0x18,0xb5}};
struct TextureRecolorCOM;
class SurfaceResource;
struct TextureRecolorCOM {
 virtual long __stdcall QueryInterface(const TextureRecolorGUID &,void **)=0;
 virtual unsigned long __stdcall AddRef()=0;
 virtual unsigned long __stdcall Release()=0;
 virtual void slot3()=0; virtual void slot4()=0; virtual void slot5()=0;
 virtual void slot6()=0; virtual void slot7()=0; virtual void slot8()=0;
 virtual void slot9()=0; virtual void slot10()=0; virtual void slot11()=0;
 virtual void slot12()=0; virtual void slot13()=0; virtual void slot14()=0;
 virtual void slot15()=0; virtual void slot16()=0; virtual void slot17()=0;
 virtual long __stdcall GetSurfaceLevel(unsigned,SurfaceResource **)=0;
};
class SurfaceResource {public:
 virtual long __stdcall QueryInterface(const TextureRecolorGUID &,void **)=0;
 virtual unsigned long __stdcall AddRef()=0;
 virtual unsigned long __stdcall Release()=0;
};
class W3DRadarResetSurface {public:
 SurfaceResource *m_surface;
 W3DRadarResetSurface(SurfaceResource *);
 ~W3DRadarResetSurface();
};
class SurfaceClass {public:
 struct SurfaceDescription {unsigned Format,Width,Height;};
 void Get_Description(SurfaceDescription &);
};
class Rva00116680 {public:void *rva00116680(int *,bool);};
class Member0C00739C70 {public:void clear();};
struct TextureRecolorSurfaceLock {
 W3DRadarResetSurface &surface;
 TextureRecolorSurfaceLock(W3DRadarResetSurface &s,void *&bits,int &pitch,bool discard):surface(s) {
  bits=reinterpret_cast<Rva00116680 *>(&s)->rva00116680(&pitch,discard);
 }
 ~TextureRecolorSurfaceLock() {reinterpret_cast<Member0C00739C70 *>(&surface)->clear();}
};
void Log_DX8_ErrorCode(unsigned);
extern "C" long __stdcall D3DXFilterTexture(void *,void *,unsigned,unsigned);
struct TextureRecolorFlags {
 unsigned count:3;
 unsigned reserved03:27;
 unsigned dynamic:1;
 unsigned reserved31:1;
};
class Rva000B4653 {public:
 TextureRecolorFlags flags;
 void *rva000B4653(int);
};
class Rva00131D7D {public:
 void rva00131D7D(unsigned);
 int red,green,blue;
};
struct TextureRecolorImpl {unsigned char prefix[8];TextureRecolorCOM *texture;unsigned type;};
class BfmeThing937B {
 unsigned char prefix[0x14];
 TextureRecolorImpl *impl;
 unsigned char unused18[0x28];
 TextureRecolorFlags flags;
 unsigned char unused44[0xC];
 unsigned char *dynamicSource;
public:
 void rva001321A7(void *);
};
static __forceinline const unsigned &TextureRecolorMin(const unsigned &a,const unsigned &b) {return b<a?b:a;}
void BfmeThing937B::rva001321A7(void *settings)
{
 if(!impl || !impl->texture || impl->type!=0)return;
 TextureRecolorCOM *texture=0;
 if(impl->texture->QueryInterface(TextureRecolorIID,reinterpret_cast<void **>(&texture))<0 || !texture)return;
 SurfaceResource *surface=0;
 long hr=texture->GetSurfaceLevel(0,&surface);
 if(hr!=0)Log_DX8_ErrorCode(hr);
 W3DRadarResetSurface holder(surface);
 if(surface)surface->Release();
 texture->Release();
 texture=0;
 void *bits=0;
 int pitch=0;
 {
  TextureRecolorSurfaceLock lock(holder,bits,pitch,false);
  SurfaceClass::SurfaceDescription desc;
  reinterpret_cast<SurfaceClass *>(&holder)->Get_Description(desc);
  int pixelSize=0;
  if(desc.Format==21)pixelSize=4;
  else if(desc.Format==26)pixelSize=2;
  if(!pixelSize)return;
  Rva000B4653 *options=reinterpret_cast<Rva000B4653 *>(settings);
  if(options->flags.dynamic && !dynamicSource) {
   dynamicSource=new unsigned char[desc.Height*desc.Width*pixelSize];
   if(!dynamicSource)return;
   for(unsigned y=0;y<desc.Height;++y)
    memcpy(dynamicSource+y*desc.Width*pixelSize,reinterpret_cast<unsigned char *>(bits)+y*pitch,desc.Width*pixelSize);
   return;
  }
  unsigned char *source;
  int sourcePitch;
  if(flags.dynamic) {
   if(!dynamicSource)return;
   source=dynamicSource;
   sourcePitch=desc.Width*pixelSize;
  } else {
   source=reinterpret_cast<unsigned char *>(bits);
   sourcePitch=pitch;
  }
  unsigned count=options->flags.count;
  Rva00131D7D colors[3];
  for(unsigned i=0;i<count;++i)
   colors[i].rva00131D7D(reinterpret_cast<unsigned>(options->rva000B4653(i)));
  if(desc.Format==26) {
   unsigned short *src=reinterpret_cast<unsigned short *>(source);
   unsigned short *dst=reinterpret_cast<unsigned short *>(bits);
   int srcStride=sourcePitch/2;
   for(unsigned y=desc.Height;y;--y) {
    for(unsigned x=desc.Width;x;--x) {
     unsigned short pixel=*src++;
     *dst++=static_cast<unsigned short>((((pixel*colors[0].green)/255)&0xF0) |
              (((pixel*colors[0].blue)/255)&0xF) |
              (((pixel*colors[0].red)/255)&0xF00) | (pixel&0xF000));
    }
    dst+=pitch/2-desc.Width;
    src+=srcStride-desc.Width;
   }
  } else if(desc.Format==21) {
   unsigned char *src=source;
   unsigned char *dst=reinterpret_cast<unsigned char *>(bits);
   int srcGap=sourcePitch-desc.Width*4;
   int dstGap=pitch-desc.Width*4;
   switch(count) {
    case 0:
     for(unsigned y=desc.Height;y;--y,src+=srcGap,dst+=dstGap)
      for(unsigned x=desc.Width;x;--x,src+=4,dst+=4)
       *reinterpret_cast<unsigned *>(dst)=*reinterpret_cast<unsigned *>(src);
     break;
    case 1:
     for(unsigned y=desc.Height;y;--y,src+=srcGap,dst+=dstGap)
      for(unsigned x=desc.Width;x;--x,src+=4,dst+=4) {
       unsigned red=src[2];
       dst[0]=(red*colors[0].blue)>>8;
       dst[1]=(red*colors[0].green)>>8;
       dst[2]=(red*colors[0].red)>>8;
       dst[3]=src[3];
      }
     break;
    case 2:
     for(unsigned y=desc.Height;y;--y,src+=srcGap,dst+=dstGap)
      for(unsigned x=desc.Width;x;--x,src+=4,dst+=4) {
       unsigned red=src[2],green=src[1];
       dst[0]=TextureRecolorMin(((red*colors[0].blue)>>8)+((green*colors[1].blue)>>8),255U);
       dst[1]=TextureRecolorMin(((red*colors[0].green)>>8)+((green*colors[1].green)>>8),255U);
       dst[2]=TextureRecolorMin(((red*colors[0].red)>>8)+((green*colors[1].red)>>8),255U);
       dst[3]=src[3];
      }
     break;
    case 3:
     for(unsigned y=desc.Height;y;--y,src+=srcGap,dst+=dstGap)
      for(unsigned x=desc.Width;x;--x,src+=4,dst+=4) {
       unsigned red=src[2],green=src[1],blue=src[0];
       dst[0]=TextureRecolorMin(((blue*colors[2].blue)>>8)+((green*colors[1].blue)>>8)+((red*colors[0].blue)>>8),255U);
       dst[1]=TextureRecolorMin(((blue*colors[2].green)>>8)+((green*colors[1].green)>>8)+((red*colors[0].green)>>8),255U);
       dst[2]=TextureRecolorMin(((blue*colors[2].red)>>8)+((green*colors[1].red)>>8)+((red*colors[0].red)>>8),255U);
       dst[3]=src[3];
      }
     break;
   }
  }
 }
 D3DXFilterTexture(impl->texture,0,0,-1);
}
