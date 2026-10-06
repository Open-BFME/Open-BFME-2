// cl: /MD
// ?rva005D3F6D@Rva005D3F6D@@QAEXH@Z @0x005D3F6D 32B
// Evidence: leaf; virtual call slot 0x28 on object at +0x24 with cache at +0x2C;
// caller 0x0057A3A3; neighbours share /O1 /MD
class Rva005D3F6DInner
{
public:
	virtual void s00() = 0;
	virtual void s01() = 0;
	virtual void s02() = 0;
	virtual void s03() = 0;
	virtual void s04() = 0;
	virtual void s05() = 0;
	virtual void s06() = 0;
	virtual void s07() = 0;
	virtual void s08() = 0;
	virtual void s09() = 0;
	virtual void set(int a, int b) = 0;
};

class Rva005D3F6D
{
public:
	void rva005D3F6D(int v);
private:
	char m_pad[0x24];
	Rva005D3F6DInner *m_ptr24;
	int m_pad28;
	int m_cached2C;
};

void Rva005D3F6D::rva005D3F6D(int v)
{
	if (v == m_cached2C)
		return;
	m_ptr24->set(v, 0);
	m_cached2C = v;
}
