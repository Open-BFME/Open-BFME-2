// cl: /Ireference/shims/bfme2_ascii /EHsc
// ?length@Rva00513E03@@QBEHXZ @0x00513E03 34B: four-part narrow concat length (Text+String+Text+String); base TextPlusString length at 0x00513B94 plus third pair len at +0x10 plus fourth string len at +0x14; chain from 0x00513B94 landing; callers 0x00513E6F 0x005E3693 0x005E36EA.
#include "ascii_string.h"
class UnicodeString;
class Rva000B3F84Pair
{
public:
	Rva000B3F84Pair() {}
	Rva000B3F84Pair *init(const char *src);
	int write(char *dst);
	const char *m_ptr;
	int m_len;
};
struct AsciiStringRef
{
	int write(char *dst);
	const AsciiString *m_string;
};
struct Rva002226E5TextPlusString
{
	int length() const;
	int write(char *dst);
	Rva000B3F84Pair m_left;
	AsciiStringRef m_right;
};
struct Rva00513E03
{
	int length() const;
	Rva000B3F84Pair m_first;
	const AsciiString *m_second;
	Rva000B3F84Pair m_third;
	const AsciiString *m_fourth;
};
int Rva00513E03::length() const
{
	int third = m_third.m_len;
	int fourth = m_fourth->getLength();
	int base = ((const Rva002226E5TextPlusString *)this)->length();
	return base + fourth + third;
}

// ?length@Rva005E3693@@QBEHXZ @0x005E3693 13B: five-part extension (four-part base at 0x00513E03 plus fifth pair len at +0x1C); chain from 0x00513E03 landing.
struct Rva005E3693 : Rva00513E03
{
	int length() const;
	Rva000B3F84Pair m_fifth;
};
int Rva005E3693::length() const
{
	return Rva00513E03::length() + m_fifth.m_len;
}

// ?length@Rva005E366A@@QBEHXZ @0x005E366A 13B: three-part extension (TextPlusString base at 0x00513B94 plus third pair len at +0x10); chain from 0x00513B94 landing.
struct Rva005E366A : Rva002226E5TextPlusString
{
	int length() const;
	Rva000B3F84Pair m_third;
};
int Rva005E366A::length() const
{
	return Rva002226E5TextPlusString::length() + m_third.m_len;
}

// ?length@Rva005F1B75@@QBEHXZ @0x005F1B75 27B: three-part string extension (TextPlusString base at 0x00513B94 plus third string len at +0x0C); chain from 0x00513B94 landing; callers 0x005F1BAA 0x005F1D47.
struct Rva005F1B75 : Rva002226E5TextPlusString
{
	int length() const;
	int write(char *dst);
	AsciiStringRef m_third;
};
int Rva005F1B75::length() const
{
	int third = m_third.m_string->getLength();
	int base = Rva002226E5TextPlusString::length();
	return base + third;
}

int Rva005F1B75::write(char *dst)
{
	int n = Rva002226E5TextPlusString::write(dst);
	return n + m_third.write(dst + n);
}

// ?length@Rva005F1BAA@@QBEHXZ @0x005F1BAA 13B: four-part extension (three-part string base at 0x005F1B75 plus fourth pair len at +0x14); chain from 0x005F1B75 landing.
struct Rva005F1BAA : Rva005F1B75
{
	int length() const;
	Rva000B3F84Pair m_fourth;
};
int Rva005F1BAA::length() const
{
	return Rva005F1B75::length() + m_fourth.m_len;
}
