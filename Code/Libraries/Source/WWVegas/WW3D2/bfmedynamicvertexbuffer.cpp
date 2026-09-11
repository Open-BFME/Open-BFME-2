// cl: /arch:SSE /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep
// Copyright 2025 Electronic Arts Inc.
// SPDX-License-Identifier: GPL-3.0-or-later
// Reconstructed from BFME2 and the GPL-3.0-or-later EA reference
// Code/Libraries/Source/WWVegas/WW3D2/dx8vertexbuffer.cpp.
// Recovered role names and independent identities: docs/reconstruction/dynamic-vertex-buffer.md.
#include <d3d8.h>
#include <string.h>
typedef unsigned long ULONG;
typedef void *HANDLE;
void *__cdecl operator new(unsigned);
// throw() as <new> declares them: otherwise every buffer destructor that
// frees something grows an unwind frame for its base, which retail's have not.
void __cdecl operator delete(void *) throw();
void __cdecl operator delete[](void *) throw();
// Without this declaration MSVC routes `new T[n]` to the SCALAR ??2@YAPAXI@Z
// (0x0002FDA0); retail's sorting constructor calls the array form ??_U@YAPAXI@Z
// at 0x0002FDE0, and those are two byte-verified distinct bodies here.
void *__cdecl operator new[](unsigned);
// The 96-byte vertex-format records of the fifteen dynamic pools, a table at
// 0x00DF2AA0.  Only their FVF prefix (BfmeDynamicFVFPrefix) is examined here.
struct BfmeFVFDescriptor {
 BfmeFVFDescriptor(unsigned fvf,unsigned fvf_size,bool additional_basis,unsigned extension_count);
 unsigned char record[0x60];
};
extern BfmeFVFDescriptor bfmeDynamicFVFDescriptors[15];
struct BfmeDynamicFVFPrefix {
 unsigned fvf;bool additionalBasis;unsigned extensionCount,stride;
 unsigned Get_FVF() const { return fvf; }
 unsigned Get_FVF_Size() const { return stride; }
};
struct BfmeDynamicCapsPrefix {
 unsigned maxDisplayWidth,maxDisplayHeight;
 // Actual 304-byte D3D9 caps aggregate; its internal fields are not accessed.
 unsigned char d3dCaps[304];
 bool supportTnL,supportDXTC,supportGamma,supportNPatches;
};
extern BfmeDynamicCapsPrefix *bfmeDynamicCaps;
class BfmeDynamicVBRefCount {
public:
 BfmeDynamicVBRefCount():references(1) {}
 virtual void DeleteThis();
 // RefCountClass's destructor: the base constructor's unwind state 0 is this
 // subobject, finished before the vtable store, and every buffer destructor
 // ends by restoring this class's vtable (0x00BC650C).
 virtual ~BfmeDynamicVBRefCount() {}
 int references;
 void AddRef() { ++references; }
 void ReleaseRef() { --references; if(references==0) DeleteThis(); }
};
class BfmeDynamicVBBase:public BfmeDynamicVBRefCount {
public:
 // Retail's shared base constructor lives at 0x00139350 and both derived
 // constructors below reach it through a REL32; it is defined after them so
 // they cannot inline it. Argument order is read out of the two call sites,
 // not assumed -- the sorting buffer passes (1,0x252,count,0) and the native
 // one (0,fvf,count,fvf_size).
 BfmeDynamicVBBase(unsigned,unsigned,unsigned short,unsigned);
 // Declared after DeleteThis so it takes vtable slot 1 and leaves slot 0 where
 // the already-matched bodies in this unit call it. Its presence is what gives
 // both constructors below retail's unwind frame: with no destructible base
 // there is nothing to unwind and MSVC emits no frame at all.
 virtual ~BfmeDynamicVBBase();
 unsigned type;
 unsigned short vertexCount;
 int engineReferences;
 BfmeFVFDescriptor *format;
 bool usesDeclaration;
 const BfmeDynamicFVFPrefix &FVF_Info() const { return *reinterpret_cast<BfmeDynamicFVFPrefix *>(format); }
};
struct BfmeDynamicVertexBuffer9;
class Vector2;
class Vector3;
class Vector4;
class BfmeDynamicNativeVB:public BfmeDynamicVBBase {
public:
 void *buffer;
 BfmeDynamicNativeVB(unsigned,unsigned short,unsigned,unsigned);
 // Zero Hour's array-taking DX8VertexBufferClass constructors, one per FVF.
 BfmeDynamicNativeVB(const Vector3 *,const Vector3 *,const Vector2 *,unsigned short,unsigned);
 BfmeDynamicNativeVB(const Vector3 *,const Vector3 *,const Vector4 *,const Vector2 *,unsigned short,unsigned);
 BfmeDynamicNativeVB(const Vector3 *,const Vector4 *,const Vector2 *,unsigned short,unsigned);
 BfmeDynamicNativeVB(const Vector3 *,const Vector2 *,unsigned short,unsigned);
 virtual ~BfmeDynamicNativeVB();
 void Create(unsigned);
 void Copy(const Vector3 *,const Vector3 *,const Vector2 *,unsigned,unsigned);
 void Copy(const Vector3 *,const Vector3 *,const Vector2 *,const Vector4 *,unsigned,unsigned);
 void Copy(const Vector3 *,const Vector2 *,const Vector4 *,unsigned,unsigned);
 void Copy(const Vector3 *,const Vector2 *,unsigned,unsigned);
 BfmeDynamicVertexBuffer9 *Get_DX8_Vertex_Buffer() const { return reinterpret_cast<BfmeDynamicVertexBuffer9 *>(buffer); }
};
class BfmeDynamicSortingVB:public BfmeDynamicVBBase {
public:
 void *buffer;
 BfmeDynamicSortingVB(unsigned short);
 virtual ~BfmeDynamicSortingVB();
};
typedef char BfmeDynamicVBBaseSize[(sizeof(BfmeDynamicVBBase)==28)?1:-1];
typedef char BfmeDynamicNativeVBSize[(sizeof(BfmeDynamicNativeVB)==32)?1:-1];
extern bool bfmeDynamicVBInUse[15];
extern BfmeDynamicNativeVB *bfmeDynamicVBs[15];
extern unsigned short bfmeDynamicVBSizes[15],bfmeDynamicVBOffsets[15];
extern unsigned bfmeDynamicFVFs[15];
static bool bfmeSortingVBInUse;
static BfmeDynamicSortingVB *bfmeSortingVB;
static unsigned short bfmeSortingVBSize,bfmeSortingVBOffset;
extern void BFME_DX8_Thread_Lock();
extern void BFME_DX8_Thread_Assert();
class BFMEDX8DeviceLock {
public:
 BFMEDX8DeviceLock() { BFME_DX8_Thread_Lock(); }
 ~BFMEDX8DeviceLock() { BFME_DX8_Thread_Assert(); }
};
struct BfmeSortingVertex { float x,y,z,nx,ny,nz;unsigned diffuse;float u1,v1,u2,v2; };
struct BfmeDynamicVBAccess {
 const BfmeFVFDescriptor *format;
 unsigned type,formatIndex,declaration;
 unsigned short vertexCount,vertexOffset;
 BfmeDynamicVBBase *buffer;
 BfmeDynamicVBAccess(unsigned type,unsigned format_index,unsigned short vertex_count,unsigned declaration);
 void AllocateNative();
 void AllocateSorting();
 static void _Reset(bool frame_changed);
 unsigned Get_Type() const { return type; }
 unsigned short Get_Vertex_Count() const { return vertexCount; }
 struct WriteLock {
  BfmeDynamicVBAccess *owner;
  BfmeSortingVertex *data;
  BFMEDX8DeviceLock guard;
  WriteLock(BfmeDynamicVBAccess *);
  ~WriteLock();
 };
};
// Type 2 draws from the per-format native pools; anything else shares the
// single sorting buffer.  The vertex offset is left for the allocator to set.
BfmeDynamicVBAccess::BfmeDynamicVBAccess(unsigned type,unsigned format_index,unsigned short vertex_count,unsigned declaration)
 : format(&bfmeDynamicFVFDescriptors[format_index]),type(type),formatIndex(format_index),declaration(declaration),vertexCount(vertex_count),buffer(0)
{
 if(type==2) AllocateNative();
 else AllocateSorting();
}
void BfmeDynamicVBAccess::AllocateNative()
{
 bfmeDynamicVBInUse[formatIndex]=true;
 if(vertexCount>bfmeDynamicVBSizes[formatIndex]) {
  if(bfmeDynamicVBs[formatIndex]) {
   bfmeDynamicVBs[formatIndex]->ReleaseRef();
   bfmeDynamicVBs[formatIndex]=0;
  }
  bfmeDynamicVBSizes[formatIndex]=vertexCount;
  if(bfmeDynamicVBSizes[formatIndex]<5000) bfmeDynamicVBSizes[formatIndex]=5000;
 }
 if(!bfmeDynamicVBs[formatIndex]) {
  unsigned usage=1;
  if(bfmeDynamicCaps->supportNPatches) usage|=4;
  bfmeDynamicVBs[formatIndex]=new BfmeDynamicNativeVB(bfmeDynamicFVFs[formatIndex],bfmeDynamicVBSizes[formatIndex],usage,0);
  bfmeDynamicVBOffsets[formatIndex]=0;
 }
 bfmeDynamicVBs[formatIndex]->usesDeclaration=declaration!=0;
 if((unsigned(vertexCount)+bfmeDynamicVBOffsets[formatIndex])>bfmeDynamicVBSizes[formatIndex]) bfmeDynamicVBOffsets[formatIndex]=0;
 if(bfmeDynamicVBs[formatIndex]) bfmeDynamicVBs[formatIndex]->AddRef();
 if(buffer) buffer->ReleaseRef();
 buffer=bfmeDynamicVBs[formatIndex];
 vertexOffset=bfmeDynamicVBOffsets[formatIndex];
}
void BfmeDynamicVBAccess::AllocateSorting()
{
 bfmeSortingVBInUse=true;
 unsigned newCount=bfmeSortingVBOffset+vertexCount;
 if(newCount>bfmeSortingVBSize) {
  if(bfmeSortingVB) { bfmeSortingVB->ReleaseRef();bfmeSortingVB=0; }
  bfmeSortingVBSize=newCount;
  if(bfmeSortingVBSize<5000) bfmeSortingVBSize=5000;
 }
 if(!bfmeSortingVB) {
  bfmeSortingVB=new BfmeDynamicSortingVB(bfmeSortingVBSize);
  bfmeSortingVBOffset=0;
 }
 if(bfmeSortingVB) bfmeSortingVB->AddRef();
 if(buffer) buffer->ReleaseRef();
 buffer=bfmeSortingVB;
 vertexOffset=bfmeSortingVBOffset;
}
// Zero Hour's DynamicVBAccessClass::_Reset with BFME's fifteen native pools:
// the sorting offset always rewinds, the per-format offsets only on a new
// frame -- one 30-byte clear, seven dword stores and a word.
void BfmeDynamicVBAccess::_Reset(bool frame_changed)
{
 bfmeSortingVBOffset=0;
 if(frame_changed) memset(bfmeDynamicVBOffsets,0,sizeof(bfmeDynamicVBOffsets));
}

