// ?Apply@ShaderClass@@AAEXXZ
// cl: /DBFME_WWSTRING_NATIVE_CSTR_ASSIGN /Ireference/shims/wwstring_teardown/zhmd /Ireference/shims/bfme_dx8wrapper_home_link /Ireference/shims/bfmecamera /Ireference/shims/bfmeshader /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// stlport
//
// dx8wrapper.h comes from the bfme_dx8wrapper_home_link shim: retail Apply calls
// Set_DX8_Render_State (0x0006615F) and Set_DX8_Texture_Stage_State (0x000661DD) out of line,
// and that view only declares them, so this unit emits no /O2 COMDAT copy of either (the
// bfmecamera view's inline bodies did, and those copies are not retail's /O1 bodies).
//
// ShaderClass::Apply, the BFME2 shader state pipeline (RVA 0x137590, 2838
// executable bytes followed by two alignment bytes and a 92-byte switch table).
// Zero Hour shader.cpp body on the BFME2 shader layout: two-bit alpha-test
// field at bit 18, cull mode at bit 20, source/destination blend LUTs at
// VA 0x00DB6284/0x00DB62A4 and the cached alpha-reference override.
//
// Retail tests the ALPHATEST_MAX case on its own before the commutative
// SRCALPHA/INVSRCALPHA pair, each pair testing sf before df; folding the three
// into one condition makes MSVC 7.1 swap the sf/df register assignment.
// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it. Retail links one
// copy, the /O1 body at 0x00001423; this unemitted anchor makes this unit's
// copy that same body, so it no longer loses to retail's at link time.
// It can also change how later array constructions here compile; checked to
// change nothing else in this unit, but if a function added later that builds
// an array will not match, try it without this block.
#include "../../../../GameEngine/Include/Common/BfmeVciAnchorElem.h"
#pragma optimize("gsy", on)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
#define Matrix4x4 Matrix4  // BFME renamed it
#define __PLACEMENT_VEC_NEW_INLINE  // always.h/GameMemory.h define array placement-new themselves
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



#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <dx8caps.h>

#ifndef DX8CAPS_H
#define DX8CAPS_H

// BFME2 layout independently recovered by the complete 2160-byte Compute_Caps
// body at RVA0x12BDE0 and its capability-check siblings. Keep the typed fields

#include "always.h"
#include "ww3dformat.h"
#include <d3d8.h>

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/dx8caps.h
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

	enum DeviceTypeATI {
		DEVICE_ATI_UNKNOWN,
		DEVICE_ATI_RAGE_II,
		DEVICE_ATI_RAGE_II_PLUS,
		DEVICE_ATI_RAGE_IIC_PCI,
		DEVICE_ATI_RAGE_IIC_AGP,
		DEVICE_ATI_RAGE_128_MOBILITY,
		DEVICE_ATI_RAGE_128_MOBILITY_M3,
		DEVICE_ATI_RAGE_128_MOBILITY_M4,
		DEVICE_ATI_RAGE_128_PRO_ULTRA,
		DEVICE_ATI_RAGE_128_4X,
		DEVICE_ATI_RAGE_128_PRO_GL,
		DEVICE_ATI_RAGE_128_PRO_VR,
		DEVICE_ATI_RAGE_128_GL,
		DEVICE_ATI_RAGE_128_VR,
		DEVICE_ATI_RAGE_PRO,
		DEVICE_ATI_RAGE_PRO_MOBILITY,
		DEVICE_ATI_MOBILITY_RADEON,
		DEVICE_ATI_MOBILITY_RADEON_VE_M6,
		DEVICE_ATI_RADEON_VE,
		DEVICE_ATI_RADEON_DDR,
		DEVICE_ATI_RADEON,
		DEVICE_ATI_MOBILITY_R7500,
		DEVICE_ATI_R7500,
		DEVICE_ATI_R8500
	};

	enum DeviceType3DLabs {
		DEVICE_3DLABS_UNKNOWN,
		DEVICE_3DLABS_PERMEDIA,
		DEVICE_3DLABS_300SX,
		DEVICE_3DLABS_500TX,
		DEVICE_3DLABS_DELTA,
		DEVICE_3DLABS_MX,
		DEVICE_3DLABS_GAMMA,
		DEVICE_3DLABS_PERMEDIA2S_ST,
		DEVICE_3DLABS_PERMEDIA3,
		DEVICE_3DLABS_R3,
		DEVICE_3DLABS_PERMEDIA4,
		DEVICE_3DLABS_R4,
		DEVICE_3DLABS_G2,
		DEVICE_3DLABS_OXYGEN_VX1,
		DEVICE_3DLABS_TI_P1,
		DEVICE_3DLABS_PERMEDIA2
	};

	enum DeviceTypeNVidia {
		DEVICE_NVIDIA_UNKNOWN,
		DEVICE_NVIDIA_GEFORCE3,
		DEVICE_NVIDIA_QUADRO2_PRO,
		DEVICE_NVIDIA_GEFORCE2_GO,
		DEVICE_NVIDIA_GEFORCE2_ULTRA,
		DEVICE_NVIDIA_GEFORCE2_GTS,
		DEVICE_NVIDIA_QUADRO,
		DEVICE_NVIDIA_GEFORCE_DDR,
		DEVICE_NVIDIA_GEFORCE_256,
		DEVICE_NVIDIA_TNT2_ALADDIN,
		DEVICE_NVIDIA_TNT2,
		DEVICE_NVIDIA_TNT2_ULTRA,
		DEVICE_NVIDIA_TNT2_VANTA,
		DEVICE_NVIDIA_TNT2_M64,
		DEVICE_NVIDIA_TNT,
		DEVICE_NVIDIA_RIVA_128,
		DEVICE_NVIDIA_TNT_VANTA,
		DEVICE_NVIDIA_NV1,
		DEVICE_NVIDIA_GEFORCE2_MX,
		DEVICE_NVIDIA_GEFORCE4_TI_4600,
		DEVICE_NVIDIA_GEFORCE4_TI_4400,
		DEVICE_NVIDIA_GEFORCE4_TI,
		DEVICE_NVIDIA_GEFORCE4_TI_4200,
		DEVICE_NVIDIA_GEFORCE4_MX_460,
		DEVICE_NVIDIA_GEFORCE4_MX_440,
		DEVICE_NVIDIA_GEFORCE4_MX_420,
		DEVICE_NVIDIA_GEFORCE4,
		DEVICE_NVIDIA_GEFORCE4_GO_440,
		DEVICE_NVIDIA_GEFORCE4_GO_420,
		DEVICE_NVIDIA_GEFORCE4_GO_420_32M,
		DEVICE_NVIDIA_GEFORCE4_GO_440_64M,
		DEVICE_NVIDIA_GEFORCE4_GO,
		DEVICE_NVIDIA_GEFORCE3_TI_500,
		DEVICE_NVIDIA_GEFORCE3_TI_200,
		DEVICE_NVIDIA_GEFORCE2_INTEGRATED,
		DEVICE_NVIDIA_GEFORCE2_TI,
		DEVICE_NVIDIA_QUADRO2_MXR_EX_GO,
		DEVICE_NVIDIA_GEFORCE2_MX_100_200,
		DEVICE_NVIDIA_GEFORCE2_MX_400,
		DEVICE_NVIDIA_QUADRO_DCC
	};

	enum DeviceType3Dfx {
		DEVICE_3DFX_UNKNOWN,
		DEVICE_3DFX_VOODOO_5500_AGP,
		DEVICE_3DFX_VOODOO_3,
		DEVICE_3DFX_BANSHEE,
		DEVICE_3DFX_VOODOO_2,
		DEVICE_3DFX_VOODOO_GRAPHICS,
		DEVICE_3DFX_VOODOO_RUSH
	};

	enum DeviceTypeMatrox {
		DEVICE_MATROX_UNKNOWN,
		DEVICE_MATROX_G550,
		DEVICE_MATROX_G400,
		DEVICE_MATROX_G200_AGP,
		DEVICE_MATROX_G200_PCI,
		DEVICE_MATROX_G100_PCI,
		DEVICE_MATROX_G100_AGP,
		DEVICE_MATROX_MILLENNIUM_II_AGP,
		DEVICE_MATROX_MILLENNIUM_II_PCI,
		DEVICE_MATROX_MYSTIQUE,
		DEVICE_MATROX_MILLENNIUM,
		DEVICE_MATROX_PARHELIA,
		DEVICE_MATROX_PARHELIA_AGP8X
	};

	enum DeviceTypePowerVR {
		DEVICE_POWERVR_UNKNOWN,
		DEVICE_POWERVR_KYRO
	};

	enum DeviceTypeS3 {
		DEVICE_S3_UNKNOWN,
		DEVICE_S3_SAVAGE_MX,
		DEVICE_S3_SAVAGE_4,
		DEVICE_S3_SAVAGE_200
	};

	enum DeviceTypeIntel {
		DEVICE_INTEL_UNKNOWN,
		DEVICE_INTEL_810,
		DEVICE_INTEL_810E,
		DEVICE_INTEL_815
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
	static DeviceTypeATI Get_ATI_Device(unsigned device_id);
	static DeviceType3DLabs Get_3DLabs_Device(unsigned device_id);
	static DeviceTypeNVidia Get_NVidia_Device(unsigned device_id);
	static DeviceType3Dfx Get_3Dfx_Device(unsigned device_id);
	static DeviceTypeMatrox Get_Matrox_Device(unsigned device_id);
	static DeviceTypePowerVR Get_PowerVR_Device(unsigned device_id);
	static DeviceTypeS3 Get_S3_Device(unsigned device_id);
	static DeviceTypeIntel Get_Intel_Device(unsigned device_id);

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
	unsigned DeviceId;          // mapped classification at0x2C0
	unsigned RawDeviceId;       // adapter PCI device ID at0x2C4
	unsigned DriverBuildVersion;
	DriverVersionStatusType DriverVersionStatus;
	VendorIdType VendorId;      // mapped vendor at0x2D0
	StringClass DriverDLL;
	IDirect3D8* Direct3D; // warning XDK name conflict KJM
	StringClass CapsLog;
	StringClass CompactLog;

};

