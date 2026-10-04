// cl: /O1 /DNDEBUG /MD /GX
//
// GloriousChargeUpdate methods (retail GloriousChargeUpdate.cpp order).
// Retail 0x004AD613 (109 bytes): rva004AD613, the non-virtual helper that
// update() calls on the full object. It walks the ObjectID list at +0x88 (the
// pooled list member Rva0029FB3BMember that the matched ctor 0x004AD680 builds
// and its matched reset 0x0026549E empties): for each object still alive,
// clear condition bit 6*32+9, zero its +0x44C dword and clear bit 8 of its
// Drawable through the matched Rva00270619Clear; then reset the list. Retail
// keeps both the empty() test and the loop entry test, which cl only does when
// the walk goes through an iterator struct (as with STLport list iterators);
// raw node pointers let it fold the two tests.
// Retail 0x004AD710 (166 bytes): update(), slot 0 of the vtable 0x00C55108 the
// matched GloriousChargeUpdate dtor installs at +0x10 (UpdateModuleInterface),
// compiled with that subobject this. Starts the charge when bit 0xD6 of the
// Object +0x10C word array is set (matched 0x0006F039, ledgered as
// Object::isKindOf; called on the Object) (virtual slot 15 of the primary vtable, the matched override
// 0x004AD554, sets condition bit 6*32+15), keeps it running until the frame at
// +0x8C (virtual slot 17 each frame) and then clears the bit and Drawable bit
// 0x10. Returns the module data +0xD0 value while running, else
// UPDATE_SLEEP_FOREVER. Slot names are not established; slot positions come
// from the SpecialAbilityUpdate vtable 0x00C3FBA8.
//
// Retail 0x004AD7B6 (218 bytes): rva004AD7B6, the non-virtual helper the
// slot-17 override 0x004AD8E3 calls: push the ID of every other object
// within the module data's +0xC8 radius that is allied (relationship 4,
// 0x00260EB1), alive and passes 0x002611BF for this object onto the +0x88
// list (0x002A1B6F). /GX for the filter temporaries.
//
// Model-condition bits: the Object word array starts at +0x10C (see
// GloriousChargeUpdateRva004AD554.cpp); masked-word accessors in a free
// __forceinline helper call the pinned notifier 0x0028AE6D on a change.

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
class Object
{
public:
	void rva0028AE6D();
	Drawable *getDrawable() const;
	bool isKindOf(KindOfType t) const;
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
class GloriousChargeUpdateModuleData
{
public:
	unsigned char m_pad[0xC8];
	float m_C8; // +0xC8
	unsigned int m_CC; // +0xCC
	int m_D0; // +0xD0
};
class GloriousChargeUpdate : public SpecialAbilityUpdate
{
public:
	void rva004AD613();
	void rva004AD7B6();
	virtual UpdateSleepTime update();
private:
	const GloriousChargeUpdateModuleData *getGloriousChargeData() const
	{
		return (const GloriousChargeUpdateModuleData *)m_moduleData;
	}
	Rva0029FB3BMember m_88; // +0x88
	unsigned int m_8C; // +0x8C
	bool m_90; // +0x90
};
void GloriousChargeUpdate::rva004AD613()
{
	if (!m_88.empty())
	{
		for (Rva004AD613Iterator it = m_88.begin(); it != m_88.end(); ++it)
		{
			Object *object = TheGameLogic->findObjectByID(*it);
			if (object)
			{
				clearModelConditionBit(object, 6 * 32 + 9);
				object->m_44C = 0;
				Drawable *draw = object->getDrawable();
				if (draw)
					((Rva00270619 *)draw)->Rva00270619Clear(8);
			}
		}
		m_88.reset();
	}
}
UpdateSleepTime GloriousChargeUpdate::update()
{
	rva004AD613();
	if (!m_90)
	{
		if (!m_object->isKindOf((KindOfType)0xD6))
			return (UpdateSleepTime)getGloriousChargeData()->m_D0;
		slot15();
		m_8C = getGloriousChargeData()->m_CC + TheGameLogic->getFrame();
		m_90 = true;
	}
	if (TheGameLogic->getFrame() >= m_8C)
	{
		m_90 = false;
		clearModelConditionBit(m_object, 6 * 32 + 15);
		Drawable *draw = m_object->getDrawable();
		if (draw)
			((Rva00270619 *)draw)->Rva00270619Clear(0x10);
		return UPDATE_SLEEP_FOREVER;
	}
	slot17();
	return (UpdateSleepTime)getGloriousChargeData()->m_D0;
}
void GloriousChargeUpdate::rva004AD7B6()
{
	Object *self = m_object;
	const GloriousChargeUpdateModuleData *data = getGloriousChargeData();
	BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(self->getPosition(), data->m_C8, 0,
		Rva00260EB1Filter(self, 4, false).link(Rva0026119DFilter().link(&Rva002611BFFilter(self))), 1);
	for (Object *obj = hits.next(); obj; obj = hits.next()) {
		if (obj == self)
			continue;
		m_88.push_back(obj->getID());
	}
}
