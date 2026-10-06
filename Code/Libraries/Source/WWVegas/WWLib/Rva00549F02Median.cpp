// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?Rva00549F02Median@@YAABQAUFoo00549DCB@@ABQAU1@00URva00549DCB@@@Z, RVA 0x00549F02, 101B
// Median-of-three via Rva00549DCB comparator (5 calls). Evidence: chain lane
// after 0x00549DCB; 12-byte refs (Foo* const&) plus empty comp at +0x14 whose
// address is leaed into ecx for each thiscall; control flow returns b/c/a and
// a/c/b matching retail branches.
struct Bar00549DCB {
	char pad[0x5da];
	unsigned short key;
};
struct Foo00549DCB {
	int unk0;
	Bar00549DCB *bar;
};
struct Rva00549DCB {
	bool rva00549DCB(Foo00549DCB * const &a, Foo00549DCB * const &b) const;
};
Foo00549DCB * const &Rva00549F02Median(Foo00549DCB * const &a, Foo00549DCB * const &b, Foo00549DCB * const &c, Rva00549DCB comp)
{
	if (comp.rva00549DCB(a, b)) {
		if (comp.rva00549DCB(b, c))
			return b;
		else if (comp.rva00549DCB(a, c))
			return c;
		else
			return a;
	} else {
		if (comp.rva00549DCB(a, c))
			return a;
		else if (comp.rva00549DCB(b, c))
			return c;
		else
			return b;
	}
}
