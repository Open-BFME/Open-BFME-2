// cl: /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva00541913@@QAE@ABV0@@Z @0x00541913 66B. Copy ctor for member-plus-vector holder.
// Evidence: calls rowed Rva00330757Member default ctor 0x00330757 for +0 then rowed vector BfmePod28 copy ctor 0x00541434 for +0x10 then copies dword +0x1c; caller 0x00541F1F; prev/next are vector bodies.
// Honest Rva name; /O1 for push/mov idioms; /EHsc for vector copy unwind; bfmealloc for vector allocator.
#include <vector>

struct BfmePod28 {
	int a[7];
};

struct BfmeE16 {
	float x;
	float y;
	float z;
	float w;
};

class Rva00330757Member
{
public:
	Rva00330757Member();
private:
	_STL::vector<BfmeE16> m_items;
	int m_flags;
};

class Rva00541913
{
public:
	Rva00541913(const Rva00541913 &that);
private:
	Rva00330757Member m_00;
	_STL::vector<BfmePod28> m_10;
	int m_1C;
};

Rva00541913::Rva00541913(const Rva00541913 &that)
	: m_10(that.m_10)
	, m_1C(that.m_1C)
{
}
