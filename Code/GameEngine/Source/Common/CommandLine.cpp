// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
//
// Bodies ported from Open-BFME-1's GameEngine/Source/Common/CommandLine.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus
// /O1). Compiled that way each body below places uniquely on unclaimed
// game.dat .text by masked whole-.text search, and ./build.sh reproduces it
// byte for byte: parseFPUPreserve 0x003B959D (30B). Callee addresses are read
// off retail's call sites (reverse/symbols.csv). Only the placed bodies are
// carried; the donor's other definitions are omitted.
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

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////


#include "PreRTS.h"	// This must go first in EVERY cpp file in the GameEngine

#include "Common/ArchiveFileSystem.h"
#include "Common/CommandLine.h"
#include "Common/CRCDebug.h"
#include "Common/LocalFileSystem.h"
#include "Common/Version.h"
#include "GameClient/TerrainVisual.h" // for TERRAIN_LOD_MIN definition
#include "GameClient/GameText.h"

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif


extern Bool TheDebugIgnoreSyncErrors;
extern Int DX8Wrapper_PreserveFPU;

#ifdef DEBUG_CRC
Int TheCRCFirstFrameToLog = -1;
UnsignedInt TheCRCLastFrameToLog = 0xffffffff;
Bool g_keepCRCSaves = FALSE;
Bool g_crcModuleDataFromLogic = FALSE;
Bool g_crcModuleDataFromClient = FALSE;
Bool g_verifyClientCRC = FALSE; // verify that GameLogic CRC doesn't change from client
Bool g_clientDeepCRC = FALSE;
Bool g_logObjectCRCs = FALSE;
#endif

#if defined(_DEBUG) || defined(_INTERNAL)
extern Bool g_useStringFile;
#endif

// Retval is number of cmd-line args eaten
typedef Int (*FuncPtr)( char *args[], int num );

static const UnsignedByte F_NOCASE = 1; // Case-insensitive

struct CommandLineParam
{
	const char *name;
	FuncPtr func;
};


//=============================================================================
//=============================================================================
// parseWin (retail 0x000609C0, table entry "-win") is defined in
// T3CommandLineParsers.cpp: retail's m_windowed is +0x29, not this header's +0x20.
Int parseWin(char *args[], int);


//=============================================================================
//=============================================================================
Int parseFPUPreserve(char *args[], int argc)
{
	if (argc > 1)
	{
		DX8Wrapper_PreserveFPU = atoi(args[1]);
	}
	return 2;
}

#if defined(_DEBUG) || defined(_INTERNAL)


#endif // _DEBUG || _INTERNAL

//=============================================================================
//=============================================================================
// parseNoAudio (retail 0x00060A60, table entry "-noaudio") is defined in
// T3CommandLineParsers.cpp: retail stores six audio bytes at +0xA6C..+0xA71.
Int parseNoAudio(char *args[], int);


// parseYRes (retail 0x00060C10, table entry "-yres") is defined in
// T3CommandLineParsers.cpp: retail's m_yResolution is +0x30.
Int parseYRes(char *args[], int num);

#if defined(_DEBUG) || defined(_INTERNAL)


#endif // defined(_DEBUG) || defined(_INTERNAL)


#if defined(_DEBUG) || defined(_INTERNAL) || defined(_ALLOW_DEBUG_CHEATS_IN_RELEASE)

#endif


#if defined(_DEBUG) || defined(_INTERNAL) 


/// end stuff for VTUNE

#endif // defined(_DEBUG) || defined(_INTERNAL)


#if defined(_DEBUG) || defined(_INTERNAL)

#endif


#if defined(_DEBUG) || defined(_INTERNAL)

#endif


// parseNoShellMap (retail 0x00060880, table entry "-noshellmap") is defined in
// T3CommandLineParsers.cpp: retail stores +0xBB4 = FALSE and +0xBB5 = TRUE.
Int parseNoShellMap(char *args[], int);


#if (defined(_DEBUG) || defined(_INTERNAL))

#endif


#if (defined(_DEBUG) || defined(_INTERNAL))

#endif


#if defined(_DEBUG) || defined(_INTERNAL)


#endif


// parseNetMinPlayers (retail 0x00060F40) is defined in T3CommandLineParsers.cpp:
// BFME1 WorldBuilder's full CommandLineParam table pairs "-netMinPlayers" with
// a body storing to GlobalData+0xB0C, not this header's +0x788.
Int parseNetMinPlayers(char *args[], int num);


#if defined(_DEBUG) || defined(_INTERNAL)

#endif

#if defined(_DEBUG) || defined(_INTERNAL)

#endif

#if defined(_DEBUG) || defined(_INTERNAL)

#endif

#if defined(_DEBUG) || defined(_INTERNAL)

#endif

#if defined(_DEBUG) || defined(_INTERNAL)

#endif

#if defined(_DEBUG) || defined(_INTERNAL)
#ifdef DUMP_PERF_STATS

#endif
#endif

#if defined(_DEBUG) || defined(_INTERNAL)

#endif

#if defined(_DEBUG) || defined(_INTERNAL)

#endif


// parseDumpAssetUsage (retail 0x00061050) is defined in T3CommandLineParsers.cpp:
// retail's m_dumpAssetUsage is +0x20, not this header's +0x15.
Int parseDumpAssetUsage(char *args[], int num);


// parseCommandLine is defined by the byte-matched retail reconstruction in
// ParseCommandLine.cpp.  The release parser above remains available as the
// source of the shared option handlers and their declarations.


