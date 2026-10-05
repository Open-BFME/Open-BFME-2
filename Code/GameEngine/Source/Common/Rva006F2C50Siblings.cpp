// cl: /O2 /MD
// ?Rva006F2C50@Rva006F2C50@@UAEXXZ @0x006F2C50 30B.
// Recovered from the ?Rva0070DF60@Rva006DE2B0@@UAEXXZ recipe at 0x0070DF60.
// Same operand-masked shape: release the AptRef member through vtable slot 1,
// clear it, then tail-jump to the rowed clear on the same this. Only the member
// offset (+0x20 here, +0x1C in the template) and the tail target differ; the
// tail is the rowed 5-byte thunk ?rva0070DFE0@BfmeAptValue006DCD20@@QAEXXZ at 0x0070DFE0,
// itself a jmp to Rva006DE150::rva006DE150 at 0x006DE150, so the row name resolves it. Virtual slot 0x2C of the class vtable.
class AptRef
{
public:
	virtual void AddRef();
	virtual void Release();
};

class BfmeAptValue006DCD20
{
public:
	void rva0070DFE0();
};

class Rva006F2C50
{
public:
	char m_pad[0x1c];
	AptRef *m_ctor;
	virtual void rva006F2C50();
};

void Rva006F2C50::rva006F2C50()
{
	if (m_ctor)
		m_ctor->Release();
	m_ctor = 0;
	((BfmeAptValue006DCD20 *)this)->rva0070DFE0();
}
