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
class AsciiString;

class Rva000427195
{
public:
	int rva00223429(const AsciiString *key);
};

class Rva00062908Host
{
public:
	bool rva00222481(int index);
};

class Rva0022494F
{
public:
	void rva0022494F();
	char m_a[4];
	char m_b[4];
	int m_8;
	int m_c;
	char m_table[0x14];
	unsigned char m_24;
};

class Rva00224B7DTarget
{
private:
	char m_pad_00_5C[0x5C];
	Rva000427195 m_map_view;
	char m_pad_5D_CC[0x6F];
	Rva0022494F m_entries[14];

public:
	bool method(int index);
};

// ?method@Rva00224B7DTarget@@QAE_NH@Z @ 0x00224B7D (76B):
// The direct wrapper 0x00224BC9 supplies the Apt global and a slot index.
// Target bounds the index to 14; uses records at this+0xCC with stride 0x28;
// rejects the +0x0C sentinel -1; on +0x24 bit 1 calls 0x00222481; then erases
// the record's AsciiString through the +0x5C map view and resets the record via
// 0x0022494F. Owner and slot meaning remain address-derived.
bool Rva00224B7DTarget::method(int index)
{
	if ((unsigned int)index >= 14)
		return false;
	Rva0022494F &entry = m_entries[index];
	if (entry.m_c == -1)
		return false;
	if ((entry.m_24 & 2) != 0)
		((Rva00062908Host *)this)->rva00222481(index);
	m_map_view.rva00223429((const AsciiString *)&entry.m_a);
	entry.rva0022494F();
	return true;
}

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

class ExperienceLevelSystem;
extern ExperienceLevelSystem *TheExperienceLevelSystem;

class ExperienceTracker
{
public:
	bool rva0039ABFF() const;
};

struct Rva003F1BD3TemplateView;
class LivingWorldBuildPlot
{
public:
	void ConstructBuildingImmediately(const Rva003F1BD3TemplateView *value);
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
	return reinterpret_cast<Rva00288CFA *>(TheExperienceLevelSystem)->rva00288CFA((int)this);
}

void __stdcall Rva003EFE72(int target, int value)
{
	((LivingWorldBuildPlot *)target)->ConstructBuildingImmediately(
		(const Rva003F1BD3TemplateView *)value);
}

void Rva00437E9C(int value)
{
	g_pRva00437E9C->method(value);
}
