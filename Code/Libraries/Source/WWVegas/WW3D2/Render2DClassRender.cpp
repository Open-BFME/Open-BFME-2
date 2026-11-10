// cl: /O2 /arch:SSE -DBFME_WWSTRING_NATIVE_CSTR_ASSIGN -Ireference/shims/wwstring_teardown/bfme -G7 -Ireference/shims/bfmerendobj -DNDEBUG -MD -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDownload -Ireference/open-bfme-1/game/Libraries/Source/Compression -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug -Ireference/shims/sweep -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDownload -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug -Ireference/open-bfme-1/game/Libraries/Source/Compression -Ireference/shims/sweep
// ?Render@Render2DClass@@QAEXXZ retail 0x0011A040..0x0011BD74 (7476 bytes).
// Render2DClass::Render, adapted from Zero Hour render2d.cpp with the BFME 2
// seven-mode batch renderer: save view/projection, full-screen viewport,
// PRELIT_DIFFUSE material, copy the linked vertex runs and indices into
// dynamic DX8 buffers, then per mode and batch set shader, texture and the
// dot3/stencil render and texture-stage states (each inlined RS/TSS setter
// takes the MESH_RENDER_SNAPSHOT StringClass value-name path through
// Get_DX8_Render_State_Value_Name 0x00121A10 and
// Get_DX8_Texture_Stage_State_Value_Name 0x00120B90) and draw; restore the
// transforms. WorldBuilder twin 0x009C07A0 (shape evidence: viewport without
// locals, PlainDataVectorClass branchy operator[] at 0x009C2BD0/0x009C2E40,
// shader setter sequence at 0x009C0E89). The dx8wrapper/dx8caps/vertex and
// index buffer/sorting renderer declarations are Zero Hour header copies
// reduced to this unit; layouts beyond the accessed fields are donor-derived.
// Attempt history: reverse/attempt_support/render2d-render-11a040-20261020/.
/* Copyright 2025 Electronic Arts Inc.
* Adapted from Command & Conquer Generals Zero Hour WW3D2 sources.
* Licensed under GNU General Public License version 3 or later.
* Distributed without warranty; see <http://www.gnu.org/licenses/>. */
#if _MSC_VER >= 1000
#pragma once
#endif 
#ifndef DX8CAPS_H
#define DX8CAPS_H
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
#include "always.h"
#include "ww3dformat.h"
#include <d3d8.h>
class DX8Caps
{
public:
enum DriverVersionStatusType {
DRIVER_STATUS_UNKNOWN,
DRIVER_STATUS_GOOD,
DRIVER_STATUS_OK,
DRIVER_STATUS_BAD
};
enum VendorIdType {
VENDOR_UNKNOWN,
VENDOR_NVIDIA,
VENDOR_ATI,
VENDOR_INTEL,
VENDOR_S3,
VENDOR_POWERVR,
VENDOR_MATROX,
VENDOR_3DFX,
VENDOR_3DLABS,
VENDOR_CIRRUSLOGIC,
VENDOR_RENDITION
};
DX8Caps(IDirect3D8* direct3d, const D3DCAPS8& caps,WW3DFormat display_format, const D3DADAPTER_IDENTIFIER8& adapter_id);
DX8Caps(IDirect3D8* direct3d, IDirect3DDevice8* D3DDevice,WW3DFormat display_format, const D3DADAPTER_IDENTIFIER8& adapter_id);
static void Shutdown(void);
void Compute_Caps(WW3DFormat display_format, const D3DADAPTER_IDENTIFIER8& adapter_id);
bool Support_TnL() const { return SupportTnL; };	
bool Support_DXTC() const { return SupportDXTC; }
bool Support_Gamma() const { return supportGamma; }
bool Support_NPatches() const { return SupportNPatches; }
bool Support_Bump_Envmap() const { return SupportBumpEnvmap; }
bool Support_Bump_Envmap_Luminance() const { return SupportBumpEnvmapLuminance; }
bool Support_ZBias() const { return SupportZBias; }
bool Support_Anisotropic_Filtering() const { return SupportAnisotropicFiltering; }
bool Support_ModAlphaAddClr() const { return SupportModAlphaAddClr; }
bool Support_Dot3() const { return SupportDot3; }
bool Support_PointSprites() const { return SupportPointSprites; }
bool Support_Cubemaps() const { return SupportCubemaps; }
bool Can_Do_Multi_Pass() const { return CanDoMultiPass; }
bool Is_Fog_Allowed() const { return IsFogAllowed; }
bool Is_Valid_Display_Format(int width, int height, WW3DFormat format);
int Get_Max_Textures_Per_Pass() const { return MaxTexturesPerPass; }
int Get_Vertex_Shader_Major_Version() const { return 0xff&(VertexShaderVersion>>8); }
int Get_Vertex_Shader_Minor_Version() const { return 0xff&(VertexShaderVersion); }
int Get_Pixel_Shader_Major_Version() const { return 0xff&(PixelShaderVersion>>8); }
int Get_Pixel_Shader_Minor_Version() const { return 0xff&(PixelShaderVersion); }
int Get_Max_Simultaneous_Textures()	const { return MaxSimultaneousTextures;}
bool Support_Texture_Format(WW3DFormat format) const { return SupportTextureFormat[format]; }
bool Support_Render_To_Texture_Format(WW3DFormat format) const { return SupportRenderToTextureFormat[format]; }
bool Support_Depth_Stencil_Format(WW3DZFormat format) const { return SupportDepthStencilFormat[format]; }
D3DCAPS8 const & Get_DX8_Caps() const { return Caps; }
const StringClass& Get_Log() const { return CapsLog; }
const StringClass& Get_Compact_Log() const { return CompactLog; }
unsigned Get_Vendor() const { return VendorId; }
unsigned Get_Device() const { return DeviceId; }
const StringClass& Get_Driver_Name() const { return DriverDLL; }
unsigned Get_Driver_Build_Version() const { return DriverBuildVersion; }
DriverVersionStatusType Get_Driver_Version_Status() { return DriverVersionStatus; }
private:
static VendorIdType Define_Vendor(unsigned vendor_id);
void Init_Caps(IDirect3DDevice8* D3DDevice);
void Check_Texture_Format_Support(WW3DFormat display_format,const D3DCAPS8& caps);
void Check_Render_To_Texture_Support(WW3DFormat display_format,const D3DCAPS8& caps);
void Check_Depth_Stencil_Support(WW3DFormat display_format, const D3DCAPS8& caps);
void Check_Texture_Compression_Support(const D3DCAPS8& caps);
void Check_Bumpmap_Support(const D3DCAPS8& caps);
void Check_Shader_Support(const D3DCAPS8& caps);
void Check_Maximum_Texture_Support(const D3DCAPS8& caps);
void Check_Driver_Version_Status();
void Vendor_Specific_Hacks(const D3DADAPTER_IDENTIFIER8& adapter_id);
int MaxDisplayWidth;
int MaxDisplayHeight;
D3DCAPS8 Caps;
char _d3d9CapsTail[0x138 - 0x8 - sizeof(D3DCAPS8)];
bool SupportTnL;	
bool SupportDXTC;
bool supportGamma;
bool SupportNPatches;
bool SupportBumpEnvmap;
bool SupportBumpEnvmapLuminance;
bool SupportTextureFormat[123];
bool SupportRenderToTextureFormat[118];
bool SupportDepthStencilFormat[118];
bool SupportZBias;
bool SupportAnisotropicFiltering;
bool SupportModAlphaAddClr;
bool SupportDot3;
bool SupportPointSprites;
bool SupportCubemaps;
bool CanDoMultiPass;
bool IsFogAllowed;
bool SupportDynamicTextures;
int MaxTexturesPerPass;
int VertexShaderVersion;
int PixelShaderVersion;
int MaxSimultaneousTextures;
unsigned DeviceId;          
unsigned RawDeviceId;       
unsigned DriverBuildVersion;
DriverVersionStatusType DriverVersionStatus;
VendorIdType VendorId;      
StringClass DriverDLL;
IDirect3D8* Direct3D; 
StringClass CapsLog;
StringClass CompactLog;
};
typedef char BFME_DX8Caps_layout_size[(sizeof(DX8Caps)==0x2E4)?1:-1];
#endif
#include "sharebuf.h"
#include "texture.h"
#include "vertmaterial.h"
#include <d3d8.h>
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
VertexFormatXYZNDUV2 * Get_Formatted_Vertex_Array() { return Vertices; }
};
friend WriteLock;
};
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
#endif  
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
class DX8_CleanupHook
{
public:
virtual void ReleaseResources(void)=0;
virtual void ReAcquireResources(void)=0;
};
#include "RenderStateStruct.h"
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
static __declspec(dllimport) __forceinline void Set_Transform(D3DTRANSFORMSTATETYPE transform,const Matrix4x4& m);
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
static __declspec(dllimport) __forceinline void Set_Material(const VertexMaterialClass* material);
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
protected:
static bool Registry_Save_Render_Device( const char * sub_key );
static bool Registry_Load_Render_Device( const char * sub_key, bool resize_window );
static const char* Get_DX8_Render_State_Name(D3DRENDERSTATETYPE state);
static const char* Get_DX8_Texture_Stage_State_Name(D3DTEXTURESTAGESTATETYPE state);
static unsigned Get_DX8_Render_State(D3DRENDERSTATETYPE state) { return RenderStates[state]; }
public:
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
public:
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
protected:
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
static Matrix4x4 DeviceProjectionMatrix;
friend void DX8_Assert();
friend class WW3D;
friend class DX8IndexBufferClass;
friend class DX8VertexBufferClass;
};












