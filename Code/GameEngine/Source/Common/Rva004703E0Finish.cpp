// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
//
// ??1Rva004703E0@@QAE@XZ @ 0x004703E0 78B non-virtual dtor.
//
// Layout: +0 int, +4 StringBase<char> (AsciiString), +8 an STLport vector whose
// destruction is modelled by the inline holder below: erase(begin, end) then a
// guarded free of begin, then the AsciiString releaseBuffer. The target keeps
// this first member destruction at EH state 0 and flips to state -1 only before
// the AsciiString releaseBuffer, which is exactly the compiler-generated member
// destruction sequence for an empty destructor body (matched sibling 0x0053FB33
// uses the same holder idiom). Evidence: callees rowed vector erase 0x002BF70F,
// free 0x00030830 and StringBase releaseBuffer 0x00036410; callers 0x004704AC
// and 0x00475942; EH prolog helper 0x00629188.
extern "C" void __cdecl free(void *block);

struct BfmePod16
{
	int a[4];
};

namespace _STL
{
template <typename T>
class allocator {};

template <typename T, typename A>
class vector
{
public:
	typedef T *iterator;
	iterator erase(iterator first, iterator last);
	iterator begin() { return m_start; }
	iterator end() { return m_finish; }
	T *m_start;
	T *m_finish;
	T *m_end_of_storage;
};

template <>
vector<BfmePod16, allocator<BfmePod16> >::iterator
vector<BfmePod16, allocator<BfmePod16> >::erase(
	vector<BfmePod16, allocator<BfmePod16> >::iterator first,
	vector<BfmePod16, allocator<BfmePod16> >::iterator last);
}

typedef _STL::vector<BfmePod16, _STL::allocator<BfmePod16> > BfmePod16Vector;

struct Rva004703E0VecHolder
{
	void *m_begin;
	void *m_end;
	void *m_cap;

	__forceinline ~Rva004703E0VecHolder()
	{
		BfmePod16Vector &v = *(BfmePod16Vector *)this;
		v.erase(v.begin(), v.end());
		if (m_begin != 0)
			free(m_begin);
	}
};

template <typename T>
class StringBase
{
public:
	~StringBase() { releaseBuffer(); }
private:
	void releaseBuffer();
	T *m_data;
};

// Narrow teardown routed onto the verified releaseBuffer worker at 0x00036410.
template <> StringBase<char>::~StringBase();
#pragma comment(linker, "/alternatename:??1?$StringBase@D@@QAE@XZ=?releaseBuffer@?$StringBase@D@@AAEXXZ")

class Rva004703E0
{
public:
	~Rva004703E0();

private:
	int m_unk0;
	StringBase<char> m_str;
	Rva004703E0VecHolder m_vec;
};

Rva004703E0::~Rva004703E0()
{
}
