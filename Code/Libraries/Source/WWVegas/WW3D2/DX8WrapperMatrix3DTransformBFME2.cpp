// Link view first: Vector4(x,y,z,w) stays inline without emitting an SSE copy that competes with retail's integer-move owner (0x006D8A30).
// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it; retail links the
// /O1 body at 0x00001423. Instantiate it first in an unemitted anchor (the
// lookuptable.cpp pattern) so this unit's copy is that body.
#include "../../../../GameEngine/Include/Common/BfmeVciAnchorElem.h"
#pragma optimize("gsy", on)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
#include "../../../../../reference/shims/bfme_matrix3d_sse_link/vector4.h"
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
// cl: /O1 /Oy- /G7 /arch:SSE /DNDEBUG /MD /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// dxsdk
// platformsdk
// ZH dx8wrapper.h donor at BFME1 revision9cbfb551fe20dae985f91f2319d8997287b6a705.
// DX8Wrapper Matrix3D transform overload at6A553,1042B throughRET6A964.
// ZH dx8wrapper.h is the semantic guide; BFME Matrix4 sibling A68A7 and
// bfmecamera's verified projection treatment establish the two projection copies.
// Native WORLD/VIEW flags clear identity before setting the changed bit.
#include "winbase_shim.h"
#include "matrix3d.h"
// Link view: Matrix4(Vector4 x4), Transpose and the Matrix3D overloads stay inline without emitting
// copies that lose to retail's /O1 owners (0x0006A34E, 0x0006A3D1).
#include "../../../../../reference/shims/bfme_matrix4_rows_link/matrix4_bfme1_rows_link.h"
#include <d3d9.h>
struct IDirect3DDevice8;
#include "RenderStateStruct.h"
extern unsigned number_of_DX8_calls;
#include "DX8WrapperClass.h"
// Select-any like every other TU's copy (a strong definition would duplicate theirs at link time);
// the anchor keeps the noinline body emitted.
__declspec(noinline) inline void DX8Wrapper::Set_Transform(D3DTRANSFORMSTATETYPE transform,const Matrix3D& m) {
 Matrix4 m2(m);
 switch((int)transform) {
 case D3DTS_WORLD:
  render_state.world=m2.Transpose();
  render_state_changed&=~(unsigned)(1<<18);
  render_state_changed|=1;
  break;
 case D3DTS_VIEW:
  render_state.view=m2.Transpose();
  render_state_changed&=~(unsigned)(1<<19);
  render_state_changed|=2;
  break;
 case D3DTS_PROJECTION:
  ProjectionMatrix=m2.Transpose();
  DeviceProjectionMatrix=ProjectionMatrix;
  ZFar=0.0f;ZNear=0.0f;
  reinterpret_cast<IDirect3DDevice9*>(D3DDevice)->SetTransform(D3DTS_PROJECTION,(D3DMATRIX*)&DeviceProjectionMatrix);
  number_of_DX8_calls++;
  break;
 default:
  matrix_changes++;
  m2=m2.Transpose();
  reinterpret_cast<IDirect3DDevice9*>(D3DDevice)->SetTransform(transform,(D3DMATRIX*)&m2);
  number_of_DX8_calls++;
  break;
 }
}

// ?bfmeAnchorDX8WrapperSet_Transform absent-from-retail
void bfmeAnchorDX8WrapperSet_Transform(DX8Wrapper *dX8Wrapper, D3DTRANSFORMSTATETYPE transform, const Matrix3D& matrix3D)
{
	dX8Wrapper->Set_Transform(transform, matrix3D);
}
