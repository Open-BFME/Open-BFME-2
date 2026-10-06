// cl: /MD
// ?set@Rva002E3766Holder@@QAEXHH@Z, retail 0x002E3766, 17 bytes.
// ?Rva002E3777Invoke@Rva002E3766Holder@@QAEXH@Z, retail 0x002E3777, 29 bytes.
// ?Rva002E3794Invoke@Rva002E3766Holder@@QAEXH@Z, retail 0x002E3794, 29 bytes.
// Leaf thiscall setter storing two ints at +0x54/+0x58 plus two callback
// invokers differing only by push 1 vs push 0. Callers 0x0039867C 0x004B0BC3
// 0x004EBD7D for setter; 0x0029223B for 3777 and 0x00292118 for 3794.
// Owning class unproven so honest Rva holder. Shape matches Rva002716.
class Rva002E3766Holder
{
public:
	void set(int a, int b);
	void Rva002E3777Invoke(int arg);
	void Rva002E3794Invoke(int arg);

private:
	unsigned char m_pad[0x54];
	int m_54;
	int m_58;
};

void Rva002E3766Holder::set(int a, int b)
{
	m_54 = a;
	m_58 = b;
}

void Rva002E3766Holder::Rva002E3777Invoke(int arg)
{
	if (m_54 != 0 && m_58 != 0)
		((void (__cdecl *)(int, int, int))m_54)(arg, m_58, 1);
}

void Rva002E3766Holder::Rva002E3794Invoke(int arg)
{
	if (m_54 != 0 && m_58 != 0)
		((void (__cdecl *)(int, int, int))m_54)(arg, m_58, 0);
}
