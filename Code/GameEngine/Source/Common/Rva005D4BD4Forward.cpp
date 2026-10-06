// cl: /MD
// ?rva005D4BD4@Rva005D4BD4@@QAEXM@Z @0x005D4BD4 19B: float forwarder to rowed SetPos 0x005D4B6E via member at +0x14. Evidence: fld fstp x87 copy plus rowed callee 0x005D4B6E plus caller 0x0057A4D6 sibling forwarders 0x005D4BAE 0x005D4BC1.
class Rva005D4B6E
{
public:
	void rva005D4B6E(float v);
};

class Rva005D4BD4
{
public:
	void rva005D4BD4(float v);
private:
	char m_pad00[0x14];
	Rva005D4B6E *m_target14;
};

void Rva005D4BD4::rva005D4BD4(float v)
{
	m_target14->rva005D4B6E(v);
}
