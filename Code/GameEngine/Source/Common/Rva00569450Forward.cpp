// cl: /O1 /MD
//
// ?rva00569450@@YAHPAX00@Z @0x00569450 27B.
// __cdecl forwarder: bool out-param at [ebp-1] plus the three arguments go
// to the pinned 4-arg __cdecl 0x00569109, whose return passes through.
// Honest address-derived names; return-bool-vs-int unproven, int-sized.
int __cdecl rva00569109(void *a, void *b, void *c, bool *out);

int __cdecl rva00569450(void *a, void *b, void *c)
{
	bool out;
	return rva00569109(a, b, c, &out);
}
