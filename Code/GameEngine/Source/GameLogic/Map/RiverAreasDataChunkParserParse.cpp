// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /ICode/Libraries/Include /DNDEBUG /MD /EHsc
//
// ?parse@RiverAreasDataChunkParser@@UAE_NAAVDataChunkInput@@PAUDataChunkInfo@@@Z
// retail 0x0030C6C8..0x0030C882 (442 bytes, EH, RET 8).
//
// Identity: WorldBuilder 0x00BAA4F0 is RiverAreasDataChunkParser::parse
// (RiverArea.cpp, asserts 400..459); the sibling of the rowed
// StandingWaterAreasDataChunkParser::parse 0x003091B1, whose layout (the
// area set at +0x0C) and helpers it shares.
//
// What the body does:
// - It clears the area set (pinned 0x00282135) and reads the count.
// - For each record it:
//   - reads the id;
//   - news a 0x94-byte river area (rowed constructor 0x0030C4DE, a most
//     derived object over the shared virtual base) held by a reference;
//   - runs the rowed WaterArea::parse;
//   - reads the four texture names (rowed 0x0030C1C8, WB
//     RiverArea::setTextureName);
//   - reads the colour (RGBColor::setFromInt, rowed 0x0030BD5B), a real
//     (rowed 0x0030BBC8) and an int (rowed 0x0030BBE5);
//   - from version 2 on, reads a level name and stores its index in the
//     four-name table at 0x009B9650 ("Low", "Medium", "High", "UltraHigh";
//     -1 when absent), else -1 (rowed 0x0030BBB4);
//   - parses a quad strip (rowed constructor 0x005388AB and
//     QuadStrip2D::parse) and hands it to the area (rowed 0x0030C157);
//   - inserts the area under its id (rowed RiverAreaSetView::insert).
// The table's original name is unknown; it is defined here under the data
// ledger's address name, which the save side (RiverAreasDataChunkParserSave)
// also reads.
#include "ascii_string.h"
#include "AreaSetEntryView.h"
#include "Lib/RGBColor.h"

typedef int Int;
typedef bool Bool;
typedef float Real;

#include "../../../Include/Common/DataChunk.h"

#include "../../../Include/Common/DataChunkInfo.h"

// Match the quad-strip cleanup emitted by Rva0030C1FCOwnerCtor.cpp:
// the verified game allocator wrapper owns retail's free at 0x00030830.
void __cdecl Rva00030830GameFree(void *);

#include "../../../Include/Common/VBase00C6EE28.h"

// The river area as Rva0030C1FCOwnerCtor.cpp lays it out: the reference
// count of the primary root at +4, the shared virtual base at +0x90.
class Rva0030C1FCRoot
{
public:
	virtual ~Rva0030C1FCRoot();
	Int references;								// +0x04
	char m_pad08[0x30 - 0x08];
};

class Rva0030C1FCOwner : public Rva0030C1FCRoot, public virtual VBase00C6EE28
{
public:
	Rva0030C1FCOwner(Int count);
	virtual ~Rva0030C1FCOwner();
	virtual void s0();
private:
	char m_pad34[0x8C - 0x34];	// this view keeps its vbptr at +0x30
};

class RiverAreaRef
{
public:
	RiverAreaRef(Rva0030C1FCOwner *p) : m_ptr(p)
	{
		if (m_ptr) ++m_ptr->references;
	}
	~RiverAreaRef()
	{
		if (m_ptr) ReleaseTreeHintRef00217D4C(reinterpret_cast<TargetRef00217D4C *>(m_ptr));
	}
	Rva0030C1FCOwner *m_ptr;
};

#include "../../../Include/GameLogic/WaterArea.h"

// The quad strip storage: rowed constructor 0x005388AB; QuadStrip2D::parse.
class Rva005388AB
{
public:
	Rva005388AB();
protected:
	void *m_data;
	char m_pad04[0x24 - 0x04];
};
// The native constructor initializes this storage. Keep the parser's
// observed cleanup local instead of publishing another owner's destructor.
class RiverQuadStripStorage_RV : public Rva005388AB
{
public:
	~RiverQuadStripStorage_RV()
	{
		if (m_data)
			Rva00030830GameFree(m_data);
	}
};
#include "../../../Include/Common/QuadStrip2D.h"
struct Rva005386B7;

class Rva0030C1C8 { public: void rva0030C1C8(Int index, const StringBase<char> &name); };
class Rva0030BDEE { public: void rva0030BD5B(const RGBColor *color); };
#include "../../../Include/Common/Rva0030BBC8.h"
#include "../../../Include/Common/Rva0030BBE5.h"
class Rva0030BBB4 { public: void rva0030BBB4(Int level); };
class Rva0030C129Owner { public: void rva0030C157(Rva005386B7 *strip); };

class Rva00282135
{
public:
	void rva00282135();
};
class RiverAreaSetView
{
public:
	void insert(Int id, AreaRefValueView area);
};

const char *g_00DB9650[] = { "Low", "Medium", "High", "UltraHigh" };

class RiverAreasDataChunkParser
{
public:
	virtual ~RiverAreasDataChunkParser();
	virtual Bool parse(DataChunkInput &file, DataChunkInfo *info);
private:
	void *m_registry;
	void *m_token;
	Rva00282135 *m_areas;							// +0x0C
};

Bool RiverAreasDataChunkParser::parse(DataChunkInput &file, DataChunkInfo *info)
{
	m_areas->rva00282135();
	Int count = file.readInt();
	while (count > 0)
	{
		Int id = file.readInt();
		RiverAreaRef river(new Rva0030C1FCOwner(0));
		reinterpret_cast<WaterArea *>(river.m_ptr)->parse(file, (void *)1);
		for (Int i = 0; i < 4; ++i)
			reinterpret_cast<Rva0030C1C8 *>(river.m_ptr)->rva0030C1C8(i, *(const StringBase<char> *)&file.readAsciiString());
		RGBColor color;
		color.setFromInt(file.readInt());
		reinterpret_cast<Rva0030BDEE *>(river.m_ptr)->rva0030BD5B(&color);
		reinterpret_cast<Rva0030BBC8 *>(river.m_ptr)->rva0030BBC8(file.readReal());
		reinterpret_cast<Rva0030BBE5 *>(river.m_ptr)->rva0030BBE5(file.readInt());
		if (info->version >= 2)
		{
			AsciiString name = file.readAsciiString();
			Int level = -1;
			for (unsigned int j = 0; j < 4; ++j)
			{
				if (name.compare(g_00DB9650[j]) == 0)
				{
					level = j;
					break;
				}
			}
			reinterpret_cast<Rva0030BBB4 *>(river.m_ptr)->rva0030BBB4(level);
		}
		else
		{
			reinterpret_cast<Rva0030BBB4 *>(river.m_ptr)->rva0030BBB4(-1);
		}
		{
			RiverQuadStripStorage_RV strip;
			reinterpret_cast<QuadStrip2D *>(&strip)->parse(file, 1);
			reinterpret_cast<Rva0030C129Owner *>(river.m_ptr)->rva0030C157(reinterpret_cast<Rva005386B7 *>(&strip));
		}
		reinterpret_cast<RiverAreaSetView *>(m_areas)->insert(id, reinterpret_cast<const AreaRefValueView &>(river));
		--count;
	}
	return true;
}
