// cl: /MD
// ?Rva005875DCFill@@YAXPAVRva00587375@@IPBV1@@Z @0x005875DC 27B
// 3-arg fill wrapper: forwards dest count src plus dummy byte to rowed 4-arg
// 0x00587422. Unblocks 0x00587DCD.
// Evidence: caller 0x00587E5C plus add esp 0x10 plus leave ret (cdecl).
class Rva00587375
{
public:
	void rva00587375(const Rva00587375 *src);
};
Rva00587375 *__cdecl Rva00587422Fill(Rva00587375 *dest, unsigned int count, const Rva00587375 *src, const void *unused);
void __cdecl Rva005875DCFill(Rva00587375 *dest, unsigned int count, const Rva00587375 *src)
{
	unsigned char dummy;
	Rva00587422Fill(dest, count, src, &dummy);
}
