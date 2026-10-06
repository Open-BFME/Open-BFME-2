// cl: /EHsc /MD
// ?Rva0037BA97Init@@YA?AUTriple12@@PBUPair8@@H@Z @0x0037BA97 43B
// Value-returning (struct-return) Triple12 builder: loads the two ints of the
// Pair8 source, stores them plus the third argument into a stack temporary and
// copies it through the hidden return pointer. Evidence: exact 43-byte match;
// the target's `mov eax,[ebp+8]` / `mov edi,eax` pair is the hidden
// struct-return pointer, which a void dest-pointer signature cannot produce
// (that shape is 41B and pushes esi/edi before the tmp.b store). The banked
// void `...YAXPAUTriple12...` body was the 41B near miss. Neighbour
// Rva0037BA48Get (0x0037BA48) uses the same /O1 /EHsc struct-return recipe.
struct Pair8
{
	int a;
	int b;
};

struct Triple12
{
	int a;
	int b;
	int c;
};

Triple12 __cdecl Rva0037BA97Init(const Pair8 *src, int c)
{
	Triple12 tmp;
	tmp.a = src->a;
	tmp.b = src->b;
	tmp.c = c;
	return tmp;
}
