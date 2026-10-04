// cl: /O1 /MD
// ?rva002C5F65@Rva002C5F65@@QAEXXZ @0x002C5F65 13B
// Evidence: leaf tail-forward to rowed Rva0050542B rva005058F7 when member at +0xC non-null; caller 0x002C685E.
class Rva0050542B
{
public:
	void rva005058F7();
};

class Rva002C5F65
{
public:
	void rva002C5F65();
private:
	char _pad[0xc];
	Rva0050542B *m_c;
};

void Rva002C5F65::rva002C5F65()
{
	Rva0050542B *p = m_c;
	if (!p)
		return;
	return p->rva005058F7();
}
