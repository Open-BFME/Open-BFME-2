// cl: /Od

class Rva008143A0Obj
{
public:
	char m_lead[0x210];
	int m_at210;
	int m_at214;
};

void Rva008143A0Set(Rva008143A0Obj *obj, int value)
{
	obj->m_at214 = value;
	obj->m_at210 |= 2;
}
