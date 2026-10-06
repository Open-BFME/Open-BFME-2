// cl: /Oy- /MD
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

// ?rva004F83F2@@YGXHHHH@Z @0x004F83F2 25B.
void __stdcall rva004F83F2(int a, int b, int c, int d)
{
	rva004F7EE9(a, b, c, (void *)((char *)&c + 3));
}

void __cdecl rva004F8C16(int a, int b, int c, int d, int e, int f);

// ?rva004F904F@@YAXHHHH@Z @0x004F904F 40B.
void __cdecl rva004F904F(int a, int b, int c, int d)
{
	if (a == b)
		return;
	if (b == c)
		return;
	rva004F8C16(a, b, c, 0, 0, d);
}
