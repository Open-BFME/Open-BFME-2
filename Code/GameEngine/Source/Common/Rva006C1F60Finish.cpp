// cl: /MD
// platformsdk
// ?rva006C1F60@Rva006C1F60@@QAEHI@Z @ 0x006C1F60 113B chain of 0x00030DF0
// Release. AddRef at +0x4e4 Release guarded float clamp via __ftol2 returning
// clamped int. Evidence: calls AddRef 0x00030DD0 Release 0x00030DF0 __ftol2
// rowed; flag bit 0x800 at +0x514 scale float at +0x534 min at +0x538 max at
// +0x53c; caller at 0x006C2463. Honest address-derived method of Rva006C1F60.
struct Rva00030DD0Lock;
int Rva00030DD0AddRef(Rva00030DD0Lock *lock);
int Rva00030DF0Release(Rva00030DD0Lock *lock);
extern "C" int __cdecl __ftol2(float f);
#include "../../Include/Common/Rva006C1F60.h"
int Rva006C1F60::rva006C1F60(unsigned int v)
{
	Rva00030DD0Lock *lock = m_pLock;
	if (lock != 0)
		Rva00030DD0AddRef(lock);
	unsigned int result = 0;
	if ((m_514 & 0x800) != 0) {
		float f = (float)v * m_534;
		result = (unsigned int)(int)f;
		if (result < m_538)
			result = m_538;
		if (result > m_53C)
			result = m_53C;
	}
	if (lock != 0)
		Rva00030DF0Release(lock);
	return (int)result;
}

//
// ?rva006C2AA0@GeneralAllocatorDebug@@QAEXEEEEE@Z, retail 0x006C2AA0 (638 bytes). The
// retail body runs to its `ret 0x14` at 0x006C2D1B, 638 bytes (the Ghidra
// boundary stops three bytes short at 635). Takes five fill bytes for the
// allocator's fill slots +0x508..+0x50C (the debug constructor 0x006C4A50
// sets them to DD DE CD AB FE) and refills existing memory where a value
// changes, under the +0x4E4 lock (rowed AddRef 0x00030DD0 / Release
// 0x00030DF0; the unwind state releases it). Target evidence:
//  - +0x50A and +0x50C are stored directly;
//  - a new +0x508 value is written over every free chunk of every core block
//    (core list sentinel +0x448; next +0x1C; first chunk +0; size +4)
//    after its 16-byte header;
//  - a new +0x509 value (1 also clears +0x540) is written over each block of
//    the delayed-free list (sentinel +0x548; next +0x0C) past its two link
//    words, sized inline from the debug trailer or else through the rowed
//    GetBlockSize 0x00032A20;
//  - a new +0x50B value (1 also clears flag 0x800 of +0x514) is written over
//    each allocated block's guard run: the pinned block walk 0x000353B0 /
//    0x00032F60 / 0x00033E90 and the pinned guard-run builder 0x006C25F0
//    (kind 0xB) as in the rowed VerifyGuardFill 0x006C3020.
// The fills are the intrinsic memset. Method name address-derived.

#include <string.h>
#include <windows.h>
#pragma intrinsic(memset)
#pragma intrinsic(memcpy)

struct Rva00030DD0Lock;
int Rva00030DD0AddRef(Rva00030DD0Lock *lock);
int Rva00030DF0Release(Rva00030DD0Lock *lock);

#include "../../Include/Common/GeneralAllocator.h"

namespace EA { namespace Allocator {
struct BlockInfo
{
	void *mpCore; // +0x00
};
}}

struct GeneralAllocatorChunk
{
	unsigned int m_prevSize; // +0x00
	unsigned int m_size; // +0x04
	GeneralAllocatorChunk *m_prev; // +0x08
	GeneralAllocatorChunk *m_next; // +0x0C
};

struct GeneralAllocatorCore
{
	char *m_first; // +0x00
	unsigned int m_size; // +0x04
	unsigned char m_pad08[0x1C - 0x08];
	GeneralAllocatorCore *m_next; // +0x1C
};

