// cl: /O1 /DNDEBUG /MD
//
// ?rva002D363E@Rva002D363EOwner@@QAEXH@Z @0x002D363E 80B: dual-subobject
// forward with gated pair (thiscall, int arg, void). Forwards arg to the
// landed 0x0052A287 via +0x10+0x8c and to landed 0x0052854C via +0x10+0x90,
// then when landed hasOverrideWindow 0x002D35D6 on this is true forwards
// to pinned 0x00529FBE (+0x8c) and pinned 0x005288BD (+0x90). Honest
// address-derived names; sub-object identities unproven.

class RadarWindowOverrideSource
{
public:
	bool hasOverrideWindow() const;
};

struct Rva002D363E88
{
	void rva0052A287(int x);
	void rva00529FBE();
};

struct Rva002D363E90
{
	void rva0052854C(int x);
	void rva005288BD();
};

class Rva002D363EOwner
{
public:
	void rva002D363E(int x);
private:
	char m_pad00[0x10];
	void *m_p10;
};

// ?rva002D363E@Rva002D363EOwner@@QAEXH@Z
void Rva002D363EOwner::rva002D363E(int x)
{
	((Rva002D363E88 *)((char *)m_p10 + 0x8C))->rva0052A287(x);
	((Rva002D363E90 *)((char *)m_p10 + 0x90))->rva0052854C(x);
	if (((RadarWindowOverrideSource *)this)->hasOverrideWindow()) {
		((Rva002D363E88 *)((char *)m_p10 + 0x8C))->rva00529FBE();
		((Rva002D363E90 *)((char *)m_p10 + 0x90))->rva005288BD();
	}
}
