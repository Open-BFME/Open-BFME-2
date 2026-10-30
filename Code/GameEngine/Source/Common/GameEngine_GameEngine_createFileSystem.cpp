// cl: /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /Ireference/shims/bfmealloc /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/game/GameEngine/Source/Common
//
// Retail0x00042004 is the ghost-manager factory in table0x007C25E0 slot15.
// It allocates20 bytes and calls the verified W3DGhostObjectManager ctor63517.
// The old FileSystem donor placement agreed only after a false ctor pin.
// Keep the receiver address-derived: its complete target class ABI is not
// declared by the donor GameEngine view. No receiver fields are used here.
// stlport46
#define Matrix4x4 Matrix4  // BFME renamed it
// PIN STATUS 2026-09-06 -- python3 tools/pin_status.py game/GameEngine/Source/Common/GameEngine.cpp
// 4 of 12 definitions here carry a byte-verified `matched`
// targets/game/reverse/functions.csv row naming this source; 4 more are matched only
// from a split-out TU; 4 carry no ledger row at all.  Those 4 are unverified
// Zero Hour reference bodies and are not known to match BFME.  2 free functions
// are counted but not classified.  Check a body before porting behaviour off it.
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

// GameEngine.cpp /////////////////////////////////////////////////////////////////////////////////
// Implementation of the Game Engine singleton
// Author: Michael S. Booth, April 2001

#include "PreRTS.h"	// This must go first in EVERY cpp file in the GameEngine
#include <set>
// Declaration-only: the rowed set<AsciiString> ~_Rb_tree (0x589BE) is bound, this TU emits no copy.
namespace _STL {
typedef _Rb_tree<AsciiString, AsciiString, _Identity<AsciiString>, less<AsciiString>, allocator<AsciiString> > Lk6AsciiSetTree;
template <> Lk6AsciiSetTree::~_Rb_tree();
template <> set<AsciiString, less<AsciiString>, allocator<AsciiString> >::set();
}

#include "Common/ActionManager.h"
#include "Common/AudioAffect.h"
#include "Common/BuildAssistant.h"
#include "Common/CRCDebug.h"
#include "Common/Radar.h"
#include "Common/PlayerTemplate.h"
#include "Common/Team.h"
#include "Common/PlayerList.h"
#include "Common/GameAudio.h"
#include "Common/GameEngine.h"
#include "Common/INI.h"
#include "Common/INIException.h"
#include "Common/MessageStream.h"
#include "Common/ThingFactory.h"
#include "Common/File.h"
#include "Common/FileSystem.h"
#include "Common/ArchiveFileSystem.h"
#include "Common/LocalFileSystem.h"
#include "Common/CDManager.h"
#include "Common/GlobalData.h"
#include "Common/PerfTimer.h"
#include "Common/RandomValue.h"
#include "Common/NameKeyGenerator.h"
#include "Common/ModuleFactory.h"
#include "Common/Debug.h"
#include "Common/GameState.h"
#include "Common/GameStateMap.h"
#include "Common/Science.h"
#include "Common/FunctionLexicon.h"
#include "Common/CommandLine.h"
#include "Common/DamageFX.h"
#include "Common/MultiplayerSettings.h"
#include "Common/Recorder.h"
#include "Common/SpecialPower.h"
#include "Common/TerrainTypes.h"
#include "Common/Upgrade.h"
#include "Common/UserPreferences.h"
#include "Common/Xfer.h"
#include "Common/XferCRC.h"
#include "Common/GameLOD.h"
#include "Common/Registry.h"
#include "Common/GameCommon.h"	// FOR THE ALLOW_DEBUG_CHEATS_IN_RELEASE #define

#include "GameLogic/Armor.h"
#include "GameLogic/AI.h"
#include "GameLogic/CaveSystem.h"
#include "GameLogic/CrateSystem.h"
#include "GameLogic/Damage.h"
#include "GameLogic/VictoryConditions.h"
#include "GameLogic/ObjectCreationList.h"
#include "GameLogic/Weapon.h"
#include "GameLogic/GameLogic.h"
#include "GameLogic/Locomotor.h"
#include "GameLogic/RankInfo.h"
#include "GameLogic/ScriptEngine.h"
#include "GameLogic/SidesList.h"

#include "GameClient/Display.h"
#include "GameClient/FXList.h"
#include "GameClient/GameClient.h"
#include "GameClient/Keyboard.h"
#include "GameClient/Shell.h"
#include "GameClient/GameText.h"
#include "GameClient/ParticleSys.h"
#include "GameClient/Water.h"
#include "GameClient/TerrainRoads.h"
#include "GameClient/MetaEvent.h"
#include "GameClient/MapUtil.h"
#include "GameClient/GameWindowManager.h"
#include "GameClient/GlobalLanguage.h"
#include "GameClient/Drawable.h"
#include "GameClient/GUICallbacks.h"

