// cl: /O1 /DNDEBUG /MD /GX /arch:SSE
//
// RousingSpeechUpdate::update, retail 0x004AD019 (213 bytes): slot 0 of the
// vtable 0x00C54FD8 that the matched RousingSpeechUpdate dtor installs at +0x10
// (UpdateModuleInterface), compiled with that subobject this. Same scheme as
// the matched GloriousChargeUpdate::update 0x004AD710: run the +0x88 ObjectID
// list helper 0x004ACF1D on the full object (pinned), start the speech through
// virtual primary slot 15 (the matched override 0x004ACE11) with the expiry
// frame at +0x8C, then while the frame is not reached and the +0x94 radius is
// below the data cap +0xC8, grow it (+0x94 takes the +0x98 value, +0x98 grows by
// data +0xE0 capped at +0xC8, when the +0xDC flag is set), call virtual slot 17
// and return data +0xD0; afterwards clear condition bit 6*32+15 and sleep
// forever. The cap test is written !(m_94 >= cap), the form retail compares.
// RousingSpeechUpdate::rva004AD176, retail 0x004AD176 (313 bytes): the
// non-virtual helper the slot-17 override 0x004AD399 calls, GloriousCharge's
// 0x004AD7B6 with two more filters: push the ID of every other object within
// the +0x98 radius that is allied (relationship 4, 0x00260EB1), passes
// 0x002614EC over the data +0xF4 and the controlling player, is alive, passes
// 0x002611BF for this object and this unit's 0x004ACDAC (+0x94 radius round
// the object) onto the +0x88 list (0x002A1B6F). /GX for the filter
// temporaries.
// Model as in GloriousChargeUpdateUpdate.cpp; condition word array at
// Object+0x10C with masked-word accessors.

class Drawable;
class Rva0010CConditionBits
{
public:
	unsigned int test(int bit) const
	{
		return m_words[bit >> 5] & (1U << (bit & 0x1f));
	}
	void clear(int bit)
	{
		m_words[bit >> 5] &= ~(1U << (bit & 0x1f));
	}
private:
	unsigned int m_words[20];
};
enum ObjectID
{
	INVALID_ID = 0
};
enum KindOfType
{
	KINDOF_FIRST = 0
};
struct Coord3D
{
	float x;
	float y;
	float z;
};
class Player;
class Object
{
public:
	void rva0028AE6D();
	Drawable *getDrawable() const;
	bool isKindOf(KindOfType t) const;
	Player *getControllingPlayer() const; // 0x0028AFA9
	const Coord3D *getPosition() const { return &m_pos; }
	ObjectID getID() const { return m_id; }
	unsigned char m_pad000[0x38];
	Coord3D m_pos; // +0x38
	unsigned char m_pad044[0x74 - 0x44];
	ObjectID m_id; // +0x74
	unsigned char m_pad078[0x10C - 0x78];
	Rva0010CConditionBits m_conditionBits; // +0x10C
	unsigned char m_pad15C[0x44C - 0x15C];
	int m_44C; // +0x44C
};
static __forceinline void clearModelConditionBit(Object *object, int bit)
{
	if (object->m_conditionBits.test(bit) != 0)
	{
		object->m_conditionBits.clear(bit);
		object->rva0028AE6D();
	}
}
class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
	unsigned int getFrame() const { return m_frame; }
