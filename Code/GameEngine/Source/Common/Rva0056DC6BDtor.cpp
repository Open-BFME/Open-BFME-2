// cl: /MD
//
// ??1Rva0056DC6B@@UAE@XZ retail 0x0056DC6B 11B.
// Store vtable 0x0086DB78 then tail-jmp base dtor ??1Rva005248D0@@UAE@XZ.
// Evidence: pin base dtor; vtable store plus jmp; callers include Unwind
// funclets; prev ConstIntGetters TU flags.
#include "../../Include/GameClient/Rva005248D0.h"

#include "../../Include/Common/Rva0056DC6B.h"

// Select-any like the identical copies other TUs emit (a strong definition here
// would be a duplicate at link time); the anchor keeps the noinline body emitted.
__declspec(noinline) inline Rva0056DC6B::~Rva0056DC6B()
{
}

// ?bfmeAnchorRva0056DC6BDtor absent-from-retail
void bfmeAnchorRva0056DC6BDtor(Rva0056DC6B *p)
{
	p->Rva0056DC6B::~Rva0056DC6B();
}