// Retail multiplies the vertex count by 44 with a lea/add/sub chain rather than
// an imul, which is what sizeof(BfmeSortingVertex) already forces here, and
// reaches the ARRAY operator new at 0x0002FDE0 (??_U), not the scalar one.
BfmeDynamicSortingVB::BfmeDynamicSortingVB(unsigned short count)
 :BfmeDynamicVBBase(1,0x252,count,0)
{
 buffer=new BfmeSortingVertex[count];
}

BfmeDynamicNativeVB::BfmeDynamicNativeVB(unsigned fvf,unsigned short count,unsigned usage,unsigned fvfSize)
 :BfmeDynamicVBBase(0,fvf,count,fvfSize)
{
 buffer=0;
 Create(usage);
}

BfmeDynamicNativeVB::BfmeDynamicNativeVB(const Vector3 *vertices,const Vector3 *normals,const Vector2 *tex_coords,unsigned short count,unsigned usage)
 :BfmeDynamicVBBase(0,D3DFVF_XYZ|D3DFVF_TEX1|D3DFVF_NORMAL,count,0)
{
 buffer=0;
 Create(usage);
 Copy(vertices,normals,tex_coords,0,count);
}

BfmeDynamicNativeVB::BfmeDynamicNativeVB(const Vector3 *vertices,const Vector3 *normals,const Vector4 *diffuse,const Vector2 *tex_coords,unsigned short count,unsigned usage)
 :BfmeDynamicVBBase(0,D3DFVF_XYZ|D3DFVF_TEX1|D3DFVF_NORMAL|D3DFVF_DIFFUSE,count,0)
{
 buffer=0;
 Create(usage);
 Copy(vertices,normals,tex_coords,diffuse,0,count);
}

