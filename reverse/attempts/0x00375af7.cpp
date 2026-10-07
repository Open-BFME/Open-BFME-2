// ?rva00375AF7@Rva00375AF7HeightQuery@@QAEMMM@Z
// partial score=0.93 date=2026-10-07
// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
#include <list>
// Native375AF7..375B7A RET8. Circular list head at+10; node payload is
// PolygonTrigger* at+8 and height at+C. Empty list returns0; containing
// polygons update the maximum initialized to-9999. Identity remains neutral.
class ICoord3D { public: int x,y,z; };
class PolygonTrigger { public: bool pointInTrigger(const ICoord3D &); };
struct Rva00375AF7Entry { PolygonTrigger *shape; float height; };
class Rva00375AF7HeightQuery {
public: float rva00375AF7(float x,volatile float y);
private: char unknown00[0x10]; _STL::list<Rva00375AF7Entry> entries;
};
float Rva00375AF7HeightQuery::rva00375AF7(float x,volatile float y)
{
 if(entries.empty()) return 0.0f;
 float highest=-9999.0f;
 for(_STL::list<Rva00375AF7Entry>::iterator node=entries.begin(); node!=entries.end(); ++node) {
  float height=node->height;
  ICoord3D point;point.x=(int)x;point.y=(int)y;point.z=0;
  if(node->shape->pointInTrigger(point) && !(highest>height)) highest=height;
 }
 return highest;
}