private:
	unsigned char m_pad[0x40];
	unsigned int m_frame; // +0x40
};
extern GameLogic *TheGameLogic;
class Rva00270619
{
public:
	void Rva00270619Clear(int bit);
};
struct Rva004AD613Node
{
	Rva004AD613Node *m_next;
	Rva004AD613Node *m_prev;
	ObjectID m_id;
};
struct Rva004AD613Iterator
{
	Rva004AD613Node *m_node;
	ObjectID &operator*() const { return m_node->m_id; }
	Rva004AD613Iterator &operator++() { m_node = m_node->m_next; return *this; }
	bool operator!=(const Rva004AD613Iterator &other) const { return m_node != other.m_node; }
};
class Rva0029FB3BMember
{
public:
	bool empty() const { return m_head->m_next == m_head; }
	Rva004AD613Iterator begin() const { Rva004AD613Iterator it; it.m_node = m_head->m_next; return it; }
	Rva004AD613Iterator end() const { Rva004AD613Iterator it; it.m_node = m_head; return it; }
	void reset();
	void push_back(const ObjectID &id);	// 0x002A1B6F
	Rva004AD613Node *m_head;
};
// BFME2's partition filters (the view AIStructureCreepTactic.cpp documents):
// a vptr, the +0x04 link to the next filter (0x00625790), then each filter's
// own members.
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
// vftable 0x00BFBC90, allow 0x00260EB1: the object, relationship flags and
// whether a hit allows.
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
// vftable 0x00BF91BC, allow 0x002611BF: +0x08 an object.
class Rva002611BFFilter : public Rva000421C8
{
public:
	Rva002611BFFilter(const Object *obj) : m_obj(obj) {}
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
// vftable 0x00C54EB4, allow 0x004ACDAC (this unit's own filter): +0x08 a
// radius, +0x0C a centre.
class Rva004ACDACFilter : public Rva000421C8
{
public:
	Rva004ACDACFilter(float radius, const Coord3D *centre)
		: m_radius(radius), m_centre(centre) {}
	virtual bool allow(Object *obj);
	float m_radius;
	const Coord3D *m_centre;
};
#pragma comment(linker, "/alternatename:?getPlayerMask@Rva000421C8@@UAEHXZ=?Get_File_Handle@FileClass@@UAEPAXXZ")
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
class Thing;
class ModuleData;
class BehaviorModule
{
public:
	virtual ~BehaviorModule();
protected:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};
class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};
enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};
class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
};
class UpdateModule : public BehaviorModule, public BehaviorModuleInterface, public UpdateModuleInterface
{
protected:
	unsigned int m_14;
	int m_18;
	int m_1C;
};
class SpecialPowerUpdateInterface
{
public:
	virtual void specialPowerUpdateAnchor();
};
// Primary-vtable slots 1..17 of SpecialAbilityUpdate (vtable 0x00C3FBA8);
// only the positions of slots 15 and 17 matter to this unit.
class SpecialAbilityUpdate : public UpdateModule, public SpecialPowerUpdateInterface
{
public:
	virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06();
	virtual void slot07(); virtual void slot08(); virtual void slot09();
	virtual void slot10(); virtual void slot11(); virtual void slot12();
	virtual void slot13(); virtual void slot14();
	virtual void slot15(); // 0x00450D9A, GloriousChargeUpdate 0x004AD554
	virtual void slot16();
	virtual void slot17(); // 0x0045108D, GloriousChargeUpdate 0x004AD8E3
private:
	unsigned char m_pad24[0x88 - 0x24];
};
class RousingSpeechUpdateModuleData
{
public:
	unsigned char m_pad[0xC8];
	float m_C8; // +0xC8
	unsigned int m_CC; // +0xCC
	int m_D0; // +0xD0
	unsigned char m_padD4[0xDC - 0xD4];
	bool m_DC; // +0xDC
	float m_E0; // +0xE0
	unsigned char m_padE4[0xF4 - 0xE4];
	unsigned char m_F4[4]; // +0xF4
};
class RousingSpeechUpdate : public SpecialAbilityUpdate
{
public:
	void rva004ACF1D();
	void rva004AD176();
	virtual UpdateSleepTime update();
private:
	const RousingSpeechUpdateModuleData *getRousingSpeechData() const
	{
		return (const RousingSpeechUpdateModuleData *)m_moduleData;
	}
	Rva0029FB3BMember m_88; // +0x88
	unsigned int m_8C; // +0x8C
	bool m_90; // +0x90
	float m_94; // +0x94
	float m_98; // +0x98
};
UpdateSleepTime RousingSpeechUpdate::update()
{
	rva004ACF1D();
	if (!m_90)
	{
		slot15();
		m_8C = getRousingSpeechData()->m_CC + TheGameLogic->getFrame();
		m_90 = true;
	}
	const RousingSpeechUpdateModuleData *data = getRousingSpeechData();
	if (TheGameLogic->getFrame() < m_8C && !(m_94 >= data->m_C8))
	{
		if (data->m_DC)
		{
			m_94 = m_98;
			m_98 += data->m_E0;
			if (m_98 > data->m_C8)
				m_98 = data->m_C8;
		}
		slot17();
		return (UpdateSleepTime)getRousingSpeechData()->m_D0;
	}
	m_90 = false;
	clearModelConditionBit(m_object, 6 * 32 + 15);
	return UPDATE_SLEEP_FOREVER;
}
void RousingSpeechUpdate::rva004AD176()
{
	const RousingSpeechUpdateModuleData *data = getRousingSpeechData();
	Object *self = m_object;
	BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(self->getPosition(), m_98, 0,
		Rva00260EB1Filter(self, 4, false).link(Rva002614ECFilter(data->m_F4, self->getControllingPlayer(), true)
			.link(Rva0026119DFilter().link(Rva002611BFFilter(self).link(&Rva004ACDACFilter(m_94, self->getPosition()))))), 1);
	for (Object *obj = hits.next(); obj; obj = hits.next()) {
		if (obj == self)
			continue;
		m_88.push_back(obj->getID());
	}
}
