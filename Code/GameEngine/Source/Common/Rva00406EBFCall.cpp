// cl: /MD
// ?rva00406EBF@Rva00406EBF@@QAEXPAVXfer@@@Z @0x00406EBF 24B: thiscall wrapper forwarding Xfer arg to virtual slot 3 with byte flag at +0x70 set around the call. Callers 0x00409966 and 0x00409A3D pass stack Xfer object. Owner unknown so honest-address name.
class Xfer;
class Rva00406EBF
{
public:
	virtual void dummy00() = 0;
	virtual void dummy01() = 0;
	virtual void dummy02() = 0;
	virtual void dummy03(class Xfer *x) = 0;
	int m_04[27];
	bool m_70;
	void rva00406EBF(class Xfer *x);
};
void Rva00406EBF::rva00406EBF(Xfer *x)
{
	m_70 = true;
	dummy03(x);
	m_70 = false;
}
