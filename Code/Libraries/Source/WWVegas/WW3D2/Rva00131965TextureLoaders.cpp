#include <string.h>
// Retail131965..131A04 volume159B and131A04..131A9D cube153B.
// Target D3D9 import identities are independently read from the PE import table.
// Stack option values and field offsets are target facts. ZH textureloader
// and DX8.1 D3DX declarations establish purpose and argument roles; target
// Direct3D9 COM slots17/GetLevelDesc and IID_IDirect3DBaseTexture9 are verified
// against retail. Native GUID bytes equal580ca87e-1d3c-4d54-991d-b7d3e3c298ce.
// Method names remain descriptive target-derived names; class owner is the
// rowed Rva0013107A constructor and surrounding refresh methods.
// cl: /O1 /G7 /MD /EHs
extern void BFME_DX8_Thread_Lock();
extern bool BFME_DX8_Thread_Assert();
struct TextureDeviceLock {TextureDeviceLock(){BFME_DX8_Thread_Lock();}~TextureDeviceLock(){BFME_DX8_Thread_Assert();}};
struct IDirect3DDevice8;
class DX8Wrapper {friend class Rva0013107A;protected:static IDirect3DDevice8 *D3DDevice;};
struct TextureGUID {unsigned long a;unsigned short b,c;unsigned char d[8];};
const TextureGUID TextureBaseInterfaceID={0x580ca87e,0x1d3c,0x4d54,{0x99,0x1d,0xb7,0xd3,0xe3,0xc2,0x98,0xce}};
struct TextureVolumeDesc {int format,type,usage,pool;unsigned width,height,depth;};
struct TextureSurfaceDesc {int format,type,usage,pool;int multisample,quality;unsigned width,height;};
struct TextureBox {unsigned left,top,right,bottom,front,back;};
struct VolumeCOM9 { virtual void slot0()=0;virtual void slot1()=0;virtual unsigned long __stdcall Release()=0;virtual void slot3()=0;virtual void slot4()=0;virtual void slot5()=0;virtual void slot6()=0;virtual void slot7()=0;virtual long __stdcall GetDesc(TextureVolumeDesc*)=0;};
struct TextureCOM9 {
 virtual long __stdcall QueryInterface(const TextureGUID &,void**)=0;
 virtual unsigned long __stdcall AddRef()=0;
 virtual unsigned long __stdcall Release()=0;
 virtual void slot3()=0;virtual void slot4()=0;virtual void slot5()=0;virtual void slot6()=0;virtual void slot7()=0;virtual void slot8()=0;virtual void slot9()=0;virtual void slot10()=0;virtual void slot11()=0;virtual void slot12()=0;virtual unsigned __stdcall GetLevelCount()=0;virtual void slot14()=0;virtual void slot15()=0;virtual void slot16()=0;
 virtual long __stdcall GetLevelDesc(unsigned,void*)=0;
 virtual long __stdcall GetVolumeLevel(unsigned,VolumeCOM9**)=0;
 virtual long __stdcall LockRect(unsigned,void*,const void*,unsigned)=0;
 virtual long __stdcall UnlockRect(unsigned)=0;
};
extern "C" long __stdcall D3DXCreateVolumeTextureFromFileInMemoryEx(void*,const void*,unsigned,unsigned,unsigned,unsigned,unsigned,unsigned,int,int,unsigned,unsigned,unsigned,void*,void*,TextureCOM9**);
extern "C" long __stdcall D3DXCreateCubeTextureFromFileInMemoryEx(void*,const void*,unsigned,unsigned,unsigned,unsigned,int,int,unsigned,unsigned,unsigned,void*,void*,TextureCOM9**);
class Rva0013107A {
public:
 bool loadAuxImage();void loadImage();void postLoad(const char *);void loadVolume();void loadCube();void loadVolumeSlices();
private:
 char head[8];TextureCOM9*m_resource;int m_type;char gap[4];char*m_source;unsigned m_size;char gap1[4];char*m_alpha;char gap24[4];unsigned m_width,m_height,m_depth,m_sliceWidth,m_sliceHeight,m_originalDepth;int m_imageMode;unsigned m_mipLevels;int m_preference;int m_format;int m_ready,m_loading;
};
void Rva0013107A::loadVolume() {
 TextureDeviceLock lock;TextureCOM9 *texture=0;
 if(D3DXCreateVolumeTextureFromFileInMemoryEx(DX8Wrapper::D3DDevice,m_source,m_size,m_width,m_height,m_depth,m_mipLevels,0,m_format,1,-1,-1,0,0,0,&texture)<0)texture=0;
 if(texture){TextureVolumeDesc desc;texture->GetLevelDesc(0,&desc);m_format=desc.format;texture->QueryInterface(TextureBaseInterfaceID,reinterpret_cast<void **>(&m_resource));texture->Release();texture=0;}
}
void Rva0013107A::loadCube() {
 TextureDeviceLock lock;TextureCOM9 *texture=0;
 if(D3DXCreateCubeTextureFromFileInMemoryEx(DX8Wrapper::D3DDevice,m_source,m_size,m_width,m_mipLevels,0,m_format,1,-1,-1,0,0,0,&texture)<0)texture=0;
 if(texture){TextureSurfaceDesc desc;texture->GetLevelDesc(0,&desc);m_format=desc.format;texture->QueryInterface(TextureBaseInterfaceID,reinterpret_cast<void **>(&m_resource));texture->Release();texture=0;}
}

