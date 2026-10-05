// cl: /O1 /MD /G7
// ??0Rva003B76EF@@QAE@PAH@Z @0x003B76EF 28B: zeroes +0 then runs the pinned
// 0x003B7448 member entry on +4 with arg+4. Evidence: single pointer arg
// (ret 4), arg advances one int element, ecx stays member address; no vtable.
class Rva003B7448
{
public:
	void rva003B7448(int x);
};

class Rva003B76EF
{
public:
	Rva003B76EF(int *a);

private:
	int m_00;
	Rva003B7448 m_04;
};

Rva003B76EF::Rva003B76EF(int *a)
{
	m_00 = 0;
	m_04.rva003B7448((int)(a + 1));
}
