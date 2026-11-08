/* Target facts:
 * DX8Wrapper is a nonvirtual static interface with no base subobjects or instance
 * fields. No DX8Wrapper constructor, destructor or vftable is named in the matched
 * ledger. Init (RVA 0x00125620), Shutdown (0x00125DC0), Set_Vertex_Buffer
 * (0x0011D4A0), Set_Index_Buffer (0x0011D530) and Draw_Triangles (0x00120620)
 * use stack arguments and absolute state addresses, without a this pointer.
 * There is no retail constructor/destructor table disagreement for this class.
 *
 * Init clears 0x100 dwords at VA 0x00DED5F8 (0x0052565D), 0x200 at 0x00DECA38
 * (0x00525669), 0x180 at 0x00DEDFA8 (0x00525675), 0x20 at 0x00DEDF10
 * (0x00525681) and 0xA4 at 0x00DEE5D8 (0x0052568D). These are RenderStates,
 * TextureStageStates, Vertex_Shader_Constants, Pixel_Shader_Constants and the
 * separate RenderStateStruct global. The shader constant setters (RVA 0x00075343,
 * 0x00075399) use a 16-byte stride, proving 96 and 8 cached Vector4 elements.
 * Set_DX8_Texture_Stage_State (0x000661DD) checks stage against 16 and indexes
 * 32 four-byte states per stage. Set_DX8_Texture (0x00075412) checks stage against
 * 16 and indexes the pointer array at VA 0x00DEC4B0.
 *
 * Static bindings, corroborated by absolute operands in the rowed methods:
 * D3DDevice is VA 0x00DEDA34, D3DInterface 0x00DEDA30, render_state_changed
 * 0x00DEC4F4, ProjectionMatrix 0x00DEDC30 and DeviceProjectionMatrix 0x00DEDBF0.
 * Set_Transform (RVA 0x000A68A7, 0x0006A553) accesses both 64-byte matrices;
 * ZNear is VA 0x00DEC4F0 and ZFar 0x00DED9F8. Reset_Statistics (0x0011D0D0)
 * zeroes the four-byte counters matrix_changes at VA 0x00DEDA4C, texture_changes
 * at 0x00DEDA60, render_state_changes at 0x00DEDA64 and
 * texture_stage_state_changes at 0x00DEDA68. Light_Environment is VA 0x00DEDA14
 * (Set_Light_Environment, RVA 0x00122EA0). CurrentCaps is VA 0x00DEDA7C
 * (AdjustTextureSize, 0x0011E670). Get_Device_Resolution (0x0011CDF0) reads
 * ResolutionWidth at VA 0x00DB5FD4, ResolutionHeight at 0x00DB5FD8 and the
 * IsWindowed byte at 0x00DEDA06. Init sets IsInitted at VA 0x00DEDA04.
 * _Enable_Triangle_Draw (0x0012D2C0) stores the byte at VA 0x00DB5FCD.
 * Set_Render_Target_With_Z (0x00120850) sets IsRenderToTexture at VA 0x00DEDA48.
 * The fog setter (RVA 0x0006F0BB) writes FogEnable at VA 0x00DEDA21 and FogColor
 * at 0x00DEDA24. RTS3DScene::renderOneObject tests FogEnable at VA 0x0046FBF2.
 * Rva00116E40Set (RVA 0x00116E40) writes TextureBitDepth at VA 0x00DB5FE0.
 * Set_Render_Target (0x0011E250, 0x0011E3E0) reads and stores CurrentRenderTarget
 * at VA 0x00DEDA38, CurrentDepthBuffer at 0x00DEDA3C, DefaultRenderTarget at
 * 0x00DEDA40 and DefaultDepthBuffer at 0x00DEDA44. Do_Onetime_Device_Dependent_Inits
 * (0x001245A0) reads DisplayFormat at VA 0x00DEDA08. Get_Device_Resolution and
 * Get_Render_Target_Resolution (0x00121860) read BitDepth at VA 0x00DB5FDC.
 * Set_Ambient (0x00117F50) stores Ambient_Color at VA 0x00DEDC70. Reset_Device
 * (0x00122600) reads m_pCleanupHook at VA 0x00DEDA90.
 *
 * The friends own matched rows that use the protected statics directly:
 * Rva007AB81ACtorInits::rva007ACC20 (RVA 0x007ACC20) constructs render_state at
 * VA 0x00DEE5D8, W3DAptRenderer::rva00110CFE (0x00110CFE) stores render_state's
 * world matrix and updates render_state_changed, Rva007D6B70::reset (0x000F8735)
 * updates Textures at VA 0x00DEC4B0 and texture_changes at 0x00DEDA60, and
 * Rva000EDF40Get (0x000EDF40) reads and Rva00149570Set (0x00149570) stores
 * FogColor at VA 0x00DEDA24.
 *
 * The matched Get_Transform row uses the enum tag D3DTRANSFORMSTATETYPE, whereas
 * the matched Set_Transform rows use _D3DTRANSFORMSTATETYPE. The declarations
 * preserve both identities. Their identical integer representation does not
 * prove that these two C++ types are interchangeable.
 *
 * Donor facts: GeneralsMD WW3D2/dx8wrapper.h declares a class with only static
 * members and no bases. Its sizeof 1 is a donor/compiler fact, not a retail
 * allocation measurement. It proves the names of the four inline accessors
 * Set_Texture_Bitdepth, Get_Current_Caps, Get_Fog_Enable and _Get_D3D_Device8,
 * and of _Get_D3D8, Get_Device_Resolution_Width, Get_Device_Resolution_Height,
 * Get_Texture_Bitdepth, _Is_Triangle_Draw_Enabled, Get_Fog_Color, Is_Initted
 * and SetCleanupHook. BFME2 code reads or stores their statics inline:
 * D3DInterface at 0x004752F2, ResolutionWidth at 0x005184D7, ResolutionHeight at
 * 0x005184F5, TextureBitDepth at 0x00517C30, the triangle-draw byte at
 * 0x004F08C0, FogColor at 0x004EE734, IsInitted at 0x0055A9F3 and m_pCleanupHook
 * (store) at 0x0046CDC2. No out-of-line copy of any of them is in the ledger.
 * The named static data also follows that declaration, with BFME2 extents read
 * from Init. No donor or shim header is included here.
 *
 * Matched retail method RVAs and signatures follow. Access and types are those
 * of the ledger rows; each body remains declared out of line.
 * 0x00125620: bool Init(void *, bool lite = false);
 * 0x00125DC0: void Shutdown();
 * 0x001245A0: void Do_Onetime_Device_Dependent_Inits();
 * 0x001215F0: void Do_Onetime_Device_Dependent_Shutdowns();
 * 0x0011CDC0: bool Has_Stencil();
 * 0x0011FE20: void Get_Format_Name(unsigned, StringClass *);
 * 0x0011D2B0: void Begin_Scene_Inner();
 * 0x0011D2D0: void Rva0011D2D0WaitForBackBuffer();
 * 0x00122BE0: void End_Scene(bool flip_frame = true);
 * 0x00122DF0: void Flip_To_Primary();
 * 0x0011D330: void Clear(bool, bool, bool, const Vector3 &, float = 0.0f, float = 1.0f, unsigned = 0);
 * 0x0011D480: void Set_Viewport(const _D3DVIEWPORT8 *);
 * 0x0011D4A0: void Set_Vertex_Buffer(const VertexBufferClass *, unsigned stream = 0);
 * 0x0011D5C0: void Set_Vertex_Buffer(const DynamicVBAccessClass &);
 * 0x0011D530: void Set_Index_Buffer(const IndexBufferClass *, unsigned short);
 * 0x0011D690: void Set_Index_Buffer(const DynamicIBAccessClass &, unsigned short);
 * 0x00083B81: void Set_Index_Buffer_Index_Offset(unsigned);
 * 0x0012E010: void Get_Render_State(RenderStateStruct &);
 * 0x0012E3E0: void Set_Render_State(const RenderStateStruct &);
 * 0x0011C500: void Release_Render_State();
 * 0x0013C930: void Set_DX8_Material(const _D3DMATERIAL8 *);
 * 0x00120980: void Set_Gamma(float, float, float, bool calibrate = true, bool uselimit = true);
 * 0x00120CD0: void Set_Projection_Transform_With_Z_Bias(const Matrix4 &, float, float);
 * 0x000A68A7: void Set_Transform(_D3DTRANSFORMSTATETYPE, const Matrix4 &);
 * 0x0006A553: void Set_Transform(_D3DTRANSFORMSTATETYPE, const Matrix3D &);
 * 0x000768FE: void Get_Transform(D3DTRANSFORMSTATETYPE, Matrix4 &);
 * 0x0010737E: void Set_World_Identity();
 * 0x001100E8: void Set_View_Identity();
 * 0x0011C470: void Set_DX8_Light(int, _D3DLIGHT8 *);
 * 0x0006615F: void Set_DX8_Render_State(unsigned long, unsigned);
 * 0x000661DD: void Set_DX8_Texture_Stage_State(unsigned, unsigned long, unsigned);
 * 0x00075412: void Set_DX8_Texture(unsigned, IDirect3DBaseTexture8 *);
 * 0x00122EA0: void Set_Light_Environment(LightEnvironmentClass *);
 * 0x000662E5: void Set_Shader(const ShaderClass &);
 * 0x0010852B: void Get_Shader(ShaderClass &);
 * 0x000662B1: void Set_Material(const VertexMaterialClass *);
 * 0x0011DD20: void Set_Light(unsigned, const _D3DLIGHT8 *);
 * 0x0011DD80: void Set_Light(unsigned, const LightClass &);
 * 0x0011D930: void Apply_Render_State_Changes();
 * 0x001205B0: void Draw_Triangles(unsigned, unsigned, unsigned, unsigned, unsigned);
 * 0x00120620: void Draw_Triangles(unsigned, unsigned, unsigned, unsigned);
 * 0x001206D0: void Draw_Strip(unsigned, unsigned, unsigned, unsigned);
 * 0x00120650: void bfmeRva00120650(unsigned, unsigned);
 * 0x00120700: void bfmeRva00120700(unsigned, unsigned);
 * 0x0011DC60: IDirect3DSurface9 *_Create_DX8_Surface(unsigned, unsigned, WW3DFormat, _D3DPOOL);
 * 0x0011DFE0: IDirect3DSurface9 *_Get_DX8_Front_Buffer();
 * 0x0011E120: RefCountPtr<TextureClass> Create_Render_Target(int, int, WW3DFormat);
 * 0x0011E250: void Set_Render_Target(IDirect3DSurface8 *, bool use_default_depth_buffer = false);
 * 0x0011E3E0: void Set_Render_Target(IDirect3DSurface8 *, IDirect3DSurface8 *);
 * 0x00120940: void Set_Render_Target(IDirect3DSwapChain8 *);
 * 0x00120850: void Set_Render_Target_With_Z(TextureClass *, ZTextureClass * = 0);
 * 0x0011E580: IDirect3DSwapChain8 *Create_Additional_Swap_Chain(void *);
 * 0x0011E630: unsigned Get_Free_Texture_RAM();
 * 0x0011E670: void AdjustTextureSize(unsigned &, unsigned &);
 * 0x0011D140: void Begin_Statistics();
 * 0x0011D180: void End_Statistics();
 * 0x000EDF46: Vector4 Convert_Color(unsigned);
 * 0x00139290: unsigned Convert_Color(const Vector4 &);
 * 0x0006E1C0: unsigned Convert_Color(const Vector3 &, float);
 * 0x00126082: void Clamp_Color(Vector4 &);
 * 0x0012617C: unsigned Convert_Color_Clamp(Vector4);
 * 0x0012D2C0: void _Enable_Triangle_Draw(bool);
 * 0x00075343: void Set_Vertex_Shader_Constant(int, const void *, int);
 * 0x00075399: void Set_Pixel_Shader_Constant(int, const void *, int);
 * 0x00117F50: void Set_Ambient(const Vector3 &);
 * 0x00122600: bool Reset_Device(bool reload_assets = true);
 * 0x00123170: void Apply_Default_State();
 * 0x00121930: bool Registry_Save_Render_Device(const char *);
 * 0x00125A80: bool Registry_Load_Render_Device(const char *, bool);
 * 0x0011FD10: void Invalidate_Cached_Render_States();
 * 0x0011E6D0: const char *Get_DX8_Render_State_Name(unsigned long);
 * 0x0011EA70: const char *Get_DX8_Texture_Stage_State_Name(unsigned long);
 * 0x00120B90: void Get_DX8_Texture_Stage_State_Value_Name(StringClass &, unsigned long, unsigned);
 * 0x00121A10: void Get_DX8_Render_State_Value_Name(StringClass &, unsigned long, unsigned);
 * 0x0011EB60: const char *Get_DX8_Texture_Op_Name(unsigned);
 * 0x0011EC90: const char *Get_DX8_Texture_Arg_Name(unsigned);
 * 0x0011ED30: const char *Get_DX8_Texture_Filter_Name(unsigned);
 * 0x0011ED70: const char *Get_DX8_Texture_Address_Name(unsigned);
 * 0x0011EDC0: const char *Get_DX8_Texture_Transform_Flag_Name(unsigned);
 * 0x0011EE20: const char *Get_DX8_ZBuffer_Type_Name(unsigned);
 * 0x0011EE50: const char *Get_DX8_Fill_Mode_Name(unsigned);
 * 0x0011EE80: const char *Get_DX8_Shade_Mode_Name(unsigned);
 * 0x0011EEB0: const char *Get_DX8_Blend_Name(unsigned);
 * 0x0011EF50: const char *Get_DX8_Cull_Mode_Name(unsigned);
 * 0x0011EF80: const char *Get_DX8_Cmp_Func_Name(unsigned);
 * 0x0011EFF0: const char *Get_DX8_Fog_Mode_Name(unsigned);
 * 0x0011F030: const char *Get_DX8_Stencil_Op_Name(unsigned);
 * 0x0011F0A0: const char *Get_DX8_Material_Source_Name(unsigned);
 * 0x0011F0D0: const char *Get_DX8_Vertex_Blend_Flag_Name(unsigned);
 * 0x0011F120: const char *Get_DX8_Patch_Edge_Style_Name(unsigned);
 * 0x0011F140: const char *Get_DX8_Debug_Monitor_Token_Name(unsigned);
 * 0x0011F160: const char *Get_DX8_Blend_Op_Name(unsigned);
 * 0x001246C0: bool Create_Device();
 * 0x00121770: void Release_Device();
 * 0x0011D0D0: void Reset_Statistics();
 * 0x00124890: void Enumerate_Devices();
 * 0x00122510: void Set_Default_Global_Render_States();
 * 0x00125900: bool Set_Any_Render_Device();
 * 0x00125970: bool Set_Render_Device(const char *, int = -1, int = -1, int = -1, int = -1, bool = false);
 * 0x00124FF0: bool Set_Render_Device(int = -1, int = -1, int = -1, int = -1, int = -1, bool = false, bool = false, bool = true);
 * 0x00125400: bool Set_Next_Render_Device();
 * 0x0011CDE0: int Get_Render_Device();
 * 0x00120140: const RenderDeviceDescClass &Get_Render_Device_Desc(int);
 * 0x00120180: const char *Get_Render_Device_Name(int);
 * 0x00122AD0: bool Set_Device_Resolution(int = -1, int = -1, int = -1, int = -1, bool = false);
 * 0x0011CDF0: void Get_Device_Resolution(int &, int &, int &, bool &);
 * 0x001201A0: bool Registry_Save_Render_Device(const char *, int, int, int, int, bool, int);
 * 0x0011CE40: bool Registry_Load_Render_Device(const char *, char *, int, int &, int &, int &, int &, int &);
 * 0x00122A60: void Set_Swap_Interval(int);
 * 0x00121970: bool Find_Color_And_Z_Mode(int, int, int, _D3DFORMAT *, _D3DFORMAT *, _D3DFORMAT *);
 * 0x0011CF80: bool Find_Color_Mode(_D3DFORMAT, int, int, unsigned *);
 * 0x001202B0: bool Find_Z_Mode(_D3DFORMAT, _D3DFORMAT, _D3DFORMAT *);
 * 0x0011D080: bool Test_Z_Mode(_D3DFORMAT, _D3DFORMAT, _D3DFORMAT);
 * 0x00121860: void Get_Render_Target_Resolution(int &, int &, int &, bool &);
 * 0x0011D710: void Draw_Sorting_IB_VB(unsigned, unsigned, unsigned, unsigned, unsigned);
 * 0x001203C0: void Draw(unsigned, unsigned, unsigned, unsigned, unsigned, bool);
 */
