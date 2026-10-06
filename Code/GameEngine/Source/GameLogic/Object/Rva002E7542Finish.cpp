// cl: /DNDEBUG /MD /EHsc
// ?rva002E7542@Rva002E7542@@QAEPAXHPBUCoord3D@@H@Z @0x002E7542 39B
// Sibling of the Rva002E74B5 / Rva002E757D Bridge lane. Stores a1 at +0x00,
// a3 at +0x04, copies the 12-byte Coord3D to +0x08 and leaves `this` in eax.
// The banked attempt declared a void return (QAEX) and stalled on retail's
// `mov eax,ecx` prologue; the only source shape that reproduces it is one
// whose eax return value is `this`, which byte-matches exactly (39/39).

struct Coord3D { float x; float y; float z; };

class Rva002E7542
{
public:
	void *rva002E7542(int a1, const Coord3D *a2, int a3);

private:
	int m_00;
	int m_04;
	int m_08;
	int m_0c;
	int m_10;
};

void *Rva002E7542::rva002E7542(int a1, const Coord3D *a2, int a3)
{
	m_00 = a1;
	m_04 = a3;
	m_08 = *(int*)&a2->x;
	m_0c = *(int*)&a2->y;
	m_10 = *(int*)&a2->z;
	return this;
}
