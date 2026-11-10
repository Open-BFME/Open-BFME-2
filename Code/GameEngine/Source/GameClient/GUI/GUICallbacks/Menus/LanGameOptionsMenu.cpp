// cl: /Ireference/shims/gameinfo /Ireference/shims/zh_outofline /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib
// stlport
// Ported verbatim from the Generals Zero Hour reference
// (GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/LanGameOptionsMenu.cpp); this unit had no counterpart under Code/.
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

///////////////////////////////////////////////////////////////////////////////////////
// FILE: LanGameOptionsMenu.cpp
// Author: Chris Huybregts, October 2001
// Description: Lan Game Options Menu
///////////////////////////////////////////////////////////////////////////////////////

#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine
#include <map>

// vector<int> fill/insert otherwise instantiates the _Construct<int,int>
// COMDAT (one byte shape per TU flags); a file-static overload takes those
// calls instead so this TU emits no external copy.
#include <new>
namespace _STL {
static inline void _Construct(int *__p, const int &__val)
{ new (__p) int(__val); }
}

// map/set<int> internals otherwise instantiate the less<int>::operator()
// COMDAT (one byte shape per TU flags); an explicit dllimport+forceinline
// specialization takes those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return a < b; }
}

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}


#include "Common/PlayerTemplate.h"
#include "Common/GameEngine.h"
#include "Common/UserPreferences.h"
#include "Common/QuotedPrintable.h"
#include "GameClient/AnimateWindowManager.h"
#include "GameClient/WindowLayout.h"
#include "GameClient/Gadget.h"
#include "GameClient/Shell.h"
#include "GameClient/KeyDefs.h"
#include "GameClient/GameWindowManager.h"
#include "GameClient/GadgetListBox.h"
#include "GameClient/GadgetComboBox.h"
#include "GameClient/GadgetTextEntry.h"
#include "GameClient/GadgetStaticText.h"
#include "GameClient/GadgetPushButton.h"
#include "GameClient/GadgetCheckbox.h"
#include "GameClient/MapUtil.h"
#include "GameClient/Mouse.h"
#include "GameClient/GameWindowTransitions.h"
#include "GameClient/ChallengeGenerals.h"
#include "GameNetwork/GameSpy/LobbyUtils.h"

#include "GameNetwork/FirewallHelper.h"
#include "GameNetwork/LANAPI.h"
#include "GameNetwork/IPEnumeration.h"
#include "GameNetwork/LANAPICallbacks.h"
#include "Common/MultiplayerSettings.h"
#include "GameClient/GameText.h"
#include "GameNetwork/GUIUtil.h"
// bfme link decl-only begin
namespace _STL { template <> pair<_Rb_tree_iterator<int, _Nonconst_traits<int> >, bool> _Rb_tree<int, int, _Identity<int>, less<int>, allocator<int> >::insert_unique(int const &); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ??1?$_Rb_tree@HHU?$_Identity@H@_STL@@U?$less@H@2@V?$allocator@H@2@@_STL@@QAE@XZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> _Rb_tree<int,int,_Identity<int>,less<int>,allocator<int> >::~_Rb_tree(); }

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

// Retail BFME 2 has no Zero Hour LAN game options menu (its menus are Apt). This
// unit keeps only its rows and the globals other units take from it.

// LANbuttonPushed: matched references place it at VA 0xe03364 (zero-filled .bss).
bool LANbuttonPushed;

// GameInfo.h's inline GameSlot::setTeamNumber, rowed here as the ICF-folded
// 0x002E6A93 (dup_002e6a93). Taking its address keeps the copy.
void (GameSlot::*_bfmeInlineAnchor_LanGameOptionsMenu_0)(Int) = &GameSlot::setTeamNumber;

void updateMapStartSpots( GameInfo *myGame, GameWindow *buttonMapStartPositions[], Bool onLoadScreen = FALSE );

// chatSystemColor: matched references place it at VA 0xdba760 (retail .data initial value -1).
extern const int chatSystemColor = -1;
// Its Zero Hour neighbours (LANAPICallbacks.cpp's chat color table, retail initial values
// GameMakeColor(255,0,255,255) and (128,255,255,255)), which LANAPI::OnChat reads at VA
// 0xdba754 and 0xdba75c.
extern const int chatActionColor = 0xFFFF00FF;
extern const int chatLocalActionColor = 0xFF80FFFF;
// The same table's accept colors (Zero Hour's GameMakeColor(0,255,0,255) and
// (255,0,0,255)), retail .data VA 0xdba764 and 0xdba768.
extern const int acceptTrueColor = 0xFF00FF00;
extern const int acceptFalseColor = 0xFFFF0000;

// ?rva0057DFFB@Rva0057DFFB@@QAE_N_N@Z @0x0057DFFB 65B
// Retail boundary 0x0057DFFB..0x0057E03B. thiscall taking one stack bool,
// bool result in AL. +0x1C selects path: 0 refreshes via updateMapStartSpots,
// 1 calls 0x0057DB97, other values return true. See reverse/attempts/0x0057dffb.cpp.
class Rva0043DA65
{
public:
	int rva0043DA65();
	int m_00; // +0x00
	int m_refs; // +0x04 +0x04, the reference count
	int m_08; // +0x08
};

#include "../../../../../Include/GameClient/AptMapPreview.h"
class Rva0057DFFB
{
public:
	bool rva0057DFFB(bool onLoadScreen);
	/* the rowed AptMapPreview::UpdateStrategicStartSpots */ __declspec(dllimport) __forceinline void rva0057DB97() { ((AptMapPreview *)this)->UpdateStrategicStartSpots(); }

private:
	unsigned char m_pad00[0x18];
	Rva0043DA65 *m_game;
	int m_mode;
	unsigned char m_pad20[0x30 - 0x20];
	GameWindow *m_buttons[8];
};

bool Rva0057DFFB::rva0057DFFB(bool onLoadScreen)
{
	switch (m_mode)
	{
	case 0:
	{
		GameInfo *game = (GameInfo *)m_game->rva0043DA65();
		if (!game)
			return false;
		if (!m_buttons[0])
			return false;
		updateMapStartSpots(game, m_buttons, onLoadScreen);
		break;
	}
	case 1:
		rva0057DB97();
		break;
	}
	return true;
}
