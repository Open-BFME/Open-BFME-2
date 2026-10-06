// cl: /Ireference/shims/bfme2_ascii /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??4Rva0031804D@@QAEAAV0@ABV0@@Z @0x0031804D (81B): copy-assign copying
// AsciiStrings at +0x4/+0x8 via pinned 0x000366F0, byte +0xC, 4B-POD vector
// at +0x10 via int pin at 0x0021C21B, byte +0x1C, int +0x20, NoCase pair
// vector at +0x24 via rowed 0x00317EBB. Same offsets as Rva00317F6F ctor
// 0x00317F6F; caller at 0x003181C1 unblocks 0x0031816C.
#include "ascii_string.h"
struct NoCaseTreeValue4
{
	char m_body[4];
};
namespace _STL
{
template <class T1, class T2>
struct pair
{
	T1 first;
	T2 second;
};
template <class Type>
class allocator
{
};
template <class Type, class Allocator>
class vector
{
public:
	vector &operator=(const vector &x);
private:
	void *m_start;
	void *m_finish;
	void *m_endOfStorage;
};
}
class Rva0031804D
{
public:
	virtual ~Rva0031804D();
	Rva0031804D &operator=(const Rva0031804D &that);
private:
	AsciiString m_4;
	AsciiString m_8;
	unsigned char m_C;
	char m_padD[3];
	_STL::vector<int, _STL::allocator<int> > m_10;
	unsigned char m_1C;
	char m_pad1D[3];
	int m_20;
	_STL::vector<_STL::pair<const AsciiString, NoCaseTreeValue4>, _STL::allocator<_STL::pair<const AsciiString, NoCaseTreeValue4> > > m_24;
};
Rva0031804D &Rva0031804D::operator=(const Rva0031804D &that)
{
	m_4 = that.m_4;
	m_8 = that.m_8;
	m_C = that.m_C;
	m_10 = that.m_10;
	m_1C = that.m_1C;
	m_20 = that.m_20;
	m_24 = that.m_24;
	return *this;
}
