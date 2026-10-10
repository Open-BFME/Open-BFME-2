// ?rva005A92DE@Rva005A9562@@QAEMPAX@Z
// partial score=0.861269 date=2026-10-10
// cl: /I. /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Oi /ICode/Libraries/Include/Lib /O1 /Oy- /G7 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// Native5A92DE..5A943C RET4; WB callgraph supplies an AIEnemyManager
// priority-distance lead, not a proved original name. Owner pointer0,
// player record lookup2A8AB1 and base-center4EBF4B are target byte facts.
// Canonical Coord3D ABI is retained. Emitted357B vs target350: extra
// trivial-return fallback copy and stack homes remain. A separate scratch
// nontrivial return-view trial scored .9128 with an unadmitted provider
// prototype/map change; it is not included in this usable bank.
class Rva005A9562 {public:float rva005A92DE(void *);private:void *m_ptr;};
#include "wwmath.h"
#include "Code/Libraries/Include/Lib/Coord3D.h"
struct Rva002A8AB1Record;
class Rva002A8F24 {public:Rva002A8AB1Record *rva002A8AB1(void *);};
extern Rva002A8F24 *g_00DFEEF8;
class Rva004EBF4B {public:Coord3D rva004EBF4B();};
Coord3D __cdecl Rva00506CF5(void *,Coord3D *);

struct Rva005A92DEPosition {
 float x,y,z;
 __forceinline Rva005A92DEPosition(const Coord3D &p):x(p.x),y(p.y),z(p.z){}
 __forceinline Rva005A92DEPosition(const Rva005A92DEPosition &p):x(p.x),y(p.y),z(p.z){}
};
static __forceinline float positionDistance(const Coord3D &p,const Rva005A92DEPosition &saved)
{
 float x=p.x-saved.x,y=p.y-saved.y,z=p.z-saved.z;
 return WWMath::Sqrt(z*z+y*y+x*x);
}
float Rva005A9562::rva005A92DE(void *other)
{
 Rva004EBF4B *mine=(Rva004EBF4B *)g_00DFEEF8->rva002A8AB1(m_ptr);
 Rva004EBF4B *enemy=(Rva004EBF4B *)g_00DFEEF8->rva002A8AB1(other);
 if(enemy){
  Rva005A92DEPosition position(mine->rva004EBF4B());
  return positionDistance(enemy->rva004EBF4B(),position);
 }else{
  const Coord3D &position=Rva00506CF5(other,0);
  Coord3D zero;zero.x=0;zero.y=0;zero.z=0;
  if(const_cast<Coord3D &>(position)==zero)return 0;
  Rva005A92DEPosition saved(position);
  return positionDistance(mine->rva004EBF4B(),saved);
 }
}
