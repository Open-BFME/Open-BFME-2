// ?rva003FD9A3@Rva003FD9A3@@QAEXABUCoord3D@@@Z
// partial score=0.65 date=2026-10-07
// cl: /ICode/Libraries/Include /O1 /arch:SSE /G7 /DNDEBUG /MD
#include "Lib/Coord3D.h"
class ParticleSystem;
ParticleSystem* __cdecl Make001FCBD7();
struct Rva001F3899Arg { int a,b,c; };
struct Rva003FD9A3Point {
    float x,y,z;
    Rva003FD9A3Point(const Coord3D& p) : x(p.x), y(p.y), z(p.z) {}
};
class Rva001F3899Slot { public: void set(const Rva001F3899Arg&); };
class Rva003FB6C5PositionView { public: void set(const Coord3D&); };
class Rva003FD9A3 {
public:
    void rva003FD9A3(const Coord3D& position);
private:
    char m_lead[0x1c];
    ParticleSystem* m_system;
};
void Rva003FD9A3::rva003FD9A3(const Coord3D& position) {
    ((Rva003FB6C5PositionView*)this)->set(position);
    if(m_system) {
        Rva003FD9A3Point point(position);
        ParticleSystem* system=m_system;
        ((Rva001F3899Slot*)(system ? system : Make001FCBD7()))->set(*(Rva001F3899Arg*)&point);
    }
}
