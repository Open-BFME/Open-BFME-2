// cl: /MD
// ??0Rva0057BCD7@@QAE@XZ @0x0057BCD7 21B
// Honest ctor with member at +4 via rowed Rva00330757Member ctor 0x00330757.
// Donor: Code/GameEngine/Source/GameLogic/Object/Behavior/Rva004FAC6BCtor.cpp
// (21B empty ctor with novtable base + member; same push esi/mov esi,ecx/
// lea ecx,[esi+4]/call/mov [esi],vtable shape). Vtable 0x00C6F248
// (RVA 0x0086F248 8x 0x0043B810 purecall slots between ButtonState strings).
// Prev is holder 0x0057BC63 (same // cl:); next is dtor 0x0057BCEC (different
// class: that dtor frees via free while this member builds vector via
// bfmealloc so own address name is kept). Caller at 0x0057BD8E.
class Rva00330757Member
{
public:
	Rva00330757Member();
};

class __declspec(novtable) Rva0057BCD7Base0
{
public:
	virtual void base0();
};

class Rva0057BCD7 : public Rva0057BCD7Base0, public Rva00330757Member
{
public:
	Rva0057BCD7();
	virtual ~Rva0057BCD7();
};

Rva0057BCD7::Rva0057BCD7()
{
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?base0@Rva0057BCD7Base0@@UAEXXZ=__purecall")
