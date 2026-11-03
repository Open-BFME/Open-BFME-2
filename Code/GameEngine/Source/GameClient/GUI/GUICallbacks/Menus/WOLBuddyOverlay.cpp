// cl: /Ireference/shims/zh_outofline /FIzh_ascii.h /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib
// platformsdk
// dxsdk
// stlport
// Ported verbatim from the Generals Zero Hour reference
// (GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLBuddyOverlay.cpp); this unit had no counterpart under Code/.
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
// FILE: WOLBuddyOverlay.cpp
// Author: Chris Huybregts, November 2001
// Description: Lan Lobby Menu
///////////////////////////////////////////////////////////////////////////////////////

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#define _STLP_BFME_RB_MINMAX_IMPORT  // inline _Rb_tree_node_base::_S_minimum/_S_maximum without a COMDAT copy (vendor/stlport/stl/_tree.h)
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine
#include <map>

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
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _List_iterator<T, LeftTraits>& a,
                              const _List_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

#include "Common/AudioEventRTS.h"
#include "Common/PlayerList.h"
#include "Common/Player.h"
#include "GameClient/GameText.h"
#include "GameClient/WindowLayout.h"
#include "GameClient/Gadget.h"
#include "GameClient/Shell.h"
#include "GameClient/KeyDefs.h"
#include "GameClient/GameWindowManager.h"
#include "GameClient/GadgetListBox.h"
#include "GameClient/GadgetPushButton.h"
#include "GameClient/GadgetStaticText.h"
#include "GameClient/GadgetTextEntry.h"
#include "GameClient/GadgetRadioButton.h"
#include "GameClient/Display.h"
#include "GameNetwork/GameSpyOverlay.h"
#include "GameNetwork/GameSpy/PeerDefs.h"
#include "GameNetwork/GameSpy/BuddyDefs.h"
#include "GameNetwork/GameSpy/BuddyThread.h"
#include "GameNetwork/GameSpy/LobbyUtils.h"
#include "GameNetwork/GameSpy/PersistentStorageDefs.h"
#include "GameNetwork/GameSpy/PersistentStorageThread.h"
#include "GameNetwork/GameSpy/ThreadUtils.h"
// bfme link decl-only begin
namespace _STL { template <> _Rb_tree<int, pair<int const, AsciiString>, _Select1st<pair<int const, AsciiString> >, less<int>, allocator<pair<int const, AsciiString> > >::~_Rb_tree(); }
namespace _STL { template <> _String_base<char, allocator<char> >::~_String_base(); }
namespace _STL { template <> _Rb_tree_node<pair<int const, AsciiString> > * _Rb_tree<int, pair<int const, AsciiString>, _Select1st<pair<int const, AsciiString> >, less<int>, allocator<pair<int const, AsciiString> > >::_M_clone_node(_Rb_tree_node<pair<int const, AsciiString> > *); }
namespace _STL { template <> _Rb_tree_node<pair<int const, AsciiString> > * _Rb_tree<int, pair<int const, AsciiString>, _Select1st<pair<int const, AsciiString> >, less<int>, allocator<pair<int const, AsciiString> > >::_M_create_node(pair<int const, AsciiString> const &); }
namespace _STL { template <> void _STLP_alloc_proxy<char *, char, allocator<char> >::deallocate(char *, unsigned int); }
// Suppress this TU's non-retail copy of ??0?$_Rb_tree_base@U?$pair@$$CBHVAsciiString@@@_STL@@V?$allocator@U?$pair@$$CBHVAsciiString@@@_STL@@@2@@_STL@@QAE@ABV?$al:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> _Rb_tree_base<pair<int const, AsciiString>, allocator<pair<int const, AsciiString> > >::_Rb_tree_base(allocator<pair<int const, AsciiString> > const &); }
// bfme link decl-only end

// Declaration-only: the rowed set<AsciiString> tree members are bound,
// this TU emits no per-flag copy of them or of their allocator leaves.
namespace _STL {
typedef _Rb_tree<AsciiString, AsciiString, _Identity<AsciiString>, less<AsciiString>, allocator<AsciiString> > Lk6AsciiSetTree;
template <> Lk6AsciiSetTree::~_Rb_tree();
template <> set<AsciiString, less<AsciiString>, allocator<AsciiString> >::set();
}

// Retail BFME 2 has no Zero Hour buddy overlay (its menus are Apt). This unit
// keeps only what is rowed here and what other units take from it: the
// SavedIgnoreMap and BuddyInfoMap tree members, BuddyInfo's and BuddyMessage's
// destructors (with their EH funclets) and WindowLayout::getFilename, which
// Shell and SidesList call. Taking their addresses keeps the copies.
typedef _STL::pair<const Int, AsciiString> SavedIgnorePair;
typedef _STL::_Rb_tree<Int, SavedIgnorePair, _STL::_Select1st<SavedIgnorePair>, _STL::less<Int>, _STL::allocator<SavedIgnorePair> > SavedIgnoreTree;
typedef BuddyInfoMap::value_type BuddyInfoPair;

SavedIgnoreTree &(SavedIgnoreTree::*_bfmeInlineAnchor_WOLBuddyOverlay_0)(const SavedIgnoreTree &) = &SavedIgnoreTree::operator=;
void (SavedIgnoreTree::*_bfmeInlineAnchor_WOLBuddyOverlay_1)(void) = &SavedIgnoreTree::clear;
BuddyInfoMap::iterator (BuddyInfoMap::*_bfmeInlineAnchor_WOLBuddyOverlay_2)(BuddyInfoMap::iterator, const BuddyInfoPair &) = &BuddyInfoMap::insert;
BuddyInfoMap::size_type (BuddyInfoMap::*_bfmeInlineAnchor_WOLBuddyOverlay_3)(const BuddyInfoMap::key_type &) = &BuddyInfoMap::erase;
void (*_bfmeInlineAnchor_WOLBuddyOverlay_4)(BuddyMessage *) = &_STL::_Destroy;
AsciiString (WindowLayout::*_bfmeInlineAnchor_WOLBuddyOverlay_5)(void) = &WindowLayout::getFilename;
