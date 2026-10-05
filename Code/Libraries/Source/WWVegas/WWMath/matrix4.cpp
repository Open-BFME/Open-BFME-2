// cl: /Ireference/shims/bfmerendobj /arch:SSE /G7 /DNDEBUG /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it. Retail links one
// copy, the /O1 body at 0x00001423; this unemitted anchor makes this unit's
// copy that same body, so it no longer loses to retail's at link time.
// It can also change how later array constructions here compile; checked to
// change nothing else in this unit, but if a function added later that builds
// an array will not match, try it without this block.
struct BfmeVciAnchorElem { BfmeVciAnchorElem(); };
#pragma optimize("gsy", on)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
#pragma optimize("", on)
/*
**	Command & Conquer Generals(tm)
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

/***********************************************************************************************
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : WWMath                                                       *
 *                                                                                             *
 *                     $Archive:: /Commando/Code/wwmath/matrix4.cpp                           $*
 *                                                                                             *
 *                       Author:: Greg_h                                                       *
 *                                                                                             *
 *                     $Modtime:: 11/13/99 10:50a                                             $*
 *                                                                                             *
 *                    $Revision:: 5                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 *   Matrix4::Multiply -- Multiply two Matrix4's together                                      *
 *   Matrix4::Multiply -- Multiply a Matrix3D * Matrix4                                        *
 *   Matrix4::Multiply -- Multiply a Matrix4 * Matrix3D                                        *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include "rendobj.h"	// the bfmerendobj shim has to win the include guard
#include "matrix4.h"
#include <assert.h>

/***********************************************************************************************
 * Matrix4::Multiply -- Multiply two Matrix4's together                                        *
 *                                                                                             *
 * INPUT:                                                                                      *
 *  a - first operand                                                                          *
 *  b - second operand                                                                         *
 *  res - pointer to matrix to store the result in (must not point to a or b)                  *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   11/13/99   gth : Created.                                                                 *
 *=============================================================================================*/
void Matrix4::Multiply(const Matrix4 &a,const Matrix4 &b,Matrix4 * res)
{
	assert(res != &a);
	assert(res != &b);

	#define ROWCOL(i,j) a[i][0]*b[0][j] + a[i][1]*b[1][j] + a[i][2]*b[2][j] + a[i][3]*b[3][j]

	(*res)[0][0] = ROWCOL(0,0);
	(*res)[0][1] = ROWCOL(0,1);
	(*res)[0][2] = ROWCOL(0,2);
	(*res)[0][3] = ROWCOL(0,3);

	(*res)[1][0] = ROWCOL(1,0);
	(*res)[1][1] = ROWCOL(1,1);
	(*res)[1][2] = ROWCOL(1,2);
	(*res)[1][3] = ROWCOL(1,3);

	(*res)[2][0] = ROWCOL(2,0);
	(*res)[2][1] = ROWCOL(2,1);
	(*res)[2][2] = ROWCOL(2,2);
	(*res)[2][3] = ROWCOL(2,3);

	(*res)[3][0] = ROWCOL(3,0);
	(*res)[3][1] = ROWCOL(3,1);
	(*res)[3][2] = ROWCOL(3,2);
	(*res)[3][3] = ROWCOL(3,3);

	#undef ROWCOL
}


/***********************************************************************************************
 * Matrix4::Multiply -- Multiply a Matrix3D * Matrix4                                          *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   11/13/99   gth : Created.                                                                 *
 *=============================================================================================*/
void Matrix4::Multiply(const Matrix3D &a,const Matrix4 &b,Matrix4 * res)
{
	assert(res != &b);

	#define ROWCOL(i,j) a[i][0]*b[0][j] + a[i][1]*b[1][j] + a[i][2]*b[2][j] + a[i][3]*b[3][j]

	(*res)[0][0] = ROWCOL(0,0);
	(*res)[0][1] = ROWCOL(0,1);
	(*res)[0][2] = ROWCOL(0,2);
	(*res)[0][3] = ROWCOL(0,3);

	(*res)[1][0] = ROWCOL(1,0);
	(*res)[1][1] = ROWCOL(1,1);
	(*res)[1][2] = ROWCOL(1,2);
	(*res)[1][3] = ROWCOL(1,3);

	(*res)[2][0] = ROWCOL(2,0);
	(*res)[2][1] = ROWCOL(2,1);
	(*res)[2][2] = ROWCOL(2,2);
	(*res)[2][3] = ROWCOL(2,3);

	(*res)[3][0] = b[3][0];				// last row of a is 0,0,0,1
	(*res)[3][1] = b[3][1];				// this leaves the last row of b unchanged
	(*res)[3][2] = b[3][2];
	(*res)[3][3] = b[3][3];

	#undef ROWCOL
}


/***********************************************************************************************
 * Matrix4::Multiply -- Multiply a Matrix4 * Matrix3D                                          *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *=============================================================================================*/
void Matrix4::Multiply(const Matrix4 & a,const Matrix3D & b,Matrix4 * res)
{
	assert(res != &a);
	
	// ROWCOL multiplies a row of 'a' by one of the first three columns of 'b' (4th entry in b is zero)
	// ROWCOL4 multiplies a row of 'a' by the fourth column of 'b' (4th entry in b is one)

	#define ROWCOL(i,j) a[i][0]*b[0][j] + a[i][1]*b[1][j] + a[i][2]*b[2][j]
	#define ROWCOL4(i,j) a[i][0]*b[0][j] + a[i][1]*b[1][j] + a[i][2]*b[2][j] + a[i][3]

	(*res)[0][0] = ROWCOL(0,0);
	(*res)[0][1] = ROWCOL(0,1);
	(*res)[0][2] = ROWCOL(0,2);
	(*res)[0][3] = ROWCOL4(0,3);

	(*res)[1][0] = ROWCOL(1,0);
	(*res)[1][1] = ROWCOL(1,1);
	(*res)[1][2] = ROWCOL(1,2);
	(*res)[1][3] = ROWCOL4(1,3);

	(*res)[2][0] = ROWCOL(2,0);
	(*res)[2][1] = ROWCOL(2,1);
	(*res)[2][2] = ROWCOL(2,2);
	(*res)[2][3] = ROWCOL4(2,3);

	(*res)[3][0] = ROWCOL(3,0);
	(*res)[3][1] = ROWCOL(3,1);
	(*res)[3][2] = ROWCOL(3,2);
	(*res)[3][3] = ROWCOL4(3,3);

	#undef ROWCOL
	#undef ROWCOL4
}

// ??8@YAHABVMatrix4x4@@0@Z
int operator == (const Matrix4x4 & a, const Matrix4x4 & b)
{
	unsigned* m1=(unsigned*)&a;
	unsigned* m2=(unsigned*)&b;
	unsigned res=0;
	for (int i=0;i<4;++i) {
		res|=*m1++^*m2++;
		res|=*m1++^*m2++;
		res|=*m1++^*m2++;
		res|=*m1++^*m2++;
	}
	return !res;
}

// vector4.h's Swap and operator /= sit out of line at the head of this unit's
// retail range (0x007154B0, 0x00715500, just before Multiply), the row
// helpers of the header's Gauss-Jordan Matrix4::Inverse; no retail call
// reaches either. The anchor makes this unit emit its copies for the rows;
// it is not retail code.
#pragma inline_depth(0)
// ?_bfmeMatrix4VectorInlineAnchor@@YAXAAVVector4@@0@Z absent-from-retail
void _bfmeMatrix4VectorInlineAnchor(Vector4 &a, Vector4 &b)
{
	a /= 2.0f;
	Swap(a, b);
}
#pragma inline_depth()
