// cl: /arch:SSE /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep
// Copyright 2025 Electronic Arts Inc.
// SPDX-License-Identifier: GPL-3.0-or-later
// Reconstructed from BFME2 and the GPL-3.0-or-later EA reference
// Code/Libraries/Source/WWVegas/WW3D2/dx8vertexbuffer.cpp.
// Recovered role names and independent identities: docs/reconstruction/dynamic-vertex-buffer.md.
#include <d3d8.h>
typedef unsigned long ULONG;
typedef void *HANDLE;
void *__cdecl operator new(unsigned);
void __cdecl operator delete(void *);
struct BfmeFVFDescriptor;
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
 virtual void DeleteThis();
 int references;
 void AddRef() { ++references; }
 void ReleaseRef() { --references; if(references==0) DeleteThis(); }
};
class BfmeDynamicVBBase:public BfmeDynamicVBRefCount {
public:
 unsigned type;
 unsigned short vertexCount;
 int engineReferences;
 BfmeFVFDescriptor *format;
 bool usesDeclaration;
 const BfmeDynamicFVFPrefix &FVF_Info() const { return *reinterpret_cast<BfmeDynamicFVFPrefix *>(format); }
};
class BfmeDynamicNativeVB:public BfmeDynamicVBBase {
public:
 void *buffer;
 BfmeDynamicNativeVB(unsigned,unsigned short,unsigned,unsigned);
 void Create(unsigned);
};
class BfmeDynamicSortingVB:public BfmeDynamicVBBase {
public:
 void *buffer;
 BfmeDynamicSortingVB(unsigned short);
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
struct BfmeDynamicVBAccess {
 const BfmeFVFDescriptor *format;
 unsigned type,formatIndex,declaration;
 unsigned short vertexCount,vertexOffset;
 BfmeDynamicVBBase *buffer;
 void AllocateNative();
 void AllocateSorting();
};
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

extern void BFME_DX8_Thread_Lock();
extern void BFME_DX8_Thread_Assert();
class BFMEDX8DeviceLock {
public:
 BFMEDX8DeviceLock() { BFME_DX8_Thread_Lock(); }
 ~BFMEDX8DeviceLock() { BFME_DX8_Thread_Assert(); }
};
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
