// cl: /O1 /MD /GX /arch:SSE
//
// ?rva00295844@Object@@QAEXM@Z, retail 0x00295844, 227 bytes (caller
// 0x002972CF in 0x002972B1). Sums the template +0x51C value of every enemy
// (relationship 1) alive object sharing this object's map status within
// the range, stores it at +0x444 and sets the 5000 ms timer through the
// rowed 0x0028C0F2. That setter is a leaf that cannot throw; retail drops
// the hit list from the unwind map accordingly, so it is declared throw().
//
// The filters are BFME2's partition filter chain (the view
// AIStructureCreepTactic.cpp documents): a vptr, the +0x04 link to the next
// filter (PartitionFilter::link 0x00625790), then each filter's members;
// address-derived names after allow (slot 1), the ctors being inline.
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

// vftable 0x00BFAD10, allow 0x0026119D: not effectively dead (status bit 0),
// ZH's PartitionFilterAlive.
class Rva0026119DFilter : public Rva000421C8
{
public:
	virtual bool allow(Object *obj);
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

// vftable 0x00BF91BC, allow 0x002611BF.
class Rva002611BFFilter : public Rva000421C8
{
public:
	Rva002611BFFilter(const Object *obj) : m_obj(obj) {}
	virtual bool allow(Object *obj);
	const Object *m_obj;
};

// The base filter's slot 2 is the trivial virtual retail shares across many
// vftable slots (0x0036CC7A); bind the declaration to that row.
#pragma comment(linker, "/alternatename:?getPlayerMask@Rva000421C8@@UAEHXZ=?Get_File_Handle@FileClass@@UAEPAXXZ")

struct Coord3D
{
	float x;
	float y;
	float z;
};

struct ThingTemplate
{
	char m_pad000[0x51C];
	float m_51C;		// +0x51C
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

class Object
{
public:
	void rva00295844(float range);
	void rva0028C0F2(unsigned int ms) throw();	// 0x0028C0F2
	char m_pad000[4];
	const ThingTemplate *m_template;	// +0x04
	char m_pad008[0x38 - 8];
	Coord3D m_pos;			// +0x38
	char m_pad044[0x444 - 0x44];
	float m_444;			// +0x444
};

void Object::rva00295844(float range)
{
	BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(&m_pos, range, 0,
		Rva00260EB1Filter(this, 1, false).link(Rva0026119DFilter().link(&Rva002611BFFilter(this))), 0);
	float total = 0.0f;
	Object *obj;
	while ((obj = hits.next()) != 0)
		total += obj->m_template->m_51C;
	m_444 = total;
	rva0028C0F2(5000);
}