BfmeDynamicNativeVB::BfmeDynamicNativeVB(const Vector3 *vertices,const Vector4 *diffuse,const Vector2 *tex_coords,unsigned short count,unsigned usage)
 :BfmeDynamicVBBase(0,D3DFVF_XYZ|D3DFVF_TEX1|D3DFVF_DIFFUSE,count,0)
{
 buffer=0;
 Create(usage);
 Copy(vertices,tex_coords,diffuse,0,count);
}

BfmeDynamicNativeVB::BfmeDynamicNativeVB(const Vector3 *vertices,const Vector2 *tex_coords,unsigned short count,unsigned usage)
 :BfmeDynamicVBBase(0,D3DFVF_XYZ|D3DFVF_TEX1,count,0)
{
 buffer=0;
 Create(usage);
 Copy(vertices,tex_coords,0,count);
}

// dx8vertexbuffer.cpp's statistics: buffer count at 0x00DF2A40, total vertices
// at 0x00DF2A84 and total bytes at 0x00DF2A00.  Static as upstream: with their
// addresses never taken the compiler knows the adds cannot alias the object,
// which is why retail loads the vertex count once for both totals.
static int _VertexBufferCount,_VertexBufferTotalVertices,_VertexBufferTotalSize;
// Zero Hour's VertexBufferClass constructor, with the FVF record grown to BFME's
// four-argument form and the declaration flag set from the explicit size.
BfmeDynamicVBBase::BfmeDynamicVBBase(unsigned type_,unsigned fvf,unsigned short vertex_count,unsigned vertex_size)
 :type(type_),vertexCount(vertex_count),engineReferences(0),usesDeclaration(false)
{
 BfmeFVFDescriptor *descriptor=new BfmeFVFDescriptor(fvf,vertex_size,false,0);
 usesDeclaration=vertex_size!=0;
 _VertexBufferCount++;
 _VertexBufferTotalVertices+=vertexCount;
 format=descriptor;
 _VertexBufferTotalSize+=vertexCount*FVF_Info().Get_FVF_Size();
}

