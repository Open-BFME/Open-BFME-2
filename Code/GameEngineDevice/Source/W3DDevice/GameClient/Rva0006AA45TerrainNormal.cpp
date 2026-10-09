// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath
// BFME1 header revision 9cbfb551fe20dae985f91f2319d8997287b6a705.
// Semantic guide: WWMath Vector3::Normalized_Cross_Product and Normalize.
// Target 0006AA45..0006AB49 (260B), four thiscall ushort samples at6653B;
// x/y integer coordinates and output Vector3 pointer, RET12. Target constants
// BC596C=.0390625, BC5CCC=20, BC5D00=400, BC5CFC=160000.
// Original terrain-owner identity is unproven; reuse the target sample owner's
// address-derived type rather than promoting a WorldHeightMap guess.
#include "../../../../../reference/shims/bfme_vector3_ctor_link/vector3.h"
#include "vector3.h"
class Rva0006653B {
public:
 unsigned short rva0006653B(int x,int y);
 void rva0006AA45(int x,int y,Vector3 *normal);
};
void Rva0006653B::rva0006AA45(int x,int y,Vector3 *normal)
{
 Vector3 l2r(20.0f,0.0f,(rva0006653B(x+1,y)-rva0006653B(x-1,y))*0.0390625f);
 Vector3 n2f(0.0f,20.0f,(rva0006653B(x,y+1)-rva0006653B(x,y-1))*0.0390625f);
 Vector3::Normalized_Cross_Product(l2r,n2f,normal);
}
