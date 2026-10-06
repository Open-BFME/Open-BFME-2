// cl: /DNDEBUG /MD
//
// 0x00614200   5B   8b 44 24 04 c3   mov eax,[esp+4] ; ret
//
// The whole body is "load the first stack argument and return it": no
// prologue, no stack cleanup, so the argument is at [esp+4] and the call is
// __cdecl (a __thiscall or __stdcall member taking one argument would end in
// `ret 4`, because it would have to clean the argument itself).
//
// Identity is not recoverable -- the address is unclaimed, the inventory name
// is a Ghidra placeholder (FUN_00a14200), and nothing calls it that the ledger
// can see. It therefore keeps an address-derived name. AGENTS.md permits an
// opaque address-token name (it is self-labelling and counted by
// progress.py) and prohibits a plausible guessed class or method, which no
// gate can see through.
//
// The parameter type is likewise unknowable from the bytes: returning `void*`
// and returning `int` compile identically here, and only the mangled name
// differs. `void*` is written because it is the weakest claim -- it asserts
// nothing about the value's meaning.

void *rva00614200(void *p)
{
	return p;
}
