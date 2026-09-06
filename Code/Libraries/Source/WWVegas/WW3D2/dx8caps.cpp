// cl: /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
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
 *                 Project Name : dx8 caps                                                     *
 *                                                                                             *
 *                     $Archive:: /Commando/Code/ww3d2/dx8caps.cpp                            $*
 *                                                                                             *
 *              Original Author:: Hector Yee                                                   *
 *                                                                                             *
 *                       Author : Kenny Mitchell                                               * 
 *                                                                                             * 
 *                     $Modtime:: 06/27/02 1:27p                                              $*
 *                                                                                             *
 *                    $Revision:: 31                                                          $*
 *                                                                                             *
 * 06/27/02 KM Z Format support																						*
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include "always.h"
#include "dx8caps.h"
#include "dx8wrapper.h"
#include "formconv.h"
#pragma warning (disable : 4201)		// nonstandard extension - nameless struct
#include <windows.h>
#include <mmsystem.h>

static StringClass CapsWorkString;

#define DXLOG(n) CapsWorkString.Format n ; CapsLog+=CapsWorkString;
// Same as DXLOG but appends through the overlay, so the body reaches CapsLog
// at retail's 0x2DC instead of our class's 0x14C.
#define DXLOG_RETAIL(n) CapsWorkString.Format n ; retail->capsLogAll+=CapsWorkString;
#define COMPACTLOG(n) CapsWorkString.Format n ; CompactLog+=CapsWorkString;

static const char* VendorNames[]={
	"Unknown",
	"NVidia",
	"ATI",
	"Intel",
	"S3",
	"PowerVR",
	"Matrox",
	"3Dfx",
	"3DLabs",
	"CirrusLogic",
	"Rendition"
};

DX8Caps::VendorIdType DX8Caps::Define_Vendor(unsigned vendor_id)
{
	switch (vendor_id) {
	case 0x3d3d:
	case 0x104c: return VENDOR_3DLABS;
	case 0x12D2: // STB - NVIDIA's Riva128
	case 0x14AF: // Guillemot's NVIDIA based cards
	case 0x10de: return VENDOR_NVIDIA;
	case 0x1002: return VENDOR_ATI;
	case 0x8086: return VENDOR_INTEL;
	case 0x5333: return VENDOR_S3;
	case 0x104A: return VENDOR_POWERVR;
	case 0x102B: return VENDOR_MATROX;
	case 0x1142: // Alliance based reference cards
	case 0x109D: // Macronix based reference cards
	case 0x121A: return VENDOR_3DFX;
	default:
		return VENDOR_UNKNOWN;
	}
}

static const char* DeviceNamesNVidia[]={
	"Unknown NVidia device",
	"GeForce3",
	"Quadro2 PRO",
	"GeForce2 Go",
	"GeForce2 ULTRA",
	"GeForce2 GTS",
	"Quadro",
	"GeForce DDR",
	"GeForce 256",
	"TNT2 Aladdin",
	"TNT2",
	"TNT2 ULTRA",
	"TNT2 Vanta",
	"TNT2 M64",
	"TNT",
	"RIVA 128",
	"TNT Vanta",
	"NV1",
	"GeForce2 MX"
	"GeForce4 Ti 4600",
	"GeForce4 Ti 4400",
	"GeForce4 Ti",
	"GeForce4 Ti 4200",
	"GeForce4 MX 460",
	"GeForce4 MX 440",
	"GeForce4 MX 420",
	"GeForce4",
	"GeForce4 Go 440",
	"GeForce4 Go 420",
	"GeForce4 Go 420 32M",
	"GeForce4 Go 440 64M",
	"GeForce4 Go",
	"GeForce3 Ti 500",
	"GeForce3 Ti 200",
	"GeForce2 Integrated",
	"GeForce2 Ti",
	"Quadro2 MXR//EX//GO",
	"GeFORCE2_MX 100//200",
	"GeFORCE2_MX 400",
	"Quadro DCC"
};

static const char* DeviceNamesATI[]={
	"Unknown ATI Device",
	"Rage II",
	"Rage II+",
	"Rage IIc PCI",
	"Rage IIc AGP",
	"Rage 128 Mobility",
	"Rage 128 Mobility M3",
	"Rage 128 Mobility M4",
	"Rage 128 PRO ULTRA",
	"Rage 128 4X",
	"Rage 128 PRO GL",
	"Rage 128 PRO VR",
	"Rage 128 GL",
	"Rage 128 VR",
	"Rage PRO",
	"Rage PRO Mobility",
	"Mobility Radeon",
	"Mobility Radeon VE(M6)",
	"Radeon VE",
	"Radeon DDR",
	"Radeon",
	"Mobility R7500",
	"R7500",
	"R8500"
};

static const char* DeviceNames3DLabs[]={
	"Unknown 3DLabs Device",
	"Permedia",
	"300SX",
	"500TX",
	"Delta",
	"MX",
	"Gamma",
	"Permedia2S (ST)",
	"Permedia3",
	"R3",
	"Permedia4",
	"R4",
	"G2",
	"Oxygen VX1",
	"TI P1",
	"Permedia2"
};

static const char* DeviceNames3Dfx[]={
	"Unknown 3Dfx Device",
	"Voodoo 5500 AGP",
	"Voodoo 3",
	"Banshee",
	"Voodoo 2",
	"Voodoo Graphics",
	"Voodoo Rush"
};

static const char* DeviceNamesMatrox[]={
	"Unknown Matrox Device",
	"G550",
	"G400",
	"G200 AGP",
	"G200 PCI",
	"G100 PCI",
	"G100 AGP",
	"Millennium II AGP",
	"Millennium II PCI",
	"Mystique",
	"Millennium",
	"Parhelia",
	"Parhelia AGP 8X"
};

static const char* DeviceNamesPowerVR[]={
	"Unknown PowerVR Device",
	"Kyro"
};

static const char* DeviceNamesS3[]={
	"Unknown S3 Device",
	"Savage MX",
	"Savage 4",
	"Savage 200"
};

static const char* DeviceNamesIntel[]={
	"Unknown Intel Device",
	"i810",
	"i810e",
	"i815"
};

