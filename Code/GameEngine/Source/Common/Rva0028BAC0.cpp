// cl: /O1 /MD
class PartitionData
{
public:
	void makeDirty();
};
class PartitionManager
{
public:
	void rva00625330(void *p);
};
class Rva009A36F0Param;
class Rva00758240
{
public:
	void rva00758240(Rva009A36F0Param *p);
};
struct Rva00287C21Other
{
	unsigned char m_pad[0x49C];
	int m_49C;
};
class FireLogicSystem
{
public:
	void UnregisterObject(Rva00287C21Other *o);
};
class Rva00333F37Host
{
public:
	void rva00333F37(void *p);
};
class Rva002A8F56Host
{
public:
	void rva002A8F56(void *p);
};
extern PartitionManager *g_00DFE748;
extern Rva00758240 *g_00DFE754;
extern FireLogicSystem *g_00DFEC68;
extern Rva00333F37Host *g_00E01DBC;
extern Rva002A8F56Host *g_00DFEEF8;
class Rva0028BAC0Host
{
public:
	void rva0028BAC0();
private:
	unsigned char m_pad[0x6C];
	unsigned char m_6C;
	unsigned char m_pad70[0x70 - 0x6D];
	unsigned char m_70;
	unsigned char m_pad454[0x454 - 0x71];
	unsigned char m_454;
	unsigned char m_pad49C[0x49C - 0x455];
	int m_49C;
	unsigned char m_pad4C4[0x4C4 - 0x4A0];
	PartitionData *m_4C4;
	int m_4C8;
	int m_4CC;
};
// ?rva0028BAC0@Rva0028BAC0Host@@QAEXXZ
void Rva0028BAC0Host::rva0028BAC0()
{
	if (m_4C4 != 0)
		m_4C4->makeDirty();
	if (m_4C8 != 0)
		g_00DFE748->rva00625330(&m_6C);
	if (m_4CC != 0)
		g_00DFE754->rva00758240((Rva009A36F0Param*)&m_70);
	if (m_49C >= 0)
	{
		if (g_00DFEC68 != 0)
			g_00DFEC68->UnregisterObject((Rva00287C21Other *)this);
	}
	if (g_00E01DBC != 0)
		g_00E01DBC->rva00333F37(this);
	if (g_00DFEEF8 != 0)
		g_00DFEEF8->rva002A8F56(this);
	m_454 = 0;
}
