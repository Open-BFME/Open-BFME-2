// cl: /MD
// ?Rva00226146Less@@YG_NHH@Z @0x00226146 (16B): signed int less predicate.
// Retail is frameless: mov ecx [esp+4]; xor eax eax; cmp ecx [esp+8];
// setl al; ret 8. Two stack args popped by callee so __stdcall. setl proves
// signed <. Callers push two dwords then call: 0x00226510 in FUN_006264B3
// and 0x0056DF61 in FUN_0096DF04. No callees. Precedent for Less naming
// and YG_NHH shape: Rva0006038D4CStrLess and Rva0056866ALess.
bool __stdcall Rva00226146Less(int a, int b)
{
	return a < b;
}
