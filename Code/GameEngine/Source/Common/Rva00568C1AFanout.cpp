// cl: /MD
//
// ?rva00568C1A@Rva00568C1A@@QAEXXZ @0x00568C1A 28B.
// Fan-out: run every element of the +0x58/+0x5C pointer range through
// the (banked) 0x00568939 keyed notify with this as the key. Same
// Rva00568920 element view as the banked notify TU.
class Rva00568920
{
public:
	void rva00568939(int key);
};

class Rva00568C1A
{
public:
	void rva00568C1A();
private:
	char m_pad[0x58];
	Rva00568920 **m_begin58;
	Rva00568920 **m_end5C;
};

void Rva00568C1A::rva00568C1A()
{
	for (Rva00568920 **p = m_begin58; p != m_end5C; ++p)
		(*p)->rva00568939((int)this);
}
