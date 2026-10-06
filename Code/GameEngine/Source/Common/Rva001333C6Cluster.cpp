// cl: /MD
//
// Guarded tail-call from the 0x001333C6 neighbourhood. A __thiscall member that
// walks this->+0x00, then +0x14, then +0x08 and tail-calls that object's own
// member at 0x0013331A. The tail callee must be a member of the walked type:
// that is what keeps ecx live for the jump. Identity is not recovered; the
// class and method names are address-derived, matching the /O1 shape of the
// neighbouring Rva00132FE9 forwarder.

class Rva0013331A
{
public:
	void rva0013331A();

	char m_pad00[8];
	int m_field8;
};

class Rva001333C6Owner
{
public:
	char m_pad00[0x14];
	Rva0013331A *m_p14;
};

class Rva001333C6
{
public:
	Rva001333C6Owner *m_p00;
	void f();
};

void Rva001333C6::f()
{
	Rva001333C6Owner *owner = m_p00;

	if (owner != 0)
	{
		Rva0013331A *x = owner->m_p14;

		if (x != 0 && x->m_field8 != 0)
			return x->rva0013331A();
	}
}
