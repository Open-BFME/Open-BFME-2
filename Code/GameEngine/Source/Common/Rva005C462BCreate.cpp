// cl: /MD /GX
// ?rva005C462B@Rva005C462B@@QAEPAVRva005C45B6@@I@Z, RVA 0x005C462B, 60B. Chain from 0x005C45B6: new(0xC) then ctor(a, this-as-uint) with EH unwind. Evidence: retail call to rowed ??0Rva005C45B6@@QAE@II@Z plus null-check je plus __EH_prolog.
class Rva0059B7CB
{
public:
	Rva0059B7CB(unsigned int field04, unsigned int field08);
	virtual void slot00();
private:
	unsigned int m_field04;
	unsigned int m_field08;
};

class Rva005C45B6 : public Rva0059B7CB
{
public:
	Rva005C45B6(unsigned int a, unsigned int b);
};

class Rva005C462B
{
public:
	Rva005C45B6 *rva005C462B(unsigned int a);
};

Rva005C45B6 *Rva005C462B::rva005C462B(unsigned int a)
{
	return new Rva005C45B6(a, (unsigned int)this);
}