class GeneralAllocatorDebugLockGuard
{
public:
	GeneralAllocatorDebugLockGuard(Rva00030DD0Lock *lock) : m_lock(lock)
	{
		if (m_lock != 0)
			Rva00030DD0AddRef(m_lock);
	}
	~GeneralAllocatorDebugLockGuard()
	{
		if (m_lock != 0)
			Rva00030DF0Release(m_lock);
	}
private:
	Rva00030DD0Lock *m_lock;
};

class Rva006C1850 { public: bool rva006C1850(unsigned int, void **); };
class Rva006C17B0 { public: void rva006C17B0(bool, bool); };
class Rva006C1D60 { public: bool rva006C1D60(unsigned int, bool); };
class Rva006C39F0Owner { public: bool rva006C39F0(unsigned int, unsigned int, unsigned int, void *); };
struct Rva006C2270Slot { unsigned int total, length, mode; };
struct Rva006C2270Record
{
	unsigned int initial;
	Rva006C2270Slot slots[14];
	unsigned int inlineTotal, externalTotal, requestedSize, arg2, arg3, arg4, word520, word524;
	void *stack[24];
};

struct GeneralAllocatorMetricCounters
{
	unsigned __int64 currentCount, totalAllocCount, peakCount;
	unsigned __int64 currentBytes, totalAllocBytes, peakBytes;
	unsigned __int64 totalFreeCount, totalFreeBytes;
};

// Canonical base fields used here: m_448 the core list sentinel (+0x448),
// m_pLock the lock, m_508[0..4] the free, delayed-free, new, guard and
// unused-core fill bytes.
class GeneralAllocatorDebug : public EA::Allocator::GeneralAllocator
{
public:
	void rva006C26F0(void *chunk, bool allocation);
	void rva006C1B60(int option, unsigned int value);
	unsigned int rva006C1FE0(char *base, int length, char **bodyOut);
	unsigned int rva006C2510(char *block, int mode, char **outBody);
	void *rva006C2010Run6(void *block, unsigned int size, unsigned short kind, void *dst, unsigned int capacity, unsigned int *outLen);
	void rva006C2AA0(unsigned char fillFree, unsigned char fillDelayedFree,
		unsigned char fillNew, unsigned char fillGuard, unsigned char fillUnusedCore);
	void *rva006C25F0Run6(void *runBlock, int kind, int zero3, int zero2,
		unsigned int *outLen, int zero1);
	void rva006C2270(Rva006C2270Record *record, unsigned int size, unsigned int flags,
		unsigned int a3, unsigned int a4);
	bool rva006C3D30(Rva006C2270Record *record, void *block, bool fill);
	void *rva006C4730(void *data, unsigned int size, int flags);
private:
	void bookBlock(void *chunk, int allocation)
	{
		rva006C26F0(chunk, allocation);
	}
	void *mallocBackup(unsigned int size)
	{
		void *p = ((Rva006C1F60 *)this)->rva00033ED0(size, 0x80000000);
		if (p) {
			unsigned int h = ((unsigned int *)p)[-1];
// Keep capacity in h and materialize the footer for the intrinsic.
			// Separate capacity/pointer PHIs change VC7.1's allocation costs.
			if (!(h & 2)) {
			    h &= 0x7FFFFFF8;
			    h += 4;
			} else
			    h &= 0x7FFFFFF8;
			char *t = (char *)p + h - 10;
			memset(t, 0, 2);
		}
		return p;
	}

	unsigned int getDebugDataSize(char *data)
	{
		unsigned int sizeField = ((GeneralAllocatorChunk *)(data - 8))->m_size;
		if (!(sizeField & 0x80000000))
		{
			unsigned int chunkSize;
			if (!(sizeField & 2))
				chunkSize = (sizeField & 0x7FFFFFF8) + 4;
			else
				chunkSize = sizeField & 0x7FFFFFF8;
			char *trailer = data + chunkSize - 10;
			char *end = trailer - *(unsigned short *)trailer;
			if (end >= data)
				return end - data;
		}
		return rva00032A20(data);
	}

