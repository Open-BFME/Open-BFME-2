// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0Rva003F9FE6@@QAE@ABV0@@Z @0x003F9FE6 225B
// Copy ctor storing vtable 0x00837898 then copy-constructing AsciiString at +4
// via pinned StringBase copy 0x000365F0, vector<AsciiString> at +8 via rowed
// 0x000BC07E, AsciiString at +0x14 and +0x18 via pinned StringBase copy,
// then 13 dwords +0x1C..+0x4C and 7 bytes +0x50..+0x56.
// Evidence: unlock lane, callees all rowed or pinned, callers 0x003FA121
// 0x00402C18 0x00402F31, landing unblocks 0x003FA118 and 0x00402C0F.
#include "ascii_string.h"


namespace _STL
{
template <class T>
class allocator
{
};

template <class T, class A>
class vector
{
public:
	vector(const vector<T, A> &other);
	~vector();
private:
	char m_pad[12];
};
}

class Rva003F9FE6
{
public:
	virtual void v00() = 0;
	Rva003F9FE6(const Rva003F9FE6 &src);
private:
	AsciiString m_04;
	_STL::vector<AsciiString, _STL::allocator<AsciiString> > m_08;
	AsciiString m_14;
	AsciiString m_18;
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
	unsigned char m_50;
	unsigned char m_51;
	unsigned char m_52;
	unsigned char m_53;
	unsigned char m_54;
	unsigned char m_55;
	unsigned char m_56;
};

Rva003F9FE6::Rva003F9FE6(const Rva003F9FE6 &src)
	: m_04(src.m_04)
	, m_08(src.m_08)
	, m_14(src.m_14)
	, m_18(src.m_18)
{
	m_1C = src.m_1C;
	m_20 = src.m_20;
	m_24 = src.m_24;
	m_28 = src.m_28;
	m_2C = src.m_2C;
	m_30 = src.m_30;
	m_34 = src.m_34;
	m_38 = src.m_38;
	m_3C = src.m_3C;
	m_40 = src.m_40;
	m_44 = src.m_44;
	m_48 = src.m_48;
	m_4C = src.m_4C;
	m_50 = src.m_50;
	m_51 = src.m_51;
	m_52 = src.m_52;
	m_53 = src.m_53;
	m_54 = src.m_54;
	m_55 = src.m_55;
	m_56 = src.m_56;
}

class Rva003FA118 : public Rva003F9FE6
{
public:
	virtual void v00() = 0;
	Rva003FA118(const Rva003FA118 &src);
private:
	int m_58;
	unsigned char m_5C;
	unsigned char m_5D;
	unsigned char m_5E;
};

Rva003FA118::Rva003FA118(const Rva003FA118 &src)
	: Rva003F9FE6(src)
{
	m_58 = src.m_58;
	m_5C = src.m_5C;
	m_5D = src.m_5D;
	m_5E = src.m_5E;
}

// ??0Rva00402C0F@@QAE@ABV0@@Z @0x00402C0F 63B
// Copy ctor of a Rva003F9FE6 sibling storing vtable 0x00837898 then copying
// int at +0x58 and +0x5C plus 4 bytes +0x60..+0x63.
// Evidence: chain lane, callee 0x003F9FE6 rowed, caller 0x00402D4B.
class Rva00402C0F : public Rva003F9FE6
{
public:
	virtual void v00() = 0;
	Rva00402C0F(const Rva00402C0F &src);
private:
	int m_58;
	int m_5C;
	unsigned char m_60;
	unsigned char m_61;
	unsigned char m_62;
	unsigned char m_63;
};

Rva00402C0F::Rva00402C0F(const Rva00402C0F &src)
	: Rva003F9FE6(src)
{
	m_58 = src.m_58;
	m_5C = src.m_5C;
	m_60 = src.m_60;
	m_61 = src.m_61;
	m_62 = src.m_62;
	m_63 = src.m_63;
}
