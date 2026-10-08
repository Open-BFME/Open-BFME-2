// cl: /DNDEBUG /MD
//
// ?rva002D34FE@Rva002D34FE@@QAEXH@Z @0x002D34FE 46B: guarded two-stage helper
// chain. Retail bails when the pinned thiscall check
// ?rva00401E2F@Rva002D34FE@@QAE_NXZ at 0x00401E2F is true; otherwise it calls
// the pinned ?rva0071BE3C@Rva002D34FEHelper@@QAEHPAX@Z at 0x0071BE3C with
// this=dword_0xE01CFC and arg=caller-this, bails on zero return, and calls
// the pinned ?rva00805DBC@Rva002D34FEHelper@@QAEXPAXH@Z at 0x00805DBC with
// this=dword_0xE01CFC and args (prev-return, 0). The single stack arg is dead
// (frameless this-use only) but required for the ret-4 shape. The helper
// class is an unproven call-shape view; the dword at 0x00E01CFC is read as a
// pointer per the two mov-ecx sites. Honest address-derived names.

class Rva002D34FEHelper
{
public:
	int rva0071BE3C(void *arg);
	void rva00805DBC(int a, void *b);
};

class Rva002D34FE
{
public:
	bool rva00401E2F();
	void rva002D34FE(int unused);
};

// N.B. pointee type at 0x00E01CFC is unproven; viewed as helper for the
// observed thiscall shape only.
extern class ControlBar *TheControlBar;

// ?rva002D34FE@Rva002D34FE@@QAEXH@Z
void Rva002D34FE::rva002D34FE(int)
{
	if (rva00401E2F())
		return;
	int r = (*(Rva002D34FEHelper **)&TheControlBar)->rva0071BE3C(this);
	if (!r)
		return;
	(*(Rva002D34FEHelper **)&TheControlBar)->rva00805DBC(0, (void *)r);
}
