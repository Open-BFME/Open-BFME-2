// cl: /MD
// ??0Rva005C45B6@@QAE@II@Z, RVA 0x005C45B6, 28B. Unlock lane: ctor forwarding two uints to rowed base ??0Rva0059B7CB@@QAE@II@Z at 0x0059B7CB then vtable 0x008746A0. Evidence: retail call bytes plus vtable store plus caller 0x005C4653 unblocks 0x005C462B.
class Rva0059B7CB
{
public:
	Rva0059B7CB(unsigned int field04, unsigned int field08);
	virtual void slot00();
};

class Rva005C45B6 : public Rva0059B7CB
{
public:
	Rva005C45B6(unsigned int a, unsigned int b);
};

Rva005C45B6::Rva005C45B6(unsigned int a, unsigned int b)
	: Rva0059B7CB(a, b)
{
}
