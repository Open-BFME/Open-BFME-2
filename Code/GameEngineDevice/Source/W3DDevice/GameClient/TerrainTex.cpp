// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
//
// Bodies ported from Open-BFME-1's
// GameEngineDevice/Source/W3DDevice/GameClient/TerrainTex.cpp (donor revision
// 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled
// that way each body below places uniquely on unclaimed game.dat .text by
// masked whole-.text search, and ./build.sh reproduces it byte for byte:
// TerrainTextureClass::setLOD 0x000EF2A0 (33B). Callee addresses are read off
// retail's call sites (reverse/symbols.csv). Only the placed bodies are
// carried; the donor's other definitions are omitted.
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

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////

// FILE: TerrainTex.cpp ////////////////////////////////////////////////
//-----------------------------------------------------------------------------
//                                                                          
//                       Westwood Studios Pacific.                          
//                                                                          
//                       Confidential Information                           
//                Copyright (C) 2001 - All Rights Reserved                  
//                                                                          
//-----------------------------------------------------------------------------
//
// Project:   RTS3
//
// File name: TerrainTex.cpp
//
// Created:   John Ahlquist, April 2001
//
// Desc:      TextureClass overrides to perform custom texturing for the terrain.
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//         Includes                                                      
//-----------------------------------------------------------------------------
#include <stdlib.h>

#include "W3DDevice/GameClient/TerrainTex.h"
#include "W3DDevice/GameClient/WorldHeightMap.h"
#include "W3DDevice/GameClient/TileData.h"
#include "common/GlobalData.h"
#include "WW3D2/dx8wrapper.h"
#include "d3dx8tex.h"


#if 0 // old version.

#endif

//=============================================================================
// TerrainTextureClass::setLOD
//=============================================================================
/** Sets the lod of the texture to be loaded into the video card.  */
//=============================================================================
void TerrainTextureClass::setLOD(Int LOD)
{
	if (Peek_D3D_Texture()) Peek_D3D_Texture()->SetLOD(LOD);
}


