// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ??1Rva005F4AD7@@QAE@XZ @0x005F4AD7 22B
// ??0Rva005F4AD7@@QAE@ABU0@@Z @0x005F4AB9 30B copy-ctor abutting the dtor.
// ??4Rva005F4AD7@@QAEAAU0@ABU0@@Z @0x005FD4FF 63B assign same Holder trio.
// Holder dtor releasing computed TargetRef via rowed fastcall 0x0007DEEF.
// If m_ptr is null return; else Release((TargetRef *)(Q + S + 4)) where
// S is m_ptr and Q is *( *(S+4) + 4 ). Same computation as the sibling
// copy-ctor at 0x005F4AB9 (inc dword [edx+4]) and the clear at 0x005D4E8B
// (call plus null) which target the same referent.
// Evidence: unlock lane; callee all rowed; callers at 0x005D4EE1 0x005D4F61
// 0x005F4B21 0x005FD607 0x005FD864 plus Unwind funclets; member dtors at
// 0x005FD5D4 (+4) and 0x005D4EC6 (+0xC) call this alongside direct Release
// and StringBase releases.
struct TargetRef00217D4C
{
	void *m_vtbl;
	int references;
};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);
struct Rva005F4AD7Mid
{
	int m_00;
	int m_04;
};
struct Rva005F4AD7Inner
{
	int m_00;
	Rva005F4AD7Mid *m_04;
};
struct Rva005F4AD7
{
	Rva005F4AD7Inner *m_ptr;
	~Rva005F4AD7();
	Rva005F4AD7(const Rva005F4AD7 &other);
	Rva005F4AD7 &operator=(const Rva005F4AD7 &other);
};
Rva005F4AD7::~Rva005F4AD7()
{
	Rva005F4AD7Inner *p = m_ptr;
	if (p)
		ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)((char *)p + 4 + p->m_04->m_04));
}
Rva005F4AD7::Rva005F4AD7(const Rva005F4AD7 &other)
{
	Rva005F4AD7Inner *p = other.m_ptr;
	m_ptr = p;
	if (p) {
		TargetRef00217D4C *t = (TargetRef00217D4C *)((char *)p + 4 + p->m_04->m_04);
		++t->references;
	}
}
Rva005F4AD7 &Rva005F4AD7::operator=(const Rva005F4AD7 &other)
{
	if (this != &other) {
		if (other.m_ptr) {
			TargetRef00217D4C *t = (TargetRef00217D4C *)((char *)other.m_ptr + 4 + other.m_ptr->m_04->m_04);
			++t->references;
		}
		if (m_ptr)
			ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)((char *)m_ptr + 4 + m_ptr->m_04->m_04));
		m_ptr = other.m_ptr;
	}
	return *this;
}
