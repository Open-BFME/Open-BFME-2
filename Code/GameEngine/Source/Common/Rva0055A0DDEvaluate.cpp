// cl: /O1 /G7 /arch:SSE /MD /Ireference/shims/sweep
// platformsdk
// dxsdk
// Clean BFME1 6d9434269164392c5ba62aaa7c15a86b5b020d76,
// game/GameEngine/Source/Common/Bezier/BezierSegmentEvaluation.cpp.
// Copyright 2025 Electronic Arts Inc.; GPL-3.0-or-later.
// Target Ghidra361B/RET8 at55A0DD, ending exactly at55A246 ctor.
// Donor supplies cubic basis semantics. Target proves four12B control points,
// three float outputs and a true D3DXVec4Transform import through62AF4A.
// All64 PE-initial matrix bytes at VA DD2398 match this basis; no runtime
// initializer or guessed original matrix/class/method name is required.
// Original API/class identities and reachability remain unknown.
// Inline dot products preserve the target's scalar SSE arithmetic.
typedef float Real;
#include "../../../Libraries/Include/Lib/Coord3D.h"
#include <d3dx9math.h>
struct _D3DXMATRIX : public D3DXMATRIX
{
	_D3DXMATRIX(float _11, float _12, float _13, float _14,
	            float _21, float _22, float _23, float _24,
	            float _31, float _32, float _33, float _34,
	            float _41, float _42, float _43, float _44)
		: D3DXMATRIX(_11, _12, _13, _14, _21, _22, _23, _24, _31, _32, _33, _34, _41, _42, _43, _44) {}
};
extern const _D3DXMATRIX g_Rva009D2398Basis(-1,3,-3,1,3,-6,3,0,-3,3,0,0,1,0,0,0);
class Rva0055A246
{
public:
	Rva0055A246();
	Rva0055A246(const Rva0055A246 &other);
	Rva0055A246(float x0, float y0, float z0, float x1, float y1, float z1,
	             float x2, float y2, float z2, float x3, float y3, float z3);
	Rva0055A246(float coordinates[12]);
	Rva0055A246(const Coord3D &cp0, const Coord3D &cp1,
	             const Coord3D &cp2, const Coord3D &cp3);
	void rva0055A0DD(float t, Coord3D *result) const;
	float rva0055A627(float tolerance) const;
	void rva0055A40C(float t, Rva0055A246 &left, Rva0055A246 &right) const;
	Coord3D m_arr[4];
};
extern "C" D3DXVECTOR4* __stdcall rva0062AF4AD3DXVec4Transform(D3DXVECTOR4*,const D3DXVECTOR4*,const D3DXMATRIX*);
static __forceinline float rvaDot(const D3DXVECTOR4 *d3DXVECTOR4,const D3DXVECTOR4 *b) { return d3DXVECTOR4->x*b->x+d3DXVECTOR4->y*b->y+d3DXVECTOR4->z*b->z+d3DXVECTOR4->w*b->w; }
void Rva0055A246::rva0055A0DD(Real tValue, Coord3D *outResult) const

{
	if (!outResult)
		return;

	D3DXVECTOR4	parameterPowers(tValue * tValue * tValue, tValue * tValue, tValue, 1);

	D3DXVECTOR4 xCoords(m_arr[0].x, m_arr[1].x, m_arr[2].x, m_arr[3].x);
	D3DXVECTOR4 yCoords(m_arr[0].y, m_arr[1].y, m_arr[2].y, m_arr[3].y);
	D3DXVECTOR4 zCoords(m_arr[0].z, m_arr[1].z, m_arr[2].z, m_arr[3].z);

	D3DXVECTOR4 basisWeights;
	rva0062AF4AD3DXVec4Transform(&basisWeights, &parameterPowers, &g_Rva009D2398Basis);
	
	outResult->x = rvaDot(&xCoords, &basisWeights);
	outResult->y = rvaDot(&yCoords, &basisWeights);
	outResult->z = rvaDot(&zCoords, &basisWeights);
}
