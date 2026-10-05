// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// ??0Rva0056616B@@QAE@ABV0@@Z @0x0052D555 333B
// Copy ctor for Rva0056616B (vtable 0x008689D0) copying 16 members in order via rowed StringBase 0x365F0 vector copy ctors and custom copies then byte at +0xB4.
// Evidence: unlock lane; callees all rowed per packet (StringBase FXList Pod40 Pod88 Rva0052BDE6 Rva0052BE33 AsciiString Pod32 Rva004E32F2 Rva0052CD81 Rva0052C867 Rva0052C8AB E16 Rva005668E9 Rva0052BEF0); prev vector copy family next deleting dtor share layout.
#include "ascii_string.h"

class FXList;
struct BfmePod40;
struct BfmePod88;
class Rva0052BDE6;
class Rva0052BE33;
struct BfmePod32;
class Rva004E32F2;
class Rva0052CD81
{
public:
	Rva0052CD81(const Rva0052CD81 &other);
	~Rva0052CD81();
private:
	char m_pad[12];
};
class Rva0052C867
{
public:
	Rva0052C867(const Rva0052C867 &other);
	~Rva0052C867();
private:
	char m_pad[12];
};
class Rva0052C8AB
{
public:
	Rva0052C8AB(const Rva0052C8AB &other);
	~Rva0052C8AB();
private:
	char m_pad[12];
};
struct BfmeE16;
struct Rva005668E9Element;
class Rva0052BEF0;

namespace _STL {
template <typename T> class allocator {};
template <typename T, typename A> class vector {
public:
	vector(const vector &other);
	~vector();
	T *m_start;
	T *m_finish;
	T *m_end;
};
}

class Rva0056616B {
public:
	Rva0056616B(const Rva0056616B &other);
	virtual ~Rva0056616B();
	AsciiString m_04;
	_STL::vector<FXList, _STL::allocator<FXList> > m_08;
	_STL::vector<BfmePod40, _STL::allocator<BfmePod40> > m_14;
	_STL::vector<BfmePod88, _STL::allocator<BfmePod88> > m_20;
	_STL::vector<Rva0052BDE6, _STL::allocator<Rva0052BDE6> > m_2C;
	_STL::vector<Rva0052BE33, _STL::allocator<Rva0052BE33> > m_38;
	_STL::vector<AsciiString, _STL::allocator<AsciiString> > m_44;
	AsciiString m_50;
	_STL::vector<BfmePod32, _STL::allocator<BfmePod32> > m_54;
	_STL::vector<Rva004E32F2, _STL::allocator<Rva004E32F2> > m_60;
	Rva0052CD81 m_6C;
	Rva0052C867 m_78;
	Rva0052C8AB m_84;
	_STL::vector<BfmeE16, _STL::allocator<BfmeE16> > m_90;
	_STL::vector<Rva005668E9Element, _STL::allocator<Rva005668E9Element> > m_9C;
	_STL::vector<Rva0052BEF0, _STL::allocator<Rva0052BEF0> > m_A8;
	unsigned char m_B4;
};

Rva0056616B::Rva0056616B(const Rva0056616B &other)
	: m_04(other.m_04)
	, m_08(other.m_08)
	, m_14(other.m_14)
	, m_20(other.m_20)
	, m_2C(other.m_2C)
	, m_38(other.m_38)
	, m_44(other.m_44)
	, m_50(other.m_50)
	, m_54(other.m_54)
	, m_60(other.m_60)
	, m_6C(other.m_6C)
	, m_78(other.m_78)
	, m_84(other.m_84)
	, m_90(other.m_90)
	, m_9C(other.m_9C)
	, m_A8(other.m_A8)
	, m_B4(other.m_B4)
{
}
