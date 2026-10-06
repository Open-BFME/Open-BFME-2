// cl: /DNDEBUG /MD
//
// ?rva002D782C@Radar@@QAE_NPBUCoord3D@@PAUCoord2D@@@Z @0x002D782C 120B Radar float radar from world via samples plus float clamp.
// Evidence: same this as rowed worldToRadar with m_xSample at +0x24 and
// m_ySample at +0x28; caller 0x0004F53B in FUN_0044f515; prev worldToRadar
// and next rva002D78A4 share flags and Radar class; float limits live in
// .rdata at 0x007C4E90 and 0x007C4DBC.

struct Coord3D
{
	float x;
	float y;
	float z;
};

#include "../../../../Libraries/Include/Lib/Coord2D.h"

class Radar
{
public:
	bool rva002D782C(const Coord3D *world, Coord2D *radar);
private:
	unsigned char m_pad[0x24];
	float m_xSample; // +0x24
	float m_ySample; // +0x28
};

bool Radar::rva002D782C(const Coord3D *world, Coord2D *radar)
{
	if (world == 0 || radar == 0)
		return false;
	radar->x = world->x / m_xSample;
	radar->y = world->y / m_ySample;
	if (radar->x < 0.0f)
		radar->x = 0.0f;
	if (radar->x >= 128.0f)
		radar->x = 127.0f;
	if (radar->y < 0.0f)
		radar->y = 0.0f;
	if (radar->y >= 128.0f)
		radar->y = 127.0f;
	return true;
}
