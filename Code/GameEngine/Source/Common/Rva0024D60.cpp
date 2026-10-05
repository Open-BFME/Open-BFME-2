// cl: /Od /Ob1
void __cdecl bfmeCopyChV24(char *a, char *b);
void __cdecl ReportError(char *a, int b);

inline bool ptrEq24(const char *a, const char *b)
{
	return a == b;
}

class Rva0024D60
{
public:
	char *m_a;
	char *m_b;
	void f();
};

void Rva0024D60::f()
{
	if (!ptrEq24(m_a, m_b))
	{
		char tmp = 0;
		bfmeCopyChV24(m_a, &tmp);
		ReportError((char *)(m_a + 1), (int)(m_b + 1));
		m_b = m_a;
	}
}
