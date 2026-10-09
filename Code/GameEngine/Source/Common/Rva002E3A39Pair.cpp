// cl: /O1 /DNDEBUG /MD /arch:SSE
// Native callers2E3AA8/1019DA/101CF6 test AL after this call.
// WB ABA730 returns the planar query result. Rename the prior void owner
// to the existing PolygonTrigger pointer-view spelling; no extra identity.
// Layout x/y is native-measured; helper30B7C2 is the rowed bool provider.
#include "../../../Libraries/Include/Lib/Coord3D.h"
struct Rva0030B7C2Point { float x,y; };
class Rva0030B719Shape;
bool rva0030B7C2(const Rva0030B7C2Point*,Rva0030B719Shape*);
class PolygonTrigger {public:bool rva002E3A39(const Coord3D&);};
bool PolygonTrigger::rva002E3A39(const Coord3D&p){Rva0030B7C2Point point;point.x=p.x;point.y=p.y;return rva0030B7C2(&point,(Rva0030B719Shape*)((char*)this+8));}
