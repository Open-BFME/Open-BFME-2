// cl: /MD /Ireference/shims/sweep
// PE proves RVA62AF4A is FF25 through IAT BBA9C8:
// d3dx9_27.dll!D3DXVec4Transform. The existing validated SDK types
// supply the 16B vector, 64B matrix, stdcall12 and pointer-result ABI.
// Original thunk name is unknown; ordinary C++ forwarding emits all6B.
#define D3DXVec4Transform D3DXVec4Transform_unused_shim
#include "d3dx8math.h"
#undef D3DXVec4Transform
extern "C" __declspec(dllimport) D3DXVECTOR4 * __stdcall D3DXVec4Transform(
    D3DXVECTOR4 *, const D3DXVECTOR4 *, const D3DXMATRIX *);
extern "C" D3DXVECTOR4 * __stdcall rva0062AF4AD3DXVec4Transform(
    D3DXVECTOR4 *out, const D3DXVECTOR4 *v, const D3DXMATRIX *matrix)
{
    return D3DXVec4Transform(out, v, matrix);
}