extern "C" long __stdcall D3DXCreateVolumeTexture(void*,unsigned,unsigned,unsigned,unsigned,unsigned,int,int,TextureCOM9**);
extern "C" long __stdcall D3DXLoadVolumeFromFileInMemory(VolumeCOM9*,void*,const TextureBox*,const void*,unsigned,const TextureBox*,unsigned,unsigned,void*);
extern "C" long __stdcall D3DXFilterTexture(TextureCOM9*,void*,unsigned,unsigned);
struct TextureVolumeResources {VolumeCOM9 *volume;TextureCOM9 *texture;};
void Rva0013107A::loadVolumeSlices() {
 TextureDeviceLock lock;TextureVolumeResources handles;handles.texture=0;
 TextureVolumeDesc desc;TextureBox dest,src;
 if(D3DXCreateVolumeTexture(DX8Wrapper::D3DDevice,m_width,m_height,m_depth,m_mipLevels,0,m_format,1,&handles.texture)<0)return;
 handles.volume=0;
 if(handles.texture->GetVolumeLevel(0,&handles.volume)<0)goto freeTexture;
 if(handles.volume->GetDesc(&desc)<0)goto freeVolume;
 src.top=0;src.bottom=m_sliceHeight;src.front=0;src.back=1;
 dest.left=0;dest.top=0;dest.right=desc.width;dest.bottom=desc.height;
 for(unsigned i=0;i<m_depth;++i){
  src.left=m_sliceWidth*i;src.right=src.left+m_sliceWidth;
  dest.front=i;dest.back=i+1;
  if(D3DXLoadVolumeFromFileInMemory(handles.volume,0,&dest,m_source,m_size,&src,-1,0,0)<0)goto freeVolume;
 }
 handles.volume->Release();handles.volume=0;
 if(D3DXFilterTexture(handles.texture,0,0,-1)<0)goto freeTexture;
 m_format=desc.format;
 handles.texture->QueryInterface(TextureBaseInterfaceID,reinterpret_cast<void **>(&m_resource));
 freeTexture:
 handles.texture->Release();handles.texture=0;
 return;
 freeVolume:
 handles.volume->Release();handles.volume=0;
 goto freeTexture;
}

// Slice loader: target324B plus exact EH; source/destination D3DBOX layouts
// are target-verified. The two handle fields retain native volume then texture
// stack ordering. right=left+sliceWidth preserves the native single multiply.

