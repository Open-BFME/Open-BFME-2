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

// FILE: Smudge.h /////////////////////////////////////////////////////////

#pragma once

#ifndef _SMUDGE_H_
#define _SMUDGE_H_

// BFME2 native SmudgeSet20hex, Smudge8Chex; node/list geometry verified by matched owners.
#include "../../../../reference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath/wwmath.h"
#include "../../../../reference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2/dllist.h"
#include "../../../../reference/shims/wwmath/Vector2.h"
#include "../../../../reference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath/vector3.h"


struct Smudge : public DLNodeClass<Smudge>
{
	// BFME2 does not pool-allocate Smudge: native SmudgeManager destructor2D29F7
	// frees one with a plain single-argument operator delete where the pool
	// glue would route through getClassMemoryPool and freeFromW3DMemPool.

	Vector3 m_pos;	//position of smudge center
	Vector2 m_offset; // difference in position between "texture" extraction and re-insertion for center vertex
	float m_size;		//size of smudge in world space.
	float m_opacity;	//alpha of center vertex, corners are assumed at 0

	struct smudgeVertex
	{	Vector3 pos;	//world-space position of vertex
		Vector2 uv;	//uv coordinates of vertex
	};
	smudgeVertex m_verts[5];	//5 vertices of this smudge (in counter-clockwise order, starting at top-left, ending in center.)
};

struct SmudgeSet : public DLNodeClass<SmudgeSet>
{
	// BFME2 does not pool-allocate SmudgeSet: native addSmudgeSet2D291B
	// takes one from a plain single-argument operator new where the glue would
	// route through getClassMemoryPool and allocateFromW3DMemPool.

public:

	friend class SmudgeManager;

	SmudgeSet( void );
	virtual ~SmudgeSet();
	void reset(void);

	Smudge *addSmudgeToSet(void);
	void removeSmudgeFromSet ( Smudge &mySmudge);
	DLListClass<Smudge> &getUsedSmudgeList( void ) { return m_usedSmudgeList;}
	int getUsedSmudgeCount(void) { return m_usedSmudgeCount; }	///<active smudges that need rendering.

private:
	DLListClass<Smudge> m_usedSmudgeList;	///<list of smudges in this set.
	static DLListClass<Smudge> m_freeSmudgeList;	///<list of unused smudges for use by SmudgeSets.
	int m_usedSmudgeCount;
};

class SmudgeManager;

extern SmudgeManager *TheSmudgeManager;	///<singleton

#endif	//_SMUDGE_H_