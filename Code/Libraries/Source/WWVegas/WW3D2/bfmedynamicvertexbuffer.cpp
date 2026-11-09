// dxsdk
// platformsdk
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil
// Copyright 2025 Electronic Arts Inc.
// SPDX-License-Identifier: GPL-3.0-or-later
// Reconstructed from BFME2 and the GPL-3.0-or-later EA reference
// Code/Libraries/Source/WWVegas/WW3D2/dx8vertexbuffer.cpp.
// Recovered role names and independent identities: docs/reconstruction/dynamic-vertex-buffer.md.
extern class MeshModelClass *MeshModelListHead;

#include <d3d9.h>
#include <new>
#include <string.h>
// The 96-byte vertex-format records of the fifteen dynamic pools, a table at
// 0x00DF2AA0.  Only their FVF prefix (BfmeDynamicFVFPrefix) is examined here.
struct BfmeFVFDescriptor {
 BfmeFVFDescriptor(unsigned fvf,unsigned fvf_size,bool additional_basis,unsigned extension_count);
 unsigned char record[0x60];
};
extern BfmeFVFDescriptor bfmeDynamicFVFDescs[15];
#define bfmeDynamicFVFDescriptors bfmeDynamicFVFDescs
// ^ bfmeDynamicFVFDescriptors is only an alias of the owned global bfmeDynamicFVFDescs (ledger names column).
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
struct IDirect3DDevice8;
class DX8Caps;
class Vector3;
class Vector4;
struct DX8Wrapper {
 __declspec(dllimport) __forceinline static IDirect3DDevice8 *Get_D3D_Device() { return D3DDevice; }
 __declspec(dllimport) __forceinline static DX8Caps *Get_Current_Caps() { return CurrentCaps; }
 static __declspec(dllimport) __forceinline unsigned int Convert_Color(const Vector3 &color, float alpha);
 static __forceinline unsigned int Convert_Color(const Vector4 &color);
protected:
 static IDirect3DDevice8 *D3DDevice;
 static DX8Caps *CurrentCaps;
};
#define bfmeDynamicCaps ((BfmeDynamicCapsPrefix *)DX8Wrapper::Get_Current_Caps())
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
 void rva00139280(bool uses_declaration);
};
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
 void Copy(const Vector3 *,unsigned,unsigned);
 void Copy(const Vector3 *,const Vector3 *,unsigned,unsigned);
 IDirect3DVertexBuffer9 *Get_DX8_Vertex_Buffer() const { return reinterpret_cast<IDirect3DVertexBuffer9 *>(buffer); }
};
class BfmeDynamicSortingVB:public BfmeDynamicVBBase {
public:
 void *buffer;
 BfmeDynamicSortingVB(unsigned short);
 virtual ~BfmeDynamicSortingVB();
};
typedef char BfmeDynamicVBBaseSize[(sizeof(BfmeDynamicVBBase)==28)?1:-1];
typedef char BfmeDynamicNativeVBSize[(sizeof(BfmeDynamicNativeVB)==32)?1:-1];
extern bool BfmeDynamicDX8VertexBufferInUse[15];
#define bfmeDynamicVBInUse BfmeDynamicDX8VertexBufferInUse
// The pool slot is owned by DynamicVBAccessClassDeinit.cpp; cast only the access view.
class BfmeDynamicVB;
extern BfmeDynamicVB *bfmeDynamicVBs[15];
extern unsigned short bfmeDynamicVBSizes[15];
extern unsigned short BfmeDynamicDX8VertexBufferOffset[15];
#define bfmeDynamicVBOffsets BfmeDynamicDX8VertexBufferOffset
// bfmeDynamicFVFs: matched references place it at VA 0xbd2f04 (retail .rdata contents).
// Entry 10 is position, normal, diffuse and four texture coordinate sets, the
// last three of them three-component (D3DFVF_TEXCOORDSIZE3(1..3)).
#define BFME_D3DFVF_XYZ			0x002u
#define BFME_D3DFVF_NORMAL		0x010u
#define BFME_D3DFVF_DIFFUSE		0x040u
#define BFME_D3DFVF_TEX4		0x400u
#define BFME_D3DFVF_TEXCOORDSIZE3(i)	(1u << ((i) * 2 + 16))
unsigned bfmeDynamicFVFs[15] = {
	2u, 0x12u, 0x112u, 0x212u, 0x152u, 0x252u, 0x142u, 0x242u,
	0x102u, 0x202u,
	BFME_D3DFVF_XYZ | BFME_D3DFVF_NORMAL | BFME_D3DFVF_DIFFUSE | BFME_D3DFVF_TEX4 |
		BFME_D3DFVF_TEXCOORDSIZE3(1) | BFME_D3DFVF_TEXCOORDSIZE3(2) | BFME_D3DFVF_TEXCOORDSIZE3(3),
	0xb0312u, 0x52u, 0x344u, 0x444u,
};
// The sorting buffer's allocator and its statics are in dx8vertexbuffer.cpp, with _Deinit and the destructor.
extern void BFME_DX8_Thread_Lock();
extern bool BFME_DX8_Thread_Assert();
#include "../../../../GameEngineDevice/Include/W3DDevice/GameClient/BFMEDX8DeviceLock.h"
struct BfmeSortingVertex { float x,y,z,nx,ny,nz;unsigned diffuse;float u1,v1,u2,v2; };
class DynamicVBAccessClass
{
public:
 const BfmeFVFDescriptor *format;
 unsigned type,formatIndex,declaration;
 unsigned short vertexCount,vertexOffset;
 BfmeDynamicVBBase *buffer;
 DynamicVBAccessClass(unsigned type,unsigned format_index,unsigned short vertex_count,unsigned declaration);
 void Allocate_DX8_Dynamic_Buffer();
 void Allocate_Sorting_Dynamic_Buffer();
 static void _Reset(bool frame_changed);
 unsigned Get_Type() const { return type; }
 __declspec(dllimport) __forceinline unsigned short Get_Vertex_Count() const { return vertexCount; }
 struct WriteLock {
  DynamicVBAccessClass *owner;
  BfmeSortingVertex *data;
  BFMEDX8DeviceLock guard;
  WriteLock(DynamicVBAccessClass *);
  ~WriteLock();
 };
};
// Type 2 draws from the per-format native pools; anything else shares the
// single sorting buffer.  The vertex offset is left for the allocator to set.
DynamicVBAccessClass::DynamicVBAccessClass(unsigned type,unsigned format_index,unsigned short vertex_count,unsigned declaration)
 : format(&bfmeDynamicFVFDescriptors[format_index]),type(type),formatIndex(format_index),declaration(declaration),vertexCount(vertex_count),buffer(0)
{
 if(type==2) Allocate_DX8_Dynamic_Buffer();
 else Allocate_Sorting_Dynamic_Buffer();
}
void DynamicVBAccessClass::Allocate_DX8_Dynamic_Buffer()
{
 bfmeDynamicVBInUse[formatIndex]=true;
 if(vertexCount>bfmeDynamicVBSizes[formatIndex]) {
  if(bfmeDynamicVBs[formatIndex]) {
   ((BfmeDynamicNativeVB *)bfmeDynamicVBs[formatIndex])->ReleaseRef();
   bfmeDynamicVBs[formatIndex]=0;
  }
  bfmeDynamicVBSizes[formatIndex]=vertexCount;
  if(bfmeDynamicVBSizes[formatIndex]<5000) bfmeDynamicVBSizes[formatIndex]=5000;
 }
 if(!bfmeDynamicVBs[formatIndex]) {
  unsigned usage=1;
  if(bfmeDynamicCaps->supportNPatches) usage|=4;
  bfmeDynamicVBs[formatIndex]=(BfmeDynamicVB *)new BfmeDynamicNativeVB(bfmeDynamicFVFs[formatIndex],bfmeDynamicVBSizes[formatIndex],usage,0);
  bfmeDynamicVBOffsets[formatIndex]=0;
 }
 ((BfmeDynamicNativeVB *)bfmeDynamicVBs[formatIndex])->usesDeclaration=declaration!=0;
 if((unsigned(vertexCount)+bfmeDynamicVBOffsets[formatIndex])>bfmeDynamicVBSizes[formatIndex]) bfmeDynamicVBOffsets[formatIndex]=0;
 if(bfmeDynamicVBs[formatIndex]) ((BfmeDynamicNativeVB *)bfmeDynamicVBs[formatIndex])->AddRef();
 if(buffer) buffer->ReleaseRef();
 buffer=(BfmeDynamicNativeVB *)bfmeDynamicVBs[formatIndex];
 vertexOffset=bfmeDynamicVBOffsets[formatIndex];
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

inline IDirect3DDevice9 *bfmeGetDynamicDevice() { return (IDirect3DDevice9 *)DX8Wrapper::Get_D3D_Device(); }

#include "WW3DClass.h"
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
DynamicVBAccessClass::WriteLock::WriteLock(DynamicVBAccessClass *access):owner(access),data(0)
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
DynamicVBAccessClass::WriteLock::~WriteLock()
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

typedef char BfmeDynamicWriteLockSize[(sizeof(DynamicVBAccessClass::WriteLock)==12)?1:-1];
typedef char BfmeSortingVertexSize[(sizeof(BfmeSortingVertex)==44)?1:-1];

// Zero Hour's VertexBufferClass lock helpers, layout-identical to the matched
// VertexBufferLockClasses.cpp unit (buffer/kind/FVF record placement proven
// there); the vertex-array accessor rides along because Copy needs it.
#include "VertexBufferClass.h"

#include "../../../../../reference/shims/wwmath/Vector2.h"

class Vector3
{
public:
	float X;
	float Y;
	float Z;

	float &operator[](int i) { return (&X)[i]; }
	const float &operator[](int i) const { return (&X)[i]; }
};

#include "../WWMath/Vector4Data.h"

// upstream layout: dx8fvf.h VertexFormatXYZNDUV1 (36 bytes).
struct VertexFormatXYZNDUV1
{
	float x;
	float y;
	float z;
	float nx;
	float ny;
	float nz;
	unsigned diffuse;
	float u1;
	float v1;
};

// Zero Hour's float-to-ARGB pack, dx8wrapper.h: the Vector4 form forwards to
// the Vector3-plus-alpha form whose __asm body sets truncate rounding,
// scales by 255 and shifts the four bytes together. Force-inline here so no
// call survives: retail's Copy bodies inline it per vertex.
__declspec(dllimport) __forceinline unsigned int DX8Wrapper::Convert_Color(const Vector3 &color, float alpha)
	{
		const float scale = 255.0;
		// Retail zeroes this slot before the asm block writes it back, so the
		// upstream uninitialized declaration does not reproduce: keep the init.
		unsigned int col = 0;

		__asm
		{
			sub	esp,20

			fwait
			fstcw		[esp+16]
			mov		eax,[esp+16]
			mov		edi,eax
			and		eax,~(1024|2048)
			or			eax,(1024|2048)
			sub		edi,eax
			jz			skip
			mov		[esp],eax
			fldcw		[esp]
	skip:

			mov	esi,dword ptr color
			fld	dword ptr[scale]

			fld	dword ptr[esi]
			fld	dword ptr[esi+4]
			fld	dword ptr[esi+8]
			fld	dword ptr[alpha]
			fld	st(4)
			fmul	st(4),st
			fmul	st(3),st
			fmul	st(2),st
			fmulp	st(1),st
			fistp	dword ptr[esp+0]
			fistp	dword ptr[esp+4]
			fistp	dword ptr[esp+8]
			fistp	dword ptr[esp+12]
			mov	ecx,[esp]
			mov	eax,[esp+4]
			mov	edx,[esp+8]
			mov	ebx,[esp+12]
			shl	ecx,24
			shl	ebx,16
			shl	edx,8
			or		eax,ecx
			or		eax,ebx
			or		eax,edx

			fstp	st(0)

			cmp	edi,0
			je		not_changed
			fwait
			fldcw	[esp+16];
		not_changed:
			add	esp,20

			mov	col,eax
		}
		return col;
	}

	__forceinline unsigned int DX8Wrapper::Convert_Color(const Vector4 &color)
	{
		return Convert_Color(reinterpret_cast<const Vector3 &>(color), color[3]);
	}

// upstream layout: dx8fvf.h VertexFormatXYZDUV1 (24 bytes).
struct VertexFormatXYZDUV1
{
	float x;
	float y;
	float z;
	unsigned diffuse;
	float u1;
	float v1;
};

// Zero Hour's DX8VertexBufferClass::Copy for XYZDUV1, dx8vertexbuffer.cpp:
// same lock dance as the XYZNDUV1 form, fanning loc/uv/diffuse out.
void BfmeDynamicNativeVB::Copy(const Vector3 *loc, const Vector2 *uv, const Vector4 *diffuse, unsigned first_vertex, unsigned count)
{
	if (first_vertex) {
		VertexBufferClass::AppendLockClass l(reinterpret_cast<VertexBufferClass *>(this), first_vertex, count);
		VertexFormatXYZDUV1 *verts = (VertexFormatXYZDUV1 *)l.Get_Vertex_Array();
		for (unsigned v = 0; v < count; ++v) {
			verts[v].x = (*loc)[0];
			verts[v].y = (*loc)[1];
			verts[v].z = (*loc++)[2];
			verts[v].u1 = (*uv)[0];
			verts[v].v1 = (*uv++)[1];
			verts[v].diffuse = DX8Wrapper::Convert_Color(diffuse[v]);
		}
	}
	else {
		VertexBufferClass::WriteLockClass l(reinterpret_cast<VertexBufferClass *>(this));
		VertexFormatXYZDUV1 *verts = (VertexFormatXYZDUV1 *)l.Get_Vertex_Array();
		for (unsigned v = 0; v < count; ++v) {
			verts[v].x = (*loc)[0];
			verts[v].y = (*loc)[1];
			verts[v].z = (*loc++)[2];
			verts[v].u1 = (*uv)[0];
			verts[v].v1 = (*uv++)[1];
			verts[v].diffuse = DX8Wrapper::Convert_Color(diffuse[v]);
		}
	}
}
// upstream layout: dx8fvf.h VertexFormatXYZNUV1 (32 bytes).
struct VertexFormatXYZNUV1
{
	float x;
	float y;
	float z;
	float nx;
	float ny;
	float nz;
	float u1;
	float v1;
};

// upstream layout: dx8fvf.h VertexFormatXYZUV1 (20 bytes).
struct VertexFormatXYZUV1
{
	float x;
	float y;
	float z;
	float u1;
	float v1;
};

// Zero Hour's DX8VertexBufferClass::Copy for XYZNUV1, dx8vertexbuffer.cpp:
// same lock dance, no diffuse pack.
void BfmeDynamicNativeVB::Copy(const Vector3 *loc, const Vector3 *norm, const Vector2 *uv, unsigned first_vertex, unsigned count)
{
	if (first_vertex) {
		VertexBufferClass::AppendLockClass l(reinterpret_cast<VertexBufferClass *>(this), first_vertex, count);
		VertexFormatXYZNUV1 *verts = (VertexFormatXYZNUV1 *)l.Get_Vertex_Array();
		for (unsigned v = 0; v < count; ++v) {
			verts[v].x = (*loc)[0];
			verts[v].y = (*loc)[1];
			verts[v].z = (*loc++)[2];
			verts[v].nx = (*norm)[0];
			verts[v].ny = (*norm)[1];
			verts[v].nz = (*norm++)[2];
			verts[v].u1 = (*uv)[0];
			verts[v].v1 = (*uv++)[1];
		}
	}
	else {
		VertexBufferClass::WriteLockClass l(reinterpret_cast<VertexBufferClass *>(this));
		VertexFormatXYZNUV1 *verts = (VertexFormatXYZNUV1 *)l.Get_Vertex_Array();
		for (unsigned v = 0; v < count; ++v) {
			verts[v].x = (*loc)[0];
			verts[v].y = (*loc)[1];
			verts[v].z = (*loc++)[2];
			verts[v].nx = (*norm)[0];
			verts[v].ny = (*norm)[1];
			verts[v].nz = (*norm++)[2];
			verts[v].u1 = (*uv)[0];
			verts[v].v1 = (*uv++)[1];
		}
	}
}

// Zero Hour's DX8VertexBufferClass::Copy for XYZUV1, dx8vertexbuffer.cpp:
// same lock dance, positions and uvs only.
void BfmeDynamicNativeVB::Copy(const Vector3 *loc, const Vector2 *uv, unsigned first_vertex, unsigned count)
{
	if (first_vertex) {
		VertexBufferClass::AppendLockClass l(reinterpret_cast<VertexBufferClass *>(this), first_vertex, count);
		VertexFormatXYZUV1 *verts = (VertexFormatXYZUV1 *)l.Get_Vertex_Array();
		for (unsigned v = 0; v < count; ++v) {
			verts[v].x = (*loc)[0];
			verts[v].y = (*loc)[1];
			verts[v].z = (*loc++)[2];
			verts[v].u1 = (*uv)[0];
			verts[v].v1 = (*uv++)[1];
		}
	}
	else {
		VertexBufferClass::WriteLockClass l(reinterpret_cast<VertexBufferClass *>(this));
		VertexFormatXYZUV1 *verts = (VertexFormatXYZUV1 *)l.Get_Vertex_Array();
		for (unsigned v = 0; v < count; ++v) {
			verts[v].x = (*loc)[0];
			verts[v].y = (*loc)[1];
			verts[v].z = (*loc++)[2];
			verts[v].u1 = (*uv)[0];
			verts[v].v1 = (*uv++)[1];
		}
	}
}

// upstream layout: dx8fvf.h VertexFormatXYZ (12 bytes).
struct VertexFormatXYZ
{
	float x;
	float y;
	float z;
};

// upstream layout: dx8fvf.h VertexFormatXYZN (24 bytes).
struct VertexFormatXYZN
{
	float x;
	float y;
	float z;
	float nx;
	float ny;
	float nz;
};

// ?rva00139280@BfmeDynamicVBBase@@QAEX_N@Z, retail 0x00139280 (10B): the
// out-of-line setter of the uses-declaration flag at +0x18, in the int3-padded
// run directly ahead of Convert_Color 0x00139290. No direct caller reaches it
// in retail (the pool allocator stores the flag inline), so it keeps an
// address-derived name.
void BfmeDynamicVBBase::rva00139280(bool uses_declaration)
{
 usesDeclaration=uses_declaration;
}

// Zero Hour's DX8VertexBufferClass::Copy for XYZ, dx8vertexbuffer.cpp
// (retail 0x00139BF0, between the XYZNUV1 and XYZUV1 copies as upstream
// orders them): same lock dance, positions only.
void BfmeDynamicNativeVB::Copy(const Vector3 *loc, unsigned first_vertex, unsigned count)
{
	if (first_vertex) {
		VertexBufferClass::AppendLockClass l(reinterpret_cast<VertexBufferClass *>(this), first_vertex, count);
		VertexFormatXYZ *verts = (VertexFormatXYZ *)l.Get_Vertex_Array();
		for (unsigned v = 0; v < count; ++v) {
			verts[v].x = (*loc)[0];
			verts[v].y = (*loc)[1];
			verts[v].z = (*loc++)[2];
		}
	}
	else {
		VertexBufferClass::WriteLockClass l(reinterpret_cast<VertexBufferClass *>(this));
		VertexFormatXYZ *verts = (VertexFormatXYZ *)l.Get_Vertex_Array();
		for (unsigned v = 0; v < count; ++v) {
			verts[v].x = (*loc)[0];
			verts[v].y = (*loc)[1];
			verts[v].z = (*loc++)[2];
		}
	}
}

// Zero Hour's DX8VertexBufferClass::Copy for XYZN, dx8vertexbuffer.cpp
// (retail 0x00139FE0, after the XYZUV1 copy): positions and normals.
void BfmeDynamicNativeVB::Copy(const Vector3 *loc, const Vector3 *norm, unsigned first_vertex, unsigned count)
{
	if (first_vertex) {
		VertexBufferClass::AppendLockClass l(reinterpret_cast<VertexBufferClass *>(this), first_vertex, count);
		VertexFormatXYZN *verts = (VertexFormatXYZN *)l.Get_Vertex_Array();
		for (unsigned v = 0; v < count; ++v) {
			verts[v].x = (*loc)[0];
			verts[v].y = (*loc)[1];
			verts[v].z = (*loc++)[2];
			verts[v].nx = (*norm)[0];
			verts[v].ny = (*norm)[1];
			verts[v].nz = (*norm++)[2];
		}
	}
	else {
		VertexBufferClass::WriteLockClass l(reinterpret_cast<VertexBufferClass *>(this));
		VertexFormatXYZN *verts = (VertexFormatXYZN *)l.Get_Vertex_Array();
		for (unsigned v = 0; v < count; ++v) {
			verts[v].x = (*loc)[0];
			verts[v].y = (*loc)[1];
			verts[v].z = (*loc++)[2];
			verts[v].nx = (*norm)[0];
			verts[v].ny = (*norm)[1];
			verts[v].nz = (*norm++)[2];
		}
	}
}

// Zero Hour's DX8VertexBufferClass::Copy for XYZNDUV1, dx8vertexbuffer.cpp:
// lock the range (append when first_vertex is nonzero, full write otherwise)
// and fan the four arrays out, packing diffuse through Convert_Color.
void BfmeDynamicNativeVB::Copy(const Vector3 *loc, const Vector3 *norm, const Vector2 *uv, const Vector4 *diffuse, unsigned first_vertex, unsigned count)
{
	if (first_vertex) {
		VertexBufferClass::AppendLockClass l(reinterpret_cast<VertexBufferClass *>(this), first_vertex, count);
		VertexFormatXYZNDUV1 *verts = (VertexFormatXYZNDUV1 *)l.Get_Vertex_Array();
		for (unsigned v = 0; v < count; ++v) {
			verts[v].x = (*loc)[0];
			verts[v].y = (*loc)[1];
			verts[v].z = (*loc++)[2];
			verts[v].nx = (*norm)[0];
			verts[v].ny = (*norm)[1];
			verts[v].nz = (*norm++)[2];
			verts[v].u1 = (*uv)[0];
			verts[v].v1 = (*uv++)[1];
			verts[v].diffuse = DX8Wrapper::Convert_Color(diffuse[v]);
		}
	}
	else {
		VertexBufferClass::WriteLockClass l(reinterpret_cast<VertexBufferClass *>(this));
		VertexFormatXYZNDUV1 *verts = (VertexFormatXYZNDUV1 *)l.Get_Vertex_Array();
		for (unsigned v = 0; v < count; ++v) {
			verts[v].x = (*loc)[0];
			verts[v].y = (*loc)[1];
			verts[v].z = (*loc++)[2];
			verts[v].nx = (*norm)[0];
			verts[v].ny = (*norm)[1];
			verts[v].nz = (*norm++)[2];
			verts[v].u1 = (*uv)[0];
			verts[v].v1 = (*uv++)[1];
			verts[v].diffuse = DX8Wrapper::Convert_Color(diffuse[v]);
		}
	}
}

// Retail 0x001718E0, 21 bytes. MeshModelClass instance-list walk: a null
// model yields the global list head, otherwise the +0xB8 next link.
class MeshModelClass { public: char m_pad00[0xB8]; MeshModelClass *m_next; void rva001716E0UnregisterMeshModel(); };
__declspec(noinline) MeshModelClass *rva001718E0GetNextMeshModel(MeshModelClass *model)
{
 if(!model) return *(MeshModelClass **)&MeshModelListHead;
 return model->m_next;
}

class DX8MeshRendererClass { public: void Invalidate(bool); };
extern DX8MeshRendererClass *TheDX8MeshRenderer;

// Retail 0x001170A0, 120 bytes. WW3D mesh-cache invalidation under the DX8
// device lock: walk every MeshModelClass instance and unregister it, then
// invalidate a guarded renderer.
void WW3D::_Invalidate_Mesh_Cache()
{
 BFMEDX8DeviceLock lock;
 for(MeshModelClass *model=rva001718E0GetNextMeshModel(0);model!=0;model=rva001718E0GetNextMeshModel(model))
  model->rva001716E0UnregisterMeshModel();
 if(TheDX8MeshRenderer!=0)
  TheDX8MeshRenderer->Invalidate(false);
}



// Callers elsewhere reach bodies in this unit through spellings pinned to the same
// retail address (same cdecl/thiscall ABI); bind them here.
#pragma comment(linker, "/alternatename:??0DX8VertexBufferClass@@QAE@IGW4UsageType@0@I@Z=??0BfmeDynamicNativeVB@@QAE@IGII@Z")

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??0BfmeSortingVBAccess@@QAE@IIGI@Z=??0DynamicVBAccessClass@@QAE@IIGI@Z")
#pragma comment(linker, "/alternatename:??0WriteLock@BfmeSortingVBAccess@@QAE@PAU1@@Z=??0WriteLock@DynamicVBAccessClass@@QAE@PAV1@@Z")
#pragma comment(linker, "/alternatename:??1WriteLock@BfmeSortingVBAccess@@QAE@XZ=??1WriteLock@DynamicVBAccessClass@@QAE@XZ")


