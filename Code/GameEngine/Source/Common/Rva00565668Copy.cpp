// cl: /DNDEBUG /MD
//
// ?Rva00565668Copy@@YAPAVRva00564B1A@@PAV1@00PAD@Z @0x00565668 (29B).
// 4-arg cdecl wrapper over rowed 3-arg Copy 0x00564CD4. Forwards first/last/dest
// plus &tmp/0 as 4th/5th pushes; cdecl callee ignores the extras. Evidence: call
// at 0x0056567B to rowed Copy; caller 0x00565898 passes 4 with lea ebp+0xb as char*;
// neighbours FillN 0x00565643/0x00565685 share flags. Cast keeps the relocation on
// the row name so the file links; no second pin at the rowed address.
class Rva00564B1A
{
	char m_pad[0xc];
};

Rva00564B1A *Rva00564CD4Copy(Rva00564B1A *first, Rva00564B1A *last, Rva00564B1A *dest);
typedef Rva00564B1A *(__cdecl *Rva00565668Copy5)(Rva00564B1A *, Rva00564B1A *, Rva00564B1A *, char *, int);

Rva00564B1A *Rva00565668Copy(Rva00564B1A *first, Rva00564B1A *last, Rva00564B1A *dest, char *extra)
{
	char tmp;
	return ((Rva00565668Copy5)Rva00564CD4Copy)(first, last, dest, &tmp, 0);
}
