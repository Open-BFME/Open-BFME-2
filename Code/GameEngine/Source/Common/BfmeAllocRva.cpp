// cl: /Od
// Alloc dispatcher twin of bfmeAllocPR (BfmeTwoHundredSeventySeven.cpp):
// blocks over 0x80 bytes go through the one-argument big alloc at 0x00023790
// (pinned as bfmeBigAllocPR), the rest through the one-argument small alloc
// at 0x00027A90 (rowed as the node-alloc _M_allocate, pinned here as
// bfmeSmallAllocPS), where the PR sibling reaches its own small alloc at
// 0x000279A0. The true instance name is not proven by these bytes, so this
// row rides under an Rva owner.

void *bfmeBigAllocPR(unsigned int bytes);

void *bfmeSmallAllocPS(unsigned int bytes);

// ?Rva00028D80Alloc@@YAPAXI@Z
void *Rva00028D80Alloc(unsigned int bytes)
{
	void *got;

	if (bytes > 0x80)
		got = bfmeBigAllocPR(bytes);
	else
		got = bfmeSmallAllocPS(bytes);

	return got;
}