DX8Caps::DeviceTypeATI DX8Caps::Get_ATI_Device(unsigned device_id)
{
	switch (device_id) {
	case 0x4754: return DEVICE_ATI_RAGE_II;
	case 0x4755: return DEVICE_ATI_RAGE_II_PLUS;
	case 0x5656: return DEVICE_ATI_RAGE_IIC_PCI;
	case 0x4756: return DEVICE_ATI_RAGE_IIC_PCI;
	case 0x475A: return DEVICE_ATI_RAGE_IIC_AGP;
	case 0x4759: return DEVICE_ATI_RAGE_IIC_AGP;
	case 0x4757: return DEVICE_ATI_RAGE_IIC_AGP;
	case 0x4742:
	case 0x4744:
	case 0x4749:
	case 0x4750:
	case 0x474C:
	case 0x474E:
	case 0x474D:
	case 0x474F:
	case 0x4752: return DEVICE_ATI_RAGE_PRO;

	case 0x4C4D:
	case 0x4C52:
	case 0x4C42:
	case 0x4C49:
	case 0x4C50: return DEVICE_ATI_RAGE_PRO_MOBILITY;

	case 0x4C57: return DEVICE_ATI_MOBILITY_R7500;

	case 0x4C59:
	case 0x4C5A: return DEVICE_ATI_MOBILITY_RADEON_VE_M6;

	case 0x4D46:
	case 0x4D4C: return DEVICE_ATI_RAGE_128_MOBILITY_M4;
	case 0x4C45:
	case 0x4C46: return DEVICE_ATI_RAGE_128_MOBILITY_M3;

	case 0x5041: 
	case 0x5042: 
	case 0x5043: 
	case 0x5044: 
	case 0x5045: 
	case 0x5046: return DEVICE_ATI_RAGE_128_PRO_GL;

	case 0x5047:
	case 0x5048:
	case 0x5049:
	case 0x504A:
	case 0x504B:
	case 0x504C:
	case 0x504D:
	case 0x504E:
	case 0x504F:
	case 0x5050:
	case 0x5051:
	case 0x5052:
	case 0x5053:
	case 0x5054:
	case 0x5055:
	case 0x5056:
	case 0x5057:
	case 0x5058: return DEVICE_ATI_RAGE_128_PRO_VR;

	case 0x5159:
	case 0x515A: return DEVICE_ATI_RADEON_VE;

	case 0x5144:
	case 0x5145:
	case 0x5146:
	case 0x5147: return DEVICE_ATI_RADEON_DDR;

	case 0x514c:
	case 0x514e:
	case 0x514f: return DEVICE_ATI_R8500;

	case 0x5157: return DEVICE_ATI_R7500;

	case 0x5245: 
	case 0x5246: 
	case 0x534B: 
	case 0x534C: 
	case 0x534D: return DEVICE_ATI_RAGE_128_GL;

	case 0x524B:
	case 0x524C:
	case 0x5345:
	case 0x5346:
	case 0x5347: return DEVICE_ATI_RAGE_128_VR;

	case 0x5446:
	case 0x544C:
	case 0x5452:
	case 0x5453:
	case 0x5454:
	case 0x5455: return DEVICE_ATI_RAGE_128_PRO_ULTRA;

	case 0x534E: return DEVICE_ATI_RAGE_128_4X;

	default: return DEVICE_ATI_UNKNOWN;
	}
}

DX8Caps::DeviceType3DLabs DX8Caps::Get_3DLabs_Device(unsigned device_id)
{
	switch (device_id) {
	case 0x0001: return DEVICE_3DLABS_300SX;
	case 0x0002: return DEVICE_3DLABS_500TX;
	case 0x0003: return DEVICE_3DLABS_DELTA;
	case 0x0004: return DEVICE_3DLABS_PERMEDIA;
	case 0x0006: return DEVICE_3DLABS_MX;
	case 0x0007: return DEVICE_3DLABS_PERMEDIA2;
	case 0x0008: return DEVICE_3DLABS_GAMMA;
	case 0x0009: return DEVICE_3DLABS_PERMEDIA2S_ST;
	case 0x000a: return DEVICE_3DLABS_PERMEDIA3;
	case 0x000b: return DEVICE_3DLABS_R3;
	case 0x000c: return DEVICE_3DLABS_PERMEDIA4;
	case 0x000d: return DEVICE_3DLABS_R4;
	case 0x000e: return DEVICE_3DLABS_G2;
	case 0x4C59: return DEVICE_3DLABS_OXYGEN_VX1;
	case 0x3D04: return DEVICE_3DLABS_TI_P1;
	case 0x3D07: return DEVICE_3DLABS_PERMEDIA2;
	default: return DEVICE_3DLABS_UNKNOWN;
	}
}

DX8Caps::DeviceTypeNVidia DX8Caps::Get_NVidia_Device(unsigned device_id)
{
	switch (device_id) {
	case 0x0250: return DEVICE_NVIDIA_GEFORCE4_TI_4600;
	case 0x0251: return DEVICE_NVIDIA_GEFORCE4_TI_4400;
	case 0x0252: return DEVICE_NVIDIA_GEFORCE4_TI;
	case 0x0253: return DEVICE_NVIDIA_GEFORCE4_TI_4200;
	case 0x0170: return DEVICE_NVIDIA_GEFORCE4_MX_460;
	case 0x0171: return DEVICE_NVIDIA_GEFORCE4_MX_440;
	case 0x0172: return DEVICE_NVIDIA_GEFORCE4_MX_420;
	case 0x0173: return DEVICE_NVIDIA_GEFORCE4;
	case 0x0174: return DEVICE_NVIDIA_GEFORCE4_GO_440;
	case 0x0175: return DEVICE_NVIDIA_GEFORCE4_GO_420;
	case 0x0176: return DEVICE_NVIDIA_GEFORCE4_GO_420_32M;
	case 0x0178: return DEVICE_NVIDIA_GEFORCE4_GO;
	case 0x0179: return DEVICE_NVIDIA_GEFORCE4_GO_440_64M;
	case 0x0203: return DEVICE_NVIDIA_QUADRO_DCC;
	case 0x0202: return DEVICE_NVIDIA_GEFORCE3_TI_500;
	case 0x0201: return DEVICE_NVIDIA_GEFORCE3_TI_200;
	case 0x0200: return DEVICE_NVIDIA_GEFORCE3;
	case 0x01A0: return DEVICE_NVIDIA_GEFORCE2_INTEGRATED;
	case 0x0153: return DEVICE_NVIDIA_QUADRO2_PRO;
	case 0x0152: return DEVICE_NVIDIA_GEFORCE2_ULTRA;
	case 0x0151: return DEVICE_NVIDIA_GEFORCE2_TI;
	case 0x0150: return DEVICE_NVIDIA_GEFORCE2_GTS;
	case 0x0113: return DEVICE_NVIDIA_QUADRO2_MXR_EX_GO;
	case 0x0112: return DEVICE_NVIDIA_GEFORCE2_GO;
	case 0x0111: return DEVICE_NVIDIA_GEFORCE2_MX_100_200;
	case 0x0110: return DEVICE_NVIDIA_GEFORCE2_MX_400;
	case 0x0103: return DEVICE_NVIDIA_QUADRO;
	case 0x0101: return DEVICE_NVIDIA_GEFORCE_DDR;
	case 0x0100: return DEVICE_NVIDIA_GEFORCE_256;
	case 0x00A0: return DEVICE_NVIDIA_TNT2_ALADDIN;
	case 0x0028: return DEVICE_NVIDIA_TNT2;
	case 0x0029: return DEVICE_NVIDIA_TNT2_ULTRA;
	case 0x002C: return DEVICE_NVIDIA_TNT2_VANTA;
	case 0x002D: return DEVICE_NVIDIA_TNT2_M64;
	case 0x0020: return DEVICE_NVIDIA_TNT;
	case 0x0008: return DEVICE_NVIDIA_NV1;

	// STB cards
	case 0x0019:
	case 0x0018: return DEVICE_NVIDIA_RIVA_128;

	// Guillemot Cards
	case 0x5008: return DEVICE_NVIDIA_TNT_VANTA;		// Maxi Gamer Phoenix 2
	case 0x5810: return DEVICE_NVIDIA_TNT2;			// Maxi Gamer Xentor
	case 0x5820: return DEVICE_NVIDIA_TNT2_ULTRA;	// Maxi Gamer Xentor 32
	case 0x4d20: return DEVICE_NVIDIA_TNT2_M64;		// Maxi Gamer Cougar
	case 0x5620: return DEVICE_NVIDIA_TNT2_M64;		// Maxi Gamer Cougar Video Edition
	case 0x5020: return DEVICE_NVIDIA_GEFORCE_256;	// Maxi Gamer 3D Prophet

	default: return DEVICE_NVIDIA_UNKNOWN;
	}
}


