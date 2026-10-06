// cl: /DNDEBUG /MD
//
// ?Rva0056574BFill@@YAPAXPAXIPBX@Z @0x0056574B (37B).
// __uninitialized_fill_n over 0x10-stride pair elements. Evidence: loop
// calls dup Construct 0x0052C404 stride 0x10 caller 0x005664B9 same shape
// as rowed 0x0056561E. Owner unknown so honest address name. Callee binds
// through honest pin Rva0052C404Construct at 0x0052C404.
void __cdecl Rva0052C404Construct(void *d, const void *s);

void *__cdecl Rva0056574BFill(void *first, unsigned int n, const void *x)
{
	char *cur = (char *)first;
	for (; n > 0; --n, cur += 16)
		Rva0052C404Construct(cur, x);
	return cur;
}
