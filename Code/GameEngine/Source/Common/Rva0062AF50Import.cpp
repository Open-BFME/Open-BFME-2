// cl: /O1 /arch:SSE /G7 /MD /Ireference/shims/sweep
// rva0062AF50D3DXPlaneFromPointNormal at 0x0062AF50 (6B). Retail thunk targets the PE IAT entry for d3dx9_27.dll!D3DXPlaneFromPointNormal.
#define D3DXPlaneFromPointNormal D3DXPlaneFromPointNormal_unused_shim
#define D3DXVec3Transform D3DXVec3Transform_unused_shim
#include "d3dx8math.h"
#undef D3DXPlaneFromPointNormal
#undef D3DXVec3Transform

extern "C" __declspec(dllimport) D3DXPLANE * __stdcall D3DXPlaneFromPointNormal(
	D3DXPLANE *out, const D3DXVECTOR3 *point, const D3DXVECTOR3 *normal);

extern "C" D3DXPLANE * __stdcall rva0062AF50D3DXPlaneFromPointNormal(
	D3DXPLANE *out, const D3DXVECTOR3 *point, const D3DXVECTOR3 *normal)
{
	return D3DXPlaneFromPointNormal(out, point, normal);
}

extern "C" __declspec(dllimport) D3DXVECTOR4 * __stdcall D3DXVec3Transform(
	D3DXVECTOR4 *out, const D3DXVECTOR3 *vector, const D3DXMATRIX *matrix);

extern "C" D3DXVECTOR4 * __stdcall rva0062AF56D3DXVec3Transform(
	D3DXVECTOR4 *out, const D3DXVECTOR3 *vector, const D3DXMATRIX *matrix)
{
	return D3DXVec3Transform(out, vector, matrix);
}
