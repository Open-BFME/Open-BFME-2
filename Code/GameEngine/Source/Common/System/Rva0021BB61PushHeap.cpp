// cl: /Ireference/shims/bfme2_ascii /EHsc /MD
// ?Rva0021BB61PushHeap@@YAXPAVRva0021915B@@HHV1@URva0021B753@@@Z @0x0021BB61 123B
// __push_heap for 8-byte AsciiString-plus-bool entries with empty comparator
// Rva0021B753 (rowed 0x0021B753). Bubbles val up while parent < val.
// Callees rowed: assign 0x0021915B, comparator 0x0021B753, releaseBuffer
// 0x00036410, EH_prolog. Caller 0x0021C8D7 (adjust-heap path, add esp 0x18).
// Evidence: parent (hole-1)/2 via lea/cdq/sub/sar; same loop as STL push_heap
// with 8B stride (esi*8); true-first bool plus nocase secondary ordering.

#include "ascii_string.h"


class Rva0021915B
{
public:
	Rva0021915B &operator=(const Rva0021915B &other);
	friend struct Rva0021B753;

private:
	AsciiString m_str;
	bool m_byte;
};

struct Rva0021B753
{
	bool operator()(const Rva0021915B &a, const Rva0021915B &b) const;
};

void __cdecl Rva0021BB61PushHeap(Rva0021915B *first, int holeIndex, int topIndex, Rva0021915B val, Rva0021B753 comp);

void __cdecl Rva0021BB61PushHeap(Rva0021915B *first, int holeIndex, int topIndex, Rva0021915B val, Rva0021B753 comp)
{
	int parent = (holeIndex - 1) / 2;
	while (holeIndex > topIndex && comp(*(first + parent), val)) {
		*(first + holeIndex) = *(first + parent);
		holeIndex = parent;
		parent = (holeIndex - 1) / 2;
	}
	*(first + holeIndex) = val;
}
