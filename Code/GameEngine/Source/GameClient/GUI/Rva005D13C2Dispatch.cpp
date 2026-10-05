// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD
// ?rva005D13C2@Rva005D13C2@@QAEXXZ @ 0x005D13C2, 19 bytes.
// Target evidence: the body saves this, dispatches through the wrapper at
// +0x0C to rowed 0x005ED5EB, then tail-dispatches through the object at +0.
// Caller 0x005D14C0 reaches this entry directly. The two pointer views and
// the meaning of the virtual slot are structural inferences; class identity
// is unknown and remains address-derived.

class Rva005ED976
{
public:
	void rva005ED5EB();
};

class Rva005D13C2DispatchTarget
{
public:
	virtual void v0();
	virtual void dispatch();
};

class Rva005D13C2
{
public:
	void rva005D13C2();

private:
	Rva005D13C2DispatchTarget *m_target;
	char m_pad04[8];
	Rva005ED976 *m_view;
};

void Rva005D13C2::rva005D13C2()
{
	m_view->rva005ED5EB();
	m_target->dispatch();
}