/*
 * Copyright (C) 2002-2003 Jason Edmeades
 *                         Raphael Junqueira
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */

// Device9 method prefix through CreateVertexBuffer, in Wine/SDK order.
// https://github.com/wine-mirror/wine/blob/master/include/d3d9.h
struct IDirect3D9;
struct D3DCAPS9;
struct IDirect3DSurface9;
struct IDirect3DSwapChain9;
struct IDirect3DTexture9;
struct IDirect3DVolumeTexture9;
struct IDirect3DCubeTexture9;
struct IDirect3DVertexBuffer9;
struct IDirect3DIndexBuffer9;
struct IDirect3DBaseTexture9;
struct D3DVIEWPORT9;
struct D3DMATERIAL9;
struct D3DLIGHT9;
struct IDirect3DStateBlock9;
struct D3DCLIPSTATUS9;
typedef DWORD D3DTEXTUREFILTERTYPE;
typedef DWORD D3DBACKBUFFER_TYPE;
typedef DWORD D3DMULTISAMPLE_TYPE;
typedef DWORD D3DSTATEBLOCKTYPE;
typedef DWORD D3DSAMPLERSTATETYPE;
struct RGNDATA;
struct BfmeDynamicDevice9 {
    virtual HRESULT __stdcall QueryInterface(REFIID riid, void** ppvObject) = 0;
    virtual ULONG __stdcall AddRef() = 0;
    virtual ULONG __stdcall Release() = 0;
    virtual HRESULT __stdcall TestCooperativeLevel() = 0;
    virtual UINT __stdcall GetAvailableTextureMem() = 0;
    virtual HRESULT __stdcall EvictManagedResources() = 0;
    virtual HRESULT __stdcall GetDirect3D(IDirect3D9** ppD3D9) = 0;
    virtual HRESULT __stdcall GetDeviceCaps(D3DCAPS9* pCaps) = 0;
    virtual HRESULT __stdcall GetDisplayMode(UINT iSwapChain, D3DDISPLAYMODE* pMode) = 0;
    virtual HRESULT __stdcall GetCreationParameters(D3DDEVICE_CREATION_PARAMETERS *pParameters) = 0;
    virtual HRESULT __stdcall SetCursorProperties(UINT XHotSpot, UINT YHotSpot, IDirect3DSurface9* pCursorBitmap) = 0;
    virtual void __stdcall SetCursorPosition(int X,int Y, DWORD Flags) = 0;
    virtual BOOL __stdcall ShowCursor(BOOL bShow) = 0;
    virtual HRESULT __stdcall CreateAdditionalSwapChain(D3DPRESENT_PARAMETERS* pPresentationParameters, IDirect3DSwapChain9** pSwapChain) = 0;
    virtual HRESULT __stdcall GetSwapChain(UINT iSwapChain, IDirect3DSwapChain9** pSwapChain) = 0;
    virtual UINT __stdcall GetNumberOfSwapChains() = 0;
    virtual HRESULT __stdcall Reset(D3DPRESENT_PARAMETERS* pPresentationParameters) = 0;
    virtual HRESULT __stdcall Present(const RECT *src_rect, const RECT *dst_rect, HWND dst_window_override, const RGNDATA *dirty_region) = 0;
    virtual HRESULT __stdcall GetBackBuffer(UINT iSwapChain, UINT iBackBuffer, D3DBACKBUFFER_TYPE Type, IDirect3DSurface9** ppBackBuffer) = 0;
    virtual HRESULT __stdcall GetRasterStatus(UINT iSwapChain, D3DRASTER_STATUS* pRasterStatus) = 0;
    virtual HRESULT __stdcall SetDialogBoxMode(BOOL bEnableDialogs) = 0;
    virtual void __stdcall SetGammaRamp(UINT swapchain_idx, DWORD flags, const D3DGAMMARAMP *ramp) = 0;
    virtual void __stdcall GetGammaRamp(UINT iSwapChain, D3DGAMMARAMP* pRamp) = 0;
    virtual HRESULT __stdcall CreateTexture(UINT Width, UINT Height, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DTexture9** ppTexture, HANDLE* pSharedHandle) = 0;
    virtual HRESULT __stdcall CreateVolumeTexture(UINT Width, UINT Height, UINT Depth, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DVolumeTexture9** ppVolumeTexture, HANDLE* pSharedHandle) = 0;
    virtual HRESULT __stdcall CreateCubeTexture(UINT EdgeLength, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DCubeTexture9** ppCubeTexture, HANDLE* pSharedHandle) = 0;
    virtual HRESULT __stdcall CreateVertexBuffer(UINT Length, DWORD Usage, DWORD FVF, D3DPOOL Pool, IDirect3DVertexBuffer9** ppVertexBuffer, HANDLE* pSharedHandle) = 0;
};

