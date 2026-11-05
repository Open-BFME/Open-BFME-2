// cl: /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ??1HordeMeleeAmoeba@@UAE@XZ, retail 0x00587F69 59B.
// (Renamed from Rva00587F69: same class.) HordeMeleeAmoeba (ctor unit Rva00587D9CCtor.cpp) installs vtable 0x00C6FF38, whose slot 0 is the deleting dtor 0x00587F4D that calls this body.
// Dtor: derived from Rva005D6FCC (vptr+held at +0, vtbl 0x00C75C38) with char* at +8
// freed via rowed _free 0x00030830 then base dtor (ICF twin of rowed apply 0x005D6FDE).
// Caller 0x00587F4D 28B is ??_G (push esi call test flag call delete) which becomes ready.
// Built with /EHs, not /EHsc: retail keeps an EH state around the extern "C"
// free call, so the CRT declaration must be allowed to throw.
#include <stdlib.h>

class Rva005D6FCC
{
public:
	Rva005D6FCC(void *held);
	virtual ~Rva005D6FCC();
	void *m_held;
};

class __declspec(novtable) HordeMeleeAmoeba : public Rva005D6FCC
{
public:
	virtual ~HordeMeleeAmoeba();
private:
	char *m_08;
};

HordeMeleeAmoeba::~HordeMeleeAmoeba()
{
	if (m_08)
		free(m_08);
}

// ??1HordeMeleeSwarm@@UAE@XZ @0x00584502 59B: byte-identical to ~HordeMeleeAmoeba above except its
// own EH handler (formerly matched as the alias dup_00584502). Rva005843DACtor.cpp holds the
// full view (Rva005D6FCC base, vector<Rva00583CE0Elem> at +8); this destructor needs only the
// +8 storage pointer the vector frees, so the view here keeps that layout.
class __declspec(novtable) HordeMeleeSwarm : public Rva005D6FCC
{
public:
	virtual ~HordeMeleeSwarm();
private:
	char *m_08;
};

HordeMeleeSwarm::~HordeMeleeSwarm()
{
	if (m_08)
		free(m_08);
}

// ??1Rva005838B5@@UAE@XZ @0x005838F8 59B: byte-identical to ~HordeMeleeAmoeba above
// except its own EH handler (formerly the alias dup_005838f8). The 0x005838B5 ctor
// (Rva005838B5Ctor.cpp) installs vtable 0x00C6FC30, whose slot 0 is the deleting
// dtor 0x005838DC that calls this body; same Rva005D6FCC base and +8 storage.
class __declspec(novtable) Rva005838B5 : public Rva005D6FCC
{
public:
	virtual ~Rva005838B5();
private:
	char *m_08;
};

Rva005838B5::~Rva005838B5()
{
	if (m_08)
		free(m_08);
}
