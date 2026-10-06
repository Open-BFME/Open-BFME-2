// cl: /DNDEBUG /MD
//
// ?bfmeFreeOneJT@@YAXPAX@Z, retail 0x001B6410, 5 bytes: a single tail jump to
// the rowed bfmeTwoBZB (0x001B63A0) with the same argument. game.dat is not
// incrementally linked, so this is a real forwarding function, not an ILT
// stub. Two units (BfmeConv2079/2080, bfmeAllocJX's callers) call it by this
// pinned name.

void bfmeTwoBZB(void *block);

void bfmeFreeOneJT(void *block)
{
	bfmeTwoBZB(block);
}
