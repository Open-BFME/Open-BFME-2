// cl: /O2 /MD /DNDEBUG
// Address-derived allocation engine 33ED0 (1478 B) and calloc 34A60 (204 B).
// Retail gives the complete boundaries, offsets, links, calls and lock accesses.
// The dlmalloc 2.7 mALLOc structure supplied by the prior bank is a structural
// guide; chunk/bin labels and original EA method identities remain inferred.
// Target-specific differences and independent compiler controls are documented
// in reverse/attempt_support/allocator-malloc-33ed0-20261020.md.
// The +18 volatile lock counter follows MemoryPoolInit.cpp and memory_pool.cpp.
// It preserves the observed load/update/store operations around Enter/Leave.
#include <string.h>

#include <windows.h>

struct Rva00030DD0Lock
{
    unsigned char m_cs[0x18];
    volatile int m_ref;
};

struct malloc_chunk
{
    unsigned int prev_size;
    unsigned int size;
    malloc_chunk *bk;
    malloc_chunk *fd;
};
typedef malloc_chunk *mchunkptr;
typedef malloc_chunk *mbinptr;
typedef malloc_chunk *mfastbinptr;

class Rva00034C90
{
public:
    void consolidate();
};

#include "../../Include/Common/GeneralAllocator.h"

typedef bool (*GrowCallback)(void *, unsigned int, unsigned int, unsigned int);

#define SIZE_BITS 0x80000007u
#define chunksize(p) ((p)->size & ~(SIZE_BITS))
#define chunk2mem(p) ((void *)((char *)(p) + 8))
#define chunk_at_offset(p, s) ((mchunkptr)(((char *)(p)) + (s)))
#define set_inuse_bit_at_offset(p, s) (((mchunkptr)(((char *)(p)) + (s)))->size |= 1)
#define set_head(p, s) ((p)->size = (s))
#define set_foot(p, s) (((mchunkptr)((char *)(p) + (s)))->prev_size = (s))
#define MINSIZE 16
#define in_smallbin_range(sz) ((unsigned long)(sz) < 0x200)
#define smallbin_index(sz) (((unsigned)(sz)) >> 3)
#define largebin_index(sz) \
(((((unsigned long)(sz)) >>  6) <= 32)?  56 + (((unsigned long)(sz)) >>  6): \
 ((((unsigned long)(sz)) >>  9) <= 20)?  91 + (((unsigned long)(sz)) >>  9): \
 ((((unsigned long)(sz)) >> 12) <= 10)? 110 + (((unsigned long)(sz)) >> 12): \
 ((((unsigned long)(sz)) >> 15) <=  4)? 119 + (((unsigned long)(sz)) >> 15): \
 ((((unsigned long)(sz)) >> 18) <=  2)? 124 + (((unsigned long)(sz)) >> 18): \
                                        126)
#define bin_at(m, i) ((mbinptr)((char *)&((m)->m_030[(i) << 1]) - 8))
#define next_bin(b) ((mbinptr)((char *)(b) + 8))
#define last(b) ((b)->bk)
#define unsorted_chunks(M) (bin_at(M, 1))
#define idx2block(i) ((i) >> 5)
#define idx2bit(i) ((1U << ((i) & 31)))
#define mark_bin(m, i) ((m)->m_430[idx2block(i)] |= idx2bit(i))
#define fastbin_index(sz) ((((unsigned int)(sz)) >> 3) - 2)
#define have_fastchunks(M) (((M)->m_004 & 1))
#define unlink(P, BK, FD) { P->bk->fd = P->fd; P->fd->bk = P->bk; }
#define request2size(req) \
    (((req) + 4 + 7 <= MINSIZE) ? MINSIZE : ((req) + 4 + 7) & ~7u)

// The dlmalloc state lives in the canonical base: max_fast m_004, fastbins
// m_008, bins m_030, binmap m_430, top m_440, last_remainder m_444, the
// mmap-enable byte m_46D, n_mmaps m_488, n_mmaps_max m_490, mmap_threshold
// m_494, the grow callback m_4AC with its argument m_4B0 and retry limit m_4B4,
// and the lock m_pLock.
class Rva006C1F60 : public EA::Allocator::GeneralAllocator
{
public:
    void *rva00033ED0(unsigned int bytes, int flags);

};

