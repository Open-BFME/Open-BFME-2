// cl: /MD
struct Rva0028ECDBAux
{
	unsigned char m_pad[0x11F];
	unsigned char m_11F;
	unsigned char m_pad2[0x123 - 0x120];
	unsigned char m_123;
};
struct Rva002E9897Host;
struct Rva002DFF0F8
{
	unsigned char m_pad[0x10];
	Rva002E9897Host *m_10;
};
extern Rva002DFF0F8 *g_00DFF0F8;
class Rva002E9897Host
{
public:
	bool rva002E9897(void *a, int b);
};
class Rva0028ECDBHost
{
public:
	bool rva0028ECDB(void *a);
private:
	unsigned char m_pad[4];
	Rva0028ECDBAux *m_04;
	unsigned char m_pad2[0x250 - 0x8];
	int m_250;
};
// ?rva0028ECDB@Rva0028ECDBHost@@QAE_NPAX@Z
bool Rva0028ECDBHost::rva0028ECDB(void *a)
{
	Rva0028ECDBAux *aux = m_04;
	if ((aux->m_11F & 0x80) != 0 && (aux->m_123 & 2) != 0 && m_250 != 0 && !g_00DFF0F8->m_10->rva002E9897(a, 1))
		return true;
	return false;
}
