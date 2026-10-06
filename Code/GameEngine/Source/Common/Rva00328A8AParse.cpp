// cl: /Ireference/shims/bfme2_ascii /EHsc /MD
// ?Rva00328A8AParse@@YAXAAVDataChunkInput@@HPAX@Z, retail 0x00328A8A, 272 bytes.
// Parses DataChunkInput into holder: int plus 2 AsciiStrings plus bool plus int plus 6 AsciiStrings plus bool plus RGBColor plus 3 floats plus rowed 0x0030BB87.
// Evidence: chain from 0x0030BB87; caller 0x003295B4 passes DataChunkInput plus word plus out; callees readInt 0x00306E78 readByte 0x00306E9A readReal 0x00306E56 rva0030750A 0x0030750A set 0x000366F0 releaseBuffer 0x00036410 setFromInt 0x00004EDF 0x0030BB87 rowed.
#include "ascii_string.h"
class DataChunkInput
{
public:
	int readInt();
	unsigned char readByte();
	float readReal();
	AsciiString rva0030750A();
};
struct RGBColor
{
	int c[3];
	void setFromInt(int v);
};
struct Rva0030BB87
{
	void rva0030BB87(DataChunkInput &file, int val);
};
struct Out
{
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
	char m_48[0x2c];
};
void __cdecl Rva00328A8AParse(DataChunkInput &file, int unused, void *outPtr)
{
	Out &out = *(Out *)outPtr;
	out.m_00 = file.readInt();
	{
		out.m_04 = file.rva0030750A();
	}
	{
		out.m_08 = file.rva0030750A();
	}
	out.m_0c = file.readByte() != 0;
	out.m_10 = file.readInt();
	AsciiString *p = out.m_14;
	int n = 6;
	do {
		*p = file.rva0030750A();
		++p;
	} while (--n != 0);
	out.m_2c = file.readByte() != 0;
	out.m_30.setFromInt(file.readInt());
	out.m_3c = file.readReal();
	out.m_40 = file.readReal();
	out.m_44 = file.readReal();
	((Rva0030BB87 *)((char *)&out + 0x48))->rva0030BB87(file, 1);
}
