// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva00402BE3@@QAE@ABVAsciiString@@@Z @0x00402BE3 44B
// Honest Rva ctor: AsciiString at +0 via rowed ascii_string copy 0x001D8F56,
// vector<BfmeE16> at +4 via rowed Vector_base 0x00211E58, ints at +0x10/+0x14/+0x18
// zeroed. Caller 0x002140DB news 0x1C bytes and calls this with its AsciiString arg.
// Flags and bfmealloc shim copied from sibling Rva003F9FE6CopyCtor.cpp.
#include <vector>
template <typename T>
class StringBase
{
	friend class AsciiString;
	StringBase(const StringBase<T> &other);
	~StringBase();
	void releaseBuffer();
	T *m_data;
};
class AsciiString : public StringBase<char>
{
public:
	AsciiString();
	AsciiString(const AsciiString &other);
	~AsciiString();
};
struct BfmeE16 { float x, y, z, w; };
class Rva00402BE3
{
public:
	Rva00402BE3(const AsciiString &name);
private:
	AsciiString m_name;
	_STL::vector<BfmeE16, _STL::allocator<BfmeE16> > m_vec;
	int m_10;
	int m_14;
	int m_18;
};
Rva00402BE3::Rva00402BE3(const AsciiString &name)
	: m_name(name)
	, m_vec()
	, m_10(0)
	, m_14(0)
	, m_18(0)
{
}
