// cl: /Ireference/shims/bfme2_ascii /MD
// ?Rva00410AABFree@@YGXPAX@Z at 0x00410AAB (28B).
// Free helper: destroys Rva00410688 at +4 via rowed dtor then frees via
// rowed operator delete 0x30830. Evidence: 3 callers in 0x410D05/0x410D96,
// unblocks 2.

// Retail calls free directly (the game allocator), not through the CRT
// import: read <stdlib.h> without dllimport.
#define _CRTIMP
#include <stdlib.h>
#include <new>
#undef _CRTIMP

#include "ascii_string.h"


struct TargetRef00217D4C
{
	virtual void *destroy(unsigned flags);
	int references;
};

class Rva00410688
{
public:
	~Rva00410688();
private:
	AsciiString m_00;
	TargetRef00217D4C *m_04;
};

struct Holder00410AAB
{
	char m_pad00[4];
	Rva00410688 m_04;
};



void __stdcall Rva00410AABFree(void *p);

void __stdcall Rva00410AABFree(void *memoryBlock)
{
	((Holder00410AAB *)memoryBlock)->m_04.~Rva00410688();
	if (memoryBlock != 0)
		free(memoryBlock);
}

class Rva00410AABHelper
{
public:
	void rva00410AAB(void *memoryBlock);
};

// ICF-folded twin of Rva00410AABFree above (same 28 bytes at 0x00410AAB):
// the member spelling ignores its receiver, so its stack frame matches the
// stdcall spelling exactly, including the callee-cleaned return.
void Rva00410AABHelper::rva00410AAB(void *memoryBlock)
{
	((Holder00410AAB *)memoryBlock)->m_04.~Rva00410688();
	if (memoryBlock != 0)
		free(memoryBlock);
}
