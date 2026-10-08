// cl: /Ireference/shims/bfme2_ascii /ICode/Libraries/Include /Ob2 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// Waypoint's constructors and destructor (vtable 0x007FB21C, whose slot 0 is
// ??_GWaypoint at 0x00282B9F), from Zero Hour's GameLogic/Map/TerrainLogic.cpp
// as Open-BFME-1 reconstructs them (its WaypointConstructor.cpp), its
// save-game xfer (Open-BFME-1's WaypointXfer.cpp) and the post-load pass that
// turns the saved link ids back into waypoints.
//
// Target facts: the nine-argument constructor (0x00282212, ret 0x24) takes
// its five strings by value and destroys them itself; the waypoint list head
// is the data ledger's g_waypointListHead (0x009FEC54) and the next automatic
// id is the dword at 0x009BB708. Every constructor and the destructor clear
// TheTerrainLogic's id cache at +0x56C (0x00280AB6). Against BFME 1 the two
// kind masks grow to 0x1C bytes, built by the shared memset constructor
// 0x0024C7B3 and zeroed again in the body; a flag at +0xA9 defaults true, a
// flag at +0xB8 is cleared in the body and a member at +0xBC (constructor
// 0x003623E5, destructor 0x00360D26) closes the object. Member names other
// than Zero Hour's are Open-BFME-1's.
#include "ascii_string.h"
#include "Lib/Coord3D.h"

extern "C" void *memset(void *dst, int value, unsigned int size);

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;

#define NULL 0

enum { WAYPOINT_ID_AUTO = 0x7ffffffe, INVALID_WAYPOINT_ID = 0x7fffffff };

struct XferVersion
{
	UnsignedByte m_first;
	UnsignedByte m_version;
};

class Xfer
{
public:
	virtual void slot00();
	virtual Bool isLoading(); // +0x04
	virtual Bool isStoring(); // +0x08
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void xferUser(void *data, Int size); // +0x24
	virtual void xferVersion(XferVersion *version); // +0x28
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4C();
	virtual void slot50();
	virtual void slot54();
	virtual void slot58();
	virtual void slot5C();
	virtual void xferCoord3D(Coord3D *value); // +0x60
	virtual void slot64();
	virtual void slot68();
	virtual void xferAsciiString(AsciiString *value); // +0x6C
	virtual void slot70();
	virtual void slot74();
	virtual void xferUnsignedInt(UnsignedInt *value); // +0x78
	virtual void xferInt(Int *value); // +0x7C
	virtual void slot80();
	virtual void slot84();
	virtual void slot88();
	virtual void slot8C();
	virtual void xferBool(Bool *value); // +0x90
};

enum ObjectID
{
	INVALID_ID = 0
};

void XferWaypointID(Xfer *xfer, Int *id);
void XferObjectID(Xfer *xfer, ObjectID *id);

template <int NUMBITS> class BitFlags
{
public:
	void xfer(Xfer *xfer);
};

// The rowed xfer of the member at +0xBC, named for its address.
class Rva003189ADSub10
{
public:
	void rva00362255(Xfer *xfer);
};

// Zero Hour's Coord3D::zero, and a location copied member by member rather
// than as a block.
struct WaypointLocation : public Coord3D
{
	WaypointLocation() {}
	void zero() { x = 0; y = 0; z = 0; }
	WaypointLocation(const Coord3D &that) { x = that.x; y = that.y; z = that.z; }
};

class Waypoint;
extern Waypoint *g_waypointListHead;
extern int g_Va00DBB708; // next automatically assigned waypoint id

class Rva0027F4CB
{
public:
	void rva00280AB6();
private:
	void *m_00Head;
	int m_04Flag;
};

class Rva0024C7B3Member
{
public:
	Rva0024C7B3Member();
	void zeroData() { memset(m_data, 0, sizeof(m_data)); }
	void xfer(Xfer *xfer) { ((BitFlags<218> *)this)->xfer(xfer); }
private:
	unsigned int m_data[7];
};

class Rva00360D26Member
{
public:
	Rva00360D26Member();
	~Rva00360D26Member();
	void xfer(Xfer *xfer) { ((Rva003189ADSub10 *)this)->rva00362255(xfer); }
private:
	unsigned m_unknown;
};

// N unnamed vftable slots appended to Base.
template <class Base, int N> class TerrainLogicSlots : public TerrainLogicSlots<Base, N - 1>
{
public:
	virtual void gap(Base *, char (*)[N]);
};
template <class Base> class TerrainLogicSlots<Base, 0> : public Base
{
};

class TerrainLogicHead
{
public:
	virtual void slot0();
};

class TerrainLogic : public TerrainLogicSlots<TerrainLogicHead, 34>
{
public:
	virtual Waypoint *getWaypointByID(UnsignedInt id); // +0x8C

