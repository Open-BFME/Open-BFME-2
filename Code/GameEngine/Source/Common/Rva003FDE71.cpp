// cl: /MD
// ?rva003FDE71@Rva003FDE71@@QAEXXZ @0x003FDE71 27B: __thiscall void method iterating
// pointer range [+0x2C,+0x30) calling rowed Rva0056B95E::rva0056B95E(). Evidence:
// retail loads begin/end from ecx+0x2C/0x30 steps 4 derefs each with no stack arg;
// caller at 0x002B3564; callee row Rva0056B95E.cpp; siblings 0x003FDE50/0x003FDE8C same shape.
class Rva0056B95E
{
public:
	void rva0056B95E();
};

class Rva003FDE71
{
	char m_pad[0x2C];
	Rva0056B95E **m_begin; // +0x2C
	Rva0056B95E **m_end; // +0x30
public:
	void rva003FDE71();
};

void Rva003FDE71::rva003FDE71()
{
	Rva0056B95E **first = m_begin;
	Rva0056B95E **last = m_end;
	for (; first != last; ++first)
		(*first)->rva0056B95E();
}
