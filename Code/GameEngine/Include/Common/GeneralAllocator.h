// FILE: GeneralAllocator.h ///////////////////////////////////////////////////////////////////////
// Desc:   Canonical BFME2 EA::Allocator::GeneralAllocator (the PPMalloc heap behind MemoryPool).
//
// Target facts:
//  - No virtual functions: the constructor 0x00033B90 stores no table and writes a byte at +0,
//    the flag the setup 0x00033700 tests and sets (0x00033707, 0x00033719) and the teardown
//    0x00033D50 tests and clears (0x00033D7A, 0x00033D88). The derived debug allocator's
//    constructor 0x006C4A50 calls 0x00033B90 first (0x006C4A8E) and stores no table either.
//  - sizeof 0x510: MemoryPool::_Init passes 0x510 to HeapAlloc (0x0003009A, 0x00030116) and runs
//    0x00033B90 on the block (0x000300D0, 0x00030144). The constructor's stores run from +0x000
//    to the byte at +0x50C; the derived constructor's own members start at +0x510 (0x006C4AD8).
//  - Field widths are the constructor's stores; +0x46D = 1, +0x474 = 9, +0x475 = 0x0A,
//    +0x4B4 = 0x100, +0x4D4 = 0x1000, +0x4D8 = 0x1000000, +0x4DC = 0x400000, +0x508..+0x50C =
//    DD DE CD AB FE; +0x4B8/+0x4BC = 0x000327D0 and this, +0x4C0/+0x4C4 = 0x00031420 and this.
//  - +0x4E4 is the lock: the setup builds it in the +0x4E8 storage through 0x00030D90 and stores
//    the result (0x0003371E..0x0003372D); the teardown passes it to 0x00030DD0 (0x00033D6F) and
//    0x00030DF0 (0x00033E6B).
//  - The destructor is not virtual and is called out of line: 0x006C3D08 in the derived
//    destructor 0x006C3CC0 and the unwind funclet 0x007A7CF0 reach 0x00034D00, `jmp 0x00033D50`;
//    the matched destructor row owns this 0x00034D00 thunk, distinct from teardown 0x00033D50.
//  - Snapshot (+0 'SNAP' 0x534E4150, +4 size, +8 context, +0xC..+0xE flags, +0x10..+0x20) is
//    laid out by its constructor 0x00031570.
//  - The class-key is `class`: every ledger row mangles VGeneralAllocator@Allocator@EA@@.
// Unproven: the constructor 0x00033B90 is rowed under the address-derived class
// Rva00033B90Allocator, so it is not declared here. Field names are offsets unless a retail
// access proves the role; method names are the ledger rows'. TraceFunction and ReportFunction
// spell the parameter types the 0x000353F0 and 0x00035540 rows mangle.
// Include at file scope: this header opens namespace EA::Allocator itself.
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef __BFME2_GENERALALLOCATOR_H_
#define __BFME2_GENERALALLOCATOR_H_

struct Rva00030DD0Lock;
struct Rva00031010Node;

namespace EA
{
namespace Allocator
{

struct BlockInfo;

//-------------------------------------------------------------------------------------------------
class GeneralAllocator
{
public:
	// Report state the snapshot builder 0x00034D10 fills and 0x000338D0 releases.
	struct Snapshot
	{
		unsigned int m_magic;			// +0x00 'SNAP'
		unsigned int m_size;			// +0x04
		void *m_arg2;				// +0x08
		unsigned char m_state[4];		// +0x0C
		unsigned int m_values[5];		// +0x10

		__declspec(nothrow) Snapshot(unsigned int size, void *context);	// 0x00031570
	};

	typedef void (*TraceFunction)(const char *text, void *context);
	typedef bool (*ReportFunction)(const BlockInfo *info, void *context);

	~GeneralAllocator();	// 0x00034D00

	static unsigned int GetLargeBinIndexFromChunkSize(unsigned int size);	// 0x00030F10
	static void AddDoubleFencepost(void *chunk, unsigned int flags);	// 0x00031120
	void SetAssertionFailureFunction(void *function, void *context);	// 0x000313E0

