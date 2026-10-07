// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ??1Rva0022CCB0@@QAE@XZ @0x0022CCB0 53B
// Non-virtual dtor over AsciiString at +0 and rowed member ??1Rva00226829@@QAE@XZ
// at +8 with 4B POD gap at +4. Retail calls the +8 dtor first (lea ecx [esi+8]
// call 0x0022C5A2) then the narrow releaseBuffer 0x00036410 for +0 under an
// __EH_prolog frame with and [ebp-4] 0 and or [ebp-4] -1. Same 53B EH shape as
// the rowed ??1Rva0022304A@@QAE@XZ at 0x0022304A. Evidence: unlock packet calls
// rowed 0x0022C5A2 and rowed releaseBuffer 0x00036410; callers at 0x0022CFFE
// 0x00418427 and jmp at 0x00786606; unblocks 0x0022CFE6 0x004183AC.
#include "ascii_string.h"

class Rva00226829
{
public:
	~Rva00226829();
};

class Rva0022CCB0
{
public:
	~Rva0022CCB0();
private:
	AsciiString m_head;
	int m_unk04;
	Rva00226829 m_item;
};

Rva0022CCB0::~Rva0022CCB0()
{
}

class Rva002294A3
{
public:
	~Rva002294A3();
};

class Rva002294D0
{
public:
	~Rva002294D0();
};

class Rva0022CCE5
{
public:
	void rva0022CCE5();
};

void Rva0022CCE5::rva0022CCE5()
{
	((Rva002294A3 *)this)->~Rva002294A3();
}

class Rva0022CCEA
{
public:
	void rva0022CCEA();
};

void Rva0022CCEA::rva0022CCEA()
{
	((Rva002294D0 *)this)->~Rva002294D0();
}

