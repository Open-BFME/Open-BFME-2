// cl: /O1 /G7 /DNDEBUG /MD
// ?rva000E585F@Rva006F8700Owner@@QAEXPAX0PAH1@Z @0x000E585F 95B.
// Saves *arg4 at +0x44 and *arg3 at +0x3C, clears +0x40 and +0x48, then
// folds the rowed 0x000E569A result into *arg4 and +0x40 and the
// 0x000E56AF result into *arg3, with that result divided by 3 added at +0x48.

class Rva006F8700Owner
{
public:
	int rva006F8700(void *a, int b, void *c, void *p);
	int rva000E56AF(void *a, int b, int c, void *p);
	void rva000E585F(void *arg1, void *arg2, int *arg3, int *arg4);

	char m_pad[0x28];
	void *m_28;
	char m_pad2[0x10];
	int m_3c;
	int m_40;
	int m_44;
	int m_48;
	char m_pad4c[4];
	int m_50;
};

void Rva006F8700Owner::rva000E585F(void *arg1, void *arg2, int *arg3, int *arg4)
{
	m_44 = *arg4;
	int seen3 = *arg3;
	m_40 = 0;
	m_48 = 0;
	m_3c = seen3;
	int first = rva006F8700(arg2, *arg4, &m_50, m_28);
	int second = rva000E56AF(arg1, *arg3, *arg4, m_28);
	*arg3 += second;
	*arg4 += first;
	m_40 += first;
	m_48 += second / 3;
}
