// cl: /Os -Ireference/open-bfme-1/game/GameEngine/Source/Common
// ?Rva00217B07Each@@YAXPAUBfmeElemQR@@0PAX@Z @0x00217B07 23B
// Unlock thin __cdecl wrapper forwarding to rowed bfmeEachQR at 0x002178FD
// with a hard 0 third arg. Evidence: push push-0 push push plus call plus add
// esp 0x10; caller at 0x002188C8.
struct BfmeElemQR;

void __cdecl bfmeEachQR(BfmeElemQR *first, BfmeElemQR *last, int unused, void *extra);

void __cdecl Rva00217B07Each(BfmeElemQR *first, BfmeElemQR *last, void *extra)
{
	bfmeEachQR(first, last, 0, extra);
}