DX8Caps::DeviceType3Dfx DX8Caps::Get_3Dfx_Device(unsigned device_id)
{
	switch (device_id) {
	case 0x0009: return DEVICE_3DFX_VOODOO_5500_AGP;
	case 0x0005: return DEVICE_3DFX_VOODOO_3;
	case 0x0003: return DEVICE_3DFX_BANSHEE;
	case 0x0002: return DEVICE_3DFX_VOODOO_2;
	case 0x0001: return DEVICE_3DFX_VOODOO_GRAPHICS;
	case 0x643d: // Alliance AT25/AT3D based reference board
	case 0x8626: // Macronix based reference board
		return DEVICE_3DFX_VOODOO_RUSH;
	default: return DEVICE_3DFX_UNKNOWN;
	}
}

DX8Caps::DeviceTypeMatrox DX8Caps::Get_Matrox_Device(unsigned device_id)
{
	switch (device_id) {
	case 0x2527: return DEVICE_MATROX_G550;
	case 0x0525: return DEVICE_MATROX_G400;
	case 0x0521: return DEVICE_MATROX_G200_AGP;
	case 0x0520: return DEVICE_MATROX_G200_PCI;
	case 0x1000: return DEVICE_MATROX_G100_PCI;
	case 0x1001: return DEVICE_MATROX_G100_AGP;
	case 0x051F: return DEVICE_MATROX_MILLENNIUM_II_AGP;
	case 0x051B: return DEVICE_MATROX_MILLENNIUM_II_PCI;
	case 0x051A: return DEVICE_MATROX_MYSTIQUE;
	case 0x0519: return DEVICE_MATROX_MILLENNIUM;
	case 0x0527: return DEVICE_MATROX_PARHELIA;
	case 0x0528: return DEVICE_MATROX_PARHELIA_AGP8X;

	default: return DEVICE_MATROX_UNKNOWN;
	}
}
 
DX8Caps::DeviceTypePowerVR DX8Caps::Get_PowerVR_Device(unsigned device_id)
{
	switch (device_id) {
	case 0x0010: return DEVICE_POWERVR_KYRO;
	default: return DEVICE_POWERVR_UNKNOWN;
	}
}

DX8Caps::DeviceTypeS3 DX8Caps::Get_S3_Device(unsigned device_id)
{
	switch (device_id) {
	case 0x8C10: return DEVICE_S3_SAVAGE_MX;
	case 0x8A22: return DEVICE_S3_SAVAGE_4;
	case 0x9102: return DEVICE_S3_SAVAGE_200;
	default: return DEVICE_S3_UNKNOWN;
	}
}

DX8Caps::DeviceTypeIntel DX8Caps::Get_Intel_Device(unsigned device_id)
{
	switch (device_id) {
	case 0x7123: return DEVICE_INTEL_810;
	case 0x7121: return DEVICE_INTEL_810E;
	case 0x1132: return DEVICE_INTEL_815;
	default: return DEVICE_INTEL_UNKNOWN;
	}
}

// ??0DX8Caps@@QAE@PAUIDirect3D8@@PAUIDirect3DDevice8@@W4WW3DFormat@@ABU_D3DADAPTER_IDENTIFIER8@@@Z
// Body in DX8Caps_ctor_device.asm (exact 233B retail @ 0x0091CB00).
// C++ blocked: BFME class layout (DriverDLL@+0x29c) vs ZH header (+0x144).

// byte-exact reconstruction: Code/Libraries/Source/WWVegas/WW3D2/DX8Caps_ctor_device_Thunk.cpp
// ??0DX8Caps@@ present-unmatched
DX8Caps::DX8Caps(
	IDirect3D8* direct3d,
	const D3DCAPS8& caps, 
	WW3DFormat display_format, 
	const D3DADAPTER_IDENTIFIER8& adapter_id)
	:
	Direct3D(direct3d),
	Caps(caps),
	MaxDisplayWidth(0),
	MaxDisplayHeight(0)
{
	if ((Caps.DevCaps&D3DDEVCAPS_HWTRANSFORMANDLIGHT)==D3DDEVCAPS_HWTRANSFORMANDLIGHT) {
		SupportTnL=true;
	} else {
		SupportTnL=false;			
	}

	Compute_Caps(display_format,adapter_id);
}

//Don't really need this but I added this function to free static variables so
//they don't show up in our memory manager as a leak. -MW 7-22-03
// ?Shutdown@DX8Caps@@SAXXZ present-unmatched
void DX8Caps::Shutdown(void)
{
	CapsWorkString.Release_Resources();
}

// ----------------------------------------------------------------------------
//
// Init the caps structure
//
// ----------------------------------------------------------------------------

// BFME's device interface is IDirect3DDevice9, not IDirect3DDevice8, so the
// software-vertex-processing switch is the dedicated method at vtable slot 77
// (+0x134) rather than the D3DRS_SOFTWAREVERTEXPROCESSING render state ZH sets
// through SetRenderState. Three independent slots confirm the D3D9 numbering
// against retail: SetRenderState +0xe4 (D3D9 index 57), SetVertexShaderConstantF
// +0x178 (94) and SetPixelShaderConstantF +0x1b4 (109) -- exactly the offsets
// reference/shims/d3d8_shim_validated.h was padded to reproduce. That shim
// still models the intervening slots with DX8 names, so slot 77 is spelled here
// as a direct dispatch rather than renamed out from under every other WW3D2
// source in the tree.
typedef HRESULT (__stdcall *SetSoftwareVertexProcessingProc)(IDirect3DDevice8 *device, BOOL software);

static void Set_Software_Vertex_Processing(IDirect3DDevice8 *device, BOOL software)
{
	(*(SetSoftwareVertexProcessingProc **)device)[0x134 / 4](device, software);
}

// Same overlay trick as BFME_DX8Caps_CheckBumpmapFields and
// BFME_DX8Caps_CheckShaderFields: SupportTnL sits at 0x138 in BFME's DX8Caps
// where ours puts it at 0xdc, exactly four bytes ahead of the 0x13c
// SupportBumpEnvmap the bumpmap overlay already uses -- the two agree, which is
// what says this is one layout and not two guesses. The 92-byte gap is
// sizeof(D3DCAPS9) - sizeof(D3DCAPS8): BFME's Caps member is the D3D9 struct,
// which is the same D3D9 device interface the slot-77 dispatch above needs.
// Caps itself still starts at 0x08, so &Caps and Caps.DevCaps at 0x24 are
// already at their retail offsets and need no overlay.
struct BFME_DX8Caps_InitCapsFields
{
	char pad[0x138];
	bool supportTnL;						// 0x138
};