#pragma once

#ifndef BFME2_DX8WRAPPERCLASS_H
#define BFME2_DX8WRAPPERCLASS_H

class Matrix3D;
class Matrix4;
class Vector3;
class Vector4;
class ShaderClass;
class StringClass;
class VertexMaterialClass;
class VertexBufferClass;
class IndexBufferClass;
class DynamicVBAccessClass;
class DynamicIBAccessClass;
class TextureClass;
class ZTextureClass;
class LightClass;
class LightEnvironmentClass;
class RenderDeviceDescClass;
class DX8Caps;
class DX8_CleanupHook;
class RenderInfoClass;
class IDirect3DSurface9;
template<class T> class RefCountPtr;
struct RenderStateStruct;
struct IDirect3D8;
struct IDirect3DDevice8;
struct IDirect3DBaseTexture8;
struct IDirect3DSurface8;
struct IDirect3DSwapChain8;
struct _D3DMATERIAL8;
struct _D3DLIGHT8;
struct _D3DVIEWPORT8;
enum _D3DPOOL;
enum _D3DFORMAT;
enum _D3DTRANSFORMSTATETYPE;
// The DirectX SDK types make D3DTRANSFORMSTATETYPE a typedef of _D3DTRANSFORMSTATETYPE.
#if !defined(_D3D8TYPES_H_) && !defined(_d3d9TYPES_H_)
enum D3DTRANSFORMSTATETYPE;
#endif
enum WW3DFormat;

