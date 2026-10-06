// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?Rva0018C0F1Clear@@YAXXZ @0x0018C0F1 8B
// Zero dword at g_00DFCEBC via and-0 idiom. Evidence: and dword plus ret,
// no name yet so g_VA, 1 caller, honest Clear verb.
extern int g_00DFCEBC;
// g_00DFCEBC: matched references place it at VA 0xdfcebc (zero-filled .bss).
int g_00DFCEBC;

void __cdecl Rva0018C0F1Clear()
{
	g_00DFCEBC = 0;
}
