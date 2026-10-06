// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva002E0C2B@Rva002E0C2B@@QAEHXZ @0x002E0C2B 61B min of this plus 0x25c and minus 100 minus scaled GlobalData field
// Evidence: caller 0x002A9E36 moves Player ptr into ecx then calls; data refs TheWritableGlobalData plus 0xE98 times g_00BCF9B0; neighbours 0x002E0BEB and 0x002E0CD4 share O1; min idiom from Rva002E0CD4Get
class GlobalData
{
public:
	char m_pad[0xE98];
	float m_E98;
};

extern GlobalData *TheWritableGlobalData;
extern float g_00BCF9B0;
// g_00BCF9B0: matched references place it at VA 0xbcf9b0 (retail .rdata value -1e+02f).
float g_00BCF9B0 = -1e+02f;

class Rva002E0C2B
{
public:
	int rva002E0C2B();
private:
	char m_pad[0x25C];
	int m_25C;
};

int Rva002E0C2B::rva002E0C2B()
{
	float f = TheWritableGlobalData->m_E98 * g_00BCF9B0;
	int a = m_25C;
	int b = -100 - (int)f;
	return *(a < b ? &a : &b);
}