	unsigned char m_pad510[0x514 - 0x510];
	unsigned int m_flags; // +0x514
	unsigned char m_pad518[0x540 - 0x518];
	unsigned int m_delayedFreeTotal; // +0x540
	unsigned int m_544;
	GeneralAllocatorChunk m_delayedFree; // +0x548
	unsigned char m_pad558[0x560 - 0x558];
	bool m_metricsEnabled; // +0x560
	unsigned char m_pad561[0x568 - 0x561];
	unsigned __int64 m_allocRequests; // +0x568
	GeneralAllocatorMetricCounters m_metrics[4]; // +0x570..0x66F
	unsigned int m_lastAllocation; // +0x670
	unsigned int m_lastFree; // +0x674
	unsigned char m_pad678[0x67C - 0x678];
	int m_tableGate; // +0x67C
	bool m_tableEnabled; // +0x680
	unsigned char m_pad681[0x684 - 0x681];
	Rva006C17B0 m_table; // +0x684
};

void GeneralAllocatorDebug::rva006C2AA0(unsigned char fillFree, unsigned char fillDelayedFree,
	unsigned char fillNew, unsigned char fillGuard, unsigned char fillUnusedCore)
{
	GeneralAllocatorDebugLockGuard guard(m_pLock);

	m_508[2] = fillNew;
	m_508[4] = fillUnusedCore;

	if (m_508[0] != fillFree)
	{
		m_508[0] = fillFree;
		for (GeneralAllocatorCore *core = ((GeneralAllocatorCore *)m_448)->m_next; core != (GeneralAllocatorCore *)m_448; core = core->m_next)
		{
			char *end = (char *)core + core->m_size - 0x10;
			for (char *chunk = core->m_first; chunk < end;
				chunk += ((GeneralAllocatorChunk *)chunk)->m_size & 0x7FFFFFF8)
			{
				unsigned int size = ((GeneralAllocatorChunk *)chunk)->m_size & 0x7FFFFFF8;
				if (!(((GeneralAllocatorChunk *)(chunk + size))->m_size & 1))
					memset(chunk + 0x10, m_508[0], size - 0x10);
			}
		}
	}

	if (m_508[1] != fillDelayedFree)
	{
		m_508[1] = fillDelayedFree;
		if (fillDelayedFree == 1)
			m_delayedFreeTotal = 0;
		for (GeneralAllocatorChunk *chunk = m_delayedFree.m_next; chunk != &m_delayedFree; chunk = chunk->m_next)
		{
			char *data = (char *)chunk + 8;
			unsigned int size = getDebugDataSize(data);
			memset(data + 8, m_508[1], size - 8);
		}
	}

	if (m_508[3] != fillGuard)
	{
		m_508[3] = fillGuard;
		if (fillGuard == 1)
			m_flags &= ~0x800;
		void *walk = rva000353B0(0, 2, false, 0, 0);
		for (const EA::Allocator::BlockInfo *info = rva00032F60(walk, 2); info; info = rva00032F60(walk, 2))
		{
			GeneralAllocatorChunk *chunk = (GeneralAllocatorChunk *)info->mpCore;
			char *data = (char *)chunk + 8;
			unsigned int len;
			char *run = (char *)rva006C25F0Run6(data, 0xB, 0, 0, &len, 0);
			if (run)
			{
				char *end = run + len;
				if (run < data + 8)
					run = data + 8;
				memset(run, m_508[3], end - run);
			}
		}
		rva00033E90(walk);
	}
}

// Native 0x006C2010..0x006C209F (143B): six stack arguments, RET18,
// backward ushort tag/length traversal bounded by the trailer extent; optional
// copy and length output. Address-derived identity, no donor semantic name.
void *GeneralAllocatorDebug::rva006C2010Run6(void *block, unsigned int size, unsigned short kind, void *dst, unsigned int capacity, unsigned int *outLen)
{
 char *end=(char *)block+size-2;
 char *begin=end-*(unsigned short *)end;
 if (begin >= (char *)block) {
  while (end > begin) {
   end-=2; unsigned short len=*(unsigned short *)end;
   end-=2; unsigned short tag=*(unsigned short *)end;
   end-=len;
   if (tag==kind) {
    if (dst) {
     unsigned int n=capacity;
     if (n>=len) n=len;
     memcpy(dst,end,n);
    }
    if (outLen) *outLen=len;
    return end;
   }
  }
 }
 if (outLen) *outLen=0;
 return 0;
}

