// cl: /MD /EHsc
// ?rva0025C4A4@Display@@QAEHH@Z @0x0025C4A4 79B evidence: same class Display as neighbours rva0025C46E in BfmeConv1435.cpp with mutexes at +0x40 +0x44; guarded virtual slot +0x18c with arg 3 via BFMEDX8DeviceLock RAII Lock 0x0011F520 Assert 0x00120F50; ret 4 one int arg int return for xor eax epilogue
void BFME_DX8_Thread_Lock();
bool BFME_DX8_Thread_Assert();

#include "../../../GameEngineDevice/Include/W3DDevice/GameClient/BFMEDX8DeviceLock.h"

#include "../../Include/GameClient/Display.h"

int Display::rva0025C4A4(int flag)
{
	if (flag != 0 || (field40 == 0 && field44 == 0)) {
		BFMEDX8DeviceLock guard;
		slot99(3);
	}
	return 0;
}
