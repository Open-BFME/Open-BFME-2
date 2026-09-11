// bfmeTwoBZB, retail 0x001B63A0, 28 bytes. Declared and called from
// Code/GameEngine/Source/Common/BfmeConv557.cpp (bfmeGoBZB) and from
// BfmeReleaseSetBZB.cpp (bfmeOneBZB, matched at 0x001B65F0), which already
// releases six owned pointers through it. Kept in its own TU so those
// callers cannot see (and inline) this body, matching retail's separate
// out-of-line function. Dispatches through a global host object's vtable
// slot 1 when present, otherwise falls back to a shared free() helper
// (tail-jumped at 0x00030830) — same shape as the other Bfme*BZB release
// helpers in this pass.
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
