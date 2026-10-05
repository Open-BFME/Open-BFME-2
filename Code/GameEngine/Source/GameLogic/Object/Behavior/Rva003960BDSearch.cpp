// cl: /Ireference/shims/bfme2_ascii /O1 /Oy- /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ?rva003960BD@@YA_NHPBURva0036BDD0Vec@@0@Z @0x003960BD 97B: true when every
// relationship-3 player with remaining mask has no failing object under the
// rowed 0x00796023 iterate callback over the [v1,v2] box. Evidence: global
// ThePlayerList feeds rowed getPlayersWithRelationship(.,3,false) at
// 0x002A7C70 and getEachPlayerFromMask at 0x002A7BC9, the local is the rowed
// Rva0036BDD0 box set from (v1,v2) by rowed 0x003958F6, rowed
// Player::iterateObjects at 0x002AB08B runs callback+box, result is box m_18;
// flags and decls follow neighbouring Behavior TUs.
typedef int Int;

class Object;
class Player;
class PlayerList;

typedef int PlayerMaskType;
typedef Int (*ObjectIterateFunc)(Object *obj, void *userData);

struct Rva0036BDD0Vec
{
	int a;
	int b;
	int c;
};

class Rva0036BDD0
{
	Rva0036BDD0Vec m_00;
	Rva0036BDD0Vec m_0C;
	bool m_flag18;

public:
	Rva0036BDD0 &set(const Rva0036BDD0Vec *p, const Rva0036BDD0Vec *q);
	bool getFlag18(void) const { return m_flag18; }
};

class Player
{
public:
	Int iterateObjects(ObjectIterateFunc func, void *userData) const;
};

class PlayerList
{
public:
	Player *getEachPlayerFromMask(PlayerMaskType &maskToAdjust);
	PlayerMaskType getPlayersWithRelationship(Int srcPlayerIndex, unsigned int allowedRelationships, bool reverse);
};

extern PlayerList *ThePlayerList;
Int rva00796023(Object *obj, void *userData);

bool __cdecl rva003960BD(Int rel, const Rva0036BDD0Vec *v1, const Rva0036BDD0Vec *v2)
{
	PlayerMaskType mask = ThePlayerList->getPlayersWithRelationship(rel, 3, false);
	Rva0036BDD0 box;
	box.set(v1, v2);
	while (mask != 0) {
		Player *p = ThePlayerList->getEachPlayerFromMask(mask);
		if (p != 0) {
			if (p->iterateObjects(rva00796023, &box) == 0)
				return false;
		}
	}
	return box.getFlag18();
}
