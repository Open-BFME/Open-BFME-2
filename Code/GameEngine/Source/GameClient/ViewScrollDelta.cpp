// cl: -O1 -arch:SSE -G7 -DNDEBUG -MD -ICode/Libraries/Include/Lib
// BFME1 1399ad37d42ea52a63829e417c46a1ba9ed2cd20 Bfme5TinySeventeen.cpp
// supplies the two-float addition shape. Zero Hour View::scrollBy is the
// semantic lead, but its void return differs from native's observed EAX=0.
// Target evidence: table0xBF6178 slot23 at0xBF61D4 points to0x25EAD5;
// slot21 points to the rowed View::lookAt0x25EA7C ending exactly at this body.
// Native this+0xC/+0x10 accesses are the same view position used by lookAt.
// Keep the original target method name and return-type meaning unasserted.
#include "Coord2D.h"
class Rva0025EAD5View {
public:
 int rva0025EAD5(Coord2D *delta);
private:
 unsigned char m_unreconstructed_00[0x0C];
 float m_x, m_y;
};
// ?rva0025EAD5@Rva0025EAD5View@@QAEHPAVCoord2D@@@Z
int Rva0025EAD5View::rva0025EAD5(Coord2D *delta)
{
 m_x = delta->x + m_x;
 m_y = delta->y + m_y;
 return 0;
}
