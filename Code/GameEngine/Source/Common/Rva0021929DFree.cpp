// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
// ?Rva0021929DFree@@YGXPAPAX@Z @0x0021929D 35B
// Honest-address free function: virtual slot 0 with 0 then operator delete and clear.
// Evidence: retail mov eax,[ecx]; push 0; call [eax] plus direct call to rowed
// ??3@YAXPAX@Z 0x0002FD60; caller 0x0040A1AC passes slot pointer with no stack
// cleanup (stdcall ret 4); and [esi],0 clearing matches /O1.
struct IRva0021929D
{
	virtual void *Get(int x) = 0;
};

void __stdcall Rva0021929DFree(void **slot)
{
	void *toFree = *slot ? ((IRva0021929D *)*slot)->Get(0) : 0;
	::operator delete(toFree);
	*slot = 0;
}
