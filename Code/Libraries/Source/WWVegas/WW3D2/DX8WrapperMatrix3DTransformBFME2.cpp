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
// ZH dx8wrapper.h donor at BFME1 revision9cbfb551fe20dae985f91f2319d8997287b6a705.
// DX8Wrapper Matrix3D transform overload at6A553,1042B throughRET6A964.
// ZH dx8wrapper.h is the semantic guide; BFME Matrix4 sibling A68A7 and
// bfmecamera's verified projection treatment establish the two projection copies.
// Native WORLD/VIEW flags clear identity before setting the changed bit.
#include "winbase_shim.h"
#include "matrix3d.h"
#include "matrix4.h"
#include <d3d8.h>
struct RenderStateStruct { unsigned char unused_fields[0x1EC]; Matrix4 world,view; };
extern unsigned number_of_DX8_calls;
class DX8Wrapper {
public:
 static void Set_Transform(D3DTRANSFORMSTATETYPE transform,const Matrix3D& m);
protected:
 static RenderStateStruct render_state;
 static unsigned render_state_changed;
 static unsigned matrix_changes;
 static IDirect3DDevice8* D3DDevice;
 static float ZNear,ZFar;
 static Matrix4 ProjectionMatrix,DeviceProjectionMatrix;
};
void DX8Wrapper::Set_Transform(D3DTRANSFORMSTATETYPE transform,const Matrix3D& m) {
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
  D3DDevice->SetTransform(D3DTS_PROJECTION,(D3DMATRIX*)&DeviceProjectionMatrix);
  number_of_DX8_calls++;
  break;
 default:
  matrix_changes++;
  m2=m2.Transpose();
  D3DDevice->SetTransform(transform,(D3DMATRIX*)&m2);
  number_of_DX8_calls++;
  break;
 }
}
