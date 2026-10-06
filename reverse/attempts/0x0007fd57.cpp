// ?rva0007FD57@Rva0007FD57Host@@QAEXPAPAXH@Z
// partial score=0.85 date=2026-10-06
// cl: /O1 /DNDEBUG /MD /Oy-
class Rva0007FD57Host
{
public:
	void rva0007FD57(void **out, int x);
	void rva0007F0FB(int a, int b);
	unsigned char m_pad[0xFC];
	void *m_ptr;
};

struct Rva0007FD57Ref
{
	int m_0;
	int m_ref;
};

void Rva0007FD57Host::rva0007FD57(void **out, int x)
{
	int zero = 0;
	if (zero != 0)
		rva0007F0FB(0, 0);
	if (x != 0)
		rva0007F0FB(x, 1);
	Rva0007FD57Ref *p = (Rva0007FD57Ref *)m_ptr;
	*out = p;
	if (p != 0)
		p->m_ref++;
}
