// cl: /DNDEBUG /MD
//
// ?rva00459109@Rva00459109@@QAEHXZ, retail 0x00459109 75B. Chain via 0x0045906E.
// Float m_10 vs 0 plus minus g_Va00BBB8D8 plus double lt0 plus reset 0 plus
// rva false via this-0x10 plus 0x3fffffff else g_Va00DBA4E4. Prev is 0x45906E.

extern float g_Va00BBB8D8;
extern int g_Va00DBA4E4;

class Rva0045906E
{
public:
	void rva0045906E(bool b);
};

class Rva00459109
{
public:
	int rva00459109();
private:
	unsigned char m_pad00[0x10];
	float m_10;
};

int Rva00459109::rva00459109()
{
	float f = m_10;
	if (!(f > 0.0f))
		return g_Va00DBA4E4;
	float nv = f - g_Va00BBB8D8;
	m_10 = nv;
	if ((double)nv <= 0.0) {
		m_10 = 0.0f;
		((Rva0045906E *)((char *)this - 0x10))->rva0045906E(false);
		return 0x3fffffff;
	}
	return g_Va00DBA4E4;
}
