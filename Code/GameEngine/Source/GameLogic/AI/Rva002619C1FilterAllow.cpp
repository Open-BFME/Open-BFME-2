// cl: /O1 /DNDEBUG /MD /EHsc /arch:SSE
// ?allow@Rva002619C1Filter@@UAE_NPAVObject@@@Z @0x002619C1 250B
// Partition filter allow (vftable 0x00C07150 slot 1, Rva002619C1Filter):
// line-of-sight/attack check using rowed getCurrentWeapon, Pathfinder
// rva002EE96B + isViewBlockedByObstacle, GeometryInfo heights and the
// TerrainLogic slot 0x3c test. Evidence: vftable pin
// ??_7Rva002619C1Filter@@6B@ at 0x00C07150 slot 1, stack-constructed
// filter at 0x003430EE with that vtable, callers 0x00343106 0x0044F4D8.
struct Coord3D
{
	float x;
	float y;
	float z;
};

class ObjectTemplate
{
public:
	char m_pad00[0x108];
	unsigned char m_108;
	char m_pad109[0x10F - 0x109];
	unsigned char m_10F;
};

class GeometryInfo
{
public:
	float getMaxHeightAbovePosition() const;
};

class Weapon;
enum WeaponSlotType
{
	WEAPONSLOT_FIRST = 0
};

class Object
{
public:
	virtual void dummy();
	const Weapon *getCurrentWeapon(WeaponSlotType *slot) const;
	ObjectTemplate *m_template;
	char m_pad08[0x38 - 8];
	Coord3D m_pos;
	char m_pad44[0xA8 - 0x44];
	GeometryInfo m_geo;
};

class Pathfinder
{
public:
	int rva002EE96B(Coord3D *a, const Coord3D *b);
	bool isViewBlockedByObstacle(const Object *a, const Object *b);
};

class AI
{
public:
	char m_pad00[0x10];
	Pathfinder *m_pathfinder;
};

extern class AI *TheAI;

class TerrainLogic
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual bool slot15(Coord3D *a, Coord3D *b);
};

extern TerrainLogic *TheTerrainLogic;

class Rva000421C8
{
public:
	virtual ~Rva000421C8();
	virtual bool allow(Object *obj);
	virtual int getPlayerMask();
	Rva000421C8 *m_next;
};

class Rva002619C1Filter : public Rva000421C8
{
public:
	virtual bool allow(Object *obj);
	const Object *m_obj;
};

bool Rva002619C1Filter::allow(Object *obj)
{
	if (m_obj->getCurrentWeapon(0) == 0) {
		const Coord3D *spos = &m_obj->m_pos;
		Coord3D start;
		start.x = spos->x;
		start.y = spos->y;
		start.z = spos->z;
		Coord3D end;
		end.x = obj->m_pos.x;
		end.y = obj->m_pos.y;
		end.z = obj->m_pos.z;
		if (obj->m_template->m_10F & 0x10) {
			AI *ai = TheAI;
			if (ai != 0 && ai->m_pathfinder != 0)
				ai->m_pathfinder->rva002EE96B(&end, &start);
		}
		if ((m_obj->m_template->m_108 & 0x80) == 0)
			start.z += m_obj->m_geo.getMaxHeightAbovePosition();
		end.z += obj->m_geo.getMaxHeightAbovePosition();
		if (!TheTerrainLogic->slot15(&start, &end))
			return false;
	}
	AI *ai2 = TheAI;
	if (ai2 == 0)
		goto ret_true;
	{
		Pathfinder *pf = ai2->m_pathfinder;
		if (pf->isViewBlockedByObstacle(m_obj, obj))
			goto ret_false;
		goto ret_true;
	}
ret_false:
	return false;
ret_true:
	return true;
}
