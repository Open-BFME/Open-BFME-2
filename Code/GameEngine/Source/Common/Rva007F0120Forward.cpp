// cl: /DNDEBUG /MD
//
// ?Rva007F0120@@YAXPAX0@Z, retail 0x0065D000, 5 bytes: a single tail jump to
// the rowed ?Rva007F00B0@@YAXPAX0@Z (0x0065CF90) with the same two
// arguments. Address-derived names (BFME1 addresses) as the pins and the
// rowed target carry them; identity not witnessed.

void Rva007F00B0(void *first, void *second);

void Rva007F0120(void *first, void *second)
{
	Rva007F00B0(first, second);
}
