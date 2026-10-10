// cl: /O1 /MD
// ?rva004211A0@Rva004211A0Host@@QAE_NPBURva004211A0Key@@PBVOverridable@@@Z @0x004211A0 42B.
// Native 4211A0..4211CA RET8, frameless. Called from Player::rva002A9ED9 with ECX = the
// 0x00E03158 manager. The manager walk 0x004210F8 (thiscall, one pushed argument, same ECX)
// returns a signed result; negative gates through, otherwise the second argument's final
// override (rowed 0x00288609) is compared with the first argument's +4 dword (signed >=).
// Names are address-derived; neither class identity is proven.
// Codegen: the bool result is a merge of two arms; a plain 'return a >= b' emits
// xor edx,edx/setge dl/mov al,dl (46B), the assigned 'r' merge emits native 'setge al' (42B).
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
class Rva004211A0Host
{
public:
	bool rva004211A0(const Rva004211A0Key *key, const Overridable *o);
	int rva004210F8(const Overridable *o);
};
bool Rva004211A0Host::rva004211A0(const Rva004211A0Key *key, const Overridable *o)
{
	bool r;
	if (rva004210F8(o) < 0)
		r = true;
	else
		r = key->m_04 >= o->friend_getFinalOverride()->m_30;
	return r;
}