void __cdecl operator delete[](void *);
struct TextureImageInfo {unsigned width,height,depth,mips;int format,type,imageMode;};
extern "C" long __stdcall D3DXGetImageInfoFromFileInMemory(const void*,unsigned,TextureImageInfo*);
int Rva00117C00Get();
class BfmeResetTextureBackend {public:void CreateTexture(int,int,int,int,int,int,int);};
class SurfaceResource {public:virtual void slot0();virtual void slot1();virtual unsigned long __stdcall Release();};
class SurfaceClass {public:void DrawPixel(unsigned,unsigned,unsigned);};
class W3DRadarResetSurface {
public:W3DRadarResetSurface(SurfaceResource*);~W3DRadarResetSurface();
 __forceinline void DrawPixel(unsigned x,unsigned y,unsigned c){reinterpret_cast<SurfaceClass*>(this)->DrawPixel(x,y,c);}
private:SurfaceResource*surface;
};
void Log_DX8_ErrorCode(unsigned);
struct Texture2DSurfaceView {
 virtual void slot0();virtual void slot1();virtual void slot2();virtual void slot3();virtual void slot4();virtual void slot5();virtual void slot6();virtual void slot7();virtual void slot8();virtual void slot9();virtual void slot10();virtual void slot11();virtual void slot12();virtual void slot13();virtual void slot14();virtual void slot15();virtual void slot16();virtual void slot17();
 virtual long __stdcall GetSurfaceLevel(unsigned,SurfaceResource**);
};
// ?postLoad@Rva0013107A@@QAEXPBD@Z
// Native 0x00131E6E..0x001320B4 (582 bytes); WorldBuilder PostLoad lead.
// Existing constructor and the three loaders establish the neutral owner.
// Retail proves image-info field assignments, resource-kind dispatch, _vol
// slice detection, livingmap reduction limit, source-buffer lifetime, and
// the one-pixel magenta fallback. D3D9 slots 13/18 and existing surface
// holder/lock providers preserve the native ownership and EH states.
// The 2D loadImage provider remains unrowed; its complete 726-byte native
// body and same-receiver calls establish the descriptive callee ABI only.
void Rva0013107A::postLoad(const char*name) {
 if(m_source) {
  m_resource=0;
  TextureImageInfo info;
  if(D3DXGetImageInfoFromFileInMemory(m_source,m_size,&info)>=0) {
   m_width=info.width;m_sliceWidth=m_width;m_height=info.height;m_sliceHeight=m_height;m_depth=info.depth;m_originalDepth=m_depth;m_imageMode=info.imageMode;
   if(info.type==4)m_type=1;else if(info.type==5)m_type=2;else m_type=0;
   bool slices=false;
   if(m_type==0) {
    const char *dot=strrchr(name,'.');
    if(dot && dot-4>name && !_strnicmp(dot-4,"_vol",4) && m_width>m_height && m_width%m_height==0) {
     slices=true;m_type=1;m_depth=m_width/m_height;m_originalDepth=m_depth;m_width=m_height;m_sliceWidth=m_width;m_mipLevels=1;
    }
   }
   int reduction=Rva00117C00Get();
   if(m_preference>=2)reduction=0;
   else {
    if(m_preference>=1){if(m_width<=512&&m_height<=512)reduction=0;else --reduction;}
    if(reduction>1&&!_strnicmp(name,"livingmap",9))reduction=1;
   }
   while(reduction>0) {
    --reduction;
    if(m_width<=32||m_height<=32||(m_type==1&&m_depth<=32))break;
    m_width>>=1;m_height>>=1;if(m_type==1)m_depth>>=1;
   }
   if(m_type==0)loadImage();
   else if(m_type==1){if(slices)loadVolumeSlices();else loadVolume();}
   else if(m_type==2)loadCube();
  }
  m_ready=1;m_loading=0;::operator delete[](m_source);m_source=0;
  if(m_alpha){::operator delete[](m_alpha);m_alpha=0;}
  if(m_resource){TextureDeviceLock lock;m_mipLevels=m_resource->GetLevelCount();return;}
 }
 TextureDeviceLock lock;
 reinterpret_cast<BfmeResetTextureBackend*>(this)->CreateTexture(1,1,21,1,1,0,0);
 if(m_resource) {
  SurfaceResource *surface=0;
  long hr=reinterpret_cast<Texture2DSurfaceView*>(m_resource)->GetSurfaceLevel(0,&surface);
  if(hr)Log_DX8_ErrorCode(hr);
  W3DRadarResetSurface(surface).DrawPixel(0,0,0xffff00ff);
  surface->Release();
 }
}