	unsigned int rva000311E0(const void *src, unsigned int count, char *ascii, unsigned short *wide, unsigned int cap);
	int rva00031430(const void *block, char *dst, unsigned int left);
	void rva00031660(void *node);
	void *rva00031680(const void *block);
	bool rva000316B0(void *block, bool release);
	void rva000317F0(int option, unsigned int value);
	void *rva00031B60(const void *block);
	bool rva00031BB0(const void *block);
	int rva00031BF0(const void *block);
	int rva00031D00(void *block);
	int rva00031E60(const void *block);
	int rva00031F90(void *block);
	unsigned int rva00032050(void *chunk, unsigned int flags);
	unsigned int rva000320E0(void *chunk, unsigned int flags, bool checkPrev, bool skipPrev);
	unsigned int rva00032160(void *block);
	int rva000321F0(int level);
	int rva000327E0(const void *blockData, char *dst, unsigned int left);
	bool rva00032830(const void *block, int addressType);
	bool rva00032920(const void *block);
	bool rva000329E0(int level);
	unsigned int rva00032A20(const void *block);
	void *rva00032B00(unsigned int size);
	unsigned int rva00032C60(unsigned int pad);
	void *rva00032DF0(unsigned int size);
	void rva00032EC0(const void *block, BlockInfo *info);
	const BlockInfo *rva00032F60(void *context, int blockTypes);
	void rva00033150(const void *block);
	bool rva000332D0(void *core, unsigned int size, bool freeCore, bool trimCore, void *releaseFunction, void *releaseContext);
	Rva00031010Node *rva000334A0(unsigned int size);
	void rva000338D0(Snapshot *snapshot);
	void rva000338F0(void *block);
	unsigned int rva00033A80(bool full);
	bool rva00033D50();
	void rva00033E90(void *context);
	void *rva000344A0(unsigned int size, unsigned int alignment, unsigned int offset, int flags);
	void *realloc(void *block, unsigned int size, int flags);	// 0x000347A0
	void *calloc(unsigned int count, unsigned int size, int flags);	// 0x00034A60
	void *rva00034D10(int blockTypes, bool copy, void *storage, unsigned int storageSize);
	void *rva00035080(unsigned int size, int flags);
	void *rva00035100(unsigned int size, unsigned int alignment, unsigned int offset, int flags);
	void *rva00035190(void *block, unsigned int size, int flags);
	void *rva00035210(unsigned int count, unsigned int size, int flags);
	void *rva00035290(unsigned int count, unsigned int size, void **out, int flags);
	void *rva00035320(unsigned int count, const unsigned int *sizes, void **out, int flags);
	void *rva000353B0(void *context, int blockTypes, bool copy, void *storage, unsigned int storageSize);
	void traceAllocatedMemory(TraceFunction function, void *functionContext, void *context, int blockTypes);	// 0x000353F0
	bool reportHeap(ReportFunction function, void *context, int blockTypes, bool copy, char *storage, unsigned int storageSize);	// 0x00035540
	unsigned int rva006C1D10(const void *block);

	bool m_000;					// +0x000 set by 0x00033700, cleared by 0x00033D50
	unsigned int m_004;				// +0x004
	Rva00031010Node *m_008[10];			// +0x008
	Rva00031010Node *m_030[256];			// +0x030
	unsigned int m_430[4];				// +0x430
	Rva00031010Node *m_440;				// +0x440
	Rva00031010Node *m_444;				// +0x444
	unsigned int m_448[8];				// +0x448 list head, next +0x460, prev +0x464
	unsigned int m_468;				// +0x468
	bool m_46C;					// +0x46C
	bool m_46D;					// +0x46D
	unsigned int m_470;				// +0x470
	unsigned char m_474;				// +0x474
	unsigned char m_475;				// +0x475
	unsigned int m_478;				// +0x478
	unsigned int m_47C;				// +0x47C
	unsigned int m_480;				// +0x480
	unsigned char m_484;				// +0x484
	unsigned int m_488;				// +0x488
	unsigned int m_48C;				// +0x48C
	unsigned int m_490;				// +0x490
	unsigned int m_494;				// +0x494
	bool m_498;					// +0x498
	unsigned int m_49C[4];				// +0x49C list head
	unsigned int m_4AC;				// +0x4AC
	unsigned int m_4B0;				// +0x4B0
	unsigned int m_4B4;				// +0x4B4
	void *m_4B8;					// +0x4B8 0x000327D0 by default
	void *m_4BC;					// +0x4BC
	void *m_4C0;					// +0x4C0 0x00031420 by default
	void *m_4C4;					// +0x4C4
	unsigned int m_4C8;				// +0x4C8
	unsigned int m_4CC;				// +0x4CC
	unsigned int m_4D0;				// +0x4D0
	unsigned int m_4D4;				// +0x4D4
	unsigned int m_4D8;				// +0x4D8
	unsigned int m_4DC;				// +0x4DC
	bool m_4E0;					// +0x4E0
	Rva00030DD0Lock *m_pLock;			// +0x4E4
	unsigned int m_lockStorage[8];			// +0x4E8 the lock m_pLock points to
	unsigned char m_508[5];				// +0x508 fill bytes
};

}
}

#endif
