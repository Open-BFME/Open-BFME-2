// cl: /MD
// ?Rva00587422Fill@@YAPAVRva00587375@@PAV1@IPBV1@PBX@Z @0x00587422 37B
// Array fill_n 0x3C structs: dest+=0x3C count times via rowed 0x00587410,
// returns end. 4th void* unused (callers push byte addresses, callee ignores).
// Unblocks 0x005875DC 0x00587C40.
// Evidence: callers 0x005875ED 0x00587CAE plus add esi 0x3C plus mov eax esi.
class Rva00587375
{
public:
	void rva00587375(const Rva00587375 *src);
};
void __cdecl Rva00587410Copy(Rva00587375 *dest, const Rva00587375 *src);
Rva00587375 *__cdecl Rva00587422Fill(Rva00587375 *dest, unsigned int count, const Rva00587375 *src, const void *unused)
{
	(void)unused;
	Rva00587375 *p = dest;
	while (count > 0) {
		Rva00587410Copy(p, src);
		p = (Rva00587375 *)((char *)p + 0x3c);
		--count;
	}
	return p;
}
