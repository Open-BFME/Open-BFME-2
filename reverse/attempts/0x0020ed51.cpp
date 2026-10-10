// ?rva0020ED51@Rva0020ED51@@QAEXPAHPBVRva002E15BC@@_N@Z
// partial score=0.92 date=2026-10-10
// Seat Z1 (w5-z1) near bank for 0x0020ED51 (61B), twin of the rowed
// Rva003EEFA0::rva003EEFA0 list-walk (Code/GameEngine/Source/Common/
// Rva003EE900Forward.cpp). Every semantic fact is verified: the begin/end
// pair is the FIRST stack argument, the per-element work goes to the rowed
// Rva002E15BC::rva002E1588(void *, bool) on the SECOND argument with the
// THIRD argument forwarded as that callee's flag, and the loop body/count
// shape is byte-identical to the rowed sibling.
//
// The only difference is MSVC's stack-argument rematerialisation: retail
// reads arg2 (receiver) and arg3 (flag) from the incoming stack slots
// ([esp+0x14] twice) on EVERY iteration and uses only ESI (the array) and
// EDI (the counter, its save deferred) as saved registers. Every source
// spelling tried -- pointer or int receiver, bool or int flag, cast or
// direct call, free function -- makes MSVC rematerialise them into EBX/EBP
// and save four registers instead of two (70 bytes instead of 61).
// Source signature that compiles closest:
//   void Rva0020ED51::rva0020ED51(Int *arr, Rva002E15BC *recv, bool flag)
#include <map>
typedef int Int;

class Rva002E15BC
{
public:
	void rva002E1588(void *p, bool flag);
};

class Rva0020ED51
{
public:
	void rva0020ED51(Int *arr, Rva002E15BC *recv, bool flag);
};

void Rva0020ED51::rva0020ED51(Int *arr, Rva002E15BC *recv, bool flag)
{
	Int *p = (Int *)arr;
	for (unsigned int i = 0; i < (unsigned int)((p[1] - p[0]) >> 2); ++i) {
		Int v = *(Int *)(p[0] + i * 4);
		if (v != 0)
			recv->rva002E1588((void *)v, flag);
	}
}
