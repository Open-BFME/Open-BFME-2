// ?rva00283D70@TerrainLogic@@QAEPAVObject@@PBUCoord3D@@@Z
// partial score=0.9256 date=2026-10-09
// ?rva00283D70@TerrainLogic@@QAEPAVObject@@PBUCoord3D@@@Z
// partial score=0.9256 date=2026-10-05
// cl: /O1 /G7 /MD /EHsc /arch:SSE
#include <string.h>

class Object;
class Player;
class Team;
class ThingTemplate;

class Rva000421C8
{
public:
	Rva000421C8() : m_next(0) {}
	virtual ~Rva000421C8() {}
	virtual bool allow(Object *obj) = 0;
	virtual int getPlayerMask();
	Rva000421C8 *link(Rva000421C8 *next);	// 0x00625790
	Rva000421C8 *m_next;
};

class Rva0026119DFilter : public Rva000421C8
{
public:
	virtual bool allow(Object *obj);
};

class BfmeFixedStorage0004543D
{
public:
	BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other) throw();
private:
	unsigned char m_bytes[28];
};

class Rva0004584D : public Rva000421C8
{
public:
	Rva0004584D(const BfmeFixedStorage0004543D &a, const BfmeFixedStorage0004543D &b) throw();
	virtual bool allow(Object *obj);
	BfmeFixedStorage0004543D m_08;
	BfmeFixedStorage0004543D m_24;
};

struct Rva00045411BitSet
{
	Rva00045411BitSet(int unused, int bit) throw();	// 0x00045411
	unsigned int m_bits[7];
};
extern unsigned char g_00DFEFA4StoragePrototype[28];


#include "../../Code/Libraries/Include/Lib/Coord3D.h"

class PartitionManager
{
public:
	Object *getClosestObject(const Coord3D *pos, float maxDist, int dc,
		Rva000421C8 *filters);	// 0x00625360
};
extern PartitionManager *ThePartitionManager;

class Rva0027D098
{
public:
	void rva0027D098();	// 0x0027D098
	float m_00;
	float m_04;
	float m_08;
	int m_0C;
	int m_10;
	const ThingTemplate *m_14;
	unsigned char m_18;
	float m_1C;
	float m_20;
	float m_24;
	int m_28;
	unsigned char m_2C;
	unsigned char m_2D;
};

void Rva0027D098::rva0027D098()
{
	m_00 = 0.0f;
	m_04 = 0.0f;
	m_08 = 0.0f;
	m_0C = 0;
	m_10 = 0;
	m_14 = 0;
	m_18 = 0;
	m_1C = 0.0f;
	m_20 = 0.0f;
	m_24 = 0.0f;
	m_28 = 1;
	m_2C = 1;
	m_2D = 1;
}

struct Rva001A62D0TerrainQueryResult
{
	Rva001A62D0TerrainQueryResult() : m_0C(0), m_10(10000000.0f), m_14(0)
	{
		m_pos.x = 0.0f;
		m_pos.y = 0.0f;
		m_pos.z = 0.0f;
	}
	Coord3D m_pos;
	int m_0C;
	float m_10;
	Rva0027D098 *m_14;
};

struct CreateMask
{
	CreateMask() { memset(this, 0, sizeof(*this)); }
	unsigned int m_bits[4];
};

class Object
{
public:
	void teleportTo(const Coord3D *, bool);	// 0x0029660C
};

class Player
{
public:
	char m_pad000[0x2EC];
	Team *m_2EC;		// +0x2EC
};

class PlayerList
{
public:
	char m_pad00[0x18];
	Player *m_18;		// +0x18
};
extern PlayerList *ThePlayerList;

class ThingFactory
{
public:
	Object *newObject(const ThingTemplate *tmpl, Team *team, const CreateMask *, bool);	// 0x002D0A23
	__forceinline Object *newObject(const ThingTemplate *tmpl, Team *team)
	{
		CreateMask mask;
		return newObject(tmpl, team, &mask, false);
	}
};
extern ThingFactory *TheThingFactory;

class TerrainLogic
{
public:
	void queryPointImplAt001A4630(const Coord3D *pos, float radius,
		Rva001A62D0TerrainQueryResult *out, bool a, bool b);	// 0x0027DCF2
	void rva00283CE7(unsigned int id);	// 0x00283CE7
	Object *rva00283D70(const Coord3D *pos);


};
extern TerrainLogic *TheTerrainLogic;

Object *TerrainLogic::rva00283D70(const Coord3D *pos)
{
	Rva0027D098 *rec;
	{
		Rva001A62D0TerrainQueryResult res;
		queryPointImplAt001A4630(pos, 10.0f, &res, false, false);
		rec = res.m_14;
	}
	Object *obj = 0;
	if (rec) {
		const ThingTemplate *tmpl = rec->m_14;
		if (tmpl) {
			Team *team = ThePlayerList->m_18->m_2EC;
			obj = TheThingFactory->newObject(tmpl, team);
			obj->teleportTo(reinterpret_cast<const Coord3D *>(rec), false);
		}
		unsigned int id = rec->m_0C;
		rec->rva0027D098();
		TheTerrainLogic->rva00283CE7(id);
		return obj;
	} else {
		Rva0004584D kindFilter(*(BfmeFixedStorage0004543D *)&Rva00045411BitSet(0, 86),
			*(BfmeFixedStorage0004543D *)g_00DFEFA4StoragePrototype);
		Rva0026119DFilter aliveFilter;
		kindFilter.link(&aliveFilter);
		return ThePartitionManager->getClosestObject(pos, 10.0f, 1, &kindFilter);
	}
}