WWINLINE void DX8Wrapper::Set_DX8_Render_State(D3DRENDERSTATETYPE state, unsigned value)
{
unsigned *cached_state=&RenderStates[state];
unsigned old_state=*cached_state;
if(old_state==value)return;
#ifdef MESH_RENDER_SNAPSHOT_ENABLED
if (WW3D::Is_Snapshot_Activated()) {
StringClass value_name(0,true);
Get_DX8_Render_State_Value_Name(value_name,state,value);
SNAPSHOT_SAY(("DX8 - SetRenderState(state: %s, value: %s)\n",
Get_DX8_Render_State_Name(state),
value_name));
}
#endif
*cached_state=value;
DX8CALL(SetRenderState( state, value ));
DX8_RECORD_RENDER_STATE_CHANGE();
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

// Device9 method prefix through SetPixelShaderConstantF, in Wine/SDK order.
// https://github.com/wine-mirror/wine/blob/master/include/d3d9.h
typedef void *HANDLE;
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
struct IDirect3DVertexDeclaration9;
struct IDirect3DVertexShader9;
struct IDirect3DPixelShader9;
struct D3DVERTEXELEMENT9;
struct Render2DDevice9 {
    virtual HRESULT __stdcall QueryInterface(REFIID riid, void** ppvObject)=0;
    virtual ULONG __stdcall AddRef()=0;
    virtual ULONG __stdcall Release()=0;
    virtual HRESULT __stdcall TestCooperativeLevel()=0;
    virtual UINT __stdcall GetAvailableTextureMem()=0;
    virtual HRESULT __stdcall EvictManagedResources()=0;
    virtual HRESULT __stdcall GetDirect3D(IDirect3D9** ppD3D9)=0;
    virtual HRESULT __stdcall GetDeviceCaps(D3DCAPS9* pCaps)=0;
    virtual HRESULT __stdcall GetDisplayMode(UINT iSwapChain, D3DDISPLAYMODE* pMode)=0;
    virtual HRESULT __stdcall GetCreationParameters(D3DDEVICE_CREATION_PARAMETERS *pParameters)=0;
    virtual HRESULT __stdcall SetCursorProperties(UINT XHotSpot, UINT YHotSpot, IDirect3DSurface9* pCursorBitmap)=0;
    virtual void __stdcall SetCursorPosition(int X,int Y, DWORD Flags)=0;
    virtual BOOL __stdcall ShowCursor(BOOL bShow)=0;
    virtual HRESULT __stdcall CreateAdditionalSwapChain(D3DPRESENT_PARAMETERS* pPresentationParameters, IDirect3DSwapChain9** pSwapChain)=0;
    virtual HRESULT __stdcall GetSwapChain(UINT iSwapChain, IDirect3DSwapChain9** pSwapChain)=0;
    virtual UINT __stdcall GetNumberOfSwapChains()=0;
    virtual HRESULT __stdcall Reset(D3DPRESENT_PARAMETERS* pPresentationParameters)=0;
    virtual HRESULT __stdcall Present(const RECT *src_rect, const RECT *dst_rect, HWND dst_window_override, const RGNDATA *dirty_region)=0;
    virtual HRESULT __stdcall GetBackBuffer(UINT iSwapChain, UINT iBackBuffer, D3DBACKBUFFER_TYPE Type, IDirect3DSurface9** ppBackBuffer)=0;
    virtual HRESULT __stdcall GetRasterStatus(UINT iSwapChain, D3DRASTER_STATUS* pRasterStatus)=0;
    virtual HRESULT __stdcall SetDialogBoxMode(BOOL bEnableDialogs)=0;
    virtual void __stdcall SetGammaRamp(UINT swapchain_idx, DWORD flags, const D3DGAMMARAMP *ramp)=0;
    virtual void __stdcall GetGammaRamp(UINT iSwapChain, D3DGAMMARAMP* pRamp)=0;
    virtual HRESULT __stdcall CreateTexture(UINT Width, UINT Height, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DTexture9** ppTexture, HANDLE* pSharedHandle)=0;
    virtual HRESULT __stdcall CreateVolumeTexture(UINT Width, UINT Height, UINT Depth, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DVolumeTexture9** ppVolumeTexture, HANDLE* pSharedHandle)=0;
    virtual HRESULT __stdcall CreateCubeTexture(UINT EdgeLength, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DCubeTexture9** ppCubeTexture, HANDLE* pSharedHandle)=0;
    virtual HRESULT __stdcall CreateVertexBuffer(UINT Length, DWORD Usage, DWORD FVF, D3DPOOL Pool, IDirect3DVertexBuffer9** ppVertexBuffer, HANDLE* pSharedHandle)=0;
    virtual HRESULT __stdcall CreateIndexBuffer(UINT Length, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DIndexBuffer9** ppIndexBuffer, HANDLE* pSharedHandle)=0;
    virtual HRESULT __stdcall CreateRenderTarget(UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, DWORD MultisampleQuality, BOOL Lockable, IDirect3DSurface9** ppSurface, HANDLE* pSharedHandle)=0;
    virtual HRESULT __stdcall CreateDepthStencilSurface(UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, DWORD MultisampleQuality, BOOL Discard, IDirect3DSurface9** ppSurface, HANDLE* pSharedHandle)=0;
    virtual HRESULT __stdcall UpdateSurface(IDirect3DSurface9 *src_surface, const RECT *src_rect, IDirect3DSurface9 *dst_surface, const POINT *dst_point)=0;
    virtual HRESULT __stdcall UpdateTexture(IDirect3DBaseTexture9* pSourceTexture, IDirect3DBaseTexture9* pDestinationTexture)=0;
    virtual HRESULT __stdcall GetRenderTargetData(IDirect3DSurface9* pRenderTarget, IDirect3DSurface9* pDestSurface)=0;
    virtual HRESULT __stdcall GetFrontBufferData(UINT iSwapChain, IDirect3DSurface9* pDestSurface)=0;
    virtual HRESULT __stdcall StretchRect(IDirect3DSurface9 *src_surface, const RECT *src_rect, IDirect3DSurface9 *dst_surface, const RECT *dst_rect, D3DTEXTUREFILTERTYPE filter)=0;
    virtual HRESULT __stdcall ColorFill(IDirect3DSurface9 *surface, const RECT *rect, D3DCOLOR color)=0;
    virtual HRESULT __stdcall CreateOffscreenPlainSurface(UINT Width, UINT Height, D3DFORMAT Format, D3DPOOL Pool, IDirect3DSurface9** ppSurface, HANDLE* pSharedHandle)=0;
    virtual HRESULT __stdcall SetRenderTarget(DWORD RenderTargetIndex, IDirect3DSurface9* pRenderTarget)=0;
    virtual HRESULT __stdcall GetRenderTarget(DWORD RenderTargetIndex, IDirect3DSurface9** ppRenderTarget)=0;
    virtual HRESULT __stdcall SetDepthStencilSurface(IDirect3DSurface9* pNewZStencil)=0;
    virtual HRESULT __stdcall GetDepthStencilSurface(IDirect3DSurface9** ppZStencilSurface)=0;
    virtual HRESULT __stdcall BeginScene()=0;
    virtual HRESULT __stdcall EndScene()=0;
    virtual HRESULT __stdcall Clear(DWORD rect_count, const D3DRECT *rects, DWORD flags, D3DCOLOR color, float z, DWORD stencil)=0;
    virtual HRESULT __stdcall SetTransform(D3DTRANSFORMSTATETYPE state, const D3DMATRIX *matrix)=0;
    virtual HRESULT __stdcall GetTransform(D3DTRANSFORMSTATETYPE State, D3DMATRIX* pMatrix)=0;
    virtual HRESULT __stdcall MultiplyTransform(D3DTRANSFORMSTATETYPE state, const D3DMATRIX *matrix)=0;
    virtual HRESULT __stdcall SetViewport(const D3DVIEWPORT9 *viewport)=0;
    virtual HRESULT __stdcall GetViewport(D3DVIEWPORT9* pViewport)=0;
    virtual HRESULT __stdcall SetMaterial(const D3DMATERIAL9 *material)=0;
    virtual HRESULT __stdcall GetMaterial(D3DMATERIAL9* pMaterial)=0;
    virtual HRESULT __stdcall SetLight(DWORD index, const D3DLIGHT9 *light)=0;
    virtual HRESULT __stdcall GetLight(DWORD Index, D3DLIGHT9*)=0;
    virtual HRESULT __stdcall LightEnable(DWORD Index, BOOL Enable)=0;
    virtual HRESULT __stdcall GetLightEnable(DWORD Index, BOOL* pEnable)=0;
    virtual HRESULT __stdcall SetClipPlane(DWORD index, const float *plane)=0;
    virtual HRESULT __stdcall GetClipPlane(DWORD Index, float* pPlane)=0;
    virtual HRESULT __stdcall SetRenderState(D3DRENDERSTATETYPE State, DWORD Value)=0;
    virtual HRESULT __stdcall GetRenderState(D3DRENDERSTATETYPE State, DWORD* pValue)=0;
    virtual HRESULT __stdcall CreateStateBlock(D3DSTATEBLOCKTYPE Type, IDirect3DStateBlock9** ppSB)=0;
    virtual HRESULT __stdcall BeginStateBlock()=0;
    virtual HRESULT __stdcall EndStateBlock(IDirect3DStateBlock9** ppSB)=0;
    virtual HRESULT __stdcall SetClipStatus(const D3DCLIPSTATUS9 *clip_status)=0;
    virtual HRESULT __stdcall GetClipStatus(D3DCLIPSTATUS9* pClipStatus)=0;
    virtual HRESULT __stdcall GetTexture(DWORD Stage, IDirect3DBaseTexture9** ppTexture)=0;
    virtual HRESULT __stdcall SetTexture(DWORD Stage, IDirect3DBaseTexture9* pTexture)=0;
    virtual HRESULT __stdcall GetTextureStageState(DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD* pValue)=0;
    virtual HRESULT __stdcall SetTextureStageState(DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD Value)=0;
};
// The out-of-line copy of this inline is a COMDAT the link may keep; retail's
// (0x000661DD) is size-optimised (__EH_prolog frame), unlike this /O2 unit.
#pragma optimize("s", on)
WWINLINE void DX8Wrapper::Set_DX8_Texture_Stage_State(unsigned stage, D3DTEXTURESTAGESTATETYPE state, unsigned value)
{
if (stage >= MAX_TEXTURE_STAGES)
{	((Render2DDevice9*)_Get_D3D_Device8())->SetTextureStageState(stage,state,value); number_of_DX8_calls++;
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
((Render2DDevice9*)_Get_D3D_Device8())->SetTextureStageState(stage,state,value); number_of_DX8_calls++;
DX8_RECORD_TEXTURE_STAGE_STATE_CHANGE();
}
#pragma optimize("", on)



#if 0


#else



#endif



__declspec(dllimport) __forceinline void DX8Wrapper::Set_Material(const VertexMaterialClass* material)
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
__declspec(dllimport) __forceinline void DX8Wrapper::Set_Transform(D3DTRANSFORMSTATETYPE transform,const Matrix4x4& matrix4x4)
{
switch ((int)transform) {
case D3DTS_WORLD:
render_state.world[0][0]=matrix4x4[0][0];
render_state.world[0][1]=matrix4x4[1][0];
render_state.world[0][2]=matrix4x4[2][0];
render_state.world[0][3]=matrix4x4[3][0];
render_state.world[1][0]=matrix4x4[0][1];
render_state.world[1][1]=matrix4x4[1][1];
render_state.world[1][2]=matrix4x4[2][1];
render_state.world[1][3]=matrix4x4[3][1];
render_state.world[2][0]=matrix4x4[0][2];
render_state.world[2][1]=matrix4x4[1][2];
render_state.world[2][2]=matrix4x4[2][2];
render_state.world[2][3]=matrix4x4[3][2];
render_state.world[3][0]=matrix4x4[0][3];
render_state.world[3][1]=matrix4x4[1][3];
render_state.world[3][2]=matrix4x4[2][3];
render_state.world[3][3]=matrix4x4[3][3];
render_state_changed&=~(unsigned)WORLD_IDENTITY;
render_state_changed|=(unsigned)WORLD_CHANGED;
break;
case D3DTS_VIEW:
render_state.view[0][0]=matrix4x4[0][0];
render_state.view[0][1]=matrix4x4[1][0];
render_state.view[0][2]=matrix4x4[2][0];
render_state.view[0][3]=matrix4x4[3][0];
render_state.view[1][0]=matrix4x4[0][1];
render_state.view[1][1]=matrix4x4[1][1];
render_state.view[1][2]=matrix4x4[2][1];
render_state.view[1][3]=matrix4x4[3][1];
render_state.view[2][0]=matrix4x4[0][2];
render_state.view[2][1]=matrix4x4[1][2];
render_state.view[2][2]=matrix4x4[2][2];
render_state.view[2][3]=matrix4x4[3][2];
render_state.view[3][0]=matrix4x4[0][3];
render_state.view[3][1]=matrix4x4[1][3];
render_state.view[3][2]=matrix4x4[2][3];
render_state.view[3][3]=matrix4x4[3][3];
render_state_changed&=~(unsigned)VIEW_IDENTITY;
render_state_changed|=(unsigned)VIEW_CHANGED;
break;
case D3DTS_PROJECTION:
ProjectionMatrix=matrix4x4.Transpose();
DeviceProjectionMatrix=ProjectionMatrix;
ZFar=0.0f;
ZNear=0.0f;
DX8CALL(SetTransform(D3DTS_PROJECTION,(D3DMATRIX*)&DeviceProjectionMatrix));
break;
default:
DX8_RECORD_MATRIX_CHANGE();
Matrix4x4 m2=matrix4x4.Transpose();
DX8CALL(SetTransform(transform,(D3DMATRIX*)&m2));
break;
}
}
WWINLINE void DX8Wrapper::Set_Transform(D3DTRANSFORMSTATETYPE transform,const Matrix3D& matrix3D)
{
Matrix4x4 m2(matrix3D);
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


WWINLINE void DX8Wrapper::Get_Transform(D3DTRANSFORMSTATETYPE transform, Matrix4x4& matrix4x4)
{
D3DMATRIX mat;
switch ((int)transform) {
case D3DTS_WORLD:
if (render_state_changed&WORLD_IDENTITY) matrix4x4.Make_Identity();
else matrix4x4=render_state.world.Transpose();
break;
case D3DTS_VIEW:
if (render_state_changed&VIEW_IDENTITY) matrix4x4.Make_Identity();
else { matrix4x4[0][0]=render_state.view[0][0];
matrix4x4[0][1]=render_state.view[1][0];
matrix4x4[0][2]=render_state.view[2][0];
matrix4x4[0][3]=render_state.view[3][0];
matrix4x4[1][0]=render_state.view[0][1];
matrix4x4[1][1]=render_state.view[1][1];
matrix4x4[1][2]=render_state.view[2][1];
matrix4x4[1][3]=render_state.view[3][1];
matrix4x4[2][0]=render_state.view[0][2];
matrix4x4[2][1]=render_state.view[1][2];
matrix4x4[2][2]=render_state.view[2][2];
matrix4x4[2][3]=render_state.view[3][2];
matrix4x4[3][0]=render_state.view[0][3];
matrix4x4[3][1]=render_state.view[1][3];
matrix4x4[3][2]=render_state.view[2][3];
matrix4x4[3][3]=render_state.view[3][3]; }
break;
case D3DTS_PROJECTION:
matrix4x4[0][0]=DeviceProjectionMatrix[0][0];
matrix4x4[0][1]=DeviceProjectionMatrix[1][0];
matrix4x4[0][2]=DeviceProjectionMatrix[2][0];
matrix4x4[0][3]=DeviceProjectionMatrix[3][0];
matrix4x4[1][0]=DeviceProjectionMatrix[0][1];
matrix4x4[1][1]=DeviceProjectionMatrix[1][1];
matrix4x4[1][2]=DeviceProjectionMatrix[2][1];
matrix4x4[1][3]=DeviceProjectionMatrix[3][1];
matrix4x4[2][0]=DeviceProjectionMatrix[0][2];
matrix4x4[2][1]=DeviceProjectionMatrix[1][2];
matrix4x4[2][2]=DeviceProjectionMatrix[2][2];
matrix4x4[2][3]=DeviceProjectionMatrix[3][2];
matrix4x4[3][0]=DeviceProjectionMatrix[0][3];
matrix4x4[3][1]=DeviceProjectionMatrix[1][3];
matrix4x4[3][2]=DeviceProjectionMatrix[2][3];
matrix4x4[3][3]=DeviceProjectionMatrix[3][3];
break;
default:
DX8CALL(GetTransform(transform,&mat));
matrix4x4=*(Matrix4x4*)&mat;
matrix4x4=matrix4x4.Transpose();
break;
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
#endif
#if defined(_MSC_VER)
#endif
#ifndef SORTING_RENDERER_H
#define SORTING_RENDERER_H
#include "always.h"
class SortingNodeStruct;
class SphereClass;
#include "SortingRendererClass.h"
#endif
#include "dx8wrapper.h"
#include "wwmath.h"
#include "rinfo.h"
#include "camera.h"
#include "dx8indexbuffer.h"
#include "dx8vertexbuffer.h"
#include "sortingrenderer.h"
struct BFME2TextureRef { TextureBaseClass *Ptr; BFME2TextureRef():Ptr(0) {} ~BFME2TextureRef() { if(Ptr) Ptr->Release_Ref(); } };
void BFME2Set_Texture(unsigned stage, const BFME2TextureRef &texture);
#include <string.h>
extern int G00DB5FBC, G00DB5FC0, G00DB5FC4;
extern unsigned int g_Va00DEC4A0, g_Va00DEC4A4, g_Va00DEC4A8;
void Rva00118810();
struct BfmeRenderVertex {
float x,y,z; int NextRun,IndexStart,IndexCount; unsigned color; float u,v; char unknown24[8];
};
template<class T> struct Render2DArray {
T *Data; unsigned Size,Count; int Growth; unsigned Length()const{return Count;}
T &operator[](unsigned i) { if(i>=Count)return Data[0];return Data[i]; }
T *Get(unsigned i) { if(i>=Count)return Data;return Data+i; }
};
struct Render2DBatch {
BFME2TextureRef Texture; int RangeA[7],RangeB[7],RangeC[7],RangeD[7];
};
struct Render2DBatches {
Render2DBatch *Start,*End,*Capacity;
unsigned size() const { return End-Start; }
Render2DBatch &operator[](unsigned i) { return Start[i]; }
};
class Render2DClass {
public: void Render(); void Reset();
private:
unsigned Shader; Vector2 CoordinateScale,CoordinateOffset;
Render2DArray<BfmeRenderVertex> Vertices;
Render2DArray<unsigned short> Indices;
Render2DBatches Batches; BFME2TextureRef Texture; int CurrentBatch; bool Dirty; char tail[3];
};
void Render2DClass::Render()
{
// Twenty-four inert initialized locals. cl breaks load-order ties by symbol
// number (docs/recipes.md, "Local count decides commutative operand order"):
// with them the 27 inlined StringClass(0,true) snapshot terminator stores
// take retail's buffer-first form at sites 1-13 (except 4) and the
// terminator-first form after; k=24 and k=56 match, every other k in
// 0..63 misplaces the boundary.
int tieBreak0=0, tieBreak1=0, tieBreak2=0, tieBreak3=0, tieBreak4=0, tieBreak5=0;
int tieBreak6=0, tieBreak7=0, tieBreak8=0, tieBreak9=0, tieBreak10=0, tieBreak11=0;
int tieBreak12=0, tieBreak13=0, tieBreak14=0, tieBreak15=0, tieBreak16=0, tieBreak17=0;
int tieBreak18=0, tieBreak19=0, tieBreak20=0, tieBreak21=0, tieBreak22=0, tieBreak23=0;
if(!Vertices.Length()) return;
Matrix4x4 view,proj;
DX8Wrapper::Get_Transform(D3DTS_VIEW,view);
DX8Wrapper::Get_Transform(D3DTS_PROJECTION,proj);
D3DVIEWPORT8 vp; vp.X=0; vp.Y=0;
vp.Width=DX8Wrapper::Get_Device_Resolution_Width();
vp.Height=DX8Wrapper::Get_Device_Resolution_Height();
vp.MinZ=0; vp.MaxZ=1;
DX8Wrapper::Set_Viewport(&vp);
VertexMaterialClass *vm=VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_DIFFUSE);
DX8Wrapper::Set_Material(vm); REF_PTR_RELEASE(vm);
DX8Wrapper::Set_World_Identity(); DX8Wrapper::Set_View_Identity();
{ Matrix4x4 identity(true);
DX8Wrapper::Set_Transform(D3DTS_PROJECTION,identity); }
DynamicVBAccessClass vb(BUFFER_TYPE_DYNAMIC_DX8,5,(Indices.Length() ? Vertices.Length() : Vertices.Length()),0);
DynamicIBAccessClass ib(BUFFER_TYPE_DYNAMIC_DX8,(Vertices.Length() ? Indices.Length() : Indices.Length()));
{
DynamicVBAccessClass::WriteLock vlock(&vb);
memcpy(vlock.Get_Formatted_Vertex_Array(),Vertices.Get(0),Vertices.Length()*sizeof(BfmeRenderVertex));
DynamicIBAccessClass::WriteLockClass ilock(&ib);
unsigned short *out=ilock.Get_Index_Array();
for(unsigned b=0;b<Batches.size();++b) {
Render2DBatch &batch=Batches[(Batches.Start ? b : b)]; BFME2Set_Texture(0,batch.Texture);
for(unsigned mode=0;mode<7;++mode) {
int head=batch.RangeA[mode];
if(head<0) continue;
BfmeRenderVertex *run=Vertices.Get(head);
while(run) {
memcpy(out,&Indices[run->IndexStart],run->IndexCount*sizeof(unsigned short));
out+=run->IndexCount;
run=run->NextRun?Vertices.Get(run->NextRun):0;
_ReadWriteBarrier();
}
}
}
}
DX8Wrapper::Set_Vertex_Buffer(vb); DX8Wrapper::Set_Index_Buffer(ib,0);
volatile bool override_states=false; int start_index=0;
for(unsigned b=0;b<Batches.size();++b) {
Render2DBatch &batch=Batches[(Batches.Start ? b : b)]; BFME2Set_Texture(0,batch.Texture);
for(unsigned mode=0;mode<7;++mode) {
if(batch.RangeA[mode]<0) continue;
if(override_states) {
override_states=false; BFME2Set_Texture(1,BFME2TextureRef());
if(DX8Wrapper::Get_Current_Caps()->Get_Max_Textures_Per_Pass()>=3) {
BFME2Set_Texture(2,BFME2TextureRef());
DX8Wrapper::Set_DX8_Texture_Stage_State(2,D3DTSS_TEXCOORDINDEX,2);
DX8Wrapper::Set_DX8_Texture_Stage_State(2,D3DTSS_COLOROP,1);
DX8Wrapper::Set_DX8_Texture_Stage_State(2,D3DTSS_ALPHAOP,1);
}
ShaderClass::Invalidate();
}
ShaderClass shader;
shader.Set_Depth_Mask((ShaderClass::DepthMaskType)g_Va00DEC4A0);
shader.Set_Alpha_Test((ShaderClass::AlphaTestType)g_Va00DEC4A4);
shader.Set_Depth_Compare((ShaderClass::DepthCompareType)G00DB5FBC);
shader.Set_Src_Blend_Func((ShaderClass::SrcBlendFuncType)G00DB5FC0);
shader.Set_Dst_Blend_Func((ShaderClass::DstBlendFuncType)G00DB5FC4);
shader.Set_Fog_Func(ShaderClass::FOG_DISABLE);
shader.Set_Primary_Gradient((ShaderClass::PriGradientType)6);
shader.Set_Texturing(ShaderClass::TEXTURING_ENABLE);
if(!batch.Texture.Ptr)shader.Set_Texturing(ShaderClass::TEXTURING_DISABLE);
if(mode==5)shader.Set_Alpha_Test(ShaderClass::ALPHATEST_ENABLE);else shader.Set_Alpha_Test(ShaderClass::ALPHATEST_DISABLE);
shader.Set_Cull_Mode(ShaderClass::CULL_MODE_DISABLE);
if(mode==0 || mode==4 || mode==5) {shader.Set_Src_Blend_Func(ShaderClass::SRCBLEND_ONE);shader.Set_Dst_Blend_Func(ShaderClass::DSTBLEND_ZERO);}
else if(mode==1) {shader.Set_Src_Blend_Func(ShaderClass::SRCBLEND_ONE);shader.Set_Dst_Blend_Func(ShaderClass::DSTBLEND_ONE);}
DX8Wrapper::Set_Shader(shader);
if(mode==6 && batch.Texture.Ptr) {
override_states=true;DX8Wrapper::Apply_Render_State_Changes();
DX8Wrapper::Set_DX8_Texture_Stage_State(0,D3DTSS_ALPHAOP,2);
DX8Wrapper::Set_DX8_Texture_Stage_State(0,D3DTSS_ALPHAARG1,0);
} else if(mode==3 || mode==4) {
override_states=true;DX8Wrapper::Apply_Render_State_Changes();
if(DX8Wrapper::Get_Current_Caps()->Support_Dot3() && DX8Wrapper::Get_Current_Caps()->Get_Max_Textures_Per_Pass()>=3) {
BFME2Set_Texture(1,batch.Texture);BFME2Set_Texture(2,batch.Texture);
DX8Wrapper::Set_DX8_Render_State(D3DRS_TEXTUREFACTOR,0x8092a587);
DX8Wrapper::Set_DX8_Texture_Stage_State(0,D3DTSS_COLORARG0,0x23);
DX8Wrapper::Set_DX8_Texture_Stage_State(0,D3DTSS_COLORARG1,2);
DX8Wrapper::Set_DX8_Texture_Stage_State(0,D3DTSS_COLORARG2,0x23);
DX8Wrapper::Set_DX8_Texture_Stage_State(0,D3DTSS_COLOROP,0x19);
DX8Wrapper::Set_DX8_Texture_Stage_State(1,D3DTSS_COLORARG1,1);
DX8Wrapper::Set_DX8_Texture_Stage_State(1,D3DTSS_COLORARG2,3);
DX8Wrapper::Set_DX8_Texture_Stage_State(1,D3DTSS_COLOROP,0x18);
DX8Wrapper::Set_DX8_Texture_Stage_State(2,D3DTSS_TEXCOORDINDEX,0);
DX8Wrapper::Set_DX8_Texture_Stage_State(2,D3DTSS_COLORARG1,1);
DX8Wrapper::Set_DX8_Texture_Stage_State(2,D3DTSS_COLOROP,2);
DX8Wrapper::Set_DX8_Texture_Stage_State(2,D3DTSS_ALPHAARG1,2);
DX8Wrapper::Set_DX8_Texture_Stage_State(2,D3DTSS_ALPHAARG2,0);
DX8Wrapper::Set_DX8_Texture_Stage_State(2,D3DTSS_ALPHAOP,4);
DX8Wrapper::Set_DX8_Texture_Stage_State(3,D3DTSS_COLOROP,1);
DX8Wrapper::Set_DX8_Texture_Stage_State(3,D3DTSS_ALPHAOP,1);
} else {
DX8Wrapper::Set_DX8_Render_State(D3DRS_TEXTUREFACTOR,0x60606060);
DX8Wrapper::Set_DX8_Texture_Stage_State(0,D3DTSS_COLORARG1,2);
DX8Wrapper::Set_DX8_Texture_Stage_State(0,D3DTSS_COLORARG2,3);
DX8Wrapper::Set_DX8_Texture_Stage_State(0,D3DTSS_COLOROP,4);
}
}
if(g_Va00DEC4A8) Rva00118810();
DX8Wrapper::Draw_Triangles(start_index,batch.RangeD[mode]/3,0,Vertices.Length());
start_index+=batch.RangeD[mode];
}
}
DX8Wrapper::Set_Transform(D3DTS_VIEW,view);DX8Wrapper::Set_Transform(D3DTS_PROJECTION,proj);
BFME2Set_Texture(0,BFME2TextureRef());
if(override_states) {
BFME2Set_Texture(1,BFME2TextureRef());
if(DX8Wrapper::Get_Current_Caps()->Get_Max_Textures_Per_Pass()>=3) {
BFME2Set_Texture(2,BFME2TextureRef());
DX8Wrapper::Set_DX8_Texture_Stage_State(2,D3DTSS_TEXCOORDINDEX,2);
DX8Wrapper::Set_DX8_Texture_Stage_State(2,D3DTSS_COLOROP,1);
DX8Wrapper::Set_DX8_Texture_Stage_State(2,D3DTSS_ALPHAOP,1);
}
ShaderClass::Invalidate();
}
if(g_Va00DEC4A8) DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILENABLE,0);
Reset();
}
