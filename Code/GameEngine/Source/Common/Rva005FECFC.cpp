// cl: /DNDEBUG /MD
// ?rva005FECFCInit@@YIXPAVRva005FECFC@@HH@Z @0x005FECFC 35B evidence:
// fastcall init (this, fwd-dead-in-edx, arg): m_14 = timeGetTime() plus
// arg times 1000; then pinned thiscall-0
// ?rva005FEC0C@Rva005FA854Inner@@QAEXXZ @0x005FEC0C on this (reused pin,
// identity unproven); ret 4. TU-local view only.
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);

class Rva005FA854Inner
{
public:
	void rva005FEC0C();
};

class Rva005FECFC
{
public:
	char m_pad[0x14];
	unsigned long m_14;
};

void __fastcall rva005FECFCInit(Rva005FECFC *o, int fwd, int arg)
{
	o->m_14 = timeGetTime() + (unsigned long)(arg * 1000);
	((Rva005FA854Inner *)o)->rva005FEC0C();
}