	unsigned char m_pad[0x56c - 0x04];
	Rva0027F4CB m_tree; // +0x56C
};

extern TerrainLogic *TheTerrainLogic;

class Waypoint
{
public:
	Waypoint();
	Waypoint(UnsignedInt id, AsciiString name, const Coord3D *pLoc, AsciiString label1,
		AsciiString label2, AsciiString label3, Bool biDirectional, Int extraField,
		AsciiString extraLabel);
	virtual ~Waypoint();
	UnsignedInt getID() const { return m_id; }
	void xfer(Xfer *xfer);
	Waypoint *rva0027C313(Int id);
	void rva0027C330();
private:
	UnsignedInt m_id; // +0x04
	AsciiString m_name; // +0x08
	WaypointLocation m_location; // +0x0C
	Waypoint *m_prev; // +0x18
	Waypoint *m_next; // +0x1C
	Waypoint *m_links[8]; // +0x20
	Waypoint *m_linkSource; // +0x40
	Waypoint *m_field44; // +0x44
	Bool m_field48; // +0x48
	Int m_numLinks; // +0x4C
	AsciiString m_pathLabel1; // +0x50
	AsciiString m_pathLabel2; // +0x54
	AsciiString m_pathLabel3; // +0x58
	Bool m_biDirectional; // +0x5C
	Int m_extraField; // +0x60
	AsciiString m_extraLabel; // +0x64
	Bool m_hasInclude; // +0x68
	Rva0024C7B3Member m_includeMask; // +0x6C
	Bool m_hasExclude; // +0x88
	Rva0024C7B3Member m_excludeMask; // +0x8C
	Bool m_skipRelationship; // +0xA8
	Bool m_fieldA9; // +0xA9
	Int m_fieldAC; // +0xAC
	Int m_linkedObjectId; // +0xB0
	Int m_frameThreshold; // +0xB4
	Bool m_fieldB8; // +0xB8
	Rva00360D26Member m_bc; // +0xBC
};

// ??0Waypoint@@QAE@IVAsciiString@@PBUCoord3D@@000_NH0@Z @0x00282212
Waypoint::Waypoint(UnsignedInt id, AsciiString name, const Coord3D *pLoc, AsciiString label1,
	AsciiString label2, AsciiString label3, Bool biDirectional, Int extraField,
	AsciiString extraLabel)
	: m_id(id), m_name(name), m_location(*pLoc),
	  m_field44(0), m_field48(true), m_numLinks(0),
	  m_pathLabel1(label1), m_pathLabel2(label2), m_pathLabel3(label3),
	  m_biDirectional(biDirectional), m_extraField(extraField),
	  m_extraLabel(extraLabel), m_hasInclude(false), m_hasExclude(false),
	  m_skipRelationship(false), m_fieldA9(true), m_fieldAC(0), m_linkedObjectId(0)
{
	m_includeMask.zeroData();
	m_excludeMask.zeroData();
	m_fieldB8 = false;

	for (Int i = 0; i < 8; i++)
		m_links[i] = NULL;
	m_linkSource = NULL;

	if (g_waypointListHead == NULL)
		g_Va00DBB708 = 0x40000000;
	if (m_id == WAYPOINT_ID_AUTO)
	{
		m_id = g_Va00DBB708;
		++g_Va00DBB708;
	}

	m_next = g_waypointListHead;
	if (m_next)
		m_next->m_prev = this;
	m_prev = NULL;
	g_waypointListHead = this;

	m_frameThreshold = 0;

	if (TheTerrainLogic)
		TheTerrainLogic->m_tree.rva00280AB6();
}

// ??0Waypoint@@QAE@XZ @0x002823D1
// The load path fills the fields afterwards.
Waypoint::Waypoint() : m_fieldA9(true)
{
	m_id = 0;
	m_numLinks = 0;
	m_biDirectional = false;
	m_extraField = 0;
	m_field44 = 0;
	m_field48 = false;
	m_hasInclude = false;
	m_hasExclude = false;
	m_skipRelationship = false;
	m_location.zero();
	m_fieldAC = 0;
	m_includeMask.zeroData();
	m_excludeMask.zeroData();
	m_fieldB8 = false;

	for (Int i = 0; i < 8; i++)
		m_links[i] = NULL;
	m_linkSource = NULL;

	if (g_waypointListHead == NULL)
		g_Va00DBB708 = 0x40000000;
	if (m_id == WAYPOINT_ID_AUTO)
	{
		m_id = g_Va00DBB708;
		++g_Va00DBB708;
	}

	m_next = g_waypointListHead;
	if (m_next)
		m_next->m_prev = this;
	m_prev = NULL;
	g_waypointListHead = this;

	m_frameThreshold = 0;

	if (TheTerrainLogic)
		TheTerrainLogic->m_tree.rva00280AB6();
}

