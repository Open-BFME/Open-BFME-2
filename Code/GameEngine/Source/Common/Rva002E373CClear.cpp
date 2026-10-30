// cl: /MD
// ?Rva002E373CClear@@YAXXZ, retail 0x002E373C, 42 bytes.
// Leaf __cdecl clear of global list at 0x00DBD0F4 plus counter reset at
// 0x00DBD0F0 to 1. Head in ECX cleared via AND plus virtual slot-0 call
// with 0 then operator delete; null head deletes null. Callers 0x00283589
// 0x002E3E13 0x00328DCE. Owning class unproven so honest Rva names.
// VA 0x00DBD0F0 is PolygonTrigger's private ?s_currentID@PolygonTrigger@@0HA,
// defined in PolygonTrigger.cpp (initial 1); reached through a friend view.
struct Region2D;
struct Rva0030B72CPoint;
class Coord2D;
class Rva0030B719Shape
{
public:
	Region2D rva0030B6E3();
	Rva0030B72CPoint rva0030B72C(void) const;
	Coord2D *begin;
	Coord2D *end;
	char m_pad08[0x20];
};

struct FloatRect0073CE30;
struct IRegion2D;
class Coord2D;
struct Coord3D;
struct ICoord3D;
class PolygonTrigger
{
private:
	friend void Rva002E373CClear();
	static int s_currentID; // VA 0x00DBD0F0 (retail .data initial value 1)
public:
	static void addPolygonTrigger(PolygonTrigger *pTrigger);
	PolygonTrigger *getNext() { return m_nextPolygonTrigger; }
	Region2D rva0007E03A();
	void getBounds(FloatRect0073CE30 *rect);
	void getBounds(IRegion2D *out);
	void rva002E36B7(int);
	Rva0030B72CPoint getCenterPoint2D(void) const;
	void getCenterPoint(Coord3D *pOutCoord) const;
	void rva002E38AF(const Coord3D *offset);
	bool pointInTrigger(const ICoord3D &point);
	bool rva002E3A39(const Coord3D &);
	bool rva002E3AA8(const Coord3D *, const Coord3D *, Coord3D *, bool);
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18(int height);
	virtual void slot1C();
	virtual void slot20(const Coord2D *offset);
	char m_pad04[0x4];
private:
	Rva0030B719Shape m_shape; // +0x08
	int m_defaultHeight; // +0x30
	char m_pad34[0x8];
	PolygonTrigger *m_nextPolygonTrigger; // +0x3C
	char opaque40[8]; // +0x40
	bool flag48; // +0x48
	char opaque49[7]; // +0x49
	bool flag50; // +0x50
	char opaque51[3]; // +0x51
	int field54; // +0x54
	int field58; // +0x58
};

struct Rva002E373CNode
{
	virtual void *func(int x);
	unsigned char m_pad[0x38];
	Rva002E373CNode *m_next3C;
};
struct Rva002E373CHolder
{
public:
	PolygonTrigger *m_head;
};

struct Rva002E36D5Node;
extern Rva002E36D5Node *g_00DFF0B8;
// g_Va00DBD0F4: VA 0x00DBD0F4 (.data); retail stores 0x00DFF0B8, the address
// of the rowed zero-filled list head g_00DFF0B8.
Rva002E373CHolder *g_Va00DBD0F4 = (Rva002E373CHolder *)&g_00DFF0B8;


void Rva002E373CClear(void)
{
	Rva002E373CNode *head = reinterpret_cast<Rva002E373CNode *>(g_Va00DBD0F4->m_head);
	g_Va00DBD0F4->m_head = 0;
	PolygonTrigger::s_currentID = 1;
	void *toDelete;
	if (head != 0)
		toDelete = head->func(0);
	else
		toDelete = 0;
	operator delete(toDelete);
}
