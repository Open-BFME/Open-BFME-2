// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?Rva00422544Find@@YGHPAVRva00422544List@@@Z, retail 0x00422544, 244 bytes.
// __stdcall: if g_00DC84F5 is set and the global deque<BfmeE12> range is
// non-empty, count the caller's ring, then scan the range for the last elem
// whose key passes (phase 1: key below -1 and above the ring count; phase 2:
// maximal key above 0), returning its +0 link or -1. Evidence: rowed
// _M_increment 0x00421B1E, globals 0x00DC84F5 0x00A031B8 0x00A031A8, caller
// 0x004233F5 (passes its arg through; callee pops, so __stdcall), unlock lane.
// Note: BfmeE12 is the fleet's size stand-in (retail's integer compares prove
// the real +0/+8 are int link/key); iterators stay BfmeE12-typed so the rowed
// _M_increment mangling resolves, and the int fields are read through it.
#include <deque>
struct BfmeE12 { float x, y, z; };
struct Rva00422544Elem { Rva00422544Elem *m_next; int m_unk04; int m_key; };
struct Rva00422544List { Rva00422544Elem *m_head; };
extern unsigned char g_00DC84F5;
// g_00DC84F5: matched references place it at VA 0xdc84f5 (retail .data initial value 1).
unsigned char g_00DC84F5 = 1;
_STL::deque<BfmeE12>::iterator g_00E031A8;
_STL::deque<BfmeE12>::iterator g_00E031B8;

int __stdcall Rva00422544Find(Rva00422544List *list)
{
	if (g_00DC84F5 != 0 && g_00E031B8 != g_00E031A8) {
	Rva00422544Elem *node = (Rva00422544Elem *)-1;
	int count = 0;
	Rva00422544Elem *head = list->m_head;
	Rva00422544Elem *e = head->m_next;
	while (e != head) {
		e = e->m_next;
		count++;
	}
	_STL::deque<BfmeE12>::iterator first = g_00E031A8;
	_STL::deque<BfmeE12>::iterator last = g_00E031B8;
	int idx = -1;
	if (first != last) {
		last = g_00E031B8;
		do {
			unsigned key = *(unsigned *)&first._M_cur->z;
			if (key < (unsigned)idx && key > (unsigned)count) {
				node = *(Rva00422544Elem **)&first._M_cur->x;
				idx = (int)key;
			}
			first._M_increment();
		} while (first != last);
	}
	if ((int)node == -1) {
		first = g_00E031A8;
		idx = 0;
		last = g_00E031B8;
		if (first != last) {
			last = g_00E031B8;
			do {
				unsigned key = *(unsigned *)&first._M_cur->z;
				if (key > (unsigned)idx) {
					node = *(Rva00422544Elem **)&first._M_cur->x;
					idx = (int)key;
				}
				first._M_increment();
			} while (first != last);
		}
	}
	return (int)node;
	}
	return -1;
}
