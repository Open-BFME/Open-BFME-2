// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /ICode/Libraries/Include
// ?rva003FD9A3@Rva003FD9A3@@QAEXABUCoord3D@@@Z @0x003FD9A3, 87B, RET4.
// Sibling of Rva003FDA19Position.cpp (the same primary position worker 0x003FB6C5,
// then the +0x1C particle slot): after the worker, a present slot receives a copy of
// the position through the established slot setter 0x001F3899, fetching the shared
// system from 0x001FCBD7 when the slot is empty. The volatile pointer view keeps
// the second read of +0x1C and the factory branch that the optimiser would otherwise
// fold (as in Rva003FDA19Position.cpp; the original qualifier is unknown). The copy is
// three float moves through a stack temporary. Original receiver and names unknown.
#include "Lib/Coord3D.h"

class ParticleSystem;
ParticleSystem *__cdecl Make001FCBD7();

struct Rva001F3899Arg { int a, b, c; };

struct Rva003FD9A3Point
{
	float x, y, z;
	Rva003FD9A3Point(const Coord3D &p) : x(p.x), y(p.y), z(p.z) {}
};

class Rva001F3899Slot { public: void set(const Rva001F3899Arg &); };
class Vector3;
class Rva003FD14DBase { public: void rva003FB6C5(const Vector3 &); };	// 0x003FB6C5

class Rva003FD9A3
{
public:
	void rva003FD9A3(const Coord3D &position);
private:
	char m_lead[0x1c];
	ParticleSystem *m_system;
};

void Rva003FD9A3::rva003FD9A3(const Coord3D &position)
{
	((Rva003FD14DBase *)this)->rva003FB6C5(*(const Vector3 *)&position);
	if (m_system) {
		Rva003FD9A3Point point(position);
		ParticleSystem *system = *(ParticleSystem *volatile *)&m_system;
		((Rva001F3899Slot *)(!system ? Make001FCBD7() : system))->set(*(Rva001F3899Arg *)&point);
	}
}
