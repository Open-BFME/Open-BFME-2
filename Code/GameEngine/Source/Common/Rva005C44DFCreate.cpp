// cl: /MD /GX
// ?rva005C44DF@Rva005C44DF@@QAEPAVRva005C436E@@I@Z retail 0x005C44DF 60B
// Evidence: chain from 0x005C4403 rowed ??0Rva005C436E@@QAE@II@Z plus null-check je plus __EH_prolog; twin of 0x005C462B 60B new plus ctor EH with this-as-uint
class Rva0059B7CB
{
public:
	Rva0059B7CB(unsigned int field04, unsigned int field08);
	virtual void slot00();
private:
	unsigned int m_field04;
	unsigned int m_field08;
};

class Rva005C436E : public Rva0059B7CB
{
public:
	Rva005C436E(unsigned int a, unsigned int b);
private:
	bool m_0C;
};

class Rva005C44DF
{
public:
	Rva005C436E *rva005C44DF(unsigned int a);
};

Rva005C436E *Rva005C44DF::rva005C44DF(unsigned int a)
{
	return new Rva005C436E(a, (unsigned int)this);
}
