// Allocate-and-fill factory.
//
// BFME1 byte-identical donor (reference/open-bfme-1
// Code/GameEngine/Source/Common/Bfme5FactoryStubs.cpp); trimmed to the single
// T1 body the sweep places. The redundant vtable stores survive via volatile
// lvalues standing in for the constructor boundary.

#include "../../Include/GameNetwork/Gen007F0130.h"

extern "C" char __identifier("??_7Rva006613E0@@6B@")[];
extern "C" char __identifier("??_7Gen007F4D00@@6BGen007F4D00Listener@@@")[];
extern "C" char __identifier("??_7Gen007F4D00@@6BGen007F4D00Owner@@@")[];

struct AriesUdp
{
	void *m_ownerVtable;
	void *m_listenerVtable;
	int m_bfme08;
	int m_bfme0c;
	int m_bfme10;
	int m_bfme14;
};

AriesUdp * __cdecl bfme5MakeObj18(void)
{
	void *memory = Gen007F0130::operator new(0x18);
	AriesUdp *instance;

	if (memory) {
		instance = (AriesUdp *)memory;
		*(void *volatile *)&instance->m_listenerVtable = __identifier("??_7Rva006613E0@@6B@");
		*(void *volatile *)&instance->m_ownerVtable = __identifier("??_7Gen007F4D00@@6BGen007F4D00Owner@@@");
		*(void *volatile *)&instance->m_listenerVtable = __identifier("??_7Gen007F4D00@@6BGen007F4D00Listener@@@");
		instance->m_bfme08 = 0;
		instance->m_bfme0c = 0;
		instance->m_bfme10 = 0;
		instance->m_bfme14 = 0;
		return instance;
	}

	return 0;
}