class DX8Wrapper
{
public:
    static __forceinline void Set_Texture_Bitdepth(int depth) { TextureBitDepth = depth; }
    static __forceinline const DX8Caps *Get_Current_Caps() { return CurrentCaps; }
    static __forceinline bool Get_Fog_Enable() { return FogEnable; }
    static __forceinline IDirect3DDevice8 *_Get_D3D_Device8() { return D3DDevice; }
    static __forceinline IDirect3D8 *_Get_D3D8() { return D3DInterface; }
    static __forceinline int Get_Device_Resolution_Width() { return ResolutionWidth; }
    static __forceinline int Get_Device_Resolution_Height() { return ResolutionHeight; }
    static __forceinline int Get_Texture_Bitdepth() { return TextureBitDepth; }
    static __forceinline bool _Is_Triangle_Draw_Enabled() { return _EnableTriangleDraw; }
    static __forceinline unsigned long Get_Fog_Color() { return FogColor; }
    static __forceinline bool Is_Initted() { return IsInitted; }
    static __forceinline void SetCleanupHook(DX8_CleanupHook *hook) { m_pCleanupHook = hook; }
    static bool Init(void *, bool lite = false);
    static void Shutdown();
    static void Do_Onetime_Device_Dependent_Inits();
    static void Do_Onetime_Device_Dependent_Shutdowns();
    static bool Has_Stencil();
    static void Get_Format_Name(unsigned, StringClass *);
    static void Begin_Scene_Inner();
    static void Rva0011D2D0WaitForBackBuffer();
    static void End_Scene(bool flip_frame = true);
    static void Flip_To_Primary();
    static void Clear(bool, bool, bool, const Vector3 &, float = 0.0f, float = 1.0f, unsigned = 0);
    static void Set_Viewport(const _D3DVIEWPORT8 *);
    static void Set_Vertex_Buffer(const VertexBufferClass *, unsigned stream = 0);
    static void Set_Vertex_Buffer(const DynamicVBAccessClass &);
    static void Set_Index_Buffer(const IndexBufferClass *, unsigned short);
    static void Set_Index_Buffer(const DynamicIBAccessClass &, unsigned short);
    static void Set_Index_Buffer_Index_Offset(unsigned);
    static void Get_Render_State(RenderStateStruct &);
    static void Set_Render_State(const RenderStateStruct &);
    static void Release_Render_State();
    static void Set_DX8_Material(const _D3DMATERIAL8 *);
    static void Set_Gamma(float, float, float, bool calibrate = true, bool uselimit = true);
    static void Set_Projection_Transform_With_Z_Bias(const Matrix4 &, float, float);
    static void Set_Transform(_D3DTRANSFORMSTATETYPE, const Matrix4 &);
    static void Set_Transform(_D3DTRANSFORMSTATETYPE, const Matrix3D &);
// Its row spells the native enum, which a unit with the SDK types cannot name.
#if !defined(_D3D8TYPES_H_) && !defined(_d3d9TYPES_H_)
    static void Get_Transform(D3DTRANSFORMSTATETYPE, Matrix4 &);
#endif
    static void Set_World_Identity();
    static void Set_View_Identity();
    static void Set_DX8_Light(int, _D3DLIGHT8 *);
    static void Set_DX8_Render_State(unsigned long, unsigned);
    static void Set_DX8_Texture_Stage_State(unsigned, unsigned long, unsigned);
    static void Set_DX8_Texture(unsigned, IDirect3DBaseTexture8 *);
    static void Set_Light_Environment(LightEnvironmentClass *);
    static void Set_Shader(const ShaderClass &);
    static void Get_Shader(ShaderClass &);
    static void Set_Material(const VertexMaterialClass *);
    static void Set_Light(unsigned, const _D3DLIGHT8 *);
    static void Set_Light(unsigned, const LightClass &);
    static void Apply_Render_State_Changes();
    static void Draw_Triangles(unsigned, unsigned, unsigned, unsigned, unsigned);
    static void Draw_Triangles(unsigned, unsigned, unsigned, unsigned);
    static void Draw_Strip(unsigned, unsigned, unsigned, unsigned);
    static void bfmeRva00120650(unsigned, unsigned);
    static void bfmeRva00120700(unsigned, unsigned);
    static IDirect3DSurface9 *_Create_DX8_Surface(unsigned, unsigned, WW3DFormat, _D3DPOOL);
    static IDirect3DSurface9 *_Get_DX8_Front_Buffer();
    static RefCountPtr<TextureClass> Create_Render_Target(int, int, WW3DFormat);
    static void Set_Render_Target(IDirect3DSurface8 *, bool use_default_depth_buffer = false);
    static void Set_Render_Target(IDirect3DSurface8 *, IDirect3DSurface8 *);
    static void Set_Render_Target(IDirect3DSwapChain8 *);
    static void Set_Render_Target_With_Z(TextureClass *, ZTextureClass * = 0);
    static IDirect3DSwapChain8 *Create_Additional_Swap_Chain(void *);
    static unsigned Get_Free_Texture_RAM();
    static void AdjustTextureSize(unsigned &, unsigned &);
    static void Begin_Statistics();
    static void End_Statistics();
    static Vector4 Convert_Color(unsigned);
    static unsigned Convert_Color(const Vector4 &);
    static unsigned Convert_Color(const Vector3 &, float);
    static void Clamp_Color(Vector4 &);
    static unsigned Convert_Color_Clamp(Vector4);
    static void _Enable_Triangle_Draw(bool);
    static void Set_Vertex_Shader_Constant(int, const void *, int);
    static void Set_Pixel_Shader_Constant(int, const void *, int);
    static void Set_Ambient(const Vector3 &);
    static bool Reset_Device(bool reload_assets = true);
    static void Apply_Default_State();
    static bool Registry_Save_Render_Device(const char *);
    static bool Registry_Load_Render_Device(const char *, bool);
    static void Invalidate_Cached_Render_States();
    static const char *Get_DX8_Render_State_Name(unsigned long);
    static const char *Get_DX8_Texture_Stage_State_Name(unsigned long);
    static void Get_DX8_Texture_Stage_State_Value_Name(StringClass &, unsigned long, unsigned);
    static void Get_DX8_Render_State_Value_Name(StringClass &, unsigned long, unsigned);
    static const char *Get_DX8_Texture_Op_Name(unsigned);
    static const char *Get_DX8_Texture_Arg_Name(unsigned);
    static const char *Get_DX8_Texture_Filter_Name(unsigned);
    static const char *Get_DX8_Texture_Address_Name(unsigned);
    static const char *Get_DX8_Texture_Transform_Flag_Name(unsigned);
    static const char *Get_DX8_ZBuffer_Type_Name(unsigned);
    static const char *Get_DX8_Fill_Mode_Name(unsigned);
    static const char *Get_DX8_Shade_Mode_Name(unsigned);
    static const char *Get_DX8_Blend_Name(unsigned);
    static const char *Get_DX8_Cull_Mode_Name(unsigned);
    static const char *Get_DX8_Cmp_Func_Name(unsigned);
    static const char *Get_DX8_Fog_Mode_Name(unsigned);
    static const char *Get_DX8_Stencil_Op_Name(unsigned);
    static const char *Get_DX8_Material_Source_Name(unsigned);
    static const char *Get_DX8_Vertex_Blend_Flag_Name(unsigned);
    static const char *Get_DX8_Patch_Edge_Style_Name(unsigned);
    static const char *Get_DX8_Debug_Monitor_Token_Name(unsigned);
    static const char *Get_DX8_Blend_Op_Name(unsigned);

protected:
    static bool Create_Device();
    static void Release_Device();
    static void Reset_Statistics();
    static void Enumerate_Devices();
    static void Set_Default_Global_Render_States();
    static bool Set_Any_Render_Device();
    static bool Set_Render_Device(const char *, int = -1, int = -1, int = -1, int = -1, bool = false);
    static bool Set_Render_Device(int = -1, int = -1, int = -1, int = -1, int = -1, bool = false, bool = false, bool = true);
    static bool Set_Next_Render_Device();
    static int Get_Render_Device();
    static const RenderDeviceDescClass &Get_Render_Device_Desc(int);
    static const char *Get_Render_Device_Name(int);
    static bool Set_Device_Resolution(int = -1, int = -1, int = -1, int = -1, bool = false);
    static void Get_Device_Resolution(int &, int &, int &, bool &);
    static bool Registry_Save_Render_Device(const char *, int, int, int, int, bool, int);
    static bool Registry_Load_Render_Device(const char *, char *, int, int &, int &, int &, int &, int &);
    static void Set_Swap_Interval(int);
    static bool Find_Color_And_Z_Mode(int, int, int, _D3DFORMAT *, _D3DFORMAT *, _D3DFORMAT *);
    static bool Find_Color_Mode(_D3DFORMAT, int, int, unsigned *);
    static bool Find_Z_Mode(_D3DFORMAT, _D3DFORMAT, _D3DFORMAT *);
    static bool Test_Z_Mode(_D3DFORMAT, _D3DFORMAT, _D3DFORMAT);