// Native 0x006C25F0..0x006C26E6 (246B): locked six-argument guard-run
// provider for fill updates. Retail proves the mode gate at +67C, lookup bool
// at +680 and hash view at +684; the existing validator and hash names remain
// their owned address-derived linkage identities.
void *GeneralAllocatorDebug::rva006C25F0Run6(void *block,int kind,int a3,int a4,unsigned int *outLen,int mode)
{
 Rva00030DD0Lock *lock=m_pLock;
 if(lock)Rva00030DD0AddRef(lock);
 void *result=0;
 if((unsigned char)((Rva006C1F60*)this)->rva006C1DC0((unsigned int)block)) {
  int gate=mode;
  if(mode==2) {
   if((unsigned short)kind==0xB) goto edit;
   gate=*(int *)((char *)this+0x67C);
  }
  if(!gate) {
edit:
   unsigned int h=*((unsigned int*)block-1);
   unsigned int size;
   if(!(h&2))size=(h&0x7FFFFFF8)+4;
   else size=h&0x7FFFFFF8;
   result=rva006C2010Run6(block,size-8,(unsigned short)kind,(void*)a3,a4,outLen);
  } else if(*(bool *)((char *)this+0x680)) {
   void *out=0;
   if(((Rva006C1850*)((char*)this+0x684))->rva006C1850((unsigned int)block,&out)&&out) {
    char *bytes=*(char**)out;
    unsigned short len=*(unsigned short*)bytes;
    if(len)result=rva006C2010Run6(bytes+2,len-2,(unsigned short)kind,(void*)a3,a4,outLen);
   }
  }
 }
 if(lock)Rva00030DF0Release(lock);
 return result;
}

// 0x006C1DC0..0x006C1E14: native full-EAX 0/1 result, RET4,
// conditional hash membership with target offsets 530/680/684/68C.
// Callers explicitly preserve its low-byte result as native does.
struct Rva006C1DC0Node { unsigned int key; void *value; Rva006C1DC0Node *next; };
int Rva006C1F60::rva006C1DC0(unsigned int block) {
 if(!m_680||m_530)goto success;
 {Rva006C1DC0Node **buckets=*(Rva006C1DC0Node ***)((char *)this+0x684);
 if(buckets){Rva006C1DC0Node *node=buckets[(block>>3)%*(unsigned int *)((char *)this+0x68C)];
 while(node){if(node->key==block)goto success;node=node->next;}}
 }
 return 0;
success:return 1;
}

// Native 006C2510..006C25E6, 214 bytes, RET12. The allocator lock, mode
// override at +67C and optional record lookup at +680/+684 are independently
// established by the sibling 006C25F0 reader. The inline path reads the
// trailing unsigned 16-bit length; the record path uses the same member
// reader at 006C1FE0. The original public method name remains unproved.
unsigned int GeneralAllocatorDebug::rva006C2510(char *block, int mode, char **outBody)
{
	Rva00030DD0Lock *lock = m_pLock;
	if (lock)
		Rva00030DD0AddRef(lock);
	unsigned int result = 0;
	int gate = mode;
	if (mode == 2)
		gate = *(int *)((char *)this + 0x67C);
	if (!gate) {
		// Allocated data starts after the two header words. The free-only
		// m_prev/m_next links overlap that data; sizeof(Chunk) includes them.
		// Deriving both views from the header also retains retail's distinct
		// base/size register lifetimes without the bank's volatile self-read.
		GeneralAllocatorChunk *chunk = (GeneralAllocatorChunk *)(block - 8);
		unsigned int h = chunk->m_size;
		unsigned int size;
		if (!(h & 2))
			size = (h & 0x7FFFFFF8) + 4;
		else
			size = h & 0x7FFFFFF8;
		char *base = (char *)chunk + 2 * sizeof(unsigned int);
		unsigned short bodySize = *(unsigned short *)(size + base - 10);
		char *body = (char *)((size - bodySize) + base - 10);
		if (outBody)
			*outBody = body;
		result = bodySize + 2;
	} else if (*(bool *)((char *)this + 0x680)) {
		void *out = 0;
		if (((Rva006C1850 *)((char *)this + 0x684))->rva006C1850((unsigned int)block, &out) && out) {
			char *bytes = *(char **)out;
			unsigned short len = *(unsigned short *)bytes;
			if (len)
				result = rva006C1FE0(bytes + 2, len - 2, outBody);
		}
	}
	if (lock)
		Rva00030DF0Release(lock);
	return result;
}

