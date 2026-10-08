// cl: /MD
//
// ?rva0056B613@Rva0056B613@@QAEXH@Z @0x0056B613 43B.
// Gated forward: when the +0x5E flag is set, run pinned 0x002B269E on the
// singleton with the int argument and return early on false; otherwise (and
// on true) run the banked-spelling 0x0056B7A0 on this. Honest
// address-derived names.

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
class Rva002B269E
{
public:
	bool rva002B269E(int arg);
};

class Rva003F9FE6
{
public:
	unsigned char rva0056B7A0(int arg);
};

class Rva0056B613
{
public:
	void rva0056B613(int arg);
private:
	char m_pad[0x5E];
	unsigned char m_5E;	// +0x5E
};

void Rva0056B613::rva0056B613(int arg)
{
	if (m_5E != 0) {
		if (!(*(Rva002B269E **)&TheLivingWorldLogic)->rva002B269E(arg))
			return;
	}
	((Rva003F9FE6 *)this)->rva0056B7A0(arg);
}