typedef char BFME_DX8Caps_layout_size[(sizeof(DX8Caps)==0x2E4)?1:-1];


#endif

/* The preceding calibrated capability declaration wins the reference guard. */
#include <dx8caps.h>

#include "ShaderClass.h"

#include "shader.h"
#include "w3d_file.h"
#include "wwdebug.h"
#include "Dx8Wrapper.h"
#include "dx8caps.h"
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

// Device9 method prefix through SetNPatchMode, in Wine/SDK order.
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
struct ShaderD3D9Device {
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
    virtual HRESULT __stdcall CreateIndexBuffer(UINT Length, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DIndexBuffer9** ppIndexBuffer, HANDLE* pSharedHandle) = 0;
    virtual HRESULT __stdcall CreateRenderTarget(UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, DWORD MultisampleQuality, BOOL Lockable, IDirect3DSurface9** ppSurface, HANDLE* pSharedHandle) = 0;
    virtual HRESULT __stdcall CreateDepthStencilSurface(UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, DWORD MultisampleQuality, BOOL Discard, IDirect3DSurface9** ppSurface, HANDLE* pSharedHandle) = 0;
    virtual HRESULT __stdcall UpdateSurface(IDirect3DSurface9 *src_surface, const RECT *src_rect, IDirect3DSurface9 *dst_surface, const POINT *dst_point) = 0;
    virtual HRESULT __stdcall UpdateTexture(IDirect3DBaseTexture9* pSourceTexture, IDirect3DBaseTexture9* pDestinationTexture) = 0;
    virtual HRESULT __stdcall GetRenderTargetData(IDirect3DSurface9* pRenderTarget, IDirect3DSurface9* pDestSurface) = 0;
    virtual HRESULT __stdcall GetFrontBufferData(UINT iSwapChain, IDirect3DSurface9* pDestSurface) = 0;
    virtual HRESULT __stdcall StretchRect(IDirect3DSurface9 *src_surface, const RECT *src_rect, IDirect3DSurface9 *dst_surface, const RECT *dst_rect, D3DTEXTUREFILTERTYPE filter) = 0;
    virtual HRESULT __stdcall ColorFill(IDirect3DSurface9 *surface, const RECT *rect, D3DCOLOR color) = 0;
    virtual HRESULT __stdcall CreateOffscreenPlainSurface(UINT Width, UINT Height, D3DFORMAT Format, D3DPOOL Pool, IDirect3DSurface9** ppSurface, HANDLE* pSharedHandle) = 0;
    virtual HRESULT __stdcall SetRenderTarget(DWORD RenderTargetIndex, IDirect3DSurface9* pRenderTarget) = 0;
    virtual HRESULT __stdcall GetRenderTarget(DWORD RenderTargetIndex, IDirect3DSurface9** ppRenderTarget) = 0;
    virtual HRESULT __stdcall SetDepthStencilSurface(IDirect3DSurface9* pNewZStencil) = 0;
    virtual HRESULT __stdcall GetDepthStencilSurface(IDirect3DSurface9** ppZStencilSurface) = 0;
    virtual HRESULT __stdcall BeginScene() = 0;
    virtual HRESULT __stdcall EndScene() = 0;
    virtual HRESULT __stdcall Clear(DWORD rect_count, const D3DRECT *rects, DWORD flags, D3DCOLOR color, float z, DWORD stencil) = 0;
    virtual HRESULT __stdcall SetTransform(D3DTRANSFORMSTATETYPE state, const D3DMATRIX *matrix) = 0;
    virtual HRESULT __stdcall GetTransform(D3DTRANSFORMSTATETYPE State, D3DMATRIX* pMatrix) = 0;
    virtual HRESULT __stdcall MultiplyTransform(D3DTRANSFORMSTATETYPE state, const D3DMATRIX *matrix) = 0;
    virtual HRESULT __stdcall SetViewport(const D3DVIEWPORT9 *viewport) = 0;
    virtual HRESULT __stdcall GetViewport(D3DVIEWPORT9* pViewport) = 0;
    virtual HRESULT __stdcall SetMaterial(const D3DMATERIAL9 *material) = 0;
    virtual HRESULT __stdcall GetMaterial(D3DMATERIAL9* pMaterial) = 0;
    virtual HRESULT __stdcall SetLight(DWORD index, const D3DLIGHT9 *light) = 0;
    virtual HRESULT __stdcall GetLight(DWORD Index, D3DLIGHT9*) = 0;
    virtual HRESULT __stdcall LightEnable(DWORD Index, BOOL Enable) = 0;
    virtual HRESULT __stdcall GetLightEnable(DWORD Index, BOOL* pEnable) = 0;
    virtual HRESULT __stdcall SetClipPlane(DWORD index, const float *plane) = 0;
    virtual HRESULT __stdcall GetClipPlane(DWORD Index, float* pPlane) = 0;
    virtual HRESULT __stdcall SetRenderState(D3DRENDERSTATETYPE State, DWORD Value) = 0;
    virtual HRESULT __stdcall GetRenderState(D3DRENDERSTATETYPE State, DWORD* pValue) = 0;
    virtual HRESULT __stdcall CreateStateBlock(D3DSTATEBLOCKTYPE Type, IDirect3DStateBlock9** ppSB) = 0;
    virtual HRESULT __stdcall BeginStateBlock() = 0;
    virtual HRESULT __stdcall EndStateBlock(IDirect3DStateBlock9** ppSB) = 0;
    virtual HRESULT __stdcall SetClipStatus(const D3DCLIPSTATUS9 *clip_status) = 0;
    virtual HRESULT __stdcall GetClipStatus(D3DCLIPSTATUS9* pClipStatus) = 0;
    virtual HRESULT __stdcall GetTexture(DWORD Stage, IDirect3DBaseTexture9** ppTexture) = 0;
    virtual HRESULT __stdcall SetTexture(DWORD Stage, IDirect3DBaseTexture9* pTexture) = 0;
    virtual HRESULT __stdcall GetTextureStageState(DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD* pValue) = 0;
    virtual HRESULT __stdcall SetTextureStageState(DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD Value) = 0;
    virtual HRESULT __stdcall GetSamplerState(DWORD Sampler, D3DSAMPLERSTATETYPE Type, DWORD* pValue) = 0;
    virtual HRESULT __stdcall SetSamplerState(DWORD Sampler, D3DSAMPLERSTATETYPE Type, DWORD Value) = 0;
    virtual HRESULT __stdcall ValidateDevice(DWORD* pNumPasses) = 0;
    virtual HRESULT __stdcall SetPaletteEntries(UINT palette_idx, const PALETTEENTRY *entries) = 0;
    virtual HRESULT __stdcall GetPaletteEntries(UINT PaletteNumber,PALETTEENTRY* pEntries) = 0;
    virtual HRESULT __stdcall SetCurrentTexturePalette(UINT PaletteNumber) = 0;
    virtual HRESULT __stdcall GetCurrentTexturePalette(UINT *PaletteNumber) = 0;
    virtual HRESULT __stdcall SetScissorRect(const RECT *rect) = 0;
    virtual HRESULT __stdcall GetScissorRect(RECT* pRect) = 0;
    virtual HRESULT __stdcall SetSoftwareVertexProcessing(BOOL bSoftware) = 0;
    virtual BOOL __stdcall GetSoftwareVertexProcessing() = 0;
    virtual HRESULT __stdcall SetNPatchMode(float nSegments) = 0;
};

