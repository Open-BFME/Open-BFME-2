// ?rva004211A0@Rva004211A0Host@@QAE_NPBURva004211A0Key@@PBVOverridable@@@Z
// partial score=0.9 date=2026-10-06
// cl: /O1 /MD
// ?rva004211A0@Rva004211A0Host@@QAE_NPAVRva004211A0Key@@PBVOverridable@@@Z
// @0x004211A0 42B. Frameless two-arg compare. The first call (pinned
// 0x004210F8) is relied on to pop its own stack arg (retail ret 4): that
// restores esp so the later [esp+8]/[esp+4] read the entry args, and entry
// ecx passes through untouched as the callee's this (it dereferences
// ecx+0xC/0x10). A negative result returns true; otherwise the second arg's
// final override (rowed 0x00288609) is compared against the first arg's +4
// dword (signed >=). Evidence: callee ret-4 tail bytes plus rowed callees.
class Overridable
{
public:
	const Overridable *friend_getFinalOverride() const;
	char m_pad04[0x30];
	int m_30;
};
struct Rva004211A0Key
{
	int m_00;
	int m_04;
};
struct Rva004211A0OverrideView
{
	char m_pad[0x30];
	int m_30;
};
int __stdcall Rva004210F8Call(const Overridable *o);
class Rva004211A0Host
{
public:
	bool rva004211A0(const Rva004211A0Key *key, const Overridable *o);
};
bool Rva004211A0Host::rva004211A0(const Rva004211A0Key *key, const Overridable *o)
{
	if (Rva004210F8Call(o) < 0)
		return true;
	return key->m_04 >= o->friend_getFinalOverride()->m_30;
}
