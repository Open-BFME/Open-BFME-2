// cl: /O1 /DNDEBUG /MD /EHsc /arch:SSE
//
// ?rva0026382B@Object@@QBEXPAUCoord3D@@PBU2@@Z,
// retail 0x0026382B (47 bytes). Dedicated TU next to the forwarder that calls
// it (Object_getPlanarDirectionTo.cpp, 0x002654FC).
//
// Object planar-subtract worker (thiscall, ret 8): out = pos - this->m_position
// planar with z = 0 (SSE). Three callers pass (out, pos) with this at +0x38
// position (0x2654FC getPlanarDirectionTo, 0x2C987B, 0x37618E). Method keeps
// the address token; identity unproven beyond the planar role. Coord3D is a
// struct (PAU per the pin mangling), Object a class (PBV).

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Object
{
public:
	void rva0026382B(Coord3D *out, const Coord3D *pos) const;

private:
	char m_pad[0x38];
	Coord3D m_position; // +0x38
};

// ?rva0026382B@Object@@QBEXPAUCoord3D@@PBU2@@Z
void Object::rva0026382B(Coord3D *out, const Coord3D *pos) const
{
	// Volatile view forces forward pos loads (x then y). Plain C++ lets
	// MSVC 7.1 reverse them (y then x) for x-store-first shapes under every
	// flag tried (/O1 /O2 /Os /Ot /G6 /GB /G7 /Og-); the delta temp split
	// then reproduces retail's sub/out-load/store interleave exactly.
	const volatile Coord3D *source = pos;
	float deltaX = source->x - m_position.x;
	float deltaY = source->y - m_position.y;
	out->x = deltaX;
	out->y = deltaY;
	out->z = 0.0f;
}