#include "GameNetwork/NetworkInterface.h"
#include "GameNetwork/WOLBrowser/WebBrowser.h"
#include "GameNetwork/LANAPI.h"
#include "GameNetwork/GameSpy/GameResultsThread.h"

#include "Common/Version.h"
#include "W3DDevice/GameLogic/W3DGhostObject.h"

// Declaration-only: this TU's ZH MapMetaData view would emit a wrong ~MapMetaData
// (first in link order); bind node destruction to the copy another unit keeps.
namespace _STL { template <> void _Destroy(pair<const AsciiString, MapMetaData> *); }
// bfme link decl-only begin
namespace _STL { template <> _Rb_tree<AsciiString, pair<AsciiString const, Coord3D>, _Select1st<pair<AsciiString const, Coord3D> >, less<AsciiString>, allocator<pair<AsciiString const, Coord3D> > >::~_Rb_tree(); }
namespace _STL { template <> void _Rb_tree<AsciiString, pair<AsciiString const, Coord3D>, _Select1st<pair<AsciiString const, Coord3D> >, less<AsciiString>, allocator<pair<AsciiString const, Coord3D> > >::_M_erase(_Rb_tree_node<pair<AsciiString const, Coord3D> > *); }
namespace _STL { template <> _List_base<Coord3D, allocator<Coord3D> >::~_List_base(); }
namespace _STL { template <> void _List_base<Coord3D, allocator<Coord3D> >::clear(); }
// bfme link decl-only end

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

//-------------------------------------------------------------------------------------------------

#ifdef DEBUG_CRC
class DeepCRCSanityCheck : public SubsystemInterface
{
public:
	DeepCRCSanityCheck() {}
	virtual ~DeepCRCSanityCheck() {}

	virtual void init(void) {}
	virtual void reset(void);
	virtual void update(void) {}

protected:
};

DeepCRCSanityCheck *TheDeepCRCSanityCheck = NULL;

#endif // DEBUG_CRC

//-------------------------------------------------------------------------------------------------
/// The GameEngine singleton instance
extern GameEngine *TheGameEngine;

//-------------------------------------------------------------------------------------------------
extern SubsystemInterfaceList* TheSubsystemList;

//-------------------------------------------------------------------------------------------------
template<class SUBSYSTEM>
void initSubsystem(SUBSYSTEM*& sysref, AsciiString name, SUBSYSTEM* sys, Xfer *pXfer,  const char* path1 = NULL, 
									 const char* path2 = NULL, const char* dirpath = NULL)
{
	sysref = sys;
	TheSubsystemList->initSubsystem(sys, path1, path2, dirpath, pXfer, name);
}

//-------------------------------------------------------------------------------------------------
extern HINSTANCE ApplicationHInstance;  ///< our application instance

//-------------------------------------------------------------------------------------------------
static void updateTGAtoDDS();

//-------------------------------------------------------------------------------------------------
// byte-exact reconstruction: game/GameEngine/Source/Common/GameEngineDestructorThunk.cpp
// ??1GameEngine@@UAE@XZ is emitted by GameEngineDestructorThunk.cpp.

static __declspec(noinline) void gameEngineMapCacheDestructorAnchor(MapCache *cache)
{
	if (cache != NULL)
		delete cache;
}

static void (* volatile gameEngineMapCacheDestructorAnchorPtr)(MapCache *) =
	gameEngineMapCacheDestructorAnchor;

  // end init

// Horrible reference, but we really, really need to know if we are windowed.
extern bool DX8Wrapper_IsWindowed;
extern HWND ApplicationHWnd;

//-------------------------------------------------------------------------------------------------
class Rva00042004Factory
{
public:
    W3DGhostObjectManager *createGhostObjectManager();
};

W3DGhostObjectManager *Rva00042004Factory::createGhostObjectManager()
{
    return MSGNEW("GameEngineSubsystem") W3DGhostObjectManager;
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
#define CONVERT_EXEC1	"..\\Build\\nvdxt -list buildDDS.txt -dxt5 -full -outdir Art\\Textures > buildDDS.out"

//-------------------------------------------------------------------------------------------------
// System things

// If we're using the Wide character version of MessageBox, then there's no additional
// processing necessary. Please note that this is a sleazy way to get this information,
// but pending a better one, this'll have to do.
extern const Bool TheSystemIsUnicode;
