// ?rva005CB723@Rva005CB723@@QAEXPAX@Z
// partial score=0.3 date=2026-10-08
// cl: /MD

void rva005CB46A(void *p);

class Rva005CB723 {
public:
	void rva005CB723(void *p);
private:
	int m_00;
	void *m_04;
	void *m_08;
};

void Rva005CB723::rva005CB723(void *p)
{
	if (m_04 != p) {
		if (m_08 != 0) {
			rva005CB46A(p);
		}
		m_04 = p;
	}
}
