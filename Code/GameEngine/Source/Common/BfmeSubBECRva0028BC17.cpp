// cl: /O1
// ?rva0028BC17@BfmeSubBEC@@QAEXPAX@Z @0x0028BC17 18B: forward to rowed Rva004DF3F8::rva004DF3F8 when holder at +0x23c is non-null; tail-jmp; caller 0x004DF314 unblocks 0x004DF2FC; neighbours BfmeSubBECFilteredFind and BfmeConv448FindBEC share layout
class Rva004DF3F8
{
public:
	void rva004DF3F8(void *p);
};

class BfmeSubBEC
{
public:
	void rva0028BC17(void *p);
private:
	char m_pad00[0x23c];
	Rva004DF3F8 *m_23c;
};

void BfmeSubBEC::rva0028BC17(void *p)
{
	Rva004DF3F8 *holder = m_23c;
	if (holder != 0)
		holder->rva004DF3F8(p);
}
