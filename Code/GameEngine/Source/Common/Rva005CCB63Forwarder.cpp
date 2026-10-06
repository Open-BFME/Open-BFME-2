// cl: /O1 /MD
// ?rva005CCB63@Rva005CCB63@@QAEXXZ @0x005CCB63 8B evidence: tail-jmp to rowed 0x005CCB23 Rva005CCB23NullForwarder; thiscall caller 0x005CD762
class Rva005CCB23NullForwarder
{
public:
	void rva005CCB23();
};
class Rva005CCB63
{
public:
	void rva005CCB63();
	char m_lead[8];
	Rva005CCB23NullForwarder *m_ptr;
};
void Rva005CCB63::rva005CCB63()
{
	m_ptr->rva005CCB23();
}
