// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /ICode/Libraries/Include /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// TerrainLogic::xfer (slot 3 of the TerrainLogic vftable 0x007FB2C8) and the
// save-game xfer of the 0x30-byte records it keeps at +0x578, after
// Open-BFME-1's TerrainLogic_xferTerrainState.cpp, which carries Zero Hour's
// TerrainLogic::xfer water transfer and the BFME terrain state.
//
// Target facts: BFME 2 xfers the flags at +0x44 and +0x60, the active boundary
// at +0x3C and the waters being raised (64 entries of 0x14 bytes at +0x68,
// count at +0x568) whose handles are saved as ids through the 0x20-byte
// registry at +0x50 (id to handle 0x0027F4F8, handle to id 0x00280ADF); an id
// the registry does not know throws XferException tag 5. Waypoints follow the
// automatic id at 0x009BB708: a load creates each one empty (constructor
// 0x00282212) and lets Waypoint::xfer fill it, then resolves every link
// (0x0027C330) and clears the id cache at +0x56C. The records are owned by
// pointer: a load deletes the old ones, clears the vector through the folded
// pointer-vector range erase (rowed for vector<void*>), reserves and appends
// through the folded reserve and push_back (rowed for vector<const
// ModuleData*>), each record from a new-expression over its constructor
// (0x0027C230). Retail stores that pointer only after the null-check merge
// and keeps no unwind state for it, which is how MSVC 7.1 builds the
// new-expression when the constructor is defined earlier in the same unit
// and seen not to throw; a constructor declared elsewhere (even throw())
// sinks the store into both arms. A load then rebuilds through 0x0028360C. 2500 shorts at +0x588, an unsigned at
// +0x1910, a flag at +0x1914 and, from version 2, the unsigned at +0x48 close
// the block.
//
// A record keeps a position at +0x00, a drawable id at +0x0C (not part of a
// CRC), an unsigned at +0x10 (version 2), a thing template at +0x14 saved by
// its name (+0x64) and found again through TheThingFactory (0x002D06CA), and
// a flag, a second position, an int, a short and two more flags. A loaded
// record with a template is registered with the fire logic system at
// 0x00DFEC68 (0x00286373).
#include "ascii_string.h"
#include "Lib/Coord3D.h"

#include <vector>

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;
typedef float Real;

enum { INVALID_WAYPOINT_ID = 0x7fffffff };

struct XferVersion
{
	UnsignedByte m_first;
	UnsignedByte m_version;
	UnsignedByte m_pad[2];
};

class Xfer
{
public:
	virtual void slot00();
	virtual Bool isLoading(); // +0x04
	virtual Bool isStoring(); // +0x08
	virtual Bool isCRC(); // +0x0C
	virtual Bool isLightCRC(); // +0x10
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
	virtual void xferReal(Real *value); // +0x70
	virtual void slot74();
	virtual void xferUnsignedInt(UnsignedInt *value); // +0x78
	virtual void xferInt(Int *value); // +0x7C
	virtual void slot80();
	virtual void xferShort(short *value); // +0x84
	virtual void slot88();
	virtual void slot8C();
	virtual void xferBool(Bool *value); // +0x90
};

class XferException
{
public:
	XferException(int tag, const char *format, ...);
	XferException(const XferException &that);
	~XferException();

	char *text;
	int tag;
};

void XferWaypointID(Xfer *xfer, Int *id);
void XferDrawableID(Xfer *xfer, Int *id);

extern int g_Va00DBB708; // next automatically assigned waypoint id

class ThingTemplate
{
public:
	const AsciiString &getName() const { return m_name; }
private:
	char m_pad00[0x64];
	AsciiString m_name; // +0x64
};

// TheThingFactory's template lookup by name, named for its address.
class Rva002D06CA
{
public:
	void *rva002D06CA(const AsciiString *name);
};
extern Rva002D06CA *TheThingFactory;

// The fire logic system at 0x00DFEC68 (the data ledger names the pointer
// TheTriggerManager) and its registration of a placed template, named for its
// address.
class FireLogicSystem
{
public:
	void rva00286373(Int drawableID, const Coord3D *pos, const ThingTemplate *tmpl);
};
class Rva002872BA;
extern Rva002872BA *TheTriggerManager;
inline FireLogicSystem *TheFireLogicSystem() { return (FireLogicSystem *)TheTriggerManager; }

// TerrainLogic's 0x20-byte registry objects (0x002834C4): a vector of
// id/handle pairs at +0x14.
class WaterHandle;
struct Rva002834C4Entry
{
	Int id;
	const WaterHandle *handle;
};
class Rva002834C4
{
public:
	Int rva00280ADF(const WaterHandle *handle);
private:
	char m_pad00[0x14];
	_STL::vector<Rva002834C4Entry> m_entries; // +0x14
};

