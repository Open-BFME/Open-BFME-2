// ?rva006C26F0@GeneralAllocatorDebug@@QAEXTGeneralAllocatorMetricBlockArg@@_N@Z
// partial score=0.93 date=2026-10-09
// ?rva006C1F60@Rva006C1F60@@QAEHI@Z @ 0x006C1F60 113B chain of 0x00030DF0
// Release. AddRef at +0x4e4 Release guarded float clamp via __ftol2 returning
// clamped int. Evidence: calls AddRef 0x00030DD0 Release 0x00030DF0 __ftol2
// rowed; flag bit 0x800 at +0x514 scale float at +0x534 min at +0x538 max at
// +0x53c; caller at 0x006C2463. Honest address-derived method of Rva006C1F60.
struct Rva00030DD0Lock;
int Rva00030DD0AddRef(Rva00030DD0Lock *lock);
int Rva00030DF0Release(Rva00030DD0Lock *lock);
extern "C" int __cdecl __ftol2(float f);
class Rva006C1F60
{
public:
	int rva006C1F60(unsigned int v);
	int rva006C1DC0(unsigned int block);
private:
	unsigned char m_pad0[0x4e4];
	Rva00030DD0Lock *m_lock;
	unsigned char m_pad1[0x514 - 0x4e4 - 4];
	int m_flags;
	unsigned char m_pad2[0x534 - 0x514 - 4];
	float m_scale;
	unsigned int m_min;
	unsigned int m_max;
};
int Rva006C1F60::rva006C1F60(unsigned int v)
{
	Rva00030DD0Lock *lock = m_lock;
	if (lock != 0)
		Rva00030DD0AddRef(lock);
	unsigned int result = 0;
	if ((m_flags & 0x800) != 0) {
		float f = (float)v * m_scale;
		result = (unsigned int)(int)f;
		if (result < m_min)
			result = m_min;
		if (result > m_max)
			result = m_max;
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
#pragma intrinsic(memset)
#pragma intrinsic(memcpy)

struct Rva00030DD0Lock;
int Rva00030DD0AddRef(Rva00030DD0Lock *lock);
int Rva00030DF0Release(Rva00030DD0Lock *lock);

namespace EA { namespace Allocator {
struct BlockInfo
{
	void *mpCore; // +0x00
};
class GeneralAllocator
{
public:
	unsigned int rva00032A20(const void *block);
	void *rva000353B0(void *core, int types, bool b, void *d, unsigned int e);
	const BlockInfo *rva00032F60(void *handle, int types);
	void rva00033E90(void *handle);
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

union GeneralAllocatorMetricBlockArg { GeneralAllocatorChunk *block; unsigned int size; };

struct GeneralAllocatorMetricCounters
{
 unsigned __int64 currentCount, totalAllocCount, peakCount;
 unsigned __int64 currentBytes, totalAllocBytes, peakBytes;
 unsigned __int64 totalFreeCount, totalFreeBytes;
};
extern "C" __declspec(dllimport) unsigned int __stdcall GetTickCount(void);

class GeneralAllocatorDebug : public EA::Allocator::GeneralAllocator
{
public:
	void rva006C26F0(GeneralAllocatorMetricBlockArg arg, bool allocation);
	unsigned int rva006C2510(char *block, int mode, char **outBody);
	void *rva006C2010Run6(void *block, unsigned int size, unsigned short kind, void *dst, unsigned int capacity, unsigned int *outLen);
	void rva006C2AA0(unsigned char fillFree, unsigned char fillDelayedFree,
		unsigned char fillNew, unsigned char fillGuard, unsigned char fillUnusedCore);
	void *rva006C25F0Run6(void *runBlock, int kind, int zero3, int zero2,
		unsigned int *outLen, int zero1);
private:
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

	unsigned char m_base000[0x448];
	GeneralAllocatorCore m_coreSentinel; // +0x448
	unsigned char m_pad468[0x4E4 - 0x468];
	Rva00030DD0Lock *m_lock; // +0x4E4
	unsigned char m_pad4E8[0x508 - 0x4E8];
	unsigned char m_fillFree; // +0x508
	unsigned char m_fillDelayedFree; // +0x509
	unsigned char m_fillNew; // +0x50A
	unsigned char m_fillGuard; // +0x50B
	unsigned char m_fillUnusedCore; // +0x50C
	unsigned char m_pad50D[0x514 - 0x50D];
	unsigned int m_flags; // +0x514
	unsigned char m_pad518[0x540 - 0x518];
	unsigned int m_delayedFreeTotal; // +0x540
	unsigned int m_544;
	GeneralAllocatorChunk m_delayedFree; // +0x548
 unsigned char m_pad558[8];
 bool m_metricsEnabled; // +0x560
 unsigned char m_pad561[7];
 unsigned __int64 m_allocRequests; // +0x568
 GeneralAllocatorMetricCounters m_metrics[4]; // +0x570..0x66F
 unsigned int m_lastAllocation; // +0x670
 unsigned int m_lastFree; // +0x674
};

void GeneralAllocatorDebug::rva006C2AA0(unsigned char fillFree, unsigned char fillDelayedFree,
	unsigned char fillNew, unsigned char fillGuard, unsigned char fillUnusedCore)
{
	GeneralAllocatorDebugLockGuard guard(m_lock);

	m_fillNew = fillNew;
	m_fillUnusedCore = fillUnusedCore;

	if (m_fillFree != fillFree)
	{
		m_fillFree = fillFree;
		for (GeneralAllocatorCore *core = m_coreSentinel.m_next; core != &m_coreSentinel; core = core->m_next)
		{
			char *end = (char *)core + core->m_size - 0x10;
			for (char *chunk = core->m_first; chunk < end;
				chunk += ((GeneralAllocatorChunk *)chunk)->m_size & 0x7FFFFFF8)
			{
				unsigned int size = ((GeneralAllocatorChunk *)chunk)->m_size & 0x7FFFFFF8;
				if (!(((GeneralAllocatorChunk *)(chunk + size))->m_size & 1))
					memset(chunk + 0x10, m_fillFree, size - 0x10);
			}
		}
	}

	if (m_fillDelayedFree != fillDelayedFree)
	{
		m_fillDelayedFree = fillDelayedFree;
		if (fillDelayedFree == 1)
			m_delayedFreeTotal = 0;
		for (GeneralAllocatorChunk *chunk = m_delayedFree.m_next; chunk != &m_delayedFree; chunk = chunk->m_next)
		{
			char *data = (char *)chunk + 8;
			unsigned int size = getDebugDataSize(data);
			memset(data + 8, m_fillDelayedFree, size - 8);
		}
	}

	if (m_fillGuard != fillGuard)
	{
		m_fillGuard = fillGuard;
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
				memset(run, m_fillGuard, end - run);
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
 Rva00030DD0Lock *lock=m_lock;
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
 if(!*(bool *)((char *)this+0x680)||*(int *)((char *)this+0x530))goto success;
 {Rva006C1DC0Node **buckets=*(Rva006C1DC0Node ***)((char *)this+0x684);
 if(buckets){Rva006C1DC0Node *node=buckets[(block>>3)%*(unsigned int *)((char *)this+0x68C)];
 while(node){if(node->key==block)goto success;node=node->next;}}
 }
 return 0;
success:return 1;
}

// Native 006C26F0..006C2A96 (934B): allocation request counter and four
// 64-bit accounting records, gated by +560. All layout names are structural
// inferences from target accesses; original method/field names are unknown.
void GeneralAllocatorDebug::rva006C26F0(GeneralAllocatorMetricBlockArg arg, bool allocation)
{
 if(allocation) ++m_allocRequests;
 if(m_metricsEnabled && arg.block) {
  GeneralAllocatorChunk *block=arg.block;
  unsigned int flags=block->m_size;
  unsigned int prev=(flags&2)?block->m_prevSize:0;
  unsigned int footprint=(block->m_size&0x7FFFFFF8)+prev;
  arg.size=flags&0x7FFFFFF8;
  if(!(block->m_size&2))arg.size+=4;
  unsigned int overhead=prev+8;
  unsigned int debugSize=rva006C2510((char *)block+8,0,0);
  arg.size-=debugSize+8;
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
   m_metrics[3].currentBytes+=arg.size;
   m_metrics[3].totalAllocBytes+=arg.size;
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
   m_metrics[3].currentBytes-=arg.size;
   m_metrics[3].totalFreeBytes+=arg.size;
  }
 }
}
