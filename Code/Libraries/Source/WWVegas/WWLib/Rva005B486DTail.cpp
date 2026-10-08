// cl: /MD /EHsc
// ?rva005B486D@Rva005B486DOwner@@QAEXXZ @0x005B486D 34B: thiscall, no args, tail-calls 0x005B2794.
// Sets the dword slot at the pointer held in this+4 (+0x27c) to 1, then runs the owner's
// address-named member at 0x005B4653 and tail-jumps to the now-rowed Powers member at
// 0x005B2794. The outer method's name remains address-derived; the slot class is
// the matched dword setter. UpdatePalantirButtons is a WorldBuilder name lead.
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
private:
	char pad00[4];
	char *m_04;
};

namespace AptCreateAHero
{
class Powers
{
public:
	void UpdatePalantirButtons();
};
}

void Rva005B486DOwner::rva005B486D()
{
	((Rva005B034ADwordSlot *)(m_04 + 0x27c))->set(1);
	rva005B4653();
	((AptCreateAHero::Powers *)this)->UpdatePalantirButtons();
}
