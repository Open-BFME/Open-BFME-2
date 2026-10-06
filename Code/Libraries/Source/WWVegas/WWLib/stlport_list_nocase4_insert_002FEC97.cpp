// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?Rva002FEC97Insert@@YGPAXPAXPAUListNode@@PBU?$pair@$$CBVAsciiString@@UNoCaseTreeValue4@@@_STL@@@Z @0x002FEC97 37B: list insert creating node via rowed 0x002FE8AA then linking before position. Evidence: calls 0x002FE8AA; callers at 0x002FED25 and 0x002FED66; same 37B shape as list AsciiString insert 0x001FD72C.
#include <list>
#include "ascii_string.h"

struct NoCaseTreeValue4 { unsigned char m_data[4]; };
struct ListNode {
	ListNode *_M_next;
	ListNode *_M_prev;
	_STL::pair<const AsciiString, NoCaseTreeValue4> _M_val;
};

void *__stdcall Rva002FE8AACreate(const _STL::pair<const AsciiString, NoCaseTreeValue4> *src);

void *__stdcall Rva002FEC97Insert(void *out, ListNode *pos, const _STL::pair<const AsciiString, NoCaseTreeValue4> *src)
{
	ListNode *n = (ListNode *)Rva002FE8AACreate(src);
	ListNode *prev = pos->_M_prev;
	n->_M_next = pos;
	n->_M_prev = prev;
	prev->_M_next = n;
	pos->_M_prev = n;
	*(ListNode **)out = n;
	return out;
}