//=============================================================================
// AlphaTerrainTextureClass::Apply
//=============================================================================
/** Sets the texture as the current D3D texture, and does some custom setup.
This may be applied in either single pass, as the second texture in the pipe, 
or multipass.  If stage==0, we are doing multipass and we set up the pipe 
for a single texture.  If stage==1, then we are doing a single pass, and we
set up the pipe so that we blend onto the base texture in stage 0.
(standard D3D setup, but beyond the scope of W3D). */
//=============================================================================
#define ALPHA_DEVICE_SLOT(n) virtual void __stdcall slot##n(void);
struct Rva006D4FF0Device
{
	ALPHA_DEVICE_SLOT(0) ALPHA_DEVICE_SLOT(1) ALPHA_DEVICE_SLOT(2)
	ALPHA_DEVICE_SLOT(3) ALPHA_DEVICE_SLOT(4) ALPHA_DEVICE_SLOT(5)
	ALPHA_DEVICE_SLOT(6) ALPHA_DEVICE_SLOT(7) ALPHA_DEVICE_SLOT(8)
	ALPHA_DEVICE_SLOT(9) ALPHA_DEVICE_SLOT(10) ALPHA_DEVICE_SLOT(11)
	ALPHA_DEVICE_SLOT(12) ALPHA_DEVICE_SLOT(13) ALPHA_DEVICE_SLOT(14)
	ALPHA_DEVICE_SLOT(15) ALPHA_DEVICE_SLOT(16) ALPHA_DEVICE_SLOT(17)
	ALPHA_DEVICE_SLOT(18) ALPHA_DEVICE_SLOT(19) ALPHA_DEVICE_SLOT(20)
	ALPHA_DEVICE_SLOT(21) ALPHA_DEVICE_SLOT(22) ALPHA_DEVICE_SLOT(23)
	ALPHA_DEVICE_SLOT(24) ALPHA_DEVICE_SLOT(25) ALPHA_DEVICE_SLOT(26)
	ALPHA_DEVICE_SLOT(27) ALPHA_DEVICE_SLOT(28) ALPHA_DEVICE_SLOT(29)
	ALPHA_DEVICE_SLOT(30) ALPHA_DEVICE_SLOT(31) ALPHA_DEVICE_SLOT(32)
	ALPHA_DEVICE_SLOT(33) ALPHA_DEVICE_SLOT(34) ALPHA_DEVICE_SLOT(35)
	ALPHA_DEVICE_SLOT(36) ALPHA_DEVICE_SLOT(37) ALPHA_DEVICE_SLOT(38)
	ALPHA_DEVICE_SLOT(39) ALPHA_DEVICE_SLOT(40) ALPHA_DEVICE_SLOT(41)
	ALPHA_DEVICE_SLOT(42) ALPHA_DEVICE_SLOT(43) ALPHA_DEVICE_SLOT(44)
	ALPHA_DEVICE_SLOT(45) ALPHA_DEVICE_SLOT(46) ALPHA_DEVICE_SLOT(47)
	ALPHA_DEVICE_SLOT(48) ALPHA_DEVICE_SLOT(49) ALPHA_DEVICE_SLOT(50)
	ALPHA_DEVICE_SLOT(51) ALPHA_DEVICE_SLOT(52) ALPHA_DEVICE_SLOT(53)
	ALPHA_DEVICE_SLOT(54) ALPHA_DEVICE_SLOT(55) ALPHA_DEVICE_SLOT(56)
	ALPHA_DEVICE_SLOT(57) ALPHA_DEVICE_SLOT(58) ALPHA_DEVICE_SLOT(59)
	ALPHA_DEVICE_SLOT(60) ALPHA_DEVICE_SLOT(61) ALPHA_DEVICE_SLOT(62)
	ALPHA_DEVICE_SLOT(63) ALPHA_DEVICE_SLOT(64) ALPHA_DEVICE_SLOT(65)
	ALPHA_DEVICE_SLOT(66) ALPHA_DEVICE_SLOT(67) ALPHA_DEVICE_SLOT(68)
	virtual long __stdcall SetTextureStageState(unsigned int stage,
		unsigned int state, unsigned int value);
};
#undef ALPHA_DEVICE_SLOT

extern unsigned int Rva01340594DX8Calls;
extern unsigned int Rva01340568StageChanges;

struct Rva006C9270Texture
{
	virtual void __stdcall QueryInterface(void);
	virtual void __stdcall AddRef(void);
	virtual void __stdcall Release(void);
};

