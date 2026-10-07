// cl: /O1 /MD
class Rva00286926Host
{
public:
	void rva00286926(int a, int b, int c, int d, int e);
};
class Rva00287519Host
{
public:
	void rva00287519(int v);
private:
	unsigned char m_pad[0x78];
	int m_78;
	int m_7C;
};
// ?rva00287519@Rva00287519Host@@QAEXH@Z
void Rva00287519Host::rva00287519(int v)
{
	int i = 0;
	if (m_78 <= i)
		return;
	do
	{
		int n = m_7C;
		int j = 0;
		if (n <= j)
			goto next_outer;
		do
		{
			((Rva00286926Host *)this)->rva00286926(i, i, j, v, 0);
			n = m_7C;
			j++;
		} while (j < n);
next_outer: ;
		i++;
	} while (i < m_78);
}
