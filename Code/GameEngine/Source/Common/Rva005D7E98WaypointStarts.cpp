// cl: /O1 /G7 /EHsc /MD /Ireference/shims/bfme2_ascii
// Target5D7E98/197 formats Player_%d_Start for1..8; TerrainLogic slot33
// supplies waypoint chain (name+8,next+1C,wordID+4); caches IDs atreceiver2C
// and increments existingcount28. Receiver original identity and complete
// object size are unknown; only the accessed prefixes are represented.
#include "ascii_string.h"
class TerrainLogic;extern TerrainLogic *TheTerrainLogic;
struct Rva005D7E98Waypoint { unsigned int unknown0,id;StringBase<char> name;unsigned char unknownC[0x10];Rva005D7E98Waypoint *next; };
template<int N> class Rva005D7E98Slots:public Rva005D7E98Slots<N-1> { public:virtual void gap(char(*)[N])=0; };
template<> class Rva005D7E98Slots<0>{};
class Rva005D7E98TerrainView:public Rva005D7E98Slots<33> { public:virtual Rva005D7E98Waypoint *firstWaypoint()=0; };
class Rva005D7E98 { public:void rva005D7E98();unsigned char unknown[0x28];int count;unsigned int starts[8]; };
// ?findWaypoint present-unmatched
// Helper is expanded into the verified caller; no independent retail entry asserted.
static __forceinline Rva005D7E98Waypoint *findWaypoint(AsciiString key) {
 Rva005D7E98Waypoint *current=((Rva005D7E98TerrainView*)TheTerrainLogic)->firstWaypoint();
 for(;current;current=current->next)
  if(current->name.compare(*(StringBase<char>*)&key)==0)return current;
 return 0;
}
void Rva005D7E98::rva005D7E98() {
 for(int i=0;i<8;++i) {
  AsciiString name;name.format("Player_%d_Start",i+1);
  Rva005D7E98Waypoint *waypoint=findWaypoint(name);
  if(!waypoint)break;
  starts[i]=waypoint->id;
  ++count;
 }
}
