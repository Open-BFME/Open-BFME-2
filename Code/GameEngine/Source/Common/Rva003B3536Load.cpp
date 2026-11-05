// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva003B3536@Rva003B3536@@QAEXAAVDataChunkInput@@G@Z @0x003B3536 123B
// DataChunkInput field loader: two readByte bools then readInt then readByte
// bool then counted-string reader readAsciiString with StringBase set into +0xC.
// Evidence: unlock lane callees all rowed readByte 0x306E9A readInt 0x306E78
// readAsciiString 0x30750A StringBase set 0x366F0 releaseBuffer 0x36410 plus
// caller 0x3B79F1 layout bool+0 bool+1 int+4 bool+8 AsciiString+0xC ret 8.
#include "../../Include/Common/DataChunk.h"
#include "../../Include/GameLogic/ScriptClass.h"

Rva003B3536::Rva003B3536(const Rva003B3536 &other)
	: m_field00(other.m_field00)
	, m_field01(other.m_field01)
	, m_field04(other.m_field04)
	, m_field08(other.m_field08)
	, m_field0C(other.m_field0C)
{
}

void Rva003B3536::rva003B3536(DataChunkInput &input, unsigned short version)
{
	m_field00 = input.readByte() != 0;
	m_field01 = input.readByte() != 0;
	m_field04 = input.readInt();
	m_field08 = input.readByte() != 0;
	m_field0C = input.readAsciiString();
}

// Version parameter established by native Script reader3B79F1 and parser3B8699.
// The body ignores the value; 123 bytes and RET8 are unchanged.