void DX8Caps::Init_Caps(IDirect3DDevice8* D3DDevice)
{
	// BFME does NOT do Zero Hour's two-pass probe here.  Retail is 51 bytes:
	// one GetDeviceCaps through the device global, the call counter, and
	// SupportTnL set from a `sete` on the DevCaps bit.  There is no
	// Set_Software_Vertex_Processing on either side and no second query.
	BFME_DX8Caps_InitCapsFields *retail = (BFME_DX8Caps_InitCapsFields *)this;

	DX8CALL(GetDeviceCaps(&Caps));

	retail->supportTnL=((Caps.DevCaps&D3DDEVCAPS_HWTRANSFORMANDLIGHT)==D3DDEVCAPS_HWTRANSFORMANDLIGHT);
}

// ----------------------------------------------------------------------------
//
// Compute the caps bits
//
// ----------------------------------------------------------------------------
// ?Compute_Caps@DX8Caps@@QAEXW4WW3DFormat@@ABU_D3DADAPTER_IDENTIFIER8@@@Z present-unmatched
void DX8Caps::Compute_Caps(WW3DFormat display_format, const D3DADAPTER_IDENTIFIER8& adapter_id)
{
//	Init_Caps(D3DDevice);

	CanDoMultiPass=true;
	IsFogAllowed=true;

	CapsLog="";
	CompactLog="";
	DXLOG(("Video Card: %s\r\n",adapter_id.Description));
	DXLOG(("Driver: %s\r\n",adapter_id.Driver));

	DriverDLL=adapter_id.Driver;
	int Product = HIWORD(adapter_id.DriverVersion.HighPart);
	int Version = LOWORD(adapter_id.DriverVersion.HighPart);
	int SubVersion = HIWORD(adapter_id.DriverVersion.LowPart);
	DriverBuildVersion = LOWORD(adapter_id.DriverVersion.LowPart);

	DXLOG(("Product=%d, Version=%d, SubVersion=%d, Build=%d\r\n",Product, Version, SubVersion, DriverBuildVersion));

	VendorId=Define_Vendor(adapter_id.VendorId);
	// Make a guess - if driver doesn't intruduce itself and the name starts with 3, what could it possibly be?
	if (VendorId==VENDOR_UNKNOWN) {
		if (DriverDLL[0]=='3') VendorId=VENDOR_3DFX;
	}
	COMPACTLOG(("%s\t",VendorNames[VendorId]));
	DXLOG(("Video Card Chip Vendor: %s\r\n",VendorNames[VendorId]));
	DXLOG(("Type of chip: "));
	switch (VendorId) {
	default:
	case VENDOR_UNKNOWN:
		DeviceId=0;
		DXLOG(("Unknown"));
		COMPACTLOG(("Unknown"));
		break;
	case VENDOR_NVIDIA:
		DeviceId=(unsigned)Get_NVidia_Device(adapter_id.DeviceId);
		DXLOG((DeviceNamesNVidia[DeviceId]));
		COMPACTLOG((DeviceNamesNVidia[DeviceId]));
		break;
	case VENDOR_ATI:
		DeviceId=(unsigned)Get_ATI_Device(adapter_id.DeviceId);
		DXLOG((DeviceNamesATI[DeviceId]));
		COMPACTLOG((DeviceNamesATI[DeviceId]));
		break;
	case VENDOR_INTEL:
		DeviceId=(unsigned)Get_Intel_Device(adapter_id.DeviceId);
		DXLOG((DeviceNamesIntel[DeviceId]));
		COMPACTLOG((DeviceNamesIntel[DeviceId]));
		break;
	case VENDOR_S3:
		DeviceId=(unsigned)Get_S3_Device(adapter_id.DeviceId);
		DXLOG((DeviceNamesS3[DeviceId]));
		COMPACTLOG((DeviceNamesS3[DeviceId]));
		break;
	case VENDOR_POWERVR:
		DeviceId=(unsigned)Get_PowerVR_Device(adapter_id.DeviceId);
		DXLOG((DeviceNamesPowerVR[DeviceId]));
		COMPACTLOG((DeviceNamesPowerVR[DeviceId]));
		break;
	case VENDOR_MATROX:
		DeviceId=(unsigned)Get_Matrox_Device(adapter_id.DeviceId);
		DXLOG((DeviceNamesMatrox[DeviceId]));
		COMPACTLOG((DeviceNamesMatrox[DeviceId]));
		break;
	case VENDOR_3DFX:
		DeviceId=(unsigned)Get_3Dfx_Device(adapter_id.DeviceId);
		DXLOG((DeviceNames3Dfx[DeviceId]));
		COMPACTLOG((DeviceNames3Dfx[DeviceId]));
		break;
	case VENDOR_3DLABS:
		DeviceId=(unsigned)Get_3DLabs_Device(adapter_id.DeviceId);
		DXLOG((DeviceNames3DLabs[DeviceId]));
		COMPACTLOG((DeviceNames3DLabs[DeviceId]));
		break;
	}

	COMPACTLOG(("\t%d\t",DriverBuildVersion));

	DXLOG(("\r\n"));

	DXLOG(("Vendor id: 0x%x\r\n",adapter_id.VendorId));
	DXLOG(("Device id: 0x%x\r\n",adapter_id.DeviceId));
	DXLOG(("SubSys id: 0x%x\r\n",adapter_id.SubSysId));
	DXLOG(("Revision: %d\r\n",adapter_id.Revision));

	DXLOG(("GUID = {0x%x, 0x%x, 0x%x}, {0x%2.2x, 0x%2.2x, 0x%2.2x, 0x%2.2x, 0x%2.2x, 0x%2.2x, 0x%2.2x, 0x%2.2x}\r\n",
		adapter_id.DeviceIdentifier.Data1,
		adapter_id.DeviceIdentifier.Data2,
		adapter_id.DeviceIdentifier.Data3,
		adapter_id.DeviceIdentifier.Data4[0],
		adapter_id.DeviceIdentifier.Data4[1],
		adapter_id.DeviceIdentifier.Data4[2],
		adapter_id.DeviceIdentifier.Data4[3],
		adapter_id.DeviceIdentifier.Data4[4],
		adapter_id.DeviceIdentifier.Data4[5],
		adapter_id.DeviceIdentifier.Data4[6],
		adapter_id.DeviceIdentifier.Data4[7]));


	SupportPointSprites = (Caps.MaxPointSize > 1.0f);
	SupportNPatches = ((Caps.DevCaps&D3DDEVCAPS_NPATCHES)==D3DDEVCAPS_NPATCHES);
	SupportZBias = ((Caps.RasterCaps&D3DPRASTERCAPS_ZBIAS)==D3DPRASTERCAPS_ZBIAS);
	supportGamma=((Caps.Caps2&D3DCAPS2_FULLSCREENGAMMA)==D3DCAPS2_FULLSCREENGAMMA);
	SupportModAlphaAddClr = (Caps.TextureOpCaps & D3DTEXOPCAPS_MODULATEALPHA_ADDCOLOR) == D3DTEXOPCAPS_MODULATEALPHA_ADDCOLOR;
	SupportDot3=(Caps.TextureOpCaps & D3DTEXOPCAPS_DOTPRODUCT3) == D3DTEXOPCAPS_DOTPRODUCT3;
	SupportCubemaps=(Caps.TextureCaps & D3DPTEXTURECAPS_CUBEMAP) == D3DPTEXTURECAPS_CUBEMAP;
	SupportAnisotropicFiltering=
		(Caps.TextureFilterCaps&D3DPTFILTERCAPS_MAGFANISOTROPIC) && (Caps.TextureFilterCaps&D3DPTFILTERCAPS_MINFANISOTROPIC);

	DXLOG(("Hardware T&L support: %s\r\n",SupportTnL ? "Yes" : "No"));
	DXLOG(("NPatch support: %s\r\n",SupportNPatches ? "Yes" : "No"));
	DXLOG(("ZBias support: %s\r\n",SupportZBias ? "Yes" : "No"));
	DXLOG(("Gamma support: %s\r\n",supportGamma ? "Yes" : "No"));
	DXLOG(("ModAlphaAddClr support: %s\r\n",SupportModAlphaAddClr ? "Yes" : "No"));
	DXLOG(("Dot3 support: %s\r\n",SupportDot3 ? "Yes" : "No"));
	DXLOG(("Anisotropic filtering support: %s\r\n",SupportAnisotropicFiltering ? "Yes" : "No"));

	Check_Texture_Format_Support(display_format,Caps);
	Check_Render_To_Texture_Support(display_format,Caps);
	Check_Depth_Stencil_Support(display_format,Caps);
	Check_Texture_Compression_Support(Caps);
	Check_Bumpmap_Support(Caps);
	Check_Shader_Support(Caps);
	Check_Driver_Version_Status();
	Check_Maximum_Texture_Support(Caps);

	MaxTexturesPerPass=Caps.MaxSimultaneousTextures;

	DXLOG(("Max textures per pass: %d\r\n",MaxTexturesPerPass));

	Vendor_Specific_Hacks(adapter_id);
	CapsWorkString="";
}

