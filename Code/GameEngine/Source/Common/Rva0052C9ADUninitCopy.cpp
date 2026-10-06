// cl: /DNDEBUG /MD
//
// ?Rva0052C9ADGet@@YAPAXPAX00@Z retail 0x0052C9AD 38B. Unlock lane:
// uninitialized copy over 0x10-stride opaque elements via Construct helper
// at 0x0052C404 (45B placement copy calling pair copy 0x0052BEC9; rowed
// under 0-arg dup name, callable 2-arg honest pin in this TU); push-esi/edi
// loop with late cmp, returns final dest. Callers at
// 0x0052CE60/0x0056648C/0x005664D7. Landing unblocks 0x0052CE20/93 and
// 0x0056644E/180. Prev/next are Pod40 bodies. Owner unknown so honest
// address-derived names; element is size-only (16 bytes).
struct Rva0052C9ADElem {
	char m_body[16];
};

void __cdecl Rva0052C404Construct(void *d, const void *s);
void *__cdecl Rva0052C9ADGet(void *first, void *last, void *result)
{
	char *cur = (char *)result;
	for (; first != last; first = (char *)first + 16, cur += 16)
		Rva0052C404Construct(cur, first);
	return cur;
}
