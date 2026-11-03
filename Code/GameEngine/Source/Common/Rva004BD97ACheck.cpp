// cl: /O1 /DNDEBUG /MD
//
// ?rva004BD97A@@YGHHH@Z @ 0x004BD97A (39B).
// Temp plus two calls returning the arg: build a 4-byte local, run the
// rowed memset thunk 0x006291AE on (&tmp,0,4), then the rowed copy ctor 0x002CF0F0
// on (arg as this) with (&tmp), returning arg. Evidence: retail pushes 4 /
// lea tmp / push 0 / push tmp for the first call (caller-cleans cdecl), mov
// ecx,arg for the second call's this, no add-esp after it (callee-cleans
// thiscall), mov eax,arg for return; boundary prev ret at 0x004BD979 and
// next proc at 0x004BD9A1.

// 0x006291AE is the rowed memset import thunk; 0x002CF0F0 is the rowed
// BfmeFixedStorage002CF0F0 copy constructor.
#pragma function(memset)
#include <string.h>

#include "../../Include/Common/BfmeFixedStorage002CF0F0.h"

int __stdcall rva004BD97A(int arg)
{
	int tmp;
	memset(&tmp, 0, 4);
	((BfmeFixedStorage002CF0F0 *)arg)->BfmeFixedStorage002CF0F0::BfmeFixedStorage002CF0F0(
		*(BfmeFixedStorage002CF0F0 *)&tmp);
	return arg;
}

