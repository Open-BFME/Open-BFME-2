// cl: /O1 /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/inputs/reference/shims/asciistringsetoutofline /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
//
// Bodies ported from Open-BFME-1's
// GameEngine/Source/Common/System/SubsystemInterface.cpp (donor revision
// 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled
// that way each body below places uniquely on unclaimed game.dat .text by
// masked whole-.text search, and ./build.sh reproduces it byte for byte:
// SubsystemInterfaceList::postProcessLoadAll 0x001B4E49 (26B). Callee
// addresses are read off retail's call sites (reverse/symbols.csv). Only the
// placed bodies are carried; the donor's other definitions are omitted.
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

// FILE: SubsystemInterface.cpp 
// ----------------------------------------------------------------------------
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/SubsystemInterface.h"
#include "Common/Xfer.h"

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

#ifdef DUMP_PERF_STATS
#include "GameLogic/GameLogic.h"
#include "Common/PerfTimer.h"

Real SubsystemInterface::s_msConsumed = 0;
#endif

// SubsystemInterface::SubsystemInterface is not carried: retail's base ctor
// (0x001B4E63) is a different body, and this unit's donor copy was kept by
// the link over it.

#ifdef DUMP_PERF_STATS
static const Real MIN_TIME_THRESHOLD = 0.0002f;


#endif


// BFME's subsystem list holds eight-byte subsystem/slot PAIRS where the vendored
// header has a plain vector<SubsystemInterface*>, and reset is at vtable +0x10
// rather than +0x0C. The walk is otherwise the reverse iteration the reference
// spells, including re-reading m_begin on every iteration.
class BfmeSubsystemInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void reset() = 0;					///< vtable +0x10
};

struct BfmeSubsystemEntry
{
	BfmeSubsystemInterface *m_subsystem;
	void *m_slot;
};

struct BfmeSubsystemList
{
	BfmeSubsystemEntry *m_begin;
	BfmeSubsystemEntry *m_end;
	BfmeSubsystemEntry *m_capacity;
};

//-----------------------------------------------------------------------------
void SubsystemInterfaceList::postProcessLoadAll()
{
	BfmeSubsystemList *self = (BfmeSubsystemList *)this;

	for (BfmeSubsystemEntry *it = self->m_begin; it != self->m_end; ++it)
	{
		it->m_subsystem->slot0C();
	}
}


#ifdef DUMP_PERF_STATS

#endif
