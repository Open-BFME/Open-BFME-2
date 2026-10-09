// cl: /O1 /G7 /arch:SSE /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /D_CRTIMP= /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// flags: region default (reverse/retail_inventory/flag_regions.csv)
// stlport
//
// BaseTemplateLibrary's map-file chunk parser (BFME2 AIBaseTemplate.cpp).
// WorldBuilder's debug build names the body (WB 0x01330A90,
// BaseTemplateLibrary::parseBaseTemplateDataChunk, AIBaseTemplate.cpp:324
// assert "Incorrect data file length.") and keeps its statement order;
// retail 0x0041ED84 has the same reads, the same rowed callees and the same
// version tests (4 for the two trailing base fields, 2 for the trailing
// list, 5 for its names, 3 for Real points). The records go to the rowed
// BaseTemplateLibrary::addToSideBasesMap 0x0041E9D2 (WB 0x01330F80, the
// same call site 0x0041EEB3); one it refuses is destroyed and freed through
// the global operator delete (::delete: virtual slot 0 with flag 0, then
// operator delete). The trailing point lists are read and dropped, as in WB;
// their vector<Coord2D>::push_back is the ICF-folded 8-byte-element body at
// 0x00539A2E, pinned there by fold proof from this unit.
//
// Base-template record (target): 0x60 bytes built by the rowed ctor
// 0x00573E7C (Rva00573E7CCtor.cpp) on the shared base whose rowed setter
// 0x00573A00 copies the position and drops it onto the terrain
// (Rva00573A00Set.cpp). Fields written here: +0x04 Real, +0x0C template name,
// +0x2C name ("Unnamed" when empty), +0x3C Real, +0x50 Int.

#include <stdlib.h>
namespace _STL { void __cdecl free(void *block) throw(...); }
#define free _STL::free
#include "../../../../../../reference/shims/bfme_stlport_unsigned_max_link/unsigned_max.h"
#include <vector>
#undef free

#include "ascii_string.h"
#include "../../../../../Libraries/Include/Lib/Coord2D.h"
#include "../../../../../Libraries/Include/Lib/Coord3D.h"

enum NameKeyType { NAMEKEY_INVALID = 0 };

struct DataChunkInfo
{
	AsciiString label;
	AsciiString parentLabel;
	unsigned short version;				// +0x08
	int dataSize;
};

class DataChunkInput
{
public:
	int readInt();						// 0x00306E78
	float readReal();					// 0x00306E56
	NameKeyType readNameKey();			// 0x003077E0
	AsciiString readAsciiString();		// 0x0030750A
};

// The records' shared base; its position setter is rowed at 0x00573A00.
struct Rva00573A00
{
	virtual ~Rva00573A00();
	void rva00573A00(const Coord3D *pos);	// 0x00573A00

	float m_04;							// +0x04
	char m_pad08[0x0C - 0x08];
	AsciiString m_templateName;			// +0x0C
	char m_pad10[0x2C - 0x10];
	AsciiString m_name;					// +0x2C
	Coord3D m_pos;						// +0x30
	float m_3c;							// +0x3C
};

// The base-template record, rowed under its constructor's address name.
class Rva00573E7C : public Rva00573A00
{
public:
	Rva00573E7C();						// 0x00573E7C
	virtual ~Rva00573E7C();

	Coord3D m_40;						// +0x40
	float m_4c;							// +0x4C
	int m_50;							// +0x50
	bool m_54;
	char m_pad55[0x58 - 0x55];
	unsigned int m_58;
	unsigned int m_5c;
};

// The ledger's spelling of addToSideBasesMap types the record parameter as a
// ModuleData pointer.
class ModuleData;

class BaseTemplateLibrary
{
public:
	bool addToSideBasesMap(NameKeyType side, const ModuleData *base);	// 0x0041E9D2
	bool parseBaseTemplateDataChunk(DataChunkInput &file, DataChunkInfo *info);
};

// BaseTemplateLibrary::parseBaseTemplateDataChunk, retail 0x0041ED84.
bool BaseTemplateLibrary::parseBaseTemplateDataChunk(DataChunkInput &file, DataChunkInfo *info)
{
	NameKeyType side = file.readNameKey();
	int count = file.readInt();
	for (int i = 0; i < count; ++i)
	{
		Rva00573E7C *base = new Rva00573E7C;
		AsciiString name = file.readAsciiString();
		if (name != AsciiString::TheEmptyString)
			base->m_name = name;
		else
			base->m_name = AsciiString("Unnamed");
		base->m_templateName = file.readAsciiString();

		Coord3D pos;
		pos.x = file.readReal();
		pos.y = file.readReal();
		pos.z = file.readReal();
		base->rva00573A00(&pos);
		base->m_3c = file.readReal();
		if (info->version >= 4)
		{
			base->m_04 = (float)file.readInt();
			base->m_50 = file.readInt();
		}

		if (!addToSideBasesMap(side, (const ModuleData *)base))
			::delete base;
	}

	if (info->version >= 2)
	{
		int numLists = file.readInt();
		for (int i = 0; i < numLists; ++i)
		{
			AsciiString listName;
			if (info->version >= 5)
				listName = file.readAsciiString();
			int numPoints = file.readInt();
			if (numPoints)
			{
				_STL::vector<Coord2D> points;
				for (int j = 0; j < numPoints; ++j)
				{
					Coord2D pt;
					if (info->version >= 3)
					{
						pt.x = file.readReal();
						pt.y = file.readReal();
					}
					else
					{
						pt.x = (float)file.readInt();
						pt.y = (float)file.readInt();
						file.readInt();
					}
					points.push_back(pt);
				}
			}
		}
	}
	return true;
}
