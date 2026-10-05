// cl: /O1 /MD
// ?rva00576FBA@Rva00576FBA@@QAEXXZ @ 0x00576FBA (20B). Chain calling rva00319B31 then tail-jumping rva00319B0A on object at +0x18.
// Evidence: callers 0x005775C1 0x00577634; callees rowed in Rva003196A7ListenerWalks.cpp.
class Rva00319B0AOwner
{
public:
	void rva00319B0A();
	void rva00319B31();
};

class Rva00576FBA
{
public:
	void rva00576FBA();
private:
	char m_pad[0x18];
	Rva00319B0AOwner *m_ptr;
};

void Rva00576FBA::rva00576FBA()
{
	m_ptr->rva00319B31();
	return m_ptr->rva00319B0A();
}
