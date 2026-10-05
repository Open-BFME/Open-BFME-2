// cl: /O1 /MD
// ?rva0057A382@Rva0057A382@@QAEXXZ @0x0057A382 39B
// Evidence: caller 0x0057A748 sets +0x58=0 +0x5C=1; callee row ?rva005D3F6D@Rva005D3F6D@@QAEXH@Z; neighbours share /O1 /MD
extern int g_00E06374;
extern int g_00E06378;
extern int g_00E0637C;

class Rva005D3F6DInner;
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

class Rva0057A382
{
public:
	void rva0057A382();
private:
	char m_pad00[8];
	Rva005D3F6D m_08;
	char m_pad38[0x20];
	int m_58;
	bool m_5C;
};

void Rva0057A382::rva0057A382()
{
	int v = g_00E06374;
	if (m_58 == 1)
		v = g_00E06378;
	else if (m_5C != 0)
		v = g_00E0637C;
	m_08.rva005D3F6D(v);
}
