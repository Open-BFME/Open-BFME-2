// cl: /MD
// ??0Rva005753D1@@QAE@XZ @0x005753D1 12B. Trivial derived ctor delegating to
// rowed base ctor 0x005CC61E. Evidence: same this passed through; returns this.
#include "../../Include/Common/Rva005CC61E.h"
class Rva005753D1 : public Rva005CC61E {
public:
    Rva005753D1();
};
Rva005753D1::Rva005753D1()
{
}
