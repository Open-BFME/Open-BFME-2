// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva0018C0E7Set@@YAXPAX@Z @0x0018C0E7 10B: store arg to g_00DFCEBC caller 0x0041FD27 passes edi
extern int g_00DFCEBC;

void __cdecl Rva0018C0E7Set(void *p)
{
	g_00DFCEBC = (int)p;
}
