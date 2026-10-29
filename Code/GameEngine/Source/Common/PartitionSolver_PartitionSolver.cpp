// cl: /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /G7 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib
// stlport46
// Split from PartitionSolver.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
// Ported verbatim from the Generals Zero Hour reference
// (GameEngine/Source/Common/PartitionSolver.cpp); this unit had no counterpart under Code/.
// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it. Retail links one
// copy, the /O1 body at 0x00001423; this unemitted anchor makes this unit's
// copy that same body, so it no longer loses to retail's at link time.
// It can also change how later array constructions here compile; checked to
// change nothing else in this unit, but if a function added later that builds
// an array will not match, try it without this block.
// Retail keeps one unsigned max, RVA 0x00013740 (the vendored STLport row). This unit's
// flags (/G7 /arch:SSE) compile a different copy, and retail kept another unit's. This unit-local
// overload keeps the inlined code and offers the link no second copy.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

struct BfmeVciAnchorElem { BfmeVciAnchorElem(); };
#pragma optimize("gsy", on)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
#pragma optimize("", on)
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

// FILE: PartitionSolver.cpp //////////////////////////////////////////////////////////////////////
/*---------------------------------------------------------------------------*/
/* EA Pacific                                                                */
/* Confidential Information	                                                 */
/* Copyright (C) 2001 - All Rights Reserved                                  */
/* DO NOT DISTRIBUTE                                                         */
/*---------------------------------------------------------------------------*/
/* Project:    RTS3                                                          */
/* File name:  PartitionSolver.cpp                                           */
/* Created:    John K. McDonald, Jr., 4/2/2002                               */
/* Desc:       This contains a general-purpose Partition solver							 */
/* Revision History:                                                         */
/*		4/12/2002 : Initial creation                                           */
/*---------------------------------------------------------------------------*/
/**************************************************************************************************
Some info about partioning problems:

	This problem is contained in a very interesting class of problems known as NP complete. The 
	basic problem is that there is no way to tell whether you have an optimal solution or not. 
	Worst case, you try out every possible solution and still don't find the optimal solution: 
	this takes 2^n time to find, where N is the number of elements you are attempting to place.
	For this reason, a value near PREFER_FAST_SOLUTION should almost always be chosen. We will use
	a flat multiply to determine how many solutions to attempt before giving up and returning our 
	best attempt. If you want more info, this site contains info on the problem:
	http://odysseus.nat.uni-magdeburg.de/~mertens/npp/index.shtml
**************************************************************************************************/

#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/PartitionSolver.h"
// Suppress this TU's non-retail copy of ??0?$_Vector_base@U?$pair@W4ObjectID@@I@_STL@@V?$allocator@U?$pair@W4ObjectID@@I@_STL@@@2@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
enum ObjectID;
namespace _STL { template <> _Vector_base<pair<ObjectID,unsigned int>,allocator<pair<ObjectID,unsigned int> > >::_Vector_base(unsigned int,allocator<pair<ObjectID,unsigned int> > const &); }
// Suppress this TU's non-retail copy of ??$make_pair@W4ObjectID@@W41@@_STL@@YA?AU?$pair@W4ObjectID@@W41@@0@ABW4ObjectID@@0@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
enum ObjectID;
namespace _STL { template <> pair<ObjectID,ObjectID> make_pair<ObjectID,ObjectID>(ObjectID const &,ObjectID const &); }

// Retail's shared __lg<int> is rowed at 0x78C9C. The /G7 /arch:SSE
// body emitted here differs; call the verified provider without a local copy.
namespace _STL { template <> int __lg<int>(int); }

// Both native assignment calls use the rowed trivial 8-byte vector provider
// at 0x001D9BEE. Keep its established element name at the call boundary.
struct BfmePod8 { int a[2]; };
namespace _STL {
template <> vector<BfmePod8, allocator<BfmePod8> > &
vector<BfmePod8, allocator<BfmePod8> >::operator=(const vector<BfmePod8, allocator<BfmePod8> > &);
}
typedef _STL::vector<BfmePod8, _STL::allocator<BfmePod8> > RetailPartitionEntries;

static Bool greater_than(PairObjectIDAndUInt a, PairObjectIDAndUInt b)
{
	return a.second > b.second;
}

#pragma optimize("s", on)
PartitionSolver::PartitionSolver(const EntriesVec& elements, const SpacesVec& spaces, SolutionType solveHow)
{
	reinterpret_cast<RetailPartitionEntries &>(m_data) = reinterpret_cast<const RetailPartitionEntries &>(elements);
	reinterpret_cast<RetailPartitionEntries &>(m_spacesForData) = reinterpret_cast<const RetailPartitionEntries &>(spaces);
	m_howToSolve = solveHow;
	//Added By Sadullah Nader
	//Initializations inserted
	m_currentSolutionLeftovers = 0;
	//
}
#pragma optimize("", on)



// Keep the independently rowed template providers under their original flags.
template _STL::_Vector_base<PairObjectIDAndUInt,_STL::allocator<PairObjectIDAndUInt> >::_Vector_base(size_t,const _STL::allocator<PairObjectIDAndUInt>&);
template _STL::pair<ObjectID,ObjectID> _STL::make_pair<ObjectID,ObjectID>(const ObjectID&,const ObjectID&);
