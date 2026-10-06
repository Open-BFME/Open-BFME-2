// cl: /MD /DNDEBUG
// ?Release@Rva006FBDF0@@QAEXXZ, retail 0x006FBDF0 (20 B).
// Mnemonic-sequence sibling of the rowed ??0INIClass@@QAE@XZ 0x006169A0
// (push esi / mov esi,ecx / three stores / call / mov / pop / ret), but the
// operands say what it is: it loads the owned interface pointer at +0x60,
// calls its second vtable slot, then clears the member. That is a release /
// shutdown method, not a constructor -- the recipe is the prologue and the
// member-call shape, the local order and operands are its own. Layout offset
// 0x60 is the only witness; no caller and no symbol names the class, so the
// identity is outlined under an honest address-derived name.

class Rva006FBDF0Iface
{
public:
	virtual void first();
	virtual void second();
};

class Rva006FBDF0
{
public:
	void Release();
private:
	char m_pad[0x60];
	Rva006FBDF0Iface *m_owned;
};

void Rva006FBDF0::Release()
{
	m_owned->second();
	m_owned = 0;
}
