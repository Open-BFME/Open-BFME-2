// cl: /O1 /MD /GX /arch:SSE
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

class Object
{
public:
	Player *getControllingPlayer() const;	// 0x0028AFA9
	void *rva0028C197() const;		// 0x0028C197
	char m_pad000[0x274];
	Object *m_274;		// +0x274
};

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

// A replacement entry (0x004B2A9D picks one of its ints at random).
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
private:
	const ReplaceObjectUpdateModuleData *getReplaceObjectData() const
	{
		return (const ReplaceObjectUpdateModuleData *)m_moduleData;
	}
	char m_pad0C[0x44 - 0x0C];
	Coord3D m_44;		// +0x44
};

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