// ?rva006C26F0@GeneralAllocatorDebug@@QAEXPAX_N@Z,
// retail 0x006C26F0 (934 B): the allocation/free metrics update. With metrics on
// (+0x560) it books the chunk footprint, header overhead, the debug data size
// (rva006C2510) and the user size into the four 64-bit counter blocks and
// stamps the allocation or free time. The usable size is one conditional
// expression (mmapped chunks carry no trailing word), as EA's GetUsableSize;
// with it cl spills the user size into the dead arg slot as retail does.
void GeneralAllocatorDebug::rva006C26F0(void *chunk, bool allocation)
{
 if(allocation) ++m_allocRequests;
 if(m_metricsEnabled && chunk) {
  GeneralAllocatorChunk *block=(GeneralAllocatorChunk *)chunk;
  unsigned int flags=block->m_size;
  unsigned int prev=(flags&2)?block->m_prevSize:0;
  unsigned int footprint=(block->m_size&0x7FFFFFF8)+prev;
  unsigned int usable=(block->m_size&2)?(flags&0x7FFFFFF8):(flags&0x7FFFFFF8)+4;
  unsigned int overhead=prev+8;
  unsigned int debugSize=rva006C2510((char *)block+8,0,0);
  unsigned int size=usable-debugSize-8;
  if(allocation) {
   m_lastAllocation=GetTickCount()/1000;
   ++m_metrics[0].currentCount;
   ++m_metrics[0].totalAllocCount;
   m_metrics[0].currentBytes+=footprint;
   m_metrics[0].totalAllocBytes+=footprint;
   if(m_metrics[0].peakCount<m_metrics[0].currentCount)m_metrics[0].peakCount=m_metrics[0].currentCount;
   if(m_metrics[0].peakBytes<m_metrics[0].currentBytes)m_metrics[0].peakBytes=m_metrics[0].currentBytes;
   m_metrics[1].currentBytes+=overhead;
   m_metrics[1].totalAllocBytes+=overhead;
   m_metrics[2].currentBytes+=debugSize;
   m_metrics[2].totalAllocBytes+=debugSize;
   unsigned int used=size;
   m_metrics[3].currentBytes+=used;
   m_metrics[3].totalAllocBytes+=used;
   if(m_metrics[3].peakBytes<m_metrics[3].currentBytes)m_metrics[3].peakBytes=m_metrics[3].currentBytes;
  } else {
   m_lastFree=GetTickCount()/1000;
   --m_metrics[0].currentCount;
   m_metrics[0].currentBytes-=footprint;
   ++m_metrics[0].totalFreeCount;
   m_metrics[0].totalFreeBytes+=footprint;
   m_metrics[1].currentBytes-=overhead;
   m_metrics[1].totalFreeBytes+=overhead;
   m_metrics[2].currentBytes-=debugSize;
   m_metrics[2].totalFreeBytes+=debugSize;
   m_metrics[3].currentBytes-=size;
   m_metrics[3].totalFreeBytes+=size;
  }
 }
}

// ?rva006C1B60@GeneralAllocatorDebug@@QAEXHI@Z, retail 0x006C1B60 (114 B): the
// debug allocator's option setter. Option 1000 switches the metrics (+0x560),
// option 1001 the block table (+0x680; enabling is refused while +0x67C is 1
// and disabling clears the table at +0x684); every other option goes to the
// base GeneralAllocator option setter 0x000317F0.
void GeneralAllocatorDebug::rva006C1B60(int option, unsigned int value)
{
	if (option == 1000)
		m_metricsEnabled = value != 0;
	else if (option == 1001)
	{
		bool enable = value != 0;
		if (m_tableEnabled != enable)
		{
			if (enable || m_tableGate != 1)
			{
				m_tableEnabled = enable;
				if (!enable)
					m_table.rva006C17B0(true, true);
			}
		}
	}
	else
		GeneralAllocator::rva000317F0(option, value);
}

