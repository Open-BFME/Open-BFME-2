// cl: /O1 /MD
// ?init@Rva004152BCHost@@QAEHHH@Z @0x004152BC 42B
struct Rva004152BCInner
{
	char m_00;
	int m_04;
	void *m_08;
	void *m_0C;
};
class Rva004152BCHost
{
public:
	int init(int a, int b);
	void setup(int b); // pinned retail 0x004151C4
private:
	Rva004152BCInner *m_00;
	int m_04;
};
int Rva004152BCHost::init(int a, int b)
{
	setup(b);
	m_04 = 0;
	m_00->m_00 = 0;
	m_00->m_04 = 0;
	m_00->m_08 = m_00;
	m_00->m_0C = m_00;
	return (int)this;
}
