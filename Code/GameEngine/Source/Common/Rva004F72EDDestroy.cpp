// cl: /MD
// ?Rva004F72EDDestroy@@YAXPAX0@Z retail 0x004F72ED 27B placeholder
// Evidence: LINK BONUS via 0x005F97BC; caller 0x005F97CA; callee rowed rva005F8FCC 0x005F8FCC; prev 0x004F711C next 0x004F76EA; destroys range step 4 via flags 0
class Rva005F8FCC
{
public:
	void *rva005F8FCC(unsigned int flags);
};

void __cdecl Rva004F72EDDestroy(void *begin, void *end)
{
	for (char *p = (char *)begin; p != end; p += 4)
		((Rva005F8FCC *)p)->rva005F8FCC(0);
}
