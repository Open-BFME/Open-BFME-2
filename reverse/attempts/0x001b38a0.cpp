// ?Render@LineGroupClass@@QAEXAAVRenderInfoClass@@@Z
// partial score=0.8 date=2026-10-07
// cl: /O2 /arch:SSE -DBFME_WWSTRING_NATIVE_CSTR_ASSIGN -Ireference/shims/wwstring_teardown/bfme -G7 -Ireference/shims/bfmerendobj -DNDEBUG -MD -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDownload -Ireference/open-bfme-1/game/Libraries/Source/Compression -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug -Ireference/shims/sweep -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDownload -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug -Ireference/open-bfme-1/game/Libraries/Source/Compression -Ireference/shims/sweep
// Banked render: 4371B retail boundary ends at 0x001B49B3.
// Required deltas: 24B vertex access/four arguments, both locks12B, gradient6,
// no index catch, owning texture reference and four DWORD draw/center ranges.
// Remaining: frame0x118 vs0x10C, SSE register/stack allocation; not a recovery.
// Ported verbatim from the Generals Zero Hour reference
// (Libraries/Source/WWVegas/WW3D2/linegrp.cpp); this unit had no counterpart under Code/.
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/***********************************************************************************************
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : Linegroup.cpp                                                *
 *                                                                                             *
 *                     $Archive::                                                             $*
 *                                                                                             *
 *              Original Author:: Hector Yee                                                   *
 *                                                                                             *
 *                      $Author:: Kenny Mitchell                                               * 
 *                                                                                             * 
 *                     $Modtime:: 06/26/02 4:04p                                             $*
 *                                                                                             *
 *                    $Revision:: 2                                                            $*
 *                                                                                             *
 * 06/26/02 KM Matrix name change to avoid MAX conflicts                                       *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include "sharebuf.h"
#include "linegrp.h"
#include "texture.h"
#include "vertmaterial.h"

// Isolated BFME2 ABI views for this bank; reference inputs 1399ad37.
#include <d3d8.h>

// Adapted dx8vertexbuffer.h (GPL-3.0-or-later).
 
#if defined(_MSC_VER)

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


// Adapted dx8indexbuffer.h (GPL-3.0-or-later).
 
#if defined(_MSC_VER)

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


// Adapted dx8wrapper.h (GPL-3.0-or-later).
 
#if defined(_MSC_VER)

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
const unsigned MAX_TEXTURE_STAGES=8;
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
WWINLINE void DX8_ErrorCode(unsigned res)
{
	if (res==D3D_OK) return;
	Log_DX8_ErrorCode(res);
}
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
class DX8Wrapper
{
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
	static void Draw_Sorting_IB_VB(
		unsigned primitive_type,
		unsigned short start_index,
		unsigned short polygon_count,
		unsigned short min_vertex_index,
		unsigned short vertex_count);
	static void Draw(
		unsigned primitive_type,
		unsigned short start_index,
		unsigned short polygon_count,
		unsigned short min_vertex_index=0,
		unsigned short vertex_count=0);
public:
#ifdef EXTENDED_STATS
	static DX8_Stats stats;
#endif
	static bool Init(void * hwnd, bool lite = false);
	static void Shutdown(void);
	static void SetCleanupHook(DX8_CleanupHook *pCleanupHook) {m_pCleanupHook = pCleanupHook;};
	static void	Do_Onetime_Device_Dependent_Inits(void);
	static void Do_Onetime_Device_Dependent_Shutdowns(void);
	static bool Is_Device_Lost() { return IsDeviceLost; }
	static bool Is_Initted(void) { return IsInitted; }
	static bool Has_Stencil (void);
	static void Get_Format_Name(unsigned int format, StringClass *tex_format);
	static void Begin_Scene(void);
	static void End_Scene(bool flip_frame = true);
	static void Flip_To_Primary(void);
	static void Clear(bool clear_color, bool clear_z_stencil, const Vector3 &color, float dest_alpha=0.0f, float z=1.0f, unsigned int stencil=0);
	static void	Set_Viewport(CONST D3DVIEWPORT8* pViewport);
	static void Set_Vertex_Buffer(const VertexBufferClass* vb, unsigned stream=0);
	static void Set_Vertex_Buffer(const DynamicVBAccessClass& vba);
	static void Set_Index_Buffer(const IndexBufferClass* ib,unsigned short index_base_offset);
	static void Set_Index_Buffer(const DynamicIBAccessClass& iba,unsigned short index_base_offset);
	static void Set_Index_Buffer_Index_Offset(unsigned offset);
	static void Get_Render_State(RenderStateStruct& state);
	static void Set_Render_State(const RenderStateStruct& state);
	static void Release_Render_State();
	static void Set_DX8_Material(const D3DMATERIAL8* mat);
	static void Set_Gamma(float gamma,float bright,float contrast,bool calibrate=true,bool uselimit=true);
	static void Set_DX8_ZBias(int zbias);
	static void Set_Projection_Transform_With_Z_Bias(const Matrix4x4& matrix,float znear, float zfar);	 
	static void Set_Transform(D3DTRANSFORMSTATETYPE transform,const Matrix4x4& m);
	static void Set_Transform(D3DTRANSFORMSTATETYPE transform,const Matrix3D& m);
	static void Get_Transform(D3DTRANSFORMSTATETYPE transform, Matrix4x4& m);
	static void	Set_World_Identity();
	static void Set_View_Identity();
	static bool	Is_World_Identity();
	static bool Is_View_Identity();
	static void _Set_DX8_Transform(D3DTRANSFORMSTATETYPE transform,const Matrix4x4& m);
	static void _Set_DX8_Transform(D3DTRANSFORMSTATETYPE transform,const Matrix3D& m);
	static void _Get_DX8_Transform(D3DTRANSFORMSTATETYPE transform, Matrix4x4& m);
	static void Set_DX8_Light(int index,D3DLIGHT8* light);
	static void Set_DX8_Render_State(D3DRENDERSTATETYPE state, unsigned value);
	static void Set_DX8_Clip_Plane(DWORD Index, CONST float* pPlane);
	static void Set_DX8_Texture_Stage_State(unsigned stage, D3DTEXTURESTAGESTATETYPE state, unsigned value);
	static void Set_DX8_Texture_Stage_State_Body(unsigned stage, D3DTEXTURESTAGESTATETYPE state, unsigned value);
	static void Set_DX8_Texture(unsigned int stage, IDirect3DBaseTexture8* texture);
	static void Set_Light_Environment(LightEnvironmentClass* light_env);
	static LightEnvironmentClass* Get_Light_Environment() { return Light_Environment; }
	static void Set_Fog(bool enable, const Vector3 &color, float start, float end);
	static WWINLINE const D3DLIGHT8& Peek_Light(unsigned index);
	static WWINLINE bool Is_Light_Enabled(unsigned index);
	static bool Validate_Device(void);
	static void Set_Shader(const ShaderClass& shader);
	static void Get_Shader(ShaderClass& shader);
	static void Set_Texture(unsigned stage,TextureBaseClass* texture);
	static void Set_Material(const VertexMaterialClass* material);
	static void Set_Light(unsigned index,const D3DLIGHT8* light);
	static void Set_Light(unsigned index,const LightClass &light);
	static void Apply_Render_State_Changes();	 
	static void Draw_Triangles(
		unsigned buffer_type,
		unsigned short start_index,
		unsigned short polygon_count,
		unsigned short min_vertex_index,
		unsigned short vertex_count);
	static void Draw_Triangles(
		unsigned start_index,
		unsigned polygon_count,
		unsigned min_vertex_index,
		unsigned vertex_count);
	static void Draw_Strip(
		unsigned short start_index,
		unsigned short index_count,
		unsigned short min_vertex_index,
		unsigned short vertex_count);
	static IDirect3DVolumeTexture8* _Create_DX8_Volume_Texture
	(
		unsigned int width,
		unsigned int height,
		unsigned int depth,
		WW3DFormat format,
		MipCountType mip_level_count,
		D3DPOOL pool=D3DPOOL_MANAGED
	);
	static IDirect3DCubeTexture8* _Create_DX8_Cube_Texture
	(
		unsigned int width,
		unsigned int height,
		WW3DFormat format,
		MipCountType mip_level_count,
		D3DPOOL pool=D3DPOOL_MANAGED,
		bool rendertarget=false
	);
	static IDirect3DTexture8* _Create_DX8_ZTexture
	(
		unsigned int width,
		unsigned int height,
		WW3DZFormat zformat,
		MipCountType mip_level_count,
		D3DPOOL pool=D3DPOOL_MANAGED
	);
	static IDirect3DTexture8 * _Create_DX8_Texture
	(
		unsigned int width,
		unsigned int height,
		WW3DFormat format,
		MipCountType mip_level_count,
		D3DPOOL pool=D3DPOOL_MANAGED,
		bool rendertarget=false
	);
	static IDirect3DTexture8 * _Create_DX8_Texture(const char *filename, MipCountType mip_level_count);
	static IDirect3DTexture8 * _Create_DX8_Texture(IDirect3DSurface8 *surface, MipCountType mip_level_count);
	static IDirect3DSurface8 * _Create_DX8_Surface(unsigned int width, unsigned int height, WW3DFormat format);
	static IDirect3DSurface8 * _Create_DX8_Surface(const char *filename);
	static IDirect3DSurface8 * _Get_DX8_Front_Buffer();
	static SurfaceClass * _Get_DX8_Back_Buffer(unsigned int num=0);
	static void _Copy_DX8_Rects(
			IDirect3DSurface8* pSourceSurface,
			CONST RECT* pSourceRectsArray,
			UINT cRects,
			IDirect3DSurface8* pDestinationSurface,
			CONST POINT* pDestPointsArray
	);
	static void _Update_Texture(TextureClass *system, TextureClass *video);
	static void Flush_DX8_Resource_Manager(unsigned int bytes=0);
	static unsigned int Get_Free_Texture_RAM();
	static unsigned _Get_Main_Thread_ID() { return _MainThreadID; }
	static const D3DADAPTER_IDENTIFIER8& Get_Current_Adapter_Identifier() { return CurrentAdapterIdentifier; }
	static void Begin_Statistics();
	static void End_Statistics();
	static unsigned Get_Last_Frame_Matrix_Changes();
	static unsigned Get_Last_Frame_Material_Changes();
	static unsigned Get_Last_Frame_Vertex_Buffer_Changes();
	static unsigned Get_Last_Frame_Index_Buffer_Changes();
	static unsigned Get_Last_Frame_Light_Changes();
	static unsigned Get_Last_Frame_Texture_Changes();
	static unsigned Get_Last_Frame_Render_State_Changes();
	static unsigned Get_Last_Frame_Texture_Stage_State_Changes();
	static unsigned Get_Last_Frame_DX8_Calls();
	static unsigned Get_Last_Frame_Draw_Calls();
	static unsigned long Get_FrameCount(void);
	static bool						Get_Fog_Enable() { return FogEnable; }
	static D3DCOLOR				Get_Fog_Color() { return FogColor; }
	static Vector4 Convert_Color(unsigned color);
	static unsigned int Convert_Color(const Vector4& color);
	static unsigned int Convert_Color(const Vector3& color, const float alpha);
	static void Clamp_Color(Vector4& color);
	static unsigned int Convert_Color_Clamp(const Vector4& color);
	static void			  Set_Alpha (const float alpha, unsigned int &color);
	static void _Enable_Triangle_Draw(bool enable) { _EnableTriangleDraw=enable; }
	static bool _Is_Triangle_Draw_Enabled() { return _EnableTriangleDraw; }
	static IDirect3DSwapChain8 *	Create_Additional_Swap_Chain (HWND render_window);
	static TextureClass *	Create_Render_Target (int width, int height, WW3DFormat format = WW3D_FORMAT_UNKNOWN);
	static void					Set_Render_Target (IDirect3DSurface8 *render_target, bool use_default_depth_buffer = false);
	static void					Set_Render_Target (IDirect3DSurface8* render_target, IDirect3DSurface8* dpeth_buffer);
	static void					Set_Render_Target (IDirect3DSwapChain8 *swap_chain);
	static bool					Is_Render_To_Texture(void) { return IsRenderToTexture; }
	static void Create_Render_Target
	(
		int width, 
		int height, 
		WW3DFormat format,
		WW3DZFormat zformat,
		TextureClass** target,
		ZTextureClass** depth_buffer
	);
	static void					Set_Render_Target_With_Z (TextureClass * texture, ZTextureClass* ztexture=NULL);
	static void Set_Shadow_Map(int idx, ZTextureClass* ztex) { Shadow_Map[idx]=ztex; }
	static ZTextureClass* Get_Shadow_Map(int idx) { return Shadow_Map[idx]; }
	static void Apply_Default_State();
	static void Set_Vertex_Shader(DWORD vertex_shader);
	static void Set_Pixel_Shader(DWORD pixel_shader);
	static void Set_Vertex_Shader_Constant(int reg, const void* data, int count);
	static void Set_Pixel_Shader_Constant(int reg, const void* data, int count);
	static DWORD Get_Vertex_Processing_Behavior() { return Vertex_Processing_Behavior; }
	static void						Set_Ambient(const Vector3& color);
	static const Vector3&		Get_Ambient() { return Ambient_Color; }
	static IDirect3DDevice8* _Get_D3D_Device8() { return D3DDevice; }
	static IDirect3D8* _Get_D3D8() { return D3DInterface; }
	static WW3DFormat	getBackBufferFormat( void );
	static bool Reset_Device(bool reload_assets=true);
	static const DX8Caps*	Get_Current_Caps() { WWASSERT(CurrentCaps); return CurrentCaps; }
	static bool Registry_Save_Render_Device( const char * sub_key );
	static bool Registry_Load_Render_Device( const char * sub_key, bool resize_window );
	static const char* Get_DX8_Render_State_Name(D3DRENDERSTATETYPE state);
	static const char* Get_DX8_Texture_Stage_State_Name(D3DTEXTURESTAGESTATETYPE state);
	static unsigned Get_DX8_Render_State(D3DRENDERSTATETYPE state) { return RenderStates[state]; }
	static void Get_DX8_Texture_Stage_State_Value_Name(StringClass& name, D3DTEXTURESTAGESTATETYPE state, unsigned value);
	static void Get_DX8_Render_State_Value_Name(StringClass& name, D3DRENDERSTATETYPE state, unsigned value);
	static const char* Get_DX8_Texture_Address_Name(unsigned value);
	static const char* Get_DX8_Texture_Filter_Name(unsigned value);
	static const char* Get_DX8_Texture_Arg_Name(unsigned value);
	static const char* Get_DX8_Texture_Op_Name(unsigned value);
	static const char* Get_DX8_Texture_Transform_Flag_Name(unsigned value);
	static const char* Get_DX8_ZBuffer_Type_Name(unsigned value);
	static const char* Get_DX8_Fill_Mode_Name(unsigned value);
	static const char* Get_DX8_Shade_Mode_Name(unsigned value);
	static const char* Get_DX8_Blend_Name(unsigned value);
	static const char* Get_DX8_Cull_Mode_Name(unsigned value);
	static const char* Get_DX8_Cmp_Func_Name(unsigned value);
	static const char* Get_DX8_Fog_Mode_Name(unsigned value);
	static const char* Get_DX8_Stencil_Op_Name(unsigned value);
	static const char* Get_DX8_Material_Source_Name(unsigned value);
	static const char* Get_DX8_Vertex_Blend_Flag_Name(unsigned value);
	static const char* Get_DX8_Patch_Edge_Style_Name(unsigned value);
	static const char* Get_DX8_Debug_Monitor_Token_Name(unsigned value);
	static const char* Get_DX8_Blend_Op_Name(unsigned value);
	static void Invalidate_Cached_Render_States(void);
	static void Set_Draw_Polygon_Low_Bound_Limit(unsigned n) { DrawPolygonLowBoundLimit=n; }
protected:
	static bool	Create_Device(void);
	static void Release_Device(void);
	static void Reset_Statistics();
	static void Enumerate_Devices();
	static void Set_Default_Global_Render_States(void);
	static bool Set_Any_Render_Device(void);
	static bool	Set_Render_Device(const char * dev_name,int width=-1,int height=-1,int bits=-1,int windowed=-1,bool resize_window=false);
	static bool	Set_Render_Device(int dev=-1,int resx=-1,int resy=-1,int bits=-1,int windowed=-1,bool resize_window = false, bool reset_device = false, bool restore_assets=true);
	static bool Set_Next_Render_Device(void);
	static bool Toggle_Windowed(void);
	static int	Get_Render_Device_Count(void);
	static int	Get_Render_Device(void);
	static const RenderDeviceDescClass & Get_Render_Device_Desc(int deviceidx);
	static const char * Get_Render_Device_Name(int device_index);
	static bool Set_Device_Resolution(int width=-1,int height=-1,int bits=-1,int windowed=-1, bool resize_window=false);
	static void Get_Device_Resolution(int & set_w,int & set_h,int & set_bits,bool & set_windowed);
	static void Get_Render_Target_Resolution(int & set_w,int & set_h,int & set_bits,bool & set_windowed);
	static int	Get_Device_Resolution_Width(void) { return ResolutionWidth; }
	static int	Get_Device_Resolution_Height(void) { return ResolutionHeight; }
	static bool Registry_Save_Render_Device( const char *sub_key, int device, int width, int height, int depth, bool windowed, int texture_depth);
	static bool Registry_Load_Render_Device( const char * sub_key, char *device, int device_len, int &width, int &height, int &depth, int &windowed, int &texture_depth);
	static bool Is_Windowed(void) { return IsWindowed; }
	static void	Set_Texture_Bitdepth(int depth)	{ WWASSERT(depth==16 || depth==32); TextureBitDepth = depth; }
	static int	Get_Texture_Bitdepth(void)			{ return TextureBitDepth; }
	static void	Set_Swap_Interval(int swap);
	static int	Get_Swap_Interval(void);
	static void Set_Polygon_Mode(int mode);
	static bool Find_Color_And_Z_Mode(int resx,int resy,int bitdepth,D3DFORMAT * set_colorbuffer,D3DFORMAT * set_backbuffer, D3DFORMAT * set_zmode);
	static bool Find_Color_Mode(D3DFORMAT colorbuffer, int resx, int resy, UINT *mode);
	static bool Find_Z_Mode(D3DFORMAT colorbuffer,D3DFORMAT backbuffer, D3DFORMAT *zmode);
	static bool Test_Z_Mode(D3DFORMAT colorbuffer,D3DFORMAT backbuffer, D3DFORMAT zmode);
	static void Compute_Caps(WW3DFormat display_format);
	static DX8_CleanupHook *m_pCleanupHook;
	static RenderStateStruct			render_state;
	static unsigned						render_state_changed;
	static Matrix4x4						DX8Transforms[D3DTS_WORLD+1];
	static bool								IsInitted;
	static bool								IsDeviceLost;
	static void *							Hwnd;
	static unsigned						_MainThreadID;
	static bool								_EnableTriangleDraw;
	static int								CurRenderDevice;
	static int								ResolutionWidth;
	static int								ResolutionHeight;
	static int								BitDepth;
	static int								TextureBitDepth;
	static bool								IsWindowed;
	static D3DFORMAT					DisplayFormat;
	static D3DMATRIX						old_world;
	static D3DMATRIX						old_view;
	static D3DMATRIX						old_prj;
	static DWORD							Vertex_Shader;
	static DWORD							Pixel_Shader;
	static Vector4							Vertex_Shader_Constants[MAX_VERTEX_SHADER_CONSTANTS];
	static Vector4							Pixel_Shader_Constants[MAX_PIXEL_SHADER_CONSTANTS];
	static LightEnvironmentClass*		Light_Environment;
	static RenderInfoClass*				Render_Info;
	static DWORD							Vertex_Processing_Behavior;
	static ZTextureClass*				Shadow_Map[MAX_SHADOW_MAPS];
	static Vector3							Ambient_Color;
	static bool								world_identity;
	static unsigned						RenderStates[256];
	static unsigned						TextureStageStates[MAX_TEXTURE_STAGES][32];
	static IDirect3DBaseTexture8 *	Textures[MAX_TEXTURE_STAGES];
	static bool								FogEnable;
	static D3DCOLOR						FogColor;
	static unsigned						matrix_changes;
	static unsigned						material_changes;
	static unsigned						vertex_buffer_changes;
	static unsigned						index_buffer_changes;
	static unsigned						light_changes;
	static unsigned						texture_changes;
	static unsigned						render_state_changes;
	static unsigned						texture_stage_state_changes;
	static unsigned						draw_calls;
	static bool								CurrentDX8LightEnables[4];
	static unsigned long FrameCount;
	static DX8Caps*						CurrentCaps;
	static D3DADAPTER_IDENTIFIER8		CurrentAdapterIdentifier;
	static IDirect3D8 *					D3DInterface;			 
	static IDirect3DDevice8 *			D3DDevice;				 
	static IDirect3DSurface8 *			CurrentRenderTarget;
	static IDirect3DSurface8 *			CurrentDepthBuffer;
	static IDirect3DSurface8 *			DefaultRenderTarget;
	static IDirect3DSurface8 *			DefaultDepthBuffer;
	static unsigned							DrawPolygonLowBoundLimit;
	static bool								IsRenderToTexture;
	static int								ZBias;
	static float							ZNear;
	static float							ZFar;
	static Matrix4x4						ProjectionMatrix;
	friend void DX8_Assert();
	friend class WW3D;
	friend class DX8IndexBufferClass;
	friend class DX8VertexBufferClass;
};
WWINLINE void DX8Wrapper::Set_Vertex_Shader(DWORD vertex_shader)
{
#if 0  
	if (Vertex_Shader==vertex_shader) return;
#endif
	Vertex_Shader=vertex_shader;
	DX8CALL(SetVertexShader(Vertex_Shader));
}
WWINLINE void DX8Wrapper::Set_Pixel_Shader(DWORD pixel_shader)
{
	if (Pixel_Shader==pixel_shader) return;
	Pixel_Shader=pixel_shader;
	DX8CALL(SetPixelShader(Pixel_Shader));
}
WWINLINE void DX8Wrapper::Set_Vertex_Shader_Constant(int reg, const void* data, int count)
{
	int memsize=sizeof(Vector4)*count;
	if (memcmp(data, &Vertex_Shader_Constants[reg],memsize)==0) return;
	memcpy(&Vertex_Shader_Constants[reg],data,memsize);
	DX8CALL(SetVertexShaderConstant(reg,data,count));
}
WWINLINE void DX8Wrapper::Set_Pixel_Shader_Constant(int reg, const void* data, int count)
{
	int memsize=sizeof(Vector4)*count;
	if (memcmp(data, &Pixel_Shader_Constants[reg],memsize)==0) return;
	memcpy(&Pixel_Shader_Constants[reg],data,memsize);
	DX8CALL(SetPixelShaderConstant(reg,data,count));
}
WWINLINE void DX8Wrapper::_Set_DX8_Transform(D3DTRANSFORMSTATETYPE transform,const Matrix4x4& m)
{
	WWASSERT(transform<=D3DTS_WORLD);
#if 0  
	if (m!=DX8Transforms[transform]) 
#endif
	{
		DX8Transforms[transform]=m;
		SNAPSHOT_SAY(("DX8 - SetTransform %d [%f,%f,%f,%f][%f,%f,%f,%f][%f,%f,%f,%f][%f,%f,%f,%f]\n",transform,m[0][0],m[0][1],m[0][2],m[0][3],m[1][0],m[1][1],m[1][2],m[1][3],m[2][0],m[2][1],m[2][2],m[2][3],m[3][0],m[3][1],m[3][2],m[3][3]));
		DX8_RECORD_MATRIX_CHANGE();
		DX8CALL(SetTransform(transform,(D3DMATRIX*)&m));
	}
}
WWINLINE void DX8Wrapper::_Set_DX8_Transform(D3DTRANSFORMSTATETYPE transform,const Matrix3D& m)
{
	WWASSERT(transform<=D3DTS_WORLD);
	Matrix4x4 mtx(m);
#if 0  
	if (mtx!=DX8Transforms[transform]) 
#endif
	{
		DX8Transforms[transform]=mtx;
		SNAPSHOT_SAY(("DX8 - SetTransform %d [%f,%f,%f,%f][%f,%f,%f,%f][%f,%f,%f,%f]\n",transform,m[0][0],m[0][1],m[0][2],m[0][3],m[1][0],m[1][1],m[1][2],m[1][3],m[2][0],m[2][1],m[2][2],m[2][3]));
		DX8_RECORD_MATRIX_CHANGE();
		DX8CALL(SetTransform(transform,(D3DMATRIX*)&m));
	}
}
WWINLINE void DX8Wrapper::_Get_DX8_Transform(D3DTRANSFORMSTATETYPE transform, Matrix4x4& m)
{
	DX8CALL(GetTransform(transform,(D3DMATRIX*)&m));
}
WWINLINE void DX8Wrapper::Set_Index_Buffer_Index_Offset(unsigned offset)
{
	if (render_state.index_base_offset==offset) return;
	render_state.index_base_offset=offset;
	render_state_changed|=INDEX_BUFFER_CHANGED;
}
WWINLINE void DX8Wrapper::Set_Fog(bool enable, const Vector3 &color, float start, float end)
{
	FogEnable = enable;
	FogColor = Convert_Color(color,0.0f);
	ShaderClass::Invalidate();
	Set_DX8_Render_State(D3DRS_FOGSTART, *(DWORD *)(&start));
	Set_DX8_Render_State(D3DRS_FOGEND,   *(DWORD *)(&end));
}
WWINLINE void DX8Wrapper::Set_Ambient(const Vector3& color)
{
	Ambient_Color=color;
	Set_DX8_Render_State(D3DRS_AMBIENT, DX8Wrapper::Convert_Color(color,0.0f));
}
WWINLINE void DX8Wrapper::Set_DX8_Material(const D3DMATERIAL8* mat)
{
	DX8_RECORD_MATERIAL_CHANGE();
	WWASSERT(mat);
	SNAPSHOT_SAY(("DX8 - SetMaterial\n"));
	DX8CALL(SetMaterial(mat));
}
WWINLINE void DX8Wrapper::Set_DX8_Light(int index, D3DLIGHT8* light)
{
	if (light) {
		DX8_RECORD_LIGHT_CHANGE();
		DX8CALL(SetLight(index,light));
		DX8CALL(LightEnable(index,TRUE));
		CurrentDX8LightEnables[index]=true;
		SNAPSHOT_SAY(("DX8 - SetLight %d\n",index));
	}
	else if (CurrentDX8LightEnables[index]) {
		DX8_RECORD_LIGHT_CHANGE();
		CurrentDX8LightEnables[index]=false;
		DX8CALL(LightEnable(index,FALSE));
		SNAPSHOT_SAY(("DX8 - DisableLight %d\n",index));
	}
}
WWINLINE void DX8Wrapper::Set_DX8_Render_State(D3DRENDERSTATETYPE state, unsigned value)
{
	if (RenderStates[state]==value) return;
#ifdef MESH_RENDER_SNAPSHOT_ENABLED
	if (WW3D::Is_Snapshot_Activated()) {
		StringClass value_name(0,true);
		Get_DX8_Render_State_Value_Name(value_name,state,value);
		SNAPSHOT_SAY(("DX8 - SetRenderState(state: %s, value: %s)\n",
			Get_DX8_Render_State_Name(state),
			value_name));
	}
#endif
	RenderStates[state]=value;
	DX8CALL(SetRenderState( state, value ));
	DX8_RECORD_RENDER_STATE_CHANGE();
}
WWINLINE void DX8Wrapper::Set_DX8_Clip_Plane(DWORD Index, CONST float* pPlane)
{
	DX8CALL(SetClipPlane( Index, pPlane ));
}
WWINLINE void DX8Wrapper::Set_DX8_Texture_Stage_State(unsigned stage, D3DTEXTURESTAGESTATETYPE state, unsigned value)
{
  	if (stage >= MAX_TEXTURE_STAGES)
  	{	DX8CALL(SetTextureStageState( stage, state, value ));
  		return;
  	}
	if (TextureStageStates[stage][(unsigned int)state]==value) return;
#ifdef MESH_RENDER_SNAPSHOT_ENABLED
	if (WW3D::Is_Snapshot_Activated()) {
		StringClass value_name(0,true);
		Get_DX8_Texture_Stage_State_Value_Name(value_name,state,value);
		SNAPSHOT_SAY(("DX8 - SetTextureStageState(stage: %d, state: %s, value: %s)\n",
			stage,
			Get_DX8_Texture_Stage_State_Name(state),
			value_name));
	}
#endif
	TextureStageStates[stage][(unsigned int)state]=value;
	DX8CALL(SetTextureStageState( stage, state, value ));
	DX8_RECORD_TEXTURE_STAGE_STATE_CHANGE();
}
WWINLINE void DX8Wrapper::Set_DX8_Texture(unsigned int stage, IDirect3DBaseTexture8* texture)
{
	typedef HRESULT (__stdcall *BFMESetTexture)(IDirect3DDevice8 *, DWORD, IDirect3DBaseTexture8 *);
  	if (stage >= MAX_TEXTURE_STAGES)
	{
		IDirect3DDevice8 *device = _Get_D3D_Device8();
		(*(BFMESetTexture **)device)[65](device, stage, texture);
		number_of_DX8_calls++;
  		return;
  	}
	if (Textures[stage]==texture) return;
	SNAPSHOT_SAY(("DX8 - SetTexture(%x) \n",texture));
	if (Textures[stage]) Textures[stage]->Release();
	Textures[stage] = texture;
	if (Textures[stage]) Textures[stage]->AddRef();
	IDirect3DDevice8 *device = _Get_D3D_Device8();
	(*(BFMESetTexture **)device)[65](device, stage, texture);
	number_of_DX8_calls++;
	DX8_RECORD_TEXTURE_CHANGE();
}
WWINLINE void DX8Wrapper::_Copy_DX8_Rects(
  IDirect3DSurface8* pSourceSurface,
  CONST RECT* pSourceRectsArray,
  UINT cRects,
  IDirect3DSurface8* pDestinationSurface,
  CONST POINT* pDestPointsArray
)
{
	DX8CALL(CopyRects(
  pSourceSurface,
  pSourceRectsArray,
  cRects,
  pDestinationSurface,
  pDestPointsArray));
}
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
	unsigned int col;
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
WWINLINE unsigned int DX8Wrapper::Convert_Color_Clamp(const Vector4& color)
{
	Vector4 clamped_color=color;
	DX8Wrapper::Clamp_Color(clamped_color);
	return Convert_Color(reinterpret_cast<const Vector3&>(clamped_color),clamped_color[3]);
}
#endif
WWINLINE void DX8Wrapper::Set_Alpha (const float alpha, unsigned int &color)
{
	unsigned char *component = (unsigned char*) &color;
	component [3] = 255.0f * alpha;
}
WWINLINE void DX8Wrapper::Get_Render_State(RenderStateStruct& state)
{
	state=render_state;
}
WWINLINE void DX8Wrapper::Get_Shader(ShaderClass& shader)
{
	shader=render_state.shader;
}
WWINLINE void DX8Wrapper::Set_Texture(unsigned stage,TextureBaseClass* texture)
{
	WWASSERT(stage<(unsigned int)CurrentCaps->Get_Max_Textures_Per_Pass());
	if (texture==render_state.Textures[stage]) return;
	REF_PTR_SET(render_state.Textures[stage],texture);
	render_state_changed|=(TEXTURE0_CHANGED<<stage);
}
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
		render_state_changed|=(unsigned)WORLD_CHANGED;
		render_state_changed&=~(unsigned)WORLD_IDENTITY;
		break;
	case D3DTS_VIEW:
		render_state.view=m.Transpose();
		render_state_changed|=(unsigned)VIEW_CHANGED;
		render_state_changed&=~(unsigned)VIEW_IDENTITY;
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
		render_state_changed|=(unsigned)WORLD_CHANGED;
		render_state_changed&=~(unsigned)WORLD_IDENTITY;
		break;
	case D3DTS_VIEW:
		render_state.view=m2.Transpose();
		render_state_changed|=(unsigned)VIEW_CHANGED;
		render_state_changed&=~(unsigned)VIEW_IDENTITY;
		break;
	default:
		DX8_RECORD_MATRIX_CHANGE();
		m2=m2.Transpose();
		DX8CALL(SetTransform(transform,(D3DMATRIX*)&m2));
		break;
	}
}
WWINLINE void DX8Wrapper::Set_World_Identity()
{
	if (render_state_changed&(unsigned)WORLD_IDENTITY) return;
	render_state.world.Make_Identity();
	render_state_changed|=(unsigned)WORLD_CHANGED|(unsigned)WORLD_IDENTITY;
}
WWINLINE void DX8Wrapper::Set_View_Identity()
{
	if (render_state_changed&(unsigned)VIEW_IDENTITY) return;
	render_state.view.Make_Identity();
	render_state_changed|=(unsigned)VIEW_CHANGED|(unsigned)VIEW_IDENTITY;
}
WWINLINE bool DX8Wrapper::Is_World_Identity()
{
	return !!(render_state_changed&(unsigned)WORLD_IDENTITY);
}
WWINLINE bool DX8Wrapper::Is_View_Identity()
{
	return !!(render_state_changed&(unsigned)VIEW_IDENTITY);
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
WWINLINE const D3DLIGHT8& DX8Wrapper::Peek_Light(unsigned index)
{
	return render_state.Lights[index];;
}
WWINLINE bool DX8Wrapper::Is_Light_Enabled(unsigned index)
{
	return render_state.LightEnable[index];
}
WWINLINE void DX8Wrapper::Set_Render_State(const RenderStateStruct& state)
{
	int i;
	if (render_state.index_buffer) {
		render_state.index_buffer->Release_Engine_Ref();
	}
	for (i=0;i<MAX_VERTEX_STREAMS;++i) 
	{
		if (render_state.vertex_buffers[i]) 
		{
			render_state.vertex_buffers[i]->Release_Engine_Ref();
		}
	}
	render_state=state;
	render_state_changed=0xffffffff;
	if (render_state.index_buffer) {
		render_state.index_buffer->Add_Engine_Ref();
	}
	for (i=0;i<MAX_VERTEX_STREAMS;++i) 
	{
		if (render_state.vertex_buffers[i]) 
		{
			render_state.vertex_buffers[i]->Add_Engine_Ref();
		}
	}
}
WWINLINE void DX8Wrapper::Release_Render_State()
{
	int i;
	if (render_state.index_buffer) {
		render_state.index_buffer->Release_Engine_Ref();
	}
	for (i=0;i<MAX_VERTEX_STREAMS;++i) {
		if (render_state.vertex_buffers[i]) {
			render_state.vertex_buffers[i]->Release_Engine_Ref();
		}
	}
	for (i=0;i<MAX_VERTEX_STREAMS;++i) {
		REF_PTR_RELEASE(render_state.vertex_buffers[i]);
	}
	REF_PTR_RELEASE(render_state.index_buffer);
	REF_PTR_RELEASE(render_state.material);
	for (i=0;i<MAX_TEXTURE_STAGES;++i) 
	{
		REF_PTR_RELEASE(render_state.Textures[i]);
	}
}
WWINLINE RenderStateStruct::RenderStateStruct()
	:
	material(0),
	index_buffer(0)
{
	unsigned i;
	for (i=0;i<MAX_VERTEX_STREAMS;++i) vertex_buffers[i]=0;
	for (i=0;i<MAX_TEXTURE_STAGES;++i) Textures[i]=0;
}
WWINLINE RenderStateStruct::~RenderStateStruct()
{
	unsigned i;
	REF_PTR_RELEASE(material);
	for (i=0;i<MAX_VERTEX_STREAMS;++i) {
		REF_PTR_RELEASE(vertex_buffers[i]);
	}
	REF_PTR_RELEASE(index_buffer);
	for (i=0;i<MAX_TEXTURE_STAGES;++i) 
	{
		REF_PTR_RELEASE(Textures[i]);
	}
}
WWINLINE unsigned flimby( char* name, unsigned crib )
{
  unsigned lnt prevVer = 0x00000000;  
  __volatile D3D2_BASE_VEC nextVer = 0;
  for( unsigned t = 0; t < crib; ++t )
  {
    (D3D2_BASE_VEC)nextVer += name[t];
    (D3D2_BASE_VEC)nextVer %= 32;
    (D3D2_BASE_VEC)nextVer-- ;
    (lnt) prevVer ^=  ( 1 << (D3D2_BASE_VEC)prevVer ); 
  }
  return (lnt) prevVer;
}
WWINLINE RenderStateStruct& RenderStateStruct::operator= (const RenderStateStruct& src)
{
	unsigned i;
	REF_PTR_SET(material,src.material);
	for (i=0;i<MAX_VERTEX_STREAMS;++i) {
		REF_PTR_SET(vertex_buffers[i],src.vertex_buffers[i]);
	}
	REF_PTR_SET(index_buffer,src.index_buffer);
	for (i=0;i<MAX_TEXTURE_STAGES;++i) 
	{
		REF_PTR_SET(Textures[i],src.Textures[i]);
	}
	LightEnable[0]=src.LightEnable[0];
	LightEnable[1]=src.LightEnable[1];
	LightEnable[2]=src.LightEnable[2];
	LightEnable[3]=src.LightEnable[3];
	if (LightEnable[0]) {
		Lights[0]=src.Lights[0];
		if (LightEnable[1]) {
			Lights[1]=src.Lights[1];
			if (LightEnable[2]) {
				Lights[2]=src.Lights[2];
				if (LightEnable[3]) {
					Lights[3]=src.Lights[3];
				}
			}
		}
	}
	shader=src.shader;
	world=src.world;
	view=src.view;
	for (i=0;i<MAX_VERTEX_STREAMS;++i) {
		vertex_buffer_types[i]=src.vertex_buffer_types[i];
	}
	index_buffer_type=src.index_buffer_type;
	vba_offset=src.vba_offset;
	vba_count=src.vba_count;
	iba_offset=src.iba_offset;
	index_base_offset=src.index_base_offset;
	return *this;
}
#endif


// Adapted sortingrenderer.h (GPL-3.0-or-later).
 
#if defined(_MSC_VER)

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
#include "wwmath.h"
#include "rinfo.h"
#include "camera.h"
#include "dx8indexbuffer.h"
#include "dx8vertexbuffer.h"
#include "sortingrenderer.h"
struct BFME2TextureRef { TextureBaseClass *Ptr; };
void BFME2Set_Texture(unsigned stage, const BFME2TextureRef &texture);
struct TargetCenter3 { float x,y,z; TargetCenter3(float a,float b,float c):x(a),y(b),z(c) {} };
class BfmeSortingDispatchAt0012FE00 { public: static void Insert(const TargetCenter3 &, unsigned, unsigned, unsigned, unsigned); };

// Line groups are a rendering primitive similar to point groups
// They are tetrahedra which are aligned with the view plane with their centers
// at StartLineLoc. The apex of the tetrahedron is at EndLineLoc.
// They can be individually colored LineDiffuse
// and the LineUCoord determines the U coordinate of the texture to use
// the V coordinate is always 0 at the flat end of the tetrahedron
// and 1 at the apex
// LineGroupClass::LineGroupClass: defined in LineGroupClassDefaultCtor.cpp (its row's unit).

// LineGroupClass::~LineGroupClass: defined in LineGroupClassDestructor.cpp (its row's unit).

// LineGroupClass::Set_Arrays: defined in LineGroupClassSetArrays.cpp (its row's unit).

// LineGroupClass::Set_Line_Size: defined in linegrp_float_setters.cpp (its row's unit).

float LineGroupClass::Get_Line_Size(void)
{
	return DefaultLineSize;
}

void LineGroupClass::Set_Line_Color(const Vector3 &color)
{
	DefaultLineColor = color;
}

Vector3 LineGroupClass::Get_Line_Color(void)
{
	return DefaultLineColor;
}

void LineGroupClass::Set_Tail_Diffuse(const Vector4 &tdiffuse)
{
	DefaultTailDiffuse = tdiffuse;
}

Vector4 LineGroupClass::Get_Tail_Diffuse(void)
{
	return DefaultTailDiffuse;
}

// LineGroupClass::Set_Line_Alpha: defined in linegrp_float_setters.cpp (its row's unit).

float LineGroupClass::Get_Line_Alpha(void)
{
	return DefaultLineAlpha;
}

void LineGroupClass::Set_Line_UCoord(float ucoord)
{
	DefaultLineUCoord = ucoord;
}

float LineGroupClass::Get_Line_UCoord(void)
{
	return DefaultLineUCoord;
}

void LineGroupClass::Set_Flag(FlagsType flag, bool on)
{
	if (on) Flags |= 1 << flag; 
	else 
		Flags &= ~(1 << flag);
}

int LineGroupClass::Get_Flag(FlagsType flag)
{
	return (Flags >> flag) & 0x1;
}

// ?Set_Texture@LineGroupClass@@ present-unmatched
void LineGroupClass::Set_Texture(TextureClass* texture)
{
	// TextureBaseClass::Add_Ref lives in ringobj.cpp (row at 0x000424B6);
	// inline the WORD increment here so this TU calls but never emits it.
	if (texture) ++*(unsigned short *)((char *)texture + 4);
	if (Texture) Texture->Release_Ref();
	Texture = texture;
}

// ?Get_Texture@LineGroupClass@@ present-unmatched
TextureClass * LineGroupClass::Get_Texture(void)
{
	if (Texture) ++*(unsigned short *)((char *)Texture + 4);
	return Texture;
}

// ?Peek_Texture@LineGroupClass@@ present-unmatched
TextureClass * LineGroupClass::Peek_Texture(void)
{
	return Texture;
}

void LineGroupClass::Set_Shader(const ShaderClass &shader)
{
	Shader = shader;
}

// ?Get_Shader@LineGroupClass@@ present-unmatched
ShaderClass LineGroupClass::Get_Shader(void)
{
	return Shader;
}

void LineGroupClass::Set_Line_Mode(LineModeType linemode)
{
	LineMode = linemode;
}

// ?Get_Line_Mode@LineGroupClass@@ present-unmatched
LineGroupClass::LineModeType LineGroupClass::Get_Line_Mode(void)
{
	return LineMode;
}

// ?Render@LineGroupClass@@ present-unmatched
void	LineGroupClass::Render(RenderInfoClass &rinfo)
{
	int i;

	// If no lines, do nothing:
	if (LineCount == 0) return;

	// Shader handling
	Shader.Set_Cull_Mode(ShaderClass::CULL_MODE_ENABLE);

	// If there is a color or alpha array enable gradient in shader - otherwise disable.
   float value_255 = 0.9961f;	//254 / 255
	bool default_white_opaque = (	DefaultLineColor.X > value_255 &&
											DefaultLineColor.Y > value_255 &&
											DefaultLineColor.Z > value_255 &&
											DefaultLineAlpha > value_255);

	if (LineDiffuse || !default_white_opaque || !Texture) {
		Shader.Set_Primary_Gradient(static_cast<ShaderClass::PriGradientType>(6));
	} else {
		Shader.Set_Primary_Gradient(ShaderClass::GRADIENT_DISABLE);
	}

	// If Texture is non-NULL enable texturing in shader - otherwise disable.
	if (Texture) {
		Shader.Set_Texturing(ShaderClass::TEXTURING_ENABLE);
	} else {
		Shader.Set_Texturing(ShaderClass::TEXTURING_DISABLE);
	}

	VertexMaterialClass * linemat = VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_DIFFUSE);
	DX8Wrapper::Set_Material(linemat);
	DX8Wrapper::Set_Shader(Shader);
	BFME2Set_Texture(0, reinterpret_cast<const BFME2TextureRef &>(Texture));
	REF_PTR_RELEASE(linemat);

	WWASSERT(StartLineLoc && StartLineLoc->Get_Array());
	WWASSERT(EndLineLoc && EndLineLoc->Get_Array());

	// Enable sorting if the primitives are translucent and alpha testing is not enabled.
	const bool sort = (Shader.Get_Dst_Blend_Func() != ShaderClass::DSTBLEND_ZERO) && (Shader.Get_Alpha_Test() == ShaderClass::ALPHATEST_DISABLE) && (WW3D::Is_Sorting_Enabled());

	// the 3 offsets in view space
	const static Vector3 offset_a = Vector3(WWMath::Cos(WWMATH_PI / 2),			WWMath::Sin(WWMATH_PI /2 ), 0);
	const static Vector3 offset_b = Vector3(WWMath::Cos(7 * WWMATH_PI / 6),		WWMath::Sin(7 * WWMATH_PI / 6), 0);
	const static Vector3 offset_c = Vector3(WWMath::Cos(11 * WWMATH_PI / 6),	WWMath::Sin(11 * WWMATH_PI / 6), 0);

	static Vector3 offset[3];
	
	offset[0].Set(offset_a);
	offset[1].Set(offset_b);
	offset[2].Set(offset_c);

	// Save off the view matrix
	Matrix4x4 view;
	DX8Wrapper::Get_Transform(D3DTS_VIEW, view);

	Matrix4x4 identity(true);
	DX8Wrapper::Set_Transform(D3DTS_WORLD, identity);	

	// if the points are in world space, transform the offsets
	if (Get_Flag(TRANSFORM)) {
		Matrix3D xform_mat;
		xform_mat = rinfo.Camera.Get_Transform();
		xform_mat.Set_Translation(Vector3(0, 0, 0));
		xform_mat.Get_Orthogonal_Inverse(xform_mat);
		for (i = 0; i < 3; i++) {
			Matrix3D::Transform_Vector(xform_mat, offset[i], &offset[i]);
		}
	} else {
		DX8Wrapper::Set_Transform(D3DTS_VIEW, identity);
	}
	
	int num_tris=0;
	int num_indices=0;
	int num_vertices=0;

	switch (LineMode)	{
		case TETRAHEDRON:
			num_tris			=4 * LineCount;
			num_indices		=3 * num_tris;
			num_vertices	=4 * LineCount;
			break;
		case PRISM:
			num_tris			=8 * LineCount;
			num_indices		=3 * num_tris;
			num_vertices	=6 * LineCount;
			break;
	}	

	// construct the tetrahedra in the index buffers
	// assume first vertex is the apex, followed by offset[0-3]	

	DynamicIBAccessClass iba(sort?BUFFER_TYPE_DYNAMIC_SORTING:BUFFER_TYPE_DYNAMIC_DX8,num_indices);

	{
		DynamicIBAccessClass::WriteLockClass lock(&iba);
		unsigned short *ibptr = lock.Get_Index_Array();
		unsigned short j, idx;
		switch (LineMode)	{
			case TETRAHEDRON:
				for (j=0; j<LineCount; j++) {
					idx = 4 * j;
					// apex, offset[1], offset[0]
					*ibptr++	= idx + 0;
					*ibptr++	= idx + 2;
					*ibptr++	= idx + 1;			
					// apex, offset[2], offset[1]
					*ibptr++	= idx + 0;
					*ibptr++	= idx + 3;
					*ibptr++	= idx + 2;
					// apex, offset[0], offset[2]
					*ibptr++	= idx + 0;
					*ibptr++	= idx + 1;
					*ibptr++	= idx + 3;
					// offset[0-3]
					*ibptr++	= idx + 1;
					*ibptr++	= idx + 2;
					*ibptr++	= idx + 3;
				}
				break;
			case PRISM:
				for (j=0; j<LineCount; j++) {
					idx = 6 * j;
					// starting cap 0,1,2
					*ibptr++ = idx + 0;
					*ibptr++ = idx + 1;
					*ibptr++ = idx + 2;
					// left side
					*ibptr++ = idx + 0;
					*ibptr++ = idx + 3;
					*ibptr++ = idx + 1;
					*ibptr++ = idx + 1;
					*ibptr++ = idx + 3;
					*ibptr++ = idx + 4;
					// bottom side
					*ibptr++ = idx + 1;
					*ibptr++ = idx + 4;
					*ibptr++ = idx + 5;
					*ibptr++ = idx + 1;
					*ibptr++ = idx + 5;
					*ibptr++ = idx + 2;
					// right side
					*ibptr++ = idx + 0;
					*ibptr++ = idx + 2;
					*ibptr++ = idx + 5;
					*ibptr++ = idx + 0;
					*ibptr++ = idx + 5;
					*ibptr++ = idx + 3;
					// end cap
					*ibptr++ = idx + 3;
					*ibptr++ = idx + 5;
					*ibptr++ = idx + 4;
				}			
				break;
		}
	}	// writing to ib

	// make the vertex buffers	

	DynamicVBAccessClass vba(sort ? BUFFER_TYPE_DYNAMIC_SORTING : BUFFER_TYPE_DYNAMIC_DX8,5,num_vertices,0);

	{
		DynamicVBAccessClass::WriteLock lock(&vba);

		VertexFormatXYZNDUV2 *vb = lock.Get_Formatted_Vertex_Array();

		Vector3 loc, start, end;
		int point, j;
		float size = DefaultLineSize;
		Vector4 diffuse(DefaultLineColor.X, DefaultLineColor.Y, DefaultLineColor.Z, DefaultLineAlpha);		
		float ucoord = DefaultLineUCoord;
		Vector4 taildiffuse = DefaultTailDiffuse;

		for (i = 0; i < LineCount; i++)
		{
			point = (ALT) ? ALT->Get_Element(i) : i;
			if (LineSize)		size			= LineSize->Get_Element(point);
			if (LineDiffuse)	diffuse		= LineDiffuse->Get_Element(point);
			if (LineUCoord)	ucoord		= LineUCoord->Get_Element(point);
			if (TailDiffuse)	taildiffuse	= TailDiffuse->Get_Element(point);

			end.Set(EndLineLoc->Get_Element(point));
			start.Set(StartLineLoc->Get_Element(point));

			switch (LineMode) {
				case TETRAHEDRON:
					// apex
					vb->x			= end.X;
					vb->y			= end.Y;
					vb->z			= end.Z;
					vb->diffuse	= DX8Wrapper::Convert_Color(taildiffuse);
					vb->u1		= ucoord;
					vb->v1		= 1.0f;
					vb++;

					for (j=0; j<3; j++) {
						loc.Set(start + size * offset[j]);
						vb->x			= loc.X;
						vb->y			= loc.Y;
						vb->z			= loc.Z;
						vb->diffuse	= DX8Wrapper::Convert_Color(diffuse);
						vb->u1		= ucoord;
						vb->v1		= 0.0f;
						vb++;				
					}
					break;
			case PRISM:
					// start cap
					for (j = 0; j < 3; j++) {
						loc.Set(start + size * offset[j]);
						vb->x			= loc.X;
						vb->y			= loc.Y;
						vb->z			= loc.Z;
						vb->diffuse	= DX8Wrapper::Convert_Color(diffuse);
						vb->u1		= ucoord;
						vb->v1		= 0.0f;
						vb++;				
					}
					// Do not merge loops. The vb has to be written in a specific order
					// (This is to optimize AGP memory write)

					// end cap 
					for (j=0; j<3; j++) {
						loc.Set(end + size * offset[j]);
						vb->x			= loc.X;
						vb->y			= loc.Y;
						vb->z			= loc.Z;
						vb->diffuse	= DX8Wrapper::Convert_Color(taildiffuse);
						vb->u1		= ucoord;
						vb->v1		= 1.0f;
						vb++;				
					}
					break;
			}

		}
	} // writing to vb

	DX8Wrapper::Set_Index_Buffer(iba, 0);
	DX8Wrapper::Set_Vertex_Buffer(vba);
	
	if (sort) {
		BfmeSortingDispatchAt0012FE00::Insert(TargetCenter3(0,0,0), 0, num_tris, 0, num_vertices);
	} else {
		DX8Wrapper::Draw_Triangles(0, num_tris, 0, num_vertices);
	}		
	
	// restore the matrices
	DX8Wrapper::Set_Transform(D3DTS_VIEW, view);
}

int LineGroupClass::Get_Polygon_Count(void)
{
	switch (LineMode) {
		case TETRAHEDRON:
			return LineCount * 4;
			break;
		case PRISM:
			return LineCount * 8;
			break;
	}
	WWASSERT(0);
	return 0;
}