// ----------------------------------------------------------------------------
//
// Check bump map texture support
//
// ----------------------------------------------------------------------------

// Same overlay trick as BFME_DX8Caps_CheckShaderFields below: BFME's DX8Caps is
// laid out differently from Zero Hour's and reconciling the whole class is a
// separate job, so the two members this function touches are reached at retail's
// offsets. SupportBumpEnvmap sits at 0x13c where our class puts it at 0xe0, and
// CapsLog at 0x2dc where ours has 0x14c.  The earlier note here claimed the
// shader overlay's matching 0x2a4 was corroboration; it was not -- both were
// the same guess and both were wrong by 56 bytes.  0x2dc is read straight out
// of retail's `lea edi,[esi+2DCh]`.
struct BFME_DX8Caps_CheckBumpmapFields
{
	char pad[0x13c];
	bool supportBumpEnvmap;					// 0x13c
	bool supportBumpEnvmapLuminance;		// 0x13d
	// capsLog is at 0x2DC, not 0x2A4: retail's Check_Bumpmap_Support takes its
	// address with `lea edi,[esi+2DCh]`, and that literal was the only thing
	// separating this body from its 150 bytes.
	char padAfterFlags[0x2dc - 0x13e];
	StringClass capsLog;					// 0x2dc
};

// ?Check_Bumpmap_Support@DX8Caps@@AAEXABU_D3DCAPS8@@@Z
void DX8Caps::Check_Bumpmap_Support(const D3DCAPS8& caps)
{
	BFME_DX8Caps_CheckBumpmapFields *retail = (BFME_DX8Caps_CheckBumpmapFields *)this;
	retail->supportBumpEnvmap=!!(caps.TextureOpCaps & D3DTEXOPCAPS_BUMPENVMAP);
	retail->supportBumpEnvmapLuminance=!!(caps.TextureOpCaps & D3DTEXOPCAPS_BUMPENVMAPLUMINANCE);
	CapsWorkString.Format("Bumpmap support: %s\r\n",retail->supportBumpEnvmap ? "Yes" : "No");
	retail->capsLog+=CapsWorkString;
	CapsWorkString.Format("Bumpmap luminance support: %s\r\n",retail->supportBumpEnvmapLuminance ? "Yes" : "No");
	retail->capsLog+=CapsWorkString;
}

// ----------------------------------------------------------------------------
//
// Check compressed texture support
//
// ----------------------------------------------------------------------------

// ?Check_Texture_Compression_Support@DX8Caps@@AAEXABU_D3DCAPS8@@@Z present-unmatched
// Third overlay.  The three "zero the table" bodies at 0x0012B210, 0x0012B2A0
// and 0x0012B3A0 give the whole table region away without any guessing: they
// `rep stos` 123 bytes at this+13Eh, 118 at this+1B9h and 118 at this+22Fh, and
// 13E+123 = 1B9, 1B9+118 = 22F, 22F+118 = 2A5.  Three consecutive arrays, and
// the five DXT flags Check_Texture_Compression_Support reads at 1B4h..1B8h are
// the last five bytes of the first one.
//
// So BFME's format table starts where ours does, at 0x13E -- an earlier note
// here deduced 0x1A0 by assuming DXT1 was still index 20, and that was wrong.
// It is index 118, and Check_Texture_Format_Support at 0x0012B210 says why.
// That body loops i from 0 to 123 and computes the D3DFORMAT to query as
//
//     mov ecx,31545690h / sub ecx,ebp        ... add ecx,edi
//
// where edi is this+13Eh+i, so the format is 31545690h + 13Eh + i.  At i=118
// that is 31545844h, which is 'DXT1'.  For i below 118 it passes i unchanged.
// BFME's WW3DFormat is therefore the D3DFORMAT enumeration itself for 0..117
// with the five DXT FourCCs appended at 118..122 -- 123 values where Zero
// Hour's WW3DFormat has 26.  Naming them is a separate job, so the five flags
// this body actually touches are reached by offset instead.
//
// The other two tables follow from the same three bodies:
//   0x13E  SupportTextureFormat[123]
//   0x1B9  SupportRenderToTextureFormat[118]
//   0x22F  SupportDepthStencilFormat[118]
//   0x2D8  Direct3D          (read as [ebp+2D8h] by all three)
struct BFME_DX8Caps_CompressionFields
{
	char pad[0x139];
	bool supportDXTC;						// 0x139
	char padToDXT[0x1b4 - 0x13a];
	bool supportDXT1;						// 0x1b4
	bool supportDXT2;						// 0x1b5
	bool supportDXT3;						// 0x1b6
	bool supportDXT4;						// 0x1b7
	bool supportDXT5;						// 0x1b8
	char padToLog[0x2dc - 0x1b9];
	StringClass capsLog;					// 0x2dc
};

