// cl: /DNDEBUG /MD /EHs-c-
// ?rva002C97E8@Object@@QBEMPBUCoord3D@@0@Z @0x002C97E8 (94B).
// Object planar shrunken-distance-squared: sqr(max(0, sqrt(dx*dx+dy*dy) - majorRadius)).
// Evidence: this+0xB8 is majorRadius (Object geometry at +0xA8, minor read at +0xBC,
// so major at +0xB8 per bfmeobject shim); positions at +0x38 (planarSubtractWorker,
// isWithinTargetPitch); callers 0x00542F43/0x00547263/0x002C9B3D/0x002CB2D1 pass
// (Object+0x38, Coord3D*) with this=Object; twin 0x002636F6 is the two-radius
// (ret 0xC) shape; thunks 0x002C9846 (16B) and 0x002C9856 (21B) wrap this body.
#include <math.h>

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Object
{
public:
	float rva002C97E8(const Coord3D *a, const Coord3D *b) const;

private:
	char m_pad00[0x38];
	Coord3D m_position; // +0x38
	char m_pad44[0xB8 - 0x38 - 12];
	float m_majorRadius; // +0xB8
};

float Object::rva002C97E8(const Coord3D *a, const Coord3D *b) const
{
	float dx = a->x - b->x;
	float dy = a->y - b->y;
	float rad = m_majorRadius;
	double dist = sqrt((double)(dx * dx + dy * dy));
	float d = (float)dist - rad;
	float result;
	if (d < 0.0f)
		result = 0.0f;
	else
		result = d * d;
	return result;
}