extern BfmeDynamicDevice9 *bfmeDynamicDevice;
inline BfmeDynamicDevice9 *bfmeGetDynamicDevice() { return bfmeDynamicDevice; }

class WW3D { public:static void _Invalidate_Mesh_Cache(); };
__declspec(noinline) void bfmeEvictManagedResources();
extern void Log_DX8_ErrorCode(unsigned);
void BfmeDynamicNativeVB::Create(unsigned usage)
{
 BFMEDX8DeviceLock lock;
 unsigned flags=D3DUSAGE_WRITEONLY|
  ((usage&1)?D3DUSAGE_DYNAMIC:0)|
  ((usage&4)?D3DUSAGE_NPATCHES:0)|
  ((usage&2)?D3DUSAGE_SOFTWAREPROCESSING:0);
 if(!bfmeDynamicCaps->supportTnL) flags|=D3DUSAGE_SOFTWAREPROCESSING;
 if(!bfmeDynamicCaps->supportTnL) flags|=D3DUSAGE_SOFTWAREPROCESSING;
 HRESULT result=bfmeGetDynamicDevice()->CreateVertexBuffer(
  FVF_Info().Get_FVF_Size()*vertexCount,flags,
  FVF_Info().Get_FVF(),
  (usage&1)?D3DPOOL_DEFAULT:D3DPOOL_MANAGED,
  reinterpret_cast<IDirect3DVertexBuffer9 **>(&buffer),0);
 if(SUCCEEDED(result)) return;
 WW3D::_Invalidate_Mesh_Cache();
 bfmeEvictManagedResources();
 result=bfmeGetDynamicDevice()->CreateVertexBuffer(
  FVF_Info().Get_FVF_Size()*vertexCount,flags,
  FVF_Info().Get_FVF(),
  (usage&1)?D3DPOOL_DEFAULT:D3DPOOL_MANAGED,
  reinterpret_cast<IDirect3DVertexBuffer9 **>(&buffer),0);
 if(result!=0) Log_DX8_ErrorCode(result);
}

