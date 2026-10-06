// cl: /DNDEBUG /MD /Oy-
//
// ?rva004E9179@GateOpenBehaviorList@@QAEPAXPBUCoord3D@@PBVPlayer@@@Z, retail 0x004E9179, 197 bytes.
// Gate list closest-owned scan over the +0/+4 pointer range (same layout as
// rowed 0x004E90B1 in GateOpenBehaviorListRva004E90B1.cpp and rowed
// appendOnce 0x004E9353). Filters by exact owner via rowed 0x004989D7
// (getControllingPlayer via Rva004989D7Get.cpp) then closest squared distance
// to the input point via rowed disp8 getter 0x004989EE (Object+0x38).
// Chain-ready via 0x004989D7. Recipe is closest-scan with pos copy plus
// best/bestDist plus finish.

// ?rva004989D7@Rva004989D7@@QBEPAVPlayer@@XZ
// ?get@Rva004989EEAddDwordField@@QBEHXZ

class Player;
#include "../../../../../Libraries/Include/Lib/Coord3D.h"

class Rva004989D7
{
public:
	Player *rva004989D7() const;
};

class Rva004989EEAddDwordField
{
public:
	int get() const;
};

class GateOpenBehaviorList
{
public:
	void *rva004E9179(const Coord3D *pos, const Player *player);

private:
	void **m_begin; // +0
	void **m_end; // +4
};

void *GateOpenBehaviorList::rva004E9179(const Coord3D *pos, const Player *player)
{
	void *best = 0;
	float bestDist = 0.0f;
	void **finish = m_end;
	for (void **cur = m_begin; cur != finish; ++cur)
	{
		Rva004989D7 *obj = (Rva004989D7 *)*cur;
		if (obj->rva004989D7() != player)
			continue;
		float vals[3];
		vals[0] = pos->x;
		vals[1] = pos->y;
		vals[2] = pos->z;
		const float *q = (const float *)((Rva004989EEAddDwordField *)obj)->get();
		float dx = vals[0] - q[0];
		float dy = vals[1] - q[1];
		float dz = vals[2] - q[2];
		float distSq = dx * dx + dy * dy + dz * dz;
		if (best == 0 || bestDist > distSq)
		{
			best = obj;
			bestDist = distSq;
		}
	}
	return best;
}
