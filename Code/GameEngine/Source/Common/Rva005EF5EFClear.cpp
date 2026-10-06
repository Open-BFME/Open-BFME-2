// ?Rva005EF5EFClear@@YAXPAURva005F0647@@0@Z @0x005EF5EF 24B.
// Range-clear wrapper over the 0x005F0C39 loop body: forwards (first, last) plus
// the address of an uninitialized bool local as third argument. The callee body
// only reads begin/end (extra arg ignored), so the rowed 2-arg Destroy source is
// byte-identical there; this TU declares the 3-arg shape the call site uses.
// Evidence: callers at 0x005EF8D5/0x005EF919/0x005F11EA/0x005F1217 pass container
// first/last; landing unblocks 0x005F11D0 0x005EF8BB 0x005F120F 0x005EF8FA.
// cl: /MD
struct Rva005F0647;
void __cdecl Rva005F0C39Destroy(Rva005F0647 *begin, Rva005F0647 *end, bool *exists);
void __cdecl Rva005EF5EFClear(Rva005F0647 *first, Rva005F0647 *last)
{
	bool exists;
	Rva005F0C39Destroy(first, last, &exists);
}
