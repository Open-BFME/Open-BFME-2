// cl: /G7 /arch:SSE /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// SPDX-License-Identifier: GPL-3.0-or-later
// BFME2 DX8Caps constructors, reconstructed from the retail control flow and
// the EA reference class. The legacy names refer to a D3D9 device/caps layout.
// Keep all 304 capability bytes in one POD member: the caps-copy constructor
// emits one 76-dword copy before constructing its three StringClass members.
// A D3DCAPS8 member followed by loose tail padding cannot reproduce that copy.
// The shared EH handler, FuncInfo, three-entry unwind map and all three member
// cleanup funclets were independently verified, including the actual CRT import.

// stlport
#define Matrix4x4 Matrix4
#define DX8Caps BFME1_DX8Caps
#include "always.h"
#include "dx8caps.h"
#include "dx8wrapper.h"
#undef DX8Caps
struct BFME_D3DCAPS9Storage { D3DCAPS8 prefix; char extended[304-sizeof(D3DCAPS8)]; };
class DX8Caps
{
	int maxDisplayWidth;					// 0x000
	int maxDisplayHeight;					// 0x004
	BFME_D3DCAPS9Storage caps;
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
	bool supportDynamicTextures;
	char padToInts[0x2b0 - 0x2ae];
	int maxTexturesPerPass;					// 0x2b0
	int vertexShaderVersionAll;				// 0x2b4
	int pixelShaderVersionAll;				// 0x2b8
	int maxSimultaneousTexturesAll;			// 0x2bc
	unsigned mappedDevice;						// 0x2c0
	unsigned rawDevice;					// 0x2c4
	unsigned driverBuildVersion;						// 0x2c8
	int driverVersionStatus;				// 0x2cc
	int vendorId;							// 0x2d0
	StringClass driverDLL;					// 0x2d4
	IDirect3D8 *direct3DAll;				// 0x2d8
	StringClass capsLogAll;					// 0x2dc
	StringClass compactLogAll;
public:
 DX8Caps(IDirect3D8 *direct3d,IDirect3DDevice8 *device,WW3DFormat format,const D3DADAPTER_IDENTIFIER8 &adapter);
 DX8Caps(IDirect3D8 *,const D3DCAPS8 &,WW3DFormat,const D3DADAPTER_IDENTIFIER8 &);
 void Compute_Caps(WW3DFormat,const D3DADAPTER_IDENTIFIER8 &);
};

typedef char BFME_ConstructorCapsSize[(sizeof(DX8Caps)==0x2e4)?1:-1];

DX8Caps::DX8Caps(IDirect3D8 *direct3d,IDirect3DDevice8 *device,WW3DFormat format,const D3DADAPTER_IDENTIFIER8 &adapter)
 : maxDisplayWidth(0),maxDisplayHeight(0),rawDevice(0),direct3DAll(direct3d)
{
 DX8CALL(GetDeviceCaps(&caps.prefix));
 supportTnL=((caps.prefix.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)==D3DDEVCAPS_HWTRANSFORMANDLIGHT);
 Compute_Caps(format,adapter);
}

DX8Caps::DX8Caps(IDirect3D8 *direct3d,const D3DCAPS8 &sourceCaps,WW3DFormat format,const D3DADAPTER_IDENTIFIER8 &adapter)
 : maxDisplayWidth(0),maxDisplayHeight(0),caps((const BFME_D3DCAPS9Storage &)sourceCaps),rawDevice(0),direct3DAll(direct3d)
{
 supportTnL=((caps.prefix.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)==D3DDEVCAPS_HWTRANSFORMANDLIGHT);
 Compute_Caps(format,adapter);
}
