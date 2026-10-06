// cl: /MD
class Rva0028572AHost;
class Rva0020D959Host
{
public:
	void rva0020D959(Rva0028572AHost *o);
};
extern Rva0020D959Host *g_00DFE1A8;
class Rva0028572AHost
{
public:
	void rva0028572A();
private:
	unsigned char m_pad[0x10];
	int m_10;
};
// ?rva0028572A@Rva0028572AHost@@QAEXXZ
void Rva0028572AHost::rva0028572A()
{
	if (m_10 != -1)
	{
		g_00DFE1A8->rva0020D959(this);
		m_10 = -1;
	}
}