// The rowed id lookup on the same registry, named for its address.
class Rva0027F4F8
{
public:
	void *rva0027F4F8(Int id);
};

class Rva0027C230
{
public:
	Rva0027C230(Int value);
	void rva0028002F(Xfer *xfer);
private:
	Coord3D m_pos; // +0x00
	Int m_drawableID; // +0x0C
	UnsignedInt m_10; // +0x10
	const ThingTemplate *m_template; // +0x14
	Bool m_18; // +0x18
	Coord3D m_1C; // +0x1C
	Int m_28; // +0x28
	Bool m_2C; // +0x2C
	Bool m_2D; // +0x2D
	short m_2E; // +0x2E
};

class ModuleData;
// The records vector's out-of-line members fold with other 4-byte vectors'.
typedef _STL::vector<void *> FoldedEraseVector;
typedef _STL::vector<const ModuleData *> FoldedAppendVector;

class Waypoint
{
public:
	Waypoint(UnsignedInt id, AsciiString name, const Coord3D *pLoc, AsciiString label1,
		AsciiString label2, AsciiString label3, Bool biDirectional, Int extraField,
		AsciiString extraLabel);
	void xfer(Xfer *xfer);
	void rva0027C330();
	Waypoint *getNext() const { return m_next; }
private:
	char m_pad00[0x1C];
	Waypoint *m_next; // +0x1C
	char m_pad20[0xC0 - 0x20];
};
extern Waypoint *g_waypointListHead;

// TerrainLogic's waypoint id cache (a map) cleared by 0x00280AB6.
class Rva0027F4CB
{
public:
	void rva00280AB6();
private:
	void *m_00;
	int m_04;
	int m_08;
};

// The rowed post-load rebuild, named for its address.
class Rva0028360CHost
{
public:
	void rva0028360C();
};

struct WaterToUpdate
{
	const WaterHandle *waterTable;
	Real changePerFrame;
	Real targetHeight;
	Real damageAmount;
	Real currentHeight;
};

enum { MAX_DYNAMIC_WATER = 64 };

class TerrainLogic
{
public:
	void setActiveBoundary(Int newActiveBoundary);
protected:
	virtual void xfer(Xfer *xfer);
private:
	char m_pad04[0x3C - 0x04];
	Int m_activeBoundary; // +0x3C
	char m_pad40[0x44 - 0x40];
	Bool m_field44; // +0x44
	UnsignedInt m_field48; // +0x48
	char m_pad4C[0x50 - 0x4C];
	Rva002834C4 *m_field50; // +0x50
	char m_pad54[0x60 - 0x54];
	Bool m_field60; // +0x60
	char m_pad61[0x68 - 0x61];
	WaterToUpdate m_waterToUpdate[MAX_DYNAMIC_WATER]; // +0x68
	UnsignedInt m_numWaterToUpdate; // +0x568
	Rva0027F4CB m_waypointsByID; // +0x56C
	_STL::vector<Rva0027C230 *> m_records; // +0x578
	char m_pad584[0x588 - 0x584];
	short m_words[2500]; // +0x588
	UnsignedInt m_field1910; // +0x1910
	Bool m_field1914; // +0x1914
};

// ?rva00280ADF@Rva002834C4@@QAEHPBVWaterHandle@@@Z @0x00280ADF
// The id a water handle was registered under, -1 when it was not.
Int Rva002834C4::rva00280ADF(const WaterHandle *handle)
{
	for (UnsignedInt i = 0; ; i++)
	{
		if (i >= m_entries.size())
			return -1;
		if (m_entries[i].handle == handle)
			return m_entries[i].id;
	}
}

// ??0Rva0027C230@@QAE@H@Z @0x0027C230
Rva0027C230::Rva0027C230(Int value)
{
	m_2E = -1;
	m_drawableID = 0;
	m_10 = value;
	m_template = NULL;
	m_18 = false;
	m_28 = 1;
	m_2C = true;
	m_2D = true;
	m_pos.x = 0.0f;
	m_pos.y = 0.0f;
	m_pos.z = 0.0f;
	m_1C.x = 0.0f;
	m_1C.y = 0.0f;
	m_1C.z = 0.0f;
}

