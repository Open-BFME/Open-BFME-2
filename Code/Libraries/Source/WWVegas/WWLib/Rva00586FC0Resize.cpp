// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /G7 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /EHs
// ?rva00586FC0@Rva00586FC0@@QAEXIVRva00585B16@@@Z @0x00586FC0 108B. The 0x54 element and deque layout follow the adjacent matched vector family; retail supplies offsets and call sequence. Retail's erase call resolves to the Rva00586E86Element vector row.
// stlport
#include <vector>
#include <deque>

struct BfmeE12
{
	float x;
	float y;
	float z;
};

struct Ints12
{
	int m_00;
	int m_04;
	int m_08;
};

class Rva00585B16
{
public:
	Rva00585B16(const Rva00585B16 &other);
	~Rva00585B16() {}

private:
	int m_00;
	float m_04;
	float m_08;
	float m_0C;
	int m_10;
	int m_14;
	int m_18;
	unsigned char m_1C;
	char m_pad1D[3];
	int m_20;
	int m_24;
	_STL::deque<BfmeE12, _STL::allocator<BfmeE12> > m_28;
	int m_50;
};

typedef _STL::vector<Rva00585B16, _STL::allocator<Rva00585B16> > Rva00586FC0Vector;

struct Rva00586E86Element
{
	char bytes[0x54];
};
typedef _STL::vector<Rva00586E86Element, _STL::allocator<Rva00586E86Element> > Rva00586FC0EraseVector;
// Both operations have matched providers; this wrapper calls their native
// bodies rather than instantiating competing vector/deque helper families.
namespace _STL {
template <> void vector<Rva00585B16>::_M_fill_insert(
    Rva00585B16 *, size_type, const Rva00585B16 &);
template <> Rva00586E86Element *vector<Rva00586E86Element>::erase(
    Rva00586E86Element *, Rva00586E86Element *);
}


class Rva00586FC0
{
public:
	void rva00586FC0(unsigned int count, Rva00585B16 value);

private:
	Rva00585B16 *m_start;
	Rva00585B16 *m_finish;
	Rva00585B16 *m_endOfStorage;
};

void Rva00586FC0::rva00586FC0(unsigned int count, Rva00585B16 value)
{
	int oldCount = (int)((char *)m_finish - (char *)m_start) / 0x54;
	if (count < (unsigned int)oldCount)
	{
		((Rva00586FC0EraseVector *)this)->erase((Rva00586E86Element *)(m_start + count), (Rva00586E86Element *)m_finish);
	}
	else
	{
		int currentCount = (int)((char *)m_finish - (char *)m_start) / 0x54;
		unsigned int insertCount = count - currentCount;
		((Rva00586FC0Vector *)this)->_M_fill_insert(m_finish, insertCount, value);
	}
}
