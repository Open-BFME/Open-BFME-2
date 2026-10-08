// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /O1 /arch:SSE /G7
// ?parse@WaterArea@@QAEXAAVDataChunkInput@@PAX@Z @0x00537FCC 145B DataChunkInput field loader via rowed setters.
// Evidence: packet disassembly; same this calls 0x537F74+0x20 0x537FA0+0x24 0x537E90 float 0x537E7C bool; callees rowed readAsciiString readReal readByte releaseBuffer.
#include "ascii_string.h"

class DataChunkInput
{
public:
	AsciiString readAsciiString();
	float readReal();
	unsigned char readByte();
};

class Rva00537F74
{
public:
	void rva00537F74(const AsciiString &v);
};

class Rva00537FA0
{
public:
	void rva00537FA0(const AsciiString &v);
};

class Rva00537E90
{
public:
	void rva00537E90(float v);
};

class Rva00537E7C
{
public:
	void rva00537E7C(bool v);
};

class WaterArea
{
public:
	void parse(DataChunkInput &input, void *info);
};

void WaterArea::parse(DataChunkInput &input, void *)
{
	((Rva00537F74 *)this)->rva00537F74(input.readAsciiString());
	((Rva00537FA0 *)this)->rva00537FA0(input.readAsciiString());
	((Rva00537E90 *)this)->rva00537E90(input.readReal());
	((Rva00537E7C *)this)->rva00537E7C(input.readByte() != 0);
}
