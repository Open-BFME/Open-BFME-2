// cl: /MD
// ?rva003FDE50@Rva003FDE50@@QAEXI@Z @0x003FDE50 33B: __thiscall void method iterating
// pointer range [+0x2C,+0x30) calling rowed Rva0056B970::rva0056B970(arg). Evidence:
// retail loads begin/end from ecx+0x2C/0x30 steps 4 derefs each and forwards stack arg;
// callers at 0x00538D5D/0x00538DB5 pass pointers as arg; callee row Rva0056B970.cpp.
class Rva0056B970
{
public:
	void rva0056B970(unsigned int arg);
};

class Rva003FDE50
{
	char m_pad[0x2C];
	Rva0056B970 **m_begin; // +0x2C
	Rva0056B970 **m_end; // +0x30
public:
	void rva003FDE50(unsigned int arg);
};

void Rva003FDE50::rva003FDE50(unsigned int arg)
{
	Rva0056B970 **first = m_begin;
	Rva0056B970 **last = m_end;
	for (; first != last; ++first)
		(*first)->rva0056B970(arg);
}
