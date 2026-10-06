// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?check@Rva002D3627Host@@QAE_NXZ retail 0x002D3627 23 bytes. Dual byte check
// via global plus member target. Evidence: pin check, caller 0x003FE8F1,
// global g_00DFEF18, no callees.

class Rva002D3627Host
{
public:
	bool check();
private:
	char m_00[0x10];
	Rva002D3627Host *m_10;
	unsigned char m_14;
	char m_15[0x18 - 0x15];
	unsigned char m_18;
	char m_19[0x7C - 0x19];
	unsigned char m_7C;
};

extern Rva002D3627Host *g_00DFEF18;
// g_00DFEF18: matched references place it at VA 0xdfef18 (zero-filled .bss).
Rva002D3627Host * g_00DFEF18;

bool Rva002D3627Host::check()
{
	return g_00DFEF18->m_18 == 0 && m_10->m_7C != 0;
}