// Native 0x0013154B..0x00131821 (726 bytes), WB Load2DTexture lead.
// The same-receiver PostLoad dispatch and adjacent rowed loaders establish
// the neutral owner. The packed TGA header and reverse-row 24/32-bit upload,
// DDS mip skip, D3D9 slots, and base-interface ownership follow retail.
// Error-first creation and the bounded even-ratio loop preserve native block
// placement. The separate-alpha provider returns bool; its complete retail
// body proves that ABI although its result is unused by this caller.
extern "C" long __stdcall D3DXCheckTextureRequirements(void*,unsigned*,unsigned*,unsigned*,unsigned,int*,int);
extern "C" long __stdcall D3DXCreateTexture(void*,unsigned,unsigned,unsigned,unsigned,int,int,TextureCOM9**);
extern "C" long __stdcall D3DXCreateTextureFromFileInMemoryEx(void*,const void*,unsigned,unsigned,unsigned,unsigned,unsigned,int,int,unsigned,unsigned,unsigned,void*,void*,TextureCOM9**);
extern "C" void *__cdecl memcpy(void*,const void*,unsigned);
struct TextureLockedRect {int pitch;unsigned char *bits;};
#pragma pack(push,1)
struct TextureTgaHeader {unsigned char id,colorMap,type;char rest[9];short width,height;unsigned char bits,flags;};
#pragma pack(pop)
void Rva0013107A::loadImage() {
 TextureDeviceLock lock;TextureCOM9 *texture=0;bool loaded=false;
 if(m_alpha){loadAuxImage();}
 else {
  const TextureTgaHeader *header=(const TextureTgaHeader*)m_source;
  if(m_imageMode==2 && header->type==2 && header->id==0 && header->colorMap==0 && (header->bits==24||header->bits==32) && header->width%4==0 && !(header->flags&0xf0)){
   int format=header->bits==24?22:21;
   if(D3DXCheckTextureRequirements(DX8Wrapper::D3DDevice,&m_width,&m_height,0,0,&format,1)>=0 && m_width==(int)header->width && m_height==(int)header->height && format==(header->bits==24?22:21)) {
    if(D3DXCreateTexture(DX8Wrapper::D3DDevice,header->width,header->height,m_mipLevels,0,format,1,&texture)<0)texture=0;
    else {
     TextureLockedRect rect;
     if(texture->LockRect(0,&rect,0,0x800)>=0){
      unsigned char *dst=rect.bits+(header->height-1)*rect.pitch;
      const unsigned char *src=(const unsigned char*)m_source+18;
      if(header->bits==24){
       for(int y=header->height;y>0;--y){
        unsigned char *d=dst;const unsigned char*p=src;
        for(int x=header->width/4;x>0;--x){
         d[0]=p[0];d[1]=p[1];d[2]=p[2];d[4]=p[3];d[5]=p[4];d[6]=p[5];d[8]=p[6];d[9]=p[7];d[10]=p[8];d[12]=p[9];d[13]=p[10];d[14]=p[11];p+=12;d+=16;
        }
        dst-=rect.pitch;src+=header->width*3;
       }
      } else {
       int stride=header->width*4;
       for(int y=header->height;y>0;--y){memcpy(dst,src,stride);src+=stride;dst-=rect.pitch;}
      }
      texture->UnlockRect(0);
     }
     if(m_mipLevels!=1)D3DXFilterTexture(texture,0,0,5);
     loaded=true;
    }
   }
  }
  if(!loaded) {
   int skip=0;
   if(m_imageMode==4){
    int ratio=m_sliceWidth/m_width;
    if(ratio>1 && m_width*ratio==m_sliceWidth && m_height*ratio==m_sliceHeight){
     while(ratio>1 && !(ratio&1)){ratio>>=1;++skip;}
     if(ratio!=1)skip=0;
    }
   }
   if(D3DXCreateTextureFromFileInMemoryEx(DX8Wrapper::D3DDevice,m_source,m_size,m_width,m_height,m_mipLevels,0,m_format,1,-1,((skip&31)<<26)|5,0,0,0,&texture)<0)texture=0;
  }
 }
 if(texture){TextureSurfaceDesc desc;texture->GetLevelDesc(0,&desc);m_format=desc.format;texture->QueryInterface(TextureBaseInterfaceID,reinterpret_cast<void **>(&m_resource));texture->Release();texture=0;}
}
