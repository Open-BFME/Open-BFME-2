// cl: /O1 /Ob2 /arch:SSE /G7 /DNDEBUG /MD /GX-
// ZH W3DRoadBuffer.h defines TRoadSegInfo's three Vector2 prefix members,
// four Vector2 corners and three scalars. NativeD4ED0's array callback is
// the existing folded3B empty constructor47A6A9. The six early stores are
// explicit zero-valued prefix construction; the later loop clears corners.
class Vector2 {
public:
 Vector2();
 __forceinline Vector2(float xValue,float yValue) : x(xValue),y(yValue) {}
 float x,y;
};
Vector2::Vector2() {}
struct TRoadSegInfo {
 TRoadSegInfo();
 Vector2 loc,roadNormal,roadVector;
 Vector2 corners[4];
 float uOffset,vOffset,scale;
};
TRoadSegInfo::TRoadSegInfo() : loc(0.f,0.f),roadNormal(0.f,0.f),roadVector(0.f,0.f) {
 uOffset=0;
 vOffset=0;
 scale=0;
 Vector2 *corner=corners;
 int count=4;
 do {
  corner->x=0;
  corner->y=0;
  ++corner;
 } while(--count);
}
