// cl: /MD
#include "../../Include/GameClient/AptSaveLoad.h"
// ?Rva00433D27Enable@@YAXXZ @0x00433D27 21B: if AptSaveLoad::s_instance==0 return else tail-jmp Rva00222479ByteOneSetter::enable via TheRva00222A8BTarget; callers 0x002B8875 0x00433DAC
class Rva00222A8BTarget;
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;
#include "../../Include/Common/Rva00222479ByteOneSetter.h"
void Rva00433D27Enable()
{
	if (AptSaveLoad::s_instance == 0)
		return;
	((Rva00222479ByteOneSetter *)(*(Rva00222A8BTarget **)&g_bfmeAptWindowManager))->enable();
}
