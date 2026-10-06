// cl: /DNDEBUG /MD
//
// ??0Rva002D76A6@@QAE@XZ @0x002D76A6 (17B).
// Ctor stores vtable 0x0087506C then zeroes dwords at +0x04 and +0x08.
// Evidence: vtable store plus two dword zeroes; 1 caller at 0x0004EF6F;
// honest Rva class, no donor.

class Rva002D76A6
{
public:
	virtual void v0();
	Rva002D76A6();

private:
	int m_04;
	int m_08;
};

Rva002D76A6::Rva002D76A6() : m_04(0), m_08(0)
{
}
