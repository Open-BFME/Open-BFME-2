// cl: /Oy-
// Four top-byte forwards (25B each): push ebp, mov ebp, esp,
// lea eax, [ebp+0x13], push eax, push [ebp+0x10], push [ebp+0x0C],
// push [ebp+8], call <worker>, pop ebp, ret N. Each forwards (a, b, c)
// plus the address of c's top byte to a stdcall worker; /O1 keeps the
// pushes on the stack slots and /Oy- keeps the ebp frame. Members with
// ret 0x10 take an ignored fourth dword; ret 0x0C members take three.
// 0x001ECB78 (-> 0x001EC1B4, 4 params), 0x001ECD19 (-> 0x001EC1B4,
// 3 params), 0x004F83F2 (-> 0x004F7EE9, 4 params), 0x004F8B89 (->
// 0x004F7EE9, 3 params). The top-byte address purpose is unrecovered;
// callee identities unproven (opaque pins); names address-derived.
// One ledger row per forward.

void __stdcall Rva001EC1B4Worker(int a, int b, int c, char *topByte);
void __stdcall Rva004F7EE9Worker(int a, int b, int c, char *topByte);

void __stdcall Rva001ECB78(int a, int b, int c, int ignored)
{
	Rva001EC1B4Worker(a, b, c, (char *)&c + 3);
}

void __stdcall Rva001ECD19(int a, int b, int c)
{
	Rva001EC1B4Worker(a, b, c, (char *)&c + 3);
}
