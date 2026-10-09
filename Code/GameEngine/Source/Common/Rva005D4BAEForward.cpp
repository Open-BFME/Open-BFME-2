// cl: /MD
// ?rva005D4BAE@Rva005D4BAE@@QAEXM@Z @0x005D4BAE 19B: float forwarder to rowed SetPageSize 0x005D4AD0 via member at +0x14. Evidence: fld fstp x87 copy plus rowed callee 0x005D4AD0 plus callers 0x0057B1AD 0x005F2611 0x005F2654 plus unblocks 0x0057B16D 0x005F258E sibling 0x005D4BC1.
class AptScrollBar
{
public:
	class Impl
	{
	public:
		void SetPageSize(float v);
	};
};

class Rva005D4BAE
{
public:
	void rva005D4BAE(float v);
private:
	char m_pad00[0x14];
	AptScrollBar::Impl *m_target14;
};

void Rva005D4BAE::rva005D4BAE(float v)
{
	m_target14->SetPageSize(v);
}
