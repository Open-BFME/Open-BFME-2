// cl: /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /Ireference/shims/dockupdate /MD /O1 /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib /Ireference/shims/bfme_namekey /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/shims -ICode/Libraries/Source/Compression/LZHCompress/CompLibHeader /Ireference/shims/bfme2htree /Ireference/shims/bfme2renderobj /Ireference/shims/bfmecamera /Ireference/shims/bfmelight /Ireference/shims/bfmeparticlehandle /Ireference/shims/bfmeparticleload /Ireference/shims/bfmeparticlequat /Ireference/shims/bfmeparticlesave /Ireference/shims/bfmeparticleline /Ireference/shims/bfme2ray /Ireference/shims/bfme2scene -D_STLP_USE_STATIC_LIB -DNDEBUG -DWIN32 -D_WINDOWS /Ireference/shims/bfmefrustum
// stlport
// Ported verbatim from the Generals Zero Hour reference (GameEngine/Source/GameLogic/Object/Update/StealthUpdate.cpp); this unit had no counterpart under Code/.
// Only its two rows remain (StealthUpdate::isDisguised and Player::getPlayerNightColor,
// both header inlines kept emitted below). Retail's StealthUpdate bodies are rowed in
// StealthUpdateLogic.cpp, StealthUpdateXfer.cpp and their siblings; the unrowed Zero Hour
// destructor, receiveGrant, allowedToStealth, calcStealthOwner, changeVisualDisguise, crc
// and the isBlackMarket/setWakeupIfInRange callbacks matched no retail body and made 18
// references no object defines.
#define Matrix4x4 Matrix4  // BFME renamed it
#define __PLACEMENT_VEC_NEW_INLINE  // always.h/GameMemory.h define array placement-new themselves
// stlport
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

// FILE: StealthUpdate.cpp ////////////////////////////////////////////////////////////////////////
// Author: Kris Morness, May 2002
// Desc:	 An update that checks for a status bit to stealth the owning object
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _List_iterator<T, LeftTraits>& a,
                              const _List_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

#define DEFINE_STEALTHLEVEL_NAMES
#define DEFINE_OBJECT_STATUS_NAMES

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include "Common/GameState.h"
// Link view of StealthUpdate.h, ahead of Object.h's include of the shared header, so
// getStealthLevel binds to its retail row; WeaponSetType.h is the view's one prerequisite.
#include "GameLogic/WeaponSetType.h"
#include "../../../../../../reference/shims/bfme_stealth_level_link/StealthUpdate.h"
#include "Common/Player.h"
#include "Common/PlayerList.h"
#include "Common/Radar.h"
#include "Common/Team.h"
#include "Common/ThingTemplate.h"
#include "Common/ThingFactory.h"
#include "Common/Xfer.h"

#include "GameClient/ControlBar.h"
#include "GameClient/Drawable.h"
#include "GameClient/FXList.h"
#include "GameClient/GameClient.h"
#include "GameClient/Eva.h"

#include "GameLogic/Damage.h"
#include "GameLogic/Object.h"
#include "GameLogic/PartitionManager.h"
#include "GameLogic/Weapon.h"

#include "GameLogic/Module/AIUpdate.h"
#include "GameLogic/Module/StealthUpdate.h"
#include "GameLogic/Module/PhysicsUpdate.h"
#include "GameLogic/Module/ContainModule.h"
#include "GameLogic/Module/SpawnBehavior.h"
// Suppress this TU's non-retail copy of ?testForAll@?$BitFlags@$0CN@@@QBE_NABV1@@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class BitFlags;
template <> bool BitFlags<45>::testForAll(BitFlags<45> const &) const;
// Suppress this TU's non-retail copy of ?_M_do_and@?$_Base_bitset@$01@_STL@@QAEXABU12@@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void _Base_bitset<2>::_M_do_and(_Base_bitset<2> const &); }

// BFME 2's Object keeps its behavior list at +0x244 (the matched
// Object::findModule 0x0028B6D6 walks it there), its contain module at +0x250
// and its body module at +0x254; this tree's Zero Hour Object.h has +0x18C,
// +0x190 and +0x194. This unit reads them through these functions instead of
// the header's inline getters, whose Zero Hour copies would otherwise come
// early in link order and displace every BFME 2 unit's copy (retail has no
// out-of-line Object getter: the 7-byte bodies at 0x00313E8C/93/9A are
// GameWindow text-colour getters).
static BehaviorModule **getRetailBehaviorModules( const Object *obj ) { return *(BehaviorModule ** const *)((const char *)obj + 0x244); }
static ContainModuleInterface *getRetailContain( const Object *obj ) { return *(ContainModuleInterface * const *)((const char *)obj + 0x250); }
static BodyModuleInterface *getRetailBodyModule( const Object *obj ) { return *(BodyModuleInterface * const *)((const char *)obj + 0x254); }


#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

// StealthUpdateModuleData ctor/dtor/buildFieldParse live in their rowed units
// (StealthUpdateModuleDataCtor.cpp, StealthUpdateModuleDataDtor.cpp,
// ModuleDataBuildFieldParse.cpp); this file merely declares them via
// GameLogic/Module/StealthUpdate.h.
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// byte-exact reconstruction: Code/GameEngine/Source/GameLogic/Object/Update/StealthUpdate_ctor_Thunk.cpp
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// byte-exact reconstruction: Code/GameEngine/Source/Common/StealthUpdateDestructorThunk.cpp

//-------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------~-_-~-_-~-


//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// StealthUpdate::hintDetectableWhileUnstealthed (0x0037441E) is defined with its retail body in Rva0037441ELeaf.cpp.



//-------------------------------------------------------------------------------




//=============================================================================
// indicate how the given unit is "stealthed" with respect to a given player.

//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
/** The update callback. */
//-------------------------------------------------------------------------------------------------
// The exact update body is owned by StealthUpdateLogic.cpp.

//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// The exact disguise body is owned by StealthUpdateLogic.cpp.

// byte-exact reconstruction: Code/GameEngine/Source/GameLogic/Object/Update/StealthUpdateChangeVisualDisguiseThunk.cpp

// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
// StealthUpdate::xfer is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Update/StealthUpdateXfer.cpp (0x00374942).

// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------
// StealthUpdate::loadPostProcess is retail's row at 0x00374AE8 (StealthUpdateLoadPost.cpp);
// this unit only declares it, so its vtable binds there.
// Its Zero Hour body was the only caller of the rowed isDisguised, so keep that body emitted.
// ?bfmeAnchorStealthUpdateIsDisguised@@YA_NPBVStealthUpdate@@@Z absent-from-retail
Bool bfmeAnchorStealthUpdateIsDisguised(const StealthUpdate *s) { return s->isDisguised(); }

// The header inline Player::getPlayerNightColor (7-byte row 0x00509D29, no
// approved TU) was emitted here only through the dropped Zero Hour
// changeVisualDisguise. Taking its address keeps this unit's select-any copy
// emitted; this pointer is not retail data.
Int (Player::*_bfmeInlineAnchor_PlayerGetPlayerNightColor)() const = &Player::getPlayerNightColor;
