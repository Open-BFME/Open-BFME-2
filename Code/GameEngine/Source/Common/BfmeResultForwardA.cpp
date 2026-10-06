// cl: /Ob0

struct BfmeResultA
{
	void *m_value;
	BfmeResultA();
	BfmeResultA(const BfmeResultA &that);
	~BfmeResultA();
};

class BfmeResultSourceA
{
public:
	BfmeResultA bfmeMakeResultA(int value);
};

class BfmeResultForwardA
{
	char m_pad[0x10];
	BfmeResultSourceA *m_source;

public:
	BfmeResultA bfmeForwardResultA();
};

BfmeResultA BfmeResultForwardA::bfmeForwardResultA()
{
	return m_source->bfmeMakeResultA(0);
}