#undef DX8CALL
#define DX8CALL(x) reinterpret_cast<ShaderD3D9Device*>(DX8Wrapper::_Get_D3D_Device8())->x; number_of_DX8_calls++;
extern bool ShaderAlphaReferenceOverride;
// ShaderAlphaReferenceOverride: matched references place it at VA 0xdf29c4 (zero-filled .bss).
bool ShaderAlphaReferenceOverride;
extern unsigned char ShaderAlphaReference;
// ShaderAlphaReference: matched references place it at VA 0xdb6224 (retail .data initial value 96).
unsigned char ShaderAlphaReference = 96;
extern bool ShaderOverbrightEnabled;
// ShaderOverbrightEnabled: matched references place it at VA 0xdb5f84 (retail .data initial value true).
bool ShaderOverbrightEnabled = true;


bool ShaderClass::ShaderDirty=true;
unsigned long ShaderClass::CurrentShader=0;
unsigned long _PolygonCullMode = D3DCULL_CW;
class Blend
{
public:

	Blend(D3DBLEND f, bool ab)
	{
		func = f;
		useAlpha = ab;
	}

	D3DBLEND	func;
	bool		useAlpha;
};

const Blend srcBlendLUT[ShaderClass::SRCBLEND_MAX] = 
{
	Blend(D3DBLEND_ZERO, false),
	Blend(D3DBLEND_ONE, false),
	Blend(D3DBLEND_SRCALPHA, true),
 	Blend(D3DBLEND_DESTCOLOR, true)
};

const Blend dstBlendLUT[ShaderClass::DSTBLEND_MAX] = 
{
	Blend(D3DBLEND_ZERO, false),
	Blend(D3DBLEND_ONE, false),
 	Blend(D3DBLEND_SRCCOLOR, false),
 	Blend(D3DBLEND_INVSRCCOLOR, false),
 	Blend(D3DBLEND_SRCALPHA, true),
 	Blend(D3DBLEND_INVSRCALPHA, true)
};



