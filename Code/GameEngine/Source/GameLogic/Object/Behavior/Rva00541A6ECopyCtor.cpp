// cl: /O1 /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0Rva00541A6E@@QAE@ABV0@@Z @0x00541A6E 66B. Copy ctor for member-plus-vector holder.
// Evidence: same shape as neighbour Rva00541913 copy 0x00541913 66B; calls rowed
// Rva00330757Member default ctor 0x00330757 for +0 then rowed vector Rva0054103E
// copy ctor 0x0054147B for +0x10 then copies dword +0x1c; caller 0x00541F1F.
#include <vector>

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

class Rva0054103E
{
public:
	unsigned int m_data[5];
};

class Rva00541A6E
{
public:
	Rva00541A6E(const Rva00541A6E &that);
private:
	Rva00330757Member m_00;
	_STL::vector<Rva0054103E> m_10;
	int m_1C;
};

Rva00541A6E::Rva00541A6E(const Rva00541A6E &that)
	: m_10(that.m_10)
	, m_1C(that.m_1C)
{
}
