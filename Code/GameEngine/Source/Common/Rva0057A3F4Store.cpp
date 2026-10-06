// cl: /MD
// ?rva0057A3F4@Rva0057A3F4@@QAEPAV1@PAVRva005D1A79DwordCounter@@@Z @0x0057A3F4 24B.
// Ref-holding pointer setter: store pointer at +0 then inc its dword counter if non-null then return this.
// Evidence: unlock lane plus caller 0x0057B0F7 plus callee inc 0x005D1A79 plus prev Disp8ByteFieldGetters plus next Rva0057A51CApt.
class Rva005D1A79DwordCounter
{
public:
	void inc();
};

class Rva0057A3F4
{
public:
	Rva0057A3F4 *rva0057A3F4(Rva005D1A79DwordCounter *p);
private:
	Rva005D1A79DwordCounter *m_ptr;
};

Rva0057A3F4 *Rva0057A3F4::rva0057A3F4(Rva005D1A79DwordCounter *p)
{
	m_ptr = p;
	if (p)
		p->inc();
	return this;
}
