// cl: /DNDEBUG /MD /EHsc
// WorldBuilder names parseWaterAreasChunkImpl in OldPolygonTrigger.cpp at
// 0x00BE2810. Its call graph maps to retail 0x003295B4. Retail proves the
// two area-set pointers at +0x20/+0x24 and the parsed holder's point vector
// at +0x48. The helper and holder names remain opaque where WB supplies none.
#include "../../../../Libraries/Include/Lib/Coord2D.h"
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
