// ?rva00490AC5@ArrowStormUpdate@@QAEXXZ
// partial score=0.8 date=2026-10-04
// cl: /O1 /DNDEBUG /MD /GX /arch:SSE
//
// ArrowStormUpdate's target gathering 0x00490AC5, tail-called by its slot-15
// override 0x00490D0A after the +0x88 list is reset (ArrowStormUpdateSlots.cpp).
// Every alive object other than this one that 0x00260EB1 accepts with flags
// 1 within the module data's +0xCC radius of the +0x44 target point (BFME2's
// partition filter chain, the view AIStructureCreepTactic.cpp documents) and
// whose template has none of the tested KindOf bits goes into the +0x88
// list, and also into a local list when its template has +0x109 bit 2. A
// non-empty +0x88 list short of the data's +0xD8 count is then topped up by
// cycling through the local list (or through itself when the local list is
// empty).
class Object;

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

// vftable 0x00BFBC90, allow 0x00260EB1: +0x08 the object, +0x0C flags,
// +0x10 whether a hit allows.
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

#pragma comment(linker, "/alternatename:?getPlayerMask@Rva000421C8@@UAEHXZ=?Get_File_Handle@FileClass@@UAEPAXXZ")

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

class ThingTemplate
{
public:
	union
	{
		struct
		{
			char m_pad000[0x109];
			unsigned char m_109;
			char m_pad10A[0x10D - 0x10A];
			unsigned char m_10D;
			char m_pad10E[0x118 - 0x10E];
			unsigned char m_118;
		} b;
		unsigned w[0x11C / 4];
	};
};

class Object
{
public:
	ObjectID getID() const { return m_id; }
	char m_pad000[0x04];
	const ThingTemplate *m_template;	// +0x04
	char m_pad008[0x74 - 0x08];
	ObjectID m_id;		// +0x74
};

// STLport list<ObjectID>: nodes +0 next, +4 previous, +8 the ID.
struct Rva0029FB3BNode
{
	Rva0029FB3BNode *m_next;
	Rva0029FB3BNode *m_previous;
	ObjectID m_value;
};

struct Rva0029FB3BAlloc
{
	Rva0029FB3BAlloc() {}
	~Rva0029FB3BAlloc() {}
};

struct Rva0029FB3BIter
{
	Rva0029FB3BIter(Rva0029FB3BNode *node) : m_node(node) {}
	Rva0029FB3BNode *m_node;
};

class Rva0029FB3BMember
{
public:
	Rva0029FB3BMember(const Rva0029FB3BAlloc &alloc = Rva0029FB3BAlloc());	// 0x0029FB3B
	~Rva0029FB3BMember() throw();	// 0x00268902
	bool empty() const { return m_node->m_next == m_node; }
	unsigned size() const
	{
		unsigned n = 0;
		for (Rva0029FB3BNode *p = m_node->m_next; p != m_node; p = p->m_next)
			++n;
		return n;
	}
	Rva0029FB3BIter end() { return Rva0029FB3BIter(m_node); }
	void push_back(const ObjectID &id);	// 0x002A1B6F
	Rva0029FB3BIter insert(Rva0029FB3BIter pos, const ObjectID &id);	// 0x002A1316
	void reset();	// 0x0026549E
	Rva0029FB3BNode *m_node;
};

struct ArrowStormUpdateModuleData
{
	unsigned char m_pad00[0xCC];
	float m_CC;		// +0xCC the radius
	unsigned char m_padD0[0xD8 - 0xD0];
	unsigned m_D8;		// +0xD8 the count
};

class ModuleData;
class SpecialAbilityUpdate
{
public:
	virtual ~SpecialAbilityUpdate();
protected:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
	unsigned char m_pad0C[0x44 - 0x0C];
	Coord3D m_44;	// +0x44 the target point
	unsigned char m_pad50[0x88 - 0x50];
};

class ArrowStormUpdate : public SpecialAbilityUpdate
{
public:
	void rva00490AC5();
private:
	Rva0029FB3BMember m_88;	// +0x88
};

void ArrowStormUpdate::rva00490AC5()
{
	const ArrowStormUpdateModuleData *data = (const ArrowStormUpdateModuleData *)m_moduleData;
	Object *obj = m_object;
	BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(&m_44, data->m_CC, 0,
		Rva00260EB1Filter(obj, 1, false).link(Rva0026119DFilter().link(&Rva002611BFFilter(obj))), 1);
	Rva0029FB3BMember extra;
	Object *other;
	while ((other = hits.next()) != 0) {
		const ThingTemplate *tmpl = other->m_template;
		if ((tmpl->w[0x114 / 4] & 0x100) || (tmpl->w[0x110 / 4] & 0x02000000)
				|| (tmpl->b.m_10D & 0x80) || (tmpl->w[0x118 / 4] & 0x400000)
				|| (tmpl->w[0x10C / 4] & 0x400000) || (tmpl->b.m_118 & 0x40))
			continue;
		ObjectID id = other->getID();
		m_88.push_back(id);
		if (other->m_template->b.m_109 & 4) {
			id = other->getID();
			extra.insert(extra.end(), id);
		}
	}
	if (m_88.size() != 0) {
		if (m_88.size() < data->m_D8) {
			Rva0029FB3BMember &source = extra.empty() ? m_88 : extra;
			Rva0029FB3BNode *it = source.m_node->m_next;
			while (m_88.size() < data->m_D8) {
				m_88.push_back(it->m_value);
				it = it->m_next;
				if (it == source.m_node)
					it = source.m_node->m_next;
			}
		}
		extra.reset();
	}
}
