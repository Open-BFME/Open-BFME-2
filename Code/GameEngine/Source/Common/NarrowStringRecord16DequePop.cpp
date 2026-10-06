// cl: /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
//
// ?rva0041A3F7@Rva0041A3F7@@QAEXXZ @0x0041A3F7, 53B: deque pop_front slow path
// for 16-byte elements (single-string record 0x0041A617: text +0, short,
// flag). Destroys *cur via rowed string dtor 0x0007FAB3, frees a null-checked
// node buffer via rowed _free 0x00030830, advances the node pointer and
// reloads first/last (0x80 = 8 elements) and cur. Called from pop_front
// 0x0041A4A7. Sibling of 28B pop_aux 0x0041A3C4 in NarrowStringRecordDequePop.
#include <memory>
#include <string>
void __cdecl free(void *);
#include "BfmeNarrowRecord0041A617.h"
struct Rva0041A3F7 {
    BfmeNarrowRecord0041A617 *_M_cur;
    BfmeNarrowRecord0041A617 *_M_first;
    BfmeNarrowRecord0041A617 *_M_last;
    BfmeNarrowRecord0041A617 **_M_node;
    void rva0041A3F7();
    void rva0041A4A7();
};
void Rva0041A3F7::rva0041A3F7()
{
	_M_cur->text.~basic_string();
	if (_M_first != 0)
		free(_M_first);
	BfmeNarrowRecord0041A617 **node = _M_node + 1;
	_M_node = node;
	_M_first = *node;
	_M_last = _M_first + 8;
	_M_cur = _M_first;
}
void Rva0041A3F7::rva0041A4A7()
{
	if (_M_cur != _M_last - 1)
	{
		_M_cur->text.~basic_string();
		_M_cur += 1;
		return;
	}
	rva0041A3F7();
}
