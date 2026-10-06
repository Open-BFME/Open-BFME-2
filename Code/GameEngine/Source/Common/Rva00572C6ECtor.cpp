// cl: /MD
// ??0Rva00572C6E@@QAE@XZ @0x00572C5A 20B evidence: vtable 0x0086E088 store plus base ctor 0x005CB22A with null held; caller 0x0041E682; next-door Rva005CB23CDerived hosts the sibling dtors.
class Rva005CB22A
{
public:
	Rva005CB22A(void *held);
	virtual ~Rva005CB22A();

	void *m_held;
};

class Rva00572C6E : public Rva005CB22A
{
public:
	Rva00572C6E();
	virtual ~Rva00572C6E();
};

Rva00572C6E::Rva00572C6E()
	: Rva005CB22A(0)
{
}
