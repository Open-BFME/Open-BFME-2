// ?loadImage@Rva0013107A@@QAEXXZ
// partial score=0.85 date=2026-10-09
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
 virtual void slot3()=0;virtual void slot4()=0;virtual void slot5()=0;virtual void slot6()=0;virtual void slot7()=0;virtual void slot8()=0;virtual void slot9()=0;virtual void slot10()=0;virtual void slot11()=0;virtual void slot12()=0;virtual void slot13()=0;virtual void slot14()=0;virtual void slot15()=0;virtual void slot16()=0;
 virtual long __stdcall GetLevelDesc(unsigned,void*)=0;
 virtual long __stdcall GetVolumeLevel(unsigned,VolumeCOM9**)=0;
 virtual long __stdcall LockRect(unsigned,void*,const void*,unsigned)=0;
 virtual long __stdcall UnlockRect(unsigned)=0;
};
extern "C" long __stdcall D3DXCreateVolumeTextureFromFileInMemoryEx(void*,const void*,unsigned,unsigned,unsigned,unsigned,unsigned,unsigned,int,int,unsigned,unsigned,unsigned,void*,void*,TextureCOM9**);
extern "C" long __stdcall D3DXCreateCubeTextureFromFileInMemoryEx(void*,const void*,unsigned,unsigned,unsigned,unsigned,int,int,unsigned,unsigned,unsigned,void*,void*,TextureCOM9**);
class Rva0013107A {
public:
 void loadImage();void loadAuxImage();void loadVolume();void loadCube();void loadVolumeSlices();
private:
 char head[8];void*m_resource;char gap[8];const void*m_source;unsigned m_size;char gap1[0xc];unsigned m_width,m_height,m_depth,m_sliceWidth,m_sliceHeight;char gap2[4];int m_imageMode;unsigned m_mipLevels;char gap3[4];int m_format;
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

extern "C" long __stdcall D3DXCheckTextureRequirements(void*,unsigned*,unsigned*,unsigned*,unsigned,int*,int);
extern "C" long __stdcall D3DXCreateTexture(void*,unsigned,unsigned,unsigned,unsigned,int,int,TextureCOM9**);
extern "C" long __stdcall D3DXCreateTextureFromFileInMemoryEx(void*,const void*,unsigned,unsigned,unsigned,unsigned,unsigned,int,int,unsigned,unsigned,unsigned,void*,void*,TextureCOM9**);
extern "C" void *__cdecl memcpy(void*,const void*,unsigned);
struct TextureLockedRect {int pitch;unsigned char *bits;};
#pragma pack(push,1)
struct TextureTgaHeader {unsigned char id,colorMap,type;char rest[9];short width,height;unsigned char bits,flags;};
#pragma pack(pop)
void Rva0013107A::loadImage() {
 TextureDeviceLock lock;TextureCOM9 *texture=0;
 if(*(unsigned*)((char*)this+0x20)){loadAuxImage();}
 else {
  const TextureTgaHeader *header=(const TextureTgaHeader*)m_source;
  if(m_imageMode==2 && header->type==2 && header->id==0 && header->colorMap==0 && (header->bits==24||header->bits==32) && header->width%4==0 && !(header->flags&0xf0)){
   int format=header->bits==24?22:21;
   if(D3DXCheckTextureRequirements(DX8Wrapper::D3DDevice,&m_width,&m_height,0,0,&format,1)>=0 && m_width==(int)header->width && m_height==(int)header->height && format==(header->bits==24?22:21)) {
    if(D3DXCreateTexture(DX8Wrapper::D3DDevice,header->width,header->height,m_mipLevels,0,format,1,&texture)>=0) {
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
     goto finish;
    }
    texture=0;
   }
  }
  {
   int skip=0;
   if(m_imageMode==4){
    int ratio=m_sliceWidth/m_width;
    if(ratio>1 && m_width*ratio==m_sliceWidth && m_height*ratio==m_sliceHeight){
     while(!(ratio&1)){ratio>>=1;++skip;if(ratio<=1)break;}
     if(ratio!=1)skip=0;
    }
   }
   if(D3DXCreateTextureFromFileInMemoryEx(DX8Wrapper::D3DDevice,m_source,m_size,m_width,m_height,m_mipLevels,0,m_format,1,-1,((skip&31)<<26)|5,0,0,0,&texture)<0)texture=0;
  }
 }
 finish:
 if(texture){TextureSurfaceDesc desc;texture->GetLevelDesc(0,&desc);m_format=desc.format;texture->QueryInterface(TextureBaseInterfaceID,&m_resource);texture->Release();texture=0;}
}