// ??1Waypoint@@UAE@XZ @0x00282500
Waypoint::~Waypoint()
{
	if (m_next)
		m_next->m_prev = m_prev;
	if (m_prev)
		m_prev->m_next = m_next;
	else
		g_waypointListHead = m_next;
	if (TheTerrainLogic)
		TheTerrainLogic->m_tree.rva00280AB6();
}

// ?xfer@Waypoint@@QAEXPAVXfer@@@Z @0x0027F5F7
// Open-BFME-1's Waypoint::xfer (its WaypointXfer.cpp) at version 4: version 3
// adds the frame threshold at +0xB4, version 4 the member at +0xBC and the
// flag at +0xB8, and BFME 2 saves the flag at +0xA9 after the one at +0xA8.
// Links are saved as ids; loading leaves the ids in the link slots for the
// fixup pass to resolve.
void Waypoint::xfer(Xfer *xfer)
{
	XferVersion version;
	version.m_first = 1;
	version.m_version = 4;
	xfer->xferVersion(&version);

	XferWaypointID(xfer, (Int *)&m_id);
	xfer->xferAsciiString(&m_name);
	xfer->xferCoord3D(&m_location);
	if (version.m_version >= 2)
		XferWaypointID(xfer, &g_Va00DBB708);

	if (xfer->isLoading())
	{
		Int count;
		Int id;
		xfer->xferInt(&count);
		Int i = 0;
		while (i < count)
		{
			XferWaypointID(xfer, &id);
			if (i < 8)
				m_links[i] = (Waypoint *)id;
			++i;
		}
		if (i < 8)
		{
			while (i < 8)
				m_links[i++] = (Waypoint *)INVALID_WAYPOINT_ID;
		}

		XferWaypointID(xfer, &id);
		m_field44 = (Waypoint *)id;
		if (version.m_version >= 2)
		{
			XferWaypointID(xfer, &id);
			m_linkSource = (Waypoint *)id;
		}
		else
			m_linkSource = (Waypoint *)INVALID_WAYPOINT_ID;
	}
	else if (xfer->isStoring())
	{
		Int i = 8;
		xfer->xferInt(&i);
		i = 0;
		Int id;
		while (i < 8)
		{
			Waypoint *link = m_links[i];
			if (link != NULL)
				id = link->m_id;
			else
				id = INVALID_WAYPOINT_ID;
			XferWaypointID(xfer, &id);
			++i;
		}

		if (m_field44 != NULL)
			id = m_field44->m_id;
		else
			id = INVALID_WAYPOINT_ID;
		XferWaypointID(xfer, &id);
		if (version.m_version >= 2)
		{
			id = m_linkSource != NULL ? m_linkSource->getID() : INVALID_WAYPOINT_ID;
			XferWaypointID(xfer, &id);
		}
	}

	xfer->xferBool(&m_field48);
	xfer->xferInt(&m_numLinks);
	xfer->xferAsciiString(&m_pathLabel1);
	xfer->xferAsciiString(&m_pathLabel2);
	xfer->xferAsciiString(&m_pathLabel3);
	xfer->xferBool(&m_biDirectional);
	xfer->xferUser(&m_extraField, 4);
	xfer->xferAsciiString(&m_extraLabel);
	xfer->xferBool(&m_hasInclude);
	xfer->xferBool(&m_hasExclude);
	xfer->xferBool(&m_skipRelationship);
	xfer->xferBool(&m_fieldA9);
	XferObjectID(xfer, (ObjectID *)&m_linkedObjectId);
	m_includeMask.xfer(xfer);
	m_excludeMask.xfer(xfer);
	if (version.m_version >= 3)
		xfer->xferUnsignedInt((UnsignedInt *)&m_frameThreshold);
	if (version.m_version >= 4)
	{
		m_bc.xfer(xfer);
		xfer->xferBool(&m_fieldB8);
	}
}

// ?rva0027C313@Waypoint@@QAEPAV1@H@Z @0x0027C313
// A link id saved by xfer, resolved back to its waypoint.
Waypoint *Waypoint::rva0027C313(Int id)
{
	if (id == INVALID_WAYPOINT_ID)
		return NULL;
	return TheTerrainLogic->getWaypointByID(id);
}

// ?rva0027C330@Waypoint@@QAEXXZ @0x0027C330
// After a load, every link slot xfer filled with an id holds the waypoint
// again (Open-BFME-1 inlines the lookup into the same loop).
void Waypoint::rva0027C330()
{
	for (Int i = 0; i < 8; i++)
		m_links[i] = rva0027C313((Int)m_links[i]);
	m_field44 = rva0027C313((Int)m_field44);
	m_linkSource = rva0027C313((Int)m_linkSource);
}
