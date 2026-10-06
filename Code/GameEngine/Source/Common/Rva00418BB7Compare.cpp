// cl: /MD
// RVA 0x00418BB7 44B free less-compare over two dwords at +4 then +0.
// Called by the 0x00418BFB search loop plus 0x00418C33 and 0x00418D3C.
struct Rva00418BB7Key {
	int lo;
	int hi;
};
bool __stdcall Rva00418BB7Less(const void *a, const void *b)
{
	const Rva00418BB7Key *ka = (const Rva00418BB7Key *)a;
	const Rva00418BB7Key *kb = (const Rva00418BB7Key *)b;
	if (ka->hi < kb->hi)
		return true;
	if (ka->hi > kb->hi)
		return false;
	return ka->lo < kb->lo;
}
