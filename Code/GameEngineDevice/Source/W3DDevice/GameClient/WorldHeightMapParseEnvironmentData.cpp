// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ?ParseEnvironmentDataChunk@WorldHeightMap@@SA_NAAVDataChunkInput@@PAUDataChunkInfo@@PAX@Z,
// retail 0x000AE275..0x000AE37E (265B), cdecl, returns true.
//
// Map-file "EnvironmentData" chunk reader. Version 3 and later carries two
// reals stored at TheTerrainRenderObject +0x37E4 / +0x37E8 (otherwise the
// current values are written back); version 2 and later carries a flag byte.
// Two names follow: the first goes with the flag to the terrain render
// object's 0x0006ABE7 and the second (assigned over the first) to its
// 0x0006ACBD; both take the AsciiString by value.
//
// Evidence (target): the only reference to this body is the
// registerParser call at 0x000AF69D in WorldHeightMap::parse (unrowed
// 0x000AF238; WorldBuilder twin 0x76B780 carries that name and
// WorldHeightMap.cpp) with the label "EnvironmentData" (0x007C5CDC).
// WorldBuilder twin 0x76D9D0 (callgraph lead) has the same body. Callees
// read at the retail REL32s: DataChunkInput::readReal 0x00306E56 /
// readByte 0x00306E9A / readAsciiString 0x0030750A (rowed) / StringBase
// copy ctor 0x000365F0 / StringBase::set 0x000366F0 / releaseBuffer
// 0x00036410 / pinned BaseHeightMapRenderObjClass::rva0006ABE7 and rowed
// rva0006ACBD. Global TheTerrainRenderObject (0x009E1EAC, data ledger).
// The parser name follows the Parse...DataChunk convention of the other
// WorldHeightMap::parse registrations; the field names stay address-derived.
#include "ascii_string.h"

typedef float Real;
typedef bool Bool;

class DataChunkInput
{
public:
	Real readReal();
	unsigned char readByte();
	AsciiString readAsciiString();
};

struct DataChunkInfo
{
	AsciiString label;
	AsciiString parentLabel;
	unsigned short version;
	int dataSize;
};

class BaseHeightMapRenderObjClass
{
public:
	void rva0006ABE7(AsciiString name, bool flag);
	void rva0006ACBD(AsciiString name);

	char m_pad0000[0x37E4];
	Real m_37E4;	// +0x37E4
	Real m_37E8;	// +0x37E8
};

extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;

class WorldHeightMap
{
public:
	static Bool ParseEnvironmentDataChunk(DataChunkInput &file, DataChunkInfo *info, void *userData);
};

Bool WorldHeightMap::ParseEnvironmentDataChunk(DataChunkInput &file, DataChunkInfo *info, void *userData)
{
	Real a = TheTerrainRenderObject->m_37E4;
	Real b = TheTerrainRenderObject->m_37E8;
	Bool flag = false;
	if (info->version >= 3)
	{
		a = file.readReal();
		b = file.readReal();
	}
	TheTerrainRenderObject->m_37E4 = a;
	TheTerrainRenderObject->m_37E8 = b;
	if (info->version >= 2)
		flag = file.readByte() != 0;
	AsciiString name = file.readAsciiString();
	TheTerrainRenderObject->rva0006ABE7(name, flag);
	name = file.readAsciiString();
	TheTerrainRenderObject->rva0006ACBD(name);
	return true;
}
