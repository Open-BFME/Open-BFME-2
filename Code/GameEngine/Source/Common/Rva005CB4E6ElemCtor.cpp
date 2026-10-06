// cl: /MD
// ??0Rva005CB4E6Elem@@QAE@PAVRva005CB8D4@@@Z retail 0x005CB4C7 31B
// Elem ctor storing the owner pointer at +0 then zeroing six dwords at
// +4/+8/+0xC/+0x10/+0x14/+0x18 (size 0x1C). Evidence: sole caller 0x005CB8AC
// pushes 0x1C for operator new 0x0002FDA0 then calls here with outer this
// (Rva005CB8D4 vtable 0x00C74DA8) as the argument and stores the result at
// outer+4 (Rva005CB892::m_elem); pinned dtor at 0x005CB4E6 destroys members
// at +0x10/+0x14/+0x18 via 0x005CB31D; neighbours 0x005CB23C and 0x005CB85A
// share // cl: /O1 /MD. Owner identity stays honest Rva address names.
class Rva005CB8D4;
class Rva005CB4E6Elem
{
public:
	Rva005CB4E6Elem(Rva005CB8D4 *owner);
private:
	Rva005CB8D4 *m_owner;
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
	int m_14;
	int m_18;
};

Rva005CB4E6Elem::Rva005CB4E6Elem(Rva005CB8D4 *owner)
	: m_owner(owner)
	, m_04(0)
	, m_08(0)
	, m_0C(0)
	, m_10(0)
	, m_14(0)
	, m_18(0)
{
}
