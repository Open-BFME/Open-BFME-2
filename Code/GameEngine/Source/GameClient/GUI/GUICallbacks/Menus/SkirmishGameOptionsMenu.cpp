// cl: /Ireference/shims/gameinfo /Ireference/shims/zh_outofline /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib
// stlport
// Ported verbatim from the Generals Zero Hour reference
// (GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/SkirmishGameOptionsMenu.cpp); this unit had no counterpart under Code/.
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
// FILE: SkirmishGameOptionsMenu.cpp
// Author: Chris Brue, August 2002
// Description: Lan Game Options Menu
///////////////////////////////////////////////////////////////////////////////////////

// Retail BFME 2 has no Zero Hour skirmish options menu (its menus are Apt).
// This unit keeps only what its rows and other units take from it: the
// skirmish GameInfo pointer, the tech/supply image list global (ctor
// 0x003015E7 with its EH funclet) and the two header inlines rowed here.

#define _STLP_BFME_RB_MINMAX_IMPORT  // inline _Rb_tree_node_base::_S_minimum/_S_maximum without a COMDAT copy (vendor/stlport/stl/_tree.h)
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine
#include <map>

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


#include "Common/BattleHonors.h"
#include "Common/FileSystem.h"
#include "Common/GameEngine.h"
#include "Common/PlayerTemplate.h"
#include "Common/QuotedPrintable.h"
#include "Common/RandomValue.h"
#include "Common/SkirmishBattleHonors.h"
#include "Common/SkirmishPreferences.h"
#include "GameLogic/GameLogic.h"
#include "GameClient/AnimateWindowManager.h"
#include "GameClient/WindowLayout.h"
#include "GameClient/Gadget.h"
#include "GameClient/Shell.h"
#include "GameClient/ShellHooks.h"
#include "GameClient/KeyDefs.h"
#include "GameClient/GameWindowManager.h"
#include "GameClient/GadgetListBox.h"
#include "GameClient/GadgetCheckBox.h"
#include "GameClient/GadgetComboBox.h"
#include "GameClient/GadgetTextEntry.h"
#include "GameClient/GadgetPushButton.h"
#include "GameClient/GadgetSlider.h"
#include "GameClient/GadgetStaticText.h"
#include "GameClient/MapUtil.h"
#include "GameClient/Mouse.h"
#include "GameClient/GameWindowTransitions.h"
#include "GameNetwork/GameSpy/LobbyUtils.h"

#include "Common/MultiplayerSettings.h"
#include "GameClient/GameText.h"
#include "GameClient/CDCheck.h"
#include "GameClient/ExtendedMessageBox.h"
#include "GameClient/MessageBox.h"
#include "GameNetwork/GameInfo.h"
#include "GameNetwork/GUIUtil.h"
#include "GameNetwork/IPEnumeration.h"
#include "WWDownload/Registry.h"
#include "../../../../../../../reference/shims/bfme_coord3d_construct_link/coord3d_construct_link.h"
// bfme link decl-only begin
template <> int max<int>(int, int);
template <> int min<int>(int, int);
namespace _STL { template <> _Rb_tree_base<pair<AsciiString const, Coord3D>, allocator<pair<AsciiString const, Coord3D> > >::_Rb_tree_base(allocator<pair<AsciiString const, Coord3D> > const &); }
namespace _STL { template <> _String_base<char, allocator<char> >::_String_base(allocator<char> const &); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> >::basic_string(char const *, allocator<char> const &); }
namespace _STL { template <> _Rb_tree<AsciiString, pair<AsciiString const, Coord3D>, _Select1st<pair<AsciiString const, Coord3D> >, less<AsciiString>, allocator<pair<AsciiString const, Coord3D> > >::~_Rb_tree(); }
namespace _STL { template <> _String_base<char, allocator<char> >::~_String_base(); }
namespace _STL { template <> AsciiString & map<AsciiString, AsciiString, less<AsciiString>, allocator<pair<AsciiString const, AsciiString> > >::operator[](AsciiString const &); }
namespace _STL { template <> _Rb_tree_node<pair<AsciiString const, Coord3D> > * _Rb_tree<AsciiString, pair<AsciiString const, Coord3D>, _Select1st<pair<AsciiString const, Coord3D> >, less<AsciiString>, allocator<pair<AsciiString const, Coord3D> > >::_M_create_node(pair<AsciiString const, Coord3D> const &); }
namespace _STL { template <> _Rb_tree_node<pair<AsciiString const, Coord3D> > * allocator<_Rb_tree_node<pair<AsciiString const, Coord3D> > >::allocate(unsigned int, void const *) const; }
namespace _STL { template <> void _STLP_alloc_proxy<char *, char, allocator<char> >::deallocate(char *, unsigned int); }
namespace _STL { template <> _List_iterator<Coord3D, _Nonconst_traits<Coord3D> > list<Coord3D, allocator<Coord3D> >::insert(_List_iterator<Coord3D, _Nonconst_traits<Coord3D> >, Coord3D const &); }
namespace _STL { template <> pair<_Rb_tree_iterator<pair<AsciiString const, AsciiString>, _Nonconst_traits<pair<AsciiString const, AsciiString> > >, bool> _Rb_tree<AsciiString, pair<AsciiString const, AsciiString>, _Select1st<pair<AsciiString const, AsciiString> >, less<AsciiString>, allocator<pair<AsciiString const, AsciiString> > >::insert_unique(pair<AsciiString const, AsciiString> const &); }
// bfme link decl-only end

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

SkirmishGameInfo *TheSkirmishGameInfo = NULL;

// MapUtil.h's tech and supply start images; retail .data VA 0x00DFF14C.
TechAndSupplyImages TheSupplyAndTechImageLocations;

// Header inlines rowed to this unit: GadgetSliderGetPosition 0x00518246 and
// WindowLayout::runInit 0x0040FD7C. Taking their addresses keeps the copies.
Int (*_bfmeInlineAnchor_SkirmishGameOptionsMenu_0)(GameWindow *) = &GadgetSliderGetPosition;
void (WindowLayout::*_bfmeInlineAnchor_SkirmishGameOptionsMenu_1)(void *) = &WindowLayout::runInit;
