// cl: /MD
// ??0Rva00577936@@QAE@H@Z @0x005782F4 71B: ctor stores vtable g_00C6E9E8 then new Rva00577F77(this int) via rowed ??0Rva00577F77@@QAE@PAXH@Z and rowed ??2@YAPAXI@Z. Evidence: 0x50 alloc matches sizeof Rva00577F77 plus caller 0x005F8671 base-call then own vtable plus dtor ??1Rva00577936@@UAE@XZ at 0x00577936.
class Rva00577F77
{
public:
	virtual void d0();
	Rva00577F77(void *p, int v);
private:
	char m_pad[0x4C];
};

class Rva00577936
{
public:
	virtual ~Rva00577936();
	virtual void rva00577966();
	Rva00577936(int v);
private:
	Rva00577F77 *m_04;
};

Rva00577936::Rva00577936(int v)
{
	m_04 = new Rva00577F77(this, v);
}
