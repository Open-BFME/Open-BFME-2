// Verbatim copy of reference/shims/update_modules_bfme2/Common/DisabledTypes.h for the FlammableUpdate TU (changes marked "BFME 2:").
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

// FILE: DisabledTypes.h //////////////////////////////////////////////////////////////////////////
// Author: Kris Morness, September 2002
// Desc:  Defines all the types of disabled statii any given object can have.
///////////////////////////////////////////////////////////////////////////////////////////////////	

#pragma once

#ifndef __DISABLED_TYPES_H_
#define __DISABLED_TYPES_H_

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include "Lib/BaseType.h"
#include "Common/BitFlags.h"
#include "Common/BitFlagsIO.h"

//-------------------------------------------------------------------------------------------------
/** Kind of flags for determining groups of things that belong together
	* NOTE: You *MUST* keep this in the same order as the DisabledNames[] below */
//-------------------------------------------------------------------------------------------------
enum DisabledType
{
	DISABLED_HELD = 3,
	DISABLED_SCRIPT_DISABLED = 9,
	DISABLED_SCRIPT_UNDERPOWERED = 10,
	DISABLED_COUNT = 11,
	DISABLED_ANY = 65535
};

typedef BitFlags<DISABLED_COUNT>	DisabledMaskType;

#define MAKE_DISABLED_MASK(k) DisabledMaskType(DisabledMaskType::kInit, (k))
#define MAKE_DISABLED_MASK2(k,a) DisabledMaskType(DisabledMaskType::kInit, (k), (a))
#define MAKE_DISABLED_MASK3(k,a,b) DisabledMaskType(DisabledMaskType::kInit, (k), (a), (b))
#define MAKE_DISABLED_MASK4(k,a,b,c) DisabledMaskType(DisabledMaskType::kInit, (k), (a), (b), (c))
#define MAKE_DISABLED_MASK5(k,a,b,c,d) DisabledMaskType(DisabledMaskType::kInit, (k), (a), (b), (c), (d))

inline Bool TEST_DISABLEDMASK(const DisabledMaskType& m, DisabledType t) 
{ 
	return m.test(t); 
}

inline Bool TEST_DISABLEDMASK_ANY(const DisabledMaskType& m, const DisabledMaskType& mask) 
{ 
	return m.anyIntersectionWith(mask);
}

inline Bool TEST_DISABLEDMASK_MULTI(const DisabledMaskType& m, const DisabledMaskType& mustBeSet, const DisabledMaskType& mustBeClear)
{
	return m.testSetAndClear(mustBeSet, mustBeClear);
}

inline Bool DISABLEDMASK_ANY_SET(const DisabledMaskType& m) 
{ 
	return m.any(); 
}

inline void CLEAR_DISABLEDMASK(DisabledMaskType& m) 
{ 
	m.clear(); 
}

inline void SET_ALL_DISABLEDMASK_BITS(DisabledMaskType& m)
{
	m.clear();
	m.flip();
}

inline void FLIP_DISABLEDMASK(DisabledMaskType& m)
{
	m.flip();
}



// defined in Common/System/DisabledTypes.cpp
extern DisabledMaskType DISABLEDMASK_NONE;	// inits to all zeroes
extern DisabledMaskType DISABLEDMASK_ALL;		// inits to all bits set.
void initDisabledMasks();

#endif	// __DISABLED_TYPES_H_

