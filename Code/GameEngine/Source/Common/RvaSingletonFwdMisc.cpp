// flags: region default (reverse/retail_inventory/flag_regions.csv)
// Four singleton/global forwarder bodies (18B + 13B + 16B + 16B). Each pushes
// its operand from a stack slot (/O1), loads a global pointer into ecx and
// calls one thiscall method on it (thiscall is callee-cleanup, hence no
// caller cleanup after the call):
// 0x00224BC9 (member, 18B): g_AptWndMgr (0x00DFE4CC)->method(m_324).
//   The 0x00DFE4CC global is the peer-pinned Apt window manager.
// 0x0039ABFF (const member, 13B): g (0x00DFECC4)->rva00288CFA(this).
//   Wrapper class/signature follow the peer pin (ExperienceTracker const
//   bool member); the callee body ends ret 4, hence the stdcall spelling
//   alongside the peer's QAE pin at the same address.
// 0x003EFE72 (free __stdcall, 16B, ret 8): ((target *)a)->method(b).
// 0x00437E9C (free void(int), 16B): g (0x00E032FC)->method(a).
//   Signature/role follow the peer pin (cdecl forwarder, caller passes 1).
// Callee/global identities otherwise unproven; new names address-derived.
// One ledger row per body.

class Rva00224B7DTarget
{
public:
	bool method(int index);
};

extern Rva00224B7DTarget *g_pRva00224BC9;

class Rva00224BC9Owner
{
public:
	bool check();

private:
	unsigned char m_pad[0x324];
	int m_slot;
};

class Rva00288CFA
{
public:
	bool rva00288CFA(int value);
};

extern Rva00288CFA *g_pRva0039ABFF;

class ExperienceTracker
{
public:
	bool rva0039ABFF() const;
};

class Rva004FC3DCTarget
{
public:
	int method(int value);
};

class Rva0054CBEFTarget
{
public:
	void method(int value);
};

extern Rva0054CBEFTarget *g_pRva00437E9C;

bool Rva00224BC9Owner::check()
{
	return g_pRva00224BC9->method(m_slot);
}

bool ExperienceTracker::rva0039ABFF() const
{
	return g_pRva0039ABFF->rva00288CFA((int)this);
}

int __stdcall Rva003EFE72(int target, int value)
{
	return ((Rva004FC3DCTarget *)target)->method(value);
}

void Rva00437E9C(int value)
{
	g_pRva00437E9C->method(value);
}
