// cl: /O1
// Two retail wrappers (23B + 21B) over the shared callee at 0x004097AF.
// 0x00409892: push [esp+8], push 0x4A, push [esp+0x10], push [esp+0x10],
//   call, add esp, 0x10, ret -> callee(a, b, 0x4A, b).
// 0x004098A9: push 0, push 0x41, push [esp+0x10], push [esp+0x10],
//   call, add esp, 0x10, ret -> callee(a, b, 0x41, 0).
// /O1 keeps the pushes on the stack slots. Callee/tag identities unproven;
// names are address-derived. One ledger row per wrapper.

extern "C" int __cdecl Rva004097AFWorker(int a, int b, int c, int d);

int Rva00409892(int a, int b)
{
	return Rva004097AFWorker(a, b, 0x4A, b);
}

int Rva004098A9(int a, int b)
{
	return Rva004097AFWorker(a, b, 0x41, 0);
}