void DX8Caps::Check_Texture_Compression_Support(const D3DCAPS8& caps)
{
	BFME_DX8Caps_CompressionFields *retail = (BFME_DX8Caps_CompressionFields *)this;
	retail->supportDXTC=retail->supportDXT1|
		retail->supportDXT2|
		retail->supportDXT3|
		retail->supportDXT4|
		retail->supportDXT5;
	CapsWorkString.Format("Texture compression support: %s\r\n",retail->supportDXTC ? "Yes" : "No");
	retail->capsLog+=CapsWorkString;
}

// The mapping BFME uses for the five DXT slots is odd and it is reproduced
// here rather than tidied: retail computes the format as 31545690h + 13Eh + i,
// i.e. CONSECUTIVE integers from 31545844h ('DXT1') for i = 118..122, not the
// four separate FourCCs 'DXT1'..'DXT5'.  Whether that is a bug in BFME does not
// matter to the bytes; it is what the loop does.  Below 118 the index is passed
// straight through, which is the same identity the render-to-texture body uses.
struct BFME_DX8Caps_TextureFormatFields
{
	char pad[0x13e];
	bool supportTextureFormat[123];			// 0x13e
	char padToD3D[0x2d8 - (0x13e + 123)];
	IDirect3D8 *direct3D;					// 0x2d8
};

void DX8Caps::Check_Texture_Format_Support(WW3DFormat display_format,const D3DCAPS8& caps)
{
	BFME_DX8Caps_TextureFormatFields *retail = (BFME_DX8Caps_TextureFormatFields *)this;
	if (display_format==WW3D_FORMAT_UNKNOWN) {
		for (unsigned i=0;i<123;++i) {
			retail->supportTextureFormat[i]=false;
		}
		return;
	}
	for (unsigned i=0;i<123;++i) {
		D3DFORMAT format=(i<118) ? (D3DFORMAT)i : (D3DFORMAT)(0x31545844u+(i-118));
		retail->supportTextureFormat[i]=SUCCEEDED(
			retail->direct3D->CheckDeviceFormat(
				caps.AdapterOrdinal,
				caps.DeviceType,
				(D3DFORMAT)display_format,
				0,
				D3DRTYPE_TEXTURE,
				format));
	}
}

// BFME's version is much smaller than Zero Hour's: it queries all 118
// D3DFORMAT values with no name lookup and no logging, and passes the index
// straight through as the format -- which is only meaningful because
// WW3DFormat IS D3DFORMAT here (see the note above the compression overlay).
// The empty arm is a rep-stos of the 118-byte table, and Direct3D is at 0x2D8.
struct BFME_DX8Caps_RenderToTextureFields
{
	char pad[0x1b9];
	bool supportRenderToTextureFormat[118];	// 0x1b9
	char padToD3D[0x2d8 - (0x1b9 + 118)];
	IDirect3D8 *direct3D;					// 0x2d8
};

void DX8Caps::Check_Render_To_Texture_Support(WW3DFormat display_format,const D3DCAPS8& caps)
{
	BFME_DX8Caps_RenderToTextureFields *retail = (BFME_DX8Caps_RenderToTextureFields *)this;
	if (display_format==WW3D_FORMAT_UNKNOWN) {
		for (unsigned i=0;i<118;++i) {
			retail->supportRenderToTextureFormat[i]=false;
		}
		return;
	}
	for (unsigned i=0;i<118;++i) {
		retail->supportRenderToTextureFormat[i]=SUCCEEDED(
			retail->direct3D->CheckDeviceFormat(
				caps.AdapterOrdinal,
				caps.DeviceType,
				(D3DFORMAT)display_format,
				D3DUSAGE_RENDERTARGET,
				D3DRTYPE_TEXTURE,
				(D3DFORMAT)i));
	}
}

//**********************************************************************************************
//! Check Depth Stencil Format Support
/*! KJM
*/
// ?Check_Depth_Stencil_Support@DX8Caps@@AAEXW4WW3DFormat@@ABU_D3DCAPS8@@@Z present-unmatched
// STILL SHORT OF EXACT, and only by register naming.  The structure, the
// switch range, both jump tables and all 146 bytes are right; retail keeps the
// loop counter in esi and indexes the byte table with it directly
// (`movzx ecx,[esi+52B3DEh]`) while our build recomputes i-70 into eax and
// indexes with that, and the whole call sequence is shifted one register
// across -- ecx/edx where we use edx/ecx.  That is the same allocator phase
// 0x00038790 and 0x0000D050 are stuck behind.  `int` instead of `unsigned` for
// the loop variable does not move it.
//
// BFME's depth-stencil table is indexed by the D3DFORMAT value itself, like
// the other two, so the loop runs 70..80 -- D3DFMT_D16_LOCKABLE through
// D3DFMT_D16 -- and skips the four values in that span that are not depth
// formats.  Retail does the skipping with a byte-index table and a jump table
// laid down after the epilogue, which is what a switch over a dense range
// compiles to; written as an if-chain it would be a compare cascade instead.
struct BFME_DX8Caps_DepthStencilFields
{
	char pad[0x22f];
	bool supportDepthStencilFormat[118];	// 0x22f
	char padToD3D[0x2d8 - (0x22f + 118)];
	IDirect3D8 *direct3D;					// 0x2d8
};

void DX8Caps::Check_Depth_Stencil_Support(WW3DFormat display_format, const D3DCAPS8& caps)
{
	BFME_DX8Caps_DepthStencilFields *retail = (BFME_DX8Caps_DepthStencilFields *)this;
	if (display_format==WW3D_FORMAT_UNKNOWN)
	{
		for (unsigned i=0;i<118;++i)
		{
			retail->supportDepthStencilFormat[i]=false;
		}
		return;
	}

	for (unsigned i=70;i<81;++i)
	{
		switch (i)
		{
		// 82 and 83 are D3DFMT_D32F_LOCKABLE and D3DFMT_D24FS8 -- D3D9-only
		// depth formats, and more corroboration that this renderer is D3D9.
		// They are past the loop bound so they never execute, but they are in
		// the switch: retail's range guard is `cmp eax,0Dh`, which is 70..83.
		case 70: case 71: case 73: case 75: case 77: case 79: case 80:
		case 82: case 83:
			retail->supportDepthStencilFormat[i]=SUCCEEDED(
				retail->direct3D->CheckDeviceFormat(
					caps.AdapterOrdinal,
					caps.DeviceType,
					(D3DFORMAT)display_format,
					D3DUSAGE_DEPTHSTENCIL,
					D3DRTYPE_SURFACE,
					(D3DFORMAT)i));
			break;
		default:
			break;
		}
	}
}

// 0x284 falls immediately after the two shader-version words the overlay below
// places at 0x27c and 0x280, which is the corroboration that these are one layout.
struct BFME_DX8Caps_MaxTextureField
{
	// 0x2BC, not the 0x284 this used to guess: retail's body is nineteen bytes
	// and the store is `mov [ecx+2BCh],edx`.  That also sits four past the
	// pixel shader version at 0x2B8, which is where the declaration order in
	// dx8caps.h puts MaxSimultaneousTextures.
	char pad[0x2bc];
	int maxSimultaneousTextures;			// 0x2bc
};

