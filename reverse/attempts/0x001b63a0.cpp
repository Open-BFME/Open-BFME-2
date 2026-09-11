// ?bfmeTwoBZB@@YAXPAX@Z
// partial score=0.93 date=2026-09-10
// ?bfmeTwoBZB@@YAXPAX@Z
// partial score=0.93 date=2026-09-10
// cl: /O1 /MD
//
// bfmeTwoBZB, retail 0x001B63A0, 28 bytes. Dedicated TU so
// BfmeReleaseSetBZB.cpp cannot see this body. Host global and tail-jmp
// to free already match. Near-miss: retail loads what into edx then
// push edx; /O1 pushes [esp+8] and loads the vtable first.

class BfmeTwoBZBHost
{
public:
	virtual void unused();
	virtual void release(void *what, int flag);
};

#define TheBfmeTwoBZBHost (*(BfmeTwoBZBHost **)0x00DFDA54)

extern "C" void __cdecl free(void *block);

void bfmeTwoBZB(void *what)
{
	BfmeTwoBZBHost *host = TheBfmeTwoBZBHost;
	if (host)
		host->release(what, 0);
	else
		free(what);
}
