// cl: /MD
// ?rva005D4BC1@Rva005D4BC1@@QAEXM@Z @0x005D4BC1 19B: float forwarder to rowed SetLineSize 0x005D4B1F via member at +0x14. Evidence: fld fstp x87 copy plus rowed callee 0x005D4B1F plus callers 0x0057B1F5 0x005F2629 0x005F2662 plus unblocks 0x0057B16D 0x005F258E.
class Rva005D4B1F
{
public:
	void rva005D4B1F(float v);
};

class Rva005D4BC1
{
public:
	void rva005D4BC1(float v);
private:
	char m_pad00[0x14];
	Rva005D4B1F *m_target14;
};

void Rva005D4BC1::rva005D4BC1(float v)
{
	m_target14->rva005D4B1F(v);
}
