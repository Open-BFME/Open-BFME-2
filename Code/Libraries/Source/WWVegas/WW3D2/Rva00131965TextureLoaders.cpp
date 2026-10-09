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
 virtual void slot3()=0;virtual void slot4()=0;virtual void slot5()=0;virtual void slot6()=0;virtual void slot7()=0;virtual void slot8()=0;virtual void slot9()=0;virtual void slot10()=0;virtual void slot11()=0;virtual void slot12()=0;virtual void slot13()=0;virtual void slot14()=0;virtual void slot15()=0;virtual void slot16()=0;
 virtual long __stdcall GetLevelDesc(unsigned,void*)=0;
 virtual long __stdcall GetVolumeLevel(unsigned,VolumeCOM9**)=0;
};
extern "C" long __stdcall D3DXCreateVolumeTextureFromFileInMemoryEx(void*,const void*,unsigned,unsigned,unsigned,unsigned,unsigned,unsigned,int,int,unsigned,unsigned,unsigned,void*,void*,TextureCOM9**);
extern "C" long __stdcall D3DXCreateCubeTextureFromFileInMemoryEx(void*,const void*,unsigned,unsigned,unsigned,unsigned,int,int,unsigned,unsigned,unsigned,void*,void*,TextureCOM9**);
class Rva0013107A {
public:
 void loadVolume();void loadCube();void loadVolumeSlices();
private:
 char head[8];void*m_resource;char gap[8];const void*m_source;unsigned m_size;char gap1[0xc];unsigned m_width,m_height,m_depth,m_sliceWidth,m_sliceHeight;char gap2[8];unsigned m_mipLevels;char gap3[4];int m_format;
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
