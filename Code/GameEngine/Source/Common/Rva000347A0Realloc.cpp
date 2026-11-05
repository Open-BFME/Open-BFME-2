// cl: /O2 /MD /DNDEBUG
//
// The top-extend branch stores the new top into m_440 (+0x440) and reads it back into the
// local it initialises (retail keeps the stored register as the SIB base of the
// foot store); a single exit `return newMem` with newMem function-scope gives the
// dead EBP stores and pop order; computing the remainder pointer before
// set_head_size(newp, nb) in the split branch hoists the shared head load.
// ?realloc@GeneralAllocator@Allocator@EA@@QAEPAXPAXIH@Z
// Retail 0x000347A0..0x00034A60 (704 bytes including the eight-entry case
// table at 0x00034A40) RET0C: the general allocator's reallocation,
// dlmalloc's rEALLOc shape. A null block is a plain allocation (malloc
// engine 0x00033ED0). A chunk that is already big enough, or that grows
// into the top chunk (+0x440) or a free successor, is resized in place and
// any remainder of 16 bytes or more is split off and freed (0x00033150)
// with the field at +0x478 held at zero; otherwise a new block is
// allocated, the old contents copied (memcpy above 32 bytes, else the
// unrolled word copy) and the old block freed. Mmapped chunks (head bit 1)
// are kept when large enough, else copied. Chunk heads keep their size in
// the low 31 bits and flags in bits 0..2 and 31.
// Evidence: retail body and table, the sibling zeroing (0x00034A60) and
// multiple (0x00034B30) allocation entries; names are address-derived.
#include <string.h>
#pragma intrinsic(memcpy)

#include "../../Include/Common/Rva006C1F60.h"

static inline unsigned int Rva000347A0RequestSize(unsigned int request)
{
	unsigned int size = request + 11;
	return size > 16 ? size & ~7u : 16;
}

struct Rva000347A0Chunk
{
	unsigned int prevSize;
	unsigned int head;
	Rva000347A0Chunk *fd;
	Rva000347A0Chunk *bk;
};

// The top chunk is the canonical base's +0x440 node pointer, read through this
// unit's chunk view.
#include "../../Include/Common/GeneralAllocator.h"

void *EA::Allocator::GeneralAllocator::realloc(void *oldMem, unsigned int bytes, int flags)
{
	if (oldMem == 0)
		return ((Rva006C1F60 *)this)->rva00033ED0(bytes, flags);
	unsigned int nb = Rva000347A0RequestSize(bytes);
	Rva000347A0Chunk *oldp = (Rva000347A0Chunk *)((char *)oldMem - 8);
	unsigned int oldSize = oldp->head & 0x7ffffff8;
	Rva000347A0Chunk *newp;
	unsigned int newSize;
	void *newMem;
	if (!(oldp->head & 2)) {
		if (nb <= oldSize) {
			newp = oldp;
			newSize = oldSize;
		} else {
			Rva000347A0Chunk *next = (Rva000347A0Chunk *)((char *)oldp + oldSize);
			if (next == (Rva000347A0Chunk *)m_440 && (newSize = oldSize + (next->head & 0x7ffffff8)) >= nb + 16) {
				oldp->head = (oldp->head & 0x80000007) | nb;
				m_440 = (Rva00031010Node *)((char *)oldp + nb);
				unsigned int topSize = newSize - nb;
				Rva000347A0Chunk *top = (Rva000347A0Chunk *)m_440;
				top->bk = top;
				top->fd = top;
				top->head = topSize | 1;
				*(unsigned int *)((char *)top + topSize) = topSize;
				return oldMem;
			} else if (next != (Rva000347A0Chunk *)m_440 && !(((Rva000347A0Chunk *)((char *)next + (next->head & 0x7ffffff8)))->head & 1) && (newSize = oldSize + (next->head & 0x7ffffff8)) >= nb) {
				newp = oldp;
				next->fd->bk = next->bk;
				next->bk->fd = next->fd;
			} else {
				void *mem = ((Rva006C1F60 *)this)->rva00033ED0(nb - 7, flags);
				if (mem != 0) {
					newp = (Rva000347A0Chunk *)((char *)mem - 8);
					if (newp == next) {
						newSize = (newp->head & 0x7ffffff8) + oldSize;
						newp = oldp;
					} else {
						unsigned int copySize = oldSize - 4;
						if (copySize > 0x20) {
							memcpy(mem, oldMem, copySize);
						} else {
							unsigned int *dest = (unsigned int *)mem;
							unsigned int *src = (unsigned int *)oldMem;
							switch ((copySize >> 2) - 1) {
							case 7: *dest++ = *src++;
							case 6: *dest++ = *src++;
							case 5: *dest++ = *src++;
							case 4: *dest++ = *src++;
							case 3: *dest++ = *src++;
							case 2: *dest++ = *src++;
							case 1: *dest++ = *src++;
							case 0: *dest = *src;
							}
						}
						rva00033150(oldMem);
						return (char *)newp + 8;
					}
				} else
					return 0;
			}
		}
		unsigned int remainderSize = newSize - nb;
		if (remainderSize < 16) {
			newp->head = (newp->head & 0x80000007) | newSize;
			((Rva000347A0Chunk *)((char *)newp + newSize))->head |= 1;
		} else {
			Rva000347A0Chunk *remainder = (Rva000347A0Chunk *)((char *)newp + nb);
			newp->head = (newp->head & 0x80000007) | nb;
			remainder->head = remainderSize | 1;
			Rva000347A0Chunk *after = (Rva000347A0Chunk *)((char *)remainder + remainderSize);
			after->prevSize = remainderSize;
			after->head |= 1;
			int saved = m_478;
			m_478 = 0;
			rva00033150((char *)remainder + 8);
			m_478 = saved;
		}
		newMem = (char *)newp + 8;
	} else if (nb + 4 <= oldSize) {
		newMem = oldMem;
	} else {
		newMem = ((Rva006C1F60 *)this)->rva00033ED0(nb - 7, flags);
		if (newMem != 0) {
			memcpy(newMem, oldMem, oldSize - 8);
			rva00033150(oldMem);
		}
	}
	return newMem;
}
