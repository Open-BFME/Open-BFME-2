// cl: /O1 /DNDEBUG /MD /arch:SSE /G7 /EHsc
// Release debug hooks called by native Pathfinder 2EFB3A. Both complete
// one-byte providers fold to B3FD0 with no relocations; caller ABI identifies
// their distinct argument surfaces. Keep them external to the caller: VC7
// eliminates known-empty calls even with noinline, whereas retail keeps them.
#include "../../../../Libraries/Include/Lib/Coord3D.h"
struct PathfinderDebugColor { float red,green,blue; };
void Rva000B3FD0PathDebug(const Coord3D *,float,int,PathfinderDebugColor) {}
class PathfindLayer { public: void rva000B3FD0(); };
void PathfindLayer::rva000B3FD0() {}