// ?rva006C4730@GeneralAllocatorDebug@@QAEPAXPAXIH@Z, retail 0x006C4730 (798 B,
// RET12): the debug reallocation. Under the +0x4E4 lock it saves the old
// block's debug data (0x006C2510) into a 1 KB stack buffer or, when larger
// than 992 bytes, a backup block (0x00033ED0 flagged 0x80000000, purging via
// 0x006C33D0 while the delayed-free list at +0x548 is non-empty), books the
// old block out of the metrics (0x006C26F0), reallocates (0x000347A0, same
// purge retry), restores the debug data at the new block's usable end, moves
// the block-table record (+0x680/+0x684) and books the new block in.
void *GeneralAllocatorDebug::rva006C4730(void *data, unsigned int size, int flags)
{
	GeneralAllocatorDebugLockGuard guard(m_pLock);
	void *backupAllocation = 0;
	void *backup = 0;
	unsigned int backupLength;
	void *oldChunk;
	Rva006C2270Record info;
	char localBackup[1024];
	unsigned int extra;
	unsigned int total;
	if (data) {
		oldChunk = (char *)data - 8;
		char *source;
		extra = rva006C2510((char *)data, 0, &source);
		backupLength = extra;
		if (extra > 992) {
			do {
				backup = backupAllocation = mallocBackup(extra + 2);
				if (backupAllocation)
					break;
				if (m_delayedFree.m_next == &m_delayedFree)
					return 0;
				((Rva006C1F60 *)this)->rva006C33D0(0, 0);
			} while (true);
			((unsigned int *)backupAllocation)[-1] |= 4;
		} else
			backup = localBackup;
		memmove(backup, source, extra);
		total = extra + size;
	} else {
		oldChunk = 0;
		backupLength = 0;
		backup = 0;
		rva006C2270(&info, size, flags, 8, 0);
		total = size + info.inlineTotal;
	}
	bookBlock(oldChunk, false);
	void *result = realloc(data, total, flags);
	while (!result) {
		if (m_delayedFree.m_next == &m_delayedFree)
			goto failed;
		((Rva006C1F60 *)this)->rva006C33D0(0, 0);
		result = realloc(data, total, flags);
	}
	if (result) {
		if (data) {
			char *chunk = (char *)result - 8;
			unsigned int h = ((GeneralAllocatorChunk *)chunk)->m_size;
			unsigned int capacity = !(h & 2) ? (h & 0x7FFFFFF8) + 4 : (h & 0x7FFFFFF8);
			if (backup)
				memcpy(chunk + capacity - backupLength, backup, backupLength);
			else
				*(unsigned short *)(chunk + capacity - 2) = 0;
			if (m_tableEnabled) {
				void *record = 0;
				if (((Rva006C1850 *)&m_table)->rva006C1850((unsigned int)data, &record) && result != data) {
					void *oldRecord = *(void **)record;
					((Rva006C1D60 *)this)->rva006C1D60((unsigned int)data, false);
					if (!((Rva006C39F0Owner *)this)->rva006C39F0((unsigned int)result, 0, (unsigned int)oldRecord, 0)) {
						rva00033150(result);
						result = 0;
					}
				}
			}
			if (result) {
				unsigned int *stored = (unsigned int *)rva006C25F0Run6(result, 2, 0, 0, 0, 2);
				if (stored)
					*stored = size;
				bookBlock((char *)result - 8, true);
			}
		} else {
			if (rva006C3D30(&info, result, true)) {
				bookBlock((char *)result - 8, true);
			} else {
				rva00033150(result);
				result = 0;
			}
		}
	} else {
failed:
		if (data)
			((Rva006C1D60 *)this)->rva006C1D60((unsigned int)data, true);
	}
	if (backupAllocation)
		rva00033150(backupAllocation);
	return result;
}
