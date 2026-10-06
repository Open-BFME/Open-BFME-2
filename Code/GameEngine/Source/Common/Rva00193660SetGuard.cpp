// cl: /Ob0
//
// ?Rva0032ACEASet@@YAXPAVRva00193660@@PBURva00193660Src@@@Z @0x0032ACEA 18B
// Null-guarded Rva00193660::set wrapper (free function).
// Evidence: calls rowed ?set@Rva00193660@@QAEAAV1@PBURva00193660Src@@@Z at 0x0032A304;
// layout is Rva00193660Set.cpp (16B struct with refcounted tail); callers are
// uninitialized-copy loops at 0x0032AD58/0x0032CAA1/0x0032D2EA that stride 0x10.
// /O1 for the push-mem shape (vs mov+push under /O2); /Ob0 keeps set out-of-line.

struct Rva00193660Src
{
	unsigned short a;
	unsigned short b;
	unsigned short c;
	unsigned short d;
	int e;
	unsigned short *ref;
};

class Rva00193660
{
	unsigned short a;
	unsigned short b;
	unsigned short c;
	unsigned short d;
	int e;
	unsigned short *ref;

public:
	Rva00193660 &set(const Rva00193660Src *p);
};

void __cdecl Rva0032ACEASet(Rva00193660 *dest, const Rva00193660Src *src)
{
	if (dest)
		dest->set(src);
}

Rva00193660 *__cdecl Rva0032AD58Fill(Rva00193660 *first, unsigned count, const Rva00193660Src &value)
{
	Rva00193660 *cur = first;
	for (; count > 0; --count, ++cur)
		Rva0032ACEASet(cur, &value);
	return cur;
}
