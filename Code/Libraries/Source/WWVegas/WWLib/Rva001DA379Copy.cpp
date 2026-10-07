// cl: /Ireference/shims/bfme2_ascii /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /O1 /arch:SSE /G7
// stlport
// ?rva001DA379@Rva001DA379@@QAEPAV1@ABV1@@Z @0x001DA379 357B: copy from other
// via StringBase::set 0x000366F0 vector assign 0x001DA05E 0x001D9D75 0x001D9BEE
// then 16+11 ints and 3 single ints; caller 0x001DA837 unblocks 0x001DA770.
#include <vector>
#include "ascii_string.h"

struct Rva001DA05ERecord
{
	char bytes[8];
};

class BfmeStringTailRecord156
{
public:
	char m_pad[156];
};

struct BfmePod8
{
	int a[2];
};

class Rva001DA379Base
{
public:
	virtual ~Rva001DA379Base()
	{
	}
};

class Rva001DA379 : public Rva001DA379Base
{
public:
	Rva001DA379 *rva001DA379(const Rva001DA379 &other);

private:
	char m_pad04[4];
	AsciiString m_str08;
	AsciiString m_str0C;
	int m_10;
	int m_14;
	int m_18;
	int m_1C;
	int m_20;
	int m_24;
	int m_28;
	int m_2C;
	int m_30;
	int m_34;
	int m_38;
	int m_3C;
	int m_40;
	int m_44;
	int m_48;
	int m_4C;
	_STL::vector<Rva001DA05ERecord, _STL::allocator<Rva001DA05ERecord> > m_vec50;
	int m_5C;
	_STL::vector<Rva001DA05ERecord, _STL::allocator<Rva001DA05ERecord> > m_vec60;
	int m_6C;
	_STL::vector<Rva001DA05ERecord, _STL::allocator<Rva001DA05ERecord> > m_vec70;
	int m_7C;
	_STL::vector<BfmeStringTailRecord156, _STL::allocator<BfmeStringTailRecord156> > m_vec80;
	int m_8C;
	int m_90;
	int m_94;
	int m_98;
	int m_9C;
	int m_A0;
	int m_A4;
	int m_A8;
	int m_AC;
	int m_B0;
	int m_B4;
	_STL::vector<BfmePod8, _STL::allocator<BfmePod8> > m_vecB8;
};

Rva001DA379 *Rva001DA379::rva001DA379(const Rva001DA379 &other)
{
	m_str08.set(other.m_str08);
	m_str0C.set(other.m_str0C);
	m_10 = other.m_10;
	m_14 = other.m_14;
	m_18 = other.m_18;
	m_1C = other.m_1C;
	m_20 = other.m_20;
	m_24 = other.m_24;
	m_28 = other.m_28;
	m_2C = other.m_2C;
	m_30 = other.m_30;
	m_34 = other.m_34;
	m_38 = other.m_38;
	m_3C = other.m_3C;
	m_40 = other.m_40;
	m_44 = other.m_44;
	m_48 = other.m_48;
	m_4C = other.m_4C;
	m_vec50 = other.m_vec50;
	m_5C = other.m_5C;
	m_vec60 = other.m_vec60;
	m_6C = other.m_6C;
	m_vec70 = other.m_vec70;
	m_7C = other.m_7C;
	m_vec80 = other.m_vec80;
	m_8C = other.m_8C;
	m_90 = other.m_90;
	m_94 = other.m_94;
	m_98 = other.m_98;
	m_9C = other.m_9C;
	m_A0 = other.m_A0;
	m_A4 = other.m_A4;
	m_A8 = other.m_A8;
	m_AC = other.m_AC;
	m_B0 = other.m_B0;
	m_B4 = other.m_B4;
	m_vecB8 = other.m_vecB8;
	return this;
}
