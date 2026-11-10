// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva00210DC9@Rva00DFE1C8Host@@QAE_NXZ, retail 0x00210DC9, 12 bytes.
// Bool getter for the 0x00DFEF10 singleton byte at +0xB4. Every caller
// (0x0023C8E3, 0x0023D9F7 and GameLogic's init pass) loads the 0x00DFE1C8
// singleton into ecx first, so it is a member of that owner that ignores
// this, spelled as the callers' pin names it.
// Retail: mov eax,[0xDFEF10]; mov al,[eax+0xB4]; ret (dirty high, caller
// tests al only, e.g. 0x0023C8E3 test al,al). Evidence: 3 callers,
// Rva0023C6A4Check +0xB4 pattern, /O1 mov-al size form (not movzx).
// No fallback paths.

class Rva002BA8F1Logic;
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
#define TheRva00DFEF10 (*(void **)&(*(Rva002BA8F1Logic **)&TheLivingWorldLogic))

#include "../../Include/Common/Rva00DFE1C8Host.h"

bool Rva00DFE1C8Host::rva00210DC9()
{
	return *(bool *)((char *)TheRva00DFEF10 + 0xB4);
}
