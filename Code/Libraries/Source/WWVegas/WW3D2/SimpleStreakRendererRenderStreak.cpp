// cl: /O1 /Ireference/shims/bfme_d3d8_sdk_settransform /I. /DBFME_WWSTRING_NATIVE_CSTR_ASSIGN /Ireference/shims/wwstring_teardown/zhmd /arch:SSE /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// stlport
// SPDX-License-Identifier: GPL-3.0-or-later
// Adapted from Command & Conquer Generals Zero Hour, copyright 2025 Electronic Arts Inc.
// SimpleStreakRendererClass::RenderStreak (retail 0x00126433, 11984 B; WB twin 0xA1E840), kept on
// the address-derived class name Rva00126314. Evidence and the numbering record are in
// reverse/attempt_support/0x00126433_simplestreak_render.md.
// The device declaration comes from reference/shims/bfme_d3d8_sdk_settransform (SDK-typed
// SetTransform); u_values is stored element by element before `last`, in WB's order.
// Link view first: Vector4(x,y,z,w) stays inline without emitting an SSE
// copy that competes with retail's integer-move owner (0x006D8A30).
#include "reference/shims/bfme_matrix3d_sse_link/vector4.h"
#define Matrix4x4 Matrix4
// ShaderClass's copy ctor is emitted here; every other copy is the speed-optimized
// one (mov edx), so this /O1 unit compiles shader.h for speed to agree with it.
#pragma optimize("gty", on)
#define inline __forceinline
#include "reference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2/shader.h"
#undef inline
#pragma optimize("", on)
void operator delete[](void*) throw();
#include "reference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2/texture.h"
#include "reference/shims/bfmestreak/streakrender.h"
#if defined(_MSC_VER)
#pragma once
#endif
#ifndef WW3D_H
#define WW3D_H
#include "always.h"
#include "vector3.h"
#include "layer.h"
#include "w3derr.h"
#include "robjlist.h"
class		SceneClass;
class		CameraClass;
class		ShaderClass;
class		DX8Wrapper;
struct	RenderStatistics;
class		FrameGrabClass;
class		VertexMaterialClass;
class		ExtraMaterialPassClass;
class		RenderInfoClass;
class		RenderDeviceDescClass;
class		StringClass;
class		LightEnvironmentClass;
class		MaterialPassClass;
class 	StaticSortListClass;
#define MESH_RENDER_SNAPSHOT_ENABLED
#define SNAPSHOT_SAY(x)
class WW3D
{
private: static bool IsCurrentlyRenderingShadowMap;
public: static bool Is_Currently_Rendering_Shadow_Map(){return IsCurrentlyRenderingShadowMap;}
public:
enum PrelitModeEnum {
PRELIT_MODE_VERTEX,
PRELIT_MODE_LIGHTMAP_MULTI_PASS,
PRELIT_MODE_LIGHTMAP_MULTI_TEXTURE
};
enum MeshDrawModeEnum {
MESH_DRAW_MODE_OLD,
MESH_DRAW_MODE_NEW,
MESH_DRAW_MODE_DEBUG_DRAW,
MESH_DRAW_MODE_DEBUG_CLIP,
MESH_DRAW_MODE_DEBUG_BOX,
MESH_DRAW_MODE_NONE,
MESH_DRAW_MODE_DX8_ONLY
};
enum NPatchesGapFillingModeEnum {
NPATCHES_GAP_FILLING_DISABLED,
NPATCHES_GAP_FILLING_ENABLED,
NPATCHES_GAP_FILLING_FORCE
};
enum ScreenShotFormatEnum {
TGA,
BMP
};
static WW3DErrorType		Init(void * hwnd, char *defaultpal = NULL, bool lite = false);
static WW3DErrorType		Shutdown(void);
static bool					Is_Initted(void)								{ return IsInitted; }
static const int			Get_Render_Device_Count(void);
static const char *		Get_Render_Device_Name(int device_index);
static const RenderDeviceDescClass &								Get_Render_Device_Desc(int device = -1);
static int					Get_Render_Device(void);
static bool					Set_Render_Device( int dev=-1, int resx=-1, int resy=-1, int bits=-1, int windowed=-1, bool resize_window = false, bool reset_device=false, bool restore_assets=true);
static WW3DErrorType		Set_Render_Device( const char *dev_name, int resx=-1, int resy=-1, int bits=-1, int windowed=-1, bool resize_window = false  );
static WW3DErrorType		Set_Next_Render_Device(void);
static WW3DErrorType		Set_Any_Render_Device( void );
static void					Get_Pixel_Center(float &x, float &y);
static void					Get_Render_Target_Resolution(int & set_w,int & set_h,int & get_bits,bool & get_windowed);
static void					Get_Device_Resolution(int & set_w,int & set_h,int & get_bits,bool & get_windowed);
static bool					Set_Device_Resolution(int w=-1,int h=-1,int bits=-1,int windowed=-1, bool resize_window=false );
static bool					Is_Windowed( void );
static WW3DErrorType		Toggle_Windowed ( void );
static void					Set_Window( void *hwnd );
static void *				Get_Window( void );
static WW3DErrorType		On_Activate_App( void );
static WW3DErrorType		On_Deactivate_App( void );
static WW3DErrorType		Registry_Save_Render_Device( const char * sub_key );
static WW3DErrorType		Registry_Save_Render_Device( const char * sub_key, int device, int width, int height, int depth, bool windowed, int texture_depth );
static WW3DErrorType		Registry_Load_Render_Device( const char * sub_key, bool resize_window = false );
static bool					Registry_Load_Render_Device( const char * sub_key, char *device, int device_len, int &width, int &height, int &depth, int &windowed, int& texture_depth);
static void					Set_Texture_Filter(int filter);
static int					Get_Texture_Filter() { return TextureFilter; }
static WW3DErrorType		Begin_Render(bool clear = false,bool clearz = true,const Vector3 & color = Vector3(0,0,0), float dest_alpha=0.0f, void(*network_callback)(void) = NULL);
static WW3DErrorType		Render(const LayerListClass & layerlist);
static WW3DErrorType		Render(const LayerClass & layer);
static WW3DErrorType		Render(SceneClass * scene,CameraClass * cam,bool clear = false,bool clearz = false,const Vector3 & color = Vector3(0,0,0));
static WW3DErrorType		Render(RenderObjClass & obj,RenderInfoClass & rinfo);
static void					Flush(RenderInfoClass & rinfo);
static WW3DErrorType		End_Render(bool flip_frame = true);
static bool					Is_Rendering( void ) { return( IsRendering ); }
static void Flip_To_Primary(void);
static void					Sync( unsigned int sync_time );
static unsigned int		Get_Sync_Time(void) { return SyncTime; }
static unsigned int     Get_Frame_Time(void) { return SyncTime - PreviousSyncTime; }
static unsigned int     Get_Frame_Count(void) { return FrameCount; }
static unsigned int		Get_Last_Frame_Poly_Count(void);
static unsigned int		Get_Last_Frame_Vertex_Count(void);
static void					Make_Screen_Shot( const char * filename = "ScreenShot", const float gamma = 1.3f, const ScreenShotFormatEnum format = TGA);
static void					Start_Movie_Capture( const char * filename_base = "Movie", float frame_rate = 15);
static void					Stop_Movie_Capture( void);
static void					Toggle_Movie_Capture( const char * filename_base = "Movie", float frame_rate = 15);
static void					Start_Single_Frame_Movie_Capture(const char *filename_base = "Frames");
static void					Capture_Next_Movie_Frame();
static void					Update_Movie_Capture( void);
static float				Get_Movie_Capture_Frame_Rate( void);
static void					Pause_Movie(bool mode);
static bool					Is_Movie_Paused();
static bool					Is_Recording_Next_Frame();
static bool					Is_Movie_Ready();
static void             Set_Ext_Swap_Interval(long swap);
static long             Get_Ext_Swap_Interval(void);
static void					Set_Texture_Reduction( int value, int min_dim=1 );
static int					Get_Texture_Reduction( void );
static int					Get_Texture_Min_Dimension(void);
static void					Enable_Large_Texture_Extra_Reduction(bool onoff);
static bool					Is_Large_Texture_Extra_Reduction_Enabled(void);
static void					_Invalidate_Mesh_Cache();
static void					_Invalidate_Textures();
static void					Set_Thumbnail_Enabled(bool b) { ThumbnailEnabled=b; }
static bool					Get_Thumbnail_Enabled() { return ThumbnailEnabled; }
static void					Enable_Sorting(bool onoff);
static bool					Is_Sorting_Enabled(void)					{ return IsSortingEnabled; }
static void					Set_Screen_UV_Bias( bool onoff )			{ IsScreenUVBiased = onoff; }
static bool					Is_Screen_UV_Biased( void )				{ return IsScreenUVBiased; }
static void					Set_Collision_Box_Display_Mask(int mask);
static int					Get_Collision_Box_Display_Mask(void);
static void					Set_Default_Native_Screen_Size(float dnss)	{ DefaultNativeScreenSize = dnss; }
static float				Get_Default_Native_Screen_Size(void)			{ return DefaultNativeScreenSize; }
static void					Normalize_Coordinates(int x, int y, float &fx, float &fy);
static VertexMaterialClass *	Peek_Default_Debug_Material(void);
static ShaderClass		Peek_Default_Debug_Shader(void);
static ShaderClass		Peek_Backface_Debug_Shader(void);
static ShaderClass		Peek_Lightmap_Debug_Shader(void);
static void					Set_Prelit_Mode (PrelitModeEnum mode)			{ PrelitMode = mode; }
static PrelitModeEnum 	Get_Prelit_Mode ()									{ return (PrelitMode); }
static bool					Supports_Prelit_Mode (PrelitModeEnum mode)	{ return (true); }
static void					Expose_Prelit (bool onoff)							{ ExposePrelit = onoff; }
static bool					Expose_Prelit ()										{ return (ExposePrelit); }
static void					Set_Texture_Bitdepth(int bitdepth);
static int					Get_Texture_Bitdepth();
static void					Set_Mesh_Draw_Mode (MeshDrawModeEnum mode)	{ MeshDrawMode = mode; }
static MeshDrawModeEnum Get_Mesh_Draw_Mode ()								{ return (MeshDrawMode); }
static void					Set_NPatches_Gap_Filling_Mode (NPatchesGapFillingModeEnum mode);
static NPatchesGapFillingModeEnum 	Get_NPatches_Gap_Filling_Mode () { return (NPatchesGapFillingMode); }
static void					Set_NPatches_Level(unsigned level);
static unsigned			Get_NPatches_Level() { return NPatchesLevel; }
static void					Enable_Texturing(bool b);
static bool					Is_Texturing_Enabled() { return IsTexturingEnabled; }
static bool					Is_Coloring_Enabled() { return (IsColoringEnabled == 0) ? false : true; }
static void					Enable_Coloring(unsigned int color);
static int					Get_Last_Frame_Memory_Allocation_Count() { return LastFrameMemoryAllocations; }
static int					Get_Last_Frame_Memory_Free_Count() { return LastFrameMemoryFrees; }
static void					Enable_Decals(bool onoff)					{ AreDecalsEnabled = onoff; }
static bool					Are_Decals_Enabled(void)					{ return AreDecalsEnabled; }
static void					Set_Decal_Rejection_Distance(float d)	{ DecalRejectionDistance = d; }
static float				Get_Decal_Rejection_Distance(void)		{ return DecalRejectionDistance; }
static void					Enable_Static_Sort_Lists(bool onoff)	{ AreStaticSortListsEnabled = onoff; }
static bool					Are_Static_Sort_Lists_Enabled(void)		{ return AreStaticSortListsEnabled; }
static void					Enable_Munge_Sort_On_Load(bool onoff)	{ MungeSortOnLoad=onoff; }
static bool					Is_Munge_Sort_On_Load_Enabled(void)		{ return MungeSortOnLoad; }
static void					Add_To_Static_Sort_List(RenderObjClass *robj, unsigned int sort_level);
static void					Render_And_Clear_Static_Sort_Lists(RenderInfoClass & rinfo);
static void					Override_Current_Static_Sort_Lists(StaticSortListClass * sort_list);
static void					Reset_Current_Static_Sort_Lists_To_Default(void);
static void					Enable_Overbright_Modify_On_Load(bool onoff)	{ OverbrightModifyOnLoad = onoff; }
static bool					Is_Overbright_Modify_On_Load_Enabled(void)	{ return OverbrightModifyOnLoad; }
static bool					Is_Snapshot_Activated()						{ return SnapshotActivated; }
static void					Activate_Snapshot(bool b)					{ SnapshotActivated=b; }
static long             UserStat0;
static long             UserStat1;
static long             UserStat2;
static void					Set_Gamma(float gamma,float bright,float contrast,bool calibrate=true);
private:
enum
{
DEFAULT_RESOLUTION_WIDTH =			640,
DEFAULT_RESOLUTION_HEIGHT =		480,
DEFAULT_BIT_DEPTH =					16
};
static void					Read_Gerd_Render_Device_Description(RenderDeviceDescClass &desc);
static void					Update_Pixel_Center(void);
static void					Allocate_Debug_Resources(void);
static void					Release_Debug_Resources(void);
static unsigned int				SyncTime;
static unsigned int           PreviousSyncTime;
static float						PixelCenterX;
static float						PixelCenterY;
static bool							IsInitted;
static bool							IsRendering;
static bool							IsCapturing;
static bool							IsSortingEnabled;
static bool							IsScreenUVBiased;
static bool							IsBackfaceDebugEnabled;
static bool							AreDecalsEnabled;
static float						DecalRejectionDistance;
static bool							AreStaticSortListsEnabled;
static bool							MungeSortOnLoad;
static bool							OverbrightModifyOnLoad;
static FrameGrabClass *			Movie;
static bool							PauseRecord;
static bool							RecordNextFrame;
static int							FrameCount;
static VertexMaterialClass *	DefaultDebugMaterial;
static VertexMaterialClass *	BackfaceDebugMaterial;
static ShaderClass				DefaultDebugShader;
static ShaderClass				LightmapDebugShader;
static PrelitModeEnum			PrelitMode;
static bool							ExposePrelit;
static int							TextureFilter;
static bool							SnapshotActivated;
static bool							ThumbnailEnabled;
static MeshDrawModeEnum			MeshDrawMode;
static NPatchesGapFillingModeEnum NPatchesGapFillingMode;
static unsigned NPatchesLevel;
static bool							IsTexturingEnabled;
static bool							IsColoringEnabled;
static bool							Lite;
static float						DefaultNativeScreenSize;
static StaticSortListClass * DefaultStaticSortLists;
static StaticSortListClass * CurrentStaticSortLists;
static int							LastFrameMemoryAllocations;
static int							LastFrameMemoryFrees;
};
struct RenderStatistics
{
double	ElapsedSeconds;
int      FramesRendered;
double	TrianglesReceived;
double	TrianglesSubmitted;
double	TrianglesSorted;
double	VerticesReceived;
double	VerticesSubmitted;
double	ViewStateChanges;
double	DrawStateChanges;
double	TextureChanges;
double	TextureParameterChanges;
double	TexturesCreated;
double	PaletteChanges;
double	ShaderChanges;
double	DrawCommands;
double	TrianglesClipRemoved;
double	TrianglesClipCreated;
double	DeviceDriverCalls;
double	TextureTransfers;
double	PixelsDrawn;
double	PixelsRejected;
long		Hits;
long		Misses;
long		Insertions;
long		Removals;
long		MemUsed;
long		MaxMemory;
long     UserStat0;
long     UserStat1;
long     UserStat2;
};
#endif
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
unsigned							location_offset[5];
unsigned							texcoord_offset[D3DDP_MAXTEXCOORD];
unsigned							diffuse_offset;
unsigned							specular_offset;
public:
FVFInfoClass(unsigned FVF, unsigned vertex_size=0);
inline unsigned Get_Location_Offset(unsigned int n) const { return location_offset[n]; }
inline unsigned Get_Normal_Offset() const { return location_offset[1]; }
#ifdef WWDEBUG
inline unsigned Get_Tex_Offset(unsigned int n) const { WWASSERT(n<D3DDP_MAXTEXCOORD); return texcoord_offset[n]; }
#else
// LINK: inline-only, so no copy competes with the +0x14 views linked earlier.
__declspec(dllimport) __forceinline unsigned Get_Tex_Offset(unsigned int n) const { return texcoord_offset[n]; }
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
// ?Get_Formatted_Vertex_Array@WriteLock@DynamicVBAccessClass present-unmatched
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
// ?DX8_Stats@DX8_Stats present-unmatched
DX8_Stats::DX8_Stats(void) {
m_disableConsole = m_showingStats = m_disableTerrain = m_disableWater = m_disableOverhead = m_disableObjects = false;
m_sleepTime = 0;
m_debugLinesToShow = -1;
}
};
#endif
#include "RenderStateStruct.h"
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
static void Set_Vertex_Shader(DWORD);
static void Set_Pixel_Shader(DWORD);
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
static unsigned Convert_Color_Clamp(Vector4);
static void Clamp_Color(Vector4&);
static IDirect3DDevice8* _Get_D3D_Device8() { return D3DDevice; }
protected:
static IDirect3DDevice8 *D3DDevice;
static RenderStateStruct render_state;
static unsigned render_state_changed;
static float ZNear,ZFar;
static unsigned matrix_changes;
static Matrix4x4 ProjectionMatrix;
static Matrix4x4 DeviceProjectionMatrix;
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
color[0] = color[0] <= 0.0f ? 0.0f : (color[0] > 1.0f ? 1.0f : color[0]);
color[1] = color[1] <= 0.0f ? 0.0f : (color[1] > 1.0f ? 1.0f : color[1]);
color[2] = color[2] <= 0.0f ? 0.0f : (color[2] > 1.0f ? 1.0f : color[2]);
color[3] = color[3] <= 0.0f ? 0.0f : (color[3] > 1.0f ? 1.0f : color[3]);
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
WWINLINE unsigned int DX8Wrapper::Convert_Color_Clamp(Vector4 color)
{
Clamp_Color(color);
return Convert_Color(reinterpret_cast<const Vector3&>(color),color[3]);
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
WWINLINE void DX8Wrapper::Set_Transform(D3DTRANSFORMSTATETYPE transform,const Matrix4x4& matrix4x4)
{
switch ((int)transform) {
case D3DTS_WORLD:
render_state.world=matrix4x4.Transpose();
render_state_changed|=(unsigned)WORLD_CHANGED;
render_state_changed&=~(unsigned)WORLD_IDENTITY;
break;
case D3DTS_VIEW:
render_state.view=matrix4x4.Transpose();
render_state_changed|=(unsigned)VIEW_CHANGED;
render_state_changed&=~(unsigned)VIEW_IDENTITY;
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
WWINLINE void DX8Wrapper::Get_Transform(D3DTRANSFORMSTATETYPE transform, Matrix4x4& matrix4x4)
{
switch ((int)transform)
{
case D3DTS_WORLD:
if (render_state_changed & WORLD_IDENTITY) matrix4x4.Make_Identity();
else matrix4x4 = render_state.world.Transpose();
break;
case D3DTS_VIEW:
if (render_state_changed & VIEW_IDENTITY) matrix4x4.Make_Identity();
else matrix4x4 = render_state.view.Transpose();
break;
case D3DTS_PROJECTION:
matrix4x4 = DeviceProjectionMatrix.Transpose();
break;
default:
matrix4x4.Make_Identity();
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
// TU-local: SortingRendererForward.cpp owns the out-of-line 0x0012630B row.
static __forceinline void Rva0012630BForward(const TargetCenter3 &targetCenter3,unsigned start_index,unsigned polygon_count,unsigned min_vertex_index,unsigned vertex_count){BfmeSortingDispatchAt0012FE00::Insert(targetCenter3,start_index,polygon_count,min_vertex_index,vertex_count);}
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
extern unsigned number_of_DX8_calls;
struct SimpleShaderDeviceVTable {void *unused0[92]; long (__stdcall *SetVS)(void*,unsigned); void *unused93[14];long (__stdcall *SetPS)(void*,unsigned);};
struct SimpleShaderDevice {SimpleShaderDeviceVTable *v;};
struct SimpleD3DDevice9 {virtual long __stdcall m0();virtual long __stdcall m1();virtual long __stdcall m2();virtual long __stdcall m3();virtual long __stdcall m4();virtual long __stdcall m5();virtual long __stdcall m6();virtual long __stdcall m7();virtual long __stdcall m8();virtual long __stdcall m9();virtual long __stdcall m10();virtual long __stdcall m11();virtual long __stdcall m12();virtual long __stdcall m13();virtual long __stdcall m14();virtual long __stdcall m15();virtual long __stdcall m16();virtual long __stdcall m17();virtual long __stdcall m18();virtual long __stdcall m19();virtual long __stdcall m20();virtual long __stdcall m21();virtual long __stdcall m22();virtual long __stdcall m23();virtual long __stdcall m24();virtual long __stdcall m25();virtual long __stdcall m26();virtual long __stdcall m27();virtual long __stdcall m28();virtual long __stdcall m29();virtual long __stdcall m30();virtual long __stdcall m31();virtual long __stdcall m32();virtual long __stdcall m33();virtual long __stdcall m34();virtual long __stdcall m35();virtual long __stdcall m36();virtual long __stdcall m37();virtual long __stdcall m38();virtual long __stdcall m39();virtual long __stdcall m40();virtual long __stdcall m41();virtual long __stdcall m42();virtual long __stdcall m43();virtual long __stdcall SetTransform(D3DTRANSFORMSTATETYPE,const D3DMATRIX*);virtual long __stdcall m45();virtual long __stdcall m46();virtual long __stdcall m47();virtual long __stdcall m48();virtual long __stdcall m49();virtual long __stdcall m50();virtual long __stdcall m51();virtual long __stdcall m52();virtual long __stdcall m53();virtual long __stdcall m54();virtual long __stdcall m55();virtual long __stdcall m56();virtual long __stdcall m57();virtual long __stdcall m58();virtual long __stdcall m59();virtual long __stdcall m60();virtual long __stdcall m61();virtual long __stdcall m62();virtual long __stdcall m63();virtual long __stdcall m64();virtual long __stdcall m65();virtual long __stdcall m66();virtual long __stdcall m67();virtual long __stdcall m68();virtual long __stdcall m69();virtual long __stdcall m70();virtual long __stdcall m71();virtual long __stdcall m72();virtual long __stdcall m73();virtual long __stdcall m74();virtual long __stdcall m75();virtual long __stdcall m76();virtual long __stdcall m77();virtual long __stdcall m78();virtual long __stdcall m79();virtual long __stdcall m80();virtual long __stdcall m81();virtual long __stdcall m82();virtual long __stdcall m83();virtual long __stdcall m84();virtual long __stdcall m85();virtual long __stdcall m86();virtual long __stdcall m87();virtual long __stdcall m88();virtual long __stdcall m89();virtual long __stdcall m90();virtual long __stdcall m91();virtual long __stdcall SetVertexShader(unsigned);virtual long __stdcall m93();virtual long __stdcall m94();virtual long __stdcall m95();virtual long __stdcall m96();virtual long __stdcall m97();virtual long __stdcall m98();virtual long __stdcall m99();virtual long __stdcall m100();virtual long __stdcall m101();virtual long __stdcall m102();virtual long __stdcall m103();virtual long __stdcall m104();virtual long __stdcall m105();virtual long __stdcall m106();virtual long __stdcall SetPixelShader(unsigned);};
// ?Set_Vertex_Shader@DX8Wrapper present-unmatched
__forceinline void DX8Wrapper::Set_Vertex_Shader(DWORD vertex_shader){((SimpleD3DDevice9*)DX8Wrapper::_Get_D3D_Device8())->SetVertexShader(vertex_shader);number_of_DX8_calls++;}
// ?Set_Pixel_Shader@DX8Wrapper present-unmatched
__forceinline void DX8Wrapper::Set_Pixel_Shader(DWORD pixel_shader){((SimpleD3DDevice9*)DX8Wrapper::_Get_D3D_Device8())->SetPixelShader(pixel_shader);number_of_DX8_calls++;}
float Rva000032B8(float);
class SimpleShadowPass { public: virtual void Delete_This(); virtual void slot1(); virtual bool Begin(unsigned*,unsigned); virtual void BeginPass(unsigned); virtual void slot4(); virtual void EndPass(); virtual void End(); int refs; };
class FXShaderSetup;
// Shadow FX holder (WB refcount.h shapes); its out-of-line destructor and operator= are retail
// 0x0007B724 (rowed as Rva00087A93) and 0x00072A94 (rowed as Rva00072A94). Both copy the held
// pointer into a local before the decrement, as those rows do, so neither reloads it.
class Rva00087A93 { public: Rva00087A93(SimpleShadowPass*obj=0):m_obj(obj){} bool IsBound()const{return m_obj!=0;} ~Rva00087A93(){SimpleShadowPass*obj=m_obj;if(obj&&--obj->refs==0)obj->Delete_This();} Rva00087A93&operator=(const Rva00087A93&r){if(this!=&r){if(r.m_obj)r.m_obj->refs++;SimpleShadowPass*old=m_obj;if(old&&--old->refs==0)old->Delete_This();m_obj=r.m_obj;}return *this;} SimpleShadowPass*operator->()const{return m_obj;} SimpleShadowPass*m_obj; };
#pragma comment(linker, "/alternatename:?Rva000032B8@@YAMM@Z=?Rva000032B8@@YANM@Z")
#define s_AlphaShadowFXShader (*(Rva00087A93*)&g_Va00DEE870)
#define s_AdditiveShadowFXShader (*(Rva00087A93*)&g_Va00DEE86C)
class Rva007B7024Object;
extern Rva007B7024Object *g_Va00DEE870;
extern Rva007B7024Object *g_Va00DEE86C;
class ShroudFilter {public: int unknown[3],u,v; void Set_U_Addr_Mode(int m){u=m;} void Set_V_Addr_Mode(int m){v=m;}};
class ShroudTexture {public:ShroudFilter *getFilter();};
struct SimpleTextureRefPtr : BFME2TextureRef {SimpleTextureRefPtr(){Ptr=0;} ~SimpleTextureRefPtr(){if(Ptr)Ptr->Release_Ref();}};
struct SimpleTextureTemp : SimpleTextureRefPtr {SimpleTextureTemp(){}};
struct SimpleTextureHolder { TextureClass *Ptr; bool Is_Valid() const { return Ptr != 0; } };
class Rva00126314 {public:
__forceinline void agpad(){}

void RenderStreak(RenderInfoClass&,const Matrix3D&,unsigned,Vector3*,float*,const SphereClass&);
SimpleTextureHolder Texture; ShaderClass Shader; float Width; Vector3 Color; float Opacity,TextureLength; bool SortingDisabled; int Is_Sorting_Disabled()const{return SortingDisabled;}
};
void Rva00126314::RenderStreak(RenderInfoClass &rinfo,const Matrix3D &transform,unsigned num_points,Vector3 *input_points,float *texture_positions,const SphereClass &obj_sphere)
{
if(WW3D::Is_Currently_Rendering_Shadow_Map() && (!s_AlphaShadowFXShader.IsBound() || !s_AdditiveShadowFXShader.IsBound()))return;
Matrix4 view;
DX8Wrapper::Get_Transform(D3DTS_VIEW,view);
Matrix4 identity(true);DX8Wrapper::Set_Transform(D3DTS_WORLD,identity);DX8Wrapper::Set_Transform(D3DTS_VIEW,identity);
const float parallel_factor=.9f;unsigned chunk_size=129;if(chunk_size>num_points)chunk_size=num_points;
for(unsigned chunkIndex=0;chunkIndex<num_points-1;chunkIndex+=chunk_size-1){
unsigned point_cnt=num_points-chunkIndex;point_cnt=MIN(point_cnt,chunk_size);unsigned pointIndex,segmentIndex,intersectionIndex;
Vector3 xformed_pts[129];
Matrix3D view2(view[0].X,view[0].Y,view[0].Z,view[0].W,view[1].X,view[1].Y,view[1].Z,view[1].W,view[2].X,view[2].Y,view[2].Z,view[2].W);
Matrix3D modelview;modelview.mul(view2,transform);
VectorProcessorClass::Transform(xformed_pts,input_points+chunkIndex,modelview,point_cnt);
Vector3 *points=xformed_pts;float u_values[2];u_values[0]=0.0f;u_values[1]=1.0f;float tex_v[129];
float last=texture_positions[point_cnt-1];float end=last-TextureLength;
for(pointIndex=0;pointIndex<point_cnt;++pointIndex)tex_v[pointIndex]=(texture_positions[pointIndex]-end)/TextureLength;
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
};
float radius = Width * 0.5f;
LineSegmentIntersection intersection[MAX_STREAK_POINT_BUFFER_SIZE + 1][NUM_EDGES];
for (segmentIndex = 1; segmentIndex < point_cnt; segmentIndex++)
{
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
}
else
{
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
intersection[0][BOTTOM_EDGE].PointCount = 0;
intersection[0][BOTTOM_EDGE].NextSegmentID = 0;
intersection[0][BOTTOM_EDGE].Point.Set(0,0,0);
intersection[0][BOTTOM_EDGE].TexV = 0.0f;
intersection[0][BOTTOM_EDGE].Direction.Set(1,0,0);
intersection[1][TOP_EDGE].PointCount = 1;
intersection[1][TOP_EDGE].NextSegmentID = 1;
intersection[1][TOP_EDGE].Point = points[0];
intersection[1][TOP_EDGE].TexV = tex_v[0];
intersection[1][BOTTOM_EDGE].PointCount = 1;
intersection[1][BOTTOM_EDGE].NextSegmentID = 1;
intersection[1][BOTTOM_EDGE].Point = points[0];
intersection[1][BOTTOM_EDGE].TexV = tex_v[0];
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
intersection[last_isec][BOTTOM_EDGE].PointCount = 1;
intersection[last_isec][BOTTOM_EDGE].NextSegmentID = numsegs + 1;
intersection[last_isec][BOTTOM_EDGE].Point = points[point_cnt - 1];
intersection[last_isec][BOTTOM_EDGE].TexV = tex_v[point_cnt - 1];
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
if (Rva000032B8(vdp) < parallel_factor)
{
Vector3::Cross_Product(segment[intersectionIndex - 1].EdgePlane[TOP_EDGE], segment[intersectionIndex].EdgePlane[TOP_EDGE],
&(intersection[intersectionIndex][TOP_EDGE].Direction));
intersection[intersectionIndex][TOP_EDGE].Direction.Normalize();
if (Vector3::Dot_Product(intersection[intersectionIndex][TOP_EDGE].Direction, midpoint) < 0.0f)
{
intersection[intersectionIndex][TOP_EDGE].Direction = -intersection[intersectionIndex][TOP_EDGE].Direction;
}
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
}
vdp = Vector3::Dot_Product(segment[intersectionIndex - 1].EdgePlane[BOTTOM_EDGE], segment[intersectionIndex].EdgePlane[BOTTOM_EDGE]);
if (Rva000032B8(vdp) < parallel_factor)
{
Vector3::Cross_Product(segment[intersectionIndex - 1].EdgePlane[BOTTOM_EDGE], segment[intersectionIndex].EdgePlane[BOTTOM_EDGE],
&(intersection[intersectionIndex][BOTTOM_EDGE].Direction));
intersection[intersectionIndex][BOTTOM_EDGE].Direction.Normalize();
if (Vector3::Dot_Product(intersection[intersectionIndex][BOTTOM_EDGE].Direction, midpoint) < 0.0f)
{
intersection[intersectionIndex][BOTTOM_EDGE].Direction = -intersection[intersectionIndex][BOTTOM_EDGE].Direction;
}
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
unsigned int vnum = num_intersections[TOP_EDGE] + num_intersections[BOTTOM_EDGE];
VertexFormatXYZUV1 vertexArray[256];
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
vertexArray[vertexIndex].u1 = u_values[0];
vertexArray[vertexIndex].v1 = intersection[1][TOP_EDGE].TexV;
vertexIndex++;
vertexArray[vertexIndex].x = bottom.X;
vertexArray[vertexIndex].y = bottom.Y;
vertexArray[vertexIndex].z = bottom.Z;
vertexArray[vertexIndex].u1 = u_values[1];
vertexArray[vertexIndex].v1 = intersection[1][BOTTOM_EDGE].TexV;
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
vertexArray[vertexIndex].u1 = u_values[0];
vertexArray[vertexIndex].v1 = intersection[top_int_idx][TOP_EDGE].TexV;
vertexIndex++;
vertexArray[vertexIndex].x = bottom.X;
vertexArray[vertexIndex].y = bottom.Y;
vertexArray[vertexIndex].z = bottom.Z;
vertexArray[vertexIndex].u1 = u_values[1];
vertexArray[vertexIndex].v1 = intersection[bottom_int_idx][BOTTOM_EDGE].TexV;
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
vertexArray[vertexIndex].u1 = u_values[1];
vertexArray[vertexIndex].v1 = intersection[bottom_int_idx][BOTTOM_EDGE].TexV;
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
vertexArray[vertexIndex].u1 = u_values[0];
vertexArray[vertexIndex].v1 = intersection[top_int_idx][TOP_EDGE].TexV;
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
bool sorting=(!Is_Sorting_Disabled())&&(Shader.Get_Dst_Blend_Func()!=ShaderClass::DSTBLEND_ZERO&&Shader.Get_Alpha_Test()==ShaderClass::ALPHATEST_DISABLE);
Rva00087A93 shadow(0);
if(WW3D::Is_Currently_Rendering_Shadow_Map()){
sorting=false; bool additive=Shader.Get_Src_Blend_Func()==ShaderClass::SRCBLEND_ONE&&Shader.Get_Dst_Blend_Func()==ShaderClass::DSTBLEND_ONE;
shadow=additive?s_AdditiveShadowFXShader:s_AlphaShadowFXShader;
BFME2Set_Texture(0,SimpleTextureTemp());
unsigned passes=0;if(!shadow->Begin(&passes,65535))continue;if(passes!=1)continue;shadow->BeginPass(0);
}else{
ShaderClass shader=Shader;shader.Set_Cull_Mode(ShaderClass::CULL_MODE_DISABLE);shader.Set_Primary_Gradient((ShaderClass::PriGradientType)6);
VertexMaterialClass *mat=VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_DIFFUSE);DX8Wrapper::Set_Material(mat);REF_PTR_RELEASE(mat);
if(Texture.Is_Valid())shader.Set_Texturing(ShaderClass::TEXTURING_ENABLE);else shader.Set_Texturing(ShaderClass::TEXTURING_DISABLE);
((ShroudTexture*)this)->getFilter()->Set_U_Addr_Mode(1);((ShroudTexture*)this)->getFilter()->Set_V_Addr_Mode(1);
DX8Wrapper::Set_Shader(shader);
}
DynamicVBAccessClass Verts(sorting?BUFFER_TYPE_DYNAMIC_SORTING:BUFFER_TYPE_DYNAMIC_DX8,5,vnum,0);
{DynamicVBAccessClass::WriteLock Lock(&Verts);unsigned char *vb=(unsigned char*)Lock.Get_Formatted_Vertex_Array();const FVFInfoClass &fvfinfo=Verts.FVF_Info();
const unsigned verticesOffset=fvfinfo.Get_Location_Offset(0),diffuseOffset=fvfinfo.Get_Diffuse_Offset(),textureOffset=fvfinfo.Get_Tex_Offset(0),vbSize=fvfinfo.Get_FVF_Size();
unsigned argb=DX8Wrapper::Convert_Color_Clamp(Vector4(Color.X,Color.Y,Color.Z,Opacity));
for(unsigned i=0;i<vnum;++i){Vector3 *vertex=(Vector3*)(vb+verticesOffset);vertex->X=vertexArray[i].x;vertex->Y=vertexArray[i].y;vertex->Z=vertexArray[i].z;
*(unsigned*)(vb+diffuseOffset)=argb;Vector2 *texture=(Vector2*)(vb+textureOffset);texture->U=vertexArray[i].u1;texture->V=vertexArray[i].v1;vb+=vbSize;}}
DynamicIBAccessClass ib_access(sorting?BUFFER_TYPE_DYNAMIC_SORTING:BUFFER_TYPE_DYNAMIC_DX8,triangleIndex*3);
{DynamicIBAccessClass::WriteLockClass lock(&ib_access);unsigned short *inds=lock.Get_Index_Array();for(unsigned i=0;i<triangleIndex;++i){*inds++=v_index_array[i].I;*inds++=v_index_array[i].J;*inds++=v_index_array[i].K;}}
DX8Wrapper::Set_Index_Buffer(ib_access,0);DX8Wrapper::Set_Vertex_Buffer(Verts);BFME2Set_Texture(0,*(BFME2TextureRef*)&Texture);
if(sorting)Rva0012630BForward(*(const TargetCenter3*)&obj_sphere,0,triangleIndex,0,vnum);else DX8Wrapper::Draw_Triangles(0,triangleIndex,0,vnum);
if(WW3D::Is_Currently_Rendering_Shadow_Map()){shadow->EndPass();shadow->End();}
}
DX8Wrapper::Set_Transform(D3DTS_VIEW,view);DX8Wrapper::Set_Vertex_Shader(0);DX8Wrapper::Set_Pixel_Shader(0);
}
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
#include <vector>
struct BfmeAssignRecord36
{
BfmeAssignRecord36(const char *, int);
char m_prefix[28];
int m_int;
char m_tail[4];
};
struct Rva0007BB16Record
{
Rva0007BB16Record(const char *name, int type) : m_record(name, type) {}
~Rva0007BB16Record();
BfmeAssignRecord36 m_record;
};
namespace _STL {
template <> vector<Rva0007BB16Record>::~vector();
}
struct Rva00082EB8Rec;
class FXShaderSetup
{
public:
virtual void Delete_This();
void Release_Ref()
{
--NumRefs;
if (NumRefs == 0)
Delete_This();
}
private:
int NumRefs;
};
RefCountPtr<FXShaderSetup> Rva00152C47_CreateFXShaderSetup(const char *, const char *,
const _STL::vector<Rva0007BB16Record> *, int);
class Rva007B7024Object;
extern Rva007B7024Object *g_Va00DEE870;
extern Rva007B7024Object *g_Va00DEE86C;
class SimpleStreakRendererClass
{
public:
static void Init(bool enableShadows);
};
