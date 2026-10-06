// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?Rva0017351CInsert@@YAXPAUBfmeAssignRecord32@@U1@P6A_NABU1@2@Z@Z @0x0017351C 86B insertion helper for vector<BfmeAssignRecord32>.
// Retail backward walk with 0x20 stride; predicate via funcptr at +0x2c (caller cleans __cdecl).
// Copies prev to hole while comp(value prev) true then places value; value by value needs EH dtor.
// Evidence: callers at 0x00173841 (46B aux loop with copy 0x00173731 plus add esp 0x28) and 0x00173B5E (118B).
// Callees: assignment pinned at 0x00173499 and dtor rowed at 0x0017330A; copy rowed at 0x00173731 for caller temps.
// Layout 32B proven by rowed copy/dtor plus 0x20 stride; honest Rva name (free function via caller pushes).
struct Rva00087A93 { void *m_data; };
struct BfmeAssignRecord32 {
	Rva00087A93 s;
	int x;
	Rva00087A93 arr[6];
	~BfmeAssignRecord32();
	BfmeAssignRecord32 &operator=(const BfmeAssignRecord32 &other);
};
typedef bool (__cdecl *BfmePred)(const BfmeAssignRecord32 &, const BfmeAssignRecord32 &);
void __cdecl Rva0017351CInsert(BfmeAssignRecord32 *last, BfmeAssignRecord32 value, BfmePred comp)
{
	BfmeAssignRecord32 *prev = last - 1;
	while (comp(value, *prev)) {
		*last = *prev;
		last = prev;
		--prev;
	}
	*last = value;
}
