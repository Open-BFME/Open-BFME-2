// ?Rva0006FABFClear@@YGXPAPAXPAX@Z
// partial score=0.92 date=2026-10-04
// cl: /O1 /DNDEBUG /MD
// ?Rva0006FABFClear@@YGXPAPAXPAX@Z @0x0006FABF 45B: free-list prefix clear to stop. Evidence: callers 0x0006FB53 push ecx 0 and 0x000715F0 lea ebp-0x20 push ebx; global g_00DB4254; ret 8 two stack args.
extern void *g_00DB4254;

void __stdcall Rva0006FABFClear(void **ppHead, void *stop)
{
	void *cur = *ppHead;
	while (cur != stop) {
		void *freeHead = g_00DB4254;
		void *tmp = cur;
		cur = *(void **)cur;
		*(void **)tmp = freeHead;
		g_00DB4254 = tmp;
	}
	*ppHead = stop;
}
