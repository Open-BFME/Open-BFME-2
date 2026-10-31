// cl: /Ireference/shims/bfme2_ascii /O1 /MD /arch:SSE
// ?saveStandingWaveAreas@@YAXPAVRva0030CAF8Collection@@PAVDataChunkOutput@@@Z, retail 0x0030CAF8, 323 bytes.
// StandingWaveAreas save via DataChunkOutput: openDataChunk StandingWaveAreas, write count, cursor-iterate areas, write int, Rva00537EAD, Rva0030B2FE at +0x38, cvttss2si floats, AsciiString at +0x9c. Evidence: packet disassembly, chain from 0x00537EAD, sibling 0x0030C2CE cursor pattern.
#include "ascii_string.h"

class DataChunkOutput
{
public:
	void openDataChunk(char *name, unsigned short unk);
	void writeInt(int v);
	void writeReal(float v);
	void writeAsciiString(const AsciiString &s);
	void closeDataChunk();
};

class Rva00537EAD
{
public:
	void rva00537EAD(DataChunkOutput *output);
};

class Rva0030B2FE
{
public:
	void rva0030B2FE(DataChunkOutput *output);
};

struct Rva0030CAF8Elem
{
	int m_int00;
	void *m_area;
};

struct Rva0030CAF8Area
{
	char m_pad00[0x78];
	float m_f78;
	int m_i7C;
	int m_i80;
	int m_i84;
	float m_f88;
	float m_f8C;
	float m_f90;
	float m_f94;
	float m_f98;
	AsciiString m_s9C;
	int m_iA0;
};

class Rva0030CAF8Collection
{
public:
	char m_pad00[0x14];
	Rva0030CAF8Elem *m_begin;
	Rva0030CAF8Elem *m_end;
};

struct Rva0030CAF8Cursor
{
	Rva0030CAF8Collection *m_store;
	int m_index;
};

// ?Rva0030CAF8CursorEqual present-unmatched
extern "C" __declspec(noinline) bool __cdecl Rva0030CAF8CursorEqual(const Rva0030CAF8Cursor &a, const Rva0030CAF8Cursor &b)
{
	return a.m_store == b.m_store && a.m_index == b.m_index;
}

void __cdecl saveStandingWaveAreas(Rva0030CAF8Collection *coll, DataChunkOutput *out)
{
	out->openDataChunk("StandingWaveAreas", 2);
	int count = (int)(coll->m_end - coll->m_begin);
	out->writeInt(count);
	Rva0030CAF8Cursor endCur;
	Rva0030CAF8Cursor cur;
	endCur.m_store = coll;
	endCur.m_index = (int)(coll->m_end - coll->m_begin);
	cur.m_store = coll;
	cur.m_index = 0;
	if (Rva0030CAF8CursorEqual(cur, endCur) == false)
	{
		do
		{
			Rva0030CAF8Elem *begin = cur.m_store->m_begin;
			int idx = cur.m_index;
			Rva0030CAF8Area *area = (Rva0030CAF8Area *)begin[idx].m_area;
			out->writeInt(begin[idx].m_int00);
			((Rva00537EAD *)area)->rva00537EAD(out);
			((Rva0030B2FE *)((char *)area + 0x38))->rva0030B2FE(out);
			out->writeInt((int)area->m_f78);
			out->writeInt(area->m_i7C);
			out->writeInt(area->m_i80);
			out->writeInt(area->m_i84);
			out->writeInt((int)area->m_f88);
			out->writeInt((int)area->m_f8C);
			out->writeInt((int)area->m_f90);
			out->writeInt((int)area->m_f94);
			out->writeInt((int)area->m_f98);
			out->writeAsciiString(area->m_s9C);
			out->writeInt(area->m_iA0);
			++cur.m_index;
		} while (Rva0030CAF8CursorEqual(cur, endCur) == false);
	}
	out->closeDataChunk();
}
