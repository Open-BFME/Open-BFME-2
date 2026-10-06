// cl: /Ireference/shims/bfme2_ascii /EHsc /MD
// ?Rva0021C811InsertionSort@@YAXPAVRva0021915B@@0HURva0021B753@@@Z @0x0021C811 45B insertion sort via rowed linear insert 0x0021BAA3 and pair-pinned Rva copy.
// Evidence: unlock lane all callees rowed; stride 8 plus insert callers 0x0021C798/0x0021C811 prove Rva0021915B family; same loop as STL __unguarded_insertion_sort with non-trivial value copy; 4-arg shape with unused third proven by caller 0x0021D305 passing 0.
#include "ascii_string.h"
class Rva0021915B {
public:
	Rva0021915B(const Rva0021915B &other);
	Rva0021915B &operator=(const Rva0021915B &other);
	friend struct Rva0021B753;
private:
	AsciiString m_str;
	bool m_byte;
};
struct Rva0021B753 {
	bool operator()(const Rva0021915B &a, const Rva0021915B &b) const;
};
void __cdecl Rva0021BAA3Insert(Rva0021915B *last, Rva0021915B val, Rva0021B753 comp);
void __cdecl Rva0021C811InsertionSort(Rva0021915B *first, Rva0021915B *last, int unused, Rva0021B753 comp)
{
	(void)unused;
	for (Rva0021915B *i = first; i != last; ++i)
		Rva0021BAA3Insert(i, *i, comp);
}
// ?Rva0021D305Forward@@YAXPAVRva0021915B@@0URva0021B753@@@Z @0x0021D305 23B forwarder to rowed 0x0021C811 with 0 for unused.
void __cdecl Rva0021D305Forward(Rva0021915B *first, Rva0021915B *last, Rva0021B753 comp)
{
	Rva0021C811InsertionSort(first, last, 0, comp);
}
