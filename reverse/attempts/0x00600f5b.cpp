// ?Rva00600F5BWrap@@YAPAVRva00600BFB@@PAV1@PAHH@Z
// partial score=0.92 date=2026-10-06
// cl: /O1 /Oy- /MD /EHs
// ?Rva00600F5BWrap@@YAHPAV1@PAHH@Z @0x00600F5B 27B. wrapper returning o around fastcall Init with dead fwd.
// Evidence: caller 0x006014C0, callee rowed 0x00600BFB, frame from /Oy-.
class Rva00600BFB
{
public:
	int m_00;
};
Rva00600BFB *__fastcall rva00600BFBInit(Rva00600BFB *o, int fwd, int *a, int b);

Rva00600BFB *Rva00600F5BWrap(Rva00600BFB *o, int *a, int b)
{
	register int fwd;
	rva00600BFBInit(o, fwd, a, b);
	return o;
}
