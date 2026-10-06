// cl: /Ireference/shims/bfme2_ascii /MD
// ?rva00537EAD@Rva00537EAD@@QAEXPAVDataChunkOutput@@@Z @0x00537EAD 60B writes AsciiStrings at +0x20/+0x24 float at +0x28 byte at +0x2C via DataChunkOutput.
// Evidence: packet disassembly; callees rowed writeAsciiString 0x00307033 writeReal 0x00306CFF writeByte 0x00306D17; callers 0x00308B38 0x0030C2CE 0x0030CAF8.
#include "ascii_string.h"

class DataChunkOutput
{
public:
	void writeAsciiString(const AsciiString &s);
	void writeReal(float v);
	void writeByte(unsigned char v);
};

class Rva00537EAD
{
public:
	void rva00537EAD(DataChunkOutput *output);

private:
	unsigned char m_pad00[0x20];
	AsciiString m_str20;                // +0x20
	AsciiString m_str24;                // +0x24
	float m_float28;                    // +0x28
	unsigned char m_byte2C;             // +0x2C
};

void Rva00537EAD::rva00537EAD(DataChunkOutput *output)
{
	output->writeAsciiString(m_str20);
	output->writeAsciiString(m_str24);
	output->writeReal(m_float28);
	output->writeByte(m_byte2C);
}
