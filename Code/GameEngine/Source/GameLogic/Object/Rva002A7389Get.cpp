// cl: /DNDEBUG /MD
//
// Getter ?get@Rva002A7389@@QAEHH@Z at retail 0x002A7389 (6 bytes).
// Dedicated TU.
//
// Trivial thiscall dword reader: mov eax,[ecx+8]; ret 4. The single int
// parameter is ignored by the body (every caller pushes one dword; e.g.
// 0x005D787A pushes 1, 0x00048772/0x0004877B in FUN_0044826c). Callers invoke
// it on a +0x60 subobject view (0x005D7860: lea esi,[eax+0x60] after
// ?getControllingPlayer@Object@@QBEPAVPlayer@@XZ, then cvtsi2ss on the int
// result), but the owning class is unproven, so the name claims only the
// address plus the witnessed shape (taskfile honest-name precedent
// ?get@Rva0066B100@@QAEHH@Z). All callees: none, so the gate resolves it.
// Neighbour TU Code/GameEngine/Source/GameLogic/Object/Rva002A73B8Dtor.cpp
// (0x002A73B8/0x002A73E4) supplies the // cl: line.

class Rva002A7389
{
public:
	int get(int);

private:
	char m_lead[8];
	int m_value; // +0x08
};

int Rva002A7389::get(int)
{
	return m_value;
}

// Setter ?set@Rva002A738F@@QAEXHH@Z at retail 0x002A738F (21 bytes).
// Same page, same flags, appended here.
//
// Two-dword setter with a flag store: mov [ecx+4],a; mov [ecx+0x10],b;
// mov byte [ecx+0x2c],1; ret 8. Sole caller 0x003BD18D invokes it on a +0x60
// subobject view (lea ecx,[eax+0x60], forwarding its own stack args), the
// same +0x60 usage seen at the ?get@Rva002A7389@@QAEHH@Z call sites, but the
// owning class is still unproven so this stays a separate opaque holder.

class Rva002A738F
{
public:
	void set(int, int);

private:
	char m_lead[4];
	int m_4; // +0x04
	char m_pad8[8];
	int m_10; // +0x10
	char m_pad14[0x18];
	unsigned char m_2c; // +0x2c
};

void Rva002A738F::set(int a, int b)
{
	m_4 = a;
	m_10 = b;
	m_2c = 1;
}
