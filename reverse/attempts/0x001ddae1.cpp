// ?rva001DDAE1@Rva001DDAE1@@QAEXPAUCoord3D@@@Z
// partial score=0.7052023121387283 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /Oy- /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfmelist /ICode/Libraries/Include
// stlport
#include <list>
#include "Lib/Coord3D.h"
class Rva0041F431 {public:Rva0041F431*rva0041F431();};
struct BfmeFloat4Record00469C61 {BfmeFloat4Record00469C61(){((Rva0041F431*)this)->rva0041F431();}unsigned int frame;Coord3D position;};
class Rva00357E14 {public:void rva00357E14(const BfmeFloat4Record00469C61&);};
typedef _STL::list<BfmeFloat4Record00469C61,_STL::allocator<BfmeFloat4Record00469C61> > EvaLocationList;
namespace _STL {template EvaLocationList::iterator EvaLocationList::erase(EvaLocationList::iterator);}
class GameLogic {public:char pad[0x40];unsigned int frame;};extern GameLogic*TheGameLogic;
class Rva001DDAE1 {public:void rva001DDAE1(Coord3D*);char pad0[0x68];EvaLocationList locations;EvaLocationList::iterator cursor;char pad70[0x94-0x70];float minimumDistance;};
void Rva001DDAE1::rva001DDAE1(Coord3D*position)
{
 if(!locations.empty()) {
  EvaLocationList::iterator first=locations.begin();
  Coord3D delta;delta.x=position->x;delta.y=position->y;delta.z=position->z;
  delta.x-=first->position.x;delta.y-=first->position.y;delta.z-=first->position.z;
  if(delta.z*delta.z+delta.y*delta.y+delta.x*delta.x<minimumDistance*minimumDistance) {
   if(cursor==first)cursor=locations.end();
   locations.erase(first);
  }
 }
 BfmeFloat4Record00469C61 record;
 record.position=*position;
 record.frame=TheGameLogic->frame;
 ((Rva00357E14*)&locations)->rva00357E14(record);
}
