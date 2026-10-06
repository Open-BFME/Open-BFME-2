// cl: /MD
// ?rva005CCB5B@Rva005CCB5B@@QAEXXZ @0x005CCB5B 8B evidence: tail-jmp to rowed 0x005CCB16 Rva005CCB16NullForwarder; thiscall callers 0x005CD284 0x005CD2D0
class Rva005CCB16NullForwarder
{
public:
	void rva005CCB16();
};
class Rva005CCB5B
{
public:
	void rva005CCB5B();
	char m_lead[8];
	Rva005CCB16NullForwarder *m_ptr;
};
void Rva005CCB5B::rva005CCB5B()
{
	m_ptr->rva005CCB16();
}
