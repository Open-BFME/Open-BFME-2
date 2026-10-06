// cl: /MD
struct Rva00287B2AOut
{
	int m_00;
	unsigned char m_04;
};
extern "C" void __stdcall rva00286E33(Rva00287B2AOut *o, void *a);
// ?rva00287B2A@@YGXPAX0@Z
void __stdcall rva00287B2A(void *d, void *s)
{
	Rva00287B2AOut tmp;
	rva00286E33(&tmp, s);
	*(int *)d = tmp.m_00;
	*((unsigned char *)d + 4) = tmp.m_04;
}
