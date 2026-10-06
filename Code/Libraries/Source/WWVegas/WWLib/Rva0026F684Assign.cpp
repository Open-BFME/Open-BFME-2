// cl: /Ireference/shims/bfme2_ascii /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ??4Rva0026F684@@QAEAAV0@ABV0@@Z @0x0026F767 339B
// Evidence: same vtable 0x007FABF0 class as ctor 0x0026F5B3 and dtor 0x0026F684; prev/next Rva0026F684Dtor.cpp; callees AsciiString op= pin 0x000366F0 plus vector AsciiString row 0x000BDB46 plus 4B POD assign row 0x0026F4F4 plus OpaqueRefElement4 row 0x00239099; caller 0x0026F9BA.

#include "ascii_string.h"

namespace _STL
{
template <class T> class allocator
{
public:
	allocator() {}
};
template <class T, class A = allocator<T> > class vector
{
public:
	void *_M_start;
	void *_M_finish;
	void *_M_end_of_storage;
	vector &operator=(const vector &that);
};
}

struct OpaqueRefElement4
{
	void *m_ptr;
	OpaqueRefElement4 &operator=(const OpaqueRefElement4 &other);
};

class Rva0026F684
{
public:
	virtual ~Rva0026F684();
	Rva0026F684 &operator=(const Rva0026F684 &other);
private:
	int m_04;
	AsciiString m_08;
	int m_0C;
	_STL::vector<AsciiString> m_10;
	_STL::vector<unsigned int> m_1C;
	AsciiString m_28;
	AsciiString m_2C;
	int m_30;
	int m_34;
	int m_38;
	AsciiString m_3C;
	OpaqueRefElement4 m_40;
	int m_44;
	OpaqueRefElement4 m_48;
	int m_4C;
	int m_50;
	int m_54;
	int m_58;
	int m_5C;
	int m_60;
	int m_64;
	int m_68;
	AsciiString m_6C;
	int m_70;
	AsciiString m_74;
	unsigned char m_78;
	unsigned char m_79;
	AsciiString m_7C;
	int m_80;
	int m_84;
	int m_88;
	AsciiString m_8C;
	int m_90;
	unsigned char m_94;
	int m_98;
};

Rva0026F684 &Rva0026F684::operator=(const Rva0026F684 &other)
{
	m_04 = other.m_04;
	m_08 = other.m_08;
	m_0C = other.m_0C;
	m_10 = other.m_10;
	m_1C = other.m_1C;
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
	m_50 = other.m_50;
	m_54 = other.m_54;
	m_58 = other.m_58;
	m_5C = other.m_5C;
	m_60 = other.m_60;
	m_64 = other.m_64;
	m_68 = other.m_68;
	m_6C = other.m_6C;
	m_70 = other.m_70;
	m_74 = other.m_74;
	m_78 = other.m_78;
	m_79 = other.m_79;
	m_7C = other.m_7C;
	m_80 = other.m_80;
	m_84 = other.m_84;
	m_88 = other.m_88;
	m_8C = other.m_8C;
	m_90 = other.m_90;
	m_94 = other.m_94;
	m_98 = other.m_98;
	return *this;
}
