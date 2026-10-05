// cl: /O1 /MD
class Rva002856CFHost;
class Rva0020D8F1Host
{
public:
	void rva0020D8F1(Rva002856CFHost *o);
};
struct Rva00DFE1A8
{
	unsigned char m_pad[0x3C];
	int m_3C;
};
extern Rva0020D8F1Host *g_00DFE1A8;
struct Rva002DFE78C
{
	unsigned char m_pad[0x40];
	int m_40;
};
extern Rva002DFE78C *g_00DFE78C;
class Rva002856CFHost
{
public:
	void rva002856CF();
private:
	unsigned char m_pad[0x10];
	int m_10;
};
// ?rva002856CF@Rva002856CFHost@@QAEXXZ
void Rva002856CFHost::rva002856CF()
{
	if (m_10 != -1)
		return;
	if (((Rva00DFE1A8 *)g_00DFE1A8)->m_3C < -1)
		return;
	((Rva0020D8F1Host *)g_00DFE1A8)->rva0020D8F1(this);
	m_10 = g_00DFE78C->m_40;
}
