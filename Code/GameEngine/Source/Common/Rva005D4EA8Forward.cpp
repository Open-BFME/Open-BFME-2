// cl: /MD
class Rva0057C499
{
public:
	void rva0057C499(int a1, int a2);
};
class Rva005D4EA8
{
public:
	void *rva005D4EA8(int a1, int a2);
private:
	char m_00[8];
	int m_08;
	int m_0C;
};
void *Rva005D4EA8::rva005D4EA8(int a1, int a2)
{
	((Rva0057C499 *)this)->rva0057C499(a1, a2);
	m_08 = 0;
	m_0C = 0;
	return this;
}
