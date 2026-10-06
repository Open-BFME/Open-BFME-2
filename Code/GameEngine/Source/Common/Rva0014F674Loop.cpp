// cl: /DNDEBUG /MD
//
// ?rva0014F674@@YAPAXPAXI0H@Z @0x0014F674 37B cdecl loop.
// Retail: esi=a1, edi=a3(count); if (count==0) skip; do {
// helper(a1,a3) via pinned 0x0014F647; a1+=0x4C; } while (--count!=0);
// return a1. 4 args (4th unused), caller cleans. No this, no pins in body
// besides helper (pinned). Names opaque.
void __cdecl rva0014F647(void *a, void *b);

void *__cdecl rva0014F674(void *p, unsigned int count, void *ha, int unused)
{
	(void)unused;
	char *s = (char *)p;
	unsigned int n = count;
	if (n > 0) {
		do {
			rva0014F647(s, ha);
			s += 0x4C;
		} while (--n != 0);
	}
	return s;
}

// ?rva0014FA47@@YAPAXPAXI0@Z @0x0014FA47 27B forward.
// Retail: char tmp at [ebp-1]; return rva0014F674(a,b,c,&tmp)
// (4th dead in callee); caller cleans 0x10. Calls rowed 0x0014F674.
void *__cdecl rva0014FA47(void *a, unsigned int b, void *c)
{
	char tmp;
	return rva0014F674(a, b, c, (int)&tmp);
}
