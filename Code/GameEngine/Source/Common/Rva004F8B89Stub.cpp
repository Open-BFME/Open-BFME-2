// cl: /O1 /Oy- /MD
//
// ?rva004F8B89@@YGXHHH@Z @0x004F8B89 25B.
// Tiny stdcall repacker: forward three ints plus the address of the third
// arg's top byte into the pinned stdcall 0x4F7EE9. Retail keeps an ebp
// frame, so /Oy- (Rva0025BF8CHeroRemover precedent); the sibling forwarders
// stay frameless under plain /O1 in Rva004F8B89Fwd.cpp.

void __stdcall rva004F7EE9(int a, int b, int c, void *d);

// ?rva004F8B89@@YGXHHH@Z
void __stdcall rva004F8B89(int a, int b, int c)
{
	rva004F7EE9(a, b, c, (void *)((char *)&c + 3));
}