struct Rva006C9270Device
{
#define ALPHA_TEXTURE_DEVICE_SLOT(n) virtual void __stdcall slot##n(void);
	ALPHA_TEXTURE_DEVICE_SLOT(0) ALPHA_TEXTURE_DEVICE_SLOT(1)
	ALPHA_TEXTURE_DEVICE_SLOT(2) ALPHA_TEXTURE_DEVICE_SLOT(3)
	ALPHA_TEXTURE_DEVICE_SLOT(4) ALPHA_TEXTURE_DEVICE_SLOT(5)
	ALPHA_TEXTURE_DEVICE_SLOT(6) ALPHA_TEXTURE_DEVICE_SLOT(7)
	ALPHA_TEXTURE_DEVICE_SLOT(8) ALPHA_TEXTURE_DEVICE_SLOT(9)
	ALPHA_TEXTURE_DEVICE_SLOT(10) ALPHA_TEXTURE_DEVICE_SLOT(11)
	ALPHA_TEXTURE_DEVICE_SLOT(12) ALPHA_TEXTURE_DEVICE_SLOT(13)
	ALPHA_TEXTURE_DEVICE_SLOT(14) ALPHA_TEXTURE_DEVICE_SLOT(15)
	ALPHA_TEXTURE_DEVICE_SLOT(16) ALPHA_TEXTURE_DEVICE_SLOT(17)
	ALPHA_TEXTURE_DEVICE_SLOT(18) ALPHA_TEXTURE_DEVICE_SLOT(19)
	ALPHA_TEXTURE_DEVICE_SLOT(20) ALPHA_TEXTURE_DEVICE_SLOT(21)
	ALPHA_TEXTURE_DEVICE_SLOT(22) ALPHA_TEXTURE_DEVICE_SLOT(23)
	ALPHA_TEXTURE_DEVICE_SLOT(24) ALPHA_TEXTURE_DEVICE_SLOT(25)
	ALPHA_TEXTURE_DEVICE_SLOT(26) ALPHA_TEXTURE_DEVICE_SLOT(27)
	ALPHA_TEXTURE_DEVICE_SLOT(28) ALPHA_TEXTURE_DEVICE_SLOT(29)
	ALPHA_TEXTURE_DEVICE_SLOT(30) ALPHA_TEXTURE_DEVICE_SLOT(31)
	ALPHA_TEXTURE_DEVICE_SLOT(32) ALPHA_TEXTURE_DEVICE_SLOT(33)
	ALPHA_TEXTURE_DEVICE_SLOT(34) ALPHA_TEXTURE_DEVICE_SLOT(35)
	ALPHA_TEXTURE_DEVICE_SLOT(36) ALPHA_TEXTURE_DEVICE_SLOT(37)
	ALPHA_TEXTURE_DEVICE_SLOT(38) ALPHA_TEXTURE_DEVICE_SLOT(39)
	ALPHA_TEXTURE_DEVICE_SLOT(40) ALPHA_TEXTURE_DEVICE_SLOT(41)
	ALPHA_TEXTURE_DEVICE_SLOT(42) ALPHA_TEXTURE_DEVICE_SLOT(43)
	ALPHA_TEXTURE_DEVICE_SLOT(44) ALPHA_TEXTURE_DEVICE_SLOT(45)
	ALPHA_TEXTURE_DEVICE_SLOT(46) ALPHA_TEXTURE_DEVICE_SLOT(47)
	ALPHA_TEXTURE_DEVICE_SLOT(48) ALPHA_TEXTURE_DEVICE_SLOT(49)
	ALPHA_TEXTURE_DEVICE_SLOT(50) ALPHA_TEXTURE_DEVICE_SLOT(51)
	ALPHA_TEXTURE_DEVICE_SLOT(52) ALPHA_TEXTURE_DEVICE_SLOT(53)
	ALPHA_TEXTURE_DEVICE_SLOT(54) ALPHA_TEXTURE_DEVICE_SLOT(55)
	ALPHA_TEXTURE_DEVICE_SLOT(56) ALPHA_TEXTURE_DEVICE_SLOT(57)
	ALPHA_TEXTURE_DEVICE_SLOT(58) ALPHA_TEXTURE_DEVICE_SLOT(59)
	ALPHA_TEXTURE_DEVICE_SLOT(60) ALPHA_TEXTURE_DEVICE_SLOT(61)
	ALPHA_TEXTURE_DEVICE_SLOT(62) ALPHA_TEXTURE_DEVICE_SLOT(63)
	ALPHA_TEXTURE_DEVICE_SLOT(64)
#undef ALPHA_TEXTURE_DEVICE_SLOT
	virtual long __stdcall SetTexture(unsigned int stage,
		Rva006C9270Texture *texture);
};

extern Rva006C9270Texture *Rva0133F478Textures[];
extern unsigned int Rva01340560TextureChanges;


extern void __stdcall Rva0090C610Invoke(void *argument);
extern void __cdecl Rva006D4690Apply(void *argument);


#define STRETCH_FACTOR ((float)(1/(63.0*MAP_XY_FACTOR/2))) /* covers 63/2 tiles */		


