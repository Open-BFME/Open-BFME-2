// cl: /MD
struct Rva005E5884Inner
{
	virtual int f0();
	virtual int f1();
	virtual int f2();
	virtual int f3();
};
class Rva005E5884
{
public:
	int rva005E5884(int unused1, int unused2);
private:
	char m_00[0x38];
	Rva005E5884Inner *m_38;
	int m_3C;
	int m_40;
};
int Rva005E5884::rva005E5884(int unused1, int unused2)
{
	(void)unused1;
	(void)unused2;
	Rva005E5884Inner *p;
	if (m_40 != 0)
		return -1;
	if ((p = m_38) != 0)
		return p->f3();
	return -1;
}
