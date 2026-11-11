// cl: /MD
// ?rva000F278F@Rva000F278F@@QAEXXZ 0x000F278F 8B forward to +8 rva000F1AD8 via tail jmp; chain from 0x000F1AD8
#include "../../../GameEngineDevice/Include/W3DDevice/GameClient/W3DShadowGeometryManager.h"
class Rva000F278F {
public:
    void rva000F278F();
private:
    char _p0[8];
    W3DShadowGeometryManager *m_8;
};
void Rva000F278F::rva000F278F()
{
    m_8->rva000F1AD8();
}