void ShaderClass::Apply()
{
	unsigned long diff;

	unsigned int TextureOpCaps=DX8Wrapper::Get_Current_Caps()->Get_DX8_Caps().TextureOpCaps;

	if (ShaderDirty)
	{
		diff=0xffffffff;
	}
	else
	{
		diff=CurrentShader^ShaderBits;
	}

	if(!diff) return;


	CurrentShader=ShaderBits;
	ShaderDirty=false;
	// COLOR MASK

	if(diff & (ShaderClass::MASK_COLORMASK | ShaderClass::MASK_SRCBLEND | ShaderClass::MASK_DSTBLEND | ShaderClass::MASK_ALPHATEST))
	{
		ULONG planeMask = 0xffffff;

		if(Get_Color_Mask() != ShaderClass::COLOR_WRITE_ENABLE)
			planeMask = 0;

		D3DBLEND	df;
		D3DBLEND	sf;
		bool	blendAlpha = false;

		if(!planeMask)
		{
			sf = D3DBLEND_ZERO;
			df = D3DBLEND_ONE;
		}
		else
		{
			sf = srcBlendLUT[ int(Get_Src_Blend_Func()) ].func;
			df = dstBlendLUT[ int(Get_Dst_Blend_Func()) ].func;
			blendAlpha |= srcBlendLUT[ int(Get_Src_Blend_Func()) ].useAlpha;
			blendAlpha |= dstBlendLUT[ int(Get_Dst_Blend_Func()) ].useAlpha;
		}



		if(sf != D3DBLEND_ONE || df != D3DBLEND_ZERO)
		{
			DX8Wrapper::Set_DX8_Render_State(D3DRS_SRCBLEND,sf);
			DX8Wrapper::Set_DX8_Render_State(D3DRS_DESTBLEND,df);
			DX8Wrapper::Set_DX8_Render_State(D3DRS_ALPHABLENDENABLE,TRUE);
		} else {
			DX8Wrapper::Set_DX8_Render_State(D3DRS_ALPHABLENDENABLE,FALSE);
		}

		const bool overrideAlpha = ShaderAlphaReferenceOverride;
		unsigned char alphareference = overrideAlpha ? ShaderAlphaReference : 1;
		BOOL alphaTest;
		if (Get_Alpha_Test() == ShaderClass::ALPHATEST_ENABLE) {
			alphareference = overrideAlpha ? ShaderAlphaReference : 0x60;
			alphaTest = TRUE;
		} else if (Get_Alpha_Test() == ShaderClass::ALPHATEST_MAX) {
			alphaTest = TRUE;
		} else if ((sf == D3DBLEND_SRCALPHA && df == D3DBLEND_INVSRCALPHA) ||
		           (sf == D3DBLEND_INVSRCALPHA && df == D3DBLEND_SRCALPHA)) {
			alphaTest = TRUE;
		} else {
			alphaTest = FALSE;
		}
		if(alphaTest)
		{
			if(sf == D3DBLEND_INVSRCALPHA)
			{
				DX8Wrapper::Set_DX8_Render_State(D3DRS_ALPHAREF,0xff - alphareference);
				DX8Wrapper::Set_DX8_Render_State(D3DRS_ALPHAFUNC,D3DCMP_LESSEQUAL);
			}
			else
			{
				DX8Wrapper::Set_DX8_Render_State(D3DRS_ALPHAREF,alphareference);
				DX8Wrapper::Set_DX8_Render_State(D3DRS_ALPHAFUNC,D3DCMP_GREATEREQUAL);
			}
			blendAlpha = true;
		}
		DX8Wrapper::Set_DX8_Render_State(D3DRS_ALPHATESTENABLE,alphaTest);

		diff &= ~(ShaderClass::MASK_COLORMASK | ShaderClass::MASK_SRCBLEND | ShaderClass::MASK_DSTBLEND | ShaderClass::MASK_ALPHATEST);		
		if(!diff) 			
			return;
	}	

	if(diff & (ShaderClass::MASK_FOG))
	{
		// Whenever fog is enabled or disabled, the entire shader is invalidated. This is why we
		// can defer the "fog enabled" check inside the "fog settings changed" check.
		if (DX8Wrapper::Get_Current_Caps()->Is_Fog_Allowed() && DX8Wrapper::Get_Fog_Enable()) {

			BOOL fm = FALSE;
			D3DCOLOR fogColor = DX8Wrapper::Get_Fog_Color();
			
			switch(Get_Fog_Func())
			{
			case ShaderClass::FOG_ENABLE:
				fm = TRUE;
				break;
			case ShaderClass::FOG_SCALE_FRAGMENT:
				fogColor = 0;	
				fm = TRUE;
				break;
			case ShaderClass::FOG_WHITE:
				fogColor = 0xffffff;
				fm = TRUE;
				break;
			case ShaderClass::FOG_DISABLE:
				fm = FALSE;
				break;
			}

			DX8Wrapper::Set_DX8_Render_State(D3DRS_FOGENABLE,fm);

			if(fm)
			{
				DX8Wrapper::Set_DX8_Render_State(D3DRS_FOGCOLOR,fogColor);
			}

		} else {
			DX8Wrapper::Set_DX8_Render_State(D3DRS_FOGENABLE,FALSE);
		}
		
		diff &= ~(ShaderClass::MASK_FOG);
		if(!diff)
			return;
	}

	// Defaults
	
	D3DTEXTUREOP	PricOp	= D3DTOP_SELECTARG1;
	DWORD				PricArg1 = D3DTA_DIFFUSE;
	DWORD				PricArg2 = D3DTA_DIFFUSE;

	D3DTEXTUREOP	PriaOp	 = D3DTOP_SELECTARG1;	
	DWORD			PriaArg1 = D3DTA_DIFFUSE;
	DWORD			PriaArg2 = D3DTA_DIFFUSE;

	D3DTEXTUREOP	SeccOp	 = D3DTOP_DISABLE;
	DWORD			SeccArg1 = D3DTA_TEXTURE;
	DWORD			SeccArg2 = D3DTA_CURRENT;

	D3DTEXTUREOP	SecaOp	 = D3DTOP_DISABLE;
	DWORD			SecaArg1 = D3DTA_TEXTURE;
	DWORD			SecaArg2 = D3DTA_CURRENT;

	D3DTEXTUREOP TercOp = D3DTOP_DISABLE;
	DWORD TercArg1 = D3DTA_TEXTURE;
	DWORD TercArg2 = D3DTA_CURRENT;
	D3DTEXTUREOP TeraOp = D3DTOP_DISABLE;

	bool voodoo3=(DX8Wrapper::Get_Current_Caps()->Get_Vendor()==DX8Caps::VENDOR_3DFX) && (DX8Wrapper::Get_Current_Caps()->Get_Device()==DX8Caps::DEVICE_3DFX_VOODOO_3);
	int pri_mask=ShaderClass::MASK_PRIGRADIENT|ShaderClass::MASK_TEXTURING;
	int sec_mask=ShaderClass::MASK_POSTDETAILALPHAFUNC|ShaderClass::MASK_POSTDETAILCOLORFUNC|ShaderClass::MASK_TEXTURING;	

	// Voodoo3s need to keep track of any changes in any of the above
	// because it shuffles the stages around
	if (voodoo3) {
		pri_mask|=sec_mask;
		sec_mask=pri_mask;
	}

	if(diff & pri_mask)
	{
		if(Get_Texturing() == ShaderClass::TEXTURING_ENABLE)
		{
			switch(Get_Primary_Gradient())
			{
			case ShaderClass::GRADIENT_DISABLE:
				//Decal
				PricOp = D3DTOP_SELECTARG1;
				PricArg1 = D3DTA_TEXTURE;
				PricArg2 = D3DTA_CURRENT;
				PriaOp = D3DTOP_SELECTARG1;
				PriaArg1 = D3DTA_TEXTURE;
				PriaArg2 = D3DTA_CURRENT;
				break;
			case ShaderClass::GRADIENT_MODULATE:
				PricOp = ((TextureOpCaps & D3DTOP_MODULATE2X) && ShaderOverbrightEnabled) ? D3DTOP_MODULATE2X : D3DTOP_MODULATE;
				PricArg1 = D3DTA_TEXTURE;
				PricArg2 = D3DTA_DIFFUSE;
				PriaOp = D3DTOP_MODULATE;
				PriaArg1 = D3DTA_TEXTURE;
				PriaArg2 = D3DTA_DIFFUSE;
				break;
			default:
				PricOp = D3DTOP_MODULATE;
				PricArg1 = D3DTA_TEXTURE;
				PricArg2 = D3DTA_DIFFUSE;
				PriaOp = D3DTOP_MODULATE;
				PriaArg1 = D3DTA_TEXTURE;
				PriaArg2 = D3DTA_DIFFUSE;
				break;
			case ShaderClass::GRADIENT_ADD:
				//Modulate Alpha
				if(!(TextureOpCaps & D3DTEXOPCAPS_ADD))	
					PricOp = D3DTOP_MODULATE;
				else
					PricOp = D3DTOP_ADD;
				PricArg1 = D3DTA_TEXTURE;
				PricArg2 = D3DTA_DIFFUSE;
				PriaOp = D3DTOP_MODULATE;
				PriaArg1 = D3DTA_TEXTURE;
				PriaArg2 = D3DTA_DIFFUSE;
				break;

			// Bump map is a hack currently as we only have two stages in use!
			case ShaderClass::GRADIENT_BUMPENVMAP:
				if(TextureOpCaps & D3DTEXOPCAPS_BUMPENVMAP)
				{
					PricOp=D3DTOP_BUMPENVMAP;
					PricArg1=D3DTA_TEXTURE;
					PricArg2=D3DTA_DIFFUSE;
					PriaOp = D3DTOP_DISABLE;
					PriaArg1 = D3DTA_TEXTURE;
					PriaArg2 = D3DTA_CURRENT;
				} else {
					PricOp = D3DTOP_SELECTARG1;
					PricArg1 = D3DTA_DIFFUSE;
					PricArg2 = D3DTA_DIFFUSE;
					PriaOp = D3DTOP_SELECTARG1;
					PriaArg1 = D3DTA_DIFFUSE;
					PriaArg2 = D3DTA_DIFFUSE;
				}
				break;

			// Bump map is a hack currently as we only have two stages in use!
			case ShaderClass::GRADIENT_BUMPENVMAPLUMINANCE:
				if(TextureOpCaps & D3DTEXOPCAPS_BUMPENVMAPLUMINANCE)
				{
					PricOp=D3DTOP_BUMPENVMAPLUMINANCE;
					PricArg1=D3DTA_TEXTURE;
					PricArg2=D3DTA_DIFFUSE;
					PriaOp = D3DTOP_DISABLE;
					PriaArg1 = D3DTA_TEXTURE;
					PriaArg2 = D3DTA_CURRENT;
				} else {
					PricOp = D3DTOP_SELECTARG1;
					PricArg1 = D3DTA_DIFFUSE;
					PricArg2 = D3DTA_DIFFUSE;
					PriaOp = D3DTOP_SELECTARG1;
					PriaArg1 = D3DTA_DIFFUSE;
					PriaArg2 = D3DTA_DIFFUSE;
				}
				break;

			case ShaderClass::GRADIENT_MODULATE2X:
				//Modulate Alpha
				if(!(TextureOpCaps & D3DTOP_MODULATE2X))	
					PricOp = D3DTOP_MODULATE;
				else
					PricOp = D3DTOP_MODULATE2X;
				PricArg1 = D3DTA_TEXTURE;
				PricArg2 = D3DTA_DIFFUSE;
				PriaOp = D3DTOP_MODULATE;
				PriaArg1 = D3DTA_TEXTURE;
				PriaArg2 = D3DTA_DIFFUSE;
				break;
			}

		}
		else
		{
			switch(Get_Primary_Gradient())
			{
			case ShaderClass::GRADIENT_DISABLE:
				PricOp = D3DTOP_DISABLE;
				PricArg1 = D3DTA_TEXTURE;
				PricArg2 = D3DTA_CURRENT;
				PriaOp = D3DTOP_DISABLE;
				PriaArg1 = D3DTA_TEXTURE;
				PriaArg2 = D3DTA_CURRENT;
				break;
			default:
			case ShaderClass::GRADIENT_MODULATE:
				PricOp = D3DTOP_SELECTARG2;
				PricArg1 = D3DTA_TEXTURE;
				PricArg2 = D3DTA_DIFFUSE;
				PriaOp = D3DTOP_SELECTARG2;
				PriaArg1 = D3DTA_TEXTURE;
				PriaArg2 = D3DTA_DIFFUSE;
				break;
			case ShaderClass::GRADIENT_ADD:
				PricOp = D3DTOP_SELECTARG2;
				PricArg1 = D3DTA_TEXTURE;
				PricArg2 = D3DTA_DIFFUSE;
				PriaOp = D3DTOP_SELECTARG2;
				PriaArg1 = D3DTA_TEXTURE;
				PriaArg2 = D3DTA_DIFFUSE;
				break;
			}
		}
	}	

	if(diff & sec_mask)
	{
		if(Get_Texturing()== ShaderClass::TEXTURING_ENABLE)
		{
			switch(Get_Post_Detail_Color_Func())
			{
			default:
			case ShaderClass::DETAILCOLOR_DISABLE:
				break;

			case ShaderClass::DETAILCOLOR_DETAIL:
				if(TextureOpCaps & D3DTEXOPCAPS_SELECTARG1)
				{
					SeccOp = D3DTOP_SELECTARG1;
					SeccArg1 = D3DTA_TEXTURE;
					SeccArg2 = D3DTA_CURRENT;
				}
				else {
					SNAPSHOT_SAY(("Warning: Using unsupported texture op: SELECTARG1\n"));
				}
				break;

			case ShaderClass::DETAILCOLOR_SCALE:
				if(TextureOpCaps & D3DTEXOPCAPS_MODULATE)
				{
					SeccOp = D3DTOP_MODULATE;
					SeccArg1 = D3DTA_TEXTURE;
					SeccArg2 = D3DTA_CURRENT;
				}
				else {
					SNAPSHOT_SAY(("Warning: Using unsupported texture op: MODULATE\n"));
				}
				break;

			case ShaderClass::DETAILCOLOR_INVSCALE:
				if(TextureOpCaps & D3DTEXOPCAPS_ADDSMOOTH)
				{
					SeccOp = D3DTOP_ADDSMOOTH;
					SeccArg1 = D3DTA_TEXTURE;
					SeccArg2 = D3DTA_CURRENT;
				} else if(TextureOpCaps & D3DTEXOPCAPS_ADD) {
					SeccOp = D3DTOP_ADD;
					SeccArg1 = D3DTA_TEXTURE;
					SeccArg2 = D3DTA_CURRENT;
				}
				else {
					SNAPSHOT_SAY(("Warning: Using unsupported texture op: ADDSMOOTH\n"));
				}
				break;

			case ShaderClass::DETAILCOLOR_ADD:
				if(TextureOpCaps & D3DTEXOPCAPS_ADD)
				{
					SeccOp = D3DTOP_ADD;
					SeccArg1 = D3DTA_TEXTURE;
					SeccArg2 = D3DTA_CURRENT;
				}
				else {
					SNAPSHOT_SAY(("Warning: Using unsupported texture op: ADD\n"));
				}
				break;

			case ShaderClass::DETAILCOLOR_SUB:
				if(TextureOpCaps & D3DTEXOPCAPS_SUBTRACT)
				{
					SeccOp = D3DTOP_SUBTRACT;
					SeccArg1 = D3DTA_TEXTURE;
					SeccArg2 = D3DTA_CURRENT;
				}
				else {
					SNAPSHOT_SAY(("Warning: Using unsupported texture op: SUBTRACT\n"));
				}
				break;

			case ShaderClass::DETAILCOLOR_SUBR:
				if(TextureOpCaps & D3DTEXOPCAPS_SUBTRACT)
				{
					SeccOp = D3DTOP_SUBTRACT;
					SeccArg1 = D3DTA_CURRENT;
					SeccArg2 = D3DTA_TEXTURE;
				}
				else {
					SNAPSHOT_SAY(("Warning: Using unsupported texture op: SUBTRACT\n"));
				}
				break;

			case ShaderClass::DETAILCOLOR_BLEND:
				if(TextureOpCaps & D3DTEXOPCAPS_BLENDTEXTUREALPHA)
				{
					SeccOp = D3DTOP_BLENDTEXTUREALPHA;
					SeccArg1 = D3DTA_TEXTURE;
					SeccArg2 = D3DTA_CURRENT;
				}
				else {
					SNAPSHOT_SAY(("Warning: Using unsupported texture op: BLENDTEXTUREALPHA\n"));
				}
				break;

			case ShaderClass::DETAILCOLOR_DETAILBLEND:
				if(TextureOpCaps & D3DTEXOPCAPS_BLENDCURRENTALPHA)
				{
					SeccOp = D3DTOP_BLENDCURRENTALPHA;
					SeccArg1 = D3DTA_TEXTURE;
					SeccArg2 = D3DTA_CURRENT;
				}
				else {
					SNAPSHOT_SAY(("Warning: Using unsupported texture op: BLENDCURRENTALPHA\n"));
				}
				break;

			case ShaderClass::DETAILCOLOR_ADDSIGNED:
				if (TextureOpCaps & D3DTEXOPCAPS_ADDSIGNED) {
					SeccOp = D3DTOP_ADDSIGNED;
					SeccArg1 = D3DTA_TEXTURE;
					SeccArg2 = D3DTA_CURRENT;
				}  else if (TextureOpCaps & D3DTEXOPCAPS_ADD) {
					SeccOp = D3DTOP_ADD;
					SeccArg1 = D3DTA_TEXTURE;
					SeccArg2 = D3DTA_CURRENT;
				} else {
					SNAPSHOT_SAY(("Warning: Using unsupported texture op: ADDSIGNED\n"));
				}					
				break;

			case ShaderClass::DETAILCOLOR_ADDSIGNED2X:
				if (TextureOpCaps & D3DTEXOPCAPS_ADDSIGNED2X) {
					SeccOp = D3DTOP_ADDSIGNED2X;
					SeccArg1 = D3DTA_TEXTURE;
					SeccArg2 = D3DTA_CURRENT;
				} else if (TextureOpCaps & D3DTEXOPCAPS_ADDSIGNED) {
					SeccOp = D3DTOP_ADDSIGNED;
					SeccArg1 = D3DTA_TEXTURE;
					SeccArg2 = D3DTA_CURRENT;
				}  else if (TextureOpCaps & D3DTEXOPCAPS_ADD) {
					SeccOp = D3DTOP_ADD;
					SeccArg1 = D3DTA_TEXTURE;
					SeccArg2 = D3DTA_CURRENT;
				} else {
					SNAPSHOT_SAY(("Warning: Using unsupported texture op: ADDSIGNED2X\n"));
				}					
				break;

			case ShaderClass::DETAILCOLOR_SCALE2X:
				if(TextureOpCaps & D3DTEXOPCAPS_MODULATE2X) {
					SeccOp = D3DTOP_MODULATE2X;
					SeccArg1 = D3DTA_TEXTURE;
					SeccArg2 = D3DTA_CURRENT;
				} else if(TextureOpCaps & D3DTEXOPCAPS_MODULATE) {
					SeccOp = D3DTOP_MODULATE;
					SeccArg1 = D3DTA_TEXTURE;
					SeccArg2 = D3DTA_CURRENT;
				}
				else {
					SNAPSHOT_SAY(("Warning: Using unsupported texture op: MODULATE2X\n"));
				}				
				break;

			case ShaderClass::DETAILCOLOR_MODALPHAADDCOLOR:
				if (DX8Wrapper::Get_Current_Caps()->Support_ModAlphaAddClr()) {
					SeccOp = D3DTOP_MODULATEALPHA_ADDCOLOR;
					SeccArg1 = D3DTA_CURRENT;
					SeccArg2 = D3DTA_SPECULAR;
				} else if (TextureOpCaps & D3DTEXOPCAPS_ADD) {
					SeccOp = D3DTOP_ADD;
					SeccArg1 = D3DTA_TEXTURE;
					SeccArg2 = D3DTA_CURRENT;
				} else {
					SNAPSHOT_SAY(("Warning: Using unsupported texture op: MODULATEALPHA_ADDCOLOR\n"));
				}
				break;
			case ShaderClass::DETAILCOLOR_MAX:
				SeccOp = D3DTOP_BLENDTEXTUREALPHA;
				SeccArg1 = D3DTA_TEXTURE;
				SeccArg2 = D3DTA_CURRENT;
				SecaOp = D3DTOP_SELECTARG2;
				SecaArg2 = D3DTA_CURRENT;
				if (DX8Wrapper::Get_Current_Caps()->Get_Max_Textures_Per_Pass() > 2 && DX8Wrapper::Get_Current_Caps()->Support_ModAlphaAddClr()) {
					TercOp = D3DTOP_MODULATEALPHA_ADDCOLOR;
					TercArg1 = D3DTA_CURRENT;
					TercArg2 = D3DTA_SPECULAR;
					TeraOp = D3DTOP_SELECTARG2;
				}
				break;
			} // color operations

			switch(Get_Post_Detail_Alpha_Func())
			{
			default:
			case ShaderClass::DETAILALPHA_DISABLE:
				break;

			case ShaderClass::DETAILALPHA_DETAIL:
				if(TextureOpCaps & D3DTEXOPCAPS_SELECTARG1)
				{
					SecaOp = D3DTOP_SELECTARG1;
					SecaArg1 = D3DTA_TEXTURE;
					SecaArg2 = D3DTA_CURRENT;
				}
				else {
					SNAPSHOT_SAY(("Warning: Using unsupported texture op: SELECTARG1\n"));
				}
				break;

			case ShaderClass::DETAILALPHA_SCALE:
				if(TextureOpCaps & D3DTEXOPCAPS_MODULATE)
				{
					SecaOp = D3DTOP_MODULATE;
					SecaArg1 = D3DTA_TEXTURE;
					SecaArg2 = D3DTA_CURRENT;
				}
				else {
					SNAPSHOT_SAY(("Warning: Using unsupported texture op: MODULATE\n"));
				}
				break;

			case ShaderClass::DETAILALPHA_INVSCALE:
				if(TextureOpCaps & D3DTEXOPCAPS_ADDSMOOTH)
				{
					SecaOp = D3DTOP_ADDSMOOTH;
					SecaArg1 = D3DTA_TEXTURE;
					SecaArg2 = D3DTA_CURRENT;
				}
				else {
					SNAPSHOT_SAY(("Warning: Using unsupported texture op: ADDSMOOTH\n"));
				}
				break;
			} // alpha operations

			// if color is enabled and alpha is disabled set to pass alpha through
			if ((SeccOp!=D3DTOP_DISABLE) && (SecaOp==D3DTOP_DISABLE)) {
				SecaOp = D3DTOP_SELECTARG2;
				SecaArg2 = D3DTA_CURRENT;
			} else if ((SeccOp==D3DTOP_DISABLE) && (SecaOp!=D3DTOP_DISABLE)) {
				SeccOp = D3DTOP_SELECTARG2;
				SeccArg2 = D3DTA_CURRENT;
			}
		}	// texturing enabled
	}	// if diff sec_mask	
	
	bool kill_stage_2=false;

	// Apply the stage settings
	if (diff & pri_mask) {
		// for voodoo3 supported blend modes, the stage 0 color and alpha are both diffuse
		// or both not, so we can check for color diffuse only
		if ( voodoo3 && (PricArg2==D3DTA_DIFFUSE) && 
			  ( (SecaOp!=D3DTOP_DISABLE) || (SeccOp!=D3DTOP_DISABLE) )
			) {
			// Special Voodoo3 code
			// If stage 0 has a diffuse input
			// and stage 1 has an input put the diffuse in stage 2			
			
			DWORD tex_arg=D3DTA_CURRENT;
			if(Get_Texturing() == ShaderClass::TEXTURING_ENABLE) {
				tex_arg=D3DTA_TEXTURE;
			}
			
			// this is for the bad case of using
			// stage 0 for diffuse only
			if ((PricOp==D3DTOP_SELECTARG1)&&(PricArg1==D3DTA_DIFFUSE)) {
				WWDEBUG_SAY(("Wasted Stage 0 in shader-vertex diffuse only"));
				// set stage 0 to disable
				DX8Wrapper::Set_DX8_Texture_Stage_State(0,D3DTSS_COLOROP,D3DTOP_DISABLE);				
				DX8Wrapper::Set_DX8_Texture_Stage_State(0,D3DTSS_ALPHAOP,D3DTOP_DISABLE);
				// set stage 1 to accept diffuse
				if (SeccArg2==D3DTA_CURRENT) SeccArg2=D3DTA_DIFFUSE;
				if (SecaArg2==D3DTA_CURRENT) SecaArg2=D3DTA_DIFFUSE;
				// and nuke stage 2
				kill_stage_2=true;
			} else {
				// set stage 0 to pass through what it needs
				DX8Wrapper::Set_DX8_Texture_Stage_State(0,D3DTSS_COLOROP,D3DTOP_SELECTARG1);
				DX8Wrapper::Set_DX8_Texture_Stage_State(0,D3DTSS_COLORARG1,tex_arg);
				DX8Wrapper::Set_DX8_Texture_Stage_State(0,D3DTSS_ALPHAOP,D3DTOP_SELECTARG1);			
				DX8Wrapper::Set_DX8_Texture_Stage_State(0,D3DTSS_ALPHAARG1,tex_arg);

				// set stage 2 to do the diffuse op
				// bypass the wrapper since it only supports 2 texture stages
				DX8CALL(SetTextureStageState(2,D3DTSS_COLOROP,PricOp));
				DX8CALL(SetTextureStageState(2,D3DTSS_COLORARG1,D3DTA_CURRENT));
				DX8CALL(SetTextureStageState(2,D3DTSS_COLORARG2,D3DTA_DIFFUSE));
				DX8CALL(SetTextureStageState(2,D3DTSS_ALPHAOP,PriaOp));
				DX8CALL(SetTextureStageState(2,D3DTSS_ALPHAARG1,D3DTA_CURRENT));
				DX8CALL(SetTextureStageState(2,D3DTSS_ALPHAARG2,D3DTA_DIFFUSE));
				DX8CALL(SetTextureStageState(2,D3DTSS_TEXCOORDINDEX,D3DTSS_TCI_PASSTHRU));
				DX8CALL(SetTexture(2,0));
				kill_stage_2=false;
				ShaderDirty=true;
			}			
		} else {
			
#pragma message("(gth) Generals added a feature here WW3D::Is_Coloring_Enabled() which needs to be merged properly")
#if 0
			if (WW3D::Is_Coloring_Enabled())
			{
				cArg2=aArg2=D3DTA_SPECULAR;
				cOp=aOp=D3DTOP_SELECTARG2;
			}
#endif
			DX8Wrapper::Set_DX8_Texture_Stage_State(0,D3DTSS_COLOROP,PricOp);
			DX8Wrapper::Set_DX8_Texture_Stage_State(0,D3DTSS_COLORARG1,PricArg1);
			DX8Wrapper::Set_DX8_Texture_Stage_State(0,D3DTSS_COLORARG2,PricArg2);
			DX8Wrapper::Set_DX8_Texture_Stage_State(0,D3DTSS_ALPHAOP,PriaOp);
			DX8Wrapper::Set_DX8_Texture_Stage_State(0,D3DTSS_ALPHAARG1,PriaArg1);
			DX8Wrapper::Set_DX8_Texture_Stage_State(0,D3DTSS_ALPHAARG2,PriaArg2);
			kill_stage_2=true;
		}
		diff &= ~(ShaderClass::MASK_PRIGRADIENT);
	}	

	if (diff & sec_mask) {
		DX8Wrapper::Set_DX8_Texture_Stage_State(1,D3DTSS_COLOROP,SeccOp);
		DX8Wrapper::Set_DX8_Texture_Stage_State(1,D3DTSS_COLORARG1,SeccArg1);
		DX8Wrapper::Set_DX8_Texture_Stage_State(1,D3DTSS_COLORARG2,SeccArg2);	
		DX8Wrapper::Set_DX8_Texture_Stage_State(1,D3DTSS_ALPHAOP,SecaOp);
		DX8Wrapper::Set_DX8_Texture_Stage_State(1,D3DTSS_ALPHAARG1,SecaArg1);
		DX8Wrapper::Set_DX8_Texture_Stage_State(1,D3DTSS_ALPHAARG2,SecaArg2);
		if (DX8Wrapper::Get_Current_Caps()->Get_Max_Textures_Per_Pass() > 2) {
			DX8Wrapper::Set_DX8_Texture_Stage_State(2,D3DTSS_COLOROP,TercOp);
			DX8Wrapper::Set_DX8_Texture_Stage_State(2,D3DTSS_COLORARG1,TercArg1);
			DX8Wrapper::Set_DX8_Texture_Stage_State(2,D3DTSS_COLORARG2,TercArg2);
			DX8Wrapper::Set_DX8_Texture_Stage_State(2,D3DTSS_ALPHAOP,TeraOp);
			DX8Wrapper::Set_DX8_Texture_Stage_State(2,D3DTSS_ALPHAARG1,D3DTA_TEXTURE);
			DX8Wrapper::Set_DX8_Texture_Stage_State(2,D3DTSS_ALPHAARG2,D3DTA_CURRENT);
		}
		diff &= ~(ShaderClass::MASK_POSTDETAILCOLORFUNC);
		diff &= ~(ShaderClass::MASK_POSTDETAILALPHAFUNC);
		diff &= ~(ShaderClass::MASK_TEXTURING);
	}
	
	// Make sure to disable stage 2 for voodoos since we don't have state tracking for
	// stage 2
	// bypass the wrapper since it only supports 2 texture stages
	if (voodoo3 && kill_stage_2) {
		if ((SeccOp!=D3DTOP_DISABLE)&&(SecaOp!=D3DTOP_DISABLE)) {
			DX8CALL(SetTextureStageState(2,D3DTSS_COLOROP,D3DTOP_SELECTARG1));
			DX8CALL(SetTextureStageState(2,D3DTSS_COLORARG1,D3DTA_CURRENT));
			DX8CALL(SetTextureStageState(2,D3DTSS_ALPHAOP,D3DTOP_SELECTARG1));
			DX8CALL(SetTextureStageState(2,D3DTSS_ALPHAARG1,D3DTA_CURRENT));
		} else {
			DX8CALL(SetTextureStageState(2,D3DTSS_COLOROP,D3DTOP_DISABLE));
			DX8CALL(SetTextureStageState(2,D3DTSS_ALPHAOP,D3DTOP_DISABLE));
		}
		DX8CALL(SetTextureStageState(2,D3DTSS_TEXCOORDINDEX,D3DTSS_TCI_PASSTHRU));
		DX8CALL(SetTexture(2,0));
	}

	if(!diff)
		return;

	DX8Wrapper::Set_DX8_Render_State(D3DRS_SPECULARENABLE,BOOL(Get_Secondary_Gradient()));

	// DEPTH COMPARE FUNCTION
	DX8Wrapper::Set_DX8_Render_State(D3DRS_ZFUNC,D3DCMPFUNC(int(Get_Depth_Compare())+1));

	// DEPTH MASK
	DX8Wrapper::Set_DX8_Render_State(D3DRS_ZWRITEENABLE,BOOL(Get_Depth_Mask()));

	// DITHERING
//	DX8Wrapper::Set_DX8_Render_State(D3DRS_DITHERENABLE,BOOL(Get_Dither_Mask()));

	// CULLMODE
	DX8Wrapper::Set_DX8_Render_State(D3DRS_CULLMODE,Get_Cull_Mode() ? _PolygonCullMode : D3DCULL_NONE);

	// NPATCHES
	if (diff&ShaderClass::MASK_NPATCHENABLE) {
		if (Get_NPatch_Enable()) {
			DX8CALL(SetNPatchMode(float(WW3D::Get_NPatches_Level() - 1)));
		}
	}

	// Enable/disable alpha test
	DX8Wrapper::Set_DX8_Render_State(D3DRS_ALPHATESTENABLE,BOOL(Get_Alpha_Test()));	

	// Enable/disable stencil test
	// Not supported yet
}
