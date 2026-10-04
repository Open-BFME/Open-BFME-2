// ?rva003A2DBB@Team@@QAEXM@Z
// partial score=0.97 date=2026-10-04
// cl: /O1 /MD /GX /arch:SSE
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

class Object
{
public:
	char m_pad000[4];
	const ThingTemplate *m_template;	// +0x04
};

template<class OBJ> class DLINK_ITERATOR
{
public:
	void advance();						// 0x00263526
	bool done() const { return m_cur == 0; }
	OBJ *cur() const { return m_cur; }
private:
	OBJ *m_cur;
	char m_pad[20];
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

class Team
{
public:
	void rva003A2DBB(float range);
	void rva0039E5B9(Coord3D *center);			// 0x0039E5B9
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const;	// 0x00263864
	void rva0039D8D3(unsigned int ms) throw();		// 0x0039D8D3
private:
	char m_pad000[0x120];
	float m_120;		// +0x120
};

void Team::rva003A2DBB(float range)
{
	Coord3D center;
	rva0039E5B9(&center);
	DLINK_ITERATOR<Object> iter = iterate_TeamMemberList();
	Object *leader = iter.cur();
	if (!leader)
		return;
	BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(&center, range, 0,
		Rva00260EB1Filter(leader, 1, false).link(Rva0026119DFilter().link(&Rva002611BFFilter(leader))), 0);
	float total = 0.0f;
	Object *obj;
	while ((obj = hits.next()) != 0)
		total += obj->m_template->m_51C;
	m_120 = total;
	rva0039D8D3(5000);
}


