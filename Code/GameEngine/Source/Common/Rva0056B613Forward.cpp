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
private:
	char m_pad55[0x55];
	unsigned char m_55;	// +0x55, gates the +0x14 id check
	unsigned char m_56;	// +0x56, gates the helper getter
};

class Rva002E0BC0Helper
{
public:
	unsigned char rva002E0BC0(int value);
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

// ?rva0056B7A0@Rva003F9FE6@@QAEEH@Z @0x0056B7A0 62B.
// Slot 0 of vtable 0x00837898: flag/id-gated helper predicate. Byte +0x55
// gates an id check at +0x14 of the Logic+0x98 object against the int arg;
// byte +0x56 gates the pinned Helper getter with the arg. The +0x98 object is
// the LivingWorldLogic local player per LivingWorldLogic.cpp (m_localPlayer);
// the helper getter is the pinned TU-local Rva002E0BC0Helper spelling (the
// rowed Rva002E071E::rva002E0BC0 returns int, the predicate tests its low
// byte). One shared xor-0/mov-1 epilogue serves all five exits, so the body
// is written single-exit (goto True) rather than with early returns, which
// keep their own 60B epilogues. Caller at 0x0056B613.
unsigned char Rva003F9FE6::rva0056B7A0(int arg)
{
	if (arg != -1) {
		void *obj = *(void **)((char *)TheLivingWorldLogic + 0x98);
		if (obj != 0 && (m_55 == 0 || *(int *)((char *)obj + 0x14) == arg)
			&& (m_56 == 0 || ((Rva002E0BC0Helper *)obj)->rva002E0BC0(arg) != 0))
			goto True;
		return 0;
	}
True:
	return 1;
}
