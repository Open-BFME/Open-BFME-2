// cl: /O1 /MD
//
// ?getRelationship@Object@@QBE?AW4Relationship@@PBV1@@Z @0x0028D156 253B,
// the name 19 matched callers pin. Every callee is rowed. Splashes through template flags at
// +0x108/+0x10E/+0x115/+0x118, the +0x130 bit13 gate, the rva0028C197 double
// call plus vtable slot 0x110 provider, the current-weapon contains(6)
// gate, then Team relationship fallback. Layout from Object siblings:
// this+0x4 template, +0x74 id, +0x130 flags, +0x304 team, +0x438 bits.
// Callees: rva0028C197, getCurrentWeapon, Rva002CA9CA::contains,
// isKindOf(0xCE), Team::getRelationship. All rowed.

enum KindOfType
{
	KIND_206 = 206
};

enum Relationship
{
	ENEMIES = 0,
	NEUTRAL,
	ALLIES
};

enum WeaponSlotType
{
	WEAPONSLOT_PRIMARY = 0
};

class Object;
class Team;
class Weapon;
class Rva002CA9CA;

class ObjectTemplate
{
public:
	char m_pad00[0x108];
	unsigned int m_field108;
	char m_pad10C[2];
	unsigned char m_byte10E;
	char m_pad10F[6];
	unsigned char m_byte115;
	char m_pad116[2];
	unsigned int m_field118;
};

class Team
{
public:
	Relationship getRelationship(const Team *other) const;
};

class Rva002CA9CA
{
public:
	bool rva002CA9CA(int id, const void *arg);
};

class Weapon
{
public:
	char m_pad00[4];
	Rva002CA9CA *m_parent;
};

class MidProvider
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
	virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
	virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
	virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
	virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
	virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43();
	virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47();
	virtual void v48(); virtual void v49(); virtual void v50(); virtual void v51();
	virtual void v52(); virtual void v53(); virtual void v54(); virtual void v55();
	virtual void v56(); virtual void v57(); virtual void v58(); virtual void v59();
	virtual void v60(); virtual void v61(); virtual void v62(); virtual void v63();
	virtual void v64(); virtual void v65(); virtual void v66(); virtual void v67();
	virtual Object *v68();
};

class Object
{
public:
	void *rva0028C197() const;
	const Weapon *getCurrentWeapon(WeaponSlotType *slot) const;
	bool isKindOf(KindOfType t) const;
	Relationship getRelationship(const Object *other) const;
	bool testStatusBit13() const { return m_130b13; }

private:
	char m_pad00[4];
	ObjectTemplate *m_template;
	char m_pad08[0x74 - 8];
	int m_74;
	char m_pad78[0x130 - 0x78];
	unsigned int m_130lo : 13;
	unsigned int m_130b13 : 1;
	unsigned int m_130hi : 18;
	char m_pad134[0x304 - 0x134];
	Team *m_team304;
	char m_pad308[0x438 - 0x308];
	unsigned char m_byte438;
};

Relationship Object::getRelationship(const Object *other) const
{
	if (other != 0)
	{
		ObjectTemplate *tOther = other->m_template;
		if ((tOther->m_byte10E & 0x80) != 0 && (tOther->m_field108 & 4) != 0)
		{
			ObjectTemplate *tThis = m_template;
			unsigned int flags = tThis->m_field118;
			if ((flags & 0x1000) != 0)
			{
				if (testStatusBit13())
					goto ret0;
			}
			Object *cand;
			if ((flags & 0x20) != 0)
			{
				cand = (Object *)this;
			}
			else
			{
				if ((tThis->m_byte115 & 0x20) == 0)
					goto team;
				void *p1 = rva0028C197();
				if (p1 == 0)
					goto team;
				void *p2 = rva0028C197();
				Object *mid = ((MidProvider *)p2)->v68();
				if (mid == 0)
					goto team;
				if ((mid->m_template->m_field118 & 0x20) == 0)
					goto team;
				cand = mid;
			}
			if (cand == 0)
				goto team;
			const Weapon *w = cand->getCurrentWeapon(0);
			if (w == 0)
				goto team;
			if (!w->m_parent->rva002CA9CA(6, w))
				goto team;
ret0:
			return ENEMIES;
		}
	}
team:
	{
		Team *t = m_team304;
		if (t != 0 && other != 0 && (m_byte438 & 2) == 0)
		{
			if ((other->m_byte438 & 2) != 0)
				return ALLIES;
			if (isKindOf(KIND_206))
			{
				if (m_74 != other->m_74)
					return ENEMIES;
			}
			return t->getRelationship(other->m_team304);
		}
		return NEUTRAL;
	}
}