// ?rva0028002F@Rva0027C230@@QAEXPAVXfer@@@Z @0x0028002F
void Rva0027C230::rva0028002F(Xfer *xfer)
{
	XferVersion version;
	version.m_first = 1;
	version.m_version = 2;
	xfer->xferVersion(&version);

	xfer->xferCoord3D(&m_pos);
	if (!xfer->isCRC())
		XferDrawableID(xfer, &m_drawableID);

	AsciiString name;
	if (!xfer->isLoading() && m_template != NULL)
		name = m_template->getName();
	xfer->xferAsciiString(&name);
	if (xfer->isLoading())
	{
		if (!name.isEmpty())
			m_template = (const ThingTemplate *)TheThingFactory->rva002D06CA(&name);
		else
			m_template = NULL;
	}

	xfer->xferBool(&m_18);
	xfer->xferCoord3D(&m_1C);
	xfer->xferInt(&m_28);
	xfer->xferShort(&m_2E);
	xfer->xferBool(&m_2C);
	xfer->xferBool(&m_2D);
	if (version.m_version >= 2)
		xfer->xferUnsignedInt(&m_10);

	if (xfer->isLoading() && TheFireLogicSystem() != NULL && m_template != NULL)
		TheFireLogicSystem()->rva00286373(m_drawableID, &m_pos, m_template);
}

// ?xfer@TerrainLogic@@MAEXPAVXfer@@@Z @0x00283845
void TerrainLogic::xfer(Xfer *xfer)
{
	if (xfer->isLightCRC())
		return;

	XferVersion version;
	version.m_first = 1;
	version.m_version = 2;
	xfer->xferVersion(&version);

	xfer->xferBool(&m_field44);
	xfer->xferBool(&m_field60);

	Int activeBoundary = m_activeBoundary;
	xfer->xferInt(&activeBoundary);
	if (xfer->isLoading())
		setActiveBoundary(activeBoundary);

	xfer->xferInt((Int *)&m_numWaterToUpdate);
	for (UnsignedInt i = 0; i < m_numWaterToUpdate; ++i)
	{
		if (xfer->isStoring())
		{
			Int triggerID = m_field50->rva00280ADF(m_waterToUpdate[i].waterTable);
			xfer->xferInt(&triggerID);
		}
		else
		{
			Int triggerID;
			xfer->xferInt(&triggerID);
			const WaterHandle *water = (const WaterHandle *)((Rva0027F4F8 *)m_field50)->rva0027F4F8(triggerID);
			if (water == NULL)
				throw XferException(5, 0);
			m_waterToUpdate[i].waterTable = water;
		}
		xfer->xferReal(&m_waterToUpdate[i].changePerFrame);
		xfer->xferReal(&m_waterToUpdate[i].targetHeight);
		xfer->xferReal(&m_waterToUpdate[i].damageAmount);
		xfer->xferReal(&m_waterToUpdate[i].currentHeight);
	}

	Int nextID = g_Va00DBB708;
	XferWaypointID(xfer, &nextID);
	g_Va00DBB708 = nextID;

	if (xfer->isLoading())
	{
		Bool more;
		xfer->xferBool(&more);
		if (more)
		{
			Coord3D loc;
			loc.x = 0;
			loc.y = 0;
			loc.z = 0;
			do
			{
				Waypoint *way = new Waypoint(INVALID_WAYPOINT_ID, AsciiString::TheEmptyString, &loc,
					AsciiString::TheEmptyString, AsciiString::TheEmptyString, AsciiString::TheEmptyString,
					false, 0, AsciiString::TheEmptyString);
				way->xfer(xfer);
				xfer->xferBool(&more);
			} while (more);
		}
		for (Waypoint *way = g_waypointListHead; way; way = way->getNext())
			way->rva0027C330();
		m_waypointsByID.rva00280AB6();
	}
	else
	{
		Bool more = true;
		for (Waypoint *way = g_waypointListHead; way; way = way->getNext())
		{
			xfer->xferBool(&more);
			way->xfer(xfer);
		}
		more = false;
		xfer->xferBool(&more);
	}

	Int count = m_records.size();
	xfer->xferInt(&count);
	if (xfer->isLoading())
	{
		for (Rva0027C230 **it = m_records.begin(), **end = m_records.end(); it != end; ++it)
			if (*it)
				delete *it;
		((FoldedEraseVector *)&m_records)->clear();
		((FoldedAppendVector *)&m_records)->reserve(count);
		for (Int i = 0; i < count; ++i)
		{
			((FoldedAppendVector *)&m_records)->push_back((const ModuleData *)new Rva0027C230(0));
		}
	}
	for (Int j = 0; j < count; ++j)
		m_records[j]->rva0028002F(xfer);

	if (xfer->isLoading())
		((Rva0028360CHost *)this)->rva0028360C();

	for (Int k = 0; k < 2500; ++k)
		xfer->xferShort(&m_words[k]);
	xfer->xferUnsignedInt(&m_field1910);
	xfer->xferBool(&m_field1914);
	if (version.m_version >= 2)
		xfer->xferUnsignedInt(&m_field48);
}
