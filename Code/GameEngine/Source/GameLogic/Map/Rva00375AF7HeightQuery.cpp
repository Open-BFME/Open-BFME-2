// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// BFME1 ba7ddda7e8 AerialPathfinder_getNoFlyZoneHeight is the semantic
// lead. The native boundary and list offsets are independent target facts.
#include <list>
// Native375AF7..375B7A RET8. Circular list head at+10; node payload is
// PolygonTrigger* at+8 and height at+C. Empty list returns0; containing
// polygons update the maximum initialized to-9999. Identity remains neutral.
class ICoord3D { public: int x,y,z; };
class PolygonTrigger { public: bool pointInTrigger(const ICoord3D &); };
// Volatile observations preserve native y/height/shape load order; the
// retail loads are proven, but the original source qualifiers are unknown.
struct Rva00375AF7Entry { PolygonTrigger *volatile shape; volatile float height; };
class Rva00375AF7HeightQuery {
public: float rva00375AF7(float x,volatile float y);
private: char unknown00[0x10]; _STL::list<Rva00375AF7Entry> entries;
};
struct Rva00375AF7State { ICoord3D point; int padding; float height; float highest; };
float Rva00375AF7HeightQuery::rva00375AF7(float x,volatile float y)
{
 if(entries.empty()) return 0.0f;
 _STL::list<Rva00375AF7Entry>::iterator node=entries.begin();
 Rva00375AF7State state; state.highest=-9999.0f;
 for(; node!=entries.end(); ++node) {
  int px=(int)x; int py=(int)y;
  float height=node->height;
  PolygonTrigger *shape=node->shape;
  state.point.z=0; state.point.y=py;
  state.height=height; state.point.x=px;
  if(shape->pointInTrigger(state.point) && !(state.highest>state.height)) state.highest=state.height;
 }
 return state.highest;
}