// ?Check_Maximum_Texture_Support@DX8Caps@@AAEXABU_D3DCAPS8@@@Z
void DX8Caps::Check_Maximum_Texture_Support(const D3DCAPS8& caps)
{
	BFME_DX8Caps_MaxTextureField *retail = (BFME_DX8Caps_MaxTextureField *)this;
	retail->maxSimultaneousTextures=caps.MaxSimultaneousTextures;
}

struct BFME_DX8Caps_CheckShaderFields
{
	// Working backwards from capsLog at 0x2DC through the tail of DX8Caps as
	// it is declared -- DriverDLL, Direct3D, CapsLog, CompactLog preceded by
	// eight ints -- puts MaxTexturesPerPass at 0x2B4 and the two shader
	// versions at 0x2B8 and 0x2BC.
	char pad[0x2b4];
	int vertexShaderVersion;				// 0x2b4
	int pixelShaderVersion;					// 0x2b8
	// All three offsets are read straight out of retail's Check_Shader_Support
	// at 0x0012B550: `mov [esi+2B4h],ecx` for the vertex version,
	// `mov [esi+2B8h],eax` for the pixel version, and `lea ecx,[esi+2DCh]` for
	// capsLog.  This overlay used to say 0x27C/0x280/0x2A4, and the bumpmap
	// overlay agreed on 0x2A4, and a comment called that agreement
	// corroboration -- it was not, both were the same guess.
	char padAfterVersions[0x2dc - 0x2bc];
	StringClass capsLog;					// 0x2dc
};

// ?Check_Shader_Support@DX8Caps@@AAEXABU_D3DCAPS8@@@Z
void DX8Caps::Check_Shader_Support(const D3DCAPS8& caps)
{
	BFME_DX8Caps_CheckShaderFields *retail = (BFME_DX8Caps_CheckShaderFields *)this;
	retail->vertexShaderVersion = caps.VertexShaderVersion;
	retail->pixelShaderVersion = caps.PixelShaderVersion;
	CapsWorkString.Format("Vertex shader version: %d.%d, pixel shader version: %d.%d\r\n",
		(retail->vertexShaderVersion>>8)&0xff,retail->vertexShaderVersion&0xff,
		(retail->pixelShaderVersion>>8)&0xff,retail->pixelShaderVersion&0xff);
	retail->capsLog += CapsWorkString;
}

// ?Check_Driver_Version_Status@DX8Caps@@AAEXXZ
// Body in DX8Caps_Check_Driver_Version_Status.asm (exact 713B retail).

bool DX8Caps::Is_Valid_Display_Format(int width, int height, WW3DFormat format)
{
	// If nothing limits the maximum resolution, accept any resolution
	if (MaxDisplayWidth==0 && MaxDisplayHeight==0) return true;

	if (width>MaxDisplayWidth || height>MaxDisplayHeight) return false;
	return true;
}

// ----------------------------------------------------------------------------
//
// Implement some vendor-specific hacks to fix certain driver bugs that can't be
// avoided otherwise.
//
// ----------------------------------------------------------------------------

// ?Vendor_Specific_Hacks@DX8Caps@@AAEXABU_D3DADAPTER_IDENTIFIER8@@@Z present-unmatched
// One overlay with everything this file has recovered about BFME's DX8Caps.
// Every offset is read out of a retail instruction, not derived:
//
//   0x000 MaxDisplayWidth / 0x004 MaxDisplayHeight
//   0x008 Caps (D3DCAPS9, 304 bytes)
//   0x138 SupportTnL   0x139 SupportDXTC   0x13B SupportNPatches
//   0x13C SupportBumpEnvmap / 0x13D ...Luminance
//   0x13E SupportTextureFormat[123]        (DXT1 is index 118)
//   0x1B9 SupportRenderToTextureFormat[118]
//   0x22F SupportDepthStencilFormat[118]
//   0x2A5 SupportZBias .. 0x2AB CanDoMultiPass, 0x2AC IsFogAllowed
//   0x2B0 MaxTexturesPerPass  0x2B4/0x2B8 shader versions
//   0x2BC MaxSimultaneousTextures          0x2C8 DeviceId
//   0x2CC DriverVersionStatus  0x2D0 VendorId  0x2D4 DriverDLL
//   0x2D8 Direct3D             0x2DC CapsLog   0x2E0 CompactLog
struct BFME_DX8Caps_All
{
	int maxDisplayWidth;					// 0x000
	int maxDisplayHeight;					// 0x004
	char padToFlags[0x138 - 0x008];
	bool supportTnL;						// 0x138
	bool supportDXTC;						// 0x139
	bool supportGamma;						// 0x13a
	bool supportNPatches;					// 0x13b
	bool supportBumpEnvmap;					// 0x13c
	bool supportBumpEnvmapLuminance;		// 0x13d
	bool supportTextureFormat[123];			// 0x13e
	bool supportRenderToTextureFormat[118];	// 0x1b9
	bool supportDepthStencilFormat[118];	// 0x22f
	bool supportZBias;						// 0x2a5
	bool supportAnisotropicFiltering;		// 0x2a6
	bool supportModAlphaAddClr;				// 0x2a7
	bool supportDot3;						// 0x2a8
	bool supportPointSprites;				// 0x2a9
	bool supportCubemaps;					// 0x2aa
	bool canDoMultiPass;					// 0x2ab
	bool isFogAllowed;						// 0x2ac
	char padToInts[0x2b0 - 0x2ad];
	int maxTexturesPerPass;					// 0x2b0
	int vertexShaderVersionAll;				// 0x2b4
	int pixelShaderVersionAll;				// 0x2b8
	int maxSimultaneousTexturesAll;			// 0x2bc
	int unknown2c0;							// 0x2c0
	int driverBuildVersion;					// 0x2c4
	unsigned deviceId;						// 0x2c8
	int driverVersionStatus;				// 0x2cc
	int vendorId;							// 0x2d0
	StringClass driverDLL;					// 0x2d4
	IDirect3D8 *direct3DAll;				// 0x2d8
	StringClass capsLogAll;					// 0x2dc
};

