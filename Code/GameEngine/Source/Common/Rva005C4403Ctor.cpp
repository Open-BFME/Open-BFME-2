// cl: /MD
// ??0Rva005C436E@@QAE@II@Z retail 0x005C4403 32B
// Evidence: vtable 0x008745A8 plus base ??0Rva0059B7CB@@QAE@II@Z plus byte +0xC plus caller 0x005C4507 unblocks 0x005C44DF
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

Rva005C436E::Rva005C436E(unsigned int a, unsigned int b)
	: Rva0059B7CB(a, b)
{
	m_0C = 0;
}
