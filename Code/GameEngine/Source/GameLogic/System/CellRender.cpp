// cl: /O1 /G7 /arch:SSE /MD
// Primary semantic donor: BFME1 BfmeCellRva001DE2A0.cpp at
// 9cbfb551fe20dae985f91f2319d8997287b6a705. Target40495D..404A0D
// independently fixes twenty-channel arrays0/50, parameter4/8/10,
// clamp and normalized triples. Both native calls reach shared empty RET
// B3FD0 and use caller-cleaned (pointer,float,int,triple12) ABI. The
// existing address-derived empty provider is used through that raw call view;
// neither the original cell method nor the disabled callback is named.
#include "../../../../Libraries/Include/Lib/Coord3D.h"
void Rva000B3FD0(int,char *[]);
struct CellDrawTriple { float first,second,third; };
typedef void (__cdecl *CellEmptyCall)(const Coord3D *,float,int,CellDrawTriple);
struct CellDrawParameters { float unused,allyScale,enemyScale,unusedC,threshold; };
class Rva0040495D {
public: void rva0040495D(const Coord3D*,float,int,void*);
private: float first[20],second[20];
};
void Rva0040495D::rva0040495D(const Coord3D *position,float size,int index,void *parameters) {
 const CellDrawParameters *p=(const CellDrawParameters*)parameters;
 float value=first[index]*p->enemyScale-second[index]*p->allyScale;
 if (!(value>0.0f)) value=0.0f;
 if (!(value<p->threshold)) value=p->threshold;
 float ratio=value/p->threshold;
 CellDrawTriple triple;
 triple.first=1.0f;
 triple.third=1.0f;
 triple.second=ratio;
 ((CellEmptyCall)Rva000B3FD0)(position,size,6,triple);
 triple.third=0.0f;
 ((CellEmptyCall)Rva000B3FD0)(position,size-20.0f,6,triple);
}
