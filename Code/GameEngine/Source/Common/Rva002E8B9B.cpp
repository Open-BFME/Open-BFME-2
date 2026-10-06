// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva002E8B9B@Rva002E8B9B@@QAEPAVMixFileInfoBuffer@@PAUIn002E6BA1@@@Z, retail 0x002E8B9B, 52 bytes.
// Calls rowed Rva0052DBCDInit 0x0052DBCD then rowed Rva002E8B7AInit 0x002E8B7A then stores node.
// Evidence: chain from 0x002E8B7A; global 0x00A049D0 compare plus push; caller none; prev 0x002E8B70 next 0x002E8BCF.
struct In002E6BA1
{
	int m_00;
	int m_04;
};

class MixFileInfoBuffer;

MixFileInfoBuffer *Rva002E8B7AInit(MixFileInfoBuffer **pp, int a, In002E6BA1 *in);

void Rva0052DBCDInit(void);

extern MixFileInfoBuffer *g_00A049D0;

class MixFileInfoBuffer
{
};

class Rva002E8B9B
{
public:
	MixFileInfoBuffer *rva002E8B9B(In002E6BA1 *in);
private:
	MixFileInfoBuffer *m_node;
};

MixFileInfoBuffer *Rva002E8B9B::rva002E8B9B(In002E6BA1 *in)
{
	MixFileInfoBuffer *node = m_node;
	if (node == 0) {
		if (g_00A049D0 == m_node)
			Rva0052DBCDInit();
		return (m_node = Rva002E8B7AInit(&g_00A049D0, (int)this, in));
	}
	*(int *)((char *)node + 0x0C) &= 0;
	return node;
}
// ?g_00A049D0@@3PAVMixFileInfoBuffer@@A: the global at VA 0xe049d0 is ?TheMixFileInfoPool@@3HA.
#pragma comment(linker, "/alternatename:?g_00A049D0@@3PAVMixFileInfoBuffer@@A=?TheMixFileInfoPool@@3HA")
