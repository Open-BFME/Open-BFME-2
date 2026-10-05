// ?rva0014FC48@Rva00153664@@QAEXHPBDPAVRva0015354E@@@Z
// partial score=0.92 date=2026-10-05
// cl: /O1
// ?rva0014FC48@Rva00153664@@QAEXHPBDPAVRva0015354E@@@Z @0x0014FC48 126B
// Evidence: chain via rowed 0x001530E9 0x00579E47 0x00153ACA; Parse plus Inverse pair plus delegate tail from codes 0x0014D440 0x0014D474 0x0014D4CB; null selects first code.
class Rva0015354E;
struct TreeHintRef00217D4C
{
	void *m_ptr;
};
struct DelegateDesc
{
	void *m_object;
	void *m_method;
};
class Rva00579E47 : public TreeHintRef00217D4C
{
public:
	Rva00579E47 &rva00579E47(const DelegateDesc *d);
};
struct Rva001530E9Parts
{
	char m_name[64];
	bool m_hasStar;
	bool m_hasBracket;
	char m_pad[2];
	int m_index;
	const char *m_ext;
};
void __cdecl Rva001530E9Parse(const char *src, void *volatile dst);
extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *a, const char *b);
class Rva0015354E
{
public:
	void rva00153ACA(TreeHintRef00217D4C arg, const char *name);
};
class Rva00153664
{
public:
	void rva0014FC48(int a, const char *b, Rva0015354E *c);
};
void Rva00153664::rva0014FC48(int a, const char *b, Rva0015354E *c)
{
	void *code;
	if (a == 0)
		code = (void *)0x54D440;
	else
	{
		Rva001530E9Parts parts;
		Rva001530E9Parse((const char *)a, &parts);
		if (_strcmpi(parts.m_name, "Inverse") == 0)
			code = (void *)0x54D474;
		else
		{
			if (_strcmpi(parts.m_name, "InverseTranspose") != 0)
				return;
			code = (void *)0x54D4CB;
		}
	}
	DelegateDesc desc;
	desc.m_method = code;
	desc.m_object = this;
	Rva00579E47 tmp;
	tmp.rva00579E47(&desc);
	c->rva00153ACA(tmp, b);
}
