// cl: /Ireference/shims/bfme2_ascii /ICode/Libraries/Include /O1 /MD /EHsc /arch:SSE
//
// Retail 0x0030C2CE, 316 bytes: saves the river areas through DataChunkOutput:
// opens the "RiverAreas" chunk, writes the area count, then walks the
// collection with an 8-byte {store, index} cursor, writing each element's id,
// the area's 0x00537EAD block, its four strings, colour, floats, the enum
// string looked up in the 0x00DB9650 table and the 0x0053850B block.
// The element address is built from two separate index products and a
// barrier after the base pointer: retail keeps shl ecx,3 / [ecx+eax+4] (no lea).
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
#include "ascii_string.h"
#include "Lib/RGBColor.h"

#include "../../../Include/Common/DataChunkOutput.h"

#include "../../../Include/GameLogic/Rva00537EAD.h"

class Rva0053850B
{
public:
	void rva0053850B(DataChunkOutput *output);
};

extern const char *g_00DB9650[];

struct RiverAreaEntry
{
	int m_int00;
	void *m_ptr04;
};

struct Rva0030C2CEArea
{
	char m_pad00[0x40];
	AsciiString m_textureNames[4];
	RGBColor m_color;
	float m_opacity;
	int m_int60;
	int m_int64;
	Rva0053850B m_quadStrip;
};

class RiverAreaSet
{
public:
	char m_pad00[0x14];
	RiverAreaEntry *m_begin;
	RiverAreaEntry *m_end;
};

struct RiverAreaIterator
{
	RiverAreaSet *m_store;
	int m_index;
};

// Existing neutral cdecl binding at 0x0007E394 (pin _rva0007E394CursorEqual):
// equality of two 8-byte {store, index} cursors, both by reference. The body is
// kept visible and out of line (as W3DWaterStandingWaveQuery.cpp does): retail's
// caller scheduling needs the callee's side effects known.
extern "C" inline __declspec(noinline) bool __cdecl rva0007E394CursorEqual(const RiverAreaIterator &a, const RiverAreaIterator &b)
{
	return a.m_store == b.m_store && a.m_index == b.m_index;
}

void __cdecl saveRiverAreas(RiverAreaSet *coll, DataChunkOutput *out)
{
	out->openDataChunk("RiverAreas", 2);
	int count = (int)(coll->m_end - coll->m_begin);
	out->writeInt(count);
	RiverAreaIterator endCur;
	RiverAreaIterator cur;
	endCur.m_store = coll;
	endCur.m_index = (int)(coll->m_end - coll->m_begin);
	cur.m_store = coll;
	cur.m_index = 0;
	unsigned char atEnd = rva0007E394CursorEqual(cur, endCur);
	if (atEnd == false)
	{
		do
		{
			RiverAreaEntry *begin = cur.m_store->m_begin;
			int idx = cur.m_index;
			{
			char *base = (char *)begin;
			_ReadWriteBarrier();
			int off = idx * 8;
			int idOffset = cur.m_index * 8;
			Rva0030C2CEArea *area = (Rva0030C2CEArea *)*(void **)(base + off + 4);
			_ReadWriteBarrier();
			out->writeInt(*(int *)(base + idOffset));
			((Rva00537EAD *)area)->rva00537EAD(out);
			AsciiString *asciiString = area->m_textureNames;
			for (int k = 4; k > 0; --k)
			{
				out->writeAsciiString(*asciiString);
				++asciiString;
			}
			out->writeInt(area->m_color.getAsInt());
			out->writeReal(area->m_opacity);
			out->writeInt(area->m_int64);
			AsciiString tmp;
			if (area->m_int60 >= 0 && area->m_int60 < 4)
				((StringBase<char> &)tmp).set(g_00DB9650[area->m_int60]);
			out->writeAsciiString(tmp);
			area->m_quadStrip.rva0053850B(out);
			}
			++cur.m_index;
		} while (rva0007E394CursorEqual(cur, endCur) == false);
	}
	out->closeDataChunk();
}
