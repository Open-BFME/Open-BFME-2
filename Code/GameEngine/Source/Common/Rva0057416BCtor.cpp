// platformsdk
// ??0Rva0057416B@@QAE@XZ retail 0x0057416B 19 bytes.
// Default ctor: m_time = timeGetTime(); m_flag = false; returns this.
// Evidence: member init via lea ecx [esi+8] in ctors 0x005CF8A1 and 0x005E9FC1;
// heap init via new 8 then mov ecx eax in 0x0042C342 at 0x0042C4F1 and 0x0042C598;
// neighbour 0x00574192 throttles on [esi] timestamp and [esi+4] flag with STRATEGICHUD WaitMessage.

#include <windows.h>
#include "../../Include/Common/Rva0057416B.h"

Rva0057416B::Rva0057416B()
{
	m_time = timeGetTime();
	m_flag = false;
}
