// cl: /O1 /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/game/GameEngine/Include/Precompiled /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath
// stlport
//
// Bodies ported from Open-BFME-1's
// GameEngine/Source/Common/discrete_circle.cpp (donor revision
// 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled
// that way each body below places uniquely on unclaimed game.dat .text by
// masked whole-.text search, and ./build.sh reproduces it byte for byte:
// DiscreteCircle::generateEdgePairs 0x002DF8CF (110B),
// DiscreteCircle::DiscreteCircle 0x002DF93D (96B), DiscreteCircle::drawCircle
// 0x002DF82C (70B), DiscreteCircle::removeDuplicates 0x002DF872 (41B). Callee
// addresses are read off retail's call sites (reverse/symbols.csv). Only the
// placed bodies are carried; the donor's other definitions are omitted.
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
template <> inline const unsigned int &max<unsigned int>(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
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

// FILE: DiscreteCircle.cpp ////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
//                                                                          
//                       EA Pacific.                          
//                                                                          
//                       Confidential Information                           
//                Copyright (C) 2002 - All Rights Reserved                  
//                                                                          
//-----------------------------------------------------------------------------
//
// Project:   RTS3
//
// File name: DiscreteCircle.cpp
//
// Created:   John McDonald, September 2002
//
// Desc:      ???
//
//-----------------------------------------------------------------------------

#include "prerts.h"
#include "coord.h"
#include "../../../../reference/open-bfme-1/game/GameEngine/Source/Common/discrete_circle.h"

//-------------------------------------------------------------------------------------------------
DiscreteCircle::DiscreteCircle(Int xCenter, Int yCenter, Int radius)
{
	m_yPos = yCenter;
	m_yPosDoubled = (yCenter << 1);
	m_edges.reserve(radius << 1);	// largest that it should ever be.

	generateEdgePairs(xCenter, yCenter, radius);
	removeDuplicates();
}

//-------------------------------------------------------------------------------------------------
void DiscreteCircle::drawCircle(ScanlineDrawFunc functionToDrawWith, void *parmToPass)
{
	for (VecHorzLine::const_iterator it = m_edges.begin(); it != m_edges.end(); ++it) {
		(functionToDrawWith)(it->xStart, it->xEnd, it->yPos, parmToPass);
		if (it->yPos != m_yPos) {
			(functionToDrawWith)(it->xStart, it->xEnd, m_yPosDoubled - it->yPos, parmToPass);
		}
	}
}

//-------------------------------------------------------------------------------------------------
void DiscreteCircle::generateEdgePairs(Int xCenter, Int yCenter, Int radius)
{
	// Uses Bresenham to generate points.
	Int x = 0;
	Int y = radius;
	Int d = (1 - radius) << 1;

	while (y >= 0) {
		HorzLine hl;
		hl.xStart = xCenter - x;
		hl.xEnd		= xCenter + x;
		hl.yPos		= yCenter + y;
		m_edges.push_back(hl);
		
		if (d + y > 0) {
			--y;
			d -= ((y << 1) - 1);
		} 

		if (x > d) {
			++x;
			d += ((x << 1) + 1);
		}
	}
}

//-------------------------------------------------------------------------------------------------
void DiscreteCircle::removeDuplicates()
{
	VecHorzLineIt it, nextIt;
	for ( it = m_edges.begin(); it != m_edges.end(); /* empty */) {
		nextIt = it;
		++nextIt;
		if (nextIt == m_edges.end()) {
			break;
		}

		if (it->yPos == nextIt->yPos) {
			it = m_edges.erase(it);
		} else { 
			++it;
		}
	}
}