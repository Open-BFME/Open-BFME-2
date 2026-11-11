// cl: /DNDEBUG /MD
//
// Vtable-slot bodies with no ledger owner and no Ghidra entry, batch AQ:
// each calls an unrowed Ghidra-listed function on the complete object (or
// on this object) and drops its one argument; the callees are pinned in
// reverse/symbols.csv under address-derived names (no-argument thiscall,
// plain ret). Classes are address-derived.

typedef int Int;

// 0x00082E12 (interface at +0x08) and 0x005E19BF (interface at +0x0C): the
// pinned 0x00082D6A resp. 0x005E1928 of the complete object.
class Rva00082D6A
{
public:
	virtual void primarySlot();
	void rva00082D6A();
private:
	Int m_04;
};
class Rva00082E12Iface
{
public:
	virtual void rva00082E12(Int unused) = 0;
};
class Rva00082E12 : public Rva00082D6A, public Rva00082E12Iface
{
public:
	void rva00082E12(Int unused);
};
void Rva00082E12::rva00082E12(Int)
{
	rva00082D6A();
}
// 0x005CC24C: the pinned 0x005CC23B of this object.
// The target writes AL on both branches; keep its return type bool despite
// the existing void pin. Only the byte at +0x0C is established by this body.
extern void ToggleQuitMenu();
class Rva005CC23B
{
public:
	bool rva005CC23B();
private:
	char m_pad[0xC];
	unsigned char m_enabled;
};
class Rva005CC24C : public Rva005CC23B
{
public:
	void rva005CC24C(Int unused);
};
bool Rva005CC23B::rva005CC23B()
{
	if (m_enabled) {
		ToggleQuitMenu();
		return true;
	}
	return false;
}
void Rva005CC24C::rva005CC24C(Int)
{
	rva005CC23B();
}

// 0x005CE125 (interface at +0x08; slots at VA 0x00C7514C and 0x00C75180):
// returns the rowed no-argument +4 callback forwarder 0x005E6817 (ledger
// spelling Rva005E57A2Callback::invoke) on the complete object, dropping its
// one argument (call, then ret 4).
#include "../../Include/GameClient/Rva005E57A2Callback.h"
class Rva005CE125Primary
{
public:
	virtual void primarySlot();
private:
	Int m_04;
};
class Rva005CE125Iface
{
public:
	virtual Int rva005CE125(Int unused) = 0;
};
class Rva005CE125 : public Rva005CE125Primary, public Rva005CE125Iface
{
public:
	Int rva005CE125(Int unused);
};
Int Rva005CE125::rva005CE125(Int)
{
	return ((Rva005E57A2Callback *)this)->invoke();
}

// 0x005CDE69 (interface at +0x0C; slot at VA 0x00C750F4): tail-jumps with
// its argument to the rowed +4 callback forwarder 0x005E6817 (ledger
// spelling Rva005E6817Mid::fwd) on the complete object.
class GameMessage;
#include "../../Include/Common/Rva005E6817Mid.h"
class Rva005CDE69Primary
{
public:
	virtual void primarySlot();
private:
	Int m_04;
	Int m_08;
};
class Rva005CDE69Iface
{
public:
	virtual Int rva005CDE69(GameMessage *message) = 0;
};
class Rva005CDE69 : public Rva005CDE69Primary, public Rva005CDE69Iface
{
public:
	Int rva005CDE69(GameMessage *message);
};
Int Rva005CDE69::rva005CDE69(GameMessage *message)
{
	return ((Rva005E6817Mid *)this)->fwd(message);
}
