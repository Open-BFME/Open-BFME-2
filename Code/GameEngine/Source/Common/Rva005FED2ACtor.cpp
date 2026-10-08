// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ??0Rva005FED2A@@QAE@HHH@Z @0x005FED2A 35B
// Ctor slot: stores vtable 0x0087A448, base Rva005FF912 at +0 via rowed
// 0x005FF912 with (b,c), int at +8 from (a). Ret 0xC.
// Evidence: disassembly packet lane=unlock, caller 0x005FEFF9, prev/next.
#include "BattlePromptMovieClipView.h"

Rva005FED2A::Rva005FED2A(int a, int b, int c)
	: Rva005FF912(b, c)
{
	m_08 = a;
}
