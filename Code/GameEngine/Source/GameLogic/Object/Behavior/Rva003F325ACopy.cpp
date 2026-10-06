// cl: /Oy- /DNDEBUG /MD
// ?Rva003F325ACopy@@YAPAVRva003F2A11@@PAV1@00@Z @0x003F325A 29B
// Forwards 3 ranges to rowed 0x003F2A3E array-copy with dummy tag (push 0 +
// [ebp-1] dead-slot+3) via 5-arg cast, same pattern as Rva003F3159Finish 4-arg
// copy. Evidence: retail 5 pushes + add esp,0x14 calling rowed copy; ebp frame
// via /Oy-.
class Rva003F2A11;
Rva003F2A11 *Rva003F2A3E(Rva003F2A11 *, Rva003F2A11 *, Rva003F2A11 *);
typedef Rva003F2A11 *(__cdecl *Rva003F2A3E5Fn)(Rva003F2A11 *, Rva003F2A11 *, Rva003F2A11 *, void *, int);
Rva003F2A11 *Rva003F325ACopy(Rva003F2A11 *a, Rva003F2A11 *b, Rva003F2A11 *c)
{
	int dummy;
	return ((Rva003F2A3E5Fn)&Rva003F2A3E)(a, b, c, (void *)((char *)&dummy + 3), 0);
}
