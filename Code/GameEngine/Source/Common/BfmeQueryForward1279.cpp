class BfmeQuery1279
{
public:
	// First parameter is int in retail (the query asserts it with a signed
	// jge and walks it against the 16-bit node key); callers pass pointers,
	// which convert with identical pushes. Resolves via the AptDisplayList
	// row, which supersedes the void*-spelled pin.
	void bfmeQuery1279(int value, int zero, void **other, void **result);
};

struct BfmeInput1279
{
	void *m_value;
};

class BfmeWrapper1279
{
public:
	void bfmeProcess1279(void *value);
	void bfmeForwardValue1279(void *value);
	void bfmeForward1279(BfmeInput1279 *input);

private:
	BfmeQuery1279 *m_query;
};

void BfmeWrapper1279::bfmeForwardValue1279(void *value)
{
	void *other;
	m_query->bfmeQuery1279((int)value, 0, &other, &value);
	bfmeProcess1279(value);
}

void BfmeWrapper1279::bfmeForward1279(BfmeInput1279 *input)
{
	void *other;
	m_query->bfmeQuery1279((int)input->m_value, 0, &other, (void **)&input);
	bfmeProcess1279(input);
}
