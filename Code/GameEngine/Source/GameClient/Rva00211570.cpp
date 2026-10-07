// cl: /EHsc /MD /D_CRTIMP=
// ?rva00211570@Rva00211570@@QAEXXZ @0x00211570 25B
// Target evidence: this 25-byte body saves its original receiver, calls RVA
// 0x00211505 with that receiver, tests the dword at this+0x2C4, and tail-jumps
// to RVA 0x003F92DA with the tested dword as ECX. The helper names and field
// meaning remain unresolved; the address-derived names only represent the call flow.
class Rva00211505
{
public:
	void rva00211505();
};

class Rva003F92DA
{
public:
	void rva003F92DA();
};

class Rva00211570
{
public:
	void rva00211570();

private:
	char m_pad[0x2C4];
	void *m_field2C4;
};

void Rva00211570::rva00211570()
{
	((Rva00211505 *)this)->rva00211505();
	if (m_field2C4)
		((Rva003F92DA *)m_field2C4)->rva003F92DA();
}
