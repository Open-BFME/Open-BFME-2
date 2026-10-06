// flags: region default (reverse/retail_inventory/flag_regions.csv)
// The addresses below have 37B Ghidra FUN boundaries and share one target
// shape: a six-argument cdecl callback checks its context pointer, returns 1
// for null, or forwards the first five arguments through that context.
// GHTTP's post callback has the same five-value-plus-user-data contract, but
// the callback names and owning classes are not established by this body.

class Rva005571FC
{
public:
	int rva005571FC(int a1, int a2, int a3, int a4, int a5);
};

class Rva005570AB
{
public:
	int rva005570AB(int a1, int a2, int a3, int a4, int a5);
};

class Rva005573FA
{
public:
	int rva005573FA(int a1, int a2, int a3, int a4, int a5);
};

class Rva00557304
{
public:
	int rva00557304(int a1, int a2, int a3, int a4, int a5);
};

// ?rva00557902@@YAHHHHHHPAX@Z @0x00557902 37B. The sixth stack argument is
// passed as this to address-derived callee 0x005571FC; both identities remain
// unresolved.
int __cdecl rva00557902(int a1, int a2, int a3, int a4, int a5, void *context)
{
	if (!context)
		return 1;
	return ((Rva005571FC *)context)->rva005571FC(a1, a2, a3, a4, a5);
}

// ?rva00557927@@YAHHHHHHPAX@Z @0x00557927 37B. The sixth stack argument is
// passed as this to address-derived callee 0x005570AB; both identities remain
// unresolved.
int __cdecl rva00557927(int a1, int a2, int a3, int a4, int a5, void *context)
{
	if (!context)
		return 1;
	return ((Rva005570AB *)context)->rva005570AB(a1, a2, a3, a4, a5);
}

// ?rva0055794C@@YAHHHHHHPAX@Z @0x0055794C 37B. The sixth stack argument is
// passed as this to address-derived callee 0x005573FA; both identities remain
// unresolved.
int __cdecl rva0055794C(int a1, int a2, int a3, int a4, int a5, void *context)
{
	if (!context)
		return 1;
	return ((Rva005573FA *)context)->rva005573FA(a1, a2, a3, a4, a5);
}

// ?rva00557971@@YAHHHHHHPAX@Z @0x00557971 37B. The sixth stack argument is
// passed as this to address-derived callee 0x00557304; both identities remain
// unresolved.
int __cdecl rva00557971(int a1, int a2, int a3, int a4, int a5, void *context)
{
	if (!context)
		return 1;
	return ((Rva00557304 *)context)->rva00557304(a1, a2, a3, a4, a5);
}