    static IDirect3DDevice8 *D3DDevice;
    static IDirect3D8 *D3DInterface;
    static IDirect3DBaseTexture8 *Textures[16];
    static RenderStateStruct render_state;
    static unsigned render_state_changed;
    static unsigned RenderStates[256];
    static unsigned TextureStageStates[16][32];
    static unsigned matrix_changes;
    static unsigned texture_changes;
    static unsigned render_state_changes;
    static unsigned texture_stage_state_changes;
    static Matrix4 ProjectionMatrix;
    static Matrix4 DeviceProjectionMatrix;
    static Vector4 Vertex_Shader_Constants[96];
    static Vector4 Pixel_Shader_Constants[8];
    static LightEnvironmentClass *Light_Environment;
    static DX8Caps *CurrentCaps;
    static int TextureBitDepth;
    static int ResolutionWidth;
    static int ResolutionHeight;
    static bool FogEnable;
    static unsigned long FogColor;
    static bool IsInitted;
    static bool IsWindowed;
    static bool _EnableTriangleDraw;
    static bool IsRenderToTexture;
    static float ZNear;
    static float ZFar;
    static _D3DFORMAT DisplayFormat;
    static IDirect3DSurface8 *CurrentRenderTarget;
    static IDirect3DSurface8 *CurrentDepthBuffer;
    static IDirect3DSurface8 *DefaultRenderTarget;
    static IDirect3DSurface8 *DefaultDepthBuffer;
    static int BitDepth;
    static Vector3 Ambient_Color;
    static DX8_CleanupHook *m_pCleanupHook;

private:
    static void Get_Render_Target_Resolution(int &, int &, int &, bool &);
    static void Draw_Sorting_IB_VB(unsigned, unsigned, unsigned, unsigned, unsigned);
    static void Draw(unsigned, unsigned, unsigned, unsigned, unsigned, bool);

