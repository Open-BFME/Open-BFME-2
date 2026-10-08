// ?Rva00328DE4Add@@YAXPAXPAPAX@Z
// partial score=0.85 date=2026-10-08
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

struct Out
{
	Out();
	~Out();
	char m_pad00[0x0c];
	bool m_isRiver;
	char m_pad0d[0x48 - 0x0d];
	Coord2D *m_pointsBegin;
	Coord2D *m_pointsEnd;
	char m_pad50[0x74 - 0x50];
	unsigned int pointCount() const { return m_pointsEnd - m_pointsBegin; }
};

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
void *__cdecl operator new(unsigned int);

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

// Target-proven trigger prefix; this constructor's original name is unresolved.
class Rva002E3FAB
{
public:
	Rva002E3FAB(int, int, bool);
	virtual void *destroy(int);
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
	virtual void setBoundary(const void *);
	char m_pad04[0x3c - 4];
	Rva002E3FAB *m_next;
	AsciiString m_name;
	char m_pad44[8];
	AsciiString m_extra;
	char m_pad50[0x64 - 0x50];
};

struct Rva002E3E2AResult
{
	Rva002E3FAB *m_ptr;
	void detach() { m_ptr = 0; }
	~Rva002E3E2AResult()
	{
		if (m_ptr)
			m_ptr->destroy(1);
	}
};

class Rva000AD6F4
{
public:
	Rva000AD6F4(Rva002E3FAB *p) : m_ptr(p) {}
	~Rva000AD6F4();
	Rva002E3E2AResult rva002E3E2A();
	Rva002E3FAB *m_ptr;
};

// WB 0x00BE1500 is the unnamed non-water trigger importer called by the
// polygon parser. Retail independently proves allocation size 0x64, next +3C,
// strings +40/+4C, and transfer into the caller's current list link.
void __cdecl Rva00328DE4Add(void *record, void **linkPtr)
{
	Out *data = static_cast<Out *>(record);
	Rva000AD6F4 trigger(new Rva002E3FAB(*static_cast<int *>(record),
		data->m_pointsEnd - data->m_pointsBegin, true));
	void (Rva002E3FAB::*setBoundary)(const void *) = &Rva002E3FAB::setBoundary;
	(trigger.m_ptr->*setBoundary)(&data->m_pointsBegin);
	reinterpret_cast<StringBase<char> *>(&trigger.m_ptr->m_name)->set(
		*reinterpret_cast<StringBase<char> *>(static_cast<char *>(record) + 4));
	reinterpret_cast<StringBase<char> *>(&trigger.m_ptr->m_extra)->set(
		*reinterpret_cast<StringBase<char> *>(static_cast<char *>(record) + 8));
	*static_cast<Rva002E3FAB **>(*linkPtr) = trigger.m_ptr;
	*linkPtr = trigger.m_ptr ? &trigger.m_ptr->m_next : 0;
	trigger.rva002E3E2A().detach();
}
