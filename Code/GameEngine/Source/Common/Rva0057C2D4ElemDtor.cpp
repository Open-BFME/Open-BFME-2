// cl: /Ireference/shims/bfme2_ascii /EHsc /MD
// ??1Rva0057C2D4Elem@@QAE@XZ @0x0057C2D4 73B
// Elem dtor destroying TreeHintRef holder at +0x14 then Rva0052413E at +8 then AsciiString at +4.
// Evidence: retail EH_prolog test ecx [esi+0x14] call ReleaseTreeHintRef 0x0007DEEF then lea [esi+8] call 0x0052413E then lea [esi+4] call releaseBuffer 0x00036410; callers 0x0057C320 deleting dtor and 0x0057C3A8 clear; sibling Rva005F8FEEDtor same holder plus Rva plus releaseBuffer pattern.
#include "ascii_string.h"
#include "../../../Libraries/Source/Apt/AptRefTarget.h"
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);
#include "../../Include/Common/Rva0052413E.h"
struct Rva0057C2D4Holder
{
    TargetRef00217D4C *m_ptr;
    ~Rva0057C2D4Holder()
    {
        if (m_ptr)
            ReleaseTreeHintRef00217D4C(m_ptr);
    }
};
class Rva0057C2D4Elem
{
public:
    ~Rva0057C2D4Elem();
private:
    int m_00;
    AsciiString m_04;
    Rva0052413E m_08;
    Rva0057C2D4Holder m_14;
};
Rva0057C2D4Elem::~Rva0057C2D4Elem()
{
}