    friend class WW3D;
    friend class DX8IndexBufferClass;
    friend class DX8VertexBufferClass;
    friend class BfmeFVFDescriptor;
    friend class Rva0014D7D4This;
    friend class Rva00785FD0Renderer;
    friend struct Rva000FDD1C;
    friend void __cdecl bfmeGo1054E(int, int);
    friend void __cdecl bfmeGo1057C(int, int, int);
    friend int Rva0014D241Get();
    friend unsigned char Rva00131068GetByte();
    friend unsigned char Rva0006E19BGetByte();
    friend unsigned char Rva00116F70GetByte();
    friend class Rva0014D722This;
    friend class Rva0014D887This;
    friend void __cdecl bfmeGoELHa(void *);
    friend void __cdecl rva0014D522(void *, void *);
    friend int Rva00042F67Get();
    friend int Rva00042F6DGet();
    friend int Rva0011009AGet();
    friend int Rva001100A0Get();
    friend int __cdecl Rva00945460Lookup(int, int);
    friend void Pack_Ambient_Color(const Vector3 &);
    friend void Pack_Ambient_Color(const Vector3 &, float);
    friend void rva0006F0BB(bool, const Vector3 &, float, float);
    friend void rva00120670(unsigned int, unsigned int);
    friend void rva00120690(unsigned int, unsigned int);
    friend void rva001206B0(unsigned int, unsigned int);
    friend class FXShaderGeometry;
    friend class Rva0014A710;
    friend class W3DAptRenderer;
    friend struct Rva007AB81ACtorInits;
    friend class Rva007D6B70;
    friend int Rva000EDF40Get();
    friend void Rva00149570Set(int);
};

#endif
