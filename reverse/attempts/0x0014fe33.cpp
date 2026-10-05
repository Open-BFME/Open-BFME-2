// ?rva0014FE33@Rva00153664@@QAEXHPBDPAVRva0015354E@@@Z
// partial score=0.92 date=2026-10-05
// cl: /O1
// ?rva0014FE33@Rva00153664@@QAEXHPBDPAVRva0015354E@@@Z @0x0014FE33 133B
// Evidence: chain via rowed 0x00153664 0x001530E9 0x00579E47 0x00153ACA; Parse plus Color Direction plus delegate tail from codes 0x0014D66F 0x0014D722.
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
	void rva00153664(int arg1, const char *arg2, Rva0015354E *arg3);
	void rva0014FE33(int a, const char *b, Rva0015354E *c);
};
void Rva00153664::rva0014FE33(int a, const char *b, Rva0015354E *c)
{
	this->rva00153664(a, b, c);
	if (a == 0)
		return;
	Rva001530E9Parts parts;
	Rva001530E9Parse((const char *)a, &parts);
	void *code;
	if (_strcmpi(parts.m_name, "Color") == 0)
		code = (void *)0x54D66F;
	else
	{
		if (_strcmpi(parts.m_name, "Direction") != 0)
			return;
		code = (void *)0x54D722;
	}
	DelegateDesc desc;
	desc.m_method = code;
	desc.m_object = this;
	Rva00579E47 tmp;
	tmp.rva00579E47(&desc);
	c->rva00153ACA(tmp, b);
}
