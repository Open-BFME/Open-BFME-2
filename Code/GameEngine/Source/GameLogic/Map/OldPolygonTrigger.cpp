// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// WorldBuilder names parseWaterAreasChunkImpl in OldPolygonTrigger.cpp at
// 0x00BE2810. Its call graph maps to retail 0x003295B4. Retail proves the
// two area-set pointers at +0x20/+0x24 and the parsed holder's point vector
// at +0x48. The helper and holder names remain opaque where WB supplies none.
#include "../../../../Libraries/Include/Lib/Coord2D.h"
#include "ascii_string.h"
class DataChunkInput
{
public:
	int readInt();
};

struct DataChunkInfo
{
	char m_pad00[8];
	unsigned short m_version;
};

class Rva0030B9DD
{
public:
	Rva0030B9DD(int);
	Coord2D *m_pointsBegin;
	Coord2D *m_pointsEnd;
	char m_pad08[0x2c - 8];
};

struct Out
{
	Out();
	~Out();
	int m_id;
	AsciiString m_name;
	AsciiString m_extra;
	bool m_isRiver;
	char m_pad0d[3];
	int m_10;
	AsciiString m_strings[6];
	bool m_2c;
	char m_pad2d[3];
	int m_rgb[3];
	float m_3c, m_40, m_44;
	Rva0030B9DD m_polygon;
	unsigned int pointCount() const
	{
		return m_polygon.m_pointsEnd - m_polygon.m_pointsBegin;
	}
};

// Native 0x0032912D constructs two strings, six string-array elements, then
// the existing 2C-byte polygon constructor with zero at +48.
Out::Out() : m_polygon(0) {}

class Rva00282135
{
public:
	void rva00282135();
};

struct Rva003294B3Obj;
void __cdecl Rva00328A8AParse(DataChunkInput &, int, void *);
void __cdecl rva00329339(Rva003294B3Obj *, int);
void __cdecl rva0032927A(Rva003294B3Obj *, int);
void __cdecl rva003294B3(Rva003294B3Obj *, int, int);
void __cdecl Rva00328E96Parse(DataChunkInput &, int, void *);
void __cdecl Rva00328DE4Add(void *, void **);

class Rva003294D6Trigger
{
public:
	virtual void *destroy(int);
};

struct PolygonData : Out
{
	bool m_isWaterArea;
};

void __cdecl operator delete(void *);

class OldPolygonTriggerDataChunkParserBase
{
public:
	class Impl
	{
	public:
		bool parseWaterAreasChunkImpl(DataChunkInput &, const DataChunkInfo *);
		bool parsePolygonTriggersChunkImpl(DataChunkInput &, const DataChunkInfo *);
	private:
		char m_pad00[0x1c];
		Rva003294D6Trigger **m_triggerList;
		Rva00282135 *m_standingWaterAreas;
		Rva00282135 *m_riverAreas;
	};
};

bool OldPolygonTriggerDataChunkParserBase::Impl::parseWaterAreasChunkImpl(
	DataChunkInput &file, const DataChunkInfo *info)
{
	m_standingWaterAreas->rva00282135();
	m_riverAreas->rva00282135();
	int count = file.readInt();
	Out data;
	for (; count > 0; --count)
	{
		Rva00328A8AParse(file, info->m_version, &data);
		if (static_cast<int>(data.pointCount()) >= 2)
		{
			if (data.m_isRiver)
				rva00329339(reinterpret_cast<Rva003294B3Obj *>(&data),
					reinterpret_cast<int>(m_riverAreas));
			else
				rva0032927A(reinterpret_cast<Rva003294B3Obj *>(&data),
					reinterpret_cast<int>(m_standingWaterAreas));
		}
	}
	return true;
}

struct TargetRef00217D4C
{
	virtual void *destroy(unsigned int);
	int references;
};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);

class Rva0032927ABoundary
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
	virtual void setBoundary(const void *);
};

class Rva00308E63 : public TargetRef00217D4C
{
public:
	Rva00308E63(int, bool);
	char m_pad08[0x30 - 8];
	Rva0032927ABoundary m_boundary;
	char m_pad34[0xdc - 0x34];
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
	Rva00308E63 *m_ptr;
};

class Rva0030912A
{
public:
	void rva0030912A(int, StandingWaterRef);
};
class Rva00537F74
{
public:
	void rva00537F74(const AsciiString &);
};
class Rva00537FA0
{
public:
	void rva00537FA0(const AsciiString &);
};
class Rva00308765
{
public:
	void rva00308765(int, const AsciiString &);
};
void *__cdecl operator new(unsigned int);

// WB's unnamed helper at 0x00BE19B0 imports non-river water records. Retail
// proves allocation DC, retained-reference field +4 and boundary interface +30.
// Existing setter and indexed-string rows establish the argument field accesses.
void __cdecl rva0032927A(Rva003294B3Obj *record, int areaSet)
{
	Out *data = reinterpret_cast<Out *>(record);
	StandingWaterRef water(new Rva00308E63(
		data->m_polygon.m_pointsEnd - data->m_polygon.m_pointsBegin, true));
	void (Rva0032927ABoundary::*setBoundary)(const void *) =
		&Rva0032927ABoundary::setBoundary;
	(water.m_ptr->m_boundary.*setBoundary)(&data->m_polygon.m_pointsBegin);
	reinterpret_cast<Rva00537F74 *>(water.m_ptr)->rva00537F74(
		*reinterpret_cast<const AsciiString *>(reinterpret_cast<char *>(record) + 4));
	reinterpret_cast<Rva00537FA0 *>(water.m_ptr)->rva00537FA0(
		*reinterpret_cast<const AsciiString *>(reinterpret_cast<char *>(record) + 8));
	reinterpret_cast<Rva00308765 *>(water.m_ptr)->rva00308765(0,
		*reinterpret_cast<const AsciiString *>(reinterpret_cast<char *>(record) + 0x24));
	reinterpret_cast<Rva00308765 *>(water.m_ptr)->rva00308765(1,
		*reinterpret_cast<const AsciiString *>(reinterpret_cast<char *>(record) + 0x28));
	reinterpret_cast<Rva0030912A *>(areaSet)->rva0030912A(
		*reinterpret_cast<int *>(record), water);
}

// WB 0x00BE2360 identifies this adjacent parser. Retail additionally proves
// the list-head holder at +0x1C and the extended parsed record's flag at +0x74.
bool OldPolygonTriggerDataChunkParserBase::Impl::parsePolygonTriggersChunkImpl(
	DataChunkInput &file, const DataChunkInfo *info)
{
	Rva003294D6Trigger *head = *m_triggerList;
	void *toDelete;
	if (head != 0)
		toDelete = head->destroy(0);
	else
		toDelete = 0;
	operator delete(toDelete);
	*m_triggerList = 0;
	m_standingWaterAreas->rva00282135();
	m_riverAreas->rva00282135();
	void *list = m_triggerList;
	int count = file.readInt();
	PolygonData data;
	for (; count > 0; --count)
	{
		Rva00328E96Parse(file, info->m_version, &data);
		if (static_cast<int>(data.pointCount()) >= 2)
		{
			if (data.m_isWaterArea)
				rva003294B3(reinterpret_cast<Rva003294B3Obj *>(&data),
					reinterpret_cast<int>(m_standingWaterAreas),
					reinterpret_cast<int>(m_riverAreas));
			else
				Rva00328DE4Add(&data, &list);
		}
	}
	return true;
}
