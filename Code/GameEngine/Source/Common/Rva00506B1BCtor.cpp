// cl: /MD
// ??0Rva00506B1B@@QAE@XZ @0x00506B1B 13B: base/member ctor storing vtable
// 0x00C63F9C at [this] then byte 0 at +4. Called by 8 bodies (e.g. 0x004E9B46
// passes ecx=this as base, 0x00597693 passes ecx=esi+0xC as member); next row
// 0x00506B28 setter stores the same vtable immediate. Honest address-derived
// name; virtuals carry the vptr like Rva00270025.
// ?rva00506B2F@Rva00506B1B@@QAEXXZ @0x00506B2F 12B: if (+4 flag) return else
// tail-jmp second virtual (slot +4). Same +4 layout as the ctor above and
// adjacent address; 8 callers. Honest Rva method of Rva00506B1B.
// ??_GRva00506B1B@@UAEPAXI@Z @0x00506B3B 29B: vtable slot 0; the dtor is the
// inline vptr reset (0x00506B28 is its out-of-line copy), then delete.

class Rva00506B1B
{
public:
	Rva00506B1B();
	virtual ~Rva00506B1B() {}
	virtual void v1();
	void rva00506B2F();
	bool m_04;
};

Rva00506B1B::Rva00506B1B()
{
	m_04 = false;
}

void Rva00506B1B::rva00506B2F()
{
	if (m_04)
		return;
	v1();
}