extern unsigned number_of_DX8_calls;
void bfmeEvictManagedResources()
{
 bfmeGetDynamicDevice()->EvictManagedResources();
 number_of_DX8_calls++;
}

// VertexBuffer9 method order from the same Wine d3d9.h source credited above.
struct IDirect3DDevice9;
struct D3DVERTEXBUFFER_DESC;
struct BfmeDynamicVertexBuffer9 {
 virtual HRESULT __stdcall QueryInterface(REFIID,void**)=0;
 virtual ULONG __stdcall AddRef()=0;
 virtual ULONG __stdcall Release()=0;
 virtual HRESULT __stdcall GetDevice(IDirect3DDevice9**)=0;
 virtual HRESULT __stdcall SetPrivateData(REFIID,const void*,DWORD,DWORD)=0;
 virtual HRESULT __stdcall GetPrivateData(REFIID,void*,DWORD*)=0;
 virtual HRESULT __stdcall FreePrivateData(REFIID)=0;
 virtual DWORD __stdcall SetPriority(DWORD)=0;
 virtual DWORD __stdcall GetPriority()=0;
 virtual void __stdcall PreLoad()=0;
 virtual D3DRESOURCETYPE __stdcall GetType()=0;
 virtual HRESULT __stdcall Lock(UINT,UINT,void**,DWORD)=0;
 virtual HRESULT __stdcall Unlock()=0;
 virtual HRESULT __stdcall GetDesc(D3DVERTEXBUFFER_DESC*)=0;
};

// Zero Hour's VertexBufferClass destructor: the statistics come back out and
// the FVF record is freed.  Both derived destructors below inline it.
BfmeDynamicVBBase::~BfmeDynamicVBBase()
{
 _VertexBufferCount--;
 _VertexBufferTotalVertices-=vertexCount;
 _VertexBufferTotalSize-=vertexCount*FVF_Info().Get_FVF_Size();
 delete format;
}

BfmeDynamicSortingVB::~BfmeDynamicSortingVB()
{
 delete[] static_cast<BfmeSortingVertex *>(buffer);
}

// BFME releases the D3D buffer under its device mutex; the guard's unwind
// state sits inside the one the base subobject opens.
BfmeDynamicNativeVB::~BfmeDynamicNativeVB()
{
 BFMEDX8DeviceLock guard;
 Get_DX8_Vertex_Buffer()->Release();
}
extern void DX8_Assert();
BfmeDynamicVBAccess::WriteLock::WriteLock(BfmeDynamicVBAccess *access):owner(access),data(0)
{
 switch(owner->Get_Type()) {
 case 2: {
  DX8_Assert();
  HRESULT result=static_cast<BfmeDynamicNativeVB *>(owner->buffer)->Get_DX8_Vertex_Buffer()->Lock(
   owner->vertexOffset*owner->buffer->FVF_Info().Get_FVF_Size(),
   owner->Get_Vertex_Count()*owner->buffer->FVF_Info().Get_FVF_Size(),
   reinterpret_cast<void **>(&data),
   D3DLOCK_NOSYSLOCK|(!owner->vertexOffset?D3DLOCK_DISCARD:D3DLOCK_NOOVERWRITE));
  if(result!=0) Log_DX8_ErrorCode(result);
  break;
 }
 case 3:
  data=reinterpret_cast<BfmeSortingVertex *>(static_cast<BfmeDynamicSortingVB *>(owner->buffer)->buffer);
  data+=owner->vertexOffset;
  break;
 default:break;
 }
}
BfmeDynamicVBAccess::WriteLock::~WriteLock()
{
 switch(owner->Get_Type()) {
 case 2: {
  DX8_Assert();
  HRESULT result=static_cast<BfmeDynamicNativeVB *>(owner->buffer)->Get_DX8_Vertex_Buffer()->Unlock();
  if(result!=0) Log_DX8_ErrorCode(result);
  break;
 }
 case 3:break;
 default:break;
 }
}

typedef char BfmeDynamicWriteLockSize[(sizeof(BfmeDynamicVBAccess::WriteLock)==12)?1:-1];
typedef char BfmeSortingVertexSize[(sizeof(BfmeSortingVertex)==44)?1:-1];
