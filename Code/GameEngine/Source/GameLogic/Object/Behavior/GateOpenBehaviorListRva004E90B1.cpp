// cl: /DNDEBUG /MD /Oy-
//
// ?rva004E90B1@GateOpenBehaviorList@@QAEPAXPBUCoord3D@@PBVPlayer@@@Z, retail 0x004E90B1, 200 bytes.
// Gate list closest-allied scan over the +0/+4 pointer range (same layout as
// rowed appendOnce 0x004E9353 in GateOpenAndCloseBehaviorCtor.cpp; sole list
// owner is the global at [0xDFEEF8]+0x940). Filters by rowed Relationship
// 0x004989DF (ALLIES=2 via Rva004989D7Get.cpp) then closest squared distance
// to the input point via rowed disp8 getter 0x004989EE (Object+0x38).
// No callers rowed; chain-ready via 0x004989DF. Recipe is closest-scan with
// pos copy plus best/bestDist plus finish.

// ?rva004989DF@Rva004989D7@@QBE?AW4Relationship@@PBVPlayer@@@Z
// ?get@Rva004989EEAddDwordField@@QBEHXZ

enum Relationship
{
	ENEMIES = 0,
	NEUTRAL = 1,
	ALLIES = 2
};

class Player;
struct Coord3D
{
	float x;
	float y;
	float z;
};

class Rva004989D7
{
public:
	Relationship rva004989DF(const Player *p) const;
};

class Rva004989EEAddDwordField
{
public:
	int get() const;
};

class GateOpenBehaviorList
{
public:
	void *rva004E90B1(const Coord3D *pos, const Player *player);

private:
	void **m_begin; // +0
	void **m_end; // +4
};

// ?rva004E90B1@GateOpenBehaviorList@@QAEPAXPBUCoord3D@@PBVPlayer@@@Z @0x004E90B1
void *GateOpenBehaviorList::rva004E90B1(const Coord3D *pos, const Player *player)
{
	void *best = 0;
	float bestDist = 0.0f;
	void **finish = m_end;
	for (void **cur = m_begin; cur != finish; ++cur)
	{
		Rva004989D7 *obj = (Rva004989D7 *)*cur;
		if (obj->rva004989DF(player) != ALLIES)
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
