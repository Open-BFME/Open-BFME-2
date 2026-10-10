// ?Rva006B3100@@YAPAURva006B3100Pair@@PAU1@PBURva006B3100Segment@@PBU1@@Z
// partial score=0.94 date=2026-10-10
#include <cstring>
// ?Rva006B3100@@YAPAURva006B3100Pair@@PAU1@PBURva006B3100Segment@@PBU1@@Z
// partial score=0.92 date=2026-10-09
// cl: /O2 /MD /EHsc
// Closest-point projection semantic guide: BFME1 f98983a7d
// TerrainLogicRva001A8170BeaconPathPoint.cpp; native 6B3100..6B3200 proves
// the two-component segment and clamp contract. Export1138 independently names ClosestPointOnLineSegment returning Coord2D
// from LineSegment2D and Coord2D references; this local nontrivial carrier
// expresses the witnessed hidden-output/copy ABI rather than full class layout.
// Existing subtraction/addition providers prove the four-word cdecl ABI;
// their adjacent two float words are passed as one eight-byte value here.
struct Rva006B3100Pair { float x,y; Rva006B3100Pair(){} ~Rva006B3100Pair(){} Rva006B3100Pair(const Rva006B3100Pair &p){std::memcpy(this,&p,8);} };
struct Rva006B3100Segment { Rva006B3100Pair begin,end; };
void Rva001040AESub(float*,float,float,const float*);
void Rva0007DEC8Add(float*,float,float,const float*);
typedef void (__cdecl *PairOperation)(Rva006B3100Pair*,Rva006B3100Pair,const Rva006B3100Pair*);
Rva006B3100Pair *Rva006B3100(Rva006B3100Pair *result,const Rva006B3100Segment *segment,const Rva006B3100Pair *point)
{
 Rva006B3100Pair direction,offset;
 ((PairOperation)&Rva001040AESub)(&direction,segment->end,&segment->begin);
 ((PairOperation)&Rva001040AESub)(&offset,*point,&segment->begin);
 float projection=direction.x*offset.x+direction.y*offset.y;
 if(projection<=0.0f) { *result=segment->begin; return result; }
 float length=direction.x*direction.x+direction.y*direction.y;
 if(projection>=length) { *result=segment->end; return result; }
 double factor=projection/length;
 Rva006B3100Pair scaled;
 scaled.x=direction.x*factor;
 scaled.y=direction.y*factor;
 ((PairOperation)&Rva0007DEC8Add)(result,segment->begin,&scaled);
 return result;
}
