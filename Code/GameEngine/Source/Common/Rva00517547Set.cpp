// cl: /EHsc /MD
// ?rva00517547@Rva00517547@@QAEPAU1@URva0051732A@@@Z @0x00517547 59B
// EH setter: forward the by-value holder at [ebp+8] as const ref to rowed
// setter 0x005173CB (new wrapper plus AddRef), then Release the input
// pointer via rowed fastcall 0x0007DEEF, return this. Caller 0x005178E8.
struct TargetRef00217D4C
{
	void *m_vtbl;
	int references;
};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

struct Rva0051732A
{
	TargetRef00217D4C *m_ptr;
	~Rva0051732A() { if (m_ptr) ReleaseTreeHintRef00217D4C(m_ptr); }
};

struct Rva00517345
{
	void *m_vtbl;
	int m_04;
	TargetRef00217D4C *m_08;
	Rva00517345(const Rva0051732A &other);
};

struct Rva005173CB
{
	Rva00517345 *m_ptr;
	Rva005173CB *rva005173CB(const Rva0051732A &arg);
};

struct Rva00517547 : Rva005173CB
{
	Rva00517547 *rva00517547(Rva0051732A arg);
};

Rva00517547 *Rva00517547::rva00517547(Rva0051732A arg)
{
	rva005173CB(arg);
	return this;
}