void *Rva006C1F60::rva00033ED0(unsigned int bytes, int flags)
{
    unsigned int attempts = 0;
    void *result = 0;

    unsigned int nb;
    int idx;
    mbinptr bin;
    mchunkptr victim;
    unsigned int size;
    int victim_index;
    mchunkptr remainder;
    unsigned int remainder_size;
    unsigned int block;
    unsigned int bit;
    unsigned int map;
    mchunkptr fwd;
    mchunkptr bck;
    mbinptr unsorted;

    if (flags & 8)
        return ((EA::Allocator::GeneralAllocator *)this)->rva00032DF0(bytes);

    for (;;)
    {
        nb = bytes + 4 + 7;
        if (nb > MINSIZE)
            nb &= ~7u;
        else
            nb = MINSIZE;

        if (nb <= m_004)
        {
            mfastbinptr *fb = (mfastbinptr *)&m_008[fastbin_index(nb)];
            if ((victim = *fb) != 0)
            {
                victim->size &= 0x7ffffffb;
                *fb = victim->fd;
                return chunk2mem(victim);
            }
        }

        if (in_smallbin_range(nb))
        {
            idx = smallbin_index(nb);
            bin = bin_at(this, idx);
            if ((victim = last(bin)) != bin)
            {
                set_inuse_bit_at_offset(victim, nb);
                unlink(victim, bck, fwd);
                return chunk2mem(victim);
            }
        }
        else
        {
            idx = largebin_index(nb);
            if (have_fastchunks(this))
                ((Rva00034C90 *)this)->consolidate();
        }

        unsorted = unsorted_chunks(this);
        for (;;)
        {
            while ((victim = unsorted->bk) != unsorted)
            {
                bck = victim->bk;
                size = chunksize(victim);

                if (in_smallbin_range(nb) &&
                    victim == (mchunkptr)m_444 &&
                    bck == unsorted &&
                    size > nb + MINSIZE)
                {
                    remainder_size = size - nb;
                    remainder = chunk_at_offset(victim, nb);
                    unsorted->bk = unsorted->fd = remainder;
                    m_444 = (Rva00031010Node *)remainder;
                    remainder->bk = remainder->fd = unsorted;
                    set_head(victim, nb | 1);
                    set_head(remainder, remainder_size | 1);
                    set_foot(remainder, remainder_size);
                    return chunk2mem(victim);
                }

                unsorted->bk = bck;
                bck->fd = unsorted;

                if (size == nb)
                {
                    set_inuse_bit_at_offset(victim, size);
                    return chunk2mem(victim);
                }

                if (in_smallbin_range(size))
                {
                    victim_index = smallbin_index(size);
                    bck = bin_at(this, victim_index);
                    fwd = bck->fd;
                }
                else
                {
                    victim_index = largebin_index(size);
                    bck = bin_at(this, victim_index);
                    fwd = bck->fd;

                    if (bck != fwd)
                    {
                        if (size < bck->bk->size)
                        {
                            fwd = bck;
                            bck = bck->bk;
                        }
                        else
                        {
                            while (size < chunksize(fwd))
                                fwd = fwd->fd;
                            bck = fwd->bk;
                        }
                    }
                }

                block = victim_index >> 5;
                m_430[block] |= idx2bit(victim_index);
                victim->bk = bck;
                victim->fd = fwd;
                fwd->bk = victim;
                bck->fd = victim;
            }

            if (!in_smallbin_range(nb))
            {
                bin = bin_at(this, idx);
                for (victim = last(bin); victim != bin; victim = victim->bk)
                {
                    size = chunksize(victim);
                    if (size >= nb)
                    {
                        remainder_size = size - nb;
                        unlink(victim, bck, fwd);
                        if (remainder_size < MINSIZE)
                        {
                            set_inuse_bit_at_offset(victim, size);
                            return chunk2mem(victim);
                        }
                        remainder = chunk_at_offset(victim, nb);
                        unsorted->bk = unsorted->fd = remainder;
                        remainder->bk = remainder->fd = unsorted;
                        set_head(victim, nb | 1);
                        set_head(remainder, remainder_size | 1);
                        set_foot(remainder, remainder_size);
                        return chunk2mem(victim);
                    }
                }
            }

            ++idx;
            bin = bin_at(this, idx);
            block = idx2block(idx);
            map = m_430[block];
            bit = idx2bit(idx);

            for (;;)
            {
                if (bit > map || bit == 0)
                {
                    do
                    {
                        if (++block >= 4)
                            goto use_top;
                    } while ((map = m_430[block]) == 0);
                    bin = bin_at(this, (block << 5));
                    bit = 1;
                }

                while ((bit & map) == 0)
                {
                    bin = next_bin(bin);
                    bit <<= 1;
                }

                victim = last(bin);
                if (victim == bin)
                {
                    m_430[block] = map &= ~bit;
                    bin = next_bin(bin);
                    bit <<= 1;
                }
                else
                {
                    size = chunksize(victim);
                    unlink(victim, bck, fwd);
                    remainder_size = size - nb;
                    if (remainder_size < MINSIZE)
                    {
                        set_inuse_bit_at_offset(victim, size);
                        return chunk2mem(victim);
                    }
                    remainder = chunk_at_offset(victim, nb);
                    unsorted->bk = unsorted->fd = remainder;
                    remainder->bk = remainder->fd = unsorted;
                    if (in_smallbin_range(nb))
                        m_444 = (Rva00031010Node *)remainder;
                    set_head(victim, nb | 1);
                    set_head(remainder, remainder_size | 1);
                    set_foot(remainder, remainder_size);
                    return chunk2mem(victim);
                }
            }

        use_top:
            victim = (mchunkptr)m_440;
            size = chunksize(victim);
            if (size >= nb + MINSIZE)
            {
                remainder_size = size - nb;
                set_head(victim, nb | 1);
                remainder = chunk_at_offset(victim, nb);
                set_head(remainder, remainder_size | 1);
                m_440 = (Rva00031010Node *)remainder;
                mchunkptr topChunk = (mchunkptr)m_440;
                set_head(topChunk, remainder_size | 1);
                topChunk->bk = topChunk->fd = topChunk;
                set_foot(topChunk, remainder_size);
                return chunk2mem(victim);
            }
            if (!have_fastchunks(this))
                break;
            ((Rva00034C90 *)this)->consolidate();
            idx = smallbin_index(nb);
        }

        if (m_46D && nb >= m_494 && (int)m_488 < (int)m_490)
        {
            result = ((EA::Allocator::GeneralAllocator *)this)->rva00032DF0(bytes);
            if (result)
                return result;
        }
        if (m_46D)
        {
            mchunkptr allocatedChunk = (mchunkptr)((EA::Allocator::GeneralAllocator *)this)->rva000334A0(nb);
            if (allocatedChunk)
            {
                set_inuse_bit_at_offset(allocatedChunk, chunksize(allocatedChunk));
                result = chunk2mem(allocatedChunk);
            }
        }
        if (result || !m_4AC || ++attempts >= m_4B4)
            break;

        int refs = m_pLock->m_ref;
        for (int i = 0; i < refs; ++i)
        {
            Rva00030DD0Lock *lock = m_pLock;
            --lock->m_ref;
            LeaveCriticalSection((CRITICAL_SECTION *)lock);
        }
        bool ok = ((GrowCallback)m_4AC)(this, bytes, bytes + 0x40, m_4B0);
        for (int j = 0; j < refs; ++j)
        {
            Rva00030DD0Lock *lock = m_pLock;
            EnterCriticalSection((CRITICAL_SECTION *)lock);
            ++lock->m_ref;
        }
        if (!ok)
            break;
    }
    return result;
}

struct Rva00034A60Chunk
{
	unsigned int priorSize;
	unsigned int size;
};


void *EA::Allocator::GeneralAllocator::calloc(unsigned int count, unsigned int size, int flags)
{
	void *block = ((Rva006C1F60 *)this)->rva00033ED0(count * size, flags);
	if (block != 0)
	{
		const Rva00034A60Chunk *chunk = (const Rva00034A60Chunk *)((char *)block - 8);
		unsigned int chunkSize = chunk->size & 0x7FFFFFF8u;
		if (!(chunk->size & 2))
		{
			if (chunkSize - 4 > 0x20)
				memset(block, 0, chunkSize - 4);
			else
			{
				unsigned int *clearPtr = (unsigned int *)block;
				switch (((chunkSize - 4) >> 2) - 1)
				{
				case 7: *clearPtr++ = 0;
				case 6: *clearPtr++ = 0;
				case 5: *clearPtr++ = 0;
				case 4: *clearPtr++ = 0;
				case 3: *clearPtr++ = 0;
				case 2: *clearPtr++ = 0;
				case 1: *clearPtr++ = 0;
				case 0: *clearPtr = 0;
				}
			}
		}
	}
	return block;
}
