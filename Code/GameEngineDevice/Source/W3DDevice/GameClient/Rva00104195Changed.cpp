// cl: /O1 /G7 /arch:SSE /MD /EHsc
// Native 00104195..001041D8: receiver is the 0x88-byte object established
// by Rva001041D8Dtor.cpp; four saved Coord2D-sized records start at +0x28.
// The rowed array accessor at 2D3850 returns the current pair for index i.
// Caller 104A75 tests AL. Comparing both floats includes the native unordered
// branch behavior. The Palantir identity remains a donor/structural lead.
// An explicit per-iteration record pointer reproduces retail's +0x28 cursor;
// spelling saved[i].x/y directly picks +0x2C and changes the first load.
#include "../../../../GameEngine/Include/Common/Rva002D3850.h"
struct NativeCoord2 {float x,y;};
class Rva00104195 {public:bool rva00104195();private:char lead[0x28];NativeCoord2 saved[4];};
bool Rva00104195::rva00104195(){for(int i=0;i<4;++i){float*p=((Rva002D3850*)this)->GetRadarViewBoxCorner(i);NativeCoord2*nativeCoord2=&saved[i];if(nativeCoord2->x!=p[0]||nativeCoord2->y!=p[1])return true;}return false;}
