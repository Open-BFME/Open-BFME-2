// cl: /O1 /MD
// ?rva005CCB6B@Rva005CCB6B@@QAEXXZ @0x005CCB6B 8B evidence: tail-jmp to rowed 0x005CC966; chain from own landing; prev Rva005CCB63
class Rva005CC966
{
public:
	void rva005CC966();
};
class Rva005CCB6B
{
public:
	void rva005CCB6B();
	char m_lead[8];
	Rva005CC966 *m_ptr;
};
void Rva005CCB6B::rva005CCB6B()
{
	m_ptr->rva005CC966();
}
