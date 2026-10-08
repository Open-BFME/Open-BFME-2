// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// WB b16130 names FXParticleSystem::ParticleSystemManager::GetShaderSetup;
// retail boundary 1F47F8..1F4882 (138B) preserves its lazy creation and holder return.
// Target accesses prove m_particleShader at +80 and referent count at +4.
// RefCountPtr copy/release follow the existing shader factory's holder semantics;
// WB documents IsBound and the exact shader/technique literals. BFME1's clean
// particle sources do not contain this GPU shader getter, so this body is
// reconstructed from WB control flow and independently byte-verified retail.
// The legacy Rva00072A94 assignment provider is a four-byte reference holder:
// factory callers and its own bytes prove the same Add_Ref/Release_Ref contract.
// WB b15e00 names GetVertexDeclaration; native 1F4002..1F40AF fixes its
// four D3D9 vertex elements and slot86 CreateVertexDeclaration. DX8Wrapper
// retains the original device-pointer name/type; retail uses its D3D9 ABI.
// Adjacent WB b15fe0 is unnamed. rva001F40AF keeps that uncertainty while
// recovering its proven quad-index construction: 0x800 quads, six indices
// per four vertices, buffer count0x3000 at member7C. Native1F40AF..1F416C.
// IndexBufferClass/WriteLock/DX8IndexBufferClass views reproduce the current
// provider ABI in dx8indexbuffer.cpp and reference/shims/indexbuffercount;
// the write lock includes its device-lock member and occupies 12 bytes.
#include <vector>
struct Rva0007BB16Record;
class RefCountClass {
public:
virtual void Delete_This();
 void Add_Ref(){++NumRefs;}void Release_Ref(){--NumRefs;if(!NumRefs)Delete_This();}private:int NumRefs;
};

class FXShaderSetup:public RefCountClass {};

template<class T> class RefCountPtr {
public:
RefCountPtr():m_ptr(0){}
 explicit RefCountPtr(T*p):m_ptr(p){}
 RefCountPtr(const RefCountPtr&o):m_ptr(o.m_ptr){if(m_ptr)m_ptr->Add_Ref();}
 ~RefCountPtr(){if(m_ptr)m_ptr->Release_Ref();}
 T*m_ptr;
};

class Rva00072A94 {
public:
Rva00072A94 &operator=(const Rva00072A94&);
};
RefCountPtr<FXShaderSetup> Rva00152C47_CreateFXShaderSetup(const char*,const char*,const _STL::vector<Rva0007BB16Record>*,int);
void BFME_DX8_Thread_Lock();
 bool BFME_DX8_Thread_Assert();
class BFMEDX8DeviceLock {
public:
BFMEDX8DeviceLock(){BFME_DX8_Thread_Lock();}
 ~BFMEDX8DeviceLock(){BFME_DX8_Thread_Assert();}};

class IndexBufferClass:public RefCountClass {
public:class WriteLockClass {IndexBufferClass *index_buffer;unsigned short *indices;BFMEDX8DeviceLock device_lock;
public:
WriteLockClass(IndexBufferClass*,int);
 ~WriteLockClass();unsigned short*Get_Index_Array(){return indices;}};
private:unsigned engine_refs,index_count,type;
};

class DX8IndexBufferClass:public IndexBufferClass {
public:
enum UsageType{USAGE_DEFAULT=0,USAGE_DYNAMIC=1,USAGE_SOFTWAREPROCESSING=2,USAGE_NPATCHES=4};DX8IndexBufferClass(unsigned,UsageType);
private:
void *index_buffer;
};
struct IDirect3DDevice8;
struct IDirect3DVertexDeclaration9;
struct D3DVERTEXELEMENT9 {unsigned short Stream,Offset;unsigned char Type,Method,Usage,UsageIndex;
};
template<int N> class ParticleDeviceSlots:public ParticleDeviceSlots<N-1>{
public:
virtual long __stdcall gap(char(*)[N]);
};
template<> class ParticleDeviceSlots<0> {};

class ParticleDevice9:public ParticleDeviceSlots<86>{
public:
virtual long __stdcall CreateVertexDeclaration(const D3DVERTEXELEMENT9*,IDirect3DVertexDeclaration9**);
};

class DX8Wrapper {protected:static IDirect3DDevice8 *D3DDevice;
public:
static IDirect3DDevice8 *_Get_D3D_Device8(){return D3DDevice;}};
namespace FXParticleSystem {
class ParticleSystemManager {
public:
RefCountPtr<FXShaderSetup> GetShaderSetup();IDirect3DVertexDeclaration9 *GetVertexDeclaration();DX8IndexBufferClass *rva001F40AF();
private:
char opaque00[0x78];IDirect3DVertexDeclaration9 *m_vertexDeclaration;DX8IndexBufferClass *m_indexBuffer;RefCountPtr<FXShaderSetup> m_particleShader;
};
DX8IndexBufferClass *ParticleSystemManager::rva001F40AF(){
 if(!m_indexBuffer){
  BFMEDX8DeviceLock lock;
  m_indexBuffer=new DX8IndexBufferClass(0x3000,DX8IndexBufferClass::USAGE_DEFAULT);
  IndexBufferClass::WriteLockClass write(m_indexBuffer,0);
  unsigned short *indices=write.Get_Index_Array();
  for(int i=0;i<0x800;++i){
   unsigned short first=(unsigned short)(i*4);
   indices[0]=first;
   indices[1]=first+1;
   indices[2]=first+2;
   indices[3]=first;
   indices[4]=first+2;
   indices[5]=first+3;
   if(i<0x7ff)indices+=6;
  }
 }
 return m_indexBuffer;
}
IDirect3DVertexDeclaration9 *ParticleSystemManager::GetVertexDeclaration(){
 if(!m_vertexDeclaration){
  BFMEDX8DeviceLock lock;
  D3DVERTEXELEMENT9 elements[]={
   {0,0,3,0,0,0},
   {0,16,3,0,5,0},
   {0,32,1,0,5,1},
   {255,0,17,0,0,0}
  };
  reinterpret_cast<ParticleDevice9*>(DX8Wrapper::_Get_D3D_Device8())->CreateVertexDeclaration(elements,&m_vertexDeclaration);
 }
 return m_vertexDeclaration;
}
RefCountPtr<FXShaderSetup> ParticleSystemManager::GetShaderSetup(){
 if(!m_particleShader.m_ptr){
  BFMEDX8DeviceLock lock;
  *reinterpret_cast<Rva00072A94*>(&m_particleShader)=reinterpret_cast<const Rva00072A94&>(Rva00152C47_CreateFXShaderSetup("gpuparticle.fx","Default",0,4));
 }
 return m_particleShader;
}
}
