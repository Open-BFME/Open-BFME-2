// ?rva0045108D@StoreObjectsSpecialPower@@UAEXXZ
// partial score=0.97 date=2026-10-04
// cl: /O1 /DNDEBUG /MD /EHsc /arch:SSE
#include <string.h>

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

// vftable 0x00BF91BC, allow 0x002611BF.
class Rva002611BFFilter : public Rva000421C8
{
public:
	Rva002611BFFilter(const Object *obj) : m_obj(obj) {}
	virtual bool allow(Object *obj);
	const Object *m_obj;
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

// An ObjectStatusMaskType (16 bytes) as the status filter copies it.
class BfmeObject872Header
{
	char m_bytes[16];
public:
	BfmeObject872Header(const BfmeObject872Header &other);
};

// vftable 0x00C071CC, allow 0x002616EB: two status masks.
class Rva002FDF1C : public Rva000421C8
{
public:
	Rva002FDF1C(const BfmeObject872Header &a, const BfmeObject872Header &b);	// 0x002FDF1C
	virtual bool allow(Object *obj);
	BfmeObject872Header m_8;
	BfmeObject872Header m_18;
};

#pragma comment(linker, "/alternatename:?getPlayerMask@Rva000421C8@@UAEHXZ=?Get_File_Handle@FileClass@@UAEPAXXZ")

enum ObjectStatusTypes
{
	OBJECT_STATUS_RVA004CDA49_3 = 3,
	OBJECT_STATUS_RVA004CDA49_38 = 38
};

// 0x0023DA79 clears the mask and sets one bit (its first argument unused).
struct ObjectStatusMask
{
	ObjectStatusMask *Rva0023DA79(int reserved, ObjectStatusTypes bit);	// 0x0023DA79
	int m_bits[4];
};

struct ObjectStatusMaskNone : public ObjectStatusMask
{
	ObjectStatusMaskNone() { memset(this, 0, sizeof(*this)); }
};

struct Coord3D
{
	float x;
	float y;
	float z;
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

enum ObjectID
{
	INVALID_ID = 0
};

namespace _STL {
template <class T> class allocator;
template <class T, class A> class vector
{
public:
	T *begin() { return _M_start; }
	T *end() { return _M_finish; }
	void clear() { erase(begin(), end()); }
	T *erase(T *first, T *last);	// 0x00532803
	void push_back(const T &x);	// 0x002E01C6
	T *_M_start;
	T *_M_finish;
	T *_M_end_of_storage;
};
}

class ThingTemplate
{
public:
	char m_pad000[0x114];
	unsigned m_114;		// +0x114 (bit 13 tested)
};

class Object
{
public:
	Player *getControllingPlayer() const;	// 0x0028AFA9
	bool testStatus(ObjectStatusTypes bit) const;	// 0x0004E536
	ObjectID getID() const { return m_74; }
	char m_pad000[0x04];
	const ThingTemplate *m_template;	// +0x04
	char m_pad008[0x74 - 0x08];
	ObjectID m_74;		// +0x74
	ObjectID m_78;		// +0x78
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);	// 0x00049DC5
};
extern GameLogic *TheGameLogic;

class Overridable
{
public:
	const Overridable *friend_getFinalOverride() const;	// 0x00288609
};

class SpecialPowerTemplate : public Overridable
{
public:
	const void *getObjectFilter() const
	{
		return &((const SpecialPowerTemplate *)friend_getFinalOverride())->m_60;
	}
	char m_pad00[0x60];
	int m_60;	// +0x60 the object filter
};

// What 0x0044E633 returns: slot 6 is the special power template.
class Rva004CDA49Power
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual const SpecialPowerTemplate *getSpecialPowerTemplate() const;
};

class StoreObjectsSpecialPowerModuleData
{
public:
	char m_pad00[0xC8];
	float m_C8;	// +0xC8 the radius
};

class SpecialAbilityUpdate
{
public:
	virtual void rva0045108D();	// slot 17 (0x0045108D)
	Rva004CDA49Power *rva0044E633();	// 0x0044E633
protected:
	const void *m_moduleData;	// +0x04
	Object *m_object;		// +0x08
};

class StoreObjectsSpecialPower : public SpecialAbilityUpdate
{
public:
	virtual void rva0045108D();
private:
	const StoreObjectsSpecialPowerModuleData *getStoreObjectsSpecialPowerModuleData() const
	{
		return (const StoreObjectsSpecialPowerModuleData *)m_moduleData;
	}
	char m_pad0C[0x44 - 0x0C];
	Coord3D m_44;		// +0x44
	char m_pad50[0x88 - 0x50];
	_STL::vector<ObjectID, _STL::allocator<ObjectID> > m_88;	// +0x88
};

void StoreObjectsSpecialPower::rva0045108D()
{
	SpecialAbilityUpdate::rva0045108D();
	const StoreObjectsSpecialPowerModuleData *data = getStoreObjectsSpecialPowerModuleData();
	Object *owner = m_object;
	const void *filter = rva0044E633()->getSpecialPowerTemplate()->getObjectFilter();
	m_88.clear();
	ObjectStatusMask bits;
	BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(&m_44, data->m_C8, 0,
		Rva002614DFFilter(owner).link(Rva0026119DFilter().link(Rva002611BFFilter(owner).link(
			Rva002614ECFilter(filter, owner->getControllingPlayer(), true).link(
				&Rva002FDF1C(*(BfmeObject872Header *)bits.Rva0023DA79(0, OBJECT_STATUS_RVA004CDA49_38),
					*(BfmeObject872Header *)&ObjectStatusMaskNone()))))), 1);
	Object *other;
	while ((other = hits.next()) != 0) {
		Object *rider = TheGameLogic->findObjectByID(other->m_78);
		if (rider && (rider->m_template->m_114 & 0x2000))
			continue;
		if (other->testStatus(OBJECT_STATUS_RVA004CDA49_3))
			continue;
		m_88.push_back(other->getID());
	}
}
