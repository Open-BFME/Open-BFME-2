// cl: /MD
//
// ?rva0041F28C@ArmyMemberDefinition@@QAEPAMH@Z, retail 0x0041F28C, 28 bytes.
// Index-selected float field accessor: arg 0 -> +0x04, arg 1 -> +0x08,
// otherwise +0x0C, return this+off in eax, ret 4 (__thiscall with one stack
// arg). Caller 0x005DA6CC passes int at +0x16C and derefs result as float
// (movss). Neighbours 0x0041F286/0x0041F310 in ConstIntGetters5.cpp.

class ArmyMemberDefinition
{
	int m_00;
	float m_04;
	float m_08;
	float m_0C;
public:
	float *rva0041F28C(int i);
};

float *ArmyMemberDefinition::rva0041F28C(int i)
{
	float *p;
	switch (i)
	{
	case 0:
		p = &m_04;
		break;
	case 1:
		p = &m_08;
		break;
	default:
		p = &m_0C;
		break;
	}
	return p;
}
