// cl: /Ireference/shims/bfme2_ascii /ICode/Libraries/Include /Ob2 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// Waypoint's constructors and destructor (vtable 0x007FB21C, whose slot 0 is
// ??_GWaypoint at 0x00282B9F), from Zero Hour's GameLogic/Map/TerrainLogic.cpp
// as Open-BFME-1 reconstructs them (its WaypointConstructor.cpp).
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

#define NULL 0

enum { WAYPOINT_ID_AUTO = 0x7ffffffe };

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
private:
	unsigned int m_data[7];
};

class Rva00360D26Member
{
public:
	Rva00360D26Member();
	~Rva00360D26Member();
private:
	unsigned m_unknown;
};

class TerrainLogic
{
public:
	unsigned char m_pad[0x56c];
	Rva0027F4CB m_tree;
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
private:
	UnsignedInt m_id; // +0x04
	AsciiString m_name; // +0x08
	WaypointLocation m_location; // +0x0C
	Waypoint *m_prev; // +0x18
	Waypoint *m_next; // +0x1C
	Waypoint *m_links[8]; // +0x20
	Waypoint *m_linkSource; // +0x40
	Int m_field44; // +0x44
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