void DX8Caps::Vendor_Specific_Hacks(const D3DADAPTER_IDENTIFIER8& adapter_id)
{
	BFME_DX8Caps_All *retail = (BFME_DX8Caps_All *)this;
	if (retail->vendorId==VENDOR_NVIDIA) 
  {
		if (retail->supportNPatches) {
			DXLOG_RETAIL(("NVidia Driver reported N-Patch support, disabling.\r\n"));
		}
		if (retail->supportTextureFormat[118]) {
			DXLOG_RETAIL(("Disabling DXT1 support on NVidia hardware.\r\n"));
		}

		retail->supportNPatches = false;	// Driver incorrectly report N-Patch support
		retail->supportTextureFormat[118] = false;			// DXT1 is broken on NVidia hardware
		retail->supportDXTC=
			retail->supportTextureFormat[118]|
			retail->supportTextureFormat[119]|
			retail->supportTextureFormat[120]|
			retail->supportTextureFormat[121]|
			retail->supportTextureFormat[122];


    if (retail->deviceId == DEVICE_NVIDIA_GEFORCE2_MX ||
        retail->deviceId == DEVICE_NVIDIA_GEFORCE2_MX_400 )
    {
		  DXLOG_RETAIL(("Maximum screen resolution limited to 1024 x 768 on NVidia GeForce2 mx/mx400 cards\r\n"));			
		  retail->maxDisplayWidth=1024;
		  retail->maxDisplayHeight=768;
    }



	}

	if (retail->vendorId==VENDOR_MATROX) {
		// G400 and G550 claim support for ModAlphaAddClr but argument limitations make it unusable.
		if (retail->deviceId==DEVICE_MATROX_G400 ||
			retail->deviceId==DEVICE_MATROX_G550) {
			DXLOG_RETAIL(("ModAlphaAddClr disabled Matrox G400 and G550 cards (cannot put texture in 2nd arg)\r\n"));
			retail->supportModAlphaAddClr = false;
		}
	}

	if (retail->vendorId==VENDOR_ATI) {
		// Rage Pro doesn't handle multitexturing well enough...
		// It also doesn't really handle render-to-texture...
		if (retail->deviceId==DEVICE_ATI_RAGE_PRO || retail->deviceId==DEVICE_ATI_RAGE_PRO_MOBILITY) {
			DXLOG_RETAIL(("Disabling multitexturing on ATI Rage Pro\r\n"));			
			retail->maxTexturesPerPass=1;
			retail->canDoMultiPass=false;

			DXLOG_RETAIL(("Disabling render-to-texture on Rage Pro\r\n"));
			for (unsigned i=0;i<118;++i) {
				retail->supportRenderToTextureFormat[i]=false;
			}
		}

		// Rage 128 Pro GL is used in ATI Rage Fury Maxx
		// The driver support is bad and the card seems to suffer quite a bit from
		// lock-ups and rendering errors. These ease up when multitexturing and
		// render-to-texture are disabled.
		// However, E&B requires multitexturing, so renabling it.
		if (retail->deviceId==DEVICE_ATI_RAGE_128_PRO_GL) {
			retail->canDoMultiPass=false;

			DXLOG_RETAIL(("Disabling render-to-texture on ATI Rage 128 Pro GL\r\n"));
			for (unsigned i=0;i<118;++i) {
				retail->supportRenderToTextureFormat[i]=false;
			}

		}

		if (retail->deviceId==DEVICE_ATI_RAGE_128_MOBILITY ||
			retail->deviceId==DEVICE_ATI_RAGE_128_MOBILITY_M3 ||
			retail->deviceId==DEVICE_ATI_RAGE_128_MOBILITY_M4 ||
			retail->deviceId==DEVICE_ATI_RAGE_128_PRO_ULTRA ||
			retail->deviceId==DEVICE_ATI_RAGE_128_4X ||
			retail->deviceId==DEVICE_ATI_RAGE_128_PRO_GL ||
			retail->deviceId==DEVICE_ATI_RAGE_128_PRO_VR ||
			retail->deviceId==DEVICE_ATI_RAGE_128_GL ||
			retail->deviceId==DEVICE_ATI_RAGE_128_VR) {
			DXLOG_RETAIL(("Maximum screen resolution limited to 1280 x 1024 on ATI Rage 128 cards\r\n"));			
			retail->maxDisplayWidth=1280;
			retail->maxDisplayHeight=1024;
			DXLOG_RETAIL(("ModAlphaAddClr disabled ATI Rage 128 cards (cannot put texture in 2nd arg)\r\n"));
			retail->supportModAlphaAddClr = false;
		}

		if (retail->deviceId==DEVICE_ATI_MOBILITY_RADEON ||
			retail->deviceId==DEVICE_ATI_MOBILITY_RADEON_VE_M6 ||
			retail->deviceId==DEVICE_ATI_RADEON_VE ||
			retail->deviceId==DEVICE_ATI_RADEON_DDR ||
			retail->deviceId==DEVICE_ATI_RADEON ||
			retail->deviceId==DEVICE_ATI_MOBILITY_R7500 ||
			retail->deviceId==DEVICE_ATI_R7500) {
			DXLOG_RETAIL(("Disabling render-to-texture on Radeon\r\n"));
			for (unsigned i=0;i<118;++i) {
				retail->supportRenderToTextureFormat[i]=false;
			}
		}

		// CAT-lab reported that selecting anisotorpic filtering on Radeon VE causes a lock up after a while
		if (retail->deviceId==DEVICE_ATI_RADEON_VE) {
			DXLOG_RETAIL(("Disabling anisotropic filtering on Radeon VE\r\n"));
			retail->supportAnisotropicFiltering=false;
		}


	}

	if (retail->vendorId==VENDOR_3DFX) {
		// Voodoo2, Banshee and Voodoo3 don't handle multi-texturing with DX8 well enough.
		if (retail->deviceId==DEVICE_3DFX_VOODOO_3 ||
			retail->deviceId==DEVICE_3DFX_BANSHEE ||
			retail->deviceId==DEVICE_3DFX_VOODOO_2) {
			DXLOG_RETAIL(("Disabling multitexturing on Voodoo2/Voodoo3/Banshee\r\n"));			
			retail->maxTexturesPerPass=1;	// Especially important on Banshee (multitexturing crashes)!!!

			DXLOG_RETAIL(("Maximum screen resolution limited to 1280 x 1024 on Voodoo2/Voodoo3/Banshee\r\n"));			
			retail->maxDisplayWidth=1280;
			retail->maxDisplayHeight=1024;
		}

		if (retail->deviceId==DEVICE_3DFX_VOODOO_3) {
			DXLOG_RETAIL(("Disabling render-to-texture on Voodoo3\r\n"));
			for (unsigned i=0;i<118;++i) {
				retail->supportRenderToTextureFormat[i]=false;
			}
		}
	}

	if (retail->vendorId==VENDOR_POWERVR) {
		DXLOG_RETAIL(("Maximum screen resolution limited to 1280 x 1024 on PowerVR Kyro cards\r\n"));			
		retail->maxDisplayWidth=1280;
		retail->maxDisplayHeight=1024;

		// No fog on scene capture cards! (They don't like fog color changes in mid-frame)
		retail->isFogAllowed=false;
	}

	if (retail->vendorId==VENDOR_S3) {
		if (retail->deviceId==DEVICE_S3_SAVAGE_4) {
			DXLOG_RETAIL(("Maximum screen resolution limited to 1024 x 768 on S3 Savage 4 cards\r\n"));			
			retail->maxDisplayWidth=800;//1024;
			retail->maxDisplayHeight=600;//768;
		}

		if (retail->deviceId==DEVICE_S3_SAVAGE_200) {
			DXLOG_RETAIL(("Disabling multitexturing on S3 Savage 2000\r\n"));			
			retail->maxTexturesPerPass=1;
			retail->canDoMultiPass=false;
		}


	}
}
