// cl: /O1 /MD
struct Rva0028F2F8Aux
{
	unsigned char m_pad[0x11F];
	unsigned char m_11F;
};
class Rva002197A6Host
{
public:
	void *rva002197A6(int v);
};
extern Rva002197A6Host *g_00DFE344;
class Rva0028F2F8Host
{
public:
	void *rva0028F2F8();
private:
	unsigned char m_pad[4];
	Rva0028F2F8Aux *m_04;
	unsigned char m_pad2[0x74 - 0x8];
	int m_74;
};
// ?rva0028F2F8@Rva0028F2F8Host@@QAEPAXXZ
void *Rva0028F2F8Host::rva0028F2F8()
{
	if ((m_04->m_11F & 0x40) != 0)
	{
		void *r = g_00DFE344->rva002197A6(m_74);
		if (r == 0)
			return (char *)m_04 + 0x30;
		return (char *)r + 8;
	}
	return (char *)m_04 + 0x30;
}
