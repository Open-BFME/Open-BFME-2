// cl: /MD
// ?rva003FDE8C@Rva003FDE8C@@QAEXE@Z @0x003FDE8C 33B: __thiscall void method iterating
// pointer range [+0x2C,+0x30) calling rowed Rva0056B929::rva0056B929(arg). Evidence:
// retail loads begin/end from ecx+0x2C/0x30 steps 4 derefs each and forwards stack arg;
// callers at 0x003193E6/0x003FE3A1/0x00538D51/0x00538D7E; callee row Rva0056B929.cpp;
// sibling 0x003FDE50 same shape with hoisted range loop.
class Rva0056B929
{
public:
	void rva0056B929(unsigned char arg);
};

class Rva003FDE8C
{
	char m_pad[0x2C];
	Rva0056B929 **m_begin; // +0x2C
	Rva0056B929 **m_end; // +0x30
public:
	void rva003FDE8C(unsigned char arg);
};

void Rva003FDE8C::rva003FDE8C(unsigned char arg)
{
	Rva0056B929 **first = m_begin;
	Rva0056B929 **last = m_end;
	for (; first != last; ++first)
		(*first)->rva0056B929(arg);
}
