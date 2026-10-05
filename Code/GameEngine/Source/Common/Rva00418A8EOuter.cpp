// cl: /O1 /MD
// ?outer@Rva00418A8EHost@@QAEHHH@Z @0x00418A8E 36B
class Rva000427195
{
public:
	void rva00212858(unsigned v);
};
class Rva00418A8EHost : public Rva000427195
{
public:
	int outer(int a, int b);
	void apply(int a, int b); // pinned retail 0x00418A12
private:
	char m_00[0x10];
	int m_10;
};
int Rva00418A8EHost::outer(int a, int b)
{
	rva00212858(m_10 + 1);
	apply(a, b);
	return a;
}
