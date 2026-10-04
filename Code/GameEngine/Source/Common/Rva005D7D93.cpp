// cl: /O1 /MD /arch:SSE
// ?rva005D7D93@Rva005EE816@@QAE_NPAVObject@@@Z, retail 0x005D7D93, 111 bytes.
// Evidence: slot 6 of 0x00875EAC, pin Rva005EE816, calls rowed getControllingPlayer twice plus pinned record chain and rowed 0x005EEAC6 then pinned 0x005EE8DD; +0x28 finder.
class Object;
class Player;

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Object
{
public:
	Player *getControllingPlayer() const;
};

struct Rva002A8AB1Record
{
public:
	void *rva002C6ACB();
};

class Rva002A8F24
{
public:
	struct Rva002A8AB1Record *rva002A8AB1(void *player);
};

extern Rva002A8F24 *g_00DFEEF8;

class Rva005EEAC6
{
public:
	bool rva005EEAC6(Player *a1, Player *a2, Coord3D *out);
};

class Rva005EE816
{
public:
	bool rva005EE8DD(const Coord3D *pos, Object *source);
	bool rva005D7D93(Object *source);
private:
	char m_pad00[0x28];
	Rva005EEAC6 m_28;
};

bool Rva005EE816::rva005D7D93(Object *source)
{
	Player *p1 = source->getControllingPlayer();
	Rva002A8AB1Record *rec = g_00DFEEF8->rva002A8AB1(p1);
	void *v = rec->rva002C6ACB();
	if (v == 0)
		return false;
	Coord3D pos;
	pos.x = 0.0f;
	pos.y = 0.0f;
	pos.z = 0.0f;
	if (m_28.rva005EEAC6((Player *)v, source->getControllingPlayer(), &pos))
		return rva005EE8DD(&pos, source);
	return false;
}
