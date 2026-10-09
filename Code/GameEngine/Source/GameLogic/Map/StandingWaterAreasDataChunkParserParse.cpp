// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /ICode/Libraries/Include /DNDEBUG /MD /EHsc
//
// ?parse@StandingWaterAreasDataChunkParser@@UAE_NAAVDataChunkInput@@PAUDataChunkInfo@@@Z
// retail 0x003091B1..0x00309332 (385 bytes, EH, RET 8).
//
// Identity:
// - WorldBuilder 0x00BE03F0 is StandingWaterAreasDataChunkParser::parse
//   (StandingWaterArea.cpp, asserts 666..709).
// - Retail has it in slot 1 of vtable 0x00807EE8 (??_7Rva003085FB@@6B@).
//   The rowed ctor of that class, Rva003085FB.cpp, binds the
//   "StandingWaterAreas" label and stores the area set at +0x0C.
//
// What the body does:
// - It clears the area set and reads the count.
// - For each record it:
//   - reads the id;
//   - news a 0xDC-byte standing water area (pinned ctor 0x00308E63 with 0 and
//     true) held by the ref-counted StandingWaterRef, as in the rowed
//     OldPolygonTrigger.cpp sibling;
//   - runs the rowed WaterArea::parse;
//   - reads two texture names (rowed 0x00308765);
//   - parses an ElevatedAreaPolygon (rowed ctor 0x0030B9DD and parse
//     0x0030BB87) and hands it to the area's +0x30 polygon object;
//   - from version 2 on, reads two more strings (rowed 0x00308139 and
//     0x0030815D);
//   - inserts the area under its id (pinned 0x0030912A) when the area has at
//     least two points.
//
// Matching notes:
// - The +0x30 hand-off goes through 0x005CB283, a one-argument wrapper
//   (WB 0x00AB9610) whose retail body (mov eax,[ecx] / jmp [eax+0x2C]) folds
//   with the address-named no-argument rows there.
// - The point count is read through the +0x38 points sub-object so the
//   compiler keeps retail's null tests on the reference.
#include "ascii_string.h"
#include "Lib/Coord2D.h"

typedef int Int;
typedef bool Bool;


class DataChunkInput
{
public:
	Int readInt();
	AsciiString readAsciiString();
};

struct DataChunkInfo
{
	char m_pad00[8];
	unsigned short version;							// +0x08
};

namespace _STL { void free(void *); }

// ElevatedAreaPolygon storage; the native 0x2C-byte constructor is rowed as
// Rva0030B9DD and its parse as ElevatedAreaPolygon::parse.
class Rva0030B9DD
{
public:
	Rva0030B9DD(Int);
	~Rva0030B9DD()
	{
		if (m_pointsBegin)
			_STL::free(m_pointsBegin);
	}
	Coord2D *m_pointsBegin;
	Coord2D *m_pointsEnd;
	char m_pad08[0x2C - 8];
};
class ElevatedAreaPolygon
{
public:
	void parse(DataChunkInput &file, Int flag);
};

struct TargetRef00217D4C
{
	virtual void *destroy(unsigned int);
	Int references;
};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);

class WaterArea : public TargetRef00217D4C
{
public:
	void parse(DataChunkInput &file, void *userData);
};

class Rva005CB283
{
public:
	void rva005CB283(const Rva0030B9DD *polygon);
};


struct StandingWaterPoints
{
	Coord2D *m_start;
	Coord2D *m_finish;
	Coord2D *m_endOfStorage;
	Int size() const { return m_finish - m_start; }
};

class Rva00308E63 : public WaterArea
{
public:
	Rva00308E63(Int, Bool);
	char m_pad08[0x30 - 8];
	Rva005CB283 m_polygon;							// +0x30
	char m_pad31[0x38 - 0x31];
	StandingWaterPoints m_points;					// +0x38
	char m_pad44[0xDC - 0x44];
};

class StandingWaterRef
{
public:
	StandingWaterRef(Rva00308E63 *p) : m_ptr(p)
	{
		if (m_ptr) ++m_ptr->references;
	}
	StandingWaterRef(const StandingWaterRef &that) : m_ptr(that.m_ptr)
	{
		if (m_ptr) ++m_ptr->references;
	}
	~StandingWaterRef()
	{
		if (m_ptr) ReleaseTreeHintRef00217D4C(m_ptr);
	}
	Rva00308E63 *operator->() const { return m_ptr; }
	Rva00308E63 *m_ptr;
};

class Rva00308765
{
public:
	void rva00308765(Int index, const AsciiString &name);
};
class Rva00308139
{
public:
	void rva00308139(const AsciiString &name);
};
class Rva0030815D
{
public:
	void rva0030815D(const AsciiString &name);
};
class Rva0030912A
{
public:
	void rva0030912A(Int id, StandingWaterRef area);
};
class Rva00282135
{
public:
	void rva00282135();
};

class StandingWaterAreasDataChunkParser
{
public:
	virtual ~StandingWaterAreasDataChunkParser();
	virtual Bool parse(DataChunkInput &file, DataChunkInfo *info);
private:
	void *m_registry;
	void *m_token;
	Rva00282135 *m_areas;							// +0x0C
};

Bool StandingWaterAreasDataChunkParser::parse(DataChunkInput &file, DataChunkInfo *info)
{
	m_areas->rva00282135();
	Int count = file.readInt();
	while (count > 0)
	{
		Int id = file.readInt();
		StandingWaterRef water(new Rva00308E63(0, true));
		water->parse(file, (void *)1);
		for (Int i = 0; i < 2; ++i)
			reinterpret_cast<Rva00308765 *>(water.m_ptr)->rva00308765(i, file.readAsciiString());
		{
			Rva0030B9DD polygon(0);
			reinterpret_cast<ElevatedAreaPolygon *>(&polygon)->parse(file, 1);
			water->m_polygon.rva005CB283(&polygon);
		}
		if (info->version >= 2)
		{
			reinterpret_cast<Rva00308139 *>(water.m_ptr)->rva00308139(file.readAsciiString());
			reinterpret_cast<Rva0030815D *>(water.m_ptr)->rva0030815D(file.readAsciiString());
		}
		if (water->m_points.size() >= 2)
			reinterpret_cast<Rva0030912A *>(m_areas)->rva0030912A(id, water);
		--count;
	}
	return true;
}
