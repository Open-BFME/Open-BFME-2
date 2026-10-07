// ?rva00494599@Rva00494599@@QAE_NPBUCoord3D@@@Z
// partial score=1.0 date=2026-10-07
// ?rva00494599@Rva00494599@@QAE_NPBUCoord3D@@@Z
// partial score=1.0 date=2026-10-06
// cl: /ICode/Libraries/Include/Lib /Ireference/shims/bfme2_ascii /O1 /MD /EHs /arch:SSE /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
//
// ?rva00494599@Rva00494599@@QAE_NPBUCoord3D@@@Z @0x00494599 212B ret 4.
// Null holder, object, or player returns true. Otherwise the player fills
// a Coord3D vector and any point within the holder float is a hit.

#include <vector>

#include "Coord3D.h"

class Player;

class Object
{
public:
	Player *getControllingPlayer() const;
};

class Player
{
public:
	void rva002AF614(void *points);
};

class Rva00494599Holder
{
public:
	char m_pad[0x78];
	float m_limit;
};

class Rva00494599
{
public:
	bool rva00494599(const Coord3D *pos);
	char m_pad[4];
	Rva00494599Holder *m_holder;
	Object *m_obj;
};

bool Rva00494599::rva00494599(const Coord3D *pos)
{
	Rva00494599Holder *holder = m_holder;
	Object *obj;
	if (holder == 0 || (obj = m_obj) == 0)
		return true;
	Player *player = obj->getControllingPlayer();
	if (player == 0)
		return true;

	_STL::vector<Coord3D> points;
	player->rva002AF614(&points);

	bool found = false;
	for (Coord3D *it = points.begin(); it != points.end(); ++it)
	{
		float dx = pos->x;
		float dy = pos->y;
		float dz = pos->z;
		dx -= it->x;
		dy -= it->y;
		dz -= it->z;
		Coord3D delta;
		delta.x = dx;
		delta.y = dy;
		delta.z = dz;
		if (delta.length() <= holder->m_limit)
		{
			found = true;
			break;
		}
	}
	return found;
}
