// ?loadAuxImage@Rva0013107A@@QAE_NXZ
// partial score=0.97 date=2026-10-09
// Retail131965..131A04 volume159B and131A04..131A9D cube153B.
// Target D3D9 import identities are independently read from the PE import table.
// Stack option values and field offsets are target facts. ZH textureloader
// and DX8.1 D3DX declarations establish purpose and argument roles; target
// Direct3D9 COM slots17/GetLevelDesc and IID_IDirect3DBaseTexture9 are verified
// against retail. Native GUID bytes equal580ca87e-1d3c-4d54-991d-b7d3e3c298ce.
// Method names remain descriptive target-derived names; class owner is the
// rowed Rva0013107A constructor and surrounding refresh methods.
// cl: /O1 /Oy- /G7 /MD /EHs
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
};
extern "C" long __stdcall D3DXCreateVolumeTextureFromFileInMemoryEx(void*,const void*,unsigned,unsigned,unsigned,unsigned,unsigned,unsigned,int,int,unsigned,unsigned,unsigned,void*,void*,TextureCOM9**);
extern "C" long __stdcall D3DXCreateCubeTextureFromFileInMemoryEx(void*,const void*,unsigned,unsigned,unsigned,unsigned,int,int,unsigned,unsigned,unsigned,void*,void*,TextureCOM9**);
class Rva0013107A {
public:
 bool loadAuxImage();void loadImage();void PostLoad(const char *name);void loadVolume();void loadCube();void loadVolumeSlices();
private:
 char head[8];void*m_resource;int m_type;char gap10[4];unsigned char *m_source;unsigned m_size;char gap1C[4];unsigned char *m_secondBuffer;unsigned m_secondSize;unsigned m_width,m_height,m_depth,m_sliceWidth,m_sliceHeight,m_originalDepth;int m_imageMode;unsigned m_mipLevels;int m_reductionMode;int m_format;int m_pool,m_usage;
};
void Rva0013107A::loadVolume() {
 TextureDeviceLock lock;TextureCOM9 *texture=0;
 if(D3DXCreateVolumeTextureFromFileInMemoryEx(DX8Wrapper::D3DDevice,m_source,m_size,m_width,m_height,m_depth,m_mipLevels,0,m_format,1,-1,-1,0,0,0,&texture)<0)texture=0;
 if(texture){TextureVolumeDesc desc;texture->GetLevelDesc(0,&desc);m_format=desc.format;texture->QueryInterface(TextureBaseInterfaceID,&m_resource);texture->Release();texture=0;}
}
void Rva0013107A::loadCube() {
 TextureDeviceLock lock;TextureCOM9 *texture=0;
 if(D3DXCreateCubeTextureFromFileInMemoryEx(DX8Wrapper::D3DDevice,m_source,m_size,m_width,m_mipLevels,0,m_format,1,-1,-1,0,0,0,&texture)<0)texture=0;
 if(texture){TextureSurfaceDesc desc;texture->GetLevelDesc(0,&desc);m_format=desc.format;texture->QueryInterface(TextureBaseInterfaceID,&m_resource);texture->Release();texture=0;}
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
 handles.texture->QueryInterface(TextureBaseInterfaceID,&m_resource);
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

// BFME 1 f98983a7d Rva0090C2F0InnerLoad.cpp gives reduction, buffer
// ownership and missing-texture workflow. WB9D11C0 identifies PostLoad.
// BFME2 native adds ResourceType/volume-strip inference and named loaders.
void __cdecl operator delete[](void *);
extern "C" __declspec(dllimport) char *__cdecl strrchr(const char *,int);
extern "C" __declspec(dllimport) int __cdecl _strnicmp(const char *,const char *,unsigned);
struct TextureImageInfo {unsigned width,height,depth,mips,format,type,fileFormat;};
extern "C" long __stdcall D3DXGetImageInfoFromFileInMemory(const void *,unsigned,TextureImageInfo *);
int Rva00117C00Get();
class BfmeResetTextureBackend {public:void CreateTexture(int,int,int,int,int,int,int);};
class SurfaceResource {public:virtual void s0();virtual void s1();virtual unsigned __stdcall Release();};
struct TexturePostLoadCOM9 {
 virtual void s0();virtual void s1();virtual void s2();virtual void s3();virtual void s4();virtual void s5();virtual void s6();virtual void s7();virtual void s8();virtual void s9();virtual void s10();virtual void s11();virtual void s12();
 virtual unsigned __stdcall GetLevelCount();
 virtual void s14();virtual void s15();virtual void s16();virtual void s17();
 virtual long __stdcall GetSurfaceLevel(unsigned,SurfaceResource **);
 virtual long __stdcall LockRect(unsigned,void *,const void *,unsigned);
 virtual long __stdcall UnlockRect(unsigned);
};
class SurfaceClass {public:void DrawPixel(unsigned,unsigned,unsigned);};
class W3DRadarResetSurface {public:W3DRadarResetSurface(SurfaceResource *);~W3DRadarResetSurface();SurfaceResource *surface;
 __forceinline void DrawPixel(unsigned x,unsigned y,unsigned color){reinterpret_cast<SurfaceClass *>(this)->DrawPixel(x,y,color);}
};
void Log_DX8_ErrorCode(unsigned);
void Rva0013107A::PostLoad(const char *name){
 if(m_source){
  m_resource=0;
  TextureImageInfo info;
  if(D3DXGetImageInfoFromFileInMemory(m_source,m_size,&info)>=0){
   m_width=info.width;m_sliceWidth=info.width;
   m_height=info.height;m_sliceHeight=info.height;
   m_depth=info.depth;m_originalDepth=info.depth;
   m_imageMode=info.fileFormat;
   if(info.type==4)m_type=1;else if(info.type==5)m_type=2;else m_type=0;
   bool volumeStrip=false;
   if(m_type==0){
    const char *dot=strrchr(name,'.');
    if(dot && dot-4>name && _strnicmp(dot-4,"_vol",4)==0 && m_width>m_height && m_width%m_height==0){
     volumeStrip=true;m_type=1;m_depth=m_width/m_height;m_originalDepth=m_depth;
     m_width=m_height;m_sliceWidth=m_width;m_mipLevels=1;
    }
   }
   int reduction=Rva00117C00Get();
   if(m_reductionMode<2){
    if(m_reductionMode>=1){if(m_width>512 || m_height>512)--reduction;else goto load;}
    if(reduction>1 && _strnicmp(name,"livingmap",9)==0)reduction=1;
    while(reduction>0){
     --reduction;
     if(m_width<=32 || m_height<=32 || (m_type==1 && m_depth<=32))break;
     m_width>>=1;m_height>>=1;if(m_type==1)m_depth>>=1;
    }
   }
load:
   if(m_type==0)loadImage();
   else if(m_type==1){if(volumeStrip)loadVolumeSlices();else loadVolume();}
   else if(m_type==2)loadCube();
  }
  m_pool=1;m_usage=0;
  delete[] m_source;m_source=0;
  if(m_secondBuffer){delete[] m_secondBuffer;m_secondBuffer=0;}
  if(m_resource){TextureDeviceLock lock;m_mipLevels=reinterpret_cast<TexturePostLoadCOM9 *>(m_resource)->GetLevelCount();return;}
 }
 TextureDeviceLock lock;
 reinterpret_cast<BfmeResetTextureBackend *>(this)->CreateTexture(1,1,0x15,1,1,0,0);
 if(m_resource){
  SurfaceResource *surface=0;
  long result=reinterpret_cast<TexturePostLoadCOM9 *>(m_resource)->GetSurfaceLevel(0,&surface);
  if(result)Log_DX8_ErrorCode(result);
  W3DRadarResetSurface(surface).DrawPixel(0,0,0xffff00ff);
  surface->Release();
 }
}

extern "C" long __stdcall D3DXCreateTexture(void*,unsigned,unsigned,unsigned,unsigned,int,int,TextureCOM9**);
extern "C" long __stdcall D3DXCreateTextureFromFileInMemoryEx(void*,const void*,unsigned,unsigned,unsigned,unsigned,unsigned,int,int,unsigned,unsigned,unsigned,void*,void*,TextureCOM9**);
extern "C" long __stdcall D3DXLoadSurfaceFromFileInMemory(SurfaceResource*,void*,const void*,const void*,unsigned,const void*,unsigned,unsigned,void*);
struct TextureLockedRect {int pitch;unsigned char *bits;};
bool Rva0013107A::loadAuxImage(){
 if(!m_secondBuffer || !m_secondSize)return false;
 void **resource=&m_resource;
 *resource=0;
 m_format=21;
 TextureCOM9 *texture;
 if(D3DXCreateTexture(DX8Wrapper::D3DDevice,m_width,m_height,m_mipLevels,0,m_format,1,&texture)<0)return false;
 bool copied=false;
 SurfaceResource *surface;
 if(reinterpret_cast<TexturePostLoadCOM9 *>(texture)->GetSurfaceLevel(0,&surface)<0)goto freeTexture;
 if(D3DXLoadSurfaceFromFileInMemory(surface,0,0,m_source,m_size,0,-1,0,0)<0)goto freeSurface;
 {
  TextureCOM9 *alpha;
  if(D3DXCreateTextureFromFileInMemoryEx(DX8Wrapper::D3DDevice,m_secondBuffer,m_secondSize,m_width,m_height,1,0,28,2,-1,-1,0,0,0,&alpha)<0)goto freeSurface;
  TextureSurfaceDesc desc;
  alpha->GetLevelDesc(0,&desc);
  if(desc.format==28 || desc.format==50 || desc.format==21){
   int stride=1,offset=0;
   if(desc.format==21){offset=3;stride=4;}
   struct {TextureLockedRect alphaRect,colorRect;} rects;
   if(reinterpret_cast<TexturePostLoadCOM9 *>(texture)->LockRect(0,&rects.colorRect,0,0)>=0){
    if(reinterpret_cast<TexturePostLoadCOM9 *>(alpha)->LockRect(0,&rects.alphaRect,0,0)>=0){
     copied=true;
     unsigned char *colorRow=rects.colorRect.bits,*alphaRow=rects.alphaRect.bits;
     for(unsigned y=0;y<m_height;++y){
      unsigned char *a=alphaRow+offset,*c=colorRow+3;
      for(unsigned x=0;x<m_width;++x){*c=*a;a+=stride;c+=4;}
      alphaRow+=rects.alphaRect.pitch;colorRow+=rects.colorRect.pitch;
     }
     reinterpret_cast<TexturePostLoadCOM9 *>(alpha)->UnlockRect(0);
    }
    reinterpret_cast<TexturePostLoadCOM9 *>(texture)->UnlockRect(0);
   }
  }
  alpha->Release();
 }
 freeSurface:
 surface->Release();
 if(copied){D3DXFilterTexture(texture,0,0,-1);texture->QueryInterface(TextureBaseInterfaceID,resource);}
 freeTexture:
 texture->Release();
 return *resource!=0;
}
