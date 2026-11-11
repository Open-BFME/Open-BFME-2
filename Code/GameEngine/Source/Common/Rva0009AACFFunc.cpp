// cl: /MD /EHsc /DNDEBUG
//
// ?rva0009AACF@Rva0009C134Host@@QAEXHM@Z @0x0009AACF 44B: clamps the float at >= 0 and forwards the
// render pointer and float to the matched callee 0x0010E87A when the int is nonzero. Retail's callers
// 0x0009BC17 and 0x0009C4FC pass this in ecx, which the body never reads.

class RenderObjClass;
bool Rva0010E87A_SetOpacity(RenderObjClass *,float);
#include "../../../GameEngineDevice/Include/W3DDevice/GameClient/Rva0009C134Host.h"

// ?rva0009AACF@Rva0009C134Host@@QAEXHM@Z
void Rva0009C134Host::rva0009AACF(int b, float a)
{
	if (0.0f >= a)
		a = 0.0f;
	if (b)
		Rva0010E87A_SetOpacity(reinterpret_cast<RenderObjClass *>(b), a);
}
