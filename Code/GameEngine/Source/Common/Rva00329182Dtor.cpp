// cl: /Ireference/shims/bfme2_ascii /EHs /MD
// ??1Out@@QAE@XZ, retail 0x00329182, 97 bytes.
// Non-virtual dtor of parse holder Out in Rva00328A8AParse.cpp: frees Rva0030BB87 buffer at +0x48 via rowed _free 0x00030830 then destroys AsciiString[6] at +0x14 via rowed 0x0048BA39 then AsciiStrings at +0x08/+0x04 via rowed releaseBuffer 0x00036410.
// Evidence: same TU layout as Rva00328A8AParse 0x00328A8A (two AsciiStrings +6 array +Rva0030BB87 at +0x48); caller 0x003295B4 constructs via 0x0032912D then parses then destroys; /EHs (not /EHsc) for map-insert-like state stores around C calls per shape-lever guide.
#include "ascii_string.h"

extern "C" void __cdecl free(void *p);

class DataChunkInput;

struct RGBColor
{
	int c[3];
};

struct Rva0030BB87
{
	void *m_ptr;
	char m_pad[0x2c - 4];
	void rva0030BB87(DataChunkInput &file, int val);
};

struct Out
{
	~Out();
	int m_00;
	AsciiString m_04;
	AsciiString m_08;
	bool m_0c;
	char m_pad0d[3];
	int m_10;
	AsciiString m_14[6];
	bool m_2c;
	char m_pad2d[3];
	RGBColor m_30;
	float m_3c;
	float m_40;
	float m_44;
	Rva0030BB87 m_48;
};

Out::~Out()
{
	if (m_48.m_ptr != 0)
		free(m_48.m_ptr);
}
