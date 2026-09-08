// cl: /G7 /arch:SSE /Ireference/shims/bfmerendobj /DNDEBUG /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
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

// Matrix3D transform class, verbatim from the Generals reference
// (Libraries/Source/WWVegas/WWMath/matrix3d.cpp). Only the functions located in
// the binary are defined here; Multiply and Lerp are omitted because the retail
// build's inlining/codegen for them drifted from this source (see report).

#include "rendobj.h"	// the bfmerendobj shim has to win the include guard
#include "matrix3d.h"

#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include "vector3.h"
#include "matrix3.h"
#include "matrix4.h"
#include "quat.h"
#include "D3dx8math.h"

// BFME2 uses the D3DX9 4x4 inverse through d3dx9_27.dll.
// The matrix ABI is the same sixteen-float layout as the retained math header.

void Matrix3D::Get_Inverse(Matrix3D & inv) const
{
	Matrix4	mat4(*this);
	Matrix4	mat4Inv;

	float det;
	D3DXMatrixInverse((D3DXMATRIX *)&mat4Inv, &det, (D3DXMATRIX*)&mat4);

	inv.Row[0][0]=mat4Inv[0][0];
	inv.Row[0][1]=mat4Inv[0][1];
	inv.Row[0][2]=mat4Inv[0][2];
	inv.Row[0][3]=mat4Inv[0][3];

	inv.Row[1][0]=mat4Inv[1][0];
	inv.Row[1][1]=mat4Inv[1][1];
	inv.Row[1][2]=mat4Inv[1][2];
	inv.Row[1][3]=mat4Inv[1][3];

	inv.Row[2][0]=mat4Inv[2][0];
	inv.Row[2][1]=mat4Inv[2][1];
	inv.Row[2][2]=mat4Inv[2][2];
	inv.Row[2][3]=mat4Inv[2][3];
}

// Transpose rotation and apply its inverse to translation using retail SSE.
void Matrix3D::Get_Orthogonal_Inverse(Matrix3D & inv) const
{
	// Transposing the rotation submatrix
	inv.Row[0][0] = Row[0][0];
	inv.Row[0][1] = Row[1][0];
	inv.Row[0][2] = Row[2][0];

	inv.Row[1][0] = Row[0][1];
	inv.Row[1][1] = Row[1][1];
	inv.Row[1][2] = Row[2][1];

	inv.Row[2][0] = Row[0][2];
	inv.Row[2][1] = Row[1][2];
	inv.Row[2][2] = Row[2][2];

	// Now, calculate translation portion of matrix:
	// T' = -R'T
	Vector3 trans = Get_Translation();
	trans = Vector3(inv.Row[0][0]*trans[0] + inv.Row[0][1]*trans[1] + inv.Row[0][2]*trans[2],
	                inv.Row[1][0]*trans[0] + inv.Row[1][1]*trans[1] + inv.Row[1][2]*trans[2],
	                inv.Row[2][0]*trans[0] + inv.Row[2][1]*trans[1] + inv.Row[2][2]*trans[2]);
	trans = -trans;

	inv.Row[0][3] = trans[0];
	inv.Row[1][3] = trans[1];
	inv.Row[2][3] = trans[2];
}

