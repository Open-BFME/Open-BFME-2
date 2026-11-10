// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva00034B30@Rva00034B30@@QAEPAPAXIIPBIPAPAXH@Z
// Retail 0x00034B30..0x00034C8C (348 bytes) RET14: the general allocator's
// multiple-allocation entry, dlmalloc's independent_comalloc (iALLOc)
// shape. With a caller array, a zero count answers that array; without
// one, a zero count answers a plain zero-size allocation and otherwise the
// pointer array is carved from the tail of the same chunk. The element
// request sizes are rounded as request2size (size + 11, at least 16, 8-byte
// aligned), summed, and one aggregate chunk is allocated through the
// allocator's malloc 0x00033ED0 with the mmap threshold at +0x490 held at
// zero; fast chunks are first consolidated (0x00033930) when bit 0 of +4 is
// set. The chunk is then split into the elements, the last absorbing the
// slop. Chunk heads keep their size in the low 31 bits (0x7FFFFFF8 mask)
// and the in-use bit in bit 0.
// Evidence: retail body, callees and offsets; dlmalloc 2.7 iALLOc is the
// structural lead. The owner is not identified, so names are
// address-derived.

#include "../../../Include/Common/Rva006C1F60.h"

#include "../../../Include/Common/Rva00034C90.h"

static inline unsigned int Rva00034B30RequestSize(unsigned int request)
{
	unsigned int size = request + 11;
	return size > 16 ? size & ~7u : 16;
}

class Rva00034B30
{
public:
	void **rva00034B30(unsigned int count, unsigned int sizeCount, const unsigned int *sizes, void **chunks, int flags);

private:
	void *m_vtbl;
	unsigned char m_flags;			// +0x04
	unsigned char m_pad05[0x490 - 0x05];
	int m_mmapMax;				// +0x490
};

void **Rva00034B30::rva00034B30(unsigned int count, unsigned int sizeCount, const unsigned int *sizes, void **chunks, int flags)
{
	unsigned int arraySize;
	void **marray;
	if (chunks != 0) {
		if (count == 0)
			return chunks;
		marray = chunks;
		arraySize = 0;
	} else {
		if (count == 0)
			return (void **)((Rva006C1F60 *)this)->rva00033ED0(0, flags);
		marray = 0;
		arraySize = Rva00034B30RequestSize(count * sizeof(void *));
	}
	unsigned int contentsSize;
	unsigned int i;
	for (i = 0, contentsSize = 0; i < sizeCount; ++i)
		contentsSize += Rva00034B30RequestSize(sizes[i]);
	unsigned int size = contentsSize + arraySize - 7;
	if (m_flags & 1)
		((Rva00034C90 *)this)->consolidate();
	int mmx = m_mmapMax;
	m_mmapMax = 0;
	void *mem = ((Rva006C1F60 *)this)->rva00033ED0(size, flags);
	m_mmapMax = mmx;
	if (mem != 0) {
		char *p = (char *)mem - 8;
		unsigned int remainder = *(unsigned int *)(p + 4) & 0x7ffffff8;
		if (marray == 0) {
			char *arrayChunk = p + contentsSize;
			marray = (void **)(arrayChunk + 8);
			*(unsigned int *)(arrayChunk + 4) = (remainder - contentsSize) | 1;
			remainder = contentsSize;
		}
		for (unsigned int i = 0; ; ++i) {
			marray[i] = p + 8;
			if (i != count - 1) {
				unsigned int elementSize = Rva00034B30RequestSize(sizes[i]);
				remainder -= elementSize;
				*(unsigned int *)(p + 4) = elementSize | 1;
				p += elementSize;
			} else {
				*(unsigned int *)(p + 4) = remainder | 1;
				break;
			}
		}
	} else
		marray = 0;
	return marray;
}
