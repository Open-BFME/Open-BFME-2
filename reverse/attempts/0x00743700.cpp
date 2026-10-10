// ?RenderStreak@StreakRendererClass@@QAEXAAVRenderInfoClass@@ABVMatrix3D@@IPAVVector3@@PAVVector4@@PAMABVSphereClass@@PAI@Z
// partial score=0.8076875017814811 date=2026-10-10
// cl: /I. /DBFME_WWSTRING_NATIVE_CSTR_ASSIGN /Ireference/shims/wwstring_teardown/zhmd /arch:SSE /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// stlport
// SPDX-License-Identifier: GPL-3.0-or-later
// Adapted from Command & Conquer Generals Zero Hour, copyright 2025 Electronic Arts Inc.
// Reference Open-BFME-1 575ba2b04; target and donor facts distinguished in RE record.
// Complete StreakRenderer743700..746DD4 attempt; no verified retail byte credit.
// Embedded private header views are bank evidence, not shared-header changes.
#define Matrix4x4 Matrix4
void operator delete[](void*) throw();
#include "reference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2/texture.h"
#include "reference/shims/bfmestreak/streakrender.h"
#include "ww3d.h"
#include "rinfo.h"
#include <d3d8.h>
#if defined(_MSC_VER)
#pragma once
#endif
#ifndef DX8_FVF_H
#define DX8_FVF_H
#include "always.h"
#include <d3d8.h>
#ifdef WWDEBUG
#include "wwdebug.h"
#endif
class StringClass;
enum {
	DX8_FVF_XYZ				= D3DFVF_XYZ,
	DX8_FVF_XYZN			= D3DFVF_XYZ|D3DFVF_NORMAL,
	DX8_FVF_XYZNUV1		= D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX1,
	DX8_FVF_XYZNUV2		= D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX2,
	DX8_FVF_XYZNDUV1		= D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX1|D3DFVF_DIFFUSE,
	DX8_FVF_XYZNDUV2		= D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX2|D3DFVF_DIFFUSE,
	DX8_FVF_XYZDUV1		= D3DFVF_XYZ|D3DFVF_TEX1|D3DFVF_DIFFUSE,
	DX8_FVF_XYZDUV2		= D3DFVF_XYZ|D3DFVF_TEX2|D3DFVF_DIFFUSE,
	DX8_FVF_XYZUV1			= D3DFVF_XYZ|D3DFVF_TEX1,
	DX8_FVF_XYZUV2			= D3DFVF_XYZ|D3DFVF_TEX2,
 	DX8_FVF_XYZNDUV1TG3	= (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX4|D3DFVF_TEXCOORDSIZE2(0)|D3DFVF_TEXCOORDSIZE3(1)|D3DFVF_TEXCOORDSIZE3(2)|D3DFVF_TEXCOORDSIZE3(3)),
 	DX8_FVF_XYZNUV2DMAP	= (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX3 | D3DFVF_TEXCOORDSIZE1(0) | D3DFVF_TEXCOORDSIZE4(1) | D3DFVF_TEXCOORDSIZE2(2) ),
	DX8_FVF_XYZNDCUBEMAP	= D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE
};
struct VertexFormatXYZ
{
	float x;
	float y;
	float z;
};
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
struct VertexFormatXYZNUV2
{
	float x;
	float y;
	float z;
	float nx;
	float ny;
	float nz;
	float u1;
	float v1;
	float u2;
	float v2;
};
struct VertexFormatXYZN
{
	float x;
	float y;
	float z;
	float nx;
	float ny;
	float nz;
};
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
struct VertexFormatXYZNDUV2
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
	float u2;
	float v2;
};
struct VertexFormatXYZDUV1
{
	float x;
	float y;
	float z;
	unsigned diffuse;
	float u1;
	float v1;
};
struct VertexFormatXYZDUV2
{
	float x;
	float y;
	float z;
	unsigned diffuse;
	float u1;
	float v1;
	float u2;
	float v2;
};
struct VertexFormatXYZUV1
{
	float x;
	float y;
	float z;
	float u1;
	float v1;
};
struct VertexFormatXYZUV2
{
	float x;
	float y;
	float z;
	float u1;
	float v1;
	float u2;
	float v2;
};
struct VertexFormatXYZNDUV1TG3
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
	float Sx;
	float Sy;
	float Sz;
	float Tx;
	float Ty;
	float Tz;
	float SxTx;
	float SxTy;
	float SxTz;
};
struct VertexFormatXYZNUV2DMAP
{
	float x;
	float y;
	float z;
	float nx;
	float ny;
	float nz;
	float T1x;
	float T1y;
	float T1z;
	float T1w;
	float T2x;
	float T2y;
};
struct VertexFormatXYZNDCUBEMAP
{
	float x;
	float y;
	float z;
	float nx;
	float ny;
	float nz;
	unsigned diffuse;
};
class FVFInfoClass : public W3DMPO
{
	W3DMPO_GLUE(FVFInfoClass)
	mutable unsigned FVF;
 bool AdditionalBasis;
 unsigned ExtensionCount;
	mutable unsigned						fvf_size;
	unsigned							location_offset;
	unsigned							normal_offset;
	unsigned							blend_offset;
	unsigned							texcoord_offset[D3DDP_MAXTEXCOORD];
	unsigned							diffuse_offset;
	unsigned							specular_offset;
public:
	FVFInfoClass(unsigned FVF, unsigned vertex_size=0);
	inline unsigned Get_Location_Offset() const { return location_offset; }
	inline unsigned Get_Normal_Offset() const { return normal_offset; }
#ifdef WWDEBUG
	inline unsigned Get_Tex_Offset(unsigned int n) const { WWASSERT(n<D3DDP_MAXTEXCOORD); return texcoord_offset[n]; }
#else
	inline unsigned Get_Tex_Offset(unsigned int n) const { return texcoord_offset[n]; }
#endif
	inline unsigned Get_Diffuse_Offset() const { return diffuse_offset; }
	inline unsigned Get_Specular_Offset() const { return specular_offset; }
	inline unsigned Get_FVF() const { return FVF; }
	inline unsigned Get_FVF_Size() const { return fvf_size; }
	void Get_FVF_Name(StringClass& fvfname) const;
	inline void Set_FVF(unsigned fvf) const { FVF=fvf; }
	inline void Set_FVF_Size(unsigned size) const { fvf_size=size; }
};
#endif
#ifndef DX8VERTEXBUFFER_H
#define DX8VERTEXBUFFER_H
#include "always.h"
#include "wwdebug.h"
#include "refcount.h"
#include "dx8fvf.h"
const unsigned dynamic_fvf_type=D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX2|D3DFVF_DIFFUSE;
class DX8Wrapper;
class SortingRendererClass;
class Vector2;
class Vector3;
class Vector4;
class StringClass;
class DX8VertexBufferClass;
class FVFInfoClass;
struct IDirect3DVertexBuffer8;
class VertexBufferClass;
struct VertexFormatXYZNDUV2;
class VertexBufferLockClass
{
protected:
	VertexBufferClass* VertexBuffer;
	void* Vertices;
	VertexBufferLockClass(VertexBufferClass* vertex_buffer_) : VertexBuffer(vertex_buffer_) {}
public:
	void* Get_Vertex_Array() { return Vertices; }
};
class VertexBufferClass : public W3DMPO, public RefCountClass
{
protected:
	VertexBufferClass(unsigned type, unsigned FVF, unsigned short VertexCount, unsigned vertex_size=0);
	virtual ~VertexBufferClass() throw();
public:
	inline const FVFInfoClass& FVF_Info() const { return *fvf_info; }
	inline unsigned short Get_Vertex_Count() const { return VertexCount; }
	inline unsigned Type() const { return type; }
	void Add_Engine_Ref() const;
	void Release_Engine_Ref() const;
	inline unsigned Engine_Refs() const { return engine_refs; }
	class WriteLock : public VertexBufferLockClass
	{
	public:
		WriteLock(VertexBufferClass* vertex_buffer, int flags=0);
		__declspec(noinline) ~WriteLock();
	};
	class AppendLockClass : public VertexBufferLockClass
	{
	public:
		AppendLockClass(VertexBufferClass* vertex_buffer,unsigned start_index, unsigned index_range, int flags=0);
		__declspec(noinline) ~AppendLockClass();
	};
	static unsigned Get_Total_Buffer_Count();
	static unsigned Get_Total_Allocated_Vertices();
	static unsigned Get_Total_Allocated_Memory();
protected:
	unsigned							type;
	unsigned short					VertexCount;
	mutable int						engine_refs;
	FVFInfoClass*					fvf_info;
	bool								m_BFMEExplicitVertexSize;
	unsigned char					m_BFMEPadding[3];
};
class DynamicVBAccessClass
{
	friend DX8Wrapper;
	friend SortingRendererClass;
	const FVFInfoClass& FVFInfo;
	unsigned Type;
	unsigned FormatIndex;
	unsigned Declaration;
	unsigned short VertexCount;
	unsigned short VertexBufferOffset;
	VertexBufferClass* VertexBuffer;
	void Allocate_Sorting_Dynamic_Buffer();
	void Allocate_DX8_Dynamic_Buffer();
public:
	DynamicVBAccessClass(unsigned type,unsigned format_index,unsigned short vertex_count,unsigned declaration);
	~DynamicVBAccessClass();
	const FVFInfoClass& FVF_Info() const { return FVFInfo; }
	unsigned Get_Type() const { return Type; }
	unsigned short Get_Vertex_Count() const { return VertexCount; }
	static void _Deinit();
	static void _Reset(bool frame_changed);
	static unsigned short Get_Default_Vertex_Count(void);
	class WriteLock
	{
		DynamicVBAccessClass* DynamicVBAccess;
		VertexFormatXYZNDUV2 * Vertices;
		unsigned char DeviceGuard;
	public:
		WriteLock(DynamicVBAccessClass* vb_access);
		~WriteLock();
		VertexFormatXYZNDUV2 * Get_Formatted_Vertex_Array();
	};
	friend WriteLock;
};
inline VertexFormatXYZNDUV2 * DynamicVBAccessClass::WriteLock::Get_Formatted_Vertex_Array()
{
	WWASSERT(DynamicVBAccess->VertexBuffer->FVF_Info().Get_FVF() == (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX2|D3DFVF_DIFFUSE));
	return Vertices;
}
class DX8VertexBufferClass : public VertexBufferClass
{
protected:
	~DX8VertexBufferClass();
public:
	enum UsageType {
		USAGE_DEFAULT=0,
		USAGE_DYNAMIC=1,
		USAGE_SOFTWAREPROCESSING=2,
		USAGE_NPATCHES=4
	};
	DX8VertexBufferClass(unsigned FVF, unsigned short VertexCount, UsageType usage=USAGE_DEFAULT, unsigned vertex_size=0);
	DX8VertexBufferClass(const Vector3* vertices, const Vector3* normals, const Vector2* tex_coords, unsigned short VertexCount,UsageType usage=USAGE_DEFAULT);
	DX8VertexBufferClass(const Vector3* vertices, const Vector3* normals, const Vector4* diffuse, const Vector2* tex_coords, unsigned short VertexCount,UsageType usage=USAGE_DEFAULT);
	DX8VertexBufferClass(const Vector3* vertices, const Vector4* diffuse, const Vector2* tex_coords, unsigned short VertexCount,UsageType usage=USAGE_DEFAULT);
	DX8VertexBufferClass(const Vector3* vertices, const Vector2* tex_coords, unsigned short VertexCount,UsageType usage=USAGE_DEFAULT);
	IDirect3DVertexBuffer8* Get_DX8_Vertex_Buffer() { return VertexBuffer; }
	void Copy(const Vector3* loc, unsigned first_vertex, unsigned count);
	void Copy(const Vector3* loc, const Vector2* uv, unsigned first_vertex, unsigned count);
	void Copy(const Vector3* loc, const Vector3* norm, unsigned first_vertex, unsigned count);
	void Copy(const Vector3* loc, const Vector3* norm, const Vector2* uv, unsigned first_vertex, unsigned count);
	void Copy(const Vector3* loc, const Vector3* norm, const Vector2* uv, const Vector4* diffuse, unsigned first_vertex, unsigned count);
	void Copy(const Vector3* loc, const Vector2* uv, const Vector4* diffuse, unsigned first_vertex, unsigned count);
protected:
	IDirect3DVertexBuffer8*		VertexBuffer;
	void Create_Vertex_Buffer(UsageType usage);
};
class SortingVertexBufferClass : public VertexBufferClass
{
	friend DX8Wrapper;
	friend SortingRendererClass;
	friend VertexBufferClass::WriteLock;
	friend VertexBufferClass::AppendLockClass;
	friend DynamicVBAccessClass::WriteLock;
	VertexFormatXYZNDUV2* VertexBuffer;
protected:
	~SortingVertexBufferClass() throw();
public:
	SortingVertexBufferClass(unsigned short VertexCount);
};
#endif
#ifndef DX8INDEXBUFFER_H
#define DX8INDEXBUFFER_H
#include "always.h"
#include "wwdebug.h"
#include "refcount.h"
#include "sphere.h"
class DX8Wrapper;
class SortingRendererClass;
struct IDirect3DIndexBuffer8;
class DX8IndexBufferClass;
class SortingIndexBufferClass;
class IndexBufferClass : public W3DMPO, public RefCountClass
{
protected:
	virtual ~IndexBufferClass();
public:
	IndexBufferClass(unsigned type, unsigned index_count);
	void Copy(unsigned int* indices,unsigned start_index,unsigned index_count);
	void Copy(unsigned short* indices,unsigned start_index,unsigned index_count);
	inline unsigned Get_Index_Count() const { return index_count; }
	inline unsigned Type() const { return type; }
	void Add_Engine_Ref() const;
	void Release_Engine_Ref() const;
	inline unsigned Engine_Refs() const { return engine_refs; }
	class WriteLockClass
	{
		IndexBufferClass* index_buffer;
		unsigned short* indices;
	public:
		WriteLockClass(IndexBufferClass* index_buffer, int flags=0);
		~WriteLockClass();
		unsigned short* Get_Index_Array() { return indices; }
	};
	class AppendLockClass
	{
		IndexBufferClass* index_buffer;
		unsigned short* indices;
	public:
		AppendLockClass(IndexBufferClass* index_buffer,unsigned start_index, unsigned index_range);
		~AppendLockClass();
		unsigned short* Get_Index_Array() { return indices; }
	};
	static unsigned Get_Total_Buffer_Count();
	static unsigned Get_Total_Allocated_Indices();
	static unsigned Get_Total_Allocated_Memory();
protected:
	mutable int					engine_refs;
	unsigned					index_count;
	unsigned						type;
};
class DynamicIBAccessClass : public W3DMPO
{
	W3DMPO_GLUE(DynamicIBAccessClass)
	friend DX8Wrapper;
	friend SortingRendererClass;
	unsigned Type;
	unsigned short IndexCount;
	unsigned short IndexBufferOffset;
	IndexBufferClass* IndexBuffer;
	void Allocate_Sorting_Dynamic_Buffer();
	void Allocate_DX8_Dynamic_Buffer();
public:
	DynamicIBAccessClass(unsigned short type, unsigned short index_count);
	~DynamicIBAccessClass();
	unsigned Get_Type() const { return Type; }
	unsigned short Get_Index_Count() const { return IndexCount; }
	static void _Deinit();
	static void _Reset(bool frame_changed);
	static unsigned short Get_Default_Index_Count(void);
	class WriteLockClass
	{
		DynamicIBAccessClass* DynamicIBAccess;
		unsigned short* Indices;
		unsigned char DeviceGuard;
	public:
		WriteLockClass(DynamicIBAccessClass* ib_access);
		~WriteLockClass();
		unsigned short* Get_Index_Array() { return Indices; }
	};
	friend WriteLockClass;
};
class DX8IndexBufferClass : public IndexBufferClass
{
	friend IndexBufferClass::WriteLockClass;
	friend IndexBufferClass::AppendLockClass;
public:
	enum UsageType {
		USAGE_DEFAULT=0,
		USAGE_DYNAMIC=1,
		USAGE_SOFTWAREPROCESSING=2,
		USAGE_NPATCHES=4
	};
	DX8IndexBufferClass(unsigned short index_count,UsageType usage=USAGE_DEFAULT);
#ifdef BFME_DYNAMIC_IB_UINT_CTOR_ABI
	DX8IndexBufferClass(unsigned index_count,UsageType usage);
#endif
	~DX8IndexBufferClass();
	void Copy(unsigned int* indices,unsigned start_index,unsigned index_count);
	void Copy(unsigned short* indices,unsigned start_index,unsigned index_count);
	inline IDirect3DIndexBuffer8* Get_DX8_Index_Buffer()	{ return index_buffer; }
private:
	IDirect3DIndexBuffer8*	index_buffer;
};
class SortingIndexBufferClass : public IndexBufferClass
{
	friend DX8Wrapper;
	friend SortingRendererClass;
	friend IndexBufferClass::WriteLockClass;
	friend IndexBufferClass::AppendLockClass;
	friend DynamicIBAccessClass::WriteLockClass;
public:
	SortingIndexBufferClass(unsigned short index_count);
	~SortingIndexBufferClass();
protected:
	unsigned short* index_buffer;
};
extern int IndexBufferExceptionFunc(void);
#endif
#ifndef DX8_WRAPPER_H
#define DX8_WRAPPER_H
#include "always.h"
#include "dllist.h"
#include "d3d8.h"
#include "matrix4.h"
#include "statistics.h"
#include "wwstring.h"
#include "lightenvironment.h"
#include "shader.h"
#include "vector4.h"
#include "cpudetect.h"
#include "dx8caps.h"
#include "texture.h"
#include "dx8vertexbuffer.h"
#include "dx8indexbuffer.h"
#include "vertmaterial.h"
#include "dx8fvf.h"
#define	VALUE_NAME_RENDER_DEVICE_NAME					"RenderDeviceName"
#define	VALUE_NAME_RENDER_DEVICE_WIDTH				"RenderDeviceWidth"
#define	VALUE_NAME_RENDER_DEVICE_HEIGHT				"RenderDeviceHeight"
#define	VALUE_NAME_RENDER_DEVICE_DEPTH				"RenderDeviceDepth"
#define	VALUE_NAME_RENDER_DEVICE_WINDOWED			"RenderDeviceWindowed"
#define	VALUE_NAME_RENDER_DEVICE_TEXTURE_DEPTH		"RenderDeviceTextureDepth"
const unsigned MAX_TEXTURE_STAGES=16;
const unsigned MAX_VERTEX_STREAMS=2;
const unsigned MAX_VERTEX_SHADER_CONSTANTS=96;
const unsigned MAX_PIXEL_SHADER_CONSTANTS=8;
const unsigned MAX_SHADOW_MAPS=1;
#define prevVer
#define nextVer
#define __volatile unsigned
enum {
	BUFFER_TYPE_DX8,
	BUFFER_TYPE_SORTING,
	BUFFER_TYPE_DYNAMIC_DX8,
	BUFFER_TYPE_DYNAMIC_SORTING,
	BUFFER_TYPE_INVALID
};
class VertexMaterialClass;
class CameraClass;
class LightEnvironmentClass;
class RenderDeviceDescClass;
class VertexBufferClass;
class DynamicVBAccessClass;
class IndexBufferClass;
class DynamicIBAccessClass;
class TextureClass;
class ZTextureClass;
class LightClass;
class SurfaceClass;
class DX8Caps;
#define DX8_RECORD_MATRIX_CHANGE()				matrix_changes++
#define DX8_RECORD_MATERIAL_CHANGE()			material_changes++
#define DX8_RECORD_VERTEX_BUFFER_CHANGE()		vertex_buffer_changes++
#define DX8_RECORD_INDEX_BUFFER_CHANGE()		index_buffer_changes++
#define DX8_RECORD_LIGHT_CHANGE()				light_changes++
#define DX8_RECORD_TEXTURE_CHANGE()				texture_changes++
#define DX8_RECORD_RENDER_STATE_CHANGE()		render_state_changes++
#define DX8_RECORD_TEXTURE_STAGE_STATE_CHANGE() texture_stage_state_changes++
#define DX8_RECORD_DRAW_CALLS()					draw_calls++
extern unsigned number_of_DX8_calls;
extern bool _DX8SingleThreaded;
void DX8_Assert();
void Log_DX8_ErrorCode(unsigned res);
#ifdef WWDEBUG
#define DX8CALL_HRES(x,res) DX8_Assert(); res = DX8Wrapper::_Get_D3D_Device8()->x; DX8_ErrorCode(res); number_of_DX8_calls++;
#define DX8CALL(x) DX8_Assert(); DX8_ErrorCode(DX8Wrapper::_Get_D3D_Device8()->x); number_of_DX8_calls++;
#define DX8CALL_D3D(x) DX8_Assert(); DX8_ErrorCode(DX8Wrapper::_Get_D3D8()->x); number_of_DX8_calls++;
#define DX8_THREAD_ASSERT() if (_DX8SingleThreaded) { WWASSERT_PRINT(DX8Wrapper::_Get_Main_Thread_ID()==ThreadClass::_Get_Current_Thread_ID(),"DX8Wrapper::DX8 calls must be called from the main thread!"); }
#else
#define DX8CALL_HRES(x,res) res = DX8Wrapper::_Get_D3D_Device8()->x; number_of_DX8_calls++;
#define DX8CALL(x) DX8Wrapper::_Get_D3D_Device8()->x; number_of_DX8_calls++;
#define DX8CALL_D3D(x) DX8Wrapper::_Get_D3D8()->x; number_of_DX8_calls++;
#define DX8_THREAD_ASSERT() ;
#endif
#define no_EXTENDED_STATS
#ifdef EXTENDED_STATS
class DX8_Stats
{
public:
	bool m_showingStats;
	bool m_disableTerrain;
	bool m_disableWater;
	bool m_disableObjects;
	bool m_disableOverhead;
	bool m_disableConsole;
	int  m_debugLinesToShow;
	int	 m_sleepTime;
public:
	DX8_Stats::DX8_Stats(void) {
		m_disableConsole = m_showingStats = m_disableTerrain = m_disableWater = m_disableOverhead = m_disableObjects = false;
		m_sleepTime = 0;
		m_debugLinesToShow = -1;
	}
};
#endif
class DX8_CleanupHook
{
public:
	virtual void ReleaseResources(void)=0;
	virtual void ReAcquireResources(void)=0;
};
struct RenderStateStruct
{
	ShaderClass shader;
	VertexMaterialClass* material;
	TextureBaseClass * Textures[MAX_TEXTURE_STAGES];
	D3DLIGHT8 Lights[4];
	bool LightEnable[4];
	Matrix4x4 world;
	Matrix4x4 view;
	unsigned vertex_buffer_types[MAX_VERTEX_STREAMS];
	unsigned index_buffer_type;
	unsigned short vba_offset;
	unsigned short vba_count;
	unsigned short iba_offset;
	VertexBufferClass* vertex_buffers[MAX_VERTEX_STREAMS];
	IndexBufferClass* index_buffer;
	unsigned short index_base_offset;
	RenderStateStruct();
	~RenderStateStruct();
	RenderStateStruct& operator= (const RenderStateStruct& src);
};
class DX8Wrapper {
enum ChangedStates {
		WORLD_CHANGED	=	1<<0,
		VIEW_CHANGED	=	1<<1,
		LIGHT0_CHANGED	=	1<<2,
		LIGHT1_CHANGED	=	1<<3,
		LIGHT2_CHANGED	=	1<<4,
		LIGHT3_CHANGED	=	1<<5,
		TEXTURE0_CHANGED=	1<<6,
		TEXTURE1_CHANGED=	1<<7,
		TEXTURE2_CHANGED=	1<<8,
		TEXTURE3_CHANGED=	1<<9,
		MATERIAL_CHANGED=	1<<14,
		SHADER_CHANGED	=	1<<15,
		VERTEX_BUFFER_CHANGED = 1<<16,
		INDEX_BUFFER_CHANGED = 1 << 17,
		WORLD_IDENTITY=	1<<18,
		VIEW_IDENTITY=		1<<19,
		TEXTURES_CHANGED=
			TEXTURE0_CHANGED|TEXTURE1_CHANGED|TEXTURE2_CHANGED|TEXTURE3_CHANGED,
		LIGHTS_CHANGED=
			LIGHT0_CHANGED|LIGHT1_CHANGED|LIGHT2_CHANGED|LIGHT3_CHANGED,
	};
public:
 static void Set_Vertex_Buffer(const DynamicVBAccessClass&);
 static void Set_Index_Buffer(const DynamicIBAccessClass&,unsigned short);
 static void Draw_Triangles(unsigned,unsigned,unsigned,unsigned);
 static void Set_Material(const VertexMaterialClass*);
 static void Set_Shader(const ShaderClass&);
 static void Set_Transform(D3DTRANSFORMSTATETYPE,const Matrix4x4&);
 static void Set_Transform(D3DTRANSFORMSTATETYPE,const Matrix3D&);
 static void Get_Transform(D3DTRANSFORMSTATETYPE,Matrix4x4&);
 static Vector4 Convert_Color(unsigned);
 static unsigned Convert_Color(const Vector4&);
 static unsigned Convert_Color(const Vector3&,float);
 static unsigned Convert_Color_Clamp(const Vector4&);
 static void Clamp_Color(Vector4&);
 static IDirect3DDevice8* _Get_D3D_Device8();
protected:
 static RenderStateStruct render_state;
 static unsigned render_state_changed;
 static float ZNear,ZFar;
 static unsigned matrix_changes;
};
WWINLINE Vector4 DX8Wrapper::Convert_Color(unsigned color)
{
	Vector4 col;
	col[3]=((color&0xff000000)>>24)/255.0f;
	col[0]=((color&0xff0000)>>16)/255.0f;
	col[1]=((color&0xff00)>>8)/255.0f;
	col[2]=((color&0xff)>>0)/255.0f;
	return col;
}
#if 0
WWINLINE unsigned int DX8Wrapper::Convert_Color(const Vector3& color, const float alpha)
{
	WWASSERT(color.X<=1.0f);
	WWASSERT(color.Y<=1.0f);
	WWASSERT(color.Z<=1.0f);
	WWASSERT(alpha<=1.0f);
	WWASSERT(color.X>=0.0f);
	WWASSERT(color.Y>=0.0f);
	WWASSERT(color.Z>=0.0f);
	WWASSERT(alpha>=0.0f);
	return D3DCOLOR_COLORVALUE(color.X,color.Y,color.Z,alpha);
}
WWINLINE unsigned int DX8Wrapper::Convert_Color(const Vector4& color)
{
	WWASSERT(color.X<=1.0f);
	WWASSERT(color.Y<=1.0f);
	WWASSERT(color.Z<=1.0f);
	WWASSERT(color.W<=1.0f);
	WWASSERT(color.X>=0.0f);
	WWASSERT(color.Y>=0.0f);
	WWASSERT(color.Z>=0.0f);
	WWASSERT(color.W>=0.0f);
	return D3DCOLOR_COLORVALUE(color.X,color.Y,color.Z,color.W);
}
#else
WWINLINE unsigned int DX8Wrapper::Convert_Color(const Vector3& color,float alpha)
{
	const float scale = 255.0;
	unsigned int col=0;
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
WWINLINE unsigned int DX8Wrapper::Convert_Color(const Vector4& color)
{
	return Convert_Color(reinterpret_cast<const Vector3&>(color),color[3]);
}
#include "cpudetect.h"
WWINLINE void DX8Wrapper::Clamp_Color(Vector4& color)
{
	if (!CPUDetectClass::Has_CMOV_Instruction()) {
		{float f=(color[0]<0.0f)?0.0f:color[0]; color[0]=(f>1.0f)?1.0f:f;}
		{float f=(color[1]<0.0f)?0.0f:color[1]; color[1]=(f>1.0f)?1.0f:f;}
		{float f=(color[2]<0.0f)?0.0f:color[2]; color[2]=(f>1.0f)?1.0f:f;}
		{float f=(color[3]<0.0f)?0.0f:color[3]; color[3]=(f>1.0f)?1.0f:f;}
		return;
	}
	__asm
	{
		mov	esi,dword ptr color
		mov edx,0x3f800000
		mov edi,dword ptr[esi]
		mov ebx,edi
		sar edi,31
		not edi
		and edi,ebx
		cmp edi,edx
		cmovnb edi,edx
		mov dword ptr[esi],edi
		mov edi,dword ptr[esi+4]
		mov ebx,edi
		sar edi,31
		not edi
		and edi,ebx
		cmp edi,edx
		cmovnb edi,edx
		mov dword ptr[esi+4],edi
		mov edi,dword ptr[esi+8]
		mov ebx,edi
		sar edi,31
		not edi
		and edi,ebx
		cmp edi,edx
		cmovnb edi,edx
		mov dword ptr[esi+8],edi
		mov edi,dword ptr[esi+12]
		mov ebx,edi
		sar edi,31
		not edi
		and edi,ebx
		cmp edi,edx
		cmovnb edi,edx
		mov dword ptr[esi+12],edi
	}
}
WWINLINE unsigned int DX8Wrapper::Convert_Color_Clamp(const Vector4& color)
{
	Vector4 clamped_color=color;
	DX8Wrapper::Clamp_Color(clamped_color);
	return Convert_Color(reinterpret_cast<const Vector3&>(clamped_color),clamped_color[3]);
}
#endif
WWINLINE void DX8Wrapper::Set_Material(const VertexMaterialClass* material)
{
	REF_PTR_SET(render_state.material,const_cast<VertexMaterialClass*>(material));
	render_state_changed|=MATERIAL_CHANGED;
	SNAPSHOT_SAY(("DX8Wrapper::Set_Material(%s)\n",material ? material->Get_Name() : "NULL"));
}
WWINLINE void DX8Wrapper::Set_Shader(const ShaderClass& shader)
{
	if (!ShaderClass::ShaderDirty && ((unsigned&)shader==(unsigned&)render_state.shader)) {
		return;
	}
	render_state.shader=shader;
	render_state_changed|=SHADER_CHANGED;
#ifdef MESH_RENDER_SNAPSHOT_ENABLED
	StringClass str;
#endif
	SNAPSHOT_SAY(("DX8Wrapper::Set_Shader(%s)\n",shader.Get_Description(str)));
}
WWINLINE void DX8Wrapper::Set_Transform(D3DTRANSFORMSTATETYPE transform,const Matrix4x4& m)
{
	switch ((int)transform) {
	case D3DTS_WORLD:
		render_state.world=m.Transpose();
		render_state_changed&=~(unsigned)WORLD_IDENTITY;
		render_state_changed|=(unsigned)WORLD_CHANGED;
		break;
	case D3DTS_VIEW:
		render_state.view=m.Transpose();
		render_state_changed&=~(unsigned)VIEW_IDENTITY;
		render_state_changed|=(unsigned)VIEW_CHANGED;
		break;
	case D3DTS_PROJECTION:
		{
			Matrix4x4 ProjectionMatrix=m.Transpose();
			ZFar=0.0f;
			ZNear=0.0f;
			DX8CALL(SetTransform(D3DTS_PROJECTION,(D3DMATRIX*)&ProjectionMatrix));
		}
		break;
	default:
		DX8_RECORD_MATRIX_CHANGE();
		Matrix4x4 m2=m.Transpose();
		DX8CALL(SetTransform(transform,(D3DMATRIX*)&m2));
		break;
	}
}
WWINLINE void DX8Wrapper::Set_Transform(D3DTRANSFORMSTATETYPE transform,const Matrix3D& m)
{
	Matrix4x4 m2(m);
	switch ((int)transform) {
	case D3DTS_WORLD:
		render_state.world=m2.Transpose();
		render_state_changed&=~(unsigned)WORLD_IDENTITY;
		render_state_changed|=(unsigned)WORLD_CHANGED;
		break;
	case D3DTS_VIEW:
		render_state.view=m2.Transpose();
		render_state_changed&=~(unsigned)VIEW_IDENTITY;
		render_state_changed|=(unsigned)VIEW_CHANGED;
		break;
	default:
		DX8_RECORD_MATRIX_CHANGE();
		m2=m2.Transpose();
		DX8CALL(SetTransform(transform,(D3DMATRIX*)&m2));
		break;
	}
}
WWINLINE void DX8Wrapper::Get_Transform(D3DTRANSFORMSTATETYPE transform, Matrix4x4& m)
{
	D3DMATRIX mat;
	switch ((int)transform) {
	case D3DTS_WORLD:
		if (render_state_changed&WORLD_IDENTITY) m.Make_Identity();
		else m=render_state.world.Transpose();
		break;
	case D3DTS_VIEW:
		if (render_state_changed&VIEW_IDENTITY) m.Make_Identity();
		else m=render_state.view.Transpose();
		break;
	default:
		DX8CALL(GetTransform(transform,&mat));
		m=*(Matrix4x4*)&mat;
		m=m.Transpose();
		break;
	}
}
#endif
#ifndef SORTING_RENDERER_H
#define SORTING_RENDERER_H
#include "always.h"
class SortingNodeStruct;
class SphereClass;
class SortingRendererClass
{
	static bool _EnableTriangleDraw;
	static void Flush_Sorting_Pool();
	static void Insert_To_Sorting_Pool(SortingNodeStruct* state);
public:
	static void Insert_Triangles(
		const SphereClass& bounding_sphere,
		unsigned start_index,
		unsigned polygon_count,
		unsigned min_vertex_index,
		unsigned vertex_count);
	static void Insert_Triangles(
		unsigned start_index,
		unsigned polygon_count,
		unsigned min_vertex_index,
		unsigned vertex_count);
	static void Insert_VolumeParticle(
		const SphereClass& bounding_sphere,
		unsigned start_index,
		unsigned polygon_count,
		unsigned min_vertex_index,
		unsigned vertex_count,
		unsigned layerCount);
	static void Flush();
	static void Deinit();
	static void SetMinVertexBufferSize( unsigned val );
	static void _Enable_Triangle_Draw(bool enable) { _EnableTriangleDraw=enable; }
	static bool _Is_Triangle_Draw_Enabled() { return _EnableTriangleDraw; }
};
#endif
#include "dx8wrapper.h"
#include "sortingrenderer.h"
struct TargetCenter3 { float x,y,z; };
class BfmeSortingDispatchAt0012FE00 { public: static void Insert(const TargetCenter3 &, unsigned, unsigned, unsigned, unsigned); };
struct BFME2TextureRef { TextureBaseClass *Ptr; };
void BFME2Set_Texture(unsigned stage,const BFME2TextureRef &texture);
#include "vp.h"
#include "vector3i.h"
#include "random.h"
#include "reference/shims/bfme_randomizer_dtor/v3_rnd.h"
#ifdef _INTERNAL
#endif
#if MAX_STREAK_SUBDIV_LEVELS > 7
#define STREAK_CHUNK_SIZE (1 << MAX_STREAK_SUBDIV_LEVELS)
#else
#define STREAK_CHUNK_SIZE (128)
#endif
#define MAX_STREAK_POINT_BUFFER_SIZE (1 + STREAK_CHUNK_SIZE)
#define MAX_STREAK_POLY_BUFFER_SIZE (STREAK_CHUNK_SIZE * 2)
StreakRendererClass::StreakRendererClass(void) :
		Texture(NULL),
		Shader(ShaderClass::_PresetAdditiveSpriteShader),
		Width(0.0f),
		Color(Vector3(1,1,1)),
		Opacity(1.0f),
		SubdivisionLevel(0),
		NoiseAmplitude(0.0f),
		MergeAbortFactor(1.5f),
		TextureTileFactor(1.0f),
		LastUsedSyncTime(WW3D::Get_Sync_Time()),
		CurrentUVOffset(0.0f,0.0f),
		UVOffsetDeltaPerMS(0.0f, 0.0f),
		Bits(DEFAULT_BITS),
		m_vertexBufferSize(0),
		m_vertexBuffer(NULL)
{
}
StreakRendererClass::StreakRendererClass(const StreakRendererClass & that) :
		Texture(NULL),
		Shader(ShaderClass::_PresetAdditiveSpriteShader),
		Width(0.0f),
		Color(Vector3(1,1,1)),
		Opacity(1.0f),
		SubdivisionLevel(0),
		NoiseAmplitude(0.0f),
		MergeAbortFactor(1.5f),
		TextureTileFactor(1.0f),
		LastUsedSyncTime(that.LastUsedSyncTime),
		CurrentUVOffset(0.0f,0.0f),
		UVOffsetDeltaPerMS(0.0f, 0.0f),
		Bits(DEFAULT_BITS),
		m_vertexBufferSize(0),
		m_vertexBuffer(NULL)
{
	*this = that;
}
StreakRendererClass & StreakRendererClass::operator = (const StreakRendererClass & that)
{
	if (this != &that) {
		Texture = that.Texture;
		Shader = that.Shader;
		Width = that.Width;
		Color = that.Color;
		Opacity = that.Opacity;
		SubdivisionLevel = that.SubdivisionLevel;
		NoiseAmplitude = that.NoiseAmplitude;
		MergeAbortFactor = that.MergeAbortFactor;
		TextureTileFactor = that.TextureTileFactor;
		LastUsedSyncTime = that.LastUsedSyncTime;
		CurrentUVOffset = that.CurrentUVOffset;
		UVOffsetDeltaPerMS = that.UVOffsetDeltaPerMS;
		Bits = that.Bits;
	}
	return *this;
}
StreakRendererClass::~StreakRendererClass(void)
{
	delete [] m_vertexBuffer;
}
void StreakRendererClass::Init(const W3dEmitterLinePropertiesStruct & props)
{
	Set_Merge_Intersections(props.Flags & W3D_ELINE_MERGE_INTERSECTIONS);
	Set_Freeze_Random(props.Flags & W3D_ELINE_FREEZE_RANDOM);
	Set_Disable_Sorting(props.Flags & W3D_ELINE_DISABLE_SORTING);
	Set_End_Caps(props.Flags & W3D_ELINE_END_CAPS);
	int texture_mode = ((props.Flags & W3D_ELINE_TEXTURE_MAP_MODE_MASK) >> W3D_ELINE_TEXTURE_MAP_MODE_OFFSET);
	switch (texture_mode)
	{
	case W3D_ELINE_UNIFORM_WIDTH_TEXTURE_MAP:
		Set_Texture_Mapping_Mode(UNIFORM_WIDTH_TEXTURE_MAP);
		break;
	case W3D_ELINE_UNIFORM_LENGTH_TEXTURE_MAP:
		Set_Texture_Mapping_Mode(UNIFORM_LENGTH_TEXTURE_MAP);
		break;
	case W3D_ELINE_TILED_TEXTURE_MAP:
		Set_Texture_Mapping_Mode(TILED_TEXTURE_MAP);
		break;
	};
	Set_Current_Subdivision_Level(props.SubdivisionLevel);
	Set_Noise_Amplitude(props.NoiseAmplitude);
	Set_Merge_Abort_Factor(props.MergeAbortFactor);
}
TextureClass * StreakRendererClass::Get_Texture(void) const
{
	if (Texture != NULL) {
		Texture->Add_Ref();
	}
	return Texture.Peek();
}
void StreakRendererClass::Render
(
	RenderInfoClass & rinfo,
	const Matrix3D & transform,
	unsigned int num_points,
	Vector3 * points,
	const SphereClass & obj_sphere
)
{
	return;
}
void StreakRendererClass::subdivision_util(unsigned int point_cnt, const Vector3 *xformed_pts,
	const float *base_tex_v, unsigned int *p_sub_point_cnt, Vector3 *xformed_subdiv_pts,
	float *subdiv_tex_v)
{
	struct StreakRendererRetailLayout {
		TextureClass *Texture;
		ShaderClass Shader;
		float Width;
		Vector3 Color;
		float Opacity;
		unsigned int SubdivisionLevel;
		float NoiseAmplitude;
		float MergeAbortFactor;
		float TextureTileFactor;
		unsigned int LastUsedSyncTime;
		Vector2 CurrentUVOffset;
		Vector2 UVOffsetDeltaPerMS;
		unsigned int Bits;
	};
	const StreakRendererRetailLayout *retail_this =
		reinterpret_cast<const StreakRendererRetailLayout *>(this);
	int freeze_random = retail_this->Bits & FREEZE_RANDOM;
	Random3Class randomize;
	const float oo_int_max = 1.0f / (float)INT_MAX;
	Vector3SolidBoxRandomizer randomizer(Vector3(1,1,1));
	Vector3 randvec(0,0,0);
	unsigned int sub_pointIndex = 0;
	struct StreakSubdivision {
		Vector3			StartPos;
		Vector3			EndPos;
		float				StartTexV;
		float				EndTexV;
		float				Rand;
		unsigned int	Level;
	};
	StreakSubdivision stack[2 * MAX_STREAK_SUBDIV_LEVELS];
	int tos = 0;
	for (unsigned int pointIndex = 0; pointIndex < point_cnt - 1; pointIndex++) {
		tos = 0;
		stack[0].StartPos = xformed_pts[pointIndex];
		stack[0].EndPos = xformed_pts[pointIndex + 1];
		stack[0].StartTexV = base_tex_v[pointIndex];
		stack[0].EndTexV = base_tex_v[pointIndex + 1];
		stack[0].Rand = NoiseAmplitude;
		stack[0].Level = 0;
		for (; tos >= 0;) {
			if (stack[tos].Level == SubdivisionLevel) {
				xformed_subdiv_pts[sub_pointIndex] = stack[tos].StartPos;
				subdiv_tex_v[sub_pointIndex++] = stack[tos].StartTexV;
				tos--;
			} else {
				if (freeze_random) {
					randvec.Set(randomize * oo_int_max, randomize * oo_int_max, randomize * oo_int_max);
				} else {
					randomizer.Get_Vector(randvec);
				}
				stack[tos + 1].StartPos = stack[tos].StartPos;
				stack[tos + 1].EndPos = (stack[tos].StartPos + stack[tos].EndPos) * 0.5f + randvec * stack[tos].Rand;
				stack[tos + 1].StartTexV = stack[tos].StartTexV;
				stack[tos + 1].EndTexV = (stack[tos].StartTexV + stack[tos].EndTexV) * 0.5f;
				stack[tos + 1].Rand = stack[tos].Rand * 0.5f;
				stack[tos + 1].Level = stack[tos].Level + 1;
				stack[tos].StartPos = stack[tos + 1].EndPos;
				stack[tos].StartTexV = stack[tos + 1].EndTexV;
				stack[tos].Rand = stack[tos + 1].Rand;
				stack[tos].Level = stack[tos + 1].Level;
				tos++;
			}
		}
	}
	xformed_subdiv_pts[sub_pointIndex] = xformed_pts[point_cnt - 1];
	subdiv_tex_v[sub_pointIndex++] = base_tex_v[point_cnt - 1];
	*p_sub_point_cnt = sub_pointIndex;
}
void StreakRendererClass::RenderStreak
(
	RenderInfoClass & rinfo,
	const Matrix3D & transform,
	unsigned int num_points,
	Vector3 * points,
	Vector4 * colors,
	float * widths,
	const SphereClass & obj_sphere,
	unsigned int *personalities
)
{
	Matrix4x4 view;
	DX8Wrapper::Get_Transform(D3DTS_VIEW,view);
	Matrix4x4 identity(true);
	DX8Wrapper::Set_Transform(D3DTS_WORLD,identity);
	DX8Wrapper::Set_Transform(D3DTS_VIEW,identity);
	unsigned int delta = WW3D::Get_Sync_Time() - LastUsedSyncTime;
	float del = (float)delta;
	Vector2 uv_offset = CurrentUVOffset + UVOffsetDeltaPerMS * del;
	uv_offset.X = uv_offset.X - floorf(uv_offset.X);
	uv_offset.Y = uv_offset.Y - floorf(uv_offset.Y);
	CurrentUVOffset = uv_offset;
	LastUsedSyncTime = WW3D::Get_Sync_Time();
	TextureMapMode map_mode = Get_Texture_Mapping_Mode();
	const float parallel_factor = 0.9f;
	unsigned int chunk_size = (STREAK_CHUNK_SIZE >> SubdivisionLevel) + 1;
	if (chunk_size > num_points) chunk_size = num_points;
	for (unsigned int chunkIndex = 0; chunkIndex < num_points - 1; chunkIndex += (chunk_size - 1))
	{
		unsigned int point_cnt = num_points - chunkIndex;
		point_cnt = MIN(point_cnt, chunk_size);
		unsigned int pointIndex;
		unsigned int segmentIndex;
		unsigned int intersectionIndex;
		Vector3 xformed_pts[MAX_STREAK_POINT_BUFFER_SIZE];
		Matrix3D view2(	view[0].X,view[0].Y,view[0].Z,view[0].W,
								view[1].X,view[1].Y,view[1].Z,view[1].W,
								view[2].X,view[2].Y,view[2].Z,view[2].W);
#ifdef ALLOW_TEMPORARIES
		Matrix3D modelview=view2*transform;
#else
		Matrix3D modelview=transform;
		modelview.preMul(view2);
#endif
		VectorProcessorClass::Transform(&xformed_pts[0],
			&points[chunkIndex], modelview, point_cnt);
		float base_tex_v[MAX_STREAK_POINT_BUFFER_SIZE];
		float u_values[2];
		switch (map_mode)
		{
			case UNIFORM_WIDTH_TEXTURE_MAP:
				for (pointIndex = 0; pointIndex < point_cnt; pointIndex++)
				{
					base_tex_v[pointIndex] = 0.0f;
				}
				u_values[0] = 0.0f;
				u_values[1] = 1.0f;
				break;
			case UNIFORM_LENGTH_TEXTURE_MAP:
				for (pointIndex = 0; pointIndex < point_cnt; pointIndex++)
				{
					base_tex_v[pointIndex] = (float)(pointIndex + chunkIndex) * TextureTileFactor;
				}
				u_values[0] = 0.0f;
				u_values[1] = 0.0f;
				break;
			case TILED_TEXTURE_MAP:
			default:
				for (pointIndex = 0; pointIndex < point_cnt; pointIndex++)
				{
					base_tex_v[pointIndex] = (float)(pointIndex + chunkIndex) * TextureTileFactor;
				}
				u_values[0] = 0.0f;
				u_values[1] = 1.0f;
				break;
		}
		Vector3 xformed_subdiv_pts[MAX_STREAK_POINT_BUFFER_SIZE];
		float subdiv_tex_v[MAX_STREAK_POINT_BUFFER_SIZE];
		unsigned int sub_point_cnt;
		subdivision_util(point_cnt, xformed_pts, base_tex_v, &sub_point_cnt, xformed_subdiv_pts, subdiv_tex_v);
		Vector3 *points = xformed_subdiv_pts;
		float *tex_v = subdiv_tex_v;
		point_cnt = sub_point_cnt;
		enum SegmentEdge
		{
			FIRST_EDGE     = 0,
			TOP_EDGE			= 0,
			BOTTOM_EDGE		= 1,
			MAX_EDGE			= 1,
			NUM_EDGES		= 2
		};
		bool switch_edges = false;
		struct LineSegment
		{
			Vector3	StartPlane;
			Vector3	EdgePlane[NUM_EDGES];
		};
		LineSegment segment[MAX_STREAK_POINT_BUFFER_SIZE + 1];
		struct LineSegmentIntersection
		{
			unsigned int	PointCount;
			unsigned int	NextSegmentID;
			Vector3			Direction;
			Vector3			Point;
			float				TexV;
			bool				Fold;
			bool				Parallel;
		};
		float radius = Width * 0.5f;
		LineSegmentIntersection intersection[MAX_STREAK_POINT_BUFFER_SIZE + 1][NUM_EDGES];
		for (segmentIndex = 1; segmentIndex < point_cnt; segmentIndex++)
		{
			radius = widths[segmentIndex];
			Vector3 &curr_point = points[segmentIndex - 1];
			Vector3 &next_point = points[segmentIndex];
			if (Equal_Within_Epsilon(curr_point, next_point, 0.0001f))
			{
				next_point.X += 0.001f;
			}
			Vector3 &segdir = segment[segmentIndex].StartPlane;
			segdir = next_point - curr_point;
			segdir.Normalize();
			Vector3 nearest = curr_point + segdir * -Vector3::Dot_Product(segdir, curr_point);
			Vector3 offset;
			Vector3::Cross_Product(segdir, nearest, &offset);
			offset.Normalize();
			Vector3 top = curr_point + offset * radius;
			Vector3 bottom = curr_point + offset * -radius;
			Vector3 top_normal;
			Vector3::Cross_Product(top, segdir, &top_normal);
			top_normal.Normalize();
			segment[segmentIndex].EdgePlane[TOP_EDGE] = top_normal;
			Vector3 bottom_normal;
			Vector3::Cross_Product(segdir, bottom, &bottom_normal);
			bottom_normal.Normalize();
			segment[segmentIndex].EdgePlane[BOTTOM_EDGE] = bottom_normal;
			if (segmentIndex > 1)
			{
				Vector3 prev_plane;
				Vector3::Cross_Product(points[segmentIndex - 2], curr_point, &prev_plane);
				prev_plane.Normalize();
				Vector3 curr_plane;
				Vector3::Cross_Product(curr_point, next_point, &curr_plane);
				curr_plane.Normalize();
				if (Vector3::Dot_Product(prev_plane, curr_plane) < 0.0f)
				{
					switch_edges = !switch_edges;
					intersection[segmentIndex][TOP_EDGE].Fold = true;
					intersection[segmentIndex][BOTTOM_EDGE].Fold = true;
				}
				else
				{
					intersection[segmentIndex][TOP_EDGE].Fold = false;
					intersection[segmentIndex][BOTTOM_EDGE].Fold = false;
				}
			}
			if (switch_edges)
			{
				segment[segmentIndex].EdgePlane[TOP_EDGE] = -bottom_normal;
				segment[segmentIndex].EdgePlane[BOTTOM_EDGE] = -top_normal;
			}
		}
		unsigned int numsegs = point_cnt - 1;
		unsigned int num_intersections[NUM_EDGES];
		num_intersections[TOP_EDGE] = point_cnt;
		num_intersections[BOTTOM_EDGE] = point_cnt;
		intersection[0][TOP_EDGE].PointCount = 0;
		intersection[0][TOP_EDGE].NextSegmentID = 0;
		intersection[0][TOP_EDGE].Direction.Set(1,0,0);
		intersection[0][TOP_EDGE].Point.Set(0,0,0);
		intersection[0][TOP_EDGE].TexV = 0.0f;
		intersection[0][TOP_EDGE].Fold = true;
		intersection[0][TOP_EDGE].Parallel = false;
		intersection[0][BOTTOM_EDGE].PointCount = 0;
		intersection[0][BOTTOM_EDGE].NextSegmentID = 0;
		intersection[0][BOTTOM_EDGE].Point.Set(0,0,0);
		intersection[0][BOTTOM_EDGE].TexV = 0.0f;
		intersection[0][BOTTOM_EDGE].Direction.Set(1,0,0);
		intersection[0][BOTTOM_EDGE].Fold = true;
		intersection[0][BOTTOM_EDGE].Parallel = false;
		intersection[1][TOP_EDGE].PointCount = 1;
		intersection[1][TOP_EDGE].NextSegmentID = 1;
		intersection[1][TOP_EDGE].Point = points[0];
		intersection[1][TOP_EDGE].TexV = tex_v[0];
		intersection[1][TOP_EDGE].Fold = true;
		intersection[1][TOP_EDGE].Parallel = false;
		intersection[1][BOTTOM_EDGE].PointCount = 1;
		intersection[1][BOTTOM_EDGE].NextSegmentID = 1;
		intersection[1][BOTTOM_EDGE].Point = points[0];
		intersection[1][BOTTOM_EDGE].TexV = tex_v[0];
		intersection[1][BOTTOM_EDGE].Fold = true;
		intersection[1][BOTTOM_EDGE].Parallel = false;
		Vector3 top;
		Vector3 bottom;
		Vector3 &first_point = points[0];
		Vector3 *first_plane = &(segment[1].EdgePlane[0]);
		top = first_point - first_plane[TOP_EDGE] * Vector3::Dot_Product(first_plane[TOP_EDGE], first_point);
		top.Normalize();
		intersection[1][TOP_EDGE].Direction = top;
		bottom = first_point - first_plane[BOTTOM_EDGE] * Vector3::Dot_Product(first_plane[BOTTOM_EDGE], first_point);
		bottom.Normalize();
		intersection[1][BOTTOM_EDGE].Direction = bottom;
		Vector3 segdir = points[1] - points[0];
		segdir.Normalize();
		Vector3 start_pl;
		Vector3::Cross_Product(top, bottom, &start_pl);
		start_pl.Normalize();
		float dp = Vector3::Dot_Product(segdir, start_pl);
		if (dp > 0.0f)
		{
			segment[0].StartPlane = segment[0].EdgePlane[TOP_EDGE] = segment[0].EdgePlane[BOTTOM_EDGE] = start_pl;
		}
		else
		{
			segment[0].StartPlane = segment[0].EdgePlane[TOP_EDGE] = segment[0].EdgePlane[BOTTOM_EDGE] = -start_pl;
		}
		segment[1].StartPlane = segment[0].StartPlane;
		unsigned int last_isec = num_intersections[TOP_EDGE];
		intersection[last_isec][TOP_EDGE].PointCount = 1;
		intersection[last_isec][TOP_EDGE].NextSegmentID = numsegs + 1;
		intersection[last_isec][TOP_EDGE].Point = points[point_cnt - 1];
		intersection[last_isec][TOP_EDGE].TexV = tex_v[point_cnt - 1];
		intersection[last_isec][TOP_EDGE].Fold = true;
		intersection[last_isec][TOP_EDGE].Parallel = false;
		intersection[last_isec][BOTTOM_EDGE].PointCount = 1;
		intersection[last_isec][BOTTOM_EDGE].NextSegmentID = numsegs + 1;
		intersection[last_isec][BOTTOM_EDGE].Point = points[point_cnt - 1];
		intersection[last_isec][BOTTOM_EDGE].TexV = tex_v[point_cnt - 1];
		intersection[last_isec][BOTTOM_EDGE].Fold = true;
		intersection[last_isec][BOTTOM_EDGE].Parallel = false;
		Vector3 &last_point = points[point_cnt - 1];
		Vector3 *last_plane = &(segment[numsegs].EdgePlane[0]);
		top = last_point - last_plane[TOP_EDGE] * Vector3::Dot_Product(last_plane[TOP_EDGE], last_point);
		top.Normalize();
		intersection[last_isec][TOP_EDGE].Direction = top;
		bottom = last_point - last_plane[BOTTOM_EDGE] * Vector3::Dot_Product(last_plane[BOTTOM_EDGE], last_point);
		bottom.Normalize();
		intersection[last_isec][BOTTOM_EDGE].Direction = bottom;
		segdir = points[point_cnt - 1] - points[point_cnt - 2];
		segdir.Normalize();
		Vector3::Cross_Product(top, bottom, &start_pl);
		start_pl.Normalize();
		dp = Vector3::Dot_Product(segdir, start_pl);
		if (dp > 0.0f)
		{
			segment[numsegs + 1].StartPlane = segment[numsegs + 1].EdgePlane[TOP_EDGE] =
				segment[numsegs + 1].EdgePlane[BOTTOM_EDGE] = start_pl;
		}
		else
		{
			segment[numsegs + 1].StartPlane = segment[numsegs + 1].EdgePlane[TOP_EDGE] =
				segment[numsegs + 1].EdgePlane[BOTTOM_EDGE] = -start_pl;
		}
		float vdp;
		for (intersectionIndex = 2; intersectionIndex < num_intersections[TOP_EDGE]; intersectionIndex++)
		{
			Vector3 &midpoint = points[intersectionIndex - 1];
			float mid_tex_v = tex_v[intersectionIndex - 1];
			intersection[intersectionIndex][TOP_EDGE].PointCount = 1;
			intersection[intersectionIndex][TOP_EDGE].NextSegmentID = intersectionIndex;
			intersection[intersectionIndex][TOP_EDGE].Point = midpoint;
			intersection[intersectionIndex][TOP_EDGE].TexV = mid_tex_v;
			intersection[intersectionIndex][BOTTOM_EDGE].PointCount = 1;
			intersection[intersectionIndex][BOTTOM_EDGE].NextSegmentID = intersectionIndex;
			intersection[intersectionIndex][BOTTOM_EDGE].Point = midpoint;
			intersection[intersectionIndex][BOTTOM_EDGE].TexV = mid_tex_v;
			vdp = Vector3::Dot_Product(segment[intersectionIndex - 1].EdgePlane[TOP_EDGE], segment[intersectionIndex].EdgePlane[TOP_EDGE]);
			if (fabs(vdp) < parallel_factor)
			{
				Vector3::Cross_Product(segment[intersectionIndex - 1].EdgePlane[TOP_EDGE], segment[intersectionIndex].EdgePlane[TOP_EDGE],
					&(intersection[intersectionIndex][TOP_EDGE].Direction));
				intersection[intersectionIndex][TOP_EDGE].Direction.Normalize();
				if (Vector3::Dot_Product(intersection[intersectionIndex][TOP_EDGE].Direction, midpoint) < 0.0f)
				{
					intersection[intersectionIndex][TOP_EDGE].Direction = -intersection[intersectionIndex][TOP_EDGE].Direction;
				}
				intersection[intersectionIndex][TOP_EDGE].Parallel = false;
			}
			else
			{
				Vector3 pl;
				if (vdp > 0.0f)
				{
					pl = segment[intersectionIndex - 1].EdgePlane[TOP_EDGE] + segment[intersectionIndex].EdgePlane[TOP_EDGE];
				}
				else
				{
					pl = segment[intersectionIndex - 1].EdgePlane[TOP_EDGE] - segment[intersectionIndex].EdgePlane[TOP_EDGE];
				}
				pl.Normalize();
				intersection[intersectionIndex][TOP_EDGE].Direction = midpoint - pl * Vector3::Dot_Product(pl, midpoint);
				intersection[intersectionIndex][TOP_EDGE].Direction.Normalize();
				intersection[intersectionIndex][TOP_EDGE].Parallel = true;
			}
			vdp = Vector3::Dot_Product(segment[intersectionIndex - 1].EdgePlane[BOTTOM_EDGE], segment[intersectionIndex].EdgePlane[BOTTOM_EDGE]);
			if (fabs(vdp) < parallel_factor)
			{
				Vector3::Cross_Product(segment[intersectionIndex - 1].EdgePlane[BOTTOM_EDGE], segment[intersectionIndex].EdgePlane[BOTTOM_EDGE],
					&(intersection[intersectionIndex][BOTTOM_EDGE].Direction));
				intersection[intersectionIndex][BOTTOM_EDGE].Direction.Normalize();
				if (Vector3::Dot_Product(intersection[intersectionIndex][BOTTOM_EDGE].Direction, midpoint) < 0.0f)
				{
					intersection[intersectionIndex][BOTTOM_EDGE].Direction = -intersection[intersectionIndex][BOTTOM_EDGE].Direction;
				}
				intersection[intersectionIndex][BOTTOM_EDGE].Parallel = false;
			}
			else
			{
				Vector3 pl;
				if (vdp > 0.0f)
				{
					pl = segment[intersectionIndex - 1].EdgePlane[BOTTOM_EDGE] + segment[intersectionIndex].EdgePlane[BOTTOM_EDGE];
				}
				else
				{
					pl = segment[intersectionIndex - 1].EdgePlane[BOTTOM_EDGE] - segment[intersectionIndex].EdgePlane[BOTTOM_EDGE];
				}
				pl.Normalize();
				intersection[intersectionIndex][BOTTOM_EDGE].Direction = midpoint - pl * Vector3::Dot_Product(pl, midpoint);
				intersection[intersectionIndex][BOTTOM_EDGE].Direction.Normalize();
				intersection[intersectionIndex][BOTTOM_EDGE].Parallel = true;
			}
			Vector3::Cross_Product(intersection[intersectionIndex][TOP_EDGE].Direction, intersection[intersectionIndex][BOTTOM_EDGE].Direction, &start_pl);
			start_pl.Normalize();
			dp = Vector3::Dot_Product(segment[intersectionIndex].StartPlane, start_pl);
			if (dp > 0.0f)
			{
				segment[intersectionIndex].StartPlane = start_pl;
			}
			else
			{
				segment[intersectionIndex].StartPlane = -start_pl;
			}
		}
		if (Is_Merge_Intersections())
		{
			unsigned int intersectionIndex_r;
			unsigned int intersectionIndex_w;
			bool merged = true;
			while (merged)
			{
				merged = false;
				SegmentEdge edge;
				for (edge = FIRST_EDGE; edge <= MAX_EDGE; edge = (SegmentEdge)((int)edge + 1))
				{
					unsigned int num_isects = num_intersections[edge];
					for (intersectionIndex_r = 1, intersectionIndex_w = 1; intersectionIndex_r < num_isects; intersectionIndex_r++, intersectionIndex_w++) {
						LineSegmentIntersection *curr_int = &(intersection[intersectionIndex_r][edge]);
						LineSegmentIntersection *next_int = &(intersection[intersectionIndex_r + 1][edge]);
						LineSegmentIntersection *write_int = &(intersection[intersectionIndex_w][edge]);
						LineSegmentIntersection *prev_int = &(intersection[intersectionIndex_w - 1][edge]);
						LineSegment *next_seg = &(segment[next_int->NextSegmentID]);
						LineSegment *curr_seg = &(segment[curr_int->NextSegmentID]);
						LineSegment *prev_seg = &(segment[prev_int->NextSegmentID]);
						while	(	(!next_int->Fold &&
										(Vector3::Dot_Product(curr_int->Direction, next_seg->StartPlane) > 0.0f) &&
										(Vector3::Dot_Product(curr_int->Direction, next_seg->EdgePlane[edge]) > 0.0f )) ||
									(!curr_int->Fold &&
										(Vector3::Dot_Product(next_int->Direction, -curr_seg->StartPlane) > 0.0f) &&
										(Vector3::Dot_Product(next_int->Direction, prev_seg->EdgePlane[edge]) > 0.0f )) )
						{
							unsigned int new_count = curr_int->PointCount + next_int->PointCount;
							float oo_new_count = 1.0f / (float)new_count;
							float curr_factor = oo_new_count * (float)curr_int->PointCount;
							float next_factor = oo_new_count * (float)curr_int->PointCount;
							Vector3 new_point = curr_int->Point * curr_factor + next_int->Point * next_factor;
							float new_tex_v = curr_int->TexV * curr_factor + next_int->TexV * next_factor;
							bool new_parallel;
							Vector3 new_direction;
							vdp = Vector3::Dot_Product(prev_seg->EdgePlane[edge], next_seg->EdgePlane[edge]);
							if (fabs(vdp) < parallel_factor)
							{
								Vector3::Cross_Product(prev_seg->EdgePlane[edge], next_seg->EdgePlane[edge], &new_direction);
								new_direction.Normalize();
								if (Vector3::Dot_Product(new_direction, new_point) < 0.0f)
								{
									new_direction = -new_direction;
								}
								new_parallel = false;
							}
							else
							{
								Vector3 pl;
								if (vdp > 0.0f)
								{
									pl = prev_seg->EdgePlane[edge] + next_seg->EdgePlane[edge];
								}
								else
								{
									pl = prev_seg->EdgePlane[edge] - next_seg->EdgePlane[edge];
								}
								pl.Normalize();
								if (curr_int->Parallel)
								{
									new_direction = curr_int->Direction - pl * Vector3::Dot_Product(pl, curr_int->Direction);
									new_direction.Normalize();
								}
								else
								{
									Vector3::Cross_Product(curr_seg->EdgePlane[edge], pl, &new_direction);
									new_direction.Normalize();
								}
								new_parallel = true;
							}
							if (MergeAbortFactor > 0.0f)
							{
								float abort_dist = radius * MergeAbortFactor;
								float abort_dist2 = abort_dist * abort_dist;
								Vector3 diff_curr = curr_int->Point -
									new_direction * Vector3::Dot_Product(curr_int->Point, new_direction);
								if (diff_curr.Length2() > abort_dist2) break;
								Vector3 next_curr = next_int->Point -
									new_direction * Vector3::Dot_Product(next_int->Point, new_direction);
								if (next_curr.Length2() > abort_dist2) break;
							}
							merged = true;
							curr_int->Direction = new_direction;
							curr_int->Parallel = new_parallel;
							curr_int->Point = new_point;
							curr_int->TexV = new_tex_v;
							curr_int->PointCount = new_count;
							curr_int->NextSegmentID = next_int->NextSegmentID;
							curr_int->Fold = curr_int->Fold || next_int->Fold;
							num_intersections[edge]--;
							intersectionIndex_r++;
							if (intersectionIndex_r == num_isects)
							{
								break;
							}
							next_int = &(intersection[intersectionIndex_r + 1][edge]);
							next_seg = &(segment[next_int->NextSegmentID]);
						}
						write_int->PointCount		= curr_int->PointCount;
						write_int->NextSegmentID	= curr_int->NextSegmentID;
						write_int->Point				= curr_int->Point;
						write_int->TexV				= curr_int->TexV;
						write_int->Direction			= curr_int->Direction;
						write_int->Fold				= curr_int->Fold;
					}
					if (intersectionIndex_r == num_isects)
					{
						LineSegmentIntersection *write_int = &(intersection[intersectionIndex_w][edge]);
						LineSegmentIntersection *curr_int = &(intersection[intersectionIndex_r][edge]);
						write_int->PointCount		= curr_int->PointCount;
						write_int->NextSegmentID	= curr_int->NextSegmentID;
						write_int->Point				= curr_int->Point;
						write_int->TexV				= curr_int->TexV;
						write_int->Direction			= curr_int->Direction;
						write_int->Fold				= curr_int->Fold;
					}
#ifdef ENABLE_WWDEBUGGING
					unsigned int total_cnt = 0;
					for (unsigned int nidx = 0; nidx <= num_intersections[edge]; nidx++)
					{
						total_cnt += intersection[nidx][edge].PointCount;
					}
					assert(total_cnt == point_cnt);
#endif
				}
			}
		}
		unsigned int vnum = num_intersections[TOP_EDGE] + num_intersections[BOTTOM_EDGE];
		VertexFormatXYZUV1 *vertexArray = getVertexBuffer(vnum);
		Vector3i v_index_array[MAX_STREAK_POLY_BUFFER_SIZE];
		unsigned int vertexIndex = 0;
		unsigned int triangleIndex = 0;
		Vector3 &top_dir = intersection[1][TOP_EDGE].Direction;
		top = top_dir * Vector3::Dot_Product(points[0], top_dir);
		Vector3 &bottom_dir = intersection[1][BOTTOM_EDGE].Direction;
		bottom = bottom_dir * Vector3::Dot_Product(points[0], bottom_dir);
		vertexArray[vertexIndex].x = top.X;
		vertexArray[vertexIndex].y = top.Y;
		vertexArray[vertexIndex].z = top.Z;
		vertexArray[vertexIndex].u1 = u_values[0] + uv_offset.X;
		vertexArray[vertexIndex].v1 = intersection[1][TOP_EDGE].TexV + uv_offset.Y;
		vertexIndex++;
		vertexArray[vertexIndex].x = bottom.X;
		vertexArray[vertexIndex].y = bottom.Y;
		vertexArray[vertexIndex].z = bottom.Z;
		vertexArray[vertexIndex].u1 = u_values[1] + uv_offset.X;
		vertexArray[vertexIndex].v1 = intersection[1][BOTTOM_EDGE].TexV + uv_offset.Y;
		vertexIndex++;
		unsigned int last_top_vertexIndex = 0;
		unsigned int last_bottom_vertexIndex = 1;
		unsigned int top_int_idx = 1;
		unsigned int bottom_int_idx = 1;
		pointIndex = 0;
		unsigned int residual_top_points = intersection[1][TOP_EDGE].PointCount;
		unsigned int residual_bottom_points = intersection[1][BOTTOM_EDGE].PointCount;
		unsigned int delta = MIN(residual_top_points, residual_bottom_points) - 1;
		residual_top_points -= delta;
		residual_bottom_points -= delta;
		pointIndex += delta;
		for (; ; )
		{
			if (residual_top_points == 1 && residual_bottom_points == 1)
			{
				v_index_array[triangleIndex].I = last_top_vertexIndex;
				v_index_array[triangleIndex].J = last_bottom_vertexIndex;
				v_index_array[triangleIndex].K = vertexIndex;
				triangleIndex++;
				v_index_array[triangleIndex].I = last_bottom_vertexIndex;
				v_index_array[triangleIndex].J = vertexIndex + 1;
				v_index_array[triangleIndex].K = vertexIndex;
				triangleIndex++;
				last_top_vertexIndex = vertexIndex;
				last_bottom_vertexIndex = vertexIndex + 1;
				top_int_idx++;
				bottom_int_idx++;
				residual_top_points = intersection[top_int_idx][TOP_EDGE].PointCount;
				residual_bottom_points = intersection[bottom_int_idx][BOTTOM_EDGE].PointCount;
				pointIndex++;
				Vector3 &top_dir = intersection[top_int_idx][TOP_EDGE].Direction;
				top = top_dir * Vector3::Dot_Product(points[pointIndex], top_dir);
				Vector3 &bottom_dir = intersection[bottom_int_idx][BOTTOM_EDGE].Direction;
				bottom = bottom_dir * Vector3::Dot_Product(points[pointIndex], bottom_dir);
				vertexArray[vertexIndex].x = top.X;
				vertexArray[vertexIndex].y = top.Y;
				vertexArray[vertexIndex].z = top.Z;
				vertexArray[vertexIndex].u1 = u_values[0] + uv_offset.X;
				vertexArray[vertexIndex].v1 = intersection[top_int_idx][TOP_EDGE].TexV + uv_offset.Y;
				vertexIndex++;
				vertexArray[vertexIndex].x = bottom.X;
				vertexArray[vertexIndex].y = bottom.Y;
				vertexArray[vertexIndex].z = bottom.Z;
				vertexArray[vertexIndex].u1 = u_values[1] + uv_offset.X;
				vertexArray[vertexIndex].v1 = intersection[bottom_int_idx][BOTTOM_EDGE].TexV + uv_offset.Y;
				vertexIndex++;
			}
			else
			{
				if (residual_top_points > 1)
				{
					v_index_array[triangleIndex].I = last_top_vertexIndex;
					v_index_array[triangleIndex].J = last_bottom_vertexIndex;
					v_index_array[triangleIndex].K = vertexIndex;
					triangleIndex++;
					last_bottom_vertexIndex = vertexIndex;
					residual_top_points--;
					bottom_int_idx++;
					residual_bottom_points = intersection[bottom_int_idx][BOTTOM_EDGE].PointCount;
					pointIndex++;
					Vector3 &bottom_dir = intersection[bottom_int_idx][BOTTOM_EDGE].Direction;
					bottom = bottom_dir * Vector3::Dot_Product(points[pointIndex], bottom_dir);
					vertexArray[vertexIndex].x = bottom.X;
					vertexArray[vertexIndex].y = bottom.Y;
					vertexArray[vertexIndex].z = bottom.Z;
					vertexArray[vertexIndex].u1 = u_values[1] + uv_offset.X;
					vertexArray[vertexIndex].v1 = intersection[bottom_int_idx][BOTTOM_EDGE].TexV + uv_offset.Y;
					vertexIndex++;
				}
				else
				{
					v_index_array[triangleIndex].I = last_top_vertexIndex;
					v_index_array[triangleIndex].J = last_bottom_vertexIndex;
					v_index_array[triangleIndex].K = vertexIndex;
					triangleIndex++;
					last_top_vertexIndex = vertexIndex;
					residual_bottom_points--;
					top_int_idx++;
					residual_top_points = intersection[top_int_idx][TOP_EDGE].PointCount;
					pointIndex++;
					Vector3 &top_dir = intersection[top_int_idx][TOP_EDGE].Direction;
					top = top_dir * Vector3::Dot_Product(points[pointIndex], top_dir);
					vertexArray[vertexIndex].x = top.X;
					vertexArray[vertexIndex].y = top.Y;
					vertexArray[vertexIndex].z = top.Z;
					vertexArray[vertexIndex].u1 = u_values[0] + uv_offset.X;
					vertexArray[vertexIndex].v1 = intersection[top_int_idx][TOP_EDGE].TexV + uv_offset.Y;
					vertexIndex++;
				}
			}
			delta = MIN(residual_top_points, residual_bottom_points) - 1;
			residual_top_points -= delta;
			residual_bottom_points -= delta;
			pointIndex += delta;
			if (	(top_int_idx >= num_intersections[TOP_EDGE] && residual_top_points == 1) ||
					(bottom_int_idx >= num_intersections[BOTTOM_EDGE] && residual_bottom_points == 1))
			{
				assert(top_int_idx == num_intersections[TOP_EDGE]);
				assert(bottom_int_idx == num_intersections[BOTTOM_EDGE]);
				assert(pointIndex == point_cnt - 1);
				break;
			}
		}
		bool sorting = (!Is_Sorting_Disabled()) && (Shader.Get_Dst_Blend_Func() != ShaderClass::DSTBLEND_ZERO && Shader.Get_Alpha_Test() == ShaderClass::ALPHATEST_DISABLE);
		ShaderClass shader = Shader;
		shader.Set_Cull_Mode(ShaderClass::CULL_MODE_DISABLE);
		shader.Set_Primary_Gradient(ShaderClass::GRADIENT_MODULATE);
		VertexMaterialClass *mat;
		mat=VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_DIFFUSE);
		DX8Wrapper::Set_Material(mat);
		REF_PTR_RELEASE(mat);
		if (Texture)
		{
			shader.Set_Texturing(ShaderClass::TEXTURING_ENABLE);
		}
		else
		{
			shader.Set_Texturing(ShaderClass::TEXTURING_DISABLE);
		}
		DynamicVBAccessClass Verts((sorting?BUFFER_TYPE_DYNAMIC_SORTING:BUFFER_TYPE_DYNAMIC_DX8),5,vnum,0);
		{
			DynamicVBAccessClass::WriteLock Lock(&Verts);
			unsigned int i;
			unsigned char *vb=(unsigned char*)Lock.Get_Formatted_Vertex_Array();
			const FVFInfoClass& fvfinfo=Verts.FVF_Info();
			int segIdx = 0;
			unsigned int argb = 0x00000000;
			unsigned int oddEven = 0;
			const unsigned verticesOffset = fvfinfo.Get_Location_Offset();
			const unsigned diffuseOffset = fvfinfo.Get_Diffuse_Offset();
			const unsigned textureOffset = fvfinfo.Get_Tex_Offset(0);
			const unsigned vbSize = fvfinfo.Get_FVF_Size();
			for (i=0; i<vnum; i++)
			{
				DEBUG_ASSERTCRASH(vertexArray[i].x != (float)0xdeadbeef && vertexArray[i].y != (float)0xdeadbeef && vertexArray[i].z != (float)0xdeadbeef && vertexArray[i].u1 != (float)0xdeadbeeef && vertexArray[i].v1 != (float)0xdeadbeef, ("Uninitialized vertexArray[%d]", i));
				DEBUG_ASSERTCRASH((! _isnan(vertexArray[i].x) && _finite(vertexArray[i].x) && ! _isnan(vertexArray[i].y) && _finite(vertexArray[i].y) && ! _isnan(vertexArray[i].z) && _finite(vertexArray[i].z)) , ("Bad vertexArray[%d]", i));
				Vector3 *vertex = reinterpret_cast<Vector3 *>(vb + verticesOffset);
				vertex->X = vertexArray[i].x;
				vertex->Y = vertexArray[i].y;
				vertex->Z = vertexArray[i].z;
				*reinterpret_cast<unsigned int *>(vb + diffuseOffset) = DX8Wrapper::Convert_Color_Clamp(colors[MIN((i/2), point_cnt)]);
				Vector2 *texture = reinterpret_cast<Vector2 *>(vb + textureOffset);
				texture->U = vertexArray[i].u1;
				texture->V = vertexArray[i].v1;
				vb += vbSize;
			}
		}
		DynamicIBAccessClass ib_access((sorting?BUFFER_TYPE_DYNAMIC_SORTING:BUFFER_TYPE_DYNAMIC_DX8),triangleIndex*3);
		{
			unsigned int i;
			DynamicIBAccessClass::WriteLockClass lock(&ib_access);
			unsigned short* inds=lock.Get_Index_Array();
			for (i=0; i<triangleIndex; i++)
			{
				*inds++=v_index_array[i].I;
				*inds++=v_index_array[i].J;
				*inds++=v_index_array[i].K;
			}
		}
		DX8Wrapper::Set_Index_Buffer(ib_access,0);
		DX8Wrapper::Set_Vertex_Buffer(Verts);
		BFME2Set_Texture(0,reinterpret_cast<const BFME2TextureRef&>(Texture));
		DX8Wrapper::Set_Shader(shader);
		if (sorting)
		{
			BfmeSortingDispatchAt0012FE00::Insert(reinterpret_cast<const TargetCenter3&>(obj_sphere),0,triangleIndex,0,vnum);
		}
		else
		{
			DX8Wrapper::Draw_Triangles(0,triangleIndex,0,vnum);
		}
	}
	if(0){StringClass unused;}
	DX8Wrapper::Set_Transform(D3DTS_VIEW,view);
}
VertexFormatXYZUV1 *StreakRendererClass::getVertexBuffer(unsigned int number)
{
	if (number > m_vertexBufferSize)
	{
		unsigned int numberToAlloc = number + (number >> 1);
	  delete [] m_vertexBuffer;
		m_vertexBuffer = W3DNEWARRAY VertexFormatXYZUV1[numberToAlloc];
		m_vertexBufferSize = numberToAlloc;
	}
#ifdef _INTERNAL
	for (unsigned i = 0; i < number; ++i)
	{
	  m_vertexBuffer[i].x = m_vertexBuffer[i].y = m_vertexBuffer[i].z = m_vertexBuffer[i].u1 = m_vertexBuffer[i].v1 = (float)0xdeadbeef;
	}
#endif
	return m_vertexBuffer;
}
#pragma comment(linker, "/alternatename:??1MaterialPassStage@@QAE@XZ=??1?$RefCountPtr@VTextureClass@@@@QAE@XZ")
#pragma comment(linker, "/alternatename:??1TextureClassPtr@@QAE@XZ=??1?$RefCountPtr@VTextureClass@@@@QAE@XZ")
#pragma comment(linker, "/alternatename:??1BfmeElemBY@@QAE@XZ=??1?$RefCountPtr@VTextureClass@@@@QAE@XZ")
#pragma comment(linker, "/alternatename:??1BfmeElemVVE@@QAE@XZ=??1?$RefCountPtr@VTextureClass@@@@QAE@XZ")
#pragma comment(linker, "/alternatename:?rva00906340CellDtor@@YAXPAX@Z=??1?$RefCountPtr@VTextureClass@@@@QAE@XZ")
#pragma comment(linker, "/alternatename:??1BfmeElementA@@QAE@XZ=??1?$RefCountPtr@VTextureClass@@@@QAE@XZ")
#pragma comment(linker, "/alternatename:?bfmeElem936B@@YGXPAX@Z=??1?$RefCountPtr@VTextureClass@@@@QAE@XZ")
