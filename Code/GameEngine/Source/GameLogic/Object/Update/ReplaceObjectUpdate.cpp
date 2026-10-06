// cl: /MD /GX
//
// ReplaceObjectUpdate.cpp (the unit 0x004B2A9D's random-range assert names).
//
//   0x004B2D28  slot 17 of ReplaceObjectUpdate's vftable 0x00C56BB0 (slot 0 the
//               deleting dtor 0x004B2A44): after SpecialAbilityUpdate's slot
//               17 (0x0045108D), for each non-null entry of the module data's
//               +0xC8..+0xCC array, walk the alive objects within the data's
//               +0xD4 radius of the +0x44 point that pass 0x002614DF for the
//               object and 0x002614EC for the entry and the controlling
//               player, and hand each whose +0x274 object is null or passes
//               0x0028C197 to 0x004B2C00 with the entry
//
//   0x004B2A60  kill the given object on behalf of this module's object (a
//               DamageInfo with the +0x08 source ID and the +0x24 flag set)
//               and destroy it
//
// The filters are BFME2's partition filter chain (the view
// AIStructureCreepTactic.cpp documents).

class Object;
class Player;

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

// vftable 0x00BFAD10, allow 0x0026119D: not effectively dead.
class Rva0026119DFilter : public Rva000421C8
{
public:
	virtual bool allow(Object *obj);
};

// vftable 0x00C07190, allow 0x002614DF: +0x08 an object.
class Rva002614DFFilter : public Rva000421C8
{
public:
	Rva002614DFFilter(const Object *obj) : m_obj(obj) {}
	virtual bool allow(Object *obj);
	const Object *m_obj;
};

// vftable 0x00BCECF0, allow 0x002614EC: +0x08 what to compare, +0x0C a
// player, +0x10 whether a hit allows.
class Rva002614ECFilter : public Rva000421C8
{
public:
	Rva002614ECFilter(const void *what, Player *player, bool match)
		: m_what(what), m_player(player), m_match(match) {}
	virtual bool allow(Object *obj);
	const void *m_what;
	Player *m_player;
	bool m_match;
};

#pragma comment(linker, "/alternatename:?getPlayerMask@Rva000421C8@@UAEHXZ=?Get_File_Handle@FileClass@@UAEPAXXZ")

struct Coord3D
{
	float x;
	float y;
	float z;
};

enum ObjectID
{
	INVALID_ID = 0
};

class DamageInfo
{
public:
	DamageInfo();		// 0x00263895
	char m_pad00[0x08];
	ObjectID m_sourceID;	// +0x08
	char m_pad0C[0x24 - 0x0C];
	bool m_24;		// +0x24
	char m_pad25[0x7C - 0x25];
};

class Object
{
public:
	Player *getControllingPlayer() const;	// 0x0028AFA9
	void *rva0028C197() const;		// 0x0028C197
	void attemptDamage(DamageInfo *info);	// 0x0029848E
	ObjectID getID() const { return m_id; }
	char m_pad000[0x38];
	Coord3D m_pos;		// +0x38
	float m_44;		// +0x44
	char m_pad048[0x74 - 0x48];
	ObjectID m_id;		// +0x74
	char m_pad078[0x274 - 0x78];
	Object *m_274;		// +0x274
};

class GameLogic
{
public:
	void destroyObject(Object *obj);	// 0x00242C09
};
extern GameLogic *TheGameLogic;

struct BfmeWideResult
{
	Object *next() throw();	// 0x00045623
	~BfmeWideResult();	// 0x0004AA28
	void *m_value;
};

class PartitionManager
{
public:
	BfmeWideResult iterateObjectsInRange(const Coord3D *pos, float radius, int distCalc,
		Rva000421C8 *filters, int order);	// 0x00625610
};
extern PartitionManager *ThePartitionManager;

// A replacement entry (0x004B2A9D picks one of its names at random).
class Rva004B2A9D;

class ReplaceObjectUpdateModuleData
{
public:
	char m_pad00[0xC8];
	Rva004B2A9D **m_C8;	// +0xC8 the entries
	Rva004B2A9D **m_CC;	// +0xCC their end
	char m_padD0[4];
	float m_D4;		// +0xD4 the radius
};

class SpecialAbilityUpdate
{
public:
	virtual void rva0045108D();	// slot 17 (0x0045108D)
	Object *getObject() const { return m_object; }
protected:
	const void *m_moduleData;	// +0x04
	Object *m_object;		// +0x08
};

class ReplaceObjectUpdate : public SpecialAbilityUpdate
{
public:
	virtual void rva004B2D28();
	void rva004B2C00(Object *obj, Rva004B2A9D *entry);	// 0x004B2C00
	void rva004B2A60(Object *obj);
private:
	const ReplaceObjectUpdateModuleData *getReplaceObjectData() const
	{
		return (const ReplaceObjectUpdateModuleData *)m_moduleData;
	}
	char m_pad0C[0x44 - 0x0C];
	Coord3D m_44;		// +0x44
};

void ReplaceObjectUpdate::rva004B2A60(Object *obj)
{
	DamageInfo info;
	info.m_24 = true;
	info.m_sourceID = getObject()->getID();
	obj->attemptDamage(&info);
	TheGameLogic->destroyObject(obj);
}
void ReplaceObjectUpdate::rva004B2D28()
{
	SpecialAbilityUpdate::rva0045108D();
	if (getObject()) {
		const ReplaceObjectUpdateModuleData *data = getReplaceObjectData();
		for (Rva004B2A9D **it = data->m_C8; it != data->m_CC; ++it) {
			Rva004B2A9D *entry = *it;
			if (entry) {
				BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(&m_44, data->m_D4, 0,
					Rva0026119DFilter().link(Rva002614DFFilter(m_object).link(&Rva002614ECFilter(entry, m_object->getControllingPlayer(), true))), 0);
				Object *obj;
				while ((obj = hits.next()) != 0) {
					Object *other = obj->m_274;
					if (!other || other->rva0028C197())
						rva004B2C00(obj, entry);
				}
			}
		}
	}
}
