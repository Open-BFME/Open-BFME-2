// cl: /EHsc /MD
// ??1Rva0056B126@@UAE@XZ, RVA 0x0056B126, 90 bytes.
// Dtor with three vptrs unregistering via rowed erase 0x002B7250 then base dtor 0x0056AC26.
// Evidence: caller at 0x0056B3D9 is deleting dtor; sibling shape of 0x0056B0BF with holder at parent+4.
class CreateAHeroData;
#include "../../Include/Common/Rva002B7250.h"
struct Parent0056B126 {
    char pad[4];
    Rva002B7250 holder;
};
class Rva0056AC26 {
public:
    virtual ~Rva0056AC26();
private:
    char m_pad04[4];
};
#include "../../Include/Common/Rva0056B126B1.h"
#include "../../Include/Common/Rva0056B126B2.h"
class Rva0056B126 : public Rva0056AC26, public Rva0056B126B1, public Rva0056B126B2 {
public:
    virtual ~Rva0056B126();
private:
    Parent0056B126 *m_parent18;
};
Rva0056B126::~Rva0056B126()
{
    m_parent18->holder.rva002B7250((CreateAHeroData *)(Rva0056B126B2 *)this);
}
