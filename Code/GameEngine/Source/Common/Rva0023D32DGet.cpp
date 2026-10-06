// cl: /MD
// ?Rva0023D32DGet@@YAEXZ, retail 0x0023D32D, 12 bytes.
// call Rva00437EDCGet; neg al; sbb al,al; inc al; ret.
// Evidence: unlock lane; callee row ?Rva00437EDCGet@@YA_NXZ; caller 0x0024096A tests al.
bool Rva00437EDCGet();
unsigned char Rva0023D32DGet()
{
	return !Rva00437EDCGet();
}
