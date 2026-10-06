// cl: /MD
// ?Rva00587410Copy@@YAXPAVRva00587375@@PBV1@@Z @0x00587410 18B
// Null-checked single copy: if dest==0 return else dest->rva00587375(src).
// Calls rowed 0x00587375. Unblocks 0x00587422 0x00587599 0x00587C40.
// Evidence: callers 0x00587435 0x005875A7 0x00587C96 plus ret (cdecl).
class Rva00587375
{
public:
	void rva00587375(const Rva00587375 *src);
};
void __cdecl Rva00587410Copy(Rva00587375 *dest, const Rva00587375 *src)
{
	if (dest == 0)
		return;
	dest->rva00587375(src);
}
