// cl: /MD
// ?Rva00396260Copy@@YAPAVRva0039597C@@PAV1@00PAX@Z @0x00396260 29B evidence: chain-unlock wrapper over rowed 0x00395D45 array copy; caller 0x003997CD passes 4 with tmp addr; retail pushes 5 to callee (3 fwd plus local byte addr plus 0) with add esp 0x14; EBP frame; beside Rva0039627DCtor with same flags.
class Rva0039597C;

Rva0039597C *Rva00395D45CopyAux(Rva0039597C *first, Rva0039597C *last, Rva0039597C *dest, char *tmp, int zero);

Rva0039597C *Rva00396260Copy(Rva0039597C *first, Rva0039597C *last, Rva0039597C *dest, void *unused)
{
	char tmp;
	(void)unused;
	return Rva00395D45CopyAux(first, last, dest, &tmp, 0);
}
