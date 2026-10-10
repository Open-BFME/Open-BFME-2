// cl: /O1 /G7 /arch:SSE /Oy- /DNDEBUG /MD
//
// ?rva0028BE93@Object@@QBEPAUCoord3D@@PAU2@@Z, retail 0x0028BE93, 77 bytes, ret 4.
// Copies a position into the caller's output and returns it: the Coord3D the member at +0x240
// writes through the rowed 0x0028A82A when that member exists, else a zeroed one.
// Evidence: target bytes and the rowed member call; the member's class and field are neutral.

#include "../../../../Libraries/Include/Lib/Coord3D.h"

class Rva0028AF76Sub
{
public:
	void *rva0028A82A(void *out) const;
};

class Object
{
public:
	Coord3D *rva0028BE93(Coord3D *out) const;
private:
	char m_pad[0x240];
	Rva0028AF76Sub *m_sub240;
};

Coord3D *Object::rva0028BE93(Coord3D *out) const
{
	struct { Coord3D tmp; Coord3D zero; int w; } l;
	l.w = 0;
	l.zero.x = 0.0f;
	l.zero.y = 0.0f;
	l.zero.z = 0.0f;
	const Coord3D *source;
	if (m_sub240)
		source = (const Coord3D *)m_sub240->rva0028A82A(&l.tmp);
	else
		source = &l.zero;
	out->x = source->x;
	out->y = source->y;
	out->z = source->z;
	return out;
}
