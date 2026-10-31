// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /Ireference/shims/sweep
// Clean BFME1 CatmullRom003A14C0.cpp at revision
// 6d9434269164392c5ba62aaa7c15a86b5b020d76, compiled O1/G7/SSE/MD.
// Target Ghidra311638+679: seven cdecl stack slots; either the PE-proven
// D3DXVec3CatmullRom thunk or the identical Catmull-Rom polynomial.
// Target EAX returns out on the polynomial path and the SDK pointer on the
// imported path. Original function name and reachability remain unknown;
// no direct E8/E9 caller was found. Inputs/output access three floats at0/4/8.
// TU-private value arithmetic preserves donor operation/copy ordering without
// exporting incompatible public Vector3 arithmetic or constructor COMDATs.
// These private helpers have no target identity or byte credit.
// Copyright 2025 Electronic Arts Inc.; GPL-3.0-or-later, as in the donor.
#include "d3dx8math.h"
extern "C" D3DXVECTOR3 * __stdcall rva0062AFC8D3DXVec3CatmullRom(D3DXVECTOR3 *,const D3DXVECTOR3 *,const D3DXVECTOR3 *,const D3DXVECTOR3 *,const D3DXVECTOR3 *,float);
namespace {
class CurveValue {
public:
 float X,Y,Z;
 __forceinline CurveValue(const D3DXVECTOR3 &d3DXVECTOR3){X=d3DXVECTOR3.x;Y=d3DXVECTOR3.y;Z=d3DXVECTOR3.z;}
 __forceinline CurveValue(const CurveValue &curveValue){X=curveValue.X;Y=curveValue.Y;Z=curveValue.Z;}
 __forceinline CurveValue(float x,float y,float z){X=x;Y=y;Z=z;}
};
// ?operatorPlus present-unmatched
static __forceinline CurveValue operator+(const CurveValue &a,const CurveValue &b){return CurveValue(a.X+b.X,a.Y+b.Y,a.Z+b.Z);}
// ?operatorMinus present-unmatched
static __forceinline CurveValue operator-(const CurveValue &a,const CurveValue &b){return CurveValue(a.X-b.X,a.Y-b.Y,a.Z-b.Z);}
// ?operatorTimes present-unmatched
static __forceinline CurveValue operator*(const CurveValue &a,float k){return CurveValue(a.X*k,a.Y*k,a.Z*k);}
// ?operatorLeftTimes present-unmatched
static __forceinline CurveValue operator*(float k,const CurveValue &a){return CurveValue(a.X*k,a.Y*k,a.Z*k);}
}
D3DXVECTOR3 *rva00311638CatmullRom(D3DXVECTOR3 *out,const D3DXVECTOR3 *d3DXVECTOR3,const D3DXVECTOR3 *point1,const D3DXVECTOR3 *point2,const D3DXVECTOR3 *point3,float t,bool imported)
{
 if(imported) return rva0062AFC8D3DXVec3CatmullRom(out,d3DXVECTOR3,point1,point2,point3,t);
 float tSquared=t*t;
 float tCubed=t*tSquared;
 CurveValue startPoint=*d3DXVECTOR3,b=*point1,c=*point2,d=*point3;
 CurveValue term0=2.0f*b;
 CurveValue term1=(c-startPoint)*t;
 CurveValue term2=(2.0f*startPoint-5.0f*b+4.0f*c-d)*tSquared;
 CurveValue term3=(3.0f*b-startPoint-3.0f*c+d)*tCubed;
 CurveValue interpolated=(term0+term1+term2+term3)*0.5f;
 out->x=interpolated.X;out->y=interpolated.Y;out->z=interpolated.Z;
 return out;
}
