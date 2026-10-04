// cl: /O1 /DNDEBUG /MD /EHsc /arch:SSE
//
// DominateEnemySpecialPower's slot 17 (0x004CCBDF; SpecialAbilityUpdate's
// slot 17 first) and its per-target helper (0x004CCB0E), beside the matched
// DominateEnemySpecialPower ctor 0x004CC988 and pool key 0x004CC9DF.
//
//   0x004CCBDF  the object 0x00049DC5 finds for +0x40 is dominated directly
//               (flag true); without one, every alive object other than the
//               owner, relationship 1 to it and passing the 0x002616EB
//               status filter (status 38 set, none cleared) within the
//               module data's +0xC8 radius of +0x44 is (flag false; BFME2's
//               partition filter chain, the view AIStructureCreepTactic.cpp
//               documents), then FXList::doFXPos of the data's +0xCC there
//   0x004CCB0E  skip the owner, its team, what the data's +0xD8 object
//               filter refuses for the owner's player and status 2; prefer
//               the 0x00049DC5 object of +0x78 with template bit 13 (only
//               when the flag allows); skip status bit 6; then
//               Object::rva00298979(owner, data +0xD4) and the data's +0xD0
//               FX through the 0x0029439D result's slot 123, else
//               FXList::doFXObj
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

// vftable 0x00BFBC90, allow 0x00260EB1, getPlayerMask 0x00260E6A: the object,
// relationship flags and whether a hit allows.
class Rva00260EB1Filter : public Rva000421C8
{
public:
	Rva00260EB1Filter(const Object *obj, int flags, bool match)
		: m_obj(obj), m_flags(flags), m_match(match) {}
	virtual bool allow(Object *obj);
	virtual int getPlayerMask();
	const Object *m_obj;
	int m_flags;
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
	OBJECT_STATUS_RVA004CCBDF_38 = 38
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

class Matrix3D;
class FXList
{
public:
	static void doFXObj(const FXList *fx, const Object *primary, const Object *secondary);	// 0x000B2235
	static void doFXPos(const FXList *fx, const Coord3D *primary, const Matrix3D *mtx,
		float speed, const Coord3D *secondary);	// 0x00094C29
};

// What 0x0029439D returns: slot 123 takes an FXList.
template <int N> class Rva004CCB0ESlots : public Rva004CCB0ESlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class Rva004CCB0ESlots<0>
{
};
class Rva004CCB0EResult : public Rva004CCB0ESlots<123>
{
public:
	virtual void rva004CCB0ESlot123(const FXList *fx) = 0;
};

class Rva2225E0Filter
{
public:
	bool accepts(Object *obj, Player *player);	// 0x00362437
};

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
	void *rva0029439D();	// 0x0029439D
	void rva00298979(Object *source, bool flag);	// 0x00298979
	bool rva004CCB0EBit6() const { return (m_94 & 0x40) != 0; }
	char m_pad000[0x04];
	const ThingTemplate *m_template;	// +0x04
	char m_pad008[0x78 - 0x08];
	ObjectID m_78;		// +0x78
	char m_pad07C[0x94 - 0x7C];
	unsigned m_94;		// +0x94 status bits (bit 6 tested)
	char m_pad098[0x304 - 0x98];
	void *m_304;		// +0x304 the team
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);	// 0x00049DC5
};
extern GameLogic *TheGameLogic;

class DominateEnemySpecialPowerModuleData
{
public:
	char m_pad00[0xC8];
	float m_C8;			// +0xC8 the radius
	const FXList *m_CC;		// +0xCC
	const FXList *m_D0;		// +0xD0
	bool m_D4;			// +0xD4
	char m_padD5[3];
	Rva2225E0Filter m_D8;		// +0xD8
};

class SpecialAbilityUpdate
{
public:
	virtual void rva0045108D();	// slot 17 (0x0045108D)
protected:
	const void *m_moduleData;	// +0x04
	Object *m_object;		// +0x08
};

class DominateEnemySpecialPower : public SpecialAbilityUpdate
{
public:
	virtual void rva0045108D();
	void rva004CCB0E(Object *target, Object *owner, const DominateEnemySpecialPowerModuleData *data, bool flag);
private:
	const DominateEnemySpecialPowerModuleData *getDominateEnemySpecialPowerModuleData() const
	{
		return (const DominateEnemySpecialPowerModuleData *)m_moduleData;
	}
	char m_pad0C[0x40 - 0x0C];
	ObjectID m_40;		// +0x40
	Coord3D m_44;		// +0x44
};

void DominateEnemySpecialPower::rva004CCB0E(Object *target, Object *owner,
	const DominateEnemySpecialPowerModuleData *data, bool flag)
{
	if (target == owner)
		return;
	if (target->m_304 == owner->m_304)
		return;
	if (!((Rva2225E0Filter &)data->m_D8).accepts(target, owner->getControllingPlayer()))
		return;
	if (target->testStatus((ObjectStatusTypes)2))
		return;
	Object *other = TheGameLogic->findObjectByID(target->m_78);
	if (other && (other->m_template->m_114 & 0x2000)) {
		if (!flag)
			return;
		target = other;
	}
	if (target->rva004CCB0EBit6())
		return;
	if (data->m_D4)
		target->rva00298979(owner, true);
	else
		target->rva00298979(owner, false);
	Rva004CCB0EResult *result = (Rva004CCB0EResult *)target->rva0029439D();
	if (result)
		result->rva004CCB0ESlot123(data->m_D0);
	else
		FXList::doFXObj(data->m_D0, target, 0);
}

void DominateEnemySpecialPower::rva0045108D()
{
	SpecialAbilityUpdate::rva0045108D();
	const DominateEnemySpecialPowerModuleData *data = getDominateEnemySpecialPowerModuleData();
	Object *owner = m_object;
	Object *target = TheGameLogic->findObjectByID(m_40);
	if (target) {
		rva004CCB0E(target, owner, data, true);
		return;
	}
	ObjectStatusMask bits;
	BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(&m_44, data->m_C8, 0,
		Rva00260EB1Filter(owner, 1, false).link(&Rva0026119DFilter())->link(&Rva002611BFFilter(owner))
			->link(&Rva002FDF1C(*(BfmeObject872Header *)bits.Rva0023DA79(0, OBJECT_STATUS_RVA004CCBDF_38),
				*(BfmeObject872Header *)&ObjectStatusMaskNone())), 1);
	Object *other;
	while ((other = hits.next()) != 0)
		rva004CCB0E(other, owner, data, false);
	FXList::doFXPos(data->m_CC, &m_44, 0, 0.0f, 0);
}
