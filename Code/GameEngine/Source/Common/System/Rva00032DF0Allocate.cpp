// cl: /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// platformsdk
//
// EA GeneralAllocator (retail 0x00032DF0, 194 bytes): allocate a fresh 4 KB-rounded VirtualAlloc
// mapping for a large request, align the 8-byte header to 8, link the end node into the mapped list.
// Target facts: size rounding 0x101E/0xFFFFF000, flags 0x3000 (or 0x103000 top-down), the 8-byte
// misalignment pad, node constants 0x13 and the list layout come from the retail bytes.
// Closing lever (0x32DF0 nd1, SIB base/index of the pad add): pad is declared at function scope WITH an
// initializer, which gives it the earlier definition and flips the base/index order of the lea.

#include <windows.h>

#include "../../../Include/Common/GeneralAllocator.h"

namespace EA
{
namespace Allocator
{

// A mapped block's end node, linked into the list headed at +0x49C.
struct MappedNode
{
	unsigned int m_base;
	unsigned int m_size;
	MappedNode *m_prev;
	MappedNode *m_next;
};

void *GeneralAllocator::rva00032DF0(unsigned int size)
{
	unsigned int pad = 0;
	unsigned int total = (size + 0x101E) & 0xFFFFF000;
	if (total >= size)
	{
		unsigned long type = 0x3000;
		if (m_498)
			type = 0x103000;
		void *memory = VirtualAlloc(0, total, type, 4);
		if (memory != 0)
		{
			++m_488;
			m_48C += total;
			total -= 0x10;
			unsigned int *header;
			unsigned int misalign = (unsigned int)memory & 7;
			if (misalign != 0)
			{
				pad = 8 - misalign;
				header = (unsigned int *)((char *)memory + pad);
				total -= pad;
				header[0] = pad;
				header[1] = (total - pad) | 2;
			}
			else
			{
				header = (unsigned int *)memory;
				header[0] = 0;
				header[1] = total | 2;
			}
			MappedNode *node = (MappedNode *)((char *)header + total);
			node->m_base = total;
			node->m_size = 0x13;
			MappedNode *head = ((MappedNode *)m_49C)->m_next;
			MappedNode *list = (MappedNode *)m_49C;
			node->m_prev = list;
			node->m_next = head;
			list->m_next = node;
			head->m_prev = node;
			return header + 2;
		}
	}
	return 0;
}

}
}
