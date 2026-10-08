// cl: /MD /EHsc
// ?rva005B486D@Rva005B486DOwner@@QAEXXZ @0x005B486D 34B: thiscall, no args, tail-calls 0x005B2794.
// Sets the dword slot at the pointer held in this+4 (+0x27c) to 1, then runs the owner's
// address-named member at 0x005B4653 and tail-jumps to the owner's address-named member at
// 0x005B2794. Member names are address-derived; the slot class is the matched dword setter.
class Rva005B034ADwordSlot
{
public:
	void set(int value);
};

class Rva005B486DOwner
{
public:
	void rva005B486D();
	void rva005B4653();
	void rva005B2794();
private:
	char pad00[4];
	char *m_04;
};

void Rva005B486DOwner::rva005B486D()
{
	((Rva005B034ADwordSlot *)(m_04 + 0x27c))->set(1);
	rva005B4653();
	rva005B2794();
}
