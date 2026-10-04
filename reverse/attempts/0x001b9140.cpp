// ?Rva009A86F0Allocate@@YAHPAX@Z
// partial score=0.95 date=2026-10-04
// ?Rva009A86F0Allocate@@YAHPAX@Z
// 0x001B9140 396B retail codec allocator. Ported from the BFME1 donor body
// (reference/open-bfme-1/targets/game/reverse/attempts/0x009a86f0.cpp) whose
// two separate halving locals match retail's ecx/edx rotation; the BFME1
// declaration lives in reference/open-bfme-1/game/GameEngine/Source/Common/BfmeCheckJX.cpp.
// Callees: bfmeStepJW 0x001B9040 (rowed), Rva001B6400Allocation::operator new
// 0x001B6400 (matched).
struct CodecAllocState;
struct Rva009A8910Context;
class Rva001B6400Allocation
{
public:
	enum AllocationTag { Zero = 0 };
	static void *operator new(unsigned, AllocationTag);
};
void bfmeStepJW(void*);

struct CodecAllocState
{
	void *at00;
	void *at04;
	unsigned char pad08[0x104];
	void *at10c;
	void *at110;
	void *at114;
	void *at118;
	void *at11c;
	void *at120;
	unsigned char pad124[0x24];
	void *at148;
	void *at14c;
	unsigned char pad150[0xA8];
	unsigned at1f8;
	unsigned at1fc;
	unsigned char pad200[0x28];
	unsigned at228;
	unsigned char pad22c[0x4C0];
	void *at6ec;
	void *at6f0;
	void *at6f4;
	void *at6f8;
	void *at6fc;
	void *at700;
};

// ?Rva009A86F0Allocate@@YAHPAX@Z present-unmatched
int Rva009A86F0Allocate(void* p)
{
	CodecAllocState* self = (CodecAllocState*)p;
	unsigned int halfCount;
	unsigned int halfCount2;
	unsigned int bufferSize;
	unsigned int bufferSize2;
	unsigned int planeSize;
	unsigned int tailSize;
	bfmeStepJW(p);

	void* first = Rva001B6400Allocation::operator new(0x320, Rva001B6400Allocation::Zero);
	self->at00 = first;
	if (first == 0)
		goto failure;
	self->at04 = (void*)(((unsigned)self->at00 + 0x1f) & ~0x1f);

	void* second = Rva001B6400Allocation::operator new((self->at1f8 + 0xa) << 4, Rva001B6400Allocation::Zero);
	self->at118 = second;
	if (second == 0)
		goto failure;
	halfCount = self->at1f8 >> 1;
	self->at10c = (void*)(((unsigned)self->at118 + 0x1f) & ~0x1f);

	void* third = Rva001B6400Allocation::operator new((halfCount + 0xa) << 4, Rva001B6400Allocation::Zero);
	self->at11c = third;
	if (third == 0)
		goto failure;
	halfCount2 = self->at1f8 >> 1;
	halfCount2 += 0;
	self->at110 = (void*)(((unsigned)self->at11c + 0x1f) & ~0x1f);

	void* fourth = Rva001B6400Allocation::operator new((halfCount2 + 0xa) << 4, Rva001B6400Allocation::Zero);
	self->at120 = fourth;
	if (fourth == 0)
		goto failure;
	self->at114 = (void*)(((unsigned)self->at120 + 0x1f) & ~0x1f);

	bufferSize = self->at228 + 0x20;
	void* fifth = Rva001B6400Allocation::operator new(bufferSize, Rva001B6400Allocation::Zero);
	self->at6f8 = fifth;
	if (fifth == 0)
		goto failure;
	bufferSize2 = self->at228 + 0x20;
	self->at6ec = (void*)(((unsigned)self->at6f8 + 0x1f) & ~0x1f);

	void* sixth = Rva001B6400Allocation::operator new(bufferSize2, Rva001B6400Allocation::Zero);
	self->at6fc = sixth;
	if (sixth == 0)
		goto failure;
	self->at6f0 = (void*)(((unsigned)self->at6fc + 0x1f) & ~0x1f);

	planeSize = self->at228 * 4 + 0x20;
	self->at700 = Rva001B6400Allocation::operator new(planeSize, Rva001B6400Allocation::Zero);
	if (self->at700 == 0)
		goto failure;
	tailSize = self->at1fc * 4 + 0x20;
	self->at6f4 = (void*)(((unsigned)self->at700 + 0x1f) & ~0x1f);

	void* eighth = Rva001B6400Allocation::operator new(tailSize, Rva001B6400Allocation::Zero);
	self->at14c = eighth;
	if (eighth == 0)
		goto failure;
	self->at148 = (void*)(((unsigned)self->at14c + 0x1f) & ~0x1f);
	return 1;

failure:
	bfmeStepJW(p);
	return 0;
}
