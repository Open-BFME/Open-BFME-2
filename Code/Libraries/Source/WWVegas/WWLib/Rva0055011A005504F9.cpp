// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?rva005504F9@Rva0055011A@@UAEXABUBfmeNarrowRecord0054FEF1@@@Z @0x005504F9 125B.
// Rva0055011A slot-6 method: lock m_14, map[text]=word0, lock m_0C, m_70++, m_44.push_back.
// Evidence: vtable slot 6 of 0x0086AB90; callees rowed 0x00613A70 0x0038E041 0x00613AC0 0x00550384; offsets match landed ctor layout.
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
template <> inline const unsigned int &max<unsigned int>(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <deque>
#include <map>
#include <string>

struct BfmeNarrowRecord0054FEF1
{
	_STL::basic_string<char> text;
	unsigned int word0;
	unsigned int word1;
	BfmeNarrowRecord0054FEF1(const BfmeNarrowRecord0054FEF1 &o);
};

class MutexClass
{
	void *handle;
	unsigned locked;
	bool Lock(int time);
	void Unlock();
public:
	MutexClass(const char *name = 0);
	~MutexClass();
	enum { WAIT_INFINITE = -1 };
	class LockClass
	{
		MutexClass &mutex;
		bool failed;
	public:
		LockClass(MutexClass &m, int time = WAIT_INFINITE);
		~LockClass();
	private:
		LockClass &operator=(const LockClass &) { return *this; }
	};
	friend class LockClass;
};

typedef _STL::deque<BfmeNarrowRecord0054FEF1, _STL::allocator<BfmeNarrowRecord0054FEF1> > NarrowRecord0054FEF1Deque;
typedef _STL::map<_STL::basic_string<char>, unsigned int, _STL::less<_STL::basic_string<char> > > NarrowWordMap;

class Rva0055011A
{
public:
	virtual ~Rva0055011A();
	virtual void rva005504F9(const BfmeNarrowRecord0054FEF1 &rec);
private:
	MutexClass m_04;
	MutexClass m_0C;
	MutexClass m_14;
	char m_1C[0x28];
	NarrowRecord0054FEF1Deque m_44;
	int m_6C;
	int m_70;
	NarrowWordMap m_74;
	char m_pad[0xB4 - 0x74 - 12];
};

void Rva0055011A::rva005504F9(const BfmeNarrowRecord0054FEF1 &rec)
{
	{
		MutexClass::LockClass lock(m_14);
		m_74[rec.text] = rec.word0;
	}
	{
		MutexClass::LockClass lock(m_0C);
		++m_70;
		m_44.push_back(rec);
	}
}
