// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??4BfmeAssignRecord172@@QAEAAU0@ABU0@@Z @0x001EB20E 84B: honest 172B record
// assign: AsciiString at +0x04 via pinned 0x366F0 then ints +0x08/+0x0C then
// 128B block +0x10..0x8F via rep movsd then int +0x90 then sub-record at
// +0x94 via rowed ??4Rva001EAFC1 0x001EAFC1; +0x00 skipped (retail never
// copies; possibly vptr/ID); returns *this (ret 4). Callers in
// stlport_asciistring_record_bodies.cpp (copy_backward/fill/dup) plus
// 0x004E0A04. Same // cl: as sibling.
#include "ascii_string.h"
class Rva001EAFC1
{
public:
	Rva001EAFC1 &operator=(const Rva001EAFC1 &other);
private:
	unsigned char m_data[24];
};
struct Block128 { int a[32]; };
struct BfmeAssignRecord172
{
	int m_00;
	AsciiString m_04;
	int m_08;
	int m_0C;
	Block128 m_10;
	int m_90;
	Rva001EAFC1 m_94;
	BfmeAssignRecord172 &operator=(const BfmeAssignRecord172 &other);
};
BfmeAssignRecord172 &BfmeAssignRecord172::operator=(const BfmeAssignRecord172 &other)
{
	m_04 = other.m_04;
	m_08 = other.m_08;
	m_0C = other.m_0C;
	m_10 = other.m_10;
	m_90 = other.m_90;
	m_94 = other.m_94;
	return *this;
}
