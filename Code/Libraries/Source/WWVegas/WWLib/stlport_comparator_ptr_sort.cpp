// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// Two STLport pointer sorts whose comparator objects carry state (two ints)
// and compare through an out-of-line member: MapMetaData pointers ordered by
// Rva0043FE9A (sort 0x004434EF, introsort loop 0x0044346B) and pointers
// ordered by Rva005B61B3 (sort 0x005B670C, loop 0x005B6688). Most of each
// family is rowed by hand (Rva00440AB0Median.cpp, Rva005B6409Heap.cpp and
// their siblings), and this instantiation reproduces those bodies. It adds sort,
// the loop, partial_sort, __partial_sort and make_heap.
//
// The comparator's operator() is retail's out-of-line member, which keeps its
// rowed name; each comparator here derives from that class and forwards to it
// inline. The forwarder takes the values by const reference: retail pushes
// them straight from memory, which a by-value forwarder turns into a register
// load and push.
//
// The linear inserts call __copy_trivial_backward. Retail's copy of it
// (0x00620840) is the speed-built body, so that header is compiled with the
// speed option and the imported memmove.

#pragma optimize("t", on)
#include <stl/_algobase.h>
#pragma optimize("", on)
#include <algorithm>

class MapMetaData;

class Rva0043FE9A
{
public:
	bool rva0043FE9A(MapMetaData *a, MapMetaData *b);
private:
	int m_sort0;
	int m_sort1;
};

struct Rva0043FE9ALess : public Rva0043FE9A
{
	bool operator()(MapMetaData *const &a, MapMetaData *const &b) { return rva0043FE9A(a, b); }
};

class Rva005B61B3
{
public:
	bool rva005B61B3(void *a, void *b);
private:
	int m_key0;
	int m_key1;
};

struct Rva005B61B3Less : public Rva005B61B3
{
	bool operator()(void *const &a, void *const &b) { return rva005B61B3(a, b); }
};

template void _STL::sort<MapMetaData **, Rva0043FE9ALess>(MapMetaData **, MapMetaData **, Rva0043FE9ALess);
template void _STL::sort<void **, Rva005B61B3Less>(void **, void **, Rva005B61B3Less);
