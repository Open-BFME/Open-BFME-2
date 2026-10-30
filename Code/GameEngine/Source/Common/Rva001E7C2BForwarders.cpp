// cl: /O1 /G7
// The 33-byte target bodies at 0x001E7C2B and 0x001E9045 forward the same
// four stack dwords to distinct direct callees. Target x87 loads identify the
// final two arguments as floats; the meanings of the first two dwords and the
// owning class are unknown. Both callee entries are Ghidra boundaries and are
// pinned by their exact REL32 calls below.

class Rva001E7053 {
public:
	void rva001e7053(unsigned int, unsigned int, float, float);
};

class Thing;
class Rva001E702E {
public:
	void rva001E702E(Thing *, int, int);
};

struct Coord3D;
class Object;
class Rva001E46E1 {
public:
	void rva001E6007(Object *, const Coord3D *, float, float);
};

class Rva001E8C1B {
public:
	void rva001E8C1B(int, int, float, float);
};

class Rva001E7C2B {
public:
	void rva001e7c2b(unsigned int, unsigned int, float, float);
};

class Rva001E9045 {
public:
	void rva001e9045(unsigned int, unsigned int, float, float);
};

// ?rva001e7053@Rva001E7053@@QAEXIIMM@Z
void Rva001E7053::rva001e7053(unsigned int a, unsigned int position, float c, float d)
{
	reinterpret_cast<Rva001E702E *>(this)->rva001E702E(reinterpret_cast<Thing *>(a), (int)position, 0);
	reinterpret_cast<Rva001E46E1 *>(this)->rva001E6007(reinterpret_cast<Object *>(a), reinterpret_cast<const Coord3D *>(position), c, d);
}

void Rva001E7C2B::rva001e7c2b(unsigned int a, unsigned int position, float c, float d)
{
	reinterpret_cast<Rva001E7053 *>(this)->rva001e7053(a, position, c, d);
}

void Rva001E9045::rva001e9045(unsigned int a, unsigned int b, float c, float d)
{
	reinterpret_cast<Rva001E8C1B *>(this)->rva001E8C1B((int)a, (int)b, c, d);
}
