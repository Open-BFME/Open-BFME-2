// cl: /Od

class Rva00815730Obj
{
public:
	char m_lead[0x214];
	int m_at214;
	int m_at218;
};

void Rva00815730Set(Rva00815730Obj *obj, int value)
{
	obj->m_at218 = value;
	obj->m_at214 |= 2;
}
