// cl: /MD
// stlport
//
// ?rva0041A3C4@Rva0041A3C4@@QAEXXZ @0x0041A3C4, 51B: deque node-boundary
// advance for 28-byte elements (record dtor at 0x0041A200 proves the element
// carries the two-string record): destroys *cur, frees a null-checked node
// buffer via rowed _free, advances the node pointer and reloads first/last
// (0x70 = 4 elements) and cur. Called from pop_front 0x0041A486.
#include <memory>
#include <string>
void __cdecl free(void *);
#include "BfmeNarrowRecord0041A5D2.h"
struct Rva0041A3C4 {
    BfmeNarrowRecord0041A5D2 *_M_cur;
    BfmeNarrowRecord0041A5D2 *_M_first;
    BfmeNarrowRecord0041A5D2 *_M_last;
    BfmeNarrowRecord0041A5D2 **_M_node;
    void rva0041A3C4();
    void rva0041A486();
};
void Rva0041A3C4::rva0041A3C4()
{
	_M_cur->~BfmeNarrowRecord0041A5D2();
	if (_M_first != 0)
		free(_M_first);
	BfmeNarrowRecord0041A5D2 **node = _M_node + 1;
	_M_node = node;
	_M_first = *node;
	_M_last = _M_first + 4;
	_M_cur = _M_first;
}
void Rva0041A3C4::rva0041A486()
{
	if (_M_cur != _M_last - 1)
	{
		_M_cur->~BfmeNarrowRecord0041A5D2();
		_M_cur += 1;
		return;
	}
	rva0041A3C4();
}
