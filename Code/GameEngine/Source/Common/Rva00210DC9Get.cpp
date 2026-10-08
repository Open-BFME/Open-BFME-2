// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?Rva00210DC9Get@@YAEXZ, retail 0x00210DC9, 12 bytes.
// Free unsigned-char getter for the 0x00DFEF10 singleton byte at +0xB4.
// Retail: mov eax,[0xDFEF10]; mov al,[eax+0xB4]; ret (dirty high, caller
// tests al only, e.g. 0x0023C8E3 test al,al). Evidence: 3 callers,
// Rva0023C6A4Check +0xB4 pattern, /O1 mov-al size form (not movzx).
// No fallback paths.

class Rva002BA8F1Logic;
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
#define TheRva00DFEF10 (*(void **)&(*(Rva002BA8F1Logic **)&TheLivingWorldLogic))

unsigned char Rva00210DC9Get()
{
	return *(unsigned char *)((char *)TheRva00DFEF10 + 0xB4);
}
