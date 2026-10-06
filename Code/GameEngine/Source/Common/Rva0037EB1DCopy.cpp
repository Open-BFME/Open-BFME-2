// cl: /MD /Oi
// ?rva0037EB1D@Rva0037EB1D@@QAEXPAX@Z @0x0037EB1D 31B. Chain of rowed 0x0037EACC
// copy-to plus dword +0xAC to dest +0xC0. Evidence: call 0x0037EACC rowed in
// Rva0037EACCCopy.cpp, ret 4, caller 0x0040F167, neighbours Rva0037EACC copy
// and VTableInstalls.
struct Rva0037EACC
{
	void rva0037EACC(void *dest);
};
class Rva0037EB1D
{
	char m_pad00[0xAC];
	int m_ac;
public:
	void rva0037EB1D(void *dest);
};
void Rva0037EB1D::rva0037EB1D(void *destPtr)
{
	((Rva0037EACC *)this)->rva0037EACC(destPtr);
	*(int *)((char *)destPtr + 0xC0) = *(int *)((char *)this + 0xAC);
}
