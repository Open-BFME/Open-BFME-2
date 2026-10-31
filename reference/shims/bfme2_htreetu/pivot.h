// Zero Hour's WW3D2/pivot.h, verbatim but for BFME 2's pivot (marked "BFME 2:"). Copied from
// reference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/pivot.h
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

/* $Header: /Commando/Code/ww3d2/pivot.h 1     1/22/01 3:36p Greg_h $ */
/*********************************************************************************************** 
 ***                            Confidential - Westwood Studios                              *** 
 *********************************************************************************************** 
 *                                                                                             * 
 *                 Project Name : Commando / G 3D Library                                      * 
 *                                                                                             * 
 *                     $Archive:: /Commando/Code/ww3d2/pivot.h                                $* 
 *                                                                                             * 
 *                       Author:: Greg_h                                                       * 
 *                                                                                             * 
 *                     $Modtime:: 1/08/01 10:04a                                              $* 
 *                                                                                             * 
 *                    $Revision:: 1                                                           $* 
 *                                                                                             * 
 *---------------------------------------------------------------------------------------------* 
 * Functions:                                                                                  * 
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#if defined(_MSC_VER)
#pragma once
#endif

#ifndef PIVOT_H
#define PIVOT_H

#include "always.h"
#include "vector3.h"
#include "matrix3d.h"
#include "quat.h"
#include "w3d_file.h"


/*

	PivotClass

	Each node of the hierarchy tree is represented by a 
	PivotClass.
	
*/

// BFME 2: ?Apply@NodeCompressedMotionStruct@@QAEXAAVCompactTransform@@MPAMMPAPAE@Z (0x00160240) names this
// class, and the pivot constructor 0x00197830 stores each block as a rotation (0,0,0,1) and a zero translation.
class CompactTransform
{
public:
	CompactTransform() {}
	// BFME 2: Simple_Evaluate_Pivot 0x001606E0 starts its accumulated transform from identity this way.
	explicit CompactTransform(bool init) : Q(init), Position(0.0f, 0.0f, 0.0f) {}
	// BFME 2: Init_Default 0x001666D0 inlines this on both blocks (its `add eax,0x14` and `add eax,0x30`).
	void Make_Identity()
	{
		Q.X = 0.0f; Q.Y = 0.0f; Q.Z = 0.0f; Q.W = 1.0f;
		Position.X = 0.0f; Position.Y = 0.0f; Position.Z = 0.0f;
	}
	Quaternion Q;
	Vector3 Position;
};

// BFME 2: 0x58 bytes by the constructor 0x00197830, the assignment 0x00197950 (??4PivotClass@@QAEAAU0@ABU0@@Z spells struct) and Scale's stride.
// No destructor: Load_W3D 0x00166800 reaches new[] with no cookie. Captured bones live in HTreeClass's +0x1C member.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/pivot.h
struct PivotClass
{
public:

	PivotClass(void);
	PivotClass(const PivotClass& that);
	PivotClass& operator=(const PivotClass& that);

public:
	char							Name[W3D_NAME_LEN];
	PivotClass *			Parent;
	CompactTransform		BaseTransform;		// base-pose transform (relative to parent); +0x14
	CompactTransform		Transform;				// computed transform for this pivot; +0x30
	int								Index;						// +0x4C
	bool							IsVisible;				// result of the visibility channel; +0x50
	float							PivotFade;				// set to 1.0f by Base_Update 0x001628A0; +0x54

};

typedef char BFME2PivotSizeMustBe88[(sizeof(PivotClass) == 0x58) ? 1 : -1];

#endif